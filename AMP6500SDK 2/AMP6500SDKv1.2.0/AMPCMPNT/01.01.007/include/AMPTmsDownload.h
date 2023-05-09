
#ifndef AMPTMSDOWNLOAD_H_
#define AMPTMSDOWNLOAD_H_

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
* File       	 : 		AMPUtils.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/09/2015
**************************************************************************/

#include <AMPDataTypes.h>
#include <AMPReturnCodes.h>
#include <AMPDefine.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define	TMS_COMM_TYPE_GPRS       1       //  uses socket comm(gprs, cdma, lan...)
#define TMS_COMM_TYPE_CDMA       2       //  uses socket comm(gprs, cdma, lan...)
#define TMS_COMM_TYPE_PPP        3       //  uses PPP comm
#define TMS_COMM_TYPE_MDMASY     4       //  uses MODEM ASYN
#define TMS_COMM_TYPE_UART       5       //  uses RS232 comm

typedef enum {
	MANUAL,
	AUTO
}TMS_DOWNLOAD_MODE;

int TMSRemoteDownLoad(int iCommType, int iCommPort, char* szTerminalID, BOOL bUploadFlag, char* UploadPath, TMS_DOWNLOAD_MODE Mode);


#ifdef __cplusplus
}
#endif

#endif /* AMPTMSDOWNLOAD_H_ */

