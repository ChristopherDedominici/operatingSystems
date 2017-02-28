#!/bin/bash

###
### VARIABLES
###

num_options=0
n_param=0
verbose=0
longest_search=0
shortest_search=0
number_search=0

#print help message
function printHelp ()
{
	echo
	echo "Usage: " $0 " [options] vocabolario file_da_tradurre output"
	echo 

	#options
	echo; echo; echo
	echo " Le opzioni possibili sono:"
	echo; echo
	echo "   -h,"
	echo "   --help:"
	echo "			stampa questo messaggio"
	echo
	echo "   -l,"
	echo "   --longest:"
	echo "			sostituisce con la traduzione piu\` lunga (default)"
	echo
	echo "   -s,"
	echo "   --shortes:"
	echo "			sostituisce con la traduzione piu\` corta"
	echo
	echo "   -n Num"
	echo "			sotituisce con la Num-esima traduzione"
	echo
	echo "   -v,"
	echo "   --verbose:"
	echo "			stampa un warning per ogni parola non tradotta."
}




## MANAGE PARAMETERS ##


#loop onto params looking for options
for command in $*
do

	num_options=$[$num_options + 1]

	#known params
	if [ $n_param -eq 1 ]
	then 
		number_search=$command
		n_param=0;
	
	#unknown params
	elif [ $command == "-h" -o $command == "--help" ]
	then
		printHelp
		exit
	elif [ $command == "-l" -o $command == "--longest" ]
	then
		longest_search=1
	elif [ $command == "-s" -o $command == "--shortest" ]
	then
		shortest_search=1
	elif [ $command == "-n" ]
	then
		n_param=1
	elif [ $command == "-v" -o $command == "--verbose" ]
	then
		verbose=1

	# mandatory params --> decrement num_options
	else
		num_options=$[$num_options - 1]
	fi

done

###
### do some tests on parameters
###

#test number of mandatory params
if [ $[$# - $num_options] -lt 3 ]
then
	echo "ERROR:  some parameter is missing"	
	echo
	printHelp
	exit
fi

#test if the parameter of -n option is a number 
echo $number_search | grep "^[0-9]\+$" &> /dev/null
if [ $? -ne 0 ]
then
	echo "ERROR: -n options must be followed by an integer value"
	echo
	printHelp
	exit
fi

#test exclusive options
if [ $shortest_search -eq 0 -a $longest_search -eq 0 -a $number_search -eq 0 ]
then
	longest_search=1
elif [ $number_search -eq 0 ]
then
	if [ $(($longest_search+$shortest_search)) -gt 1 ]
	then 
		echo "ERROR:  only one option among -l, -s and -n can be specified"	
		echo
		printHelp
		exit
	fi
else
	if [ $(($longest_search+$shortest_search)) -gt 0 ]
	then 
		echo "ERROR:  only one option among -l, -s and -n can be specified"	
		echo
		printHelp
		exit
	fi
fi


###
### EXECUTE THE AWK SCRIPT
###
search_strategy=0				#search strategy is 0 if -l, -1 if -s, or > 0 if -n option is specified
if [ $shortest_search -eq 1 ]
then
	search_strategy=-1
elif [ $number_search -ne 0 ]
then
	search_strategy=$number_search
fi

awk -v strategy=$search_strategy -v verbose=$verbose -v voc="${BASH_ARGV[2]}" -v result="${BASH_ARGV[0]}" -f traduci.awk ${BASH_ARGV[1]} 	#leggere bene il man di bash per la spiegazione di come usare le variabili BASH_ARGV e BASH_ARGC
