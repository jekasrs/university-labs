#!/bin/sh

number=$1
if [ $number -lt 0 ]
then
    echo "Invalid number!"
    exit
fi

 if [ $2 -eq "2" ]
 then
  while [ $number -gt 0 ]
  do
    binary=$(($number % 2))$binary
    number=$(($number / 2))
  done
  echo $binary
 elif [ $2 -eq "10" ]
 then 
  decimal=0
  power=1
  len=${#number}
  i=0
  while [ $i -ne $len ]
  do
    currentDigit=$((number % 10))
    if [ $currentDigit -gt 1 ]
    then
      echo "Invalid number!"
      exit
    fi
    if [ $currentDigit -eq 1 ]
    then
      decimal=$((decimal + power))
    fi
    #echo $power
    power=$((power * 2))
    number=$((number / 10))
    i=$((i + 1))
  done
  echo $decimal
 else
 echo "Invalid flag!"
fi
