#!/usr/bin/env bash

#
#    Copyright (c) 2020 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

set -e

# Build script for GN EFT32 examples GitHub workflow.

source "$(dirname "$0")/../../scripts/activate.sh"

set -x
env

if [ -z "$3" ]; then
    gn gen --check --fail-on-unused-args --root="$1" --args="" "$2"/"$EFR32_BOARD"/
    ninja -v -C "$2"/"$EFR32_BOARD"/
    #print stats
    arm-none-eabi-size -A "$2"/"$EFR32_BOARD"/*.out
else
    if [ -z "$4" ]; then
        gn gen --check --fail-on-unused-args --root="$1" --args="efr32_board=\"$3\"" "$2/$3"
    else
        gn gen --check --fail-on-unused-args --root="$1" --args="efr32_board=\"$3\" $4" "$2/$3"
    fi
    ninja -v -C "$2/$3"
    #print stats
    arm-none-eabi-size -A "$2"/"$3"/*.out
fi
