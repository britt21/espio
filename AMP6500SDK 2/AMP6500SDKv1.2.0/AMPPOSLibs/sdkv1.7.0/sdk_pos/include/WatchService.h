#ifndef WATCH_SERVICE_H
#define WATCH_SERVICE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <android/log.h>
#include <pthread.h>

#define BASIC_TAG    "LibBasicService"

#ifdef DEBUG
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, BASIC_TAG, __VA_ARGS__)
#else
#define LOGD(...) if(0){}
#endif

#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,BASIC_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,BASIC_TAG,__VA_ARGS__)
#define FIRMWARE_ID    "firmwareid"
#define INIT_ENC_FW_ID "fwid_inner"
pthread_mutex_t vfid_lock;  

typedef void *(*Routine)(void *arg);
typedef enum {
    W_ONESHOT = 0,
    W_RESTART,      /* ����߳��˳��������Զ��������̣߳�ֻ��scpd���������´����߳�*/
    W_DAEMON,       /* ��פ�߳�,�߳�����쳣�˳��������ٴ�������scpd����Ҳ�����´���*/
    W_MAX,
} WatchType;

void watch_fun_init(void);
void *watch_daemon(void *arg);
void *watch_register(WatchType type, Routine func, void*arg);
void watch_unregister(void *remove_list);

void sp_watch_entry(void *arg);

#ifdef __cplusplus
}
#endif
#endif
