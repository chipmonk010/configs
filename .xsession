
if [ -f $HOME/.Xdefaults ]; then
  xrdb -merge $HOME/.Xdefaults
fi

feh --bg-scale ~/.wallpaper/20090306_rassilonsw1600x1200.jpg &

# xbindkeys &

# /usr/bin/evilwm -term xterm -fg black -snap 10

while true
do
   xsetroot -name "[Battery: `~/bin/bat.bash`] [`date +"%a %b %d %I:%M %p"`]"
   DISPLAY=:0.1 xsetroot -name "[Battery: `~/bin/bat.bash`] [`date +"%a %b %d %I:%M %p"`]"
   sleep 30    # Update time every 30 seconds
done &
#firefox&
#thunderbird&
xterm&
xterm&
xterm&
#urxvt&
#urxvt&
#urxvt&
DISPLAY=:0.1 /usr/local/bin/dwm&
DISPLAY=:0.0 /usr/local/bin/dwm
