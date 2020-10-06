#!/bin/sh
cd `dirname ${0}`
docker-compose down
docker volume rm fossology_database fossology_repository
docker-compose up
