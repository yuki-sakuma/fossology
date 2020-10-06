#!/bin/sh
cd `dirname ${0}`
python3 `basename ${0} .sh`.py "${@}" | sort -u
