#!/bin/sh
cd `dirname ${0}`
sh agent.sh ${0} -k `basename ${0} .sh`.kb -J ${1} | jq -r '.[] | select(.type != "no-match") | .license'
