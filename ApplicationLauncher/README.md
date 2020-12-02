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
qdbus org.ROSS.ApplicationLauncher /App toggle
```
