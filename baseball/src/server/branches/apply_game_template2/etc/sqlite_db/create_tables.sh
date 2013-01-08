#!/bin/bash

if [[ $# < 1 ]]; then
	#statements
	echo Usage : create_tables.sh db_filename 
	exit 1
fi

script_path='.'
if [[ $# > 1 ]]; then
	#statements
	script_path=$2
fi

sqlite3 $1 < ${script_path}/Create_Tbl_Friend.sql
sqlite3 $1 < ${script_path}/Create_Tbl_Item.sql
sqlite3 $1 < ${script_path}/Create_Tbl_Item_Admin.sql
sqlite3 $1 < ${script_path}/Create_Tbl_PitcherSkill.sql
sqlite3 $1 < ${script_path}/Create_Tbl_PlayerBetter.sql
sqlite3 $1 < ${script_path}/Create_Tbl_PlayerPitcher.sql
sqlite3 $1 < ${script_path}/Create_Tbl_Result.sql
sqlite3 $1 < ${script_path}/Create_Tbl_RoundResult.sql
sqlite3 $1 < ${script_path}/Create_Tbl_Team.sql
sqlite3 $1 < ${script_path}/Create_Tbl_User.sql

echo === Create Table Complete =======================
sqlite3 $1 .tables
