#!/usr/bin/awk -f

BEGIN{
	#AVOID PUNTCUATION TO BE INTERPRETED AS REGEXP SYMBOLS
	res=match(word, "[[:punct:]]")
	if(res != 0) exit 1
	pattern = "^"word":$"
}

$0 ~ pattern {
	if(n == 0){
		shortest=""
		longest=""
		getline
		while($0 != "#"){
			if(shortest=="" || length($0) < length(shortest)) shortest=$0
			if(longest=="" || length($0) > length(longest)) longest=$0
			getline
		}
		if(shortest == ""){
			exit 1
		} else if(ms == 1){
			printf("%s",shortest)
			exit 0
		} else if(ms == 0){
			printf("%s",longest)
			exit 0
		}
		
	} else {
		i=n-1
		getline
		while($0 != "#" && i>0){
			getline
			i--
		}
		if($0 == "#") exit 1
		else{
			printf("%s",$0)
			exit 0
		}
	}
}

END {
	exit 1
}
