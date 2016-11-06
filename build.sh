#!/bin/sh
cd arduboy/buttons
source ~/virtualenv/python2.7/bin/activate
pip install -U platformio
platformio run
