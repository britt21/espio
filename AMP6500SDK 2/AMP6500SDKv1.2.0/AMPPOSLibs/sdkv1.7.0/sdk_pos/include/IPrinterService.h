#ifndef COM_POS_DEVICE_IPRINTERSERVICE_H
#define COM_POS_DEVICE_IPRINTERSERVICE_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include "IPrinterServiceListener.h"

namespace android
{
    /**
     * Define the status of the printer.
     */
    enum {
        PRINTER_BASE_STATUS = 0,
        PRINTER_IDLE_STATUS = PRINTER_BASE_STATUS,          /*打印机空闲*/
        PRINTER_BUSY_STATUS = PRINTER_BASE_STATUS - 1,      /* 打印机忙*/
        PRINTER_HIGHT_TEMP_STATUS =  PRINTER_BASE_STATUS - 2,   /* 打印机温度过高*/
        PRINTER_PAPER_LACK_STATUS = PRINTER_BASE_STATUS - 3,    /* 打印机缺纸 */
        PRINTER_NO_BATTERY_STATUS = PRINTER_BASE_STATUS - 4,    /* 无电池打印 */
        PRINTER_FEED_STATUS         =   PRINTER_BASE_STATUS - 5,     /* 正在走纸 */
        PRINTER_PRINT_STATUS        =   PRINTER_BASE_STATUS - 6,     /* 正在印数据 */
        PRINTER_FORCE_FEED_STATUS   =   PRINTER_BASE_STATUS - 7,     /* 强制走纸 */
        PRINTER_POWER_ON_STATUS     =   PRINTER_BASE_STATUS - 8,     /* 电源打开 */
    };

    /**
     * Define the command code.
     */
    enum {
        SVC_START_PRINT = IBinder::FIRST_CALL_TRANSACTION,
        SVC_SET_MAX_TEMPERATURE,
        SVC_SET_DEFAULT_GRAY ,
        SVC_GET_RO_WIDTH ,
        SVC_GET_VOLTAGE ,
        SVC_GET_TEMPERATURE,
        SVC_GET_STATUS ,
        SVC_GET_MAX_TEMPERATURE ,
        SVC_GET_DEFAULT_GRAY ,
        SVC_CANCEL_PRINT,
    };

    class PrinterBuffer
    {
    private:
        char* data;
        int length;

    public:
        PrinterBuffer() :
            data(NULL),
            length(0)
        {
        }

        PrinterBuffer(char* dataBytes, int dataLength)
        {
            data = new char[dataLength];
            memcpy(data, dataBytes, dataLength);
            length = dataLength;
            //printf("+++ PrinterBuffer +++ \n");
        }

        ~PrinterBuffer()
        {
            if (NULL != data) {
                //printf("--- PrinterBuffer --- \n");
                delete [] data;
            }
        }

        char* getData()
        {
            return data;
        }

        int getLength()
        {
            return length;
        }
    };

    /**
    * Define the PrintTask parcel.
    */
    class PrintTaskMiddle
    {
    private:
        int flag;
        int64_t id;
        int gray;
        int step;
        PrinterBuffer* buffer;
        sp<IPrinterServiceListener> mListener;

    public:
        PrintTaskMiddle();
        PrintTaskMiddle(Parcel* parcel);
        ~PrintTaskMiddle();

        status_t readFromParcel(Parcel* parcel);
        status_t writeToParcel(Parcel* parcel) const;

        int64_t getTaskId();
        int getGray();
        int getStep();
        PrinterBuffer* getBufferRef();
        sp<IPrinterServiceListener> getListener();
    };

    class IPrinterService : public IInterface
    {
    public:
        DECLARE_META_INTERFACE(PrinterService);
        virtual void startPrint(PrintTaskMiddle* printTask) = 0;
        virtual void setMaxTemperature(int temperature) = 0;
        virtual void setDefaultGray(int gray) = 0;
        virtual int getWidth(void) = 0;
        virtual int getVoltage(void) = 0;
        virtual int getTemperature(void) = 0;
        virtual int getStatus(void) = 0;
        virtual int getMaxTemperature(void) = 0;
        virtual int getDefaultGray(void) = 0;
        virtual void cancelPrint(int64_t taskId) = 0;
    };

    class BnPrinterService : public BnInterface<IPrinterService>
    {
    public:
        virtual status_t    onTransact(uint32_t code,
                                       const Parcel& data,
                                       Parcel*  reply,
                                       uint32_t flags = 0);
    };

};// namespace android
#endif

