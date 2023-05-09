// -----------------------------------------------------------------------------------------------------------------
// NAME.......  xgpiutils.h
// PURPOSE....  Extended Generic Platform Interface - Utilities
// PROJECT....  XGPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//      Complete Function List
//==================================================================================================================
// * xgpiIniDeleteEntry
// * xgpiIniDeleteSection
// * xgpiIniGetBoolean
// * xgpiIniGetKey
// * xgpiIniGetNumeric
// * xgpiIniGetSection
// * xgpiIniGetString
// * xgpiIniScan
// * xgpiIniSetBoolean
// * xgpiIniSetFilename
// * xgpiIniSetNumeric
// * xgpiIniSetString
// *
// -----------------------------------------------------------------------------------------------------------------

#ifndef XGPIUTILS_H
#define XGPIUTILS_H

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//      	INCLUDES
//==================================================================================================================
//---- GPI Headers ----
#include "gpierrors.h"
//---- GPI Globals ----
#include "gpi_agnos_framework_globals.h"

//==================================================================================================================
//      	MACROS + DEFINITIONS
//==================================================================================================================

#ifndef INI_CALLBACK
typedef int (*INI_SCAN_CALLBACK)(const char *Section, const char *Key, const char *Value, const void *UserData);
#endif

// This is the MinIni constant for INI Workbuffer Size, default value can be overriden here
#define INI_BUFFERSIZE  512

//==================================================================================================================
//      	PRIMITIVES
//==================================================================================================================
/**
* Set active Ini file
* @param filename Name of the Ini file
*/
DLLEXPORT tGPIError xgpiIniSetFilename(
	const char *filename
);

/**
* Launch a full scan of the active Ini file using a callback method
* @note The callback need to haveto following signature:
* @code
* 	int MyCallback(const char *Section, const char *Key, const char *Value, const void *UserInfo);
* @endcode
* @param callback Pointer to the callback function
* @expression User data that will be sent to the callback
*/
DLLEXPORT tGPIError xgpiIniScan(
	INI_SCAN_CALLBACK callback,
	const void *expression
);

/**
* Find a section by index
* @param index Index of the section to search for
* @param maxLength Max length of the returned section
* @param value [out] Found section's name
* @param length [out] Length of the found section's name
*/
DLLEXPORT tGPIError xgpiIniGetSection(
	const int index,
	const int maxLength,
	char *value,
	int *length
);

/**
* Find a key inside given section
* @param index Index of the key to search for
* @param section Section inside which to search
* @param maxLength Max length of the returned key
* @param value [out] Found key's name
* @param length [out] Length of the found key's name
*/
DLLEXPORT tGPIError xgpiIniGetKey(
	const int index,
	const char *section,
	const int maxLength,
	char *value,
	int *length
);

/**
* Find the string value of a given key
* @param section Section inside which to search
* @param key Key whose value to return
* @param maxLength Max length of the returned value
* @param value [out] Key's value
* @param length [out] Length of the key'S value
*/
DLLEXPORT tGPIError xgpiIniGetString(
	const char *section,
	const char *key,
	const int maxLength,
	char *value,
	int *length
);

/**
* Find the boolean value of a given key
* @param section Section inside which to search
* @param key Key whose value to return
* @param value [out] Key's value
*/
DLLEXPORT tGPIError xgpiIniGetBoolean(
	const char *section,
	const char *key,
	int  *value
);

/**
* Find the numerical value of a given key
* @param section Section inside which to search
* @param key Key whose value to return
* @param value [out] Key's value
*/
DLLEXPORT tGPIError xgpiIniGetNumeric(
	const char *section,
	const char *key,
	int  *value
);

/**
* Delete a section of the ini file
* @param section Section to remove
*/
DLLEXPORT tGPIError xgpiIniDeleteSection(
	const char *section
);

/**
* Delete an entry of the ini file
* @param section Section containing the entry
* @param key Entry to remove
*/
DLLEXPORT tGPIError xgpiIniDeleteEntry(
	const char *section,
	const char *key
);

/**
* Sets the string value of a given key
* @param section Section containing the entry
* @param key Key to set
* @param value Key's value
*/
DLLEXPORT tGPIError xgpiIniSetString(
	const char *section,
	const char *key,
	const char *value
);

/**
* Sets the boolean value of a given key
* @param section Section containing the entry
* @param key Key to set
* @param value Key's value
*/
DLLEXPORT tGPIError xgpiIniSetBoolean(
	const char *section,
	const char *key,
	const int value
);

/**
* Sets the numerical value of a given key
* @param section Section containing the entry
* @param key Key to set
* @param value Key's value
*/
DLLEXPORT tGPIError xgpiIniSetNumeric(
	const char *section,
	const char *key,
	const int value
);

#ifdef __cplusplus
}
#endif

#endif	/* _XGPIUTILS_H */
