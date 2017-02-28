#!/usr/bin/awk -f

BEGIN{
	getline
	getline days
	split(days, days_names)
	formatted_day = sprintf("%01d", day)
	pattern="\\<"formatted_day"\\>" #Formatted day as a word
}

$0 ~ pattern{
	for(i=1;i<=NF;++i){
		if($i~pattern) print days_names[i]
	}
}
