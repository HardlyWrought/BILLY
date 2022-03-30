#!/usr/bin/bash

set -e

for FILE in data/text/*.txt
do
	[ -e "${FILE}" ] || continue
	echo "Begin training on ${FILE}: $(date +"%c")";
	./bin/text_train ${FILE};
	echo "End training on ${FILE}: $(date +"%c")";
	mv ${FILE} data/text/completed/${FILE};
done

