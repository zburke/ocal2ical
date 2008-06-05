/*
 * ocal_export.cpp: display Oracle Calendar meetings in ICS format
 *
 * usage: ./ocal_export --hostname=ocs.host.edu \
 *                      --username=?/S=Eleazer/G=Wheelock/ \
 *                      --password=secret_password \
 *                      --password-file=/path/to/password_file \
 *                      --begin=yyyymmdd \
 *                      --end=yyyymmdd
 * 
 *
 * compilation dependencies: Oracle Collaboration Suite (OCS) SDK
 * 
 *     The MacOS OCS SDK is included, of course, on the 
 *     Linux 10gR1 (10.1.2) Supplemental DVD in the 
 *     Clients/Calendar/DeveloperPackage/SDK/Macintosh directory. 
 *     I mean, duh. Where else would you look for it? The DVD can 
 *     be downloaded here: 
 *     http://www.oracle.com/technology/software/products/cs/htdocs/1012linuxsoft.html
 * 
 * 
 * compile: g++ -Wall -arch ppc -I./sdk/public -L./sdk/lib -lcapi ocal_export.cpp -o ocal_export
 * 
 * 
 * runtime dependencies: The OracleCalendarSDK.bundle, located in 
 *     the OCS SDK's lib directory, must be in the same directory
 *     as this application
 *   
 * notes:
 * 
 * This code is based heavily on work done by Gregory Szorc 
 * at Case Western Resrve (see
 * http://wiki.case.edu/Oracle_Calendar/iCal_downloader) and
 * examples from the Oracle Collaboration Suite examples. 
 * 
 * I am not a C++ programmer. Actually, I'm not really a C 
 * programmer either, but I can kind of fake it on a good day. 
 * To anybody who knows what he's doing, the source will look
 * god-awful. Sorry. 
 * 
 * 
 * $Author$
 * $Revision$
 * $Date$
 * 
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <iostream>

#include "ocal_export.h"
#include "ctapi.h"

using namespace std;



/*
 * 1. get command line params (auth-n token, date ranges)
 * 2. open the connection and initialize the session
 * 3. retrieve the data
 * 4. there is no rule 4.
 *
 */
int 
main(int ac, char **av)
{

	// get command line params
	params *p = cli_parse(ac, av); 
	if (NULL == p) {
		cerr << "couldn't parse command line; missing required parameters" << endl;
		usage();
		exit(1); 
	}
	
	// open the connection and initialize the session
	CAPISession session = CSDK_SESSION_INITIALIZER;
	connect_init(&session, p); 
	
	// retrieve the data
	cout << get_events(&session, p);

	return 0;
}



/*
 * connect_init
 * connect to the calendar server and initialize the session. 
 * exit if the connection cannot be properly configured. 
 *
 * arguments
 *   session - session
 *   p - command line params
 *
 */
void
connect_init(CAPISession *session, params *p)
{
	CAPIStatus status = NULL;
	
	status = CSDK_CreateSession(CAPI_FLAGS_NONE, session);

	cerr << "Connecting to " << p->hostname << "...";
	status = CSDK_Connect(*session, CAPI_FLAG_NONE, p->hostname);
	if (CAPI_STAT_OK == status)
		cerr << "connected";		
	else 
		die(status, ERR_CONNECT);
	cerr << endl;


 	cerr << "Configuring Authentication, Compression, Encryption (ACE)...";
 	status = CSDK_ConfigureACE(*session, CAPI_FLAG_NONE, "cs-standard", "cs-simple", "cs-light");
	if (CAPI_STAT_OK == status)
 		cerr << "done";
	else 
		die(status, ERR_ACE);
 	cerr << endl;

	
	cerr << "Authenticating as " << p->username << "...";
	status = CSDK_Authenticate(*session, CSDK_FLAG_NONE, p->username, p->password);
	if (CAPI_STAT_OK == status)
		cerr << "authenticated" << endl;
	else 
		die(status, ERR_AUTHN);
	cerr << endl;


	CAPIHandle currUser = CSDK_HANDLE_INITIALIZER;
	status = CSDK_GetHandle(*session, NULL, CAPI_FLAG_NONE, &currUser);

}



/*
 * die
 * print an error message and EXIT. THIS FUNCTION DOES
 * NOT RETURN; IT CALLS EXIT. 
 *
 * arguments
 *     status - status code from last action
 *     errno - error number to exit with
 *
 */
void die(CAPIStatus status, int errno)
{
	const char * error_name = NULL;
	
	CSDK_GetStatusString(status, &error_name);
	cerr << endl << (error_name ? error_name : "") << ": Exiting!" << endl;
	exit(errno);
}



/*
 * get_events
 * 
 * arguments
 *   session - session
 *   p - command line params
 *
 * return
 *   pointer to string containing ics formatted events
 *
 */
