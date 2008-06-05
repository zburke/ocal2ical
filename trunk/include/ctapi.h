/*---------------------------------------------------------------------------*/
/**
 * @version $Revision$
 * @date    $Date$
 */
/*---------------------------------------------------------------------------*/
/*
 * Copyright (c) 1998, 2005, Oracle. All rights reserved.  
 */
/*---------------------------------------------------------------------------*/


#ifndef CAPI_H
#define CAPI_H

/* On Windows, you may need to define CAPI_FUNC to something like:
 * #define CAPI_FUNC(a)  __declspec(dllimport) a
 * to tell the linker that you're importing the CAPI functions.
 */
#ifndef CAPI_FUNC
#  define CAPI_FUNC(ret_type) ret_type
#endif

#include <stdlib.h>
#include <stdio.h>



/**
 * @addtogroup CAPI_TYPES
 * @{
 */
typedef void * CAPISession;
#define CSDK_SESSION_INITIALIZER 0

typedef void * CAPIHandle;
#define CSDK_HANDLE_INITIALIZER 0

typedef void * CSDKQuery;
#define CSDK_QUERY_INITIALIZER 0

typedef void * CAPIStream;
#define CSDK_STREAM_INITIALIZER 0

typedef unsigned long CAPIStatus;
typedef unsigned long CAPIFlag;

typedef char const * const * CAPIUIDSet;


#if defined(__cplusplus)
    class CcapiRequestResult;             
    typedef CcapiRequestResult *          CSDKRequestResult;
#else
    struct ScapiAbstractRequestResult;    
    typedef struct ScapiAbstractRequestResult *  CSDKRequestResult;
#endif
#define CSDK_REQUEST_RESULT_INITIALIZER 0


typedef int CSDKOperator;

typedef struct CSDKCondition
{
	const char *	prop;
	CSDKOperator	op;
	const char *	value;
} CSDKCondition;

/**
 * @}
 */

#ifndef DECL_FLAG
#    define DECL_FLAG(flag)
#endif /* DECL_FLAG */
/**
 * @addtogroup CAPI_FLAGS
 * @{
 */
/**
 * Used to select the default behaviour (same as CSDK_FLAG_NONE)
 * @ref CSDK_FLAG_NONE
 */
DECL_FLAG(CAPI_FLAG_NONE)
#define CAPI_FLAG_NONE                       ((CAPIFlag) (0))
#define CAPI_FLAGS_NONE CAPI_FLAG_NONE
/**
 * Used to select the default behaviour (same as CAPI_FLAG_NONE)
 * @ref CSDK_FLAG_NONE
 */
DECL_FLAG(CSDK_FLAG_NONE)
#define CSDK_FLAG_NONE                       ((CAPIFlag) (0))
/**
 * Used with CAPI_Store* functions to specify that the supplied properties are to be modified on the server without changing other properties (where possible)
 * @ref CSDK_FLAG_STORE_MODPROPS
 */
DECL_FLAG(CAPI_FLAG_STORE_MODPROPS)
#define CAPI_FLAG_STORE_MODPROPS             ((CAPIFlag) (1 << 2))
/**
 * Used with CAPI_Store* functions to specify that the supplied properties are to be cleared or deleted on the server.
 * @ref CSDK_FLAG_STORE_DELPROPS
 */
DECL_FLAG(CAPI_FLAG_STORE_DELPROPS)
#define CAPI_FLAG_STORE_DELPROPS             ((CAPIFlag) (1 << 3))

/**
 * Used with CAPI_DeleteEvent to specify that the instances are to be completely deleted, rather than removed from particular specified agendas.
 * Note that in this mode the handles passed to the function are ignored.
 * @ref CSDK_FLAG_DELETE_WHOLEINSTANCE
 */
DECL_FLAG(CAPI_FLAG_DELETE_WHOLEINSTANCE)
#define CAPI_FLAG_DELETE_WHOLEINSTANCE       ((CAPIFlag) (1 << 0))

/**
 * Used with CSDK_Store* calls to create a new object on the server.  If an object already exists with the same UID, an error will be returned
 * @ref CSDK_FLAG_STORE_CREATE
 */
DECL_FLAG(CSDK_FLAG_STORE_CREATE)
#define CSDK_FLAG_STORE_CREATE               ((CAPIFlag) (1 << 4))
/**
 * Used with CSDK_Store* functions to specify that the object (event/task/contact) on the server should be completely replaced by the given object
 * @ref CSDK_FLAG_STORE_REPLACE
 */
DECL_FLAG(CSDK_FLAG_STORE_REPLACE)
#define CSDK_FLAG_STORE_REPLACE              ((CAPIFlag) (1 << 5))
/**
 * Used with CSDK_Store* calls to create (CAPI_FLAG_STORE_CREATE) a new object (task/contact) on the server if none exists with the given UID, or to completely replace (CAPI_FLAG_STORE_REPLACE) an existing object 
 * @ref CSDK_FLAG_STORE_IMPORT
 */
DECL_FLAG(CSDK_FLAG_STORE_IMPORT)
#define CSDK_FLAG_STORE_IMPORT               ((CAPIFlag) (1 << 6))
/**
 * Used with CSDK_Store* calls to add, or modify the given properties to an existing object on the server.
 * @ref CSDK_FLAG_STORE_MODIFY
 */
DECL_FLAG(CSDK_FLAG_STORE_MODIFY)
#define CSDK_FLAG_STORE_MODIFY               ((CAPIFlag) (1 << 7))
/**
 * Used with CSDK_Store* calls to remove the given properties from an existing object on the server.  The UID property must be specified in the input, but will not itself be removed from the server.  This mode will not completely delete an object on the server - use CSDK_Delete* instead.
 * @ref CSDK_FLAG_STORE_REMOVE
 */
DECL_FLAG(CSDK_FLAG_STORE_REMOVE)
#define CSDK_FLAG_STORE_REMOVE               ((CAPIFlag) (1 << 8))
/**
 * Used with CSDK_StoreEvents to reply (set ATTENDEE and VALARM) to events organized by other people.
 * @ref CSDK_FLAG_STORE_REPLY
 */
DECL_FLAG(CSDK_FLAG_STORE_REPLY)
#define CSDK_FLAG_STORE_REPLY                ((CAPIFlag) (1 << 9))
/**
 * Used with CSDK_StoreEvents to invite the current user without
 * requiring an ATTENDEE property.
 * @ref CSDK_FLAG_STORE_INVITE_SELF
 */
DECL_FLAG(CSDK_FLAG_STORE_INVITE_SELF)
#define CSDK_FLAG_STORE_INVITE_SELF          ((CAPIFlag) (1 << 10))


/**
 * Used with CAPI_FetchEvent* and CSDK_FetchEvent* calls to exclude holidays
 * @ref CSDK_FLAG_FETCH_EXCLUDE_HOLIDAYS
 */
DECL_FLAG(CSDK_FLAG_FETCH_EXCLUDE_HOLIDAYS)
#define CSDK_FLAG_FETCH_EXCLUDE_HOLIDAYS        ((CAPIFlag) (1 << 0))
#define CAPI_FLAG_FETCH_EXCLUDE_HOLIDAYS CSDK_FLAG_FETCH_EXCLUDE_HOLIDAYS
/**
 * Used with CAPI_FetchEvent* and CSDK_FetchEvent* calls to exclude day events
 * @ref CSDK_FLAG_FETCH_EXCLUDE_DAYEVENTS
 */
DECL_FLAG(CSDK_FLAG_FETCH_EXCLUDE_DAYEVENTS)
#define CSDK_FLAG_FETCH_EXCLUDE_DAYEVENTS       ((CAPIFlag) (1 << 1))
#define CAPI_FLAG_FETCH_EXCLUDE_DAYEVENTS CSDK_FLAG_FETCH_EXCLUDE_DAYEVENTS
/**
 * Used with CAPI_FetchEvent* and CSDK_FetchEvent* calls to exclude daily notes
 * @ref CSDK_FLAG_FETCH_EXCLUDE_DAILYNOTES
 */
DECL_FLAG(CSDK_FLAG_FETCH_EXCLUDE_DAILYNOTES)
#define CSDK_FLAG_FETCH_EXCLUDE_DAILYNOTES      ((CAPIFlag) (1 << 2))
#define CAPI_FLAG_FETCH_EXCLUDE_DAILYNOTES CSDK_FLAG_FETCH_EXCLUDE_DAILYNOTES
/**
 * Used with CAPI_FetchEvent* and CSDK_FetchEvent* calls to exclude regular meetings (appointments)
 * @ref CSDK_FLAG_FETCH_EXCLUDE_APPOINTMENTS
 */
DECL_FLAG(CSDK_FLAG_FETCH_EXCLUDE_APPOINTMENTS)
#define CSDK_FLAG_FETCH_EXCLUDE_APPOINTMENTS    ((CAPIFlag) (1 << 3))
#define CAPI_FLAG_FETCH_EXCLUDE_APPOINTMENTS CSDK_FLAG_FETCH_EXCLUDE_APPOINTMENTS
/**
 * Used with CAPI_FetchEventsBy* to avoid reading some event properties from the
 * server.  There are significant performance gains when using this flag, but
 * X- properties and user-assigned UIDs will not be returned when using this flag.
 * @ref CSDK_FLAG_FETCH_NO_FIELDHOLDERS
 */
DECL_FLAG(CAPI_FLAG_FETCH_NO_FIELDHOLDERS)
#define CAPI_FLAG_FETCH_NO_FIELDHOLDERS ((CAPIFlag) (1 << 4))
/**
 * Used with CSDK_FetchEvent* calls to exclude events the caller has accepted.
 * @ref CSDK_FLAG_FETCH_EXCLUDE_ACCEPTED
 */
DECL_FLAG(CSDK_FLAG_FETCH_EXCLUDE_ACCEPTED)
#define CSDK_FLAG_FETCH_EXCLUDE_ACCEPTED        ((CAPIFlag) (1 << 5))
/**
 * Used with CSDK_FetchEvent* calls to exclude events the caller has declined.
 * @ref CSDK_FLAG_FETCH_EXCLUDE_DECLINED
 */
DECL_FLAG(CSDK_FLAG_FETCH_EXCLUDE_DECLINED)
#define CSDK_FLAG_FETCH_EXCLUDE_DECLINED        ((CAPIFlag) (1 << 6))
/**
 * Used with CSDK_FetchEvent* calls to exclude events the caller has not confirmed.
 * @ref CSDK_FLAG_FETCH_EXCLUDE_UNCONFIRMED
 */
DECL_FLAG(CSDK_FLAG_FETCH_EXCLUDE_UNCONFIRMED)
#define CSDK_FLAG_FETCH_EXCLUDE_UNCONFIRMED     ((CAPIFlag) (1 << 7))
/**
 * Used with CSDK_FetchEvent* calls to exclude events which are not owned by the caller.
 * @ref CSDK_FLAG_FETCH_EXCLUDE_NOTOWNER
 */
DECL_FLAG(CSDK_FLAG_FETCH_EXCLUDE_NOTOWNER)
#define CSDK_FLAG_FETCH_EXCLUDE_NOTOWNER        ((CAPIFlag) (1 << 8))
/**
 * Used with CSDK_FetchEvent* calls to filter out ATTENDEE properties for all attendees other than the agenda being viewed.
 * @ref CSDK_FLAG_FETCH_AGENDA_ATTENDEE_ONLY
 */
DECL_FLAG(CSDK_FLAG_FETCH_AGENDA_ATTENDEE_ONLY)
#define CSDK_FLAG_FETCH_AGENDA_ATTENDEE_ONLY    ((CAPIFlag) (1 << 9))
/**
 * Used with CSDK_FetchEvent* calls to return all events in a single VCALENDAR rather than one VCALENDAR per agenda.  This is faster and produces smaller output.
 * @ref CSDK_FLAG_FETCH_COMBINED
 */
DECL_FLAG(CSDK_FLAG_FETCH_COMBINED)
#define CSDK_FLAG_FETCH_COMBINED                ((CAPIFlag) (1 << 10))
/**
 * Used with CSDK_FetchContacts* calls to request version 2.1 vCards
 * @ref CSDK_FLAG_FETCH_VCARD_VERSION_2_1
 */
DECL_FLAG(CSDK_FLAG_FETCH_VCARD_VERSION_2_1)
#define CSDK_FLAG_FETCH_VCARD_VERSION_2_1       ((CAPIFlag) (1 << 11))
/**
 * Used with CSDK_FetchContacts* calls to request version 3.0 vCards (default)
 * @ref CSDK_FLAG_FETCH_VCARD_VERSION_3_0
 */
DECL_FLAG(CSDK_FLAG_FETCH_VCARD_VERSION_3_0)
#define CSDK_FLAG_FETCH_VCARD_VERSION_3_0       ((CAPIFlag) (1 << 12))
/**
 * Used with CSDK_FetchEvent* and CSDK_FetchTask* calls to request that
 * times be returned in the "local" timezone.  The current user's preferred
 * timezone as set on the calendar server is considered the "local" timezone.
 * @ref CSDK_FLAG_FETCH_LOCALTIMES
 */
DECL_FLAG(CSDK_FLAG_FETCH_LOCALTIMES)
#define CSDK_FLAG_FETCH_LOCALTIMES              ((CAPIFlag) (1 << 13))
/**
 * Used with CSDK_Store* and CSDK_Fetch* calls to specify that the stream should not be MIME encapsulated.
 * @ref CSDK_FLAG_STREAM_NOT_MIME
 */
