#!/bin/sh
cd `dirname ${0}`
sh agent.sh ${0} -- ${1} | cut -d \; -f 2 | sed -e 's/,/\n/g' | grep -v -e '^No_license_found$' -e '^UnclassifiedLicense$'
