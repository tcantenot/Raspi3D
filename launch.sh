#!/bin/bash

EXE=./bin/exe

SCHED1=SCHED_FIFO
SCHED2=SCHED_FIFO
P1=10
P2=20
SCREEN_W=1600
SCREEN_W_HALF=$[SCREEN_W / 2]
SCREEN_H=900

sudo echo "Launching apps"

sudo $EXE -s $SCHED1 -p $P1 -x 0 -w $SCREEN_W_HALF -h $SCREEN_H &
sudo $EXE -s $SCHED2 -p $P2 -x $SCREEN_W_HALF -w $SCREEN_W_HALF -h $SCREEN_H