DECL_FLAG(CSDK_FLAG_STREAM_NOT_MIME)
#define CSDK_FLAG_STREAM_NOT_MIME               ((CAPIFlag) (1 << 14))
/**
 * Can be passed to CSDK_FetchEvent* calls to request that recurrence rules not be expanded.  This flag is set by default with CSDK_FetchEventsByUID and can be overridden by using CSDK_FLAG_FETCH_EXPAND_RRULE.
 * @ref CSDK_FLAG_FETCH_DO_NOT_EXPAND_RRULE
 */
DECL_FLAG(CSDK_FLAG_FETCH_DO_NOT_EXPAND_RRULE)
#define CSDK_FLAG_FETCH_DO_NOT_EXPAND_RRULE               ((CAPIFlag) (1 << 15))
/**
 * Can be passed to CSDK_FetchEvent* calls to request that recurrence rules be expanded.  This flag is set by default with CSDK_FetchEventsByRange and CSDK_FetchEventsByAlarmRange and can be overridden by using CSDK_FLAG_FETCH_DO_NOT_EXPAND_RRULE.
 * @ref CSDK_FLAG_FETCH_EXPAND_RRULE
 */
DECL_FLAG(CSDK_FLAG_FETCH_EXPAND_RRULE)
#define CSDK_FLAG_FETCH_EXPAND_RRULE               ((CAPIFlag) (1 << 16))
/**
 * Can be passed to CSDK_FetchEvent* calls to request that resources without email addresses not be exported using invalid email addresses.
 * @ref CSDK_FLAG_FETCH_RESOURCES_WITHOUT_ADDRESSES
 */
DECL_FLAG(CSDK_FLAG_FETCH_RESOURCES_WITHOUT_ADDRESSES)
#define CSDK_FLAG_FETCH_RESOURCES_WITHOUT_ADDRESSES    ((CAPIFlag) (1 << 18))
/**
 * Can be passed to CSDK_FetchEvent* calls to request that users without email addresses not be exported using invalid email addresses.
 * @ref CSDK_FLAG_FETCH_USERS_WITHOUT_ADDRESSES
 */
DECL_FLAG(CSDK_FLAG_FETCH_USERS_WITHOUT_ADDRESSES)
#define CSDK_FLAG_FETCH_USERS_WITHOUT_ADDRESSES    ((CAPIFlag) (1 << 19))

/**
 * Can be passed to CSDK_Fetch*ByUID or CSDK_Delete*ByUID calls to request that, if possible, we continue the operations 
 * even if we encountered an error. Furthermore we return partial data if applicable (CSDK_Fetch*ByUID).   
 * Example, if we do a CSDK_Fetch*ByUID with multiple UID, and there is a UID that is not found.
 * Instead of the function returning a STATUS CODE and no data(default behavior), we would return STATUS CODE CSDK_STAT_OK
 * (error would only be reported in RequestResult) and the partial data found for the valid UID's. 
 * @ref CSDK_FLAG_CONTINUE_ON_ERROR
 */
DECL_FLAG(CSDK_FLAG_CONTINUE_ON_ERROR)
#define CSDK_FLAG_CONTINUE_ON_ERROR        ((CAPIFlag) (1 << 20))

/**
 * @} Flag ((OCAPFlag) (1 << 17)) is reserved for internal use 
 */


#ifndef DECL_CAPABILITY
#    define DECL_CAPABILITY(capab)
#endif /* DECL_CAPABILITY */
/**
 * @addtogroup CAPI_CAPABILITIES
 * @{
 */
typedef long CAPICapabilityID;
/**
 * Same as CAPI_CAPAB_CAPI_VERSION
 * @ref CSDK_CAPAB_VERSION
 */
DECL_CAPABILITY(CAPI_CAPAB_VERSION)
#define CAPI_CAPAB_VERSION                  (CAPICapabilityID)0x01
/**
 * Returns the SDK version as a string. (e.g. "9.0.4")
 * @ref CSDK_CAPAB_CSDK_VERSION
 */
DECL_CAPABILITY(CAPI_CAPAB_CAPI_VERSION)
#define CAPI_CAPAB_CAPI_VERSION             (CAPICapabilityID)0x02
/**
 * Returns the server version as a string. (e.g. "6.0").  A server connection must exist to read this capability.
 * @ref CSDK_CAPAB_SERVER_VERSION
 */
DECL_CAPABILITY(CAPI_CAPAB_SERVER_VERSION)
#define CAPI_CAPAB_SERVER_VERSION           (CAPICapabilityID)0x03
/**
 * Returns the largest date which CAPI can handle ("20371129")
 * @ref CSDK_CAPAB_MAXDATE
 */
DECL_CAPABILITY(CAPI_CAPAB_MAXDATE)
#define CAPI_CAPAB_MAXDATE                  (CAPICapabilityID)0x04
/**
 * Returns a comma delimited list of iCal components which CAPI does not process. ("VJOURNAL,VFREEBUSY")
 * @ref CSDK_CAPAB_UNSUPPORTED_ICAL_COMP
 */
DECL_CAPABILITY(CAPI_CAPAB_UNSUPPORTED_ICAL_COMP)
#define CAPI_CAPAB_UNSUPPORTED_ICAL_COMP    (CAPICapabilityID)0x05
/**
 * Returns a comma delimited list of iCal properties which CAPI does not process. ("GEO,COMMENT").  A server connection must exist to read this capability.
 * @ref CSDK_CAPAB_UNSUPPORTED_ICAL_PROP
 */
DECL_CAPABILITY(CAPI_CAPAB_UNSUPPORTED_ICAL_PROP)
#define CAPI_CAPAB_UNSUPPORTED_ICAL_PROP    (CAPICapabilityID)0x06
/**
 * Returns the authentication mechanisms supported by the server (e.g. "cs-standard,gssapi:kerberos5,sasl:KERBEROS_V4").  A server connection must exist to read this capability.
 * @ref CSDK_CAPAB_AUTH
 */
DECL_CAPABILITY(CAPI_CAPAB_AUTH)
#define CAPI_CAPAB_AUTH                     (CAPICapabilityID)0x10
/**
 * Returns the compression mechanisms supported by the server (e.g. "cs-simple,none").  A server connection must exist to read this capability.
 * @ref CSDK_CAPAB_COMP
 */
DECL_CAPABILITY(CAPI_CAPAB_COMP)
#define CAPI_CAPAB_COMP                     (CAPICapabilityID)0x11
/**
 * Returns the encryption mechanisms supported by the server (e.g. "cs-light,none").  A server connection must exist to read this capability.
 * @ref CSDK_CAPAB_ENCR
 */
DECL_CAPABILITY(CAPI_CAPAB_ENCR)
#define CAPI_CAPAB_ENCR                     (CAPICapabilityID)0x12
/**
 * Returns information about CAPI
 * @ref CSDK_CAPAB_ABOUT_BOX
 */
DECL_CAPABILITY(CAPI_CAPAB_ABOUT_BOX)
#define CAPI_CAPAB_ABOUT_BOX                (CAPICapabilityID)0x13
/**
 * Returns the minimum idle refresh rate for SDK clients
 * @ref CSDK_CAPAB_MINREFRESHRATE
 */
DECL_CAPABILITY(CAPI_CAPAB_MINREFRESHRATE)
#define CAPI_CAPAB_MINREFRESHRATE           (CAPICapabilityID)0x14
/**
 * @}
 */


/**
 * @addtogroup CAPI_FLAGS
 * @{
 */
/* Flags for CAPI_Logoff */
#define CAPI_LOGOFF_STAY_CONNECTED          0x01

/* Recurrence-Id modifier */
#define CAPI_THISINSTANCE    0x01
#define CAPI_THISANDPRIOR    0x02
#define CAPI_THISANDFUTURE   0x03

/* Return values for send and receive callbacks */
#define CAPI_CALLBACK_CONTINUE          (int)0
#define CAPI_CALLBACK_CANT_MALLOC_ERR   (int)1
#define CAPI_CALLBACK_CANT_REALLOC_ERR  (int)2
#define CAPI_CALLBACK_DONE              (int)-1

/* Flags for CAPI_HandleInfo, mutually exclusive */
#define CAPI_HANDLE_TYPE     0x00
#define CAPI_HANDLE_NAME     0x01
#define CAPI_HANDLE_MAILTO   0x02
#define CSDK_HANDLE_GUID     0x04

/* Flags for CAPI_StoreEvent, mutually exclusive */
#define CAPI_STORE_REPLACE   0x00
#define CAPI_STORE_UPDATE    0x01
#define CAPI_STORE_DELPROP   0x02

/* Email and sms notifications */
#define CAPI_NOTIFY_EMAIL    0x04
#define CAPI_NOTIFY_SMS      0x08

/* Alarm types */
#define CAPI_FLAG_ALARM_STARTTIME 0x01
#define CAPI_FLAG_ALARM_DUETIME   0x02
#define CAPI_ALARM_STARTTIME      0x01
#define CAPI_ALARM_DUETIME        0x02

/* Task range types */
#define CAPI_TASK_RANGE_MASK          0x03
#define CAPI_TASK_RANGE_STARTTIME     0x01
#define CAPI_TASK_RANGE_DUETIME       0x02
#define CAPI_TASK_RANGE_COMPLETEDTIME 0x03

/* Operators to be used for building queries */
/* Operators ending with "_CS" indicate case-sensitive searching */
/* Other operators (less, less equal, etc) are always case-INsensitive. */
/* Note that the last two operators (and, or) are Logical OPerators which 
   are used for combining conditions, not pattern matching operators. */

#define CSDK_OP_NE              (CSDKOperator) 0
#define CSDK_OP_EQ              (CSDKOperator) 1
#define CSDK_OP_LT              (CSDKOperator) 2
#define CSDK_OP_LE              (CSDKOperator) 3
#define CSDK_OP_GT              (CSDKOperator) 4
#define CSDK_OP_GE              (CSDKOperator) 5
#define CSDK_OP_STARTSWITH      (CSDKOperator) 7
#define CSDK_OP_NE_CS           (CSDKOperator) 9
#define CSDK_OP_EQ_CS           (CSDKOperator) 10
#define CSDK_OP_STARTSWITH_CS   (CSDKOperator) 12
#define CSDK_LOP_AND            (CSDKOperator) 14
#define CSDK_LOP_OR             (CSDKOperator) 15

/* These properties are currently supported by CSDK_FetchContactsByQuery. */
/* Note that for the FN property, the format is "<last name>, <first name>". */
#define CSDK_PROPERTY_FORMATTEDNAME     "FN"
#define CSDK_PROPERTY_BIRTHDATE         "BDAY"
#define CSDK_PROPERTY_TITLE             "TITLE"
#define CSDK_PROPERTY_ROLE              "ROLE"
#define CSDK_PROPERTY_COMMENT           "COMMENT"
#define CSDK_PROPERTY_CATEGORIES        "CATEGORIES"
#define CSDK_PROPERTY_NICKNAME          "NICKNAME"
#define CSDK_PROPERTY_X_SPOUSE          "X-ORACLE-SPOUSE"
#define CSDK_PROPERTY_X_ANNIVERSARY     "X-ORACLE-ANNIVERSARY"
#define CSDK_PROPERTY_X_OFFICE          "X-ORACLE-OFFICE"
#define CSDK_PROPERTY_X_ASSISTANTNAME   "X-ORACLE-ASSISTANTNAME"
        
/**
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*---------------------------------------------------------------------------
 *
 * INITIALIZATION / CONFIGURATION
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(CAPIStatus) CSDK_SetConfigFile(
    const char *    in_configFileName,              /* ini file name */
    const char *    in_logFileName);                /* log filename */


/*---------------------------------------------------------------------------
 *
 * SESSIONS
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(CAPIStatus) CSDK_CreateSession(
    CAPIFlag        in_flags,
    CAPISession *   out_session);


CAPI_FUNC(CAPIStatus) CSDK_DestroySession(
    CAPISession *   io_session);


/*---------------------------------------------------------------------------
 *
 * CONNECT / AUTHENTICATE / DISCONNECT
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(CAPIStatus) CSDK_ConnectAsSysop(
    CAPISession     in_session,
    CAPIFlag        in_flags,
    const char *    in_host,
    const char *    in_nodeId,
    const char *    in_password);


CAPI_FUNC(CAPIStatus) CSDK_Connect(
    CAPISession     in_session,
	CAPIFlag        in_flags,
	const char *    in_host);


CAPI_FUNC(CAPIStatus) CSDK_ConfigureACE(
    CAPISession     in_session,
    CAPIFlag        in_flags,
    const char *    in_authenticationMechanism,
    const char *    in_compressionMechanism,
    const char *    in_encryptionMechanism);


CAPI_FUNC(CAPIStatus) CSDK_Authenticate(
    CAPISession     in_session,
    CAPIFlag        in_flags,
    const char *    in_user,
    const char *    in_password);


CAPI_FUNC(CAPIStatus) CSDK_Deauthenticate(
    CAPISession     in_session,
    CAPIFlag        in_flags);


CAPI_FUNC(CAPIStatus) CSDK_Disconnect(
    CAPISession     in_session,
    CAPIFlag        in_flags);


CAPI_FUNC(CAPIStatus) CSDK_SetIdentity(
    CAPISession     in_session,                     /* login session handle */
    const char *    in_user,                        /* user to work as */
    CAPIFlag        in_flags);                      /* bit flags */


