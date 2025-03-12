#!/bin/sh

# Default value
NUMBER=${1:-71}

scp -r -P 22 bin/bobcar pi${NUMBER}@raspberrypi${NUMBER}.local:~/Documents

#copy paste for copying to pi14 that has broken .local at sergios house
# scp -r -P 22 bin/bobcar pi14@192.168.0.109:~/Documents
