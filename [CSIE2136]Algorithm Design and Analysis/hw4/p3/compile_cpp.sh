#!/bin/bash

problem=ada-hw4-p3

g++ -O2 -std=c++17 grader.cpp $problem.cpp -o 3
# g++ -O2 -std=c++17 grader.cpp others.cpp -o 3