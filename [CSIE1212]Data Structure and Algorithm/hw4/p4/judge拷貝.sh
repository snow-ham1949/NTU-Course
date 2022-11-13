#! /usr/bin/env bash python
# gcc main.c -o main
gcc main.c -o main
for ((i = 0 ; i < 10 ; i++)); do
    python3 testcase.py
    python3 correct.py
    timeout --preserve-status 3s ./main < test.in > out.out
    exit_code=$?
    res=$(diff test.out out.out)
    if [[ exit_code -ne 0 ]]; then
        echo -e "${i}\tTime Limit Exceeded"
        break
    elif [[ -z ${res} ]]; then
        echo -e "${i}\tAccepted"
    else
        echo -e "${i}\tWrong Answer"
        break
    fi
done