#!/usr/bin/sh

for testname in ./tests/*.dat; do
    ans="$(cat ${testname%.*}.ans)"  
    res="$(./problem_hwe.out < $testname)"

    if [ $res = $ans ]; then
        echo $testname "Passed"
    else
        echo $testname "Failed: expected" $ans "got" $res
    fi
done