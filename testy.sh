#!/bin/bash
g++ -std=c++11 ./wzor.cpp -o wzor
g++ -std=c++11 ./gen.cpp -o gen
g++ -std=c++11 ./brut.cpp -o brut
for((i=1;;i++))
do

  ./gen $i > ./tests/test_$i.in
  ./wzor < ./tests/test_$i.in > ./tests/wzor_$i.out
  ./brut < ./tests/test_$i.in > ./tests/brut_$i.out
   if ! diff -bq ./tests/wzor_$i.out ./tests/brut_$i.out; then
    echo "different"
    break
    fi
done
