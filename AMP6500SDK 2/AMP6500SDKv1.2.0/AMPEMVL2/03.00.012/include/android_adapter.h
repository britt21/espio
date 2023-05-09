/* DO NOT EDIT THIS FILE - it is machine generated */
#if defined(ANDROID)
#include <jni.h>
#undef  INI_FILE
#define INI_FILE			"/data/data/com.example.emv/files/agnos.ini"

/* Header for class com_example_emv_test_emvtest */

#ifndef _Included_com_example_emv_emvtest
#define _Included_com_example_emv_emvtest

#if 0
typedef enum {
	ANDROID_AMP8000	= 1,
	ANDROID_AMP8200,
	ANDROID_AMP6500,
	ANDROID_AMP6700
} TERMINAL_MODEL;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_example_emv_test_emvtest
 * Method:    emv_read
 * Signature: (Lcom/example/emv_test/OnEmvProcessListener;)V
 */
//JNIEXPORT void JNICALL Java_com_example_emv_emvtest_emv_1read(JNIEnv * env, jclass class, jobject obj, jstring str);

//void  jni_init(JNIEnv * env, jclass class1, jobject obj);
void  jni_init(JNIEnv * env, jobject obj);
void setListenerClass(const char *classname);

#if 0
void LoadCardLibraries(const char *szLibDir);

int GetTerminalModel(void);
#endif
 void lcdDisplay_9210(int Col, int Line, unsigned int Mode, const char *format);
 void lcdCls_9210(void);
 void lcdClrLine_9210(int BeginLine, int EndLine);
 int kbGetKey_9210(void);
 int kbhit_9210(void);
 void kbFlush_9210(void);
 void lcd_store_9210();
 void lcd_restore_9210();
 int kbGetString_9210(unsigned int mode, int minlen, int maxlen, unsigned int timeout, char *info);
 void log_9210(const char* format,...);
 void lcdDrawPicture_9210();
 void get_pin_5210();
 void remove_pin_view();
 void get_type_9220(char * buf_type,int len);

//2 Customized
void log_printf(const char* format,...);
void AndroidBeep(int frequency, int durationMs);
//void AndroidGetTermSerialNum(char *szTermSerialNum);

#ifdef __cplusplus
}
#endif
#endif

#endif
