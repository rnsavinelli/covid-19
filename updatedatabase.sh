#!/bin/bash
database=$(cat DATABASE_URL)
wget --backups=3 -N -P ./database $(echo $database)
