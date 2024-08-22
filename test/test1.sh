# MINISHELL-TESTER

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
# make -C ../ > /dev/null
# cp ../minishell .
# chmod 755 minishell

function exec_test2()
{
	TEST2=$(echo $@ | bash 2>&-)
	ES_2=$?
	printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	echo
	echo
	sleep 0.1
}
function exec_test1()
{
	echo -e $BOLDYELLOW$@ 
	
	TEST1=$(echo $@ | ./minishell 2>&-)
	ES_1=$?
	printf $BOLDBLUE"Your output : \n%.20s\n$BOLDBLUE$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	printf $BOLDBLUE"Your exit status : $BOLDBLUE$ES_1$RESET\n"
	echo
	sleep 0.1
}

printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo

# FIRST TESTS
exec_test1 'date'
exec_test2 'date'
exec_test1 '/bin/ls'
exec_test2 '/bin/ls'
exec_test1 'who'
exec_test2 'who'

# ECHO TESTS
exec_test1 'echo test   tout'
exec_test2 'echo test   tout'
exec_test1 '"echo test      tout"'
exec_test2 '"echo test      tout"'
exec_test1 'echo -n test tout'
exec_test2 'echo -n test tout'
exec_test1 'echo -n -n -n test tout'
exec_test2 'echo -n -n -n test tout'
exec_test1 'echo ''$USER'''
exec_test2 'echo ''$USER'''
exec_test1 'echo "$USER"'
exec_test2 'echo "$USER"'

# ENV EXPANSIONS + ESCAPE
# exec_test1 'env'
# exec_test2 'env'
# exec_test1 'env PATH'
# exec_test2 'env PATH'
# exec_test1 'echo $TEST'
# exec_test2 'echo $TEST'
# exec_test1 'echo "$TEST"'
# exec_test2 'echo "$TEST"'
# exec_test1 "echo '$TEST'"
# exec_test2 "echo '$TEST'"
# exec_test1 'echo "   $TEST lol $TEST"'
# exec_test2 'echo "   $TEST lol $TEST"'
# exec_test1 'echo $TEST$TEST$TEST'
# exec_test2 'echo $TEST$TEST$TEST'
# exec_test1 'echo $TEST$TEST=lol$TEST""lol'
# exec_test2 'echo $TEST$TEST=lol$TEST""lol'
# exec_test1 'echo    $TEST lol $TEST'
# exec_test2 'echo    $TEST lol $TEST'
# exec_test1 'echo test "" test "" test'
# exec_test2 'echo test "" test "" test'
# exec_test1 'echo "$=TEST"'
# exec_test2 'echo "$=TEST"'
# exec_test1 'echo "$"'
# exec_test2 'echo "$"'

# # # ENV EXPANSIONS
# # ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
# # EXPORT_SHOW="export"
# # exec_test1 'export ='
# # exec_test2 'export ='
# # exec_test1 'export 1TEST= '
# # exec_test1 $ENV_SHOW
# # exec_test2 'export 1TEST= ;' $ENV_SHOW
# # exec_test1 'export TEST=test'
# # exec_test1 $EXPORT_SHOW
# # exec_test2 'export TEST=test;' $EXPORT_SHOW
# # exec_test1 'export ""="" ; ' $ENV_SHOW
# # exec_test1 'export TES=T="" ;' $ENV_SHOW
# # exec_test1 'export TE+S=T="" ;' $ENV_SHOW
# # exec_test1 'export TEST=LOL ; echo $TEST ;' $ENV_SHOW
# # exec_test1 'export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST'
# # exec_test1 'export TEST=LOL; export TEST+=LOL ; echo $TEST ;' $ENV_SHOW
# # exec_test1 $ENV_SHOW
# # exec_test1 $EXPORT_SHOW
# # exec_test1 'export TEST="ls       -l     - a" ; echo $TEST ; $LS ; ' $ENV_SHOW

# # REDIRECTIONS
# exec_test1 'echo test > ls'
# exec_test1 'cat ls'
# exec_test2 'echo test > ls ; cat ls'
# exec_test1 'echo test > ls >> ls >> ls'
# exec_test1 'echo test >> ls'
# exec_test1 'cat ls'
# exec_test2 'echo test > ls >> ls >> ls ; echo test >> ls; cat ls'
# exec_test1 '> lol echo test lol'
# exec_test1 'cat lol'
# exec_test2 '> lol echo test lol; cat lol'
# # exec_test1 '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
# # exec_test2 '>lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test'
# exec_test1 'cat < ls'
# exec_test2 'cat < ls'
# exec_test1 'cat < ls > ls'
# exec_test2 'cat < ls > ls'

# # PIPE TESTS
# exec_test1 'cat tests/lorem.txt | grep arcu | cat -e'
# exec_test2 'cat tests/lorem.txt | grep arcu | cat -e'
# # exec_test1 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
# # exec_test2 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
# exec_test1 'cat /dev/random | head -c 100 | wc -c'
# exec_test2 'cat /dev/random | head -c 100 | wc -c'
# # exec_test1 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
# # exec_test2 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'

# # SYNTAX ERROR
# exec_test1 ';; test'
# exec_test2 ';; test'
# exec_test1 '| test'
# exec_test2 '| test'
# exec_test1 'echo > <'
# exec_test2 'echo > <'
# exec_test1 'echo | |'
# exec_test2 'echo | |'
# exec_test1 '<'
# exec_test2 '<'

# # EXIT
# exec_test1 "exit 42"
# exec_test2 "exit 42"
# exec_test1 "exit 42 53 68"
# exec_test2 "exit 42 53 68"
# exec_test1 "exit 259"
# exec_test2 "exit 259"
# exec_test1 "exit 9223372036854775807"
# exec_test2 "exit 9223372036854775807"
# exec_test1 "exit -9223372036854775808"
# exec_test2 "exit -9223372036854775808"
# exec_test1 "exit 9223372036854775808"
# exec_test2 "exit 9223372036854775808"
# exec_test1 "exit -9223372036854775810"
# exec_test2 "exit -9223372036854775810"
# exec_test1 "exit -4"
# exec_test2 "exit -4"
# exec_test1 "exit wrong"
# exec_test2 "exit wrong"
# exec_test1 "exit wrong_command"
# exec_test2 "exit wrong_command"
# exec_test1 "gdagadgag"
# exec_test2 "gdagadgag"
# exec_test1 "ls -Z"
# exec_test2 "ls -Z"
# exec_test1 "cd gdhahahad"
# exec_test2 "cd gdhahahad"
# exec_test1 "ls -la | wtf"
# exec_test2 "ls -la | wtf"

# rm lol ls