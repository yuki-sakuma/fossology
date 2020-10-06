#!/bin/sh
cd `dirname ${0}`
sh agent.sh ${0} -J ${1} | jq -r '.[].results[] | select(.type == "statement") | .content'
