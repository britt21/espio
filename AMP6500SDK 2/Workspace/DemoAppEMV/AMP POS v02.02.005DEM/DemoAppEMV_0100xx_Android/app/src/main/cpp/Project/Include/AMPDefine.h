
#ifndef AMPDEFINE_H_
#define AMPDEFINE_H_

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

// Temporary path in system for our application
#define UNIX_TMP_PATH "/var/amp_tmp/"

#define AMPCMPNT_VER "1.0.0"

// Default Sizes
#define MAX_STR_SZ 64
#define MAX_JSON_VARNAME_SZ 64
#define MAX_FILNAME_SZ 64
#define MAX_LOGICAL_NAME MAX_STR_SZ
#define SERIAL_NUMBER_SZ MAX_STR_SZ

#define AMP_GEN_TIMER               (EVT_TIMER|(1L<<28))    /*!<AMP General Timer ID */ 
#define AMP_CONSOLEWAIT_TIMER       (EVT_TIMER|(1L<<29))    /*!<AMP Console Wait Timer ID */

// Comm Port Devices (UART)
#define PORT_DEV_COM1       0x00 // PORT_COM1
#define PORT_DEV_MODEM      0x01 // PORT_MODEM
#define PORT_DEV_WNET       0x02 // PORT_WNET
#define PORT_DEV_PINPAD     0x03 // PORT_PINPAD
#define PORT_DEV_GPS        0x04 // PORT_GPS
#define PORT_DEV_EXT        0x05 // PORT_EXT
#define PORT_DEV_USBD       0x06 // PORT_XX
#define PORT_DEV_USB0       0x07 // PORT_6210LINK8210
#define PORT_DEV_ACM0       0x08 // PORT_6210LINK8210ACM
#define PORT_DEV_HID        0x09 // PORT_HID
#define PORT_DEV_BLUETOOTH	0x0A // PORT_BLUETOOTH

// Common String Separator
#define DEFAULT_SEPARATOR	"~"

#endif /* AMPDEFINE_H_ */