/*---------------------------------------------------------------------------
 *
 * CAPI, SERVER CAPABILITIES
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(CAPIStatus) CSDK_GetCapabilities(
    CAPISession      in_session,                     /* login session handle */
    CAPICapabilityID in_capabilityID,                /* the capability to look for */
    CAPIFlag         in_flags,                       /* bit flags */
    const char **    out_value);                     /* a read-only string describing the capability */

    

/*---------------------------------------------------------------------------
 *
 * STREAMS
 *
 *---------------------------------------------------------------------------*/

typedef int (*CAPICallback)(
    void *      in_userData,                        /* user-defined data (the value supplied
                                                       in CSDK_CreateXXXStream) */
    char *      io_data,                            /* buffer to read or write  */
    size_t      in_dataSize,                        /* the number of characters in io_data */
    size_t *    out_datSize);                       /* the number of characters copied */


CAPI_FUNC(CAPIStatus) CSDK_CreateCallbackStream (
    CAPISession     in_session,                     /* login session handle */
    CAPIStream *    out_stream,                     /* the created stream */
    CAPICallback    in_sendCallback,                /* send data callback */
    void *          in_sendUserData,                /* a value to pass to in_sendCallback */
    CAPICallback    in_recvCallback,                /* receive data callback */
    void *          in_recvUserData,                /* a value to pass to in_recvCallback */
    CAPIFlag        in_flags);                      /* bit flags */


CAPI_FUNC(CAPIStatus) CSDK_CreateMemoryStream(
    CAPISession     in_session,                     /* login session handle */
    CAPIStream *    out_stream,                     /* the created stream */
    const char *    in_readBuffer,                  /* buffer for CAPI to read from */
    const char **   out_writeBufferPtr,             /* on output, points to a buffer that CAPI
                                                       will write into */
    CAPIFlag        in_flags);                      /* bit flags */


CAPI_FUNC(CAPIStatus) CSDK_CreateFileStreamFromFilenames(
    CAPISession     in_session,                     /* login session handle */
    CAPIStream *    out_stream,                     /* the created stream */
    const char *    in_readFileName,                /* name of file which CAPI will read from */
    const char *    in_readMode,                    /* mode in which CAPI will read file to read from */
    const char *    in_writeFileName,               /* name of file which CAPI will write to */
    const char *    in_writeMode,                   /* mode in which CAPI will write to file to write to */
    CAPIFlag        in_flags);                      /* bit flags */


CAPI_FUNC(CAPIStatus) CSDK_DestroyStream(
    CAPISession     in_session,                     /* login session handle */
    CAPIStream *    io_stream);                     /* stream to destroy  */


CAPI_FUNC(CAPIStatus) CSDK_DestroyMultipleStreams(
    CAPISession     in_session,                     /* login session handle */
    CAPIStream *    in_streams,                     /* array of streams to destroy  */
    int             in_numStreams,                  /* number of streams in in_streams  */
    CAPIFlag        in_flags);                      /* bit flags */



/*---------------------------------------------------------------------------
 *
 * USER HANDLES
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(CAPIStatus) CSDK_GetHandle(
    CAPISession     in_session,                     /* login session handle */
    const char *    in_user,                        /* user as defined for CAPI_Login, or NULL */
    CAPIFlag        in_flags,                       /* bit flags */
    CAPIHandle *    out_handle);                    /* handle for in_user */


CAPI_FUNC(CAPIStatus) CSDK_GetHandleInfo(
    CAPISession     in_session,                     /* login session handle */
    CAPIHandle      in_handle,                      /* handle to get info for */
    CAPIFlag        in_flags,                       /* flags to specify which info to return */ 
    const char **   out_info);                      /* read-only handle information */


CAPI_FUNC(CAPIStatus) CSDK_DestroyHandle(
    CAPISession     in_session,                     /* login session handle */
    CAPIHandle *    in_handle);                     /* handle to destroy */


CAPI_FUNC(CAPIStatus) CSDK_DestroyMultipleHandles(
    CAPISession     in_session,                     /* login session handle */
    CAPIHandle *    in_handles,                     /* array of handles to destroy */
    int             in_numHandles,                  /* number of handles in in_handles  */
    CAPIFlag        in_flags);                      /* bit flags */


/*---------------------------------------------------------------------------
 *
 * QUERIES
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(CAPIStatus) CSDK_CreateQuery(
    CSDKCondition * in_condition,
    CSDKQuery *     out_query);


CAPI_FUNC(CAPIStatus) CSDK_AddConditionToQuery(
    CSDKQuery       in_query,
    CSDKCondition * in_condition,
    CSDKOperator    in_operator);
    
    
CAPI_FUNC(CAPIStatus) CSDK_DestroyQuery(
    CSDKQuery *     io_query);


/*---------------------------------------------------------------------------
 *
 * VEVENTS ("Events")
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(CAPIStatus) CSDK_StoreEvents(
    CAPISession         in_session,
    CAPIFlag            in_flags,
    CAPIStream          in_stream,
    CSDKRequestResult * out_requestResult);

CAPI_FUNC(CAPIStatus) CSDK_DeleteEvents( 
    CAPISession         in_session,
    CAPIFlag            in_flags,
    CAPIUIDSet          in_UIDs,
    const char *        in_RECURRENCEID,
    int                 in_modifier,
    CSDKRequestResult * out_requestResult);
        
CAPI_FUNC(CAPIStatus) CSDK_FetchEventsByUID( 
    CAPISession         in_session,
    CAPIFlag            in_flags,
    CAPIHandle          in_agenda,
    CAPIUIDSet          in_UIDs,
    const char *        in_RECURRENCEID,
    int                 in_modifier,
    const char **       in_requestProperties,
    CAPIStream          in_stream,
    CSDKRequestResult * out_requestResult);

CAPI_FUNC(CAPIStatus) CSDK_FetchEventsByAlarmRange( 
    CAPISession         in_session,
    CAPIFlag            in_flags,
    CAPIHandle *        in_agendas,
    const char *        in_start,
    const char *        in_end,
    const char **       in_requestProperties,
    CAPIStream          in_stream,
    CSDKRequestResult * out_requestResult);

CAPI_FUNC(CAPIStatus) CSDK_FetchEventsByRange( 
    CAPISession         in_session,
    CAPIFlag            in_flags,
    CAPIHandle *        in_agendas,
    const char *        in_start,
    const char *        in_end,
    const char **       in_requestProperties,
    CAPIStream          in_stream,
    CSDKRequestResult * out_requestResult);



/*---------------------------------------------------------------------------
 *
 * VTODOs ("Tasks")
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(CAPIStatus) CSDK_StoreTasks(
    CAPISession         in_session,                 /* login session handle */
    CAPIFlag            in_flags,                   /* bit flags */
    CAPIStream          in_stream,                  /* stream for CAPI to read data from */
    CSDKRequestResult * out_requestResult);         /* More detailed results for this request. May be NULL */


CAPI_FUNC(CAPIStatus) CSDK_FetchTasksByAlarmRange(
    CAPISession         in_session,                 /* login session handle */
    CAPIFlag            in_flags,                   /* bit flags */
    CAPIHandle *        in_handles,                 /* calendar(s) from which to fetch events  */
    const char *        in_start,                   /* range start time eg "19750401T000000Z" */
    const char *        in_end,                     /* range end time eg "20012301T000000Z" */
    const char **       in_requestProperties,       /* array of iCalendar properties to return
                                                       (NULL ==> no filtering) */
    CAPIStream          in_stream,                  /* stream for CAPI to write into */
    CSDKRequestResult * out_requestResult);         /* More detailed results for this request. May be NULL */


CAPI_FUNC(CAPIStatus) CSDK_FetchTasksByRange(
    CAPISession         in_session,                 /* login session handle */
    CAPIFlag            in_flags,                   /* bit flags */
    CAPIHandle *        in_handles,                 /* calendar(s) from which to fetch events  */
    const char *        in_start,                   /* range start time eg "19750401T000000Z" */
    const char *        in_end,                     /* range end time eg "20012301T000000Z" */
    const char **       in_requestProperties,       /* array of iCalendar properties to return
                                                       (NULL ==> no filtering) */
    CAPIStream          in_stream,                  /* stream for CAPI to write into */
    CSDKRequestResult * out_requestResult);         /* More detailed results for this request. May be NULL */


CAPI_FUNC(CAPIStatus) CSDK_FetchTasksByUID(
    CAPISession         in_session,                 /* login session handle */
    CAPIHandle          in_handle,                  /* calendar from which to fetch task(s) */
    CAPIFlag            in_flags,                   /* bit flags */
    CAPIUIDSet          in_UIDs,                    /* array of UIDs to fetch */
    const char **       in_requestProperties,       /* array of iCalendar properties to return
                                                       (NULL ==> no filtering) */
    CAPIStream          in_stream,                  /* stream for CAPI to write into */
    CSDKRequestResult * out_requestResult);         /* More detailed results for this request. May be NULL */


CAPI_FUNC(CAPIStatus) CSDK_DeleteTasks(
    CAPISession         in_session,                 /* login session handle */
    CAPIFlag            in_flags,                   /* bit flags */
    CAPIUIDSet          in_UIDs,                    /* array of UIDs to fetch */
    CSDKRequestResult * out_requestResult);         /* More detailed results for this request. May be NULL */


/*---------------------------------------------------------------------------
 *
 * VCARDs ("Contacts") 
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(CAPIStatus) CSDK_StoreContacts(
    CAPISession         in_session,                 /* login session handle */
    CAPIFlag            in_flags,                   /* bit flags */
    CAPIStream          in_stream,                  /* stream for CAPI to read data from */
    CSDKRequestResult * out_requestResult);         /* More detailed results for this request. May be NULL */


CAPI_FUNC(CAPIStatus) CSDK_FetchContactsByUID(
    CAPISession         in_session,                 /* login session handle */
    CAPIFlag            in_flags,                   /* bit flags */
    CAPIUIDSet          in_UIDs,                    /* array of UIDs to fetch */
    const char **       in_requestProperties,       /* array of iCalendar properties to return
                                                       (NULL ==> no filtering) */
    CAPIStream          in_stream,                  /* stream for CAPI to write into */
    CSDKRequestResult * out_requestResult);         /* More detailed results for this request. May be NULL */


CAPI_FUNC(CAPIStatus) CSDK_FetchContactsByQuery(
    CAPISession         in_session,                 /* login session handle */
    CAPIFlag            in_flags,                   /* bit flags */
    CSDKQuery           in_query,                   /* query */
    const char **       in_requestProperties,       /* array of vCard properties to return
                                                       (NULL ==> no filtering) */
    CAPIStream          in_stream,                  /* stream for CAPI to write into */
    CSDKRequestResult * out_requestResult);         /* More detailed results for this request. May be NULL */
    

CAPI_FUNC(CAPIStatus) CSDK_DeleteContacts(
    CAPISession         in_session,                 /* login session handle */
    CAPIFlag            in_flags,                   /* bit flags */
    CAPIUIDSet          in_UIDs,                    /* array of UIDs to fetch */
    CSDKRequestResult * out_requestResult);         /* More detailed results for this request. May be NULL */


/*---------------------------------------------------------------------------
 *
 * Request Results
 *
 *---------------------------------------------------------------------------*/


CAPI_FUNC(CAPIStatus) CSDK_GetFirstResult(      
        CSDKRequestResult    in_requestResult,      /* the RequestResult to read */
        CAPIHandle *         out_user,              /* the user that caused the results */ 
        const char **        out_uid,               /* a UID returned as a result */
        CAPIStatus *         out_status);           /* the result's status */


CAPI_FUNC(CAPIStatus) CSDK_GetFirstFailure(
        CSDKRequestResult    in_requestResult,      /* the RequestResult to read */
        CAPIHandle *         out_user,              /* the user that caused the results */ 
        const char **        out_uid,               /* a UID returned as a result */
        CAPIStatus *         out_status);           /* the result's status */


CAPI_FUNC(CAPIStatus) CSDK_GetNextResult(
        CSDKRequestResult    in_requestResult,      /* the RequestResult to read */
        CAPIHandle *         out_user,              /* the user that caused the results */ 
        const char **        out_uid,               /* a UID returned as a result */
        CAPIStatus *         out_status);           /* the result's status */


CAPI_FUNC(CAPIStatus) CSDK_GetNextFailure(
        CSDKRequestResult    in_requestResult,      /* the RequestResult to read */
        CAPIHandle *         out_user,              /* the user that caused the results */ 
        const char **        out_uid,               /* a UID returned as a result */
        CAPIStatus *         out_status);           /* the result's status */


CAPI_FUNC(CAPIStatus) CSDK_GetFirstParseError(
        CSDKRequestResult    in_requestResult,      /* the RequestResult to read */
        CAPIStatus *         out_status,            /* the result's status */
        const char **        out_errorBuffer,       /* the beginning of the buffer with the error */
        const char **        out_errorLocation,     /* the location in *out_errorBuffer where the error occurred */
        const char **        out_message);          /* may contain additional information */
    

