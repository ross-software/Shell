## Dependencies

- Qt5 [Widgets, DBus, LinguistTools, X11Extras (optional)]
- libqtxdg
- libx11 (optional)

## Compilation

```bash
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install
```

## Usage

With the recommended window manager configurations the keyboard shortcut for toggling the ApplicationLauncher is <kbd>Super</kbd> + <kbd>Space</kbd>.

You can toggle the application launcher manually with dbus with the following command:
```bash
dbus-send --dest=org.ROSS.ApplicationLauncher --type=method_call /App org.ROSS.ApplicationLauncher.toggle
```
