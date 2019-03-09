#!/bin/bash
CURRENT_DIR=$(cd "$(dirname "${BASH_SOURCE-$0}")"; pwd)
SRC_ROOT=$CURRENT_DIR/../
CROSS_COMPILE=arm-linux-gnueabihf-
WIRING_NP_DIR=$SRC_ROOT/vendor/WiringNP

# init submodule
git submodule update --init

cd $WIRING_NP_DIR

cd wiringPi
make uninstall
make clean

make CROSS_COMPILE=$CROSS_COMPILE static
make install-static

