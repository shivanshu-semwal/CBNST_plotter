#!/bin/bash

# dependencies - subversion

# cloning the C library files
echo "Cloning the repo https://github.com/InductiveComputerScience/pbPlots/tree/master/C"

svn checkout https://github.com/InductiveComputerScience/pbPlots/trunk/C
var=$?

if [[ $var -ne 0 ]];then
	echo "Unable to clone repo... Failed"
else
	cd C
	rm -r .svn 
fi