CAPI_FUNC(CAPIStatus) CSDK_GetNextParseError(
        CSDKRequestResult    in_requestResult,      /* the RequestResult to read */
        CAPIStatus *         out_status,            /* the result's status */
        const char **        out_errorBuffer,       /* the beginning of the buffer with the error */
        const char **        out_errorLocation,     /* the location in *out_errorBuffer where the error occurred */
        const char **        out_message);          /* may contain additional information */


CAPI_FUNC(CAPIStatus) CSDK_DestroyResult(   
        CSDKRequestResult *  io_requestResult);     /* the result to dispose of */


/*---------------------------------------------------------------------------
 *
 * STATUS INTERPRETATION
 *
 *---------------------------------------------------------------------------*/

CAPI_FUNC(void) CSDK_GetStatusString(
    CAPIStatus      in_status,                      /* a status code */
    const char **   out_errorString);               /* on output, points to a read-only string
                                                       which corresponds to the status.
                                                       (e.g. "CAPI_STAT_DATA_UID_NOTFOUND") */

CAPI_FUNC(void) CSDK_GetStatusCode(
    CAPIStatus      in_status,                      /* a status */
    int *           out_statusCode);                /* on output, status code 
                                                       (e.g. CSDK_STAT_DATA_UID_NOTFOUND) */

 
CAPI_FUNC(void) CSDK_GetStatusLevels(
    CAPIStatus      in_status,                      /* a status code */
    unsigned long * out_field1,                     /* field 1 (mode) of the status code */
    unsigned long * out_field2,                     /* field 2 (class) of the status code */
    unsigned long * out_field3,                     /* field 3 of the status code */
    unsigned long * out_field4,                     /* field 4 of the status code */
    unsigned long * out_field5);                    /* field 5 of the status code */


/* These masks are used for interpreting CAPIStatus values */

#define CAPI_STATMASK_MODE_FIELD        ((CAPIStatus) 0xFF << 24)
#define CAPI_STATMASK_CLASS_FIELD       ((CAPIStatus) 0x1F << 19)
#define CAPI_STATMASK_3_FIELD           ((CAPIStatus) 0x1F << 14)
#define CAPI_STATMASK_4_FIELD           ((CAPIStatus) 0x3F << 8)
#define CAPI_STATMASK_5_FIELD           ((CAPIStatus) 0xFF)

/* Status at certain levels of detail */
#define CAPI_STATMASK_CLASS    ((CAPIStatus) CAPI_STATMASK_CLASS_FIELD)
#define CAPI_STATMASK_3        ((CAPIStatus) (CAPI_STATMASK_CLASS + CAPI_STATMASK_3_FIELD))
#define CAPI_STATMASK_4        ((CAPIStatus) (CAPI_STATMASK_3 + CAPI_STATMASK_4_FIELD))
#define CAPI_STATMASK_5        ((CAPIStatus) (CAPI_STATMASK_4 + CAPI_STATMASK_5_FIELD))


#ifdef __cplusplus
}
#endif



/*---------------------------------------------------------------------------
 *
 * CAPI Status values
 *
 *---------------------------------------------------------------------------*/

#ifndef DECL_STATUS
#    define DECL_STATUS(capistat)
#endif /* DECL_STATUS */

/**
 * @addtogroup CAPI_STATUS
 * @{
 */
 
/**
 * Operation completed successfully. Value 0
 * @ref CSDK_STAT_OK
 */
DECL_STATUS(CAPI_STAT_OK)
#define CAPI_STAT_OK                   ((CAPIStatus) 0x00)

/* Mode, field 1 */
DECL_STATUS(CAPI_STATMODE_FATAL)
#define CAPI_STATMODE_FATAL      ((CAPIStatus) 0x80 << 24)


/* Class, field 2 */
/**
 * Data class status
 * @ref CSDK_STAT_DATA
 */
DECL_STATUS(CAPI_STAT_DATA)
#define CAPI_STAT_DATA       ((CAPIStatus) 0x1 << 19)

/**
 * Service class status
 * @ref CSDK_STAT_SERVICE
 */
DECL_STATUS(CAPI_STAT_SERVICE)
#define CAPI_STAT_SERVICE    ((CAPIStatus) 0x2 << 19)

/**
 * API class status
 * @ref CSDK_STAT_API
 */
DECL_STATUS(CAPI_STAT_API)
#define CAPI_STAT_API        ((CAPIStatus) 0x3 << 19)

/**
 * Security class status
 * @ref CSDK_STAT_SECUR
 */
DECL_STATUS(CAPI_STAT_SECUR)
#define CAPI_STAT_SECUR      ((CAPIStatus) 0x4 << 19)

/**
 * Library class status
 * @ref CSDK_STAT_LIBRARY
 */
DECL_STATUS(CAPI_STAT_LIBRARY)
#define CAPI_STAT_LIBRARY    ((CAPIStatus) 0x5 << 19)

/**
 * Configuration class status
 * @ref CSDK_STAT_CONFIG
 */
DECL_STATUS(CAPI_STAT_CONFIG)
#define CAPI_STAT_CONFIG    ((CAPIStatus) 0x6 << 19)

/* field 3 */

/**
 * Information about iCalendar data
 * @ref CSDK_STAT_DATA_ICAL
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL)
#define CAPI_STAT_DATA_ICAL       ((CAPIStatus) CAPI_STAT_DATA + (0x1 << 14))

/**
 * Information about MIME data
 * @ref CSDK_STAT_DATA_MIME
 */
DECL_STATUS(CAPI_STAT_DATA_MIME)
#define CAPI_STAT_DATA_MIME       ((CAPIStatus) CAPI_STAT_DATA + (0x2 << 14))

/**
 * Information about a date
 * @ref CSDK_STAT_DATA_DATE
 */
DECL_STATUS(CAPI_STAT_DATA_DATE)
#define CAPI_STAT_DATA_DATE       ((CAPIStatus) CAPI_STAT_DATA + (0x3 << 14))

/**
 * Information about a userid
 * @ref CSDK_STAT_DATA_USERID
 */
DECL_STATUS(CAPI_STAT_DATA_USERID)
#define CAPI_STAT_DATA_USERID     ((CAPIStatus) CAPI_STAT_DATA + (0x4 << 14))

/**
 * Information about a hostname
 * @ref CSDK_STAT_DATA_HOSTNAME
 */
DECL_STATUS(CAPI_STAT_DATA_HOSTNAME)
#define CAPI_STAT_DATA_HOSTNAME   ((CAPIStatus) CAPI_STAT_DATA + (0x5 << 14))

/**
 * Information about a UID
 * @ref CSDK_STAT_DATA_UID
 */
DECL_STATUS(CAPI_STAT_DATA_UID)
#define CAPI_STAT_DATA_UID        ((CAPIStatus) CAPI_STAT_DATA + (0x6 << 14))

/**
 * Information about the encoding of supplied data
 * @ref CSDK_STAT_DATA_ENCODING
 */
DECL_STATUS(CAPI_STAT_DATA_ENCODING)
#define CAPI_STAT_DATA_ENCODING   ((CAPIStatus) CAPI_STAT_DATA + (0x7 << 14))

/**
 * Information about the supplied cookie
 * @ref CSDK_STAT_DATA_COOKIE
 */
DECL_STATUS(CAPI_STAT_DATA_COOKIE)
#define CAPI_STAT_DATA_COOKIE     ((CAPIStatus) CAPI_STAT_DATA + (0x8 << 14))

/**
 * Information about a request result
 * @ref CSDK_STAT_DATA_RRESULT
 */
DECL_STATUS(CAPI_STAT_DATA_RRESULT)
#define CAPI_STAT_DATA_RRESULT    ((CAPIStatus) CAPI_STAT_DATA + (0x9 << 14))

/**
 * Information about vCard data
 * @ref CSDK_STAT_DATA_VCARD
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD)
#define CAPI_STAT_DATA_VCARD      ((CAPIStatus) CAPI_STAT_DATA + (0xA << 14))

/**
 * Information about queries
 * @ref CSDK_STAT_DATA_QUERY
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY)
#define CAPI_STAT_DATA_QUERY      ((CAPIStatus) CAPI_STAT_DATA + (0xB << 14))

/**
 * Information about email
 * @ref CSDK_STAT_DATA_EMAIL
 */
DECL_STATUS(CAPI_STAT_DATA_EMAIL)
#define CAPI_STAT_DATA_EMAIL      ((CAPIStatus) CAPI_STAT_DATA + (0xC << 14))

/**
 * Information about data on the server
 * @ref CSDK_STAT_DATA_SERVER
 */
DECL_STATUS(CAPI_STAT_DATA_SERVER)
#define CAPI_STAT_DATA_SERVER     ((CAPIStatus) CAPI_STAT_DATA + (0xD << 14))

/**
 * Information about data for the event type is incorrect. 
 * @ref CSDK_STAT_DATA_EVENTTYPE
 */
DECL_STATUS(CAPI_STAT_DATA_EVENTTYPE)
#define CAPI_STAT_DATA_EVENTTYPE     ((CAPIStatus) CAPI_STAT_DATA + (0xE << 14))

/**
 * There was a problem with system memory services
 * @ref CSDK_STAT_SERVICE_MEM
 */
DECL_STATUS(CAPI_STAT_SERVICE_MEM)
#define CAPI_STAT_SERVICE_MEM     ((CAPIStatus) CAPI_STAT_SERVICE + (0x1 << 14))

/**
 * There was a problem with system file services
 * @ref CSDK_STAT_SERVICE_FILE
 */
DECL_STATUS(CAPI_STAT_SERVICE_FILE)
#define CAPI_STAT_SERVICE_FILE    ((CAPIStatus) CAPI_STAT_SERVICE + (0x2 << 14))

/**
 * There was a problem with network services
 * @ref CSDK_STAT_SERVICE_NET
 */
DECL_STATUS(CAPI_STAT_SERVICE_NET)
#define CAPI_STAT_SERVICE_NET     ((CAPIStatus) CAPI_STAT_SERVICE + (0x3 << 14))

/**
 * There was a problem with system thread services
 * @ref CSDK_STAT_SERVICE_THREAD
 */
DECL_STATUS(CAPI_STAT_SERVICE_THREAD)
#define CAPI_STAT_SERVICE_THREAD  ((CAPIStatus) CAPI_STAT_SERVICE + (0x4 << 14))

/**
 * There was a problem with the standard library services
 * @ref CSDK_STAT_SERVICE_LIBRARY
 */
DECL_STATUS(CAPI_STAT_SERVICE_LIBRARY)
#define CAPI_STAT_SERVICE_LIBRARY ((CAPIStatus) CAPI_STAT_SERVICE + (0x5 << 14))

/**
 * There was a problem with the standard time services
 * @ref CSDK_STAT_SERVICE_TIME
 */
DECL_STATUS(CAPI_STAT_SERVICE_TIME)
#define CAPI_STAT_SERVICE_TIME    ((CAPIStatus) CAPI_STAT_SERVICE + (0x6 << 14))

/**
 * There was a problem caused by one of the ACE plugins
 * @ref CSDK_STAT_SERVICE_ACE
 */
DECL_STATUS(CAPI_STAT_SERVICE_ACE)
#define CAPI_STAT_SERVICE_ACE     ((CAPIStatus) CAPI_STAT_SERVICE + (0x7 << 14))



/**
 * Bad flags were passed
 * @ref CSDK_STAT_API_FLAGS
 */
DECL_STATUS(CAPI_STAT_API_FLAGS)
#define CAPI_STAT_API_FLAGS       ((CAPIStatus) CAPI_STAT_API + (0x1 << 14))

/**
 * A null pointer was passed
 * @ref CSDK_STAT_API_NULL
 */
DECL_STATUS(CAPI_STAT_API_NULL)
#define CAPI_STAT_API_NULL        ((CAPIStatus) CAPI_STAT_API + (0x2 << 14))

/**
 * A bad parameter was passed
 * @ref CSDK_STAT_API_BADPARAM
 */
DECL_STATUS(CAPI_STAT_API_BADPARAM)
#define CAPI_STAT_API_BADPARAM    ((CAPIStatus) CAPI_STAT_API + (0x3 << 14))

/**
 * There was a problem with a callback
 * @ref CSDK_STAT_API_CALLBACK
 */
DECL_STATUS(CAPI_STAT_API_CALLBACK)
#define CAPI_STAT_API_CALLBACK    ((CAPIStatus) CAPI_STAT_API + (0x4 << 14))

/**
 * There was a problem with a handle
 * @ref CSDK_STAT_API_HANDLE
 */
DECL_STATUS(CAPI_STAT_API_HANDLE)
#define CAPI_STAT_API_HANDLE      ((CAPIStatus) CAPI_STAT_API + (0x5 << 14))

/**
 * There was a problem with a session
 * @ref CSDK_STAT_API_SESSION
 */
DECL_STATUS(CAPI_STAT_API_SESSION)
#define CAPI_STAT_API_SESSION     ((CAPIStatus) CAPI_STAT_API + (0x6 << 14))

/**
 * There was a problem with a stream
 * @ref CSDK_STAT_API_STREAM
 */
DECL_STATUS(CAPI_STAT_API_STREAM)
#define CAPI_STAT_API_STREAM      ((CAPIStatus) CAPI_STAT_API + (0x7 << 14))

/**
 * There was a problem with the connection pool
 * @ref CSDK_STAT_API_POOL
 */
