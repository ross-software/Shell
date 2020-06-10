# Ross Scott and the quest for the holy GUI 
To quote Ross from Accursed Farms, "None of this would be possible without multiple mathematicians and scientists, working around the clock to break reality"

The main goal of this project is to create the perfect GUI. So far, I want to create 3 programs that I think are important:

- Program Menu: Able to launch programs/commands from a menu. It doesn't have to be a menu, but it could be a radian, or a cross.
	- Openbox menu: I like this, sense I can have programs in folders. https://youtu.be/KZ4QH1TIDzw
	- Dmenu: type out some text and get a program. Extremely useful for scripting. https://www.youtube.com/watch?v=R9m723tAurA example
	- Xmonad's grid launcher: I enjoy this so much. http://hackage.haskell.org/package/xmonad-contrib-0.16/docs/XMonad-Actions-GridSelect.html. I just select what I want from the keyboard, and don't even have to type it out
	- Radian mouse: https://lifehacker.com/radian-is-a-radial-mouse-centered-application-launcher-5597469 or something similar.

- Mouse/Keyboard Gestures: I like this idea, but I think being pure mouse is a bad idea. So, I want to be able to integrate keyboard. Think of a program like `sxhkd`, but instead of binding keyboards and mouse separately, we bind them together.

In terms of the MUST HAVE FEATURES, I can think of three. Feel free to add more

- Conditional status: What I mean, is if you're playing *DOOM*, or working with *Photoshop*, you should be able to unbind your keys. So maybe you binded *CTRL-Click* to do something, but in those programs, you don't want that. So, I want to disable it. Not only that, but I want other conditionals, but those I can't really think of.
- Profiles: This is an extension of the previous point, but I want there to be different profiles. The mouse radian idea for example: if you have 50+ programs, than you'll have to comprise with laziness over efficiently.
- Plantext Config: I like editing Config *outside* some interface, since I can make it more portable.

In terms of the porgramming langauge, C with xlib seems the best. 

# Must have
Window-agnostic rendering; we want to be able to extend and utilize several graphical components, often agnostic of any windows presently open.
System-level scancode reading; we want to be able to read the user's keyboard--not just the keys they press, but the positions on the keyboard (as in sxhkd)--regardless of what windows happen to be open. On most POSIX systems, this is facile; it may require additional effort on Windows.
Extensibility; this should be a program upon which abstractions may be made, whether as a matter of configuration or additional software. Part and parcel of this is keeping file length curt and source code readable so that non-predictable, detailed configurations can be made quickly and easily (suckless do this and it works quite well!)

# Time-line
The mouse gestures project seems easy enough, so I'm doing that last. I will work on the Program Menu. If you're reading this, than a doc of what to implement at this stage should be done in a week or two's time. God speed.


# Awesome
One thing though [testman](https://github.com/testman42) said over in [Reddit thread](https://www.reddit.com/r/accursedfarms/comments/h0cumc/the_gui_should_be_better_a_lot_better_new_video/ftm0dqa?utm_source=share&utm_medium=web2x), was I should make it an [awesome](https://github.com/sindresorhus/awesome#readme) document. 

# Contribute
We are still in planning stages. Contributions, discussions and research are welcome. Just join our [chat on Matrix/Riot](https://riot.im/app/#/room/#gui:matrix.org) or make a pull request/issue for this repository.
