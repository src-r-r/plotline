#!/bin/bash

# Thanks to https://stackoverflow.com/a/246128
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:src/lib $DIR/src/app/plotline
