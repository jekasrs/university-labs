#!/bin/sh

printInfo()
{
 echo "Spent time:"
 time -p ./a.out
 echo "Disk usage:"
 stat -f%z a.out
}

if [ "$#" -eq 1 ]
then
    echo "Part 1:"
   count=1
   for i in "-O0" "-O1" "-O2" "-O3" "-Os" "-O2 -march=native" "-O3 -march=native" "-O2 -march=native -funroll-loops" "-O3 -march=native -funroll-loops"
   do
       echo "Test #$count with optimization $i"
        g++-11 -Wall $i $1 -lm
        printInfo
        echo "________________________________"
        count=$(($count + 1))
   done

    echo "Part 2:"

    echo "Test with optimization: -O2 -march=native -fipa-pta -flto"
    g++-11 -Wall -O3 -march=native -fipa-pta -flto $1 -lm
    printInfo
    echo "________________________________"

    echo "Test with optimization: -O2 -march=native -fprofile-generate -fprofile-use"
    g++-11 -O3 -march=native -fprofile-generate -Wall $1 -lm
    ./a.out
    g++-11 -O3 -march=native -fprofile-use -Wall $1 -lm
    printInfo
    echo "________________________________"

    echo "Test with optimization: -O2 -march=native -fprofile-generate -fprofile-use -fipa-pta -flto"
    g++-11 -O3 -march=native -fprofile-generate -Wall $1  -lm
    g++-11 -O3 -march=native -fprofile-use -fipa-pta -flto -Wall $1 -lm
    printInfo
    echo "________________________________"

echo

else
	echo "ERROR: Wrong arguments"
fi