#!/bin/sh
FILENAME="$2/`basename $1`"
mkdir -p $2
cp -f $1 $FILENAME
chown $3:$4 $FILENAME
chmod $5 $FILENAME
