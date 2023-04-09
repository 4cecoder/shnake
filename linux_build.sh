#!/bin/bash

gcc -o shnake shnake.c -lncurses

if [ $? -eq 0 ]; then
  echo "Build successful! Run ./snake_game to start the game."
else
  echo "Build failed. Please check for errors in the source code."
fi