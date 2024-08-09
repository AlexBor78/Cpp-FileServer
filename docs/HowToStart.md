# How to build and start my project!?

## How to Build

### What are you need

Firstly you need have `make` and `gcc`/`g++` in terminal.

- on Arch you can try

    `sudo pacman -S make g++`

- on debiun/Ubuntu

    `sudo apt-get install make g++`

- on Windows you shoud to download make-build-system and g++(gcc) compiler
or use MSYS32 if you know how
(it's like arch)

### First build

Write to terminal `make init`.

Then write `make` and it will build.

### Build

Write `make` to terminal.

## How to Start

### Server

You have to write `./build/server` and server will start and listening(waiting) client's connections.

If you have error change port and/or ip in src/config.h and rebuild and restart server.

### Client

You have to write `./build/client` to one more terminal and client will start and trying to connect to server.

If client couldn't connect to server:

1. start server!!

2. change port or/and IP(address) in src/config.h and rebuild and restart client.

If you have another error you should read error message and think `is  that error of you or is my error`.
