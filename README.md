![logo](images/logo.png)
# Minishell!
We are Hugo and Thibault, our team name is <b>Über Tigo</b>

This is a project done during our cursus at [42 School](https://42.fr/en/homepage/). The assignement was to code a little [ shell ](https://en.wikipedia.org/wiki/Shell_(computing))

# Install
To install Shellpticflesh, you will need :
- `git` to clone the repo (optional, you can just download it if you feel audacious)
- `gcc` to compile the .c files and launch the Makefile
- `readline` and `readline devel` (readline development tools) for the prompt
- `curses` and `curses devel` (curses development tools) for tetris.<br>
Note that readline and curses are often already installed on freshly installed linux and mac distros.<br>
Shellpticflesh isn't designed to be portable to Windows due to the contraints of the exercise ! If you want to launch it, please be sure to run it on a Linux-based or MacOS-based computer.<br>
The shell is also only made for x86_64 architectures. Other CPU architectures may result in undefined behaviour in the Tetris game and the $$ parameter.

# Main functionalities
Here are the main functionalities of our Shellpticflesh !
## At the start
The shell doesn't start if STDIN, STDOUT and STDERR aren't TTY, for safety reasons.<br>
The shell then launches the history, and asks the user for a prompt.<br>
### Shell arguments
- `-c` or `--compute` will execute the next argument, and exit the shell with its return status.
- `-n` or `--norc` will not execute the rc-files with the source builtin (./.shellptrc and ~/.shellptrc).
- `-p` or `--nops` will not assign a default value to PS1 and PS2.
- `-b` or `--bps` will assign a basic value to PS1 and PS2, lighter than the original one. PS1 will equal '\s-\v\$ ' and PS2 will equal '> ', just like Bash.
- `-d` or `--debug` will launch Shellpticflesh with both `-n` and `-b` options on.
- `-h` or `--nohist` will not write the history automatically at the end onto .shellpthistory. You would need to use `history -w`.
## Prompt
The prompt is the main key to the interactivity of a shell.
### Prompt management
There are 3 ways to launch a prompt in the current version of Shellpticflesh :
- In the mainloop, when it asks for a new command to be processed. The prompt starts with PS1.
- When the line is incomplete (no closing quote, parenthesis...). The prompt starts with PS2.
- In heredocs. The prompt starts with PS2.
Inputting a EOF with ^D will end the prompt prematuraly, or close the shell if in PS1 without anything written.
### PROMPT_COMMAND
Every time a PS1 prompt is asked, PROMPT_COMMAND content will be executed prior to the prompt.
### Prompt expansions
Every prompt begins with either PS1 or PS2. Both are submitted to the prompt expansion. It consists of the following :
- Basic expansions which will replace backslashed characters with corresponding ones.
  - `\a` `\n` `\r` do the same as in standard C.
  - `\H` replaces with the Hostname.
  - `\s` replaces with the shellname.
  - `\u` replaces with the username.
  - `\v` replaces with current shell version.
  - `\w` replaces with the current directory (no /).
  - `\W` replaces with entire cwd.
  - `\#` replaces with current command number since history.
  - `\c` replaces with color marker (see PS colors).
  - `\\` replaces with a \ character.
  - `\$` replaces with a $ character.
- Parameter expansion (see below).
- Command substitution (see below).
### PS colors
Shellpticflesh allows a deeper and more complexe management of colors, as well as an easy alternative.<br>
The color marker must start with `\c` and end with a color letter.<br>
The letters are the following : 'n' for black, 'r' for red, 'g' for green, 'y' for yellow, 'b' for blue, 'p' for purple, 'c' for cyan, and any other letter for white.<br>
For example, `\cr` will change the color in red.<br>
Setting the color letter uppercase will make the text in bold as well. For example, `\cY` will set the text in bold yellow.<br>
The following letters or numbers can be added before the color letter to change the styling :
- 'i' or '2', sets the text in italic
- 's' or '3', sets the text underlined.
- 'd' or '4', makes the text blink (might be disabled in terminal settings, be aware).
- 'I' or '5', inverts the color.
- '1', sets the text in bold. (an uppercase letter works as well)
- '0', does nothing.
For example, `\cisR` puts the text in italic, underlined and bold red color.
## Splitting
The string to be processed must first be split into different tokens.<br>
Every variable assignements must be at the beginning of the line, otherwise it will be treated as part of a command.<br>
The string is split according to spaces, quoting and parenthesis.<br>
If the line is 'incomplete', the shell will ask for more. If you want to give up on the line, press ^D.
## Expansions
Shellpticflesh performs the following expansions in this order :
- Alias expansion
- Braces expansion
- Tilde expansion
- Parameter expansion
- Command substitution
- Arithmetic expansion
- Filename expansion
### Alias expansion
Alias expansion will replace every variable assignements and the first command according to the aliaces created with the alias builtin.
`alias ls='ls --color=auto'` <br>
`ls # replaced accordingly` <br>
### Braces expansion
Braces expansions are of 2 kinds. <br>
- Braces **coma** expansions which will distributes contained text to the outside text. Expansions might be inbricated.
- Braces **dots** expansions which will replace the string with all the values contained between the limits such as `{l_bound..u_bound..step}`. Expansions cannot be inbricated.
### Tilde expansion
Tilde expansion will replace all unquoted tildes that are parts of the command with the HOME directory.<br>
First of and foremost, it will search for the HOME directory inside the HOME variable of the shell.<br>
If not found, it will get the username with `whoami` or the $USERNAME variable, and search in the /etc/passwd file.<br>
If not successful, it will try to use `/Users/username`.<br>
If not successful, the tilde is left unmodified.<br>
Tilde expansion also replaces `~+` with PWD, and `~-` with OLDPWD.<br>
### Parameter expansion
Parameters expansions are simplified in this version compared to Bash.<br>
Every text from the command that is unquoted or within double quotes will be interpreted as a parameter expandable string.<br>
If within braces, the parameter can also include the # to return the length of the parameter. `echo ${#var}`<br>
Parameter expansion will search in the environment (local as well as exported) and replace the value if found, or remove the string if not found.<br>
Following arguments are considered __special parameters__:<br>
- 0 : replaces with shell name.
- ? : replaces with last return status.
- $ : replaces with current pid (obtained with a syscall as getpid isn't allowed)
- RANDOM : replaces with a random value ranging from 0 to 32767 (random function also built with inline asm)
Parameter expansion is then modified by word splitting.
### Command substitution
Command substitution are of sorts `$(cmd)`.<br>
The command substitution will be replaced with the output of the content of the parenthesis.<br>
Other fd can be substituted like so `$(cmd fd>&1)`.<br>
Command substitution is then modified by word splitting.
### Arithmetic expansion
TBA
### Filename expansion
Filename expansion will be used on commands, var assignements and redirections (if output is one file).<br>
It will look through all files in directories to find matching ones.<br>
. and .. are not listed except if filename expansion searches for hidden files.<br>
There are two filename indicators :<br>
- `*` which allows strings of any length and of any characters
- `?` which only allows one character length
For example, `*p?` will search for any files and directories in the current directory that has the letter 'p' in the previous to last character spot.
### Word splitting
Word split is a feature that will separate one element into multiple elements.<br>
Its functioning can be modified with the IFS variable, which, if unset, is equal to a space character, a tab character and a new line character.<br>
Every time a IFS char is found, the word is splitted into 2 elements.
## Quote removal
Quote removal is, as its name suggests, the removal of every unnecessary quotes.<br>
- When unquoted, every quotes will be removed, except if backslashed. All backslashes will be removed.
- When single quoted, every character is kept.
- When C-quoted ($''), every character is modified according to C-printf standard.
- When double quoted, every character is kept. The backslash is kept only if there is a special character after it.
## Redirections
Redirections in Shellpticflesh include :
- `[n]>&m` or `[n]>file` which overwrites the content of the file descriptor 'm' or of the file 'file' with the content of n. n is by default stdout.
- `[n]>>&m` or `[n]>>file` which appends to the file descriptor 'm' or to the file 'file' with the content of n. n is by default stdout.
- `[n]<&m` or `[n]<file` which reads from the file descriptor 'm' or from the file 'file'. n is by default stdin.
- `[n]<<word` which reads the content of stdin until the word 'word' is encountered or until the eof, and is considered to be the read entrypoint of n. n is by default stdin. (**heredoc**)
- `[n]<<<string` which sets the content of the file descriptor n as the string 'string'. n is by default stdin. (**herestring**)
- `[n]<>&m` or `[n]<>file` which sets the read and write points of n as the file descriptor 'm' or as the file 'file'. n is by default stdin.
## Execution
The execution is set in three parts : searching the command and setting it up, performing the redirections, and executing the command.<br>
This order of operation differs from Bash, as Bash performs the redirections first.<br>
The downside in doing that is that in case of a command not found or a permission denied, the loop crashes and must be ended prematuraly with a SIGINT.<br>
Doing like Shellpticflesh avoids that, but leads to another issue. A `command not found...` string might need to be redirected as such in bash : `unknown_command 2>a`. Doing so isn't possible in our Shell, but there is an easy way around this, which is to add parenthesis like so : `(unknown_command) 2>a`.
### Set up
The set up of the execution is pretty straight forward :
- get the command name and arguments and all the redirections.
- get the command path.
- create a child to execute the command.
### Performing redirections
The child is now created to avoid any time loss and make sure that the operations are done in aproximate order.<br>
The redirections are performed as dictated above.
### Executing the command
The command is then executed with execve (see man).<br>
If there is piping, the output is written in a temporary pipe which will serve as the read entry of the next command (except if the output is already redirected).
### File descriptors
A standard execution without any redirections takes 3 file descriptors, however many there are pipes.<br>
If the limit is reached, the execution will fail.
## Builtins
Shellpticflesh contains multiple builtins :
### echo
`echo` is a simple command which will just write all of its arguments in stdout.<br>
If -n is not provided, then it will add a newline character at the end.<br>
If -e is provided, the output is formated to allow for special characters such as `\n` or `\e` to be interpreted.
### printf
`printf` is very similar to C printf. It formats the output according to extra given arguments.<br>
It allows following formats :
- `%c` replaces with a character. When no character is given, it is replaced with no character. When a string is given, it is replaced with the first character.
- `%s` replaces with a string. When no string is given, it is replaced with no character.
- `%d` and `%i` replaces with a long number. If no number is given or if the number is larger than a large, it is replaced with a 0.
- `%x` and `%X` replaces with the hexadecimal of a long number. Small x puts characters in lowercase, whereas big x puts them in uppercase. When an error occurs with the argument, it is also replaced with a 0.
The following flags can be added before the letter :
- `#` adds a `0x` or a `0X` to a `%x` or a `%X` format if the number isn't NULL.
- `0` adds zeroes instead of spaces when spacing is needed (see spacing after).
- `-` puts the spacing after the argument. It overrides the '0' flag.
- ` ` adds a space in front of positive numbers (`%d` and `%i`).
- `+` adds a plus character in front of positive numbers. Overrides the ' ' flag.<br>
After the flags can be added a 'field length'. This length represents the minimum length of the field, and will add spaces before the argument to complete what is needed.<br>
Accuracy can also be added at the end, right before the format indicator. It must be separated with a dot as such `%[flags][spacing][.accuracy]format`. Accuracy will modify the argument according to its type and the accuracy size. A number will be added zeroes to get the right size, but a string will be cropped if longer.<br>
Also, the string is formated the same way as `echo -e`.
### pff
`pff` stands for 'print formated file'.<br>
`pff` isn't an essential builtin as it doesn't need to be a builtin, but its purpose can be encountered frequently.<br>
As `cat`, `pff` will open files and read their content on stdout. It will return 1 if any file fails to open.<br>
`pff` will read every line, but prints them with `echo -e`, so the output will be formated, allowing colors and other formating options in files.
### env
`env` prints out every exported arguments of the variable scope.
### export
`export` allows you to export variables and declare them. Using `export` with no arguments also prints out all the exported variables, even ones with no value.
### unset
`unset` must be used to unset variables, which means removing them from the variable list. They will no longer be exported, nor assigned to a value.
### cd
`cd` is used to navigate through directories. It can move you relatively to where you are, or through an absolute link.<br>
The `CDPATH` variable can be set to look for directories outside of yours to search through.<br>
The `PWD` and `OLDPWD` will be set accordingly.<br>
Deleting a parent folder will not cause `cd` to crash, as `PWD` checks if the file you're in still exists.<br>
### pwd
`pwd` simply prints the current working directory in stdout.
### alias
`alias` allows the creation of a new alias. `alias` with no argument prints out all the aliaces.<br>
Aliaces are a link key-value that replaces in the command line every variable assignements as well as the first COMMAND marked word by the value.<br>
For example, the alias `alias ls='ls --color=auto'` will always replace `ls` with `ls --color=auto`.
### unalias
`unalias` simply removes a named alias from the list.
### history
`history` in Shellpticflesh works differently as in Bash.<br>
- `history` with no argument will print out the whole history list.
- `history -c` or `history -C` will clear the history list. It will also erase the content of the history file at the end of the program. Using `-C` skips the warning.
- `history -i` will print the history line at index 'i'.
- `history -w` will write the content of the history in the history file.
- `history n` with n being a long number will print the `n` last entries in history.
### exit
`exit` will exit the program with either a given value or the last returned value.
### . or source
`.` and `source` are the same builtins.<br>
They open a file and execute every line one by one in the same shell process.
### [ or test
`test` and `[` refer to the same builtin.<br>
They can be used to test conditions. `[` must be ended with `]`.<br>
Conditions can be enclosed in parenthesis, or separated with `-a` for 'and' and `-o` for 'or'.<br>
This builtin doesn't output anything, but sets the return value to the return value of the conditions.<br>
An empty string results in false, whereas a non-empty string results in true.<br>
Unary tests consists of an operator followed by an argument. Unary tests are as follow :
- `-a` and `-e` : file exists
- `-b` : file is block device
- `-c` : file is character special
- `-d` : arg is a directory
- `-f` : file is regular file
- `-g` : group-id is set
- `-h` and `-L` : arg is a symbolic link
- `-n` : arg is not an empty string
- `-p` : arg is a named pipe
- `-r` : file is readable
- `-S` : arg is a socket
- `-s` : file is not empty
- `-t` : arg is a tty
- `-u` : user_id is set
- `-w` : file is writable
- `-x` : file is executable
- `-z` : arg is an empty string<br>
Binary tests consists of an argument, followed by an operator and another argument. The binary operators are :
- `=` and `==` : the strings are the same
- `!=` : the strings are different
- `>` : arg1 is greater than arg2 following ASCII rule set
- `<` : arg1 is smaller than arg2 following ASCII rule set
- `-ef` : arg1 and arg2 have the same device and inode numbers
- `-nt` : arg1 has a more recent modification date
- `-ot` : arg1 has an older modification date
- `-eq` : the number arg1 is equal to the number arg2
- `-ne` : the number arg1 is not equal to the number arg2
- `-lt` : the number arg1 is lesser than the number arg2
- `-le` : the number arg1 is lesser than or equal to the number arg2
- `-gt` : the number arg1 is greater than the number arg2
- `-ge` : the number arg1 is greater than or equal to the number arg2
### :
`:` is a very useful builtin.<br>
Its purpose is almighty and must be used with care, as a malpractice might quickly happen.<br>
Some underestimate its power and fall under its claws of torment and power.<br>
In all seriousness, it doesn't do anything and voids out all the arguments.
### hell
`hell` is a builtin that prints out a pun around the metal genre.<br>
It is randomized, and they are all funny, I swear.
### tetris
`tetris` is a real builtin in our shell.<br>
It is entirely coded in the terminal thanks to `tputs`<br>
The internal timer is counted with `/bin/sleep`, so if it isn't found, tetris won't launch.<br>
The random aspect of the code is based on either the `rdrand` on asm x86_64. If `rdrand` isn't supported, it will be based on mathematical operations around the time and the pid of the shell.<br>
Have fun !
## Post execution
When the execution is over, it checks if the line is over, or if it should continue.<br>
If `&&` is encountered at the end of the executed part, the rest will be executed if and only if the first command returned 0.<br>
On the same logic, if `||` is encountered, it will be executed if and only if the first command failed (non-zero return status).<br>
Finally, if `;` is encountered, it will execute the rest no matter what, which allows multiple command execution on a single line.<br>
Parenthesis can be used to modify priorities : `(cmd1 || cmd2) && cmd3` != `cmd1 || cmd2 && cmd3`.
## History
The history is by default stored in a file at `~/.shellpt_history`. Every line is added on `readline` history, and stored in a separate linked list as well.<br>
History file can be modified with the `HISTFILE` variable.<br>
History size can be modified with the `HISTSIZE` variable.<br>
And finally, history file size can be modified with the `HISTFILESIZE` variable.
## PS0
PS0 is a variable of the Shell that is printed on the stdout every time a command is executed.<br>
PS0 goes through all the PS expansions. It is useful to modify output color, print informations on runtime or do whatever you want.
<br><br>
Thanks for reading and have fun with it !<br>
The ÜBER TIGO
