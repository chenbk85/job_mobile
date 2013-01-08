#!/bin/bash

if [[ $# != 1 ]]; then
	#statements
	echo Usage : drop_tables.sh db_filename
	exit 1
fi

rm -rf $1
