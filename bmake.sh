#!/bin/bash
if make; then
    ./meta
else
    echo "Make failed."
fi
