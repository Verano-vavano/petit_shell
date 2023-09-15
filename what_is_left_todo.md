si motivation, faire les expansions de PS1 et PS2

(echo lol && cat gigipokp) >a 2>b

ERR VALGRIND :
- echo {#param}

PS1 PS2 :
- pas de word split -> PS1='$(ls)'

# exports with $() inside them. Et PS1 avec PROMPT_COMMAND

```sh
export PROMPT_COMMAND='available_space_on_root_fs=$(df -h --output=avail /)'
```
minisheel -> available_space_on_root_fs: command not found...
bash ->

bash le prend juste et il est ok!
apres tu peux faire

```sh
export PS1='$available_space_on_root_fs$ '
```
et bash sera content de faire ca! 
nous pas encore! Mais bientot.. j'espere

venant de cette magnifique reponses stack overflow
https://unix.stackexchange.com/a/718421

# Removal of dirs

```sh
mkdir -p /tmp/lol/mdr
cd tmp/lol/mdr
rm -rf ../../tmp
cd ../..
```

minishell -> No destination directory: No such file or directory
bash -> cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory

caused by line 80 of cd_mentiel_util.c
- ft_strcmp(dest, "..")
    - incompatible with ../.. for example

possible fix, check if !getcwd and if `dest` is relative or not
and is relative if (!dest->value[0] != '/' || dest->value[0] != '~')
