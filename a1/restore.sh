#!/bin/bash
cd /subm/u5780995/backups
if [ $? -eq 0 ]
then 
	name=`ls|sort -V | grep "$1" | head -n1`
	length=${#name}

	if [ $length -eq 0 ]
	then
		echo "no existing backup for $1"
	else 
		cd ./recovered
		if [ $? -eq 0 ]
		then
			cd $1
			if [ $? -eq 0 ]
			then 
				cd ..
				rm -rf $1
			else
				mkdir $1
			fi
		else
			mkdir -p recovered/$1
		fi
		cd ~/
		path="/subm/u5780995/backups/$name"
		cp -rf $path/. ./recovered/$1
		echo "$1 has been restored to ./recovered/"
	fi
else
	echo "no backup folder detected"
fi









