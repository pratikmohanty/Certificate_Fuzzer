# Source this file in shell scripts:
# . "$(dirname "$0")/functions.inc"
#
#  functions.inc - utility functions for shell-based test scripts
#
#  Copyright © 2002—2015 Sam Hocevar <sam@hocevar.net>
#
#  This library is free software. It comes without any warranty, to
#  the extent permitted by applicable law. You can redistribute it
#  and/or modify it under the terms of the Do What the Fuck You Want
#  to Public License, Version 2, as published by the WTFPL Task Force.
#  See http://www.wtfpl.net/ for more details.
#

DIR="$(dirname "$0")"
ZZUF="$DIR/../src/zzuf -E [.]ilist$"

ZZAT="$DIR/../src/zzat"
if [ ! -f "$ZZAT" ]; then
  echo "error: src/zzat is missing"
  exit 1
fi

ZZERO="$DIR/zzero"
if [ ! -f "$ZZERO" ]; then
  echo "error: test/zzero is missing"
  exit 1
fi

if file /bin/cat | grep 'statically linked' >/dev/null 2>&1; then
  STATIC_CAT=1
fi
if file /bin/dd | grep 'statically linked' >/dev/null 2>&1; then
  STATIC_DD=1
fi
if tail -n 1 /dev/null >/dev/null 2>&1; then
  TAILN="tail -n "
  TAILP="tail -n +"
else
  TAILN="tail -"
  TAILP="tail +"
fi

FAILED=0
TESTED=0

if [ -z "$1" ]; then
  seed=$(date | $ZZUF -m 2>/dev/null | sed 's/[^ ]* [abcdef0]*//' | tr -d abcdef | cut -b1-8)
else
  seed="$1"
fi

start_test() {
    echo ""
    echo "*** running $1 with seed $seed ***"
}

new_test() {
    echo "*** $1 *** "
}

pass_test() {
    TESTED="$(($TESTED + 1))"
    echo "$1"
}

fail_test() {
    TESTED="$(($TESTED + 1))"
    FAILED="$(($FAILED + 1))"
    echo "$1"
}

stop_test() {
    if [ "$FAILED" != 0 ]; then
        echo "*** $FAILED tests failed out of $TESTED ***"
        exit 1
    fi
    echo "*** all $TESTED tests OK ***"
}