const char *
get_events(CAPISession *session, params *p)
{
	CAPIStatus status = NULL;
	CAPIStream stream = NULL;
	CSDKRequestResult *result = 0;

	const char *iCaldata;

	cerr << "creating stream ...";
	status = CSDK_CreateMemoryStream(*session, &stream, NULL, &iCaldata, CSDK_FLAG_NONE);
	if (CAPI_STAT_OK != status)
		die(status, ERR_MEMORY);
	cerr << " done." << endl;
	
	cerr << "fetching events...";
	status = CSDK_FetchEventsByRange(*session, CSDK_FLAG_NONE, NULL, p->begin, p->end, NULL, stream, result);
	if (CAPI_STAT_OK != status)
		die(status, ERR_FETCH);
	cerr << " done ." << endl;	

	return iCaldata;
}



/*
 * cli_parse
 * grab connection params from the command line
 *
 * arguments
 *   ac - number of arguments
 *   av - argument values 
 * 
 * return
 *   pointer to a struct containing all command line values, or NULL
 *   if any required parameter is missing or empty
 *
 */
params *
cli_parse(int ac, char **av) 
{
	params *p = (params*) malloc(sizeof(params)); 

	// initialize the struct; how to do this in C++?
	// 
	// init in the type-def gives me the warning: 
	// error: ISO C++ forbids initialization of member ÔhostnameÕ
	// error: making ÔhostnameÕ static
	// error: invalid in-class initialization of static data member of non-integral type Ôconst char*Õ
	p->hostname = NULL;
	p->username = NULL;
	p->password = NULL;
	p->begin = NULL;
	p->end = NULL;
	
	if (NULL == p)
		return NULL;

	int c, i; 

	static struct option opts[] = {
		{ "hostname",      required_argument, NULL, 'h' },
		{ "username",      required_argument, NULL, 'u' },
		{ "password",      required_argument, NULL, 'p' },
		{ "password-file", optional_argument, NULL, 'f' },
		{ "begin",         required_argument, NULL, 'b' },
		{ "end",           required_argument, NULL, 'e' },
		{ NULL  , 0, NULL, 0 }
	};

	while ((c = getopt_long(ac, av, "hupfbe", opts, &i)) != -1) {
		switch (c) {
			case 'h':
				p->hostname = strdup(optarg);
				break;
			case 'u':
				p->username = strdup(optarg);
				break;
			case 'p':
				p->password = strdup(optarg);
				break;
			case 'f':
				// password on command line overrides password from file
				if (NULL != p->password)
					break; 
				p->password = read_password_file(optarg);
				break;
			case 'b':
				p->begin = strdup(optarg);
				break;
			case 'e':
				p->end = strdup(optarg);
				break;
		}
	}
	
	// all params are required
	if (NULL == p->hostname
		|| NULL == p->username
		|| NULL == p->password
		|| NULL == p->begin 
		|| NULL == p->end)
		return NULL;
		
	return p;

}



/* 
 * read_password_file
 * Read a single line from a file and return it as a string. 
 * Returns the string, or NULL if the file cannot be read. 
 *
 * arguments
 *     filepath - path of file to open
 *
 * return
 *    char * - string read from filepath
 *
 */
char *
read_password_file(char *filepath)
{
	FILE *filep = NULL;  /* ctype fp                  */
	char buf[BUFSIZ];    /* read buffer from ctype fp */
	
	/* open password file for reading                 */
	if ( (filep = fopen(filepath, "r")) == NULL) {
		cerr << "Couldn't open password file '" << filepath << endl;
		return NULL;
	}
	
	fgets(buf, BUFSIZ, filep);      // read ONE line
	buf[ strlen(buf) - 1 ] = '\0';  // make damn sure it's NULL terminated
	fclose(filep);
	
	return strdup(buf); 
	
}


/*
 * usage
 * display how this program should be called
 *
 */
void
usage() 
{
	cout << "This program exports meetings from Oracle Calendar" << endl;
	cout << "in ICS (ical) format. The output is wrapped in a MIME" << endl;
	cout << "envelope and must be decoded before it can be imported." << endl;
	cout << endl; 
	cout << "usage: " << endl;
	cout << "./ocal_export --hostname=ocs.host.edu \\" << endl;
	cout << "              --username=?/S=Eleazer/G=Wheelock/ \\" << endl;
	cout << "              --password=secret_password \\" << endl;
	cout << "              --begin=yyyymmdd \\" << endl;
	cout << "              --end=yyyymmdd" << endl;
	cout << endl;
	cout << " or " << endl;
	cout << endl;
	cout << "./ocal_export --hostname=ocs.host.edu \\" << endl;
	cout << "              --username=?/S=Eleazer/G=Wheelock/ \\" << endl;
	cout << "              --password-file=/path/to/password_file \\" << endl;
	cout << "              --begin=yyyymmdd \\" << endl;
	cout << "              --end=yyyymmdd" << endl;
}
