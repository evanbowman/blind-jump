## Overview

Blind Jump is a procedurally generated space adventure game that I've been working on off and on in my free time. The object of the game is to get to the teleporter at the end of each level, while battling monsters and evil robots.

## Reading the Code

I began this project as a way of learning C++ syntax, so some older parts of the code suffer from bad design. I have gone back and rewritten large portions of the code, but at this point I do not plan on rewriting badly designed parts of game unless there would be an obvious performance benefit. Generally speaking, the code is fast, and is usually capable of pushing out more frames than most monitors can display. If I were to go back and rewrite all the bad parts, I'd never finish adding new stuff!

## Installation

This project uses make and makedepend as a build system. Currently, the game is Mac only, but uses cross-platform libraries and could easily be ported (uses SFML 2.3, required to compile project). To install on macOS:

1. Resolve dependencies
```bash
make depend
```

2. Compile
```bash
make MacOS
```

3. Install
```bash
mv -r ../prod/BlindJump.app/ ~/Applications
```