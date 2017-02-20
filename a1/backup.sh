#!/bin/bash
topFolder=$(basename $1)
folderName="$topFolder"_$(date +%F)_$(date +%T)
echo $folderName
a="/subm/u5780995/backups/$folderName/"
mkdir -p $a
cp -ar $topFolder/. $a
echo "Backup $1 completed successfully."