## Overview

Blind Jump is a procedurally generated space adventure game that I've been working on off and on in my free time. The object of the game is to get to the teleporter at the end of each level, while battling monsters and evil robots.

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
make Linux
```
This will create an executable in the src folder. In the future running this make target will create a deb packege in the prod folder.

## Bugs

Please report any bugs that you find. I want the application to feel well polished, so if there are any legitiment runtime issues I'd appreciate being notified of them.
