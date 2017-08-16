#!/bin/sh

qmake gSimModel.pro
make
./remove_unused.sh
mv lib* ~/lib