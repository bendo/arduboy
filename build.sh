#!/bin/sh
cd $TRAVIS_BUILD_DIR/iot/arduboy/buttons
source ~/virtualenv/python2.7/bin/activate
pip install -U platformio
platformio run
