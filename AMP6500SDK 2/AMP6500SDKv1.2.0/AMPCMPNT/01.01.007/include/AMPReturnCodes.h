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
* File       	 : 		AMPReturnCodes.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/24/2015
**************************************************************************/

#ifndef AMPRETURNCODES_H_
#define AMPRETURNCODES_H_


// Common Return Values
#define AMP_ENTER		1			// Return for ENTER key press
#define AMP_SUCCESS		0			// Generic SUCCESS
#define AMP_ERROR		-1			// Generic ERROR
#define AMP_FAILURE		AMP_ERROR	// Generic FAILURE
#define AMP_TIMEOUT		-2			// Return for TIMEOUT expires
#define AMP_CANCEL		-3			// Return for CANCEL key press
#define AMP_CLEAR		-4			// Return for BACKSPACE key press
#define AMP_BACKSPACE	AMP_CLEAR

// New Return values (used first in conjunction to Client Application)
#define AMP_TRANSNOTALLOWED		-5		// Return for Transaction not allowed
#define AMP_RECNOTFOUND         -6      // Return for Record not found
#define AMP_KEYEXCHANGEERR		-7		// Return for Transaction not allowed
#define AMP_PARAMDLERR          -8      // Return for Record not found
#define AMP_EMVDLERR    		-9		// Return for Transaction not allowed

// Timer Return Values
#define AMP_TIMEREXIST			-1001	// Event Mask for this timer already registered and can't be use at the moment
#define AMP_INVALIDUSERTIMER	-1002	// Invalid timer mask, must be between EVT_USER1 to EVT_USER8
#define AMP_TIMERIDNOTEXIST		-1003	// Timer ID Not existing

// COM Port Return Values
#define AMP_INVALIDPORTDEV		-2001	// Invalid COM Port Dev
#define AMP_PORT_NOT_OPEN		-2002	// COM Port not open for usage
#define AMP_PORT_HAS_PENDING 	-2003	// COMM Port has pending data to be received
#define AMP_PORT_ALREADY_OPEN 	-2004	// COMM Port already opened

// Modem Comms Return Values
#define AMP_MODEM_NOT_OPENED	-3001
#define AMP_MODEM_NOT_CONNECTED	-3002
#define AMP_MODEM_BUSY			-3003
#define AMP_MODEM_NO_DIALTONE	-3004
#define AMP_MODEM_NO_CARRIER	-3005
#define AMP_MODEM_NO_LINE		-3006
#define AMP_MODEM_NO_ANSWER		-3007
#define AMP_MODEM_OFF_HOOK		-3008
#define AMP_MODEM_LINE_IN_USED	-3009
#define AMP_MODEM_UNOBTAINABLE	-3010
#define AMP_MODEM_LINE_REVERSAL	-3011
#define AMP_MODEM_EXT_IN_USED	-3012
#define AMP_MODEM_UNK_ERROR		-3013

// Ethernet Comms Return Values
#define AMP_IP_CONNECTED				-4001	// IP connection established
#define AMP_IP_NOT_CONNECTED			-4002	// IP Not yet connected
#define AMP_IP_NO_ACTIVE_NETWORK		-4003	// No Active network
#define AMP_IP_HOST_WAITING_FOR_CONNECT	-4004	// IP Host waiting for Connection
#define AMP_IP_SOCKET_ERROR				-4005	// Generic Socket Error
#define AMP_IP_UNABLE_TO_RESOLVED_URL	-4006	// Can't resolve Host URL
#define AMP_IP_INVALID_HOSTIPADDR		-4007	// Invalid Host IP Address
#define AMP_IP_CONNECT_ERROR			-4008	// Connection Attempt Failed
#define AMP_IP_SSL_CONNECT_ERROR		-4009	// Unable to establish SSL Connection
#define AMP_IP_GPRS_CONNECT_ERROR		-4010	// Failed to establish GPRS/PPP Link

// Inter Process Comm Module
#define AMP_IPC_FATAL_ERROR			-5001 // Unexpected error / non-recoverable
#define AMP_IPC_ALREADY_EXIST		-5002 // IPC Name already exist, created your process or other process
#define AMP_IPC_NOT_EXISTING		-5003 // IPC Name not existing
#define AMP_IPC_ALREADY_CONNECTED	-5004 // IPC Name alredy connected or created

// Magstripe
#define AMP_MSR_NOT_OPEN			-6001 // MSR Not yet open
#define AMP_MSR_ALREADY_OPEN		-6002 // MSR already open
#define AMP_MSR_READ_FAILED			-6003 // Read magstripe data failed

// Database
#define AMP_DB_NOT_OPEN				-7001 // Data base not open
#define AMP_DB_FAILED_OPEN			-7002 // Data base failed to open
#define AMP_DB_ERROR				-7003 // Generic Database Error
#define AMP_DB_ADDRESS_IN_USED		-7004 // When data address is already in used (allocated) during data retrieval
#define AMP_DB_NO_MORE_REC			-7005 // No More Records to Retrieve

// Card Slot
#define AMP_ICCSLOT_NOT_OPEN		-8001 // Card Slot Not yet open
#define AMP_ICCSLOT_ALREADY_OPEN	-8002 // Card Slot Not yet open
#define AMP_ICCSLOT_CARD_NOT_PRESENT -8003 // Card not inserted

// NFC Reader
#define AMP_NFC_NOT_OPEN			-8101 // NFC Reader Not yet open
#define AMP_NFC_ALREADY_OPEN		-8102 // NFC Reader Not yet open
#define AMP_NFC_COLLISION			-8103 // Multiple Card Tap Detected
#define AMP_NFC_NOT_CTLS_CARD		-8104 // The Card is not contacless card

//EMV Return Values
#define EMV_SUCCESS			AMP_SUCCESS
#define EMV_CANCEL			AMP_CANCEL
#define EMV_ERROR			AMP_ERROR
#define EMV_CARDNOTPRESENT	AMP_ICCSLOT_CARD_NOT_PRESENT
#define EMV_PINBYPASS		-100
#define EMV_REMOVECARD		-104

#define EMV_ERR_PARAM				-9000	// Paremeter Error
#define EMV_ERR_NO_APPL				-9001	// Candidate List was Empty
#define EMV_ERR_CARD_NOT_ACCEPTD	-9002	// Card Not Accepted
#define EMV_ERR_PIN_BLOCKED			-9003	// PIN is Blocked
#define EMV_ERR_CARD_BLOCKED		-9004	// Card is Blocked
#define EMV_ERR_APPL_BLOCKED		-9005	// Application Selected is Blocked
#define EMV_ERR_SVC_NOT_ALLOWED		-9006	// Service Not Allowed
#define EMV_ERR_CHIP_ERROR			-9007	// Error on Chip Data

//EMV Contactless Return Values
#define EMVCL_ERR_USE_CONTACT		-10001 	// Use Contact Interface

// TMS Download Return Values
#define AMP_TMS_SUCCESS				AMP_SUCCESS
#define AMP_TMS_ERROR_DOWNLOAD		AMP_ERROR
#define AMP_TMS_CANCEL				AMP_CANCEL
#define AMP_TMS_ERROR_UPDATE		-2

#endif /* AMPRETURNCODES_H_ */

