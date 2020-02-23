#!/bin/bash

# USERID=`id -u`;
# if [ ${USERID} -ne 0 ]; then
# 	echo "need root privilege !";
# 	exit;
# fi

PWD=`pwd`;
# echo ${PWD}
USER=`whoami`;
# echo ${USER}
cd ${PWD}/http/src/
./configure
make
cd -
cd ${PWD}/cgi/
make
cd -
./install.sh