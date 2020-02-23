#!/bin/bash
# PWD=`pwd`;
# USERID=`id -u`;
# if [ ${USERID} -ne 0 ]; then
# 	echo "need root privilege !";
# 	exit;
# fi

cd ${PWD}/http/src/
make clean
make distclean
cd -
cd ${PWD}/cgi/
make clean
echo "make clean Done Success............"