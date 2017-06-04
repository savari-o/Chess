#!/bin/bash

for i in {1..10000}; do echo {a..h}{1..8}{a..h}{1..8} | cut -d\  -f $((RANDOM % 4096 + 1)); done
