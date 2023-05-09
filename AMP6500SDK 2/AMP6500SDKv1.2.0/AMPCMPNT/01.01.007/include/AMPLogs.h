
#ifndef AMPLOGS_H_
#define AMPLOGS_H_

/***************************************************************************
 * 
 * Copyright (C) 2016 by APEX, Inc.
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of APEX Co. LLC.
 **************************************************************************/

/**************************************************************************
* File       	 : 		AMPLogs.h
* Library	 	 : 		AMP Component
* Date Coded  : 		12/15/2016
**************************************************************************/

typedef enum {

	EVENT_NONE = 0,

	// 1. Access to Cardholder Info Events
	EVENT_VOID_TRANS,
	EVENT_RECALL_TRANS,
	EVENT_REPRINT_TRANS,

	// 2. Admin Tasks/Events
	EVENT_MODIFY_COMMS_SETTINGS,
	EVENT_PURGE_BATCH,
	EVENT_SETTLEMENT,
	EVENT_PRINT_REPORTS,

	// 3. Access to Audit Log file (TMS Upload)
	EVENT_TMS_UPLOAD,

	// 4. Invalid User Login Attempt
	EVENT_FAILED_LOGIN,

	// 5. Creation of new User Account (Operator)
	EVENT_ACCOUNT_CREATION,

	// 6. Initialization of Audit Logs
	EVENT_INIT_AUDIT_LOGS,

	// 7. Creation/Deletion of Database Table/Records
	EVENT_DATABASE_CREATION,

	// 8. Reset Password
	EVENT_RESET_PASSWORD,

	// 9. Deletion of User Account (Operator)
	EVENT_ACCOUNT_DELETION,

	// 10. Admin Locked 
	EVENT_ADMIN_LOCKED,

	// 11. Data Changes (TMS Download)
	EVENT_TMS_DOWNLOAD,

	// 12. Admin Unlock
	EVENT_ADMIN_UNLOCK,
	
	EVENT_TMS_AUTO_DOWNLOAD_SUCCESS,
	EVENT_TMS_AUTO_DOWNLOAD_FAILURE
} EVENTLOG;

typedef enum {

	NOT_LOGGED_IN = 0,
	SUPER_ACCOUNT,
	ADMIN_ACCOUNT,
	OPERATOR_ACCOUNT,

} USER_ACCOUNT_TYPE;


class cAMPLogs {
public:
	virtual ~cAMPLogs();

	//! Methods for Retrieving AMP Objects
	static cAMPLogs* getLogsObj();

	//! Initialize Log Object
	virtual void Initialize();

	//! Log Activity / Task
	virtual int Write(EVENTLOG Event, USER_ACCOUNT_TYPE AcctType, char *OperatorName = NULL);

	//! Deletes the current contents and creates a new one
	virtual void Renew(void);

	static void SetLogsPath(char* logDir);
	static char* GetLogsPath(void);
	
protected:	
	cAMPLogs(void);

	//! Create Logs Directory (if not existing)
	void CreateLogsDirectory(void);

	//! Create Log file (if not existing)
	void CreateLogFile(void);

	//! Returns the Event Definition
	void GetEventDefinition(EVENTLOG Event, char *szEvent);

	//! Returns the Account Type Definition
	void GetAcctTypeDefinition(USER_ACCOUNT_TYPE AcctType, char *szAcctType);

	void GetTimeStamp(char *szTimeStamp);

	//! Pointer to Static cAMPLogs Object
	static cAMPLogs* LogsObj;

private:

	static char m_className[];
	static char m_logDir[256];

};

#endif /* AMPLOGS_H_ */

