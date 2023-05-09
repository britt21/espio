#ifndef AMPAGNOSEMVTRANS_H_
#define AMPAGNOSEMVTRANS_H_

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
* File       	 : 		AMPAgnosEmvTrans.h
* Library	 	 : 		AMPEMVL2
* Date Coded  : 		09/17/2017
**************************************************************************/
#include "AMPAgnos.h"


//2 AMPEMVL2 Initialization

//! Initialize AMPEMVL2 Framework
void InitAmpEmvL2(const char *szAgnosIniPath, const char *szAgnosConfigPath, const char *szAgnosLibsPath, AMPAGNOS_CB *Callback);

#ifdef __cplusplus
//}
#endif


#endif