#
# dead-simple makefile with targets to build the Oracle-Calendar
# to ics exporter, and to install it. 
# 
#
# $Author$
# $Revision$
# $Date$
#
#

# define compiler and options
# note the OCS libs are PPC only so we must declare -arch ppc
cc = g++ -Wall -arch ppc -I./include -L./lib -lcapi


#
# build the application
#
ocal: ocal_export.cpp ocal_export.h
	${cc} ocal_export.cpp -o ocal_export

#
# install it
# 
install:
	sh ./install.sh

clean:
	rm -f *.o core ocal_export
