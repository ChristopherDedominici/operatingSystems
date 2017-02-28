#!/bin/bash

AWK_SCRIPT="translate.awk"
opts="hlsn:v-:"
help_msg="Utilizzo: traduci.sh [options] <vocabolario> <fileDaTradurre> <fileProdotto> \


  Traduce ogni parola contenuta in <fileDaTradurre> mediante le informazioni di traduzione
  contenute in <vocabolario>. Scrive il risultato della traduzione in <fileProdotto>.

  OPZIONI
    -h, --help: 
        Stampa la sintassi del comando ed esce.
    -l, --longest: 
        Sostituisce ad ogni parola la traduzione più lunga disponibile.
    -s, --shortest: 
        Sostituisce ad ogni parola la traduzione più corta disponibile (default).
    -n Num:
        Sostituisce ad ogni parola la Num-esima traduzione disponibile.
    -v, --verbose: 
        Stampa un messaggio di warning per ogni parola di cui non viene trovata una 
        traduzione."
warning_msg="Warning! Traduzione non trovata"
match_shortest=1
is_verbose=0
to_match=0


#PROCESS OPTIONS
while getopts "$opts" opt; do
	case "$opt" in
		-)
			case "${OPTARG}" in
				help)
					echo "$help_msg"
					exit 0
					;;
				longest)
					match_shortest=0
					;;
				shortest)
					match_shortest=1
					;;
				verbose)
					is_verbose=1
					;;
				*)
					if [ "$OPTERR" = 1 ] && [ "${opts:0:1}" != ":" ]; then
          	echo "Unknown option --${OPTARG}" >&2
          	exit 1
          fi
			esac
			;;
		h)
			echo "$help_msg"
			exit 0
			;;
		l)
			match_shortest=0
			;;
		s)
			match_shortest=1
			;;
		n)
			to_match=${OPTARG}
			echo $to_match
			;;
		v)
			is_verbose=1
			;;
	esac
done

#PROCESS ARGUMENTS
shift $((OPTIND-1))
if test $# -ne 3
then
	echo "$help_msg"
	exit 1
fi
dict=$1
input_file=$2
output_file=$3

#TRANSLATE
rm $output_file
is_first_line=1
while read line; do
	if [[ $is_first_line -eq 0 ]]; then
		echo "" >> $output_file
	fi
	is_first_line=0
		
	is_first_word=1
	for word in $line; do
		
		if [[ $is_first_word -eq 0 ]]; then
			echo -n " " >> $output_file
		fi
		is_first_word=0
		
		translation=$(awk -v word=$word -v n=$to_match -v ms=$match_shortest -f $AWK_SCRIPT $dict)
		if [[ $translation == "" ]]; then
			if [[ is_verbose -eq 1 ]]; then
				echo "$warning_msg: $word."
			fi
			echo -n $word >> $output_file
		else 
			echo -n $translation >> $output_file
		fi
	done
done < $input_file
