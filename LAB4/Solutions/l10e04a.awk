function traduci_e_stampa (parola, vocabolario)
{
	if(parola in vocabolario){
		num = split(vocabolario[parola], traduzioni, "\n");	
		num_trad = num-2;			# perche' splittando con il '\n' si formano all'inizio e alla fine del vettore due parole "vuote"
		if(strategy > 0){
			if(num_trad >= strategy){
				printf("%s ", traduzioni[strategy+1]) >> result; 
			}
			else{
				printf("%s ", parola) >> result;
				if(verbose == 1){
					printf("Traduzione non trovata per \'%s\'\n", parola);
				}
			}
		}
		else if(strategy == 0){
			max_l = 0;
			max_ind = 1;
			for(j=1; j<=num_trad; j++){
				if(length(traduzioni[j+1]) > max_l){
					max_l = length(traduzioni[j+1]);
					max_ind = j+1;
				}
			}
			printf("%s ", traduzioni[max_ind]) >> result;
		}
		else{
			min_l = 100;
			min_ind = 1;
			for(j=1; j<=num_trad; j++){
				if(length(traduzioni[j+1]) < min_l){
					min_l = length(traduzioni[j+1]);
					min_ind = j+1;
				}
			}
			printf("%s ", traduzioni[min_ind]) >> result;
		}
	}
	else{
		printf("%s ", parola) >> result;
		if(verbose == 1){
			printf("Traduzione non trovata per \'%s\'\n", parola);
		}
	}
}



BEGIN{
	RS = "#"
	FS = ":"

	while(getline < voc){
		gsub("\n", "", $1);		#serve per togliere il '\n' all'inizio della parola (successivo al carattere #)
		vocabolario[$1] = $2;
	}

	RS = "\n"
	FS = " "

	rm_result = sprintf("rm -f %s", result);
	system(rm_result);
}


{
	for(i=1; i<NF; i++){
		traduci_e_stampa($i, vocabolario)
	}	

	printf("\n");
}
