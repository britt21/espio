#ifndef COM_POS_DEVICE_IPRINTERSERVICE_LISTENER_H
#define COM_POS_DEVICE_IPRINTERSERVICE_LISTENER_H

#include <binder/IBinder.h>
#include <binder/IInterface.h>

namespace android
{

// must be kept in sync with interface defined in OnPrintListener.aidl
    enum {
        TRANSACT_ONPRINTLISTENER_PERFORM = IBinder::FIRST_CALL_TRANSACTION,
    };

// ----------------------------------------------------------------------------

    class IPrinterServiceListener : public IInterface
    {
    public:
        DECLARE_META_INTERFACE(PrinterServiceListener);

        virtual void onPrintResult(int result,int64_t taskId) = 0;
    };

    class BnPrinterServiceListener : public BnInterface<IPrinterServiceListener>
    {
    public:
        virtual status_t    onTransact(uint32_t code,
                                       const Parcel& data,
                                       Parcel* reply,
                                       uint32_t flags = 0);
    };

// ----------------------------------------------------------------------------

}; // namespace android

#endif // COM_POS_DEVICE_IPRINTERSERVICE_LISTENER_H

