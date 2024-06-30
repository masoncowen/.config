#!/bin/sh
# pseudocode:
# for session in $@
# tmux has-session -t $session &> /dev/null

# if [ $? != 0 ] then
#   select $session
#   case "newsboat" then
#   case "essays" then
#     start_dir=$HOME/prj/essays
#   case "fiction" then
#     start_dir=$HOME/prj/fiction
#     
#   tmux new-session -s $session -n $session -c $start_dir -d
#   
#   
SESSIONNAME="newsboat"
tmux has-session -t $SESSIONNAME &> /dev/null

if [ $? != 0 ] then
  tmux new-session -s $SESSIONNAME -n newsboat -d
