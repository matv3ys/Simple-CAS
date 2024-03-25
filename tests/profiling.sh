#!/bin/bash

cd ..
make profiling
./psf < "./tests/data/test$1.txt" > /dev/null
gprof -b psf gmon.out | cat
rm gmon.out