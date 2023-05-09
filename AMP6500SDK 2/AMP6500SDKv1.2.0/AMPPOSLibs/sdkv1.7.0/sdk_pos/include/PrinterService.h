#ifndef COM_POS_DEVICE_PRINTERSERVICE_H
#define COM_POS_DEVICE_PRINTERSERVICE_H

#include <utils/List.h>
#include <utils/RefBase.h>
#include <semaphore.h>
#include "IPrinterService.h"

using namespace std;

namespace android
{

    class PrinterTaskWrapper
    {
    private:
        int fd;
        mutable Mutex mLock;
        List<PrintTaskMiddle*> *mTaskList;
        sem_t sem;

    public:

        PrinterTaskWrapper(List<PrintTaskMiddle*>* list)
        {
            fd = -1;
            mTaskList = list;
        }

        ~PrinterTaskWrapper()
        {
            printf("~~~~PrinterTaskWrapper~~~ \n");
        }

        int getPrinterFd()
        {
            return fd;
        }

        void setPrinterFd(int printerFd)
        {
            fd = printerFd;
        }

        List<PrintTaskMiddle*>* getTaskList()
        {
            return mTaskList;
        }

        Mutex* getLock()
        {
            return &mLock;
        }

        sem_t* getSem()
        {
            return &sem;
        }

    };

    class PrinterService : public BnPrinterService
    {
    public:
        static int instantiate();

    private:
        //The Printer thread.
        pthread_t printerThread;

        pthread_t printerCloseThread;
        //The printer task list.
        List<PrintTaskMiddle*> mList;
        //The printer tasks wrapper
        PrinterTaskWrapper* ptTaskWrapper;

        PrinterService();
        virtual ~PrinterService();
        virtual void openPrinterCtrl();

        virtual void startPrint(PrintTaskMiddle* printTask) ;
        virtual void setMaxTemperature(int temperature) ;
        virtual void setDefaultGray(int gray);
        virtual int getWidth(void) ;
        virtual int getVoltage(void) ;
        virtual int getTemperature(void) ;
        virtual int getStatus(void) ;
        virtual int getMaxTemperature(void) ;
        virtual int getDefaultGray(void) ;
        virtual void cancelPrint(int64_t taskId) ;

    };

};
#endif
