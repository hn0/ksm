KSM
===

Kernel shutdown module (ksm) is a kernel module that shuts down linux machine with set probability over determined time period (machine will shutdown somewhere between boot and lifetime of the module).

Module has been designed as tool for testing newcomers technical (debuging) skills. Once installed on linux box, machine will seemingly randomly power off while newcomers task is to find the issue and fix the machine.

When started module will print message about current module settings (can be seen using dmesg). Once shutdown event has been hit, module will perform force machine poweroff with following log message:

> No luck, computer will shut down!
> If you are reading this message, great job! Well done, ksm module has been responsible for unexpected computer behavior.

By printing the message, module can be easily detected, but finding the same can be challenging task (user must inspect correct log from history). By not overcomplicating (over engineering) this module can indicate skilfully technical person that, rather than reinstalling complete system, is capable of detecting an issue in the system and resolving the same in acceptable way.

Although not endorsed, module can be installed on non-technical victim machine, but please remember how annoying can be when machine is crushing wile you performing a work on it.


Installation
------------

For successful build of the module installed linux-devel (linux-header) package on the system is prerequisite. Installed automake package can also help in build process.

After cloning the repository, to build module run make command:

```shell
make
```

Module comes with small handy shell script 'inject_ksm.sh', that will install and setup ksm module on the system.

```shell
sudo ./inject_ksm.sh build/ksm.ko
```

Provided shell script will perform an standard module installation, for more advance users installation of the module to nonstandard paths. Hiding the module will make a task of debugging a problem more challenging one, but please do not forget that module can present pain in the neck for the victim.


Usage
-----

Module supports setting of two runtime variables, timeout and success_prob. 

Setting sleep interval between probabilistically driven shutdown attempts can be achieved by timeout variable, passing the value of a sleep interval in seconds (integer). Default value is 1800 seconds (or 30 min).

Probability of shutdown event occurring can be adjusted by success_prob variable. Valid variable range is between 0 and 9 in increment of 1. Distinct variable increment values maps to 10% chance of event occurring meaning that probability of shutdown event is exactly mapped to order of magnitude higher percentage value (value of 6 means 60% chance of shutdown).

Regardless to shutdown probability value, module will shutdown the machine once max call count is reached (300 calls), meaning shutdown event is bound to occur in 300 * timeout value seconds with settable probability of the same event occurring sooner.

For the usage of the variables please refer to modules manual (good example: https://wiki.archlinux.org/index.php/kernel_modules).


License
-------

This application is a free software and you can redistribute and/or modify it under terms of GNU General Public License as published by the Free Software Fundation (http://www.gnu.org/copyleft/gpl.html).


Disclaimer
----------

This application is written and distributed with good intentions and in desire that someone will find it useful. However, it is distributed "AS IS" and without warranty of any kind. For any possible usage of this software you acknowledge and agree that the author makes no representation for the adequacy of this application for users needs, or that the application will be error free. Under no event arising in any way from usage of this software, author is liable for any direct, indirect, consequential or any other kind of damage (including, but not only limited to loss of profits or business interruption) regardless of its cause and on any theory of liability.