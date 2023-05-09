
#ifndef AMPAGNOSEMVCTLS_H_
#define AMPAGNOSEMVCTLS_H_

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
* File       	 : 		AMPAgnosEmvCtls.h
* Library	 	 : 		AMP Component
* Date Coded  : 		08/16/2016
**************************************************************************/

#include <AMPDataTypes.h>

#include <paymentMW.h>
//#include <Agnostypes.h>
#include "AMPAgnosEmv.h"

class cAMPAgnosEmvCtls : public cAMPAgnosEmv
{

public:

	static cAMPAgnosEmvCtls *get_Instance(void);
	

	/*
	*	Initialization Methods
	*/
	//4 Only needs to be called once, to register the function callbacks
	//void EMVInitUserCallBack(AMP_EMVCB* UserCallback);
	//4 Must be call upon starting an EMV Transaction, preferrably right after Card Insert
	
	int InitTrans(void);
	int DeInitTrans(void);

	int ProcessCtlsEntryPoint(void);
	int ProcessCtlsCompletion(void);

	//! Option=1: LED 1-4 OFF;
	//! Optiion=2: LED 1-3 OFF, LED 4 RED
	int ErrorLEDDisplay(int Option);



	/*
	*	Utility Functions
	*/
	void RemoveTapCard(void);



protected:


	cAMPAgnosEmvCtls();
	virtual ~cAMPAgnosEmvCtls();

	
	void SetPOSEntryMode(void);
	int GetLastError(void);
	
	
private:

	//! Callback Functions
	//AMP_EMVCB m_CallbackFunc;

	BOOL m_bFirstTrans;
	tStartingPoint m_EntryPoint;

	//!The singleton instance
	static cAMPAgnosEmvCtls * single;

	static char m_className[];	

};



#endif /* AMPAGNOSEMVCTLS_H_ */

