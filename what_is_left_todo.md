PS -> \c change la couleur ?

echo $PS1
a='\e\flol'; echo $a
-> env_update doit doubler les \ afin de les conserver
a='"12' -> export rajoute un \
