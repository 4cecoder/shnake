#!/bin/bash

# Compile the code
gcc -o shnake shnake.c -lncurses -ltinfo

# Run the game
./shnake
