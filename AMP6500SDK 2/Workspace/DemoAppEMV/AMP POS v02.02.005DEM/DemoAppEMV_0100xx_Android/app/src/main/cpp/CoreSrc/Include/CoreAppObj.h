
#ifndef APPOBJ_APPOBJ_H_
#define APPOBJ_APPOBJ_H_

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
* File       	: 		AppObj.h
* Application 	: 		AMP Base Application
* Date Coded	: 		03/11/2015
**************************************************************************/

#include <AMPAppObj.h>
#include <AMPConfig.h>
#include <AMPAgnosConfig.h>

//4 App States Definition
#define APP_STATE_IDLE				0x01
#define APP_STATE_DESKTOP			0x02
#define APP_STATE_MENU				0x03
#define APP_STATE_EXEC_FUNCTION		0x04

//4 Idle Screen Transition State
#define IDLE_SCREEN_TRANSITION_STATE_1		1
#define IDLE_SCREEN_TRANSITION_STATE_2		2
#define IDLE_SCREEN_TRANSITION_STATE_3		3
#define MAX_SCREEN_TRANSITION_STATE			IDLE_SCREEN_TRANSITION_STATE_3

class cAppObj : public cAMPAppObj {
public:

	virtual ~cAppObj();

	//! Creates the App Object
	static cAppObj* Create_Application(int argc, char *argv[]);
	//! Returns the only instance of App Obj
	static cAppObj* get_AppObj(void);

	//! Method to start running the application
	void RunApp(void);


protected:	

	//! Sets the custom timers
	void SetCustomTimers(void);

	//! Enables/disables Screen Transition
	void EnableScreenTransition(bool bEnable );

	//! Initialize EMV Module (only needs to execute once on startup)
	void InitializeEMV(void);

	//! Initialize EMV Config
	void InitializeEMVConfig(void);
		
	//! Executes one time before application runs
	virtual void ApplicationColdInit();

	//! Execute after stoping the event engine
	virtual void ApplicationDeInit();

	cAppObj(int argc, char *argv[]);

private:
	static char m_className[];			

	int m_nAppState;
	int m_nIdleScreenState;	

};

#endif /* APPOBJ_APPOBJ_H_ */

