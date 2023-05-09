
#ifndef AMPCMPNT_H_
#define AMPCMPNT_H_

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
* File       	 : 		AMPCmpnt.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/08/2015
**************************************************************************/

#include <jni.h>
#include "AMPUtils.h"
#include "AMPConfig.h"

class cAMPCmpnt {
public:

	virtual ~cAMPCmpnt();

	static cAMPCmpnt* get_AMPCmpnt(void);
	static cAMPConfig* get_ConfigObj(void);

	void Initialize(JNIEnv* env, jobject AmpCmpntObj, jobject Context);

	JavaVM** get_JavaVM(void);

	jobject* get_AmpCmpntObj(void);

	jobject* get_ContextObj(void);

protected:	
	cAMPCmpnt();

private:

	static char m_className[];

	jobject m_AmpCmpntObj;
	JavaVM* m_JavaVM;
	jobject m_Context;

};

#endif /* AMPCMPNT_H_ */

