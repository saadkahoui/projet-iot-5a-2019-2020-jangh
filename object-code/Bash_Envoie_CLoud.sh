#!/bin/bash
input="/dev/ttyO2"
i=1
while IFS= read -r line
do
	if [[ $line =~ "T=" ]]; then
		val=$(echo $line | awk -F: '{print $2}' | sed 's/\r//')
		curl -F "$val" https://industrial.ubidots.com/api/v1.6/devices/jangh/?token=BBFF-UkMCX6WNIUtY8Sjr7eFLzepOR5sfid
	fi
	if [[ $line =~ "H=" ]]; then
		val=$(echo $line | awk -F: '{print $2}' | sed 's/\r//')
		curl -F "$val" https://industrial.ubidots.com/api/v1.6/devices/jangh/?token=BBFF-UkMCX6WNIUtY8Sjr7eFLzepOR5sfid
	fi
	if [[ $line =~ "A=" ]]; then
		val=$(echo $line | awk -F: '{print $2}' | sed 's/\r//')
		curl -F "$val" https://industrial.ubidots.com/api/v1.6/devices/jangh/?token=BBFF-UkMCX6WNIUtY8Sjr7eFLzepOR5sfid
	fi
	if [[ $line =~ "P=" ]]; then
		val=$(echo $line | awk -F: '{print $2}' | sed 's/\r//')
		curl -F "$val" https://industrial.ubidots.com/api/v1.6/devices/jangh/?token=BBFF-UkMCX6WNIUtY8Sjr7eFLzepOR5sfid
	fi

done < $input