DECL_STATUS(CAPI_STAT_API_POOL)
#define CAPI_STAT_API_POOL        ((CAPIStatus) CAPI_STAT_API + (0x8 << 14))

/**
 * There was a problem with the transaction (Probably a store operation) and the data has
 * been stored partially, so the data on the server might be inconsistent with the data the
 * user was trying to store.
 * @ref CSDK_STAT_API_INCOMPLETE_TRANSACTION
 */
DECL_STATUS(CAPI_STAT_API_INCOMPLETE_TRANSACTION)
#define CAPI_STAT_API_INCOMPLETE_TRANSACTION        ((CAPIStatus) CAPI_STAT_API + (0x9 << 14))

/**
 * There was a security error on logon
 * @ref CSDK_STAT_SECUR_LOGON
 */
DECL_STATUS(CAPI_STAT_SECUR_LOGON)
#define CAPI_STAT_SECUR_LOGON     ((CAPIStatus) CAPI_STAT_SECUR +(0x1 << 14))

/**
 * There was a security error on read
 * @ref CSDK_STAT_SECUR_READ
 */
DECL_STATUS(CAPI_STAT_SECUR_READ)
#define CAPI_STAT_SECUR_READ      ((CAPIStatus) CAPI_STAT_SECUR +(0x2 << 14))

/**
 * There was a security error on write
 * @ref CSDK_STAT_SECUR_WRITE
 */
DECL_STATUS(CAPI_STAT_SECUR_WRITE)
#define CAPI_STAT_SECUR_WRITE     ((CAPIStatus) CAPI_STAT_SECUR +(0x3 << 14))

/**
 * There was a security error in the server
 * @ref CSDK_STAT_SECUR_SERVER
 */
DECL_STATUS(CAPI_STAT_SECUR_SERVER)
#define CAPI_STAT_SECUR_SERVER    ((CAPIStatus) CAPI_STAT_SECUR +(0x4 << 14))


/**
 * User doesn't have sufficient rights to perform the operation
 * @ref CSDK_STAT_SECUR_INSUFFICIENTRIGHTS
 */
DECL_STATUS(CAPI_STAT_SECUR_INSUFFICIENTRIGHTS)
#define CAPI_STAT_SECUR_INSUFFICIENTRIGHTS    ((CAPIStatus) CAPI_STAT_SECUR +(0x5 << 14))


/**
 * An internal error occured in the library
 * @ref CSDK_STAT_LIBRARY_INTERNAL
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL)
#define CAPI_STAT_LIBRARY_INTERNAL       ((CAPIStatus) (CAPI_STAT_LIBRARY + (0x1 << 14)))

/**
 * The feature is not fully implemented
 * @ref CSDK_STAT_LIBRARY_IMPLEMENTATION
 */
DECL_STATUS(CAPI_STAT_LIBRARY_IMPLEMENTATION)
#define CAPI_STAT_LIBRARY_IMPLEMENTATION ((CAPIStatus) (CAPI_STAT_LIBRARY + (0x2 << 14)))

/**
 * A limitation of or occurence on the server
 * @ref CSDK_STAT_LIBRARY_SERVER
 */
DECL_STATUS(CAPI_STAT_LIBRARY_SERVER)
#define CAPI_STAT_LIBRARY_SERVER         ((CAPIStatus) (CAPI_STAT_LIBRARY + (0x3 << 14)))


/**
 * Failed to open the configuration file passed to CSK_SetConfigFile
 * @ref CSDK_STAT_CONFIG_CANNOT_OPEN
 */
DECL_STATUS(CAPI_STAT_CONFIG_CANNOT_OPEN)
#define CAPI_STAT_CONFIG_CANNOT_OPEN    ((CAPIStatus) (CAPI_STAT_CONFIG + (0x1 << 14)))

/**
 * Failed to open the tmpDirectoyPath specified in the configuration
 * @ref CSDK_STAT_CONFIG_CANNOT_OPEN_TMPDIRECTORYPATH
 */
DECL_STATUS(CAPI_STAT_CONFIG_CANNOT_OPEN_TMPDIRECTORYPATH)
#define CAPI_STAT_CONFIG_CANNOT_OPEN_TMPDIRECTORYPATH ((CAPIStatus) (CAPI_STAT_CONFIG + (0x2 << 14)))

/* field 4 */
/**
 * The provided data was not iCalendar data
 * @ref CSDK_STAT_DATA_ICAL_NONE
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_NONE)
#define CAPI_STAT_DATA_ICAL_NONE          ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x1 << 8)))

/**
 * One of the iCal data lines was too long, breaching the iCalendar spec (RFC 2445)
 * @ref CSDK_STAT_DATA_ICAL_LINEOVERFLOW
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_LINEOVERFLOW)
#define CAPI_STAT_DATA_ICAL_LINEOVERFLOW  ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x2 << 8)))

/**
 * There was a problem in the line folding
 * @ref CSDK_STAT_DATA_ICAL_FOLDING
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_FOLDING)
#define CAPI_STAT_DATA_ICAL_FOLDING       ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x3 << 8)))

/**
 * A problem with this particular iCalendar implementation
 * @ref CSDK_STAT_DATA_ICAL_IMPLEMENT
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_IMPLEMENT)
#define CAPI_STAT_DATA_ICAL_IMPLEMENT     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x4 << 8)))

/**
 * There was an overflow when parsing the iCalendar data. This is caused by an internal limitation of the iCalendar library, and not not by a breach of the spec
 * @ref CSDK_STAT_DATA_ICAL_OVERFLOW
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_OVERFLOW)
#define CAPI_STAT_DATA_ICAL_OVERFLOW      ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x5 << 8)))

/**
 * An expected or required component was missing
 * @ref CSDK_STAT_DATA_ICAL_COMPMISSING
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_COMPMISSING)
#define CAPI_STAT_DATA_ICAL_COMPMISSING   ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x6 << 8)))

/**
 * An extra component was encountered. Either multiple specifications of a component which should only appear once, or a component which should not appear
 * @ref CSDK_STAT_DATA_ICAL_COMPEXTRA
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_COMPEXTRA)
#define CAPI_STAT_DATA_ICAL_COMPEXTRA     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x7 << 8)))

/**
 * There was a problem with a component name
 * @ref CSDK_STAT_DATA_ICAL_COMPNAME
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_COMPNAME)
#define CAPI_STAT_DATA_ICAL_COMPNAME      ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x8 << 8)))

/**
 * There was a problem with what a component contained
 * @ref CSDK_STAT_DATA_ICAL_COMPVALUE
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_COMPVALUE)
#define CAPI_STAT_DATA_ICAL_COMPVALUE     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x9 << 8)))

/**
 * An expected or required property was missing
 * @ref CSDK_STAT_DATA_ICAL_PROPMISSING
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_PROPMISSING)
#define CAPI_STAT_DATA_ICAL_PROPMISSING   ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0xA << 8)))

/**
 * An extra property was encountered. Either multiple specifications of a property which should only appear once, or a property which should not appear
 * @ref CSDK_STAT_DATA_ICAL_PROPEXTRA
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_PROPEXTRA)
#define CAPI_STAT_DATA_ICAL_PROPEXTRA     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0xB << 8)))

/**
 * There was a problem with a property value
 * @ref CSDK_STAT_DATA_ICAL_PROPVALUE
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_PROPVALUE)
#define CAPI_STAT_DATA_ICAL_PROPVALUE     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0xC << 8)))

/**
 * There was a problem with a property name
 * @ref CSDK_STAT_DATA_ICAL_PROPNAME
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_PROPNAME)
#define CAPI_STAT_DATA_ICAL_PROPNAME      ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0xD << 8)))

/**
 * An expected or required parameter was missing
 * @ref CSDK_STAT_DATA_ICAL_PARAMMISSING
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_PARAMMISSING)
#define CAPI_STAT_DATA_ICAL_PARAMMISSING  ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0xE << 8)))

/**
 * An extra parameter was encountered. Either multiple specifications of a parameter which should only appear once, or a parameter which should not appear
 * @ref CSDK_STAT_DATA_ICAL_PARAMEXTRA
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_PARAMEXTRA)
#define CAPI_STAT_DATA_ICAL_PARAMEXTRA    ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0xF << 8)))

/**
 * There was a problem with a parameter value
 * @ref CSDK_STAT_DATA_ICAL_PARAMVALUE
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_PARAMVALUE)
#define CAPI_STAT_DATA_ICAL_PARAMVALUE    ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x10 << 8)))

/**
 * There was a problem with a parameter name
 * @ref CSDK_STAT_DATA_ICAL_PARAMNAME
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_PARAMNAME)
#define CAPI_STAT_DATA_ICAL_PARAMNAME     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x11 << 8)))

/**
 * There was a problem with the recurrence specification. The rules laid out in the description of CAPI_StoreEvent were breached
 * @ref CSDK_STAT_DATA_ICAL_RECURMODE
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_RECURMODE)
#define CAPI_STAT_DATA_ICAL_RECURMODE     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x12 << 8)))

/**
 * An attempt was made to store a calendar event without any ATTENDEE properties.  This is only supported with the flag CSDK_FLAG_STORE_INVITE_SELF
 * @ref CSDK_STAT_DATA_ICAL_NOATTENDEES
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_NOATTENDEES)
#define CAPI_STAT_DATA_ICAL_NOATTENDEES     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x13 << 8)))

/**
 * An attempt was made to modify the recurrence rule for a calendar entry.  This is not supported.
 * @ref CSDK_STAT_DATA_ICAL_CANTMODIFYRRULE
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_CANTMODIFYRRULE)
#define CAPI_STAT_DATA_ICAL_CANTMODIFYRRULE     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x14 << 8)))

/**
 * Multiple VEVENTs were supplied with the same UID, and at least two of them did not have a RECURRENCE-ID property.
 * @ref CSDK_STAT_DATA_ICAL_MISSINGRECURID
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_MISSINGRECURID)
#define CAPI_STAT_DATA_ICAL_MISSINGRECURID     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x15 << 8)))

/**
 * One or more VEVENTs were missing UID properties and an attemp was made to do something other than a CREATE.
 * @ref CSDK_STAT_DATA_ICAL_MISSING_UID
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_MISSING_UID)
#define CAPI_STAT_DATA_ICAL_MISSING_UID     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x16 << 8)))

/**
 * An attempt was made to reply to a calendar event which the user is not attending.  
 * @ref CSDK_STAT_DATA_ICAL_NOTANATTENDEE
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_NOTANATTENDEE)
#define CAPI_STAT_DATA_ICAL_NOTANATTENDEE     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x17 << 8)))

/**
 * The iCalendar data given did not contain a DTSTART property, required to perform the requested operation
 * @ref CSDK_STAT_DATA_ICAL_MISSING_DTSTART
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_MISSING_DTSTART)
#define CAPI_STAT_DATA_ICAL_MISSING_DTSTART     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x18 << 8)))

/**
 * The iCalendar data contained unrecognized iCalendar tokens.
 * @ref CSDK_STAT_DATA_ICAL_UNKNOWNDATA
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_UNKNOWNDATA)
#define CAPI_STAT_DATA_ICAL_UNKNOWNDATA     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x19 << 8)))

/**
 * The attachment file uri was invalid.
 * @ref CSDK_STAT_DATA_ICAL_ATTACH_INVALID_FILE_URI
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_ATTACH_INVALID_FILE_URI) 
#define CAPI_STAT_DATA_ICAL_ATTACH_INVALID_FILE_URI     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x20 << 8)))

/**
 * The operation encountered an error only with the attachment.
 * @ref CSDK_STAT_DATA_ICAL_ATTACH
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_ATTACH) 
#define CAPI_STAT_DATA_ICAL_ATTACH     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x21 << 8)))

/**
 * An Oracle iCalendar extension was used incorrectly.
 * @ref CSDK_STAT_DATA_ICAL_INVALIDEXTENSIONDATA
 */
DECL_STATUS(CAPI_STAT_DATA_ICAL_INVALIDEXTENSIONDATA) 
#define CAPI_STAT_DATA_ICAL_INVALIDEXTENSIONDATA     ((CAPIStatus) (CAPI_STAT_DATA_ICAL + (0x22 << 8)))





