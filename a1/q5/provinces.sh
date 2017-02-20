#!/bin/bash
# echo "Bangkok"
curl https://en.wikipedia.org/wiki/Provinces_of_Thailand?action=raw | grep -Eo "Bangkok" | head -n 1
curl https://en.wikipedia.org/wiki/Provinces_of_Thailand?action=raw | grep -Eo "\|\ .*\[\[.*Province.*\]\]" | grep -Eo "[a-zA-Z\ ]*Province" | sed 's/Province//'
