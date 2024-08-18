#!/bin/bash

# Color Definitions
RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell

function clean_output() {
    sed -e 's/^[^>]*> //' -e 's/^[^\$]*\$ //' -e 's/\[\[.*\]\]//g'
}

function exec_test() {
    # Run command in minishell
    OUTPUT=$(echo "$@" | ./minishell 2>&- | clean_output)
    ES_1=$?
    # Run command in bash
    EXPECTED=$(echo "$@" | bash 2>&-)
    ES_2=$?
    
    if [ "$OUTPUT" == "$EXPECTED" ] && [ "$ES_1" == "$ES_2" ]; then
        printf " $BOLDGREEN%s$RESET" "✓ "
    else
        printf " $BOLDRED%s$RESET" "✗ "
    fi
    
    printf "$CYAN \"$@\" $RESET"
    
    if [ "$OUTPUT" != "$EXPECTED" ]; then
        echo
        echo
        printf "$BOLDRED Your output : \n%.20s\n$BOLDRED$OUTPUT\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
        printf "$BOLDGREEN Expected output : \n%.20s\n$BOLDGREEN$EXPECTED\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
    fi
    
    if [ "$ES_1" != "$ES_2" ]; then
        echo
        echo
        printf "$BOLDRED Your exit status : $BOLDRED$ES_1$RESET\n"
        printf "$BOLDGREEN Expected exit status : $BOLDGREEN$ES_2$RESET\n"
    fi
    
    echo
    sleep 0.1
}

printf "$BOLDMAGENTA"
printf " __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \ | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

# ECHO TESTS
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'

# CD TESTS
exec_test 'cd .. && pwd'
exec_test 'cd /Users && pwd'
exec_test 'cd && pwd'
exec_test 'mkdir test_dir && cd test_dir && rm -rf ../test_dir && cd . && pwd && cd . && pwd && cd .. && pwd'

# PIPE TESTS
exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
exec_test 'echo test | cat -e | cat -e | cat -e | cat -e'
exec_test 'cat /dev/random | head -c 100 | wc -c'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'

# ENV EXPANSIONS + ESCAPE
exec_test 'echo test     \    test'
exec_test 'echo \"test'
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo test "" test "" test'
exec_test 'echo "\$TEST"'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$?TEST"'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$1TEST"'
exec_test 'echo "$T1TEST"'

# ENV EXPANSIONS
ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
exec_test 'export ='
exec_test 'export 1TEST= && env | sort | grep -v SHLVL | grep -v _='
exec_test 'export TEST && export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD'
exec_test 'export ""="" && env | sort | grep -v SHLVL | grep -v _='
exec_test 'export TES=T="" && env | sort | grep -v SHLVL | grep -v _='
exec_test 'export TE+S=T="" && env | sort | grep -v SHLVL | grep -v _='
exec_test 'export TEST=LOL && echo $TEST && env | sort | grep -v SHLVL | grep -v _='
exec_test 'export TEST=LOL && echo $TEST$TEST$TEST=lol$TEST'
exec_test 'export TEST=LOL && export TEST+=LOL && echo $TEST && env | sort | grep -v SHLVL | grep -v _='
exec_test 'env | sort | grep -v SHLVL | grep -v _='
exec_test 'export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD'
exec_test 'export TEST="ls       -l     - a" && echo $TEST && $LS && env | sort | grep -v SHLVL | grep -v _='

# REDIRECTIONS
exec_test 'echo test > ls && cat ls'
exec_test 'echo test > ls && echo test >> ls && cat ls'
exec_test '> lol echo test lol && cat lol'
exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test && cat test'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'

# MULTI TESTS
exec_test 'echo testing multi && echo "test 1 && | and 2" && cat tests/lorem.txt | grep Lorem'

# SYNTAX ERROR
exec_test 'echo > <'
exec_test 'echo | |'
exec_test '<'

# EXIT
exec_test "exit 42"
exec_test "exit 42 53 68"
exec_test "exit 259"
exec_test "exit 9223372036854775807"
exec_test "exit -9223372036854775808"
exec_test "exit 9223372036854775808"
exec_test "exit -9223372036854775810"
exec_test "exit -4"
exec_test "exit wrong"
exec_test "exit wrong_command"
exec_test "gdagadgag"
exec_test "ls -Z"
exec_test "cd gdhahahad"
exec_test "ls -la | wtf"

rm lol ls test

