#ifndef COM_POS_DEVICE_PRINTERSERVICE_LISTENER_H
#define COM_POS_DEVICE_PRINTERSERVICE_LISTENER_H

#include "IPrinterServiceListener.h"

namespace android
{
    class PrinterServiceListener: public BnPrinterServiceListener
    {
    public:
        PrinterServiceListener();
        virtual ~PrinterServiceListener();
        virtual void onPrintResult(int result, int64_t taskId);
    };
}

#endif

