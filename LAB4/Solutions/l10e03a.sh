#!/bin/bash

if [ $# -ne 3 ]
then
  echo "Usage: $0 gg mm yyyy"
  exit 1
fi

cal $2 $3 | awk -v day=$1 '

BEGIN {
  getline; 
  getline;
  for(i=1; i<=NF; i++){
    days[i] = $i;
  }
}

{
  if(NR == 3){
    for(i=1; i<=NF; i++){
      if($i == day){
        print days[7-NF+i];
      }
    }
  } else {
    for(i=1; i<=NF; i++){
      if($i == day){
        print days[i];
      }
    }
  }
}

'