/**
 * No MIME data was found
 * @ref CSDK_STAT_DATA_MIME_NONE
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_NONE)
#define CAPI_STAT_DATA_MIME_NONE        ((CAPIStatus) (CAPI_STAT_DATA_MIME + (0x1 << 8)))

/**
 * No MIME parts were found whose headers indicated that they contain iCalendar data
 * @ref CSDK_STAT_DATA_MIME_NOICAL
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_NOICAL)
#define CAPI_STAT_DATA_MIME_NOICAL      ((CAPIStatus) (CAPI_STAT_DATA_MIME + (0x2 << 8)))

/**
 * One of the header lines was too long
 * @ref CSDK_STAT_DATA_MIME_LENGTH
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_LENGTH)
#define CAPI_STAT_DATA_MIME_LENGTH      ((CAPIStatus) (CAPI_STAT_DATA_MIME + (0x3 << 8)))

/**
 * A header could not be parsed
 * @ref CSDK_STAT_DATA_MIME_HEADER
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_HEADER)
#define CAPI_STAT_DATA_MIME_HEADER      ((CAPIStatus) (CAPI_STAT_DATA_MIME + (0x4 << 8)))

/**
 * A comment could not be parsed
 * @ref CSDK_STAT_DATA_MIME_COMMENT
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_COMMENT)
#define CAPI_STAT_DATA_MIME_COMMENT     ((CAPIStatus) (CAPI_STAT_DATA_MIME + (0x5 << 8)))

/**
 * The encoding specified in the MIME object is not supported
 * @ref CSDK_STAT_DATA_MIME_ENCODING
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_ENCODING)
#define CAPI_STAT_DATA_MIME_ENCODING    ((CAPIStatus) (CAPI_STAT_DATA_MIME + (0x6 << 8)))

/**
 * A restriction specific to this MIME implementation was breached
 * @ref CSDK_STAT_DATA_MIME_IMPLEMENT
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_IMPLEMENT)
#define CAPI_STAT_DATA_MIME_IMPLEMENT   ((CAPIStatus) (CAPI_STAT_DATA_MIME + (0x7 << 8)))

/**
 * An overflow occurred while reading MIME data.
 * @ref CSDK_STAT_DATA_MIME_OVERFLOW
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_OVERFLOW)
#define CAPI_STAT_DATA_MIME_OVERFLOW    ((CAPIStatus) (CAPI_STAT_DATA_MIME + (0x8 << 8)))

/**
 * An unsupported character set was specified in a MIME header.
 * @ref CSDK_STAT_DATA_MIME_CHARSET
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_CHARSET)
#define CAPI_STAT_DATA_MIME_CHARSET     ((CAPIStatus) (CAPI_STAT_DATA_MIME + (0xA << 8)))



/**
 * The date range is incorrect
 * @ref CSDK_STAT_DATA_DATE_RANGE
 */
DECL_STATUS(CAPI_STAT_DATA_DATE_RANGE)
#define CAPI_STAT_DATA_DATE_RANGE       ((CAPIStatus) (CAPI_STAT_DATA_DATE + (0x1 << 8)))

/**
 * The format of the date data is incorrect
 * @ref CSDK_STAT_DATA_DATE_FORMAT
 */
DECL_STATUS(CAPI_STAT_DATA_DATE_FORMAT)
#define CAPI_STAT_DATA_DATE_FORMAT      ((CAPIStatus) (CAPI_STAT_DATA_DATE + (0x2 << 8)))

/**
 * A specified date is out of the range supported by this implementation
 * @ref CSDK_STAT_DATA_DATE_OUTOFRANGE
 */
DECL_STATUS(CAPI_STAT_DATA_DATE_OUTOFRANGE)
#define CAPI_STAT_DATA_DATE_OUTOFRANGE  ((CAPIStatus) (CAPI_STAT_DATA_DATE + (0x3 << 8)))

/**
 * A specified date is invalid (e.g. Feb 30th)
 * @ref CSDK_STAT_DATA_DATE_INVALID
 */
DECL_STATUS(CAPI_STAT_DATA_DATE_INVALID)
#define CAPI_STAT_DATA_DATE_INVALID  ((CAPIStatus) (CAPI_STAT_DATA_DATE + (0x4 << 8)))

/**
 * A UTC DTSTART (and/or DTEND) was specified for a recurring event.  Must be floating or local.
 * @ref CSDK_STAT_DATA_DATE_NOT_LOCAL
 */
DECL_STATUS(CAPI_STAT_DATA_DATE_NOT_LOCAL)
#define CAPI_STAT_DATA_DATE_NOT_LOCAL  ((CAPIStatus) (CAPI_STAT_DATA_DATE + (0x5 << 8)))

/**
 * The format of the UserId string was wrong
 * @ref CSDK_STAT_DATA_USERID_FORMAT
 */
DECL_STATUS(CAPI_STAT_DATA_USERID_FORMAT)
#define CAPI_STAT_DATA_USERID_FORMAT    ((CAPIStatus) (CAPI_STAT_DATA_USERID + (0x1 << 8)))

/**
 * There was a problem with the Id part of the UserId string
 * @ref CSDK_STAT_DATA_USERID_ID
 */
DECL_STATUS(CAPI_STAT_DATA_USERID_ID)
#define CAPI_STAT_DATA_USERID_ID        ((CAPIStatus) (CAPI_STAT_DATA_USERID + (0x2 << 8)))

/**
 * There was a problem with the Extended part of the UserId string
 * @ref CSDK_STAT_DATA_USERID_EXT
 */
DECL_STATUS(CAPI_STAT_DATA_USERID_EXT)
#define CAPI_STAT_DATA_USERID_EXT       ((CAPIStatus) (CAPI_STAT_DATA_USERID + (0x3 << 8)))



/**
 * The format of the hostname string was wrong
 * @ref CSDK_STAT_DATA_HOSTNAME_FORMAT
 */
DECL_STATUS(CAPI_STAT_DATA_HOSTNAME_FORMAT)
#define CAPI_STAT_DATA_HOSTNAME_FORMAT  ((CAPIStatus) (CAPI_STAT_DATA_HOSTNAME + (0x1 << 8)))

/**
 * The hostname string could not be resolved to a host
 * @ref CSDK_STAT_DATA_HOSTNAME_HOST
 */
DECL_STATUS(CAPI_STAT_DATA_HOSTNAME_HOST)
#define CAPI_STAT_DATA_HOSTNAME_HOST    ((CAPIStatus) (CAPI_STAT_DATA_HOSTNAME + (0x2 << 8)))

/**
 * No server could be found on the specified host and port
 * @ref CSDK_STAT_DATA_HOSTNAME_SERVER
 */
DECL_STATUS(CAPI_STAT_DATA_HOSTNAME_SERVER)
#define CAPI_STAT_DATA_HOSTNAME_SERVER  ((CAPIStatus) (CAPI_STAT_DATA_HOSTNAME + (0x3 << 8)))



/**
 * The format of the UID string was wrong
 * @ref CSDK_STAT_DATA_UID_FORMAT
 */
DECL_STATUS(CAPI_STAT_DATA_UID_FORMAT)
#define CAPI_STAT_DATA_UID_FORMAT       ((CAPIStatus) (CAPI_STAT_DATA_UID + (0x1 << 8)))

/**
 * Data with the supplied UID could not be found
 * @ref CSDK_STAT_DATA_UID_NOTFOUND
 */
DECL_STATUS(CAPI_STAT_DATA_UID_NOTFOUND)
#define CAPI_STAT_DATA_UID_NOTFOUND     ((CAPIStatus) (CAPI_STAT_DATA_UID + (0x2 << 8)))

/**
 * The specified object could not be found
 * @ref CSDK_STAT_DATA_UID_RECURRENCE
 */
DECL_STATUS(CAPI_STAT_DATA_UID_RECURRENCE)
#define CAPI_STAT_DATA_UID_RECURRENCE   ((CAPIStatus) (CAPI_STAT_DATA_UID + (0x3 << 8)))

/**
 * An object with the specified UID already exists
 * @ref CSDK_STAT_DATA_UID_ALREADYEXISTS
 */
DECL_STATUS(CAPI_STAT_DATA_UID_ALREADYEXISTS)
#define CAPI_STAT_DATA_UID_ALREADYEXISTS   ((CAPIStatus) (CAPI_STAT_DATA_UID + (0x4 << 8)))

/**
 * Multiple objects with the specified UID exist
 * @ref CSDK_STAT_DATA_UID_MULTIPLEMATCHES
 */
DECL_STATUS(CAPI_STAT_DATA_UID_MULTIPLEMATCHES)
#define CAPI_STAT_DATA_UID_MULTIPLEMATCHES   ((CAPIStatus) (CAPI_STAT_DATA_UID + (0x5 << 8)))


/**
 * No more results were found in the CSDKRequestResult
 * @ref CSDK_STAT_DATA_RRESULT_EOR
 */
DECL_STATUS(CAPI_STAT_DATA_RRESULT_EOR)
#define CAPI_STAT_DATA_RRESULT_EOR   ((CAPIStatus) (CAPI_STAT_DATA_RRESULT + (0x1 << 8)))


/**
 * An attempt was made to store a vCard using the mode CSDK_FLAG_STORE_CREATE but a contact with the same UID
 * already existed on the server.
 * @ref CSDK_STAT_DATA_VCARD_DUPERROR
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_DUPERROR)
#define CAPI_STAT_DATA_VCARD_DUPERROR   ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x1 << 8)))

/**
 * An expected or required property was missing
 * @ref CSDK_STAT_DATA_VCARD_PROPMISSING
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_PROPMISSING)
#define CAPI_STAT_DATA_VCARD_PROPMISSING   ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x2 << 8)))

/**
 * An extra property was encountered. Either multiple specifications of a property which should only appear once, or a property which should not appear
 * @ref CSDK_STAT_DATA_VCARD_PROPEXTRA
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_PROPEXTRA)
#define CAPI_STAT_DATA_VCARD_PROPEXTRA     ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x3 << 8)))

/**
 * There was a problem with a property value
 * @ref CSDK_STAT_DATA_VCARD_PROPVALUE
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_PROPVALUE)
#define CAPI_STAT_DATA_VCARD_PROPVALUE     ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x4 << 8)))

/**
 * There was a problem with a component name
 * @ref CSDK_STAT_DATA_VCARD_COMPNAME
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_COMPNAME)
#define CAPI_STAT_DATA_VCARD_COMPNAME      ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x5 << 8)))

/**
 * There was a problem with a property name
 * @ref CSDK_STAT_DATA_VCARD_PROPNAME
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_PROPNAME)
#define CAPI_STAT_DATA_VCARD_PROPNAME      ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x6 << 8)))

/**
 * An expected or required parameter was missing
 * @ref CSDK_STAT_DATA_VCARD_PARAMMISSING
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_PARAMMISSING)
#define CAPI_STAT_DATA_VCARD_PARAMMISSING  ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x7 << 8)))

/**
 * An extra parameter was encountered. Either multiple specifications of a parameter which should only appear once, or a parameter which should not appear
 * @ref CSDK_STAT_DATA_VCARD_PARAMEXTRA
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_PARAMEXTRA)
#define CAPI_STAT_DATA_VCARD_PARAMEXTRA    ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x8 << 8)))

/**
 * There was a problem with a parameter value
 * @ref CSDK_STAT_DATA_VCARD_PARAMVALUE
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_PARAMVALUE)
#define CAPI_STAT_DATA_VCARD_PARAMVALUE    ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x9 << 8)))

/**
 * There was a problem with a parameter name
 * @ref CSDK_STAT_DATA_VCARD_PARAMNAME
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_PARAMNAME)
#define CAPI_STAT_DATA_VCARD_PARAMNAME     ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x10 << 8)))

/**
 * A vCard with an unrecognized VERSION was encountered
 * @ref CSDK_STAT_DATA_VCARD_VERSION_UNSUPPORTED
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_VERSION_UNSUPPORTED)
#define CAPI_STAT_DATA_VCARD_VERSION_UNSUPPORTED     ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x11 << 8)))

/**
 * There was a problem with a property witch doen't respect a server
 * rule example daystart = 9 am and we try to store dayend = 8 am
 * Error since dayEnd < daystart
 * @ref CSDK_STAT_DATA_VCARD_PROPVALUE_VIOLATED_SERVERRULE
 */
DECL_STATUS(CAPI_STAT_DATA_VCARD_PROPVALUE_VIOLATED_SERVERRULE)
#define CAPI_STAT_DATA_VCARD_PROPVALUE_VIOLATED_SERVERRULE     ((CAPIStatus) (CAPI_STAT_DATA_VCARD + (0x12 << 8)))

/**
 * A NULL CSDKQuery object was passed into a API function
 * @ref CSDK_STAT_DATA_QUERY_NULL
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY_NULL)
#define CAPI_STAT_DATA_QUERY_NULL   ((CAPIStatus) (CAPI_STAT_DATA_QUERY + (0x1 << 8)))

/**
 * A NULL CSDKCondition object was passed into a API function
 * @ref CSDK_STAT_DATA_QUERY_CONDITION_NULL
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY_CONDITION_NULL)
#define CAPI_STAT_DATA_QUERY_CONDITION_NULL   ((CAPIStatus) (CAPI_STAT_DATA_QUERY + (0x2 << 8)))

/**
 * A CSDKCondition contained a NULL property
 * @ref CSDK_STAT_DATA_QUERY_CONDITION_PROPERTY_NULL
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY_CONDITION_PROPERTY_NULL)
#define CAPI_STAT_DATA_QUERY_CONDITION_PROPERTY_NULL   ((CAPIStatus) (CAPI_STAT_DATA_QUERY + (0x3 << 8)))

/**
 * A CSDKCondition contained a NULL value
 * @ref CSDK_STAT_DATA_QUERY_CONDITION_VALUE_NULL
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY_CONDITION_VALUE_NULL)
#define CAPI_STAT_DATA_QUERY_CONDITION_VALUE_NULL   ((CAPIStatus) (CAPI_STAT_DATA_QUERY + (0x4 << 8)))

/**
 * A CSDKCondition contained an unknown operator
 * @ref CSDK_STAT_DATA_QUERY_CONDITION_UNKNOWN_OPERATOR
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY_CONDITION_UNKNOWN_OPERATOR)
#define CAPI_STAT_DATA_QUERY_CONDITION_UNKNOWN_OPERATOR   ((CAPIStatus) (CAPI_STAT_DATA_QUERY + (0x5 << 8)))

/**
 * A CSDKCondition contained an operator which was not legal for the query being performed
 * @ref CSDK_STAT_DATA_QUERY_CONDITION_ILLEGAL_OPERATOR
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY_CONDITION_ILLEGAL_OPERATOR)
#define CAPI_STAT_DATA_QUERY_CONDITION_ILLEGAL_OPERATOR   ((CAPIStatus) (CAPI_STAT_DATA_QUERY + (0x6 << 8)))

/**
 * An illegal operator was passed to CSDK_AddConditionToQuery.  (Only CSDK_LOP_OR and CSDK_LOP_AND are supported.)
 * @ref CSDK_STAT_DATA_QUERY_ILLEGAL_OPERATOR
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY_ILLEGAL_OPERATOR)
#define CAPI_STAT_DATA_QUERY_ILLEGAL_OPERATOR   ((CAPIStatus) (CAPI_STAT_DATA_QUERY + (0x7 << 8)))

/**
 * A CSDKCondition contained a property name which was longer than expected.
 * @ref CSDK_STAT_DATA_QUERY_CONDITION_PROPERTY_TOO_LONG
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY_CONDITION_PROPERTY_TOO_LONG)
#define CAPI_STAT_DATA_QUERY_CONDITION_PROPERTY_TOO_LONG   ((CAPIStatus) (CAPI_STAT_DATA_QUERY + (0x8 << 8)))

/**
 * A CSDKCondition contained a property name which was longer than expected.
 * @ref CSDK_STAT_DATA_QUERY_CONDITION_VALUE_TOO_LONG
 */
