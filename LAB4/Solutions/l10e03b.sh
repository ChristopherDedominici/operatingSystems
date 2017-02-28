#!/bin/bash

AWK_SCRIPT="es03.awk"

if test $# -ne 3
then
	echo "Usage: $0 gg mm yyyy"
	exit 1
fi

cal $2 $3 | awk -v day=$1 -f $AWK_SCRIPT
