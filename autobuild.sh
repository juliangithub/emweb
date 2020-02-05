#!/bin/bash
PWD=`pwd`;
USERID=`id -u`;
if [ ${USERID} -ne 0 ]; then
	echo "need root privilege !";
	exit;
fi

cd ${PWD}/http/src/
./configure
make
cd -
cd ${PWD}/cgi/
make
cd -
./install.sh