DECL_STATUS(CAPI_STAT_DATA_QUERY_CONDITION_VALUE_TOO_LONG)
#define CAPI_STAT_DATA_QUERY_CONDITION_VALUE_TOO_LONG   ((CAPIStatus) (CAPI_STAT_DATA_QUERY + (0x9 << 8)))


/**
 * No email address is set on the server for 1 or more users/resources
 * @ref CSDK_STAT_DATA_EMAIL_NOTSET
 */
DECL_STATUS(CAPI_STAT_DATA_EMAIL_NOTSET)
#define CAPI_STAT_DATA_EMAIL_NOTSET   ((CAPIStatus) (CAPI_STAT_DATA_EMAIL + (0x1 << 8)))


/**
 * Could not allocate memory
 * @ref CSDK_STAT_SERVICE_MEM_ALLOC
 */
DECL_STATUS(CAPI_STAT_SERVICE_MEM_ALLOC)
#define CAPI_STAT_SERVICE_MEM_ALLOC     ((CAPIStatus) (CAPI_STAT_SERVICE_MEM + (0x1 << 8)))


/**
 * There was a problem opening a file
 * @ref CSDK_STAT_SERVICE_FILE_OPEN
 */
DECL_STATUS(CAPI_STAT_SERVICE_FILE_OPEN)
#define CAPI_STAT_SERVICE_FILE_OPEN     ((CAPIStatus) (CAPI_STAT_SERVICE_FILE + (0x1 << 8)))

/**
 * There was a problem closing a file
 * @ref CSDK_STAT_SERVICE_FILE_CLOSE
 */
DECL_STATUS(CAPI_STAT_SERVICE_FILE_CLOSE)
#define CAPI_STAT_SERVICE_FILE_CLOSE    ((CAPIStatus) (CAPI_STAT_SERVICE_FILE + (0x2 << 8)))

/**
 * There was a problem reading from a file
 * @ref CSDK_STAT_SERVICE_FILE_READ
 */
DECL_STATUS(CAPI_STAT_SERVICE_FILE_READ)
#define CAPI_STAT_SERVICE_FILE_READ     ((CAPIStatus) (CAPI_STAT_SERVICE_FILE + (0x3 << 8)))

/**
 * There was a problem writing to a file
 * @ref CSDK_STAT_SERVICE_FILE_WRITE
 */
DECL_STATUS(CAPI_STAT_SERVICE_FILE_WRITE)
#define CAPI_STAT_SERVICE_FILE_WRITE    ((CAPIStatus) (CAPI_STAT_SERVICE_FILE + (0x4 << 8)))

/**
 * There was a problem allocating a temporary file
 * @ref CSDK_STAT_SERVICE_FILE_TEMP
 */
DECL_STATUS(CAPI_STAT_SERVICE_FILE_TEMP)
#define CAPI_STAT_SERVICE_FILE_TEMP     ((CAPIStatus) (CAPI_STAT_SERVICE_FILE + (0x5 << 8)))

/**
 * There was a problem deleting a file
 * @ref CSDK_STAT_SERVICE_FILE_DELETE
 */
DECL_STATUS(CAPI_STAT_SERVICE_FILE_DELETE)
#define CAPI_STAT_SERVICE_FILE_DELETE   ((CAPIStatus) (CAPI_STAT_SERVICE_FILE + (0x6 << 8)))

/**
 * There was a problem with the read or write mode for a file
 * @ref CSDK_STAT_SERVICE_FILE_MODE
 */
DECL_STATUS(CAPI_STAT_SERVICE_FILE_MODE)
#define CAPI_STAT_SERVICE_FILE_MODE     ((CAPIStatus) (CAPI_STAT_SERVICE_FILE + (0x7 << 8)))


/**
 * Timeout while waiting for network services
 * @ref CSDK_STAT_SERVICE_NET_TIMEOUT
 */
DECL_STATUS(CAPI_STAT_SERVICE_NET_TIMEOUT)
#define CAPI_STAT_SERVICE_NET_TIMEOUT   ((CAPIStatus) (CAPI_STAT_SERVICE_NET + (0x1 << 8)))


/**
 * GMTime could not be obtained
 * @ref CSDK_STAT_SERVICE_TIME_GMTIME
 */
DECL_STATUS(CAPI_STAT_SERVICE_TIME_GMTIME)
#define CAPI_STAT_SERVICE_TIME_GMTIME   ((CAPIStatus) (CAPI_STAT_SERVICE_TIME + (0x1 << 8)))


/**
 * Requested ACE option not supported
 * @ref CSDK_STAT_SERVICE_ACE_SUPPORT
 */
DECL_STATUS(CAPI_STAT_SERVICE_ACE_SUPPORT)
#define CAPI_STAT_SERVICE_ACE_SUPPORT   ((CAPIStatus) (CAPI_STAT_SERVICE_ACE + (0x1 << 8)))


/**
 * Required ACE plugin could not be loaded
 * @ref CSDK_STAT_SERVICE_ACE_LOAD
 */
DECL_STATUS(CAPI_STAT_SERVICE_ACE_LOAD)
#define CAPI_STAT_SERVICE_ACE_LOAD      ((CAPIStatus) (CAPI_STAT_SERVICE_ACE + (0x2 << 8)))
                                                    

/**
 * The callback returned an error, which is returned in bit field 5
 * @ref CSDK_STAT_API_CALLBACK_ERROR
 */
DECL_STATUS(CAPI_STAT_API_CALLBACK_ERROR)
#define CAPI_STAT_API_CALLBACK_ERROR    ((CAPIStatus) (CAPI_STAT_API_CALLBACK + (0x1 << 8)))


/**
 * The passed handle was null
 * @ref CSDK_STAT_API_HANDLE_NULL
 */
DECL_STATUS(CAPI_STAT_API_HANDLE_NULL)
#define CAPI_STAT_API_HANDLE_NULL       ((CAPIStatus) (CAPI_STAT_API_HANDLE + (0x1 << 8)))

/**
 * The passed handle was corrupt
 * @ref CSDK_STAT_API_HANDLE_BAD
 */
DECL_STATUS(CAPI_STAT_API_HANDLE_BAD)
#define CAPI_STAT_API_HANDLE_BAD        ((CAPIStatus) (CAPI_STAT_API_HANDLE + (0x2 << 8)))

/**
 * The passed handle was not null
 * @ref CSDK_STAT_API_HANDLE_NOTNULL
 */
DECL_STATUS(CAPI_STAT_API_HANDLE_NOTNULL)
#define CAPI_STAT_API_HANDLE_NOTNULL    ((CAPIStatus) (CAPI_STAT_API_HANDLE + (0x3 << 8)))


/**
 * The passed session was null
 * @ref CSDK_STAT_API_SESSION_NULL
 */
DECL_STATUS(CAPI_STAT_API_SESSION_NULL)
#define CAPI_STAT_API_SESSION_NULL      ((CAPIStatus) (CAPI_STAT_API_SESSION + (0x1 << 8)))

/**
 * The passed session was corrupt
 * @ref CSDK_STAT_API_SESSION_BAD
 */
DECL_STATUS(CAPI_STAT_API_SESSION_BAD)
#define CAPI_STAT_API_SESSION_BAD       ((CAPIStatus) (CAPI_STAT_API_SESSION + (0x2 << 8)))

/**
 * The passed session was not null
 * @ref CSDK_STAT_API_SESSION_NOTNULL
 */
DECL_STATUS(CAPI_STAT_API_SESSION_NOTNULL)
#define CAPI_STAT_API_SESSION_NOTNULL   ((CAPIStatus) (CAPI_STAT_API_SESSION + (0x3 << 8)))


/**
 * The passed stream was null
 * @ref CSDK_STAT_API_STREAM_NULL
 */
DECL_STATUS(CAPI_STAT_API_STREAM_NULL)
#define CAPI_STAT_API_STREAM_NULL       ((CAPIStatus) (CAPI_STAT_API_STREAM + (0x1 << 8)))

/**
 * The passed stream was corrupt
 * @ref CSDK_STAT_API_STREAM_BAD
 */
DECL_STATUS(CAPI_STAT_API_STREAM_BAD)
#define CAPI_STAT_API_STREAM_BAD        ((CAPIStatus) (CAPI_STAT_API_STREAM + (0x2 << 8)))

/**
 * The passed stream was not null
 * @ref CSDK_STAT_API_STREAM_NOTNULL
 */
DECL_STATUS(CAPI_STAT_API_STREAM_NOTNULL)
#define CAPI_STAT_API_STREAM_NOTNULL    ((CAPIStatus) (CAPI_STAT_API_STREAM + (0x3 << 8)))


/**
 * The connection pool was not initialized
 * @ref CSDK_STAT_API_POOL_NOTINITIALIZED
 */
DECL_STATUS(CAPI_STAT_API_POOL_NOTINITIALIZED)
#define CAPI_STAT_API_POOL_NOTINITIALIZED ((CAPIStatus) (CAPI_STAT_API_POOL + (0x1 << 8)))

/**
 * The connection pool couldn't obtain a lock
 * @ref CSDK_STAT_API_POOL_LOCKFAILED
 */
DECL_STATUS(CAPI_STAT_API_POOL_LOCKFAILED)
#define CAPI_STAT_API_POOL_LOCKFAILED     ((CAPIStatus) (CAPI_STAT_API_POOL + (0x2 << 8)))

/**
 * The connection pool has no appropriate connections available
 * @ref CSDK_STAT_API_POOL_NOCONNECTIONS
 */
DECL_STATUS(CAPI_STAT_API_POOL_NOCONNECTIONS)
#define CAPI_STAT_API_POOL_NOCONNECTIONS     ((CAPIStatus) (CAPI_STAT_API_POOL + (0x3 << 8)))


/**
 * Logon authentication failed
 * @ref CSDK_STAT_SECUR_LOGON_AUTH
 */
DECL_STATUS(CAPI_STAT_SECUR_LOGON_AUTH)
#define CAPI_STAT_SECUR_LOGON_AUTH      ((CAPIStatus) (CAPI_STAT_SECUR_LOGON + (0x1 << 8)))

/**
 * The specified account is locked
 * @ref CSDK_STAT_SECUR_LOGON_LOCKED
 */
DECL_STATUS(CAPI_STAT_SECUR_LOGON_LOCKED)
#define CAPI_STAT_SECUR_LOGON_LOCKED    ((CAPIStatus) (CAPI_STAT_SECUR_LOGON + (0x2 << 8)))


/**
 * There was a security error reading properties
 * @ref CSDK_STAT_SECUR_READ_PROPS
 */
DECL_STATUS(CAPI_STAT_SECUR_READ_PROPS)
#define CAPI_STAT_SECUR_READ_PROPS      ((CAPIStatus) (CAPI_STAT_SECUR_READ + (0x1 << 8)))

/**
 * There was a security error reading alarm data
 * @ref CSDK_STAT_SECUR_READ_ALARM
 */
DECL_STATUS(CAPI_STAT_SECUR_READ_ALARM)
#define CAPI_STAT_SECUR_READ_ALARM      ((CAPIStatus) (CAPI_STAT_SECUR_READ + (0x2 << 8)))


/**
 * There was a security error writing to an agenda
 * @ref CSDK_STAT_SECUR_WRITE_AGENDA
 */
DECL_STATUS(CAPI_STAT_SECUR_WRITE_AGENDA)
#define CAPI_STAT_SECUR_WRITE_AGENDA    ((CAPIStatus) (CAPI_STAT_SECUR_WRITE + (0x1 << 8)))

/**
 * There was a security error writing to an event
 * @ref CSDK_STAT_SECUR_WRITE_EVENT
 */
DECL_STATUS(CAPI_STAT_SECUR_WRITE_EVENT)
#define CAPI_STAT_SECUR_WRITE_EVENT     ((CAPIStatus) (CAPI_STAT_SECUR_WRITE + (0x2 << 8)))

