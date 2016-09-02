## Overview

Blind Jump is a procedurally generated space adventure game that I've been working on for fun in my free time. The object of the game is to get to the teleporter at the end of each level, while battling monsters and evil robots.

<p align="center"><img src="screenshot.png"/></p>

## Installation

For mac users, there is a pre-compiled app package in targets/macOS, you can simply click and drag that into your Applications/ directory. For Linux users, see instructions below for compiling from the source files. Windows steps tba.

## Building

(Dependencies: SFML 2.3 and a C++14 compiler)

Navigate into src/
```bash
cd src
```

Resolve dependencies
```bash
make depend
```

Compile (macOS)
```bash
make macOS
```
This will create a .app package in targets/macOS.

Compile (Linux)
```bash
make Linux
```
This places an executable in src/. It looks for resource files in ../Resources, so don't move it!

## Bugs

Please report any bugs that you find. I want the application to feel well polished, so if there are any legitiment runtime issues I'd appreciate being notified of them. The only one I know of currently: the mac version of the game issues a crash report when returning from main, due to bad access when attempting to call some destructors. I am currently working on fixing this.
