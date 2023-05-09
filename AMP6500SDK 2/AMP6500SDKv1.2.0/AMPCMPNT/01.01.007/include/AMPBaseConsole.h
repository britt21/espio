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
* File       	 : 		AMPBaseConsole.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/09/2015
**************************************************************************/

#ifndef AMPBASECONSOLE_H_
#define AMPBASECONSOLE_H_

// Project Header
#include "AMPDataTypes.h"
#include "AMPReturnCodes.h"
#include "AMPUtils.h"

/* Keyboard Codes */
#define AMPKEY_POWER	0xF00A
#define AMPKEY_UP		0xF002
#define AMPKEY_DOWN		0xF003
#define AMPKEY_LEFT		AMPKEY_UP
#define AMPKEY_RIGHT	AMPKEY_DOWN
#define AMPKEY_MENU		0xF204
#define AMPKEY_FUNC		0xF202
#define AMPKEY_ALPHA	0xF201
#define AMPKEY_ENTER	0x000D
#define AMPKEY_CLEAR	0x0008
#define AMPKEY_CANCEL	0x001B
#define AMPKEY_0		0x0030
#define AMPKEY_1		0x0031
#define AMPKEY_2		0x0032
#define AMPKEY_3		0x0033
#define AMPKEY_4		0x0034
#define AMPKEY_5		0x0035
#define AMPKEY_6		0x0036
#define AMPKEY_7		0x0037
#define AMPKEY_8		0x0038
#define AMPKEY_9		0x0039

#define AMPKEY_MENU1	0x0081
#define AMPKEY_MENU2	0x0082
#define AMPKEY_MENU3	0x0083
#define AMPKEY_MENU4	0x0084
#define AMPKEY_MENU5	0x0085
#define AMPKEY_MENU6	0x0086

#define BEEP_NONE		0
#define BEEP_INFO		1
#define BEEP_WARN		2
#define BEEP_ERROR		3

#if 0
class cAMPBaseConsole
{
  public:

	//!Constructor
	cAMPBaseConsole();
	//!Destructor
	virtual ~cAMPBaseConsole();

  public:

	//! Enables keypad beep sound
	virtual void EnableKeypadBeep(BOOL bEnable);
	//! Enables console beep sound
	virtual void EnableConsoleBeep(BOOL bEnable);

	//! Info Beep (1 medium length low frequency beep)
	virtual void BeepInfo();
	//! Outputs 3 short beeps
	virtual void BeepWarning();
	//! Error Beep (1 long high frequency beep)
	virtual void BeepError();
	//! Outputs beep sound
	virtual void Beep();

	//! Enables/Disables KeyBoard
	virtual void SetEnableKeyBoard(BOOL bEnable);
	//! Returns the KeyBoard status (if enabled or not)
	virtual BOOL GetEnableKeyBoard();
	//! Flushes KeyBoard buffer of its contents
	virtual void FlushKeyBoard();
	//! Tests if a KeyBoard event occurred
	virtual BOOL CheckKeyBoardEvent();
	//! Gets a key
	virtual BOOL GetKey(unsigned short *Key);
	//! Gets the raw value of key pressed
	virtual BOOL GetRawKey(unsigned short *Key);
	//! Waits for a few seconds until the user press a key
	virtual short WaitKey(long lnSeconds=0, BOOL bBeeping = FALSE);

  private:
	//Enable/Disable KeyBoard function
	BOOL m_bEnableKB;
	//Enable/Disable Console Beep/Warning sound
	BOOL m_bEnableConsoleBeep;

	//! Pointer to class name
	static char m_className[];

};
#endif
#endif /* AMPBASECONSOLE_H_ */