/**
 * One or more attendees could not be booked.  This could be due to lack of access rights, or because the attendee is already booked.
 * @ref CSDK_STAT_SECUR_CANTBOOKATTENDEE
 */
DECL_STATUS(CAPI_STAT_SECUR_CANTBOOKATTENDEE)
#define CAPI_STAT_SECUR_CANTBOOKATTENDEE     ((CAPIStatus) (CAPI_STAT_SECUR_WRITE + (0x3 << 8)))

/**
 * There was a licensing error on the server
 * @ref CSDK_STAT_SECUR_SERVER_LICENSE
 */
DECL_STATUS(CAPI_STAT_SECUR_SERVER_LICENSE)
#define CAPI_STAT_SECUR_SERVER_LICENSE  ((CAPIStatus) (CAPI_STAT_SECUR_SERVER + (0x1 << 8)))

/**
 * The server requires a SetIdentity call on the sysop logon to perform the operation
 * @ref CSDK_STAT_SECUR_SERVER_SET_IDENTITY_SYSOP
 **/
DECL_STATUS(CAPI_STAT_SECUR_SERVER_SET_IDENTITY_SYSOP)
#define CAPI_STAT_SECUR_SERVER_SET_IDENTITY_SYSOP  ((CAPIStatus) (CAPI_STAT_SECUR_SERVER + (0x2 << 8)))

/**
 * Cannot set identity as a remote user while logged in as node sysop
 * @ref CSDK_STAT_SECUR_SERVER_SET_IDENTITY_SYSOP_REMOTE
 **/
DECL_STATUS(CAPI_STAT_SECUR_SERVER_SET_IDENTITY_SYSOP_REMOTE)
#define CAPI_STAT_SECUR_SERVER_SET_IDENTITY_SYSOP_REMOTE  ((CAPIStatus) (CAPI_STAT_SECUR_SERVER + (0x3 << 8)))

/**
 * The function has expired in this library
 * @ref CSDK_STAT_LIBRARY_INTERNAL_EXPIRY
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL_EXPIRY)
#define CAPI_STAT_LIBRARY_INTERNAL_EXPIRY    ((CAPIStatus) (CAPI_STAT_LIBRARY_INTERNAL + (0x1 << 8)))

/**
 * The library abused a protocol
 * @ref CSDK_STAT_LIBRARY_INTERNAL_PROTOCOL
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL_PROTOCOL)
#define CAPI_STAT_LIBRARY_INTERNAL_PROTOCOL  ((CAPIStatus) (CAPI_STAT_LIBRARY_INTERNAL + (0x2 << 8)))

/**
 * There was a corruption of data in the library
 * @ref CSDK_STAT_LIBRARY_INTERNAL_DATA
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL_DATA)
#define CAPI_STAT_LIBRARY_INTERNAL_DATA      ((CAPIStatus) (CAPI_STAT_LIBRARY_INTERNAL + (0x3 << 8)))

/**
 * The library miscalled a function
 * @ref CSDK_STAT_LIBRARY_INTERNAL_FUNCTION
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL_FUNCTION)
#define CAPI_STAT_LIBRARY_INTERNAL_FUNCTION  ((CAPIStatus) (CAPI_STAT_LIBRARY_INTERNAL + (0x4 << 8)))

/**
 * Something completely unexpected happened internally
 * @ref CSDK_STAT_LIBRARY_INTERNAL_COSMICRAY
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL_COSMICRAY)
#define CAPI_STAT_LIBRARY_INTERNAL_COSMICRAY ((CAPIStatus) (CAPI_STAT_LIBRARY_INTERNAL + (0x5 << 8)))

/**
 * Some internal maximum was exceeded
 * @ref CSDK_STAT_LIBRARY_INTERNAL_OVERFLOW
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL_OVERFLOW)
#define CAPI_STAT_LIBRARY_INTERNAL_OVERFLOW  ((CAPIStatus) (CAPI_STAT_LIBRARY_INTERNAL + (0x6 << 8)))

/**
 * Failed to map an error code from a dependant library.
 * @ref CSDK_STAT_LIBRARY_INTERNAL_UNKNOWN_LIBRARY_ERRCODE
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL_UNKNOWN_LIBRARY_ERRCODE)
#define CAPI_STAT_LIBRARY_INTERNAL_UNKNOWN_LIBRARY_ERRCODE ((CAPIStatus) (CAPI_STAT_LIBRARY_INTERNAL + (0x7 << 8)))

/**
 * CAPI received an unknown C++ exception
 * @ref CSDK_STAT_LIBRARY_INTERNAL_UNKNOWN_EXCEPTION
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL_UNKNOWN_EXCEPTION)
#define CAPI_STAT_LIBRARY_INTERNAL_UNKNOWN_EXCEPTION ((CAPIStatus) (CAPI_STAT_LIBRARY_INTERNAL + (0x8 << 8)))

/**
 * Invalid context for a dependant library
 * @ref CSDK_STAT_LIBRARY_INTERNAL_CONTEXT
 */
DECL_STATUS(CAPI_STAT_LIBRARY_INTERNAL_CONTEXT)
#define CAPI_STAT_LIBRARY_INTERNAL_CONTEXT ((CAPIStatus) (CAPI_STAT_LIBRARY_INTERNAL + (0x9 << 8)))

/**
 * The server does not provide support
 * @ref CSDK_STAT_LIBRARY_SERVER_SUPPORT
 */
DECL_STATUS(CAPI_STAT_LIBRARY_SERVER_SUPPORT)
#define CAPI_STAT_LIBRARY_SERVER_SUPPORT     ((CAPIStatus) (CAPI_STAT_LIBRARY_SERVER + (0x1 << 8)))

/**
 * There is some problem with user data on the server
 * @ref CSDK_STAT_LIBRARY_SERVER_USERDATA
 */
DECL_STATUS(CAPI_STAT_LIBRARY_SERVER_USERDATA)
#define CAPI_STAT_LIBRARY_SERVER_USERDATA    ((CAPIStatus) (CAPI_STAT_LIBRARY_SERVER + (0x2 << 8)))

/**
 * There was an error dealing with timezones from the calendar server
 * @ref CSDK_STAT_LIBRARY_SERVER_TIMEZONE
 */
DECL_STATUS(CAPI_STAT_LIBRARY_SERVER_TIMEZONE)
#define CAPI_STAT_LIBRARY_SERVER_TIMEZONE        ((CAPIStatus) (CAPI_STAT_LIBRARY_SERVER + (0x3 << 8)))

/**
 * The server cannot service the request right now because it is busy
 * @ref CSDK_STAT_LIBRARY_SERVER_BUSY
 */
DECL_STATUS(CAPI_STAT_LIBRARY_SERVER_BUSY)
#define CAPI_STAT_LIBRARY_SERVER_BUSY        ((CAPIStatus) (CAPI_STAT_LIBRARY_SERVER + (0x4 << 8)))

/**
 * The server is running, but unavailable for some reason, e.g. the desired node is down for maintenance
 * @ref CSDK_STAT_LIBRARY_SERVER_UNAVAILABLE
 */
DECL_STATUS(CAPI_STAT_LIBRARY_SERVER_UNAVAILABLE)
#define CAPI_STAT_LIBRARY_SERVER_UNAVAILABLE        ((CAPIStatus) (CAPI_STAT_LIBRARY_SERVER + (0x5 << 8)))


/* Field 5 */

/**
 * There was a problem with the inifile
 * @ref CSDK_STAT_DATA_USERID_EXT_INIFILE
 */
DECL_STATUS(CAPI_STAT_DATA_USERID_EXT_INIFILE)
#define CAPI_STAT_DATA_USERID_EXT_INIFILE           ((CAPIStatus)  (CAPI_STAT_DATA_USERID_EXT + 0x01))

/**
 * The format of the extended string was bad
 * @ref CSDK_STAT_DATA_USERID_EXT_FORMAT
 */
DECL_STATUS(CAPI_STAT_DATA_USERID_EXT_FORMAT)
#define CAPI_STAT_DATA_USERID_EXT_FORMAT            ((CAPIStatus)  (CAPI_STAT_DATA_USERID_EXT + 0x02))

/**
 * No users were identified by the string
 * @ref CSDK_STAT_DATA_USERID_EXT_NONE
 */
DECL_STATUS(CAPI_STAT_DATA_USERID_EXT_NONE)
#define CAPI_STAT_DATA_USERID_EXT_NONE              ((CAPIStatus)  (CAPI_STAT_DATA_USERID_EXT + 0x03))

/**
 * Multiple users were identified by the string
 * @ref CSDK_STAT_DATA_USERID_EXT_MANY
 */
DECL_STATUS(CAPI_STAT_DATA_USERID_EXT_MANY)
#define CAPI_STAT_DATA_USERID_EXT_MANY              ((CAPIStatus)  (CAPI_STAT_DATA_USERID_EXT + 0x04))

/**
 * The specified node could not be found
 * @ref CSDK_STAT_DATA_USERID_EXT_NODE
 */
DECL_STATUS(CAPI_STAT_DATA_USERID_EXT_NODE)
#define CAPI_STAT_DATA_USERID_EXT_NODE              ((CAPIStatus)  (CAPI_STAT_DATA_USERID_EXT + 0x05))

/**
 * Either userid AND X.400 were specified, or both a node and a calendar domain were specified.
 * @ref CSDK_STAT_DATA_USERID_EXT_CONFLICT
 */
DECL_STATUS(CAPI_STAT_DATA_USERID_EXT_CONFLICT)
#define CAPI_STAT_DATA_USERID_EXT_CONFLICT          ((CAPIStatus)  (CAPI_STAT_DATA_USERID_EXT + 0x06))



/**
 * The MIME object was nested too deeply
 * @ref CSDK_STAT_DATA_MIME_IMPLEMENT_NESTING
 */
DECL_STATUS(CAPI_STAT_DATA_MIME_IMPLEMENT_NESTING)
#define CAPI_STAT_DATA_MIME_IMPLEMENT_NESTING       ((CAPIStatus) (CAPI_STAT_DATA_MIME_IMPLEMENT + 0x01))

/**
 * The event has too many recurrences for the server to handle
 * @ref CSDK_STAT_DATA_SERVER_TOOMANYINSTANCES
 */
DECL_STATUS(CAPI_STAT_DATA_SERVER_TOOMANYINSTANCES)
#define CAPI_STAT_DATA_SERVER_TOOMANYINSTANCES      ((CAPIStatus) (CAPI_STAT_DATA_SERVER + (0x01 << 8)))

/**
 * The event has too many attendees for the server to handle
 * @ref CSDK_STAT_DATA_SERVER_TOOMANYATTENDEES
 */
DECL_STATUS(CAPI_STAT_DATA_SERVER_TOOMANYATTENDEES)
#define CAPI_STAT_DATA_SERVER_TOOMANYATTENDEES      ((CAPIStatus) (CAPI_STAT_DATA_SERVER + (0x02 << 8)))


/**
 * Logon is locked for Sysops
 * @ref CSDK_STAT_SECUR_LOGON_LOCKED_SYSOP
 */
DECL_STATUS(CAPI_STAT_SECUR_LOGON_LOCKED_SYSOP)
#define CAPI_STAT_SECUR_LOGON_LOCKED_SYSOP          ((CAPIStatus) (CAPI_STAT_SECUR_LOGON_LOCKED + 0x1))

/**
 * Logon is locked for resources
 * @ref CSDK_STAT_SECUR_LOGON_LOCKED_RESOURCE
 */
DECL_STATUS(CAPI_STAT_SECUR_LOGON_LOCKED_RESOURCE)
#define CAPI_STAT_SECUR_LOGON_LOCKED_RESOURCE       ((CAPIStatus) (CAPI_STAT_SECUR_LOGON_LOCKED + 0x2))


/**
 * There is no support for storing UIDs
 * @ref CSDK_STAT_LIBRARY_SERVER_SUPPORT_UID
 */
DECL_STATUS(CAPI_STAT_LIBRARY_SERVER_SUPPORT_UID)
#define CAPI_STAT_LIBRARY_SERVER_SUPPORT_UID        ((CAPIStatus) (CAPI_STAT_LIBRARY_SERVER_SUPPORT + 0x01))

/**
 * There is no support for CAPI on this server
 * @ref CSDK_STAT_LIBRARY_SERVER_SUPPORT_STANDARDS
 */
DECL_STATUS(CAPI_STAT_LIBRARY_SERVER_SUPPORT_STANDARDS)
#define CAPI_STAT_LIBRARY_SERVER_SUPPORT_STANDARDS  ((CAPIStatus) (CAPI_STAT_LIBRARY_SERVER_SUPPORT + 0x02))

/**
 * There is no support for the required character set
 * @ref CSDK_STAT_LIBRARY_SERVER_SUPPORT_CHARSET
 */
DECL_STATUS(CAPI_STAT_LIBRARY_SERVER_SUPPORT_CHARSET)
#define CAPI_STAT_LIBRARY_SERVER_SUPPORT_CHARSET    ((CAPIStatus) (CAPI_STAT_LIBRARY_SERVER_SUPPORT + 0x03))

#ifdef INTERNAL_OBSOLETED
#   include "ctobsoleted.h"
#endif

/**
 * @}
 */
#endif  /* CAPI_H */

