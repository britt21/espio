#ifndef COM_NEWPOS_IVERIFYSERVICE_H
#define COM_NEWPOS_IVERIFYSERVICE_H

#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android
{
    enum
    {
        SVC_VERIFY_VERIFY_PCI = IBinder::FIRST_CALL_TRANSACTION,
		SVC_VERIFY_VERIFY_NO_NEED_VERIFY_THIRDPARTY,
		SVC_VERIFY_VERIFY_IS_SYSTEM_FILE,
		SVC_VERIFY_VERIFY_IS_MF_SIGNED,
    };
 
    class IVerifyService : public IInterface
    {
        public:
			DECLARE_META_INTERFACE(VerifyService); // declare macro
			virtual int verifyPci(const char *path, int type) = 0;
			virtual int noNeedToVerifyThirdparty(const char *filename) = 0;
			virtual int isSystemFile(const char *filename) = 0;
			virtual int isMfSigned(const char *filename) = 0;
    };

	class BnVerifyService : public BnInterface<IVerifyService>
	{
		public:
		virtual status_t	onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
	}; 
} ;// namespace android
#endif
