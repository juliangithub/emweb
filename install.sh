#!/bin/bash
# USERID=`id -u`;
# if [ ${USERID} -ne 0 ]; then
# 	echo "need root privilege !";
# 	exit;
# fi

PWD=`pwd`;
# echo ${PWD}
USER=`whoami`;
Port=8080
#cp -rf ${PWD}/http/src/boa  /usr/local/bin/
mkdir -p ~/bin
cp -rf ${PWD}/http/src/boa  ~/bin/
mkdir -p /etc/boa
cp -rf ${PWD}/http/boa.conf /etc/boa/

echo "# Port: The port Boa runs on.  The default port for http servers is 80. " >> /etc/boa/boa.conf
echo "# If it is less than 1024, the server must be started as root. " >> /etc/boa/boa.conf
echo "Port ${Port}" >> /etc/boa/boa.conf

echo "#  User: The name or UID the server should run as." >> /etc/boa/boa.conf
echo "# Group: The group name or GID the server should run as." >> /etc/boa/boa.conf
echo "User ${USER}" >> /etc/boa/boa.conf
echo "Group ${USER}" >> /etc/boa/boa.conf

cp -rf ${PWD}/http/mime.types /etc/boa/
mkdir -p /var/www
cp -rf ${PWD}/www/* /var/www
mkdir -p /var/log/boa

#install cgic module.
mkdir -p /var/log/cgic
cp -rf ${PWD}/cgi/json.cgi /var/www/json.cgi
date
echo "=================="
stat ${PWD}/cgi/json.cgi
