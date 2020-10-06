#!/bin/sh
cd `dirname ${0}`
sh agent.sh ${0} -J ${1} | jq -r '.[].results[].license' | grep -v -e '^Dual-license$'
