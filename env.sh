#!/bin/bash
##
## EPITECH PROJECT, 2024
## B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
## File description:
## build
##

nproc=$(nproc)
echo "Number of processors: $nproc"
export MAKEFLAGS="-j $nproc"
