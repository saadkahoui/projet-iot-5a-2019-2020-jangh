#!/bin/bash

stty -F /dev/ttyO2 115200 raw -echo

# Active Serial2
echo 'BB-UART2' > /sys/devices/platform/bone_capemgr/slots

# Active AP + DHCP
echo $'AT+CWMODE=3' > /dev/ttyO2
echo $'AT+CWSAP="COUCOU","1234",5,0\r' > /dev/ttyO2
echo $'AT+CWDHCP=0,1\r' > /dev/ttyO2

# Server
echo $'AT+CIPMUX=1\r' > /dev/ttyO2
echo $'AT+CIPSERVER=1,8000\r' > /dev/ttyO2