#!/usr/bin/env bash

value_dir='APP DRIVE DRIVE SYSTEM USER/main.c'

find $value_dir -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;
