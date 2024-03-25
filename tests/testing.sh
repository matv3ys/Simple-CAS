#!/bin/bash

cd ..
make

if [ $? -ne 0 ]; then
    echo "Compilation error"
    exit 1
fi

for i in {1..20}; do
    input_file="./tests/test${i}.txt"
    output_file="./tests/output${i}.txt"

    actual_output=$(./psf < "$input_file")

    cmp --silent "$output_file" <(echo "$actual_output")
    cmp_result=$?

    if [ $cmp_result -eq 0 ]; then
        echo "Test $i: Passed"
    else
        echo "Test $i: Not passed"
        cmp "$output_file" <(echo "$actual_output")
        echo "Expected: $(cat $output_file)"
        echo "Actual: $actual_output"
    fi
done
