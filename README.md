# hexchat_autojoin
Plugin for hexchat executing join command for a predefined list of channels
# WARNING
I wrote this plugin many years ago (initially for xchat), I'm not a programmer, 
also probably it's full of mistakes, poor C styles (mixed) and horrible calculations.

You can:
* USE IT AT YOUR OWN RISK.
* USE IT AS A EXAMPLE HOW NOT TO PROGRAM OR WRITE C CODE
* ...
* MAKE IT BETTER

# History
Initial intention was to when authenticated I can easily join my favorite 
IRC channels.

This method is not perfect, and it's slow since it's executed sequentally by calling
join for each channel.


# How to compile
* Requires hexchat-plugin.h header (hexchat-devel on fedora).
* gcc


To compile, execute:
`gcc -Wl,--export-dynamic -Wall -O1 -shared -fPIC joinmychannels.c -o joinmychannels.so`

*copy shared object ot a addons directory of hexchat (in my case `~/.config/hexchat/addons/` )
*edit and copy config file `addon_joinmychannels.conf` into `~/.config/hexchat/`

Optionally path to a config file can be defined during compile time with
`-DCONFFILEPATH='"/path/to/addon_joinmychannels.conf"'`

This path is relative to a `HOME` env variable (users home directory) and beggins with a `'/'`

Later when hexchat is started and module is loaded, you can join you channels by execuitng
```
/JoinMyChannels
```
command. 



