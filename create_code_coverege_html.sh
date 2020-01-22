#!/bin/bash

rm -r build
mkdir build
cd build
cmake ..
make Test
./Test
cd ..

lcov --directory ./build/CMakeFiles/Test.dir/ --capture --output-file ./code_coverage.info -rc lcov_branch_coverage=1
genhtml code_coverage.info --branch-coverage --output-directory ./code_coverage_report/