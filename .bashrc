#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

export PATH="$HOME/.local/scripts:$PATH"
alias ls='ls --color=auto'
alias grep='grep --color=auto'
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'
alias sd="cd ~ && cd \$(find * -type d | fzf)"
PS1='[\u@\h \W]\$ '
