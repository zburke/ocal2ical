#!/bin/sh

# 
# install the Oracle Calendar .ICS exporter, its libraries,
# and a script to parse its output in /usr/local/. 
# 
# $Author$
# $Revision$
# $Date$
# 

PREFIX=$1
if [ -z $PREFIX ]; then
	PREFIX=/usr/local
fi

if [ `id -un` != 'root' ]
then 
	echo "You must be root to run this script!"
	exit 1;
fi


echo checking for required perl modules ...
if ! `/usr/bin/perl -MMIME::Parser -e '' > /dev/null 2>&1 `; then
	echo "missing MIME::Parser"
	exit 1;
fi
if ! `/usr/bin/perl -MGetopt::Long -e '' > /dev/null 2>&1 `; then
	echo "missing Getopt::Long"
	exit 1;
fi


echo installing libraries ...
if [ ! -d $PREFIX/lib ]; then
	mkdir $PREFIX/lib
fi
cp lib/*lib $PREFIX/lib/


echo installing header files ...
if [ ! -d $PREFIX/include ]; then
	mkdir $PREFIX/include
fi
cp include/ctapi.h $PREFIX/include/



echo installing Oracle Calendar exporter ...
if [ ! -d $PREFIX/bin ]; then
	mkdir $PREFIX/bin
fi

cp ocal_export $PREFIX/bin

echo installing Oracle Calendar export parser...
cp -R lib/OracleCalendarSDK.bundle $PREFIX/bin/

cp ocal_parse.pl $PREFIX/bin/

echo FINISHED!
