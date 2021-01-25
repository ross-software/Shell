# wm-configs

## Installation
### Arch Linux
There is an official git package available in the AUR: [ross-wm-configs-git](https://aur.archlinux.org/packages/ross-wm-configs-git/)

## Starting
### Login Manager
Just select "ROSS Shell" from your login manager (for example LightDM) and login!

### Xinit
Put the following command inside your `~/.xinitrc`:
```bash
awesome -c /etc/xdg/awesome/ross/rc.lua
```
Then start it:
```bash
startx
```
