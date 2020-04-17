#!/bin/sh

BRIMG="embedded-network"

docker run --rm -it -e INDOCKER=1\
    -v=$(realpath "build"):/v/build \
    -v=$(realpath "$HOME/.buildroot-ccache"):/root/.buildroot-ccache \
    -v=$(realpath "dl"):/buildroot/dl \
    -v=$(pwd):/pwd \
    -w=/pwd "$BRIMG" /bin/bash
