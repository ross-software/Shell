#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

struct MWMHints {
    unsigned long flags;
    unsigned long functions;
    unsigned long decorations;
    long input_mode;
    unsigned long status;
};

enum {
    MWM_HINTS_FUNCTIONS = (1L << 0),
    MWM_HINTS_DECORATIONS = (1L << 1),

    MWM_FUNC_ALL = (1L << 0),
    MWM_FUNC_RESIZE = (1L << 1),
    MWM_FUNC_MOVE = (1L << 2),
    MWM_FUNC_MINIMIZE = (1L << 3),
    MWM_FUNC_MAXIMIZE = (1L << 4),
    MWM_FUNC_CLOSE = (1L << 5)
};

int
main(int argc, char *argv[]) {
    Display *dpy = XOpenDisplay(NULL);
    int black = BlackPixel(dpy, DefaultScreen(dpy));
    int white = WhitePixel(dpy, DefaultScreen(dpy));

    XVisualInfo vinfo;
    XMatchVisualInfo(dpy, DefaultScreen(dpy), 32, TrueColor, &vinfo);

    XSetWindowAttributes attr;
    attr.colormap = XCreateColormap(dpy, DefaultRootWindow(dpy), vinfo.visual, AllocNone);
    attr.border_pixel = 0;
    attr.background_pixel = 0x80808080;

    Window win = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, 200, 100, 0, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attr);

    Atom delwin = XInternAtom(dpy, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(dpy, win, &delwin, 1);

    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);

    XEvent e;
    while(1) {
        XNextEvent(dpy, &e);

        switch(e.type) {
            case KeyPress:
            case ClientMessage:
                goto ret;
            case Expose:
                XClearWindow(dpy, win);
                XFlush(dpy);
        }
    }

ret:
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);

    return 0;
}
