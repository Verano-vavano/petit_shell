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
CD follows symlinks
2 builtin easter eggs (tetris, hell)
- Fully functional Tetris working with Termcap and Termios. The forking for the internal timer might be a bit heavy, but without threads, it was the only way. Cannot work without sleep.
- Hell is a builtin printing a pun around the metal genre. We hardcoded a new random function using the asm instruction to generate pseudo-random number to choose the pun. And they all are funny.

- The ÜBER TIGO
