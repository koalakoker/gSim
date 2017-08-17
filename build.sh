#!/bin/sh

qmake gSimModel.pro
make
rm *.o
rm moc*
rm .qmake.stash Makefile
mv lib* ~/lib