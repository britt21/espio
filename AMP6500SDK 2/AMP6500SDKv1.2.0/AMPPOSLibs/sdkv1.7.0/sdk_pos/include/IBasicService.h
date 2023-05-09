#ifndef COM_POS_DEVICE_IPRINTERSERVICE_H
#define COM_POS_DEVICE_IPRINTERSERVICE_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android
{

    /**
     * Define the command code.
     */
    enum {
        SVC_BASIC_BEEP = IBinder::FIRST_CALL_TRANSACTION,
        SVC_BASIC_SET_LED,
        SVC_BASIC_SET_TIME ,
        SVC_BASIC_GET_VALUE_FROM_VENDOR,
        SVC_BASIC_SET_VALUE_TO_VENDOR,
        SVC_BASIC_GET_SP_VERSION,
        SVC_BASIC_SET_SP_TIMEOUT,
        SVC_BASIC_WRITE_PNG_SPLASH_DEVICE,
        SVC_BASIC_FILE_COPY_CHANNEL,
        SVC_BASIC_GET_HARDWARE_VERSION,
        SVC_BASIC_GET_RANDOM_FOR_VENDOR_FWID,
        SVC_BASIC_GET_AP_FWID,
        SVC_BAISC_CHECK_FWIDS,
        SVC_BASIC_GET_SP_FWID,
    };

    class IBasicService : public IInterface
    {
    public:
        DECLARE_META_INTERFACE(BasicService);
        virtual void sysBeep(int frequency, int durationMs) = 0;
        virtual int setLedBrightness(const char* ledName, int status) = 0;
        virtual void setTime(int64_t time) = 0;
        virtual int getValue(const char *key, uint8_t *buff, uint32_t buff_len, uint32_t *out_len) = 0;
        virtual int setValue(const char *key, const char *value) = 0;
        virtual int getSPVersion(char *buff, int len) = 0;
        //mengwt 2017.8.22 add sp timeout to sleep
        virtual void setSPTimeout(int second) = 0;
        //poe.cao 2017.09.21 add write splash device
        virtual int writeSplashDevice(const char *pngpath) = 0;
        //poe.cao 2017.09.21 file copy
        virtual int fileCopyChannel(const char *src, const char* dest) = 0;
        //keiven.chen 2017.10.13 add get hardware version
        virtual int getHardwareVersion(char *buff, int length) = 0;
        virtual int getRandomForVendorFWID(uint8_t random[8]) = 0;
        virtual int getAPFirmwareId(char* buff, int len) = 0;
        virtual int getSPFirmwareId(char* buff, int len) = 0;
        virtual int checkFirmwareIds(void) = 0;
    };

    class BnBasicService : public BnInterface<IBasicService>
    {
    private :
        status_t on_beep(const Parcel& data, Parcel* reply);
        status_t on_setLedBrightness(const Parcel& data, Parcel* reply);
        status_t on_setTime(const Parcel& data, Parcel* reply);
        status_t on_getValue(const Parcel& data, Parcel* reply);
        status_t on_setValue(const Parcel& data, Parcel* reply);
        status_t on_get_sp_version(const Parcel& data, Parcel* reply);
        //mengwt 2017.8.22 add sp timeout to sleep
        status_t on_setSPTimeout(const Parcel& data, Parcel* reply);
        //poe.cao 2017.09.21 add for write splash device
        status_t on_writeSplashDevice(const Parcel& data, Parcel* reply);
        //poe.cao 2017.09.21 file copy
        status_t on_fileCopyChannel(const Parcel& data, Parcel* reply);
        //keiven.chen 2017.10.13 add get hardware version
        status_t on_get_hardware_version(const Parcel & data, Parcel * reply);
        status_t on_get_random_for_vendor_fwid(const Parcel & data, Parcel * reply);
        status_t on_get_ap_fwid(const Parcel & data, Parcel * reply);
        status_t on_get_sp_fwid(const Parcel & data, Parcel * reply);
        status_t on_check_fwids(const Parcel & data, Parcel * reply);
    public:
        virtual status_t    onTransact(uint32_t code,
                                       const Parcel& data,
                                       Parcel*  reply,
                                       uint32_t flags = 0);

    };

};// namespace android
#endif

