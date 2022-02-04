#!/bin/sh

if [ $# -ne "2" ]
then
  echo "Invalid number of parameters!"
  exit
fi

head -n $[$1+$2-1] ~/Desktop/labs_linux/example.txt | tail -n $2

cat ~/Desktop/labs_linux/example.txt | sed -n $1,+$2p
