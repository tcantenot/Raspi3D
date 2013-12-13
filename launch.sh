#!/bin/bash

EXE=./bin/exe

SCHED1=SCHED_FIFO
SCHED2=SCHED_RR
P1=20
P2=10
SCREEN_W=1600
SCREEN_W_HALF=$[SCREEN_W / 2]
SCREEN_H=900
LAG=6

sudo echo "Launching apps"

sudo $EXE -s $SCHED1 -p $P1 -x 0 -w $SCREEN_W_HALF -h $SCREEN_H -l $LAG &
sudo $EXE -s $SCHED2 -p $P2 -x $SCREEN_W_HALF -w $SCREEN_W_HALF -h $SCREEN_H -l $LAG &
