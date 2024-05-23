#!/bin/bash

RESSOURCES=bonus/gource

gource -r 60 -b 000000 --user-image-dir $RESSOURCES/avatars \
--bloom-multiplier 0.7 --background-image $RESSOURCES/background.png \
--highlight-dirs --font-size 20 --font-file $RESSOURCES/font.ttf \
--stop-at-end --hide progress,usernames,date --title "ZapPikmin"
