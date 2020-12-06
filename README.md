> "Man must shape his tools lest they shape him."
> -- <cite>[Arthur Miller][1]</cite>

[1]: https://www.azquotes.com/quote/654449

# Ross Scott and the quest for the holy GUI 
To quote Ross from Accursed Farms, "None of this would be possible without multiple mathematicians and scientists, working around the clock to break reality"

The main goal of this project is to create the perfect GUI. This is what it consists of:

- ApplicationLauncher: Desktop independent program/command launcher. It is a popup window and uses chords from the keyboard.

- Default WM configs: Configurations files for a recommended window manager for an optimized workflow.

- Session: Default GUI session you can login with that manages all recommended configurations and GUI components.

Some more must-have features:

- Conditional status: For example, if you're playing *DOOM*, or working with *GIMP*, you should be able to unbind certain shortcuts. If you binded *CTRL-Click* to do something, but in those programs, you don't want that, then it should be possible to disable the shortcuts. Some other conditions that are not decided yet can also be added.
- Profiles: This is an extension of the previous point, but with different profiles.
- Plantext config: Editing configuration files *outside* an interface makes it more portable and easier to work with.

For the programming language and framework, we use Qt with C++ and some small libraries like libqtxdg. 

# Contribute
We are still in planning stages. Contributions, discussions and research are welcome. Just join our [chat on Element.io](https://app.element.io/#/room/#ross:matrix.org) or make a pull request/issue for this repository.
