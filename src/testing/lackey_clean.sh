#!/bin/bash

valgrind --tool=lackey --trace-mem=yes "$@" 2> $1.$2.lackey.raw
grep -E '^ *[L|S|I].*[0-9a-f]+,[0-9]*$' $1.$2.lackey.raw > $1.$2.lackey.out
rm $1.$2.lackey.raw

