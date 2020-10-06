#!/bin/sh
cd `dirname ${0}`
sh agent.sh ${0} -J ${1} | jq -r '.[].results[] | select(.type == "'"`basename ${0} .sh`"'") | .content'
