#ifndef COM_POS_DEVICE_PRINTERSERVICE_H
#define COM_POS_DEVICE_PRINTERSERVICE_H

#include <utils/List.h>
#include <utils/RefBase.h>
#include <semaphore.h>
#include <sys/time.h>

#include "IBasicService.h"

using namespace std;

namespace android
{
    class BeepInfo
    {
    private:
        int frequency;
        int durationMs;

    public:
        BeepInfo(int mfrequency, int mdurationMs)
        {
            //printf("-------------BeepInfo create---------------\n");
            frequency = mfrequency;
            durationMs = mdurationMs;
        }

        ~BeepInfo()
        {
            //printf("-------------BeepInfo destory---------------\n");
        }

        int getFrequency(void)
        {
            return frequency;
        }

        int getDurationMs(void)
        {
            return durationMs;
        }
    };

    class BasicService : public BnBasicService
    {
    public:
        static int instantiate();
        virtual void sys_beep(void);
        int  get_sockfd(void)
        {
            return this->m_sk[1];
        };

    private:
        mutable Mutex mLock;
        mutable Mutex beepLock;
        BeepInfo* beepInfo;
        pthread_t m_thread;
        int  m_sk[2];

        BasicService();
        virtual ~BasicService();

        virtual void sysBeep(int frequency, int durationMs);
        virtual int setLedBrightness(const char* ledName, int status) ;
        virtual void setTime(int64_t time);
        virtual int setRealTime(struct timeval *tv);
        virtual int getValue(const char *key, uint8_t *buff, uint32_t buff_len, uint32_t *out_len);
        virtual int setValue(const char *key, const char *value);
        virtual int getSPVersion(char *buffer, int len);
        //mengwt 2017.8.22 add sp timeout to sleep
        virtual void setSPTimeout(int second);
        virtual void StartwatchD();
        //poe.cao 2017.09.21 add for write splash device
        virtual int writeSplashDevice(const char *pngpath);
        virtual int fileCopyChannel(const char *src, const char *dest);
        virtual int getHardwareVersion(char *buffer, int length);
        virtual int getRandomForVendorFWID(uint8_t random[8]);
        virtual int getAPFirmwareId(char* buff, int len);
        virtual int getSPFirmwareId(char* buff, int len);		
        virtual int checkFirmwareIds(void);
    };

};
#endif
