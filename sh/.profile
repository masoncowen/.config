#Profile
##CONFIG and sub-profiles
XDG_CONFIG_HOME="$HOME/.config"; export XDG_CONFIG_HOME
XDG_DATA_HOME="$HOME/.local/share"; export XDG_DATA_HOME
. "$XDG_CONFIG_HOME/sh/.environment" 
. $ENV
. $FUNC
. $ALIAS

#Prompt
UNAME="$(uname -n)"

PS1="<\033[36;1m$LOGNAME\033[0m@\033[36;1m$UNAME\033[0m:\033[32;1m\W\033[0m> "

#Other
PATH="$PATH:$CONFIG/bin"
PATH="$PATH:~/zig"
set -o vi
transset-df -a .75
clear
export TASKDDATA=/var/taskd
