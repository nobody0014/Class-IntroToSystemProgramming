#!/bin/bash 
# cat /proc/cpuinfo | grep "model name" | cut -d ":" -f2 | sed 
cat /proc/cpuinfo | grep "model name" | cut -c14-
