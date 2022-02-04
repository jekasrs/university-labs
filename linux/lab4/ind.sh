#!/bin/sh
if [ $# -ne "1" ]
 then 
   echo "Invalid number of parameters."
   exit 1
 fi

re='(^[-+]*([0-9])+$)'
if ! [[ $1 =~ $re ]] 
then
   echo "Error: Not a number" 
   exit 1
fi

if [ $1 -lt 3 ]
then
    echo "Invalid number - less then 3!"
    exit 1
fi

if [ $(($1 % 2)) -ne 1 ]
then
    echo "Invalid number - countable!"
    exit 1
fi

number=$1

z=1
for (( i=0; i<$((($number/2)+1)); i++ ))
    do  
        line=" "
        nextchar=$((($number-z)/2))
        for (( j=0; j<$nextchar; j++ ))
            do
            line+="  "
            done
        line+="*"
        for (( k=0; k<$(($z-1)); k++ ))
            do
            line+="_"
            line+="*"
            done
        echo "$line"
        z=$(($z+2))
    done

    z=$(($number-2))

    for (( i=$(($number/2)); i>0; i-- ))
    do  
        line=" "
        nextchar=$((($number-z)/2))
        for (( j=0; j<$nextchar; j++ ))
            do
            line+="  "
            done
        line+="*"
        for (( k=0; k<$(($z-1)); k++ ))
            do
            line+=" "
            line+="*"
            done
        echo "$line"
        z=$(($z-2))
    done