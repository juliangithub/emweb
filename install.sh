#!/bin/bash
PWD=`pwd`;
USERID=`id -u`;
if [ ${USERID} -ne 0 ]; then
	echo "need root privilege !";
	exit;
fi
#echo ${PWD}
cp -rf ${PWD}/http/src/boa /usr/local/bin/
mkdir -p /etc/boa
cp -rf ${PWD}/http/boa.conf /etc/boa/
cp -rf ${PWD}/http/mime.types /etc/boa/
#mkdir -p /var/www
cp -rf ${PWD}/www/* /var/www
mkdir -p /var/log/boa

#install cgic module.
mkdir -p /var/log/cgic
cp -rf ${PWD}/cgi/json.cgi /var/www/json.cgi


