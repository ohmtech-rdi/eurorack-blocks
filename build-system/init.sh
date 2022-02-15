#!/usr/bin/env bash

BUILD_SYSTEM_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]:-${(%):-%x}}" )" &> /dev/null && pwd )
export PATH=$PATH:$BUILD_SYSTEM_DIR/scripts
