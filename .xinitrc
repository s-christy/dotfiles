exec i3
exec --no-startup-id pulseaudio
# xset s off
# xset -dpms

#make standby time 1 hour
#xset s 3600 3600

#disable energy star features
exec xset -dpms
exec xset s 3600 3600
exec xset s off

#Fix screen tearing
#exec compton --config /home/sam/.config/compton.conf
exec --no-startup-id startCompton

