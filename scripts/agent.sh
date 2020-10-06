#!/bin/sh
AGENT=`basename ${1} .sh`; shift
/usr/local/share/fossology/${AGENT}/agent/${AGENT} "${@}"
