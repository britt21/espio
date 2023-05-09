#ifndef COM_NEWPOS_VERIFYSERVICE_H
#define COM_NEWPOS_VERIFYSERVICE_H

#include <utils/Mutex.h>

#include "IVerifyService.h"

namespace android {
// ---------------------------------------------------------------------------
class VerifyService : public BnVerifyService
{
	public:
		static int Instance();	

	private:
		// protected by mLock
	    mutable Mutex mLock;

		// IVerifyService interface
		VerifyService();
		virtual ~VerifyService();
		virtual int verifyPci(const char *path, int type);
		virtual int noNeedToVerifyThirdparty(const char *filename);
		virtual int isSystemFile(const char *filename);
		virtual int isMfSigned(const char *filename);
	};


// ---------------------------------------------------------------------------
};
#endif
