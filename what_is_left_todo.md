si motivation, faire les expansions de PS1 et PS2

(echo lol && cat gigipokp) >a 2>b

ERR VALGRIND :
- echo {#param}

echo lol >$(echo mdr jpp) : ambiguous redirect (very ambiguuguguoius)
b=12 && export b : la valeur de b n'est pas conservée

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
