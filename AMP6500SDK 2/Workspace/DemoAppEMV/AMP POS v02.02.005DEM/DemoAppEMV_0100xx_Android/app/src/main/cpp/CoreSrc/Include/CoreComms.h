
#ifndef CORECOMMS_H_
#define CORECOMMS_H_

/***************************************************************************
 * 
 * Copyright (C) 2015 by APEX, Inc.
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of APEX Co. LLC.
 **************************************************************************/

/**************************************************************************
* File       	 : 		CoreComms.h
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/21/2015
**************************************************************************/

// AMP Library Includes
#include <AMPUtils.h>
#include <CoreDefines.h>

// Comm Type
#define CT_TCPIP	1
#define CT_MODEM	2
#define CT_GPRS		3

// Modem Mode
#define MM_ASYNC	1
#define MM_SYNC		2

// SSL Method
#define SSLMETHOD_SSLV23 1
#define SSLMETHOD_SSLV2	 2
#define SSLMETHOD_SSLV3	 3
#define SSLMETHOD_TLSV1	 4
#define SSLMETHOD_TLSV11 5
#define SSLMETHOD_TLSV12 6

// SIM Number
#define GPRS_SIM1	1
#define GPRS_SIM2	2

// Comms Status
#define COMMSTAT_UNKNOWN			1
#define COMMSTAT_DEV_NOT_OPEN		2
#define COMMSTAT_CONNECTING			3
#define COMMSTAT_CONNECTED			4
#define COMMSTAT_DISCONNECTING		5
#define COMMSTAT_DISCONNECTED		6
#define COMMSTAT_CONNECT_FAILED		7

// Comms Parameter
typedef struct _tagCOMMS_PARAM
{
	// Comm Type
	int iCommType;

	// TODO: Make UNION of Parameters

	// Timeouts in Seconds
	int iConnectTO;	
	int iRecvTO;

	/*
	* 	Dial Params
	*		- Used only if ucCommType is CT_MODEM
	*/

	// Host Phone Number (Should include Country Code and Area Code if needed)
	char szPhoneNum[MAX_STR_SZ+1];

	// Connection Mode, MM_SYNC or MM_ASYNC
	int iDialConnectMode;

	/*
	* 	IP Params
	*		- Used only if ucCommType is CT_TCPIP or CT_GPRS
	*/

	// Host IP
	char szHostIP[MAX_STR_SZ+1];
	int	 iHostPort;

	// SSL Parameters
	bool bSSL;
	int  iSSLMethod;
	char szSSLHostCert[MAX_STR_SZ+1];	//4 Host's ssl certificate in pem format
										//4 Optionally specify a path relative to application location in the terminal	
										
	// SSL Client Authentication. The ff params only matters if SSL=TRUE
	bool bEnableClientAuth;
	char szClientCert[MAX_STR_SZ+1];
	char szClientKey [MAX_STR_SZ+1];
	char szClientPwd [MAX_STR_SZ+1];
	
}COMMS_PARAM;

/*************************************************************************** 
 * Exported functions
 **************************************************************************/

/*
*	- Initialize the Comms Module
*	- Opens the necessary devices used by the module
*	Note: Only needed to be executed once likely during startup
*/
int CommsInitialize(void);

int CommsConnect(BOOL bIsPredial, COMMS_PARAM*	CommTxnParams);
int CommsSend(BYTE *pTxdData, int iDataLen);
int CommsRecv(BYTE *pRxdBuff, int iBuffLen);
int CommsGetStatus(void);
void CommsDisconnect(void);

/*
*	- Deinitialize the Comms Module
*	- Closes all the devices previoulsy opened by the module
*/
void CommsDeinitialize(void);

#ifndef ANDROID_POS
/*
*	- Make a connection Link to the GPRS
*	- Normally, the APN is the only param needed to make the GPRS Link up
*/
int CommsLinkGPRS(char* APN , char* UID = NULL, 	char* Pwd = NULL, char* SimPin = NULL, 
			char* DNS = NULL,	char* PhoneNumber = NULL);
#endif

#endif /* CORECOMMS_H_ */

