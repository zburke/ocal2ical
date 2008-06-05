/*
 * ocal_export.h
 * 
 * function prototypes, constants and 
 * 
 * $Author$
 * $Revision$
 * $Date$
 *
 */


 
/* Required with ctapi.h to import functions from the CAPI shared library */
#ifdef WIN32
#define CAPI_FUNC(a)  __declspec(dllimport) a
#else
#define CAPI_FUNC(a) a
#endif

#define CSDK_USE_OLD_NAMES

#include "ctapi.h"



#define MAX_HANDLES     32




/*
 * container for commandline params
 */
typedef struct {
	char *hostname; // calendar host, e.g. ocs.host.edu
	char *username; // person to authenticate as, e.g. ?/S=Wheelock/G=Eleazer/
	char *password; // password to authenticate with, e.g. SecretWord
	char *begin;    // YYYYMMDD start date for events, e.g. 20080301
	char *end;      // YYYYMMDD end date for events, e.g. 20080331
} params;



/*
 * exit codes
 */
enum err_msg {OK,           // everything is OK
              ERR_CONNECT,  // server connection
              ERR_ACE,      // session config
              ERR_AUTHN,    // authentication
              ERR_FETCH,    // authentication
              ERR_MEMORY,   // malloc
              ERR_FILEIO,   // fopen
              };


// CLI parser
params * cli_parse(int, char**);

// password file reader
char * read_password_file(char *);

// connection init
void connect_init(CAPISession *, params *);

// event retrieval
const char *get_events(CAPISession *, params *);

// error handling
void die(CAPIStatus, int);

// how to call this program
void usage();
