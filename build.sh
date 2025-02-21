#!/bin/bash

TARGET=scoundrel
DIR=C:/Users/Dominik/Desktop/scoundrel


INCDIR="
-I$DIR/raylib/include
-I$DIR/inc
"

LIBDIR="
-L$DIR/raylib/lib
"

LIBF="
-lraylib
-lgdi32
-lwinmm
"

SRCS="$(find ./src/ -iname '*.c')"
echo $SRCS

rm "./$TARGET.exe"
gcc -o $TARGET -Wall -Wextra $SRCS $INCDIR $LIBDIR $LIBF

"$DIR/$TARGET.exe"
ls