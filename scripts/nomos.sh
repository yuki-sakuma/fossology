#!/bin/sh
cd `dirname ${0}`
sh agent.sh ${0} -J ${1} | jq -r '.results[].licenses[]' | grep -v -e '^Dual-license$' -e '^No_license_found$' -e '^UnclassifiedLicense$'
