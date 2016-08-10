## Overview

Blind Jump is a procedurally generated space adventure game that I've been working on off and on in my free time. The object of the game is to get to the teleporter at the end of each level, while battling monsters and evil robots.

<div style="text-align:center" markdown="1">
![Alt text](/screenshot.png?raw=true)
</div>

## Contributing

One thing that I can't easily do myself is add support for every type of gamepad out there, because it would be expensive for me to buy them all. In time I'll add a UI menu for customizing controls, but either way it's always good to provide reasonable defaults, the more things that I can get working out of the box the better! If you can add your controller information to the function InputController::mapJsByid() and get it working, I'll happily merge your changes! Also, I have no idea how compiling on windows works, so if anyone can add a working make target for that I'd really appreciate it! 

## Installation

This project uses make and makedepend as a build system. Currently, the game is available on Unix-like systems, but it uses cross-platform libraries and could easily be ported (uses SFML 2.3, required to compile project). In bash:

Resolve dependencies
```bash
make depend
```

Compile (macOS)
```bash
make macOS
```
This will create a .app package in the prod folder.

Compile (Linux)
```bash
make Linux CPPFLAGS=-DLINUX
```
In the future I'm hoping to simplify the build system with cmake or something, because running the Linux target and also defining LINUX is kinda redundant.

## Bugs

Please report any bugs that you find. I want the application to feel well polished, so if there are any legitiment runtime issues I'd appreciate being notified of them. The only one I know of currently: the mac version of the game issues a crash report when returning from main, due to bad access when attempting to call some destructors. Any ideas?
