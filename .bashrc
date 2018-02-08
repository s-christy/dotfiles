# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
#[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color '
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    #alias grep='grep --color=auto'
    #alias fgrep='fgrep --color=auto'
    #alias egrep='egrep --color=auto'
fi

# colored GCC warnings and errors
#export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# some more ls aliases
#alias ll='ls -l'
#alias la='ls -A'
#alias l='ls -CF'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi
#figlet $(shuf -n 10 /usr/share/dict/words|/bin/grep -v "'"|head -n1)
#HINT: use which to find the path to the command
alias lsdef="/bin/ls --color=auto "
alias ls="ls --color=auto -A "
export PATH=$PATH:/sbin
export PATH=$PATH:/usr/sbin
alias got="ps -aux | grep "
alias get="ps -aux | grep --color=auto firefox | awk '{print $2}' "
alias x="universal-open " #"xdg-open "
alias s="systemctl suspend" #consider using i3lock;systemctl suspend
alias 84="ping 8.8.4.4 "
#alias traceroute="traceroute --resolve-hostnames "
alias duh="du --max-depth=1 -h "
alias dmesg="sudo dmesg -H "
alias watch="watch -n 0 "
alias push="git push "
alias pull="git pull "
alias commit="git commit -am "
alias status="git status "
alias gitdiff="git diff "
#alias wc='printf " l    w   c\n";wc '
alias espeak="espeak -a 50 "
alias speak="xclip -o | espeak -a 2 "
alias grep="grep --color -n "
alias grepr="grep -r "
alias get-info="xprop "
alias x.="xdg-open . "
alias i3lock="i3lock -c 000000 "
alias pcsx2="PCSX2 " #what the motherfucking fuck
#alias lock="i3lock ; s "
alias ps2="PCSX2 & "
alias fehw="feh -w "
alias reversegrep="grep -v "
alias ksp="/home/sam/.steam/steam/steamapps/common/Kerbal\ Space\ Program/KSP.x86_64 "
alias axiomverge="/home/sam/.steam/steam/steamapps/common/Axiom\ Verge/AxiomVerge "
#alias steamwin="playonlinux --run 'Steam' "
alias starcraft="wine /home/sam/starcraft/Starcraft\ No\ Install/StarCraft.exe"
alias cmatrix="cmatrix -b -C red "
#OLD alias autogit='git status;git add $(read -r toadd; echo $toadd); git commit -m "$(read -r message;echo $message)"'
#changed from alias to bin program alias autogit='read toadd; git add "`echo $toadd`"; git commit -m "$(read message;echo $message)"'
alias pause='read -s -r -p "Press any key to continue..." -n 1 dummy'
alias feh="feh --force-aliasing"
alias vimnorc="vim -u NONE"
alias opendir="thunar . "
alias :x="exit "
alias :q="exit "
alias ainstall="sudo apt install "
alias mcd="read $1;for x in 1..$1; do cd ..;done "
alias temp="cd ~/tmp "
alias downloads="cd ~/Downloads"
#alias fnd="ls | grep"
#alias fnd="find . -name "
alias mutt='mutt -e "set crypt_use_gpgme=no"'
alias ..="cd ..;ls"
alias ...="cd ../..;ls"
alias ....="cd ../../..;ls"
alias .....="cd ../../../..;ls"
alias r="ranger"
alias htop="htop -d0"
alias lsr="ls -R "
alias dot="cd ~/s-christy/dotfiles "
alias searchman="apropos "
alias inxi="inxi -F ; neofetch "
alias lsl="ls -l"
alias 1tb="cd /media/sam/Sam\ 1TB/ "
alias qwed="cd ~/Downloads "
alias qwet="cd ~/tmp "
alias mpg="mpgrep "
alias estatus="expressvpn status "
alias econnect="expressvpn connect "
alias edisconnect="expressvpn disconnect "

#export PAGER="/usr/bin/most -s"
export PAGER="/usr/bin/less"
export LESS_TERMCAP_mb=$'\E[1;31m'     # begin bold
export LESS_TERMCAP_md=$'\E[1;36m'     # begin blink
export LESS_TERMCAP_me=$'\E[0m'        # reset bold/blink
export LESS_TERMCAP_so=$'\E[01;44;33m' # begin reverse video
export LESS_TERMCAP_se=$'\E[0m'        # reset reverse video
export LESS_TERMCAP_us=$'\E[1;32m'     # begin underline
export LESS_TERMCAP_ue=$'\E[0m'        # reset underline
export GROFF_NO_SGR=1                  # for konsole and gnome-terminal

PATH=$PATH:/home/sam/s-christy/dotfiles/bin
xset b off 2> /dev/null

xinput --set-prop "ETPS/2 Elantech Touchpad" 294 0 2> /dev/null

BLACK="\e[0;30;40m"
RED="\e[0;31;40m"
GREEN="\e[0;32;40m"
YELLOW="\e[0;33;40m"
BLUE="\e[0;34;40m"
PURPLE="\e[0;35;40m"
LBLUE="\e[0;36;40m"
WHITE="\e[0;37;40m"
NORMAL="\e[0;38;40m"
#To use these, use echo -e "${RED}"

cd ~/s-christy/dotfiles

estatus
echo
nmcli | /bin/grep connected
echo
ping 8.8.4.4 -c1


