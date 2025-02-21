#!/bin/bash

TARGET=scoundrel
DIR=C:/Users/Dominik/Desktop/scoundrel


INCDIR="
-I$DIR/raylib/include
"

LIBDIR="
-L$DIR/raylib/lib
"

LIBF="
-lraylib
-lgdi32
-lwinmm
"

rm "./$TARGET.exe"
gcc -o $TARGET -Wall -Wextra main.c $INCDIR $LIBDIR $LIBF

"$DIR/$TARGET.exe"
ls