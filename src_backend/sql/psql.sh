#!/usr/bin/env sh
export PGPASSWORD=$POSTGRESQL_PASSWORD
psql -h localhost -d $POSTGRES_DB -U $POSTGRES_USER "$@"
