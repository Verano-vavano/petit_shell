![logo](images/logo.png)
# Minishell!
We are Hugo and Thibault, our team name is <b>Über Tigo</b>

This is a project done during our cursus at [42 School](https://42.fr/en/homepage/). The assignement was to code a little [ shell ](https://en.wikipedia.org/wiki/Shell_(computing))

# Main functionalities
Here are the main functionalities of our Shellpticflesh !
## At the start
The shell doesn't start if STDIN, STDOUT and STDERR aren't TTY, for safety reasons.<br>
If the argument `-c` is provided, the remaining arguments will be executed, and the shell will be close.<br>
If the shell isn't launched with the argument `-n` or `--norc`, it will execute every lines of the file ./.shellptrc and $HOME/.shellptrc, the same way as the builtins `.` and `source` do.<br>
The shell then launches the history, and asks the user for a prompt.<br>
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
- `+` adds a plus character in front of positive numbers. Overrides the ' ' flag.
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
## History
The history is by default stored in a file at `~/.shellpt_history`. Every line is added on `readline` history, and stored in a separate linked list as well.<br>
History file can be modified with the `HISTFILE` variable.<br>
History size can be modified with the `HISTSIZE` variable.<br>
And finally, history file size can be modified with the `HISTFILESIZE` variable.



<br><br><br>
Functionalities :
Command substitution
- Handles $(cmd) which replaces it with the stdout of cmd
Filename expansion
- Handles partial search (l* searches for files that start with l)
- Handles both * and ?
Word split
- According to IFS
Quote removal (for both cmd and heredoc delim)
Execution using only 3 fds
Local and exported environment
Fully functional history
- History file can be changed with var. HISTFILE. History size can be changed with HISTSIZE and the history file size can be changed with HISTFILESIZE.
&& || ;
< << <<< > >> <>
- Better file management, as we close useless files, whereas bash keeps them until the end of the cmd
- Heredocs succesfully handled. ^D ends it the same way as Bash.
Redirection from fd to fd (n<&m)
Parenthesis priorities with full and partial redirections
Syntax error handling
Taking variables into account (IFS, CDPATH)
RANDOM variable using custom randint
PS0, PS1, PS2, PROMPT_COMMAND
- PS0 is written is stdout every time a function outputs
- PS1 is the beginning of the main prompt
- PS2 is the beginning of secondary prompts (heredocs && incomplete lines)
- Performs PROMPT_COMMAND before each prompt
- PS expansions allow complexe prompts such as : PS1='|->$? _$$_ $ ' and can be on par with PROMPT_COMMAND
- PS expansions allow \ expansions such as \n \w or \u
- Colors in PS_EXPANSION with \c (\cr for red, \cB for bold blue...)
-- Allows more complexe colors parameters such as blinking and italic (PS1='\cisR\s\c0w \ciG\v\c0w \cdp[\W]\c0w \c25c($?)\c0w \cW>\c0w ')
Signal handling
Shellptrc file executed line by line at launch (both in executable dir and home dir)
- use './minishell --norc' to avoid rc execution
'./minishell -c' can be used to execute a single command (can include &&, || and ;)
.shellpstart file is printed out at launch

BUILTINS :
cd : change directory
echo : prints on stdout (-neE)
env : prints env
exit : exits shell with status
alias : allow alias expansion to change command
unalias : removes an alias
export : export variables to be used externally
unset : removes variable
pwd : prints working directory
printf : prints formated input (allows %csdixX with accuracy, field spacing and the following flags : # ' ' - 0 +)
history : basic history management (-w writes in histfile, -c clears history, -i writes content at index, no arg printfs everything, and a numeric argument prints n argument)
source (.) : executes all lines in a file
: : ne fait rien et ignore donc toute la commande
2 builtin easter eggs (tetris, hell)
- Fully functional Tetris working with Termcap and Termios. The forking for the internal timer might be a bit heavy, but without threads, it was the only way. Cannot work without sleep.
- Hell is a builtin printing a pun around the metal genre. We hardcoded a new random function using the asm instruction to generate pseudo-random number to choose the pun. And they all are funny.

- The ÜBER TIGO
