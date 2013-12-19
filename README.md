tinyterm
========

A lightweight VTE-backed terminal emulator originally written by
Sebastian Linke, forked & modified by Brandon Roberts.

## Info

Tinyterm is a terminal emulator written in C that uses VTE as its
back-end. It's not intended to be overloaded with design options such
as opacity, background image, font color etc., but with useful abilities
which you won't find in other terminal implementations, e.g. access to
the contents of the terminal buffer, multiple terminal sessions in one
window and much more.

Tinyterm comes with no further windows. Instead constants (see below)
are used to configure its behavior. The predefined ones should fit most
of your needs anyway.

Note that Tinyterm is just a hobby project having a slow progress. Only
a marginal number of features has been implemented yet. So don't expect
too much and stay tuned for a release in the far future... ;-)

## Configuration, features, and default options

Currently, options are configured in the `src/config.h.in` file.

- Font set to "Liberation Mono 7"
- Scrollbar on the right side (scrollbar enabled by default)
- Copy selection with CTRL-SHIFT-C
- Paste at cursor position with CTRL-SHIFT-V
- Run selection via xdg-open with CTRL-SHIFT-X
- Intelligent selection behavior: A double-click will mark a word/path/email/url
- Scrollback buffer initially set to 10000 lines

## Requirements

- [CMake](http://www.cmake.org/) >= 2.6 (to do the build, on Debian-like systems you can `sudo apt-get install cmake`)
- The [VTE](http://library.gnome.org/devel/vte/) library (on a Debian-like system you may want to install it via `sudo apt-get install libvte-dev`)
- Unix/Linux system (Windows is not supported)

## Building

If everything goes as it should, you can run the build script,
`build.sh`, which will run `cmake` and `make`. The binary `tinyterm`
will be built in the `build/` directory. If you want to install it
globally, you can move into the `build` directory and run `make
install`.

## Memory Usage

Tinyterm is fairly lightweight. I ran a few tests, using
[pixelb's ps_mem](https://github.com/pixelb/ps_mem) tool. Here's what I
got compared to some other terminal emulators:

     Private  +    Shared  =  RAM used  Program
     4.1 MiB  + 668.0 KiB  =   4.7 MiB  tinyterm
     5.1 MiB  + 282.5 KiB  =   5.4 MiB  xterm
     5.8 MiB  +   1.2 MiB  =   7.0 MiB  xfce4-terminal
