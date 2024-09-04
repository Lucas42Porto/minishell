# minishell

The existence of shells is linked to the very existence of IT.
At the time, all developers agreed that communicating with a computer using aligned
1/0 switches was seriously irritating.
It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat
close to the human language.

## Concepts

In this project our own shell should primarily be based on the bash shell. We don't need to create a new window/ tabs our vertical splits like our iTerm. Our assignment consists in creating a ./minishell executable that when opened, will show a prompt (minishel->) and wait for user input. The user can then type any shell commands like echo, ls, env export, pwd and we will show the same information / error messages as bash. Fun fact: We can call other executables inside our minishell, including minishell itself. So we can type ./minishell to enter our minishell then ./minishell again. We will then have to exit twice to finish all our programs.


## How it works

1. The program dont need receives a parameter.
2. The program starts a loop where it waits for and receives input from the user via the command line.
3. The program operates recursively in an "infinite" loop, with a flag used to check whether the program should continue running.
4. For each new line entered by the user, the program saves it to the history and begins parsing, creating structures, and organizing them for proper execution.
5. 

## How to use
To compile this program, run the following commands:
```bash
make
```
Then, to run the program, run the following command:
```bash
./minishell
```

## Memory leaks test
For test memory leaks, run:
```bash
make leaks
```

## Tests
Due to the complexity and variety of implementations we had to carry out, we opted to create our own test, based on the reference test (aaaa), to assist with testing. It is also possible to view the output and compare it to see if it matches the output from bash. We have made it available as an option in the Makefile if you wish to try it out. 

Test1, In our initial test, we only included the basic functionality to test simple command execution and the echo command in various situations. 
For test1, run:
```bash
make test1
```

Test2, is where the fun begins, as it involves testing redirections, pipes, syntax errors, exit commands, and other commands that require careful handling to ensure our program runs smoothly.
Or:
```bash
make test2
```
