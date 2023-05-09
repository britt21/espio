//
// Created by ping_ocampo on 3/25/2018.
//

#ifndef BASEAPP_AMPBASEANDROIDIF_H
#define BASEAPP_AMPBASEANDROIDIF_H

#include <jni.h>
#include <AMPPosEntry.h>
#include <signal.h>

#ifdef __cplusplus
extern "C"
{
#endif

//! AmpBaseInterface Function Declarations
JNIEXPORT void JNICALL Java_AmpBaseInterface_AmpBaseInterface_Initialize
(JNIEnv *, jclass, jobject, jobject, jobject);

JNIEXPORT int JNICALL Java_AmpBaseInterface_AmpBaseInterface_PerformTransaction
(JNIEnv *, jclass, jlong);


#ifdef __cplusplus
}
#endif

int PerformOperation(int operID);
int PerformOperation(int operID, const char* id);
void PerformDisplayOperation(const char* szHeader, const char* szPrompt1, const char* szPrompt2, const char* szPrompt3, const char* szPrompt4, int iBeep, int iDelayMS);
int PerformEntryOperation(const char* szHeader, const char* szPrompt1, const char* szPrompt2, int iMax,
                          int iMin, char* FieldFormat, char Mask, char* CurrSymbol, INPUT_METHOD InpMethod, char* szOutBuffer, int FontSize, int iTimeout);

int PerformEnterCancelOperation(const char* szHeader, const char* szPrompt1, const char* szPrompt2, const char* szPrompt3, const char* szPrompt4, int iBeep, int iTimeout);
int PerformCancelOperation(const char* szHeader, const char* szPrompt1, const char* szPrompt2, const char* szPrompt3, const char* szPrompt4, int iBeep, int iTimeout);

char* PerformGetEntryValueOperation(void);

int PerformSelectionOperation(const char *szHeader, const char* szPrompt1, const char* szPrompt2, int nSelectionButtons,
                              const char *szButtonMsg1, const char* szButtonMsg2, const char* szButtonMsg3, int iTimeout, int iBeep);

void PerformDisplayCardEntry(const char* szHeader, const char* szPromptLang1, const char* szPromptLang2, unsigned char bDisplayIcon);
int PerformCardTypeSelectionOperation(char CardTypeLabels[][MAX_STR_SZ+1], int NumItems);
int PerformDisplayTransDetailsOperation(const char* szTransName, const char* szInvoiceNum, const char* szCardNum,
                                        const char* szRRN, const char* szAmount, const char* szAuthNum,
                                        const char* szDateTime, const char* szVoided, const char* szHeader, int DisplayType, int iTimeOut);

int PerformChoiceSelectionOperation(const char *szTitle, char CardTypeLabels[][MAX_STR_SZ+1], int NumChoices, int DefaultSelection);
int PerformDisplayPassTerminal(const char* szHeader, const char* szPrompt1, const char* szPrompt2, BOOL bWaitForKey);
void PerformClientAppBufferSetting();
void PerformClientResponseSetting();
void PerformSetDateTime(const char* dateTime);
const char* PerformGetSN();

int Android_GetErrorCode();

void AndroidReleaseString(JNIEnv* env, jstring jniString, const char* strValue);
void AndroidDeleteObject(JNIEnv* env, jobject jobj);
void AndroidDeleteObject(JNIEnv* env, jstring jobj);
void AndroidDeleteObject(JNIEnv* env, jbyteArray jobj);
void AndroidReleaseByteArray(JNIEnv* env, jbyteArray jbyteObj, jbyte* byteVal);

void CriticalErrorHandler(int signal, siginfo_t *si, void *arg);

#endif //BASEAPP_AMPBASEANDROIDIF_H
