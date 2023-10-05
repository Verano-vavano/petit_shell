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
- Braces **coma** expansions which will distributes contained text to the outside text.
- Braces **dots** expansions which will replace the string with all the values contained between the limits such as `{l_bound..u_bound..step}`
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
## Redirections
## Execution
## History
<br><br><br>
Functionalities :
Braces, tilde and parameter expansion
- Braces include inbracated (and not) coma expansion and not inbricated dots expansion
- Tilde expansion searches extensively before giving up (its determined)
- $var && ${var} works. Handles ${#var}
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
