#!/bin/bash

sudo ifconifg wlan0 up

nmcli dev wifi connect lazyshare password lazyshare

echo "Connected to Client"

# This script connects to hotspot
