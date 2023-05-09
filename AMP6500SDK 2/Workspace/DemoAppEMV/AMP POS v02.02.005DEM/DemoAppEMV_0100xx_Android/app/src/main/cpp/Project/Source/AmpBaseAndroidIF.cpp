/***************************************************************************
 *
 * Copyright (C) 2015 by APEX, Inc.
 *
 * All rights reserved.  No part of this software may be reproduced,
 * transmitted, transcribed, stored in a retrieval system, or translated
 * into any language or computer language, in any form or by any means,
 * electronic, mechanical, magnetic, optical, chemical, manual or otherwise,
 * without the prior written permission of APEX Co. LLC.
 **************************************************************************/

/**************************************************************************
* File       	 : 		AMPBaseAndroidIF.cpp
* Library	 	 :
* Date Coded  : 		09/18/2017
**************************************************************************/

/***************************************************************************
 * Includes
 **************************************************************************/

#include <jni.h>

// Standard Library
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Project Includes
#include <AMPAgnosEMV.h>
#include <AMPReturnCodes.h>
#include <AMPCmpnt.h>
#include "CoreAgnosEMVTrans.h"
#include "CoreAgnosEmvFunc.h"
#include "CoreAgnosEmvCtlsFunc.h"
#include "CoreTransObj.h"
#include "CoreCardUtils.h"
#include "CoreConfig.h"
#include "AmpBaseAndroidIF.h"


/***************************************************************************
* Perprocessor Defines
**************************************************************************/

/***************************************************************************
* Local Functions
**************************************************************************/
#define OPER_END_TRANSACTION 999

/***************************************************************************
* Globals
**************************************************************************/
static jobject	g_baseobj  = NULL;
static JavaVM* g_JavaVM = NULL;


JNIEXPORT void JNICALL
Java_AmpBaseInterface_AmpBaseInterface_Initialize
        (JNIEnv *env, jclass, jobject baseobj, jobject AmpCmpntobj, jobject contextobj)
{
    env->GetJavaVM(&g_JavaVM);
    g_baseobj = env->NewGlobalRef(baseobj);

    cAMPCmpnt *pAMPCmpnt = cAMPCmpnt::get_AMPCmpnt();
    pAMPCmpnt->Initialize(env, AmpCmpntobj, contextobj);
}

JNIEXPORT int JNICALL
Java_AmpBaseInterface_AmpBaseInterface_PerformTransaction
        (JNIEnv *, jclass, jlong transID)
{
    // critical error handler setup for the current transaction
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = CriticalErrorHandler;
    sa.sa_flags   = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);

    Purchase();
    PerformOperation(OPER_END_TRANSACTION);


    return AMP_SUCCESS;
}

int PerformOperation(int operID)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    int iRetVal;
    jclass myClass = 	env->FindClass("AmpBaseInterface/AmpBaseCBIF");
    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformOperation", "(I)I" );

    iRetVal = env->CallIntMethod(g_baseobj, myMethod, operID);

    AndroidDeleteObject(env, myClass);
    return iRetVal;
}

void PerformDisplayCardEntry(const char* szHeader, const char* szPromptLang1, const char* szPromptLang2, unsigned char bDisplayIcon)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    jstring jHeader = env->NewStringUTF(szHeader);
    jstring jPrompt1 = env->NewStringUTF(szPromptLang1);
    jstring jPrompt2 = env->NewStringUTF(szPromptLang2);

    jclass myClass = 	env->FindClass("AmpBaseInterface/AmpBaseCBIF");
    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformCardEntry",
                                          "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;C)V" );

    env->CallVoidMethod(g_baseobj, myMethod, jHeader, jPrompt1, jPrompt2, bDisplayIcon);

    AndroidDeleteObject(env, jHeader);
    AndroidDeleteObject(env, jPrompt1);
    AndroidDeleteObject(env, jPrompt2);
    AndroidDeleteObject(env, myClass);
}

void PerformDisplayOperation(const char* szHeader, const char* szPrompt1, const char* szPrompt2,
                             const char* szPrompt3, const char* szPrompt4, int iBeep, int iDelayMS)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    jclass myClass = env->FindClass("AmpBaseInterface/AmpBaseCBIF");
    jstring jHeader = env->NewStringUTF(szHeader);
    jstring jPrompt1 = env->NewStringUTF(szPrompt1);
    jstring jPrompt2 = env->NewStringUTF(szPrompt2);
    jstring jPrompt3 = env->NewStringUTF(szPrompt3);
    jstring jPrompt4 = env->NewStringUTF(szPrompt4);

    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformDisplayOperation", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;"
            "Ljava/lang/String;Ljava/lang/String;II)V" );

    env->CallVoidMethod(g_baseobj, myMethod, jHeader, jPrompt1, jPrompt2, jPrompt3, jPrompt4, iBeep, (iDelayMS));


    AndroidDeleteObject(env, jHeader);
    AndroidDeleteObject(env, jPrompt1);
    AndroidDeleteObject(env, jPrompt2);
    AndroidDeleteObject(env, jPrompt3);
    AndroidDeleteObject(env, jPrompt4);
    AndroidDeleteObject(env, myClass);
}

int PerformEntryOperation(const char* szHeader, const char* szPrompt1, const char* szPrompt2, int iMax,
                          int iMin, char* FieldFormat, char Mask, char* CurrSymbol, INPUT_METHOD InpMethod, char* szOutBuffer, int FontSize, int iTimeout)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    int iRetVal;
    jclass myClass = env->FindClass("AmpBaseInterface/AmpBaseCBIF");
    jstring jHeader = env->NewStringUTF(szHeader);
    jstring jPrompt1 = env->NewStringUTF(szPrompt1);
    jstring jPrompt2 = env->NewStringUTF(szPrompt2);
    jstring jFieldFormat = env->NewStringUTF(FieldFormat);
    jstring jCurrSymbol = env->NewStringUTF(CurrSymbol);
    jstring jInput = env->NewStringUTF(szOutBuffer);

    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformEntryOperation", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;"
            "IILjava/lang/String;CLjava/lang/String;ILjava/lang/String;II)I" );

    iRetVal = env->CallIntMethod(g_baseobj, myMethod, jHeader, jPrompt1, jPrompt2, iMax, iMin,
                                 jFieldFormat, Mask, jCurrSymbol, (int)(InpMethod), jInput, FontSize, (iTimeout*1000));

    AndroidDeleteObject(env, jHeader);
    AndroidDeleteObject(env, jPrompt1);
    AndroidDeleteObject(env, jPrompt2);
    AndroidDeleteObject(env, jFieldFormat);
    AndroidDeleteObject(env, jCurrSymbol);
    AndroidDeleteObject(env, myClass);
    return iRetVal;
}

int PerformEnterCancelOperation(const char* szHeader, const char* szPrompt1, const char* szPrompt2, const char* szPrompt3, const char* szPrompt4, int iBeep, int iTimeout)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    int iRetVal;
    jclass myClass = env->FindClass("AmpBaseInterface/AmpBaseCBIF");
    jstring jHeader = env->NewStringUTF(szHeader);
    jstring jPrompt1 = env->NewStringUTF(szPrompt1);
    jstring jPrompt2 = env->NewStringUTF(szPrompt2);
    jstring jPrompt3 = env->NewStringUTF(szPrompt3);
    jstring jPrompt4 = env->NewStringUTF(szPrompt4);

    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformEnterCancelOperation", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;"
            "Ljava/lang/String;Ljava/lang/String;II)I" );

    iRetVal = env->CallIntMethod(g_baseobj, myMethod, jHeader, jPrompt1, jPrompt2, jPrompt3, jPrompt4, iBeep, (iTimeout*1000));

    AndroidDeleteObject(env, jHeader);
    AndroidDeleteObject(env, jPrompt1);
    AndroidDeleteObject(env, jPrompt2);
    AndroidDeleteObject(env, jPrompt3);
    AndroidDeleteObject(env, jPrompt4);
    AndroidDeleteObject(env, myClass);

    return iRetVal;
}

int PerformCancelOperation(const char* szHeader, const char* szPrompt1, const char* szPrompt2, const char* szPrompt3, const char* szPrompt4, int iBeep, int iTimeout)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    int iRetVal;
    jclass myClass = env->FindClass("AmpBaseInterface/AmpBaseCBIF");
    jstring jHeader = env->NewStringUTF(szHeader);
    jstring jPrompt1 = env->NewStringUTF(szPrompt1);
    jstring jPrompt2 = env->NewStringUTF(szPrompt2);
    jstring jPrompt3 = env->NewStringUTF(szPrompt3);
    jstring jPrompt4 = env->NewStringUTF(szPrompt4);

    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformCancelOperation", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;"
            "Ljava/lang/String;Ljava/lang/String;II)I" );

    iRetVal = env->CallIntMethod(g_baseobj, myMethod, jHeader, jPrompt1, jPrompt2, jPrompt3, jPrompt4, iBeep, (iTimeout*1000));

    AndroidDeleteObject(env, jHeader);
    AndroidDeleteObject(env, jPrompt1);
    AndroidDeleteObject(env, jPrompt2);
    AndroidDeleteObject(env, jPrompt3);
    AndroidDeleteObject(env, jPrompt4);
    AndroidDeleteObject(env, myClass);

    return iRetVal;
}

char* PerformGetEntryValueOperation(void)
{
    JNIEnv *env;
    char* szRetVal = NULL;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    jclass myClass = env->FindClass("AmpBaseInterface/AmpBaseCBIF");
    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformGetEntryValueOperation", "()Ljava/lang/String;");

    jstring jstrValue = (jstring) env->CallObjectMethod(g_baseobj, myMethod);

    if(jstrValue != NULL)
        szRetVal = (char *) env->GetStringUTFChars(jstrValue, 0);

    AndroidDeleteObject(env, jstrValue);
    AndroidDeleteObject(env, myClass);

    return szRetVal;
}

int PerformSelectionOperation(const char *szHeader, const char* szPrompt1, const char* szPrompt2, int nSelectionButtons,
                              const char *szButtonMsg1, const char* szButtonMsg2, const char* szButtonMsg3, int iTimeout, int iBeep)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    int iRetVal;
    jclass myClass = env->FindClass("AmpBaseInterface/AmpBaseCBIF");
    jstring jHeader = env->NewStringUTF(szHeader);
    jstring jPrompt1 = env->NewStringUTF(szPrompt1);
    jstring jPrompt2 = env->NewStringUTF(szPrompt2);
    jstring jButtonMsg1 = env->NewStringUTF(szButtonMsg1);
    jstring jButtonMsg2 = env->NewStringUTF(szButtonMsg2);
    jstring jButtonMsg3 = env->NewStringUTF(szButtonMsg3);

    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformSelectionOperation", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;"
            "ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;II)I" );

    iRetVal = env->CallIntMethod(g_baseobj, myMethod, jHeader, jPrompt1, jPrompt2, nSelectionButtons,
                                 jButtonMsg1, jButtonMsg2, jButtonMsg3, (iTimeout*1000), iBeep);

    AndroidDeleteObject(env, jHeader);
    AndroidDeleteObject(env, jPrompt1);
    AndroidDeleteObject(env, jPrompt2);
    AndroidDeleteObject(env, jButtonMsg1);
    AndroidDeleteObject(env, jButtonMsg2);
    AndroidDeleteObject(env, jButtonMsg3);
    AndroidDeleteObject(env, myClass);

    return iRetVal;
}

int PerformChoiceSelectionOperation(const char *szTitle, char CardTypeLabels[][MAX_STR_SZ+1], int NumChoices, int DefaultSelection)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    int iRetVal;
    jstring jstrtemp, jTitle;
    jclass myClass = env->FindClass("AmpBaseInterface/AmpBaseCBIF");

    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformChoiceSelectionOperation", "(Ljava/lang/String;[Ljava/lang/String;I)I" );
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray jCardTypeLabels = env->NewObjectArray(NumChoices, stringClass, 0);
    env->DeleteLocalRef(stringClass);

    jTitle = env->NewStringUTF(szTitle);

    for(int i=0; i < NumChoices; i++) {
        jstrtemp = env->NewStringUTF(CardTypeLabels[i] );
        env->SetObjectArrayElement(jCardTypeLabels, i, jstrtemp);
        env->DeleteLocalRef(jstrtemp);
    }

    iRetVal = env->CallIntMethod(g_baseobj, myMethod, jTitle, jCardTypeLabels, DefaultSelection);

    AndroidDeleteObject(env, jTitle);
    AndroidDeleteObject(env, jCardTypeLabels);
    AndroidDeleteObject(env, myClass);

    return iRetVal;
}

int PerformDisplayPassTerminal(const char* szHeader, const char* szPrompt1, const char* szPrompt2, BOOL bWaitForKey)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    int iRetVal;
    jclass myClass = env->FindClass("AmpBaseInterface/AmpBaseCBIF");

    jmethodID myMethod = env->GetMethodID(myClass, "BaseCBPerformDisplayPassTerminal", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;C)I" );
    jstring jHeader = env->NewStringUTF(szHeader);
    jstring jPrompt1 = env->NewStringUTF(szPrompt1);
    jstring jPrompt2 = env->NewStringUTF(szPrompt2);
    iRetVal = env->CallIntMethod(g_baseobj, myMethod, jHeader, jPrompt1, jPrompt2, bWaitForKey);

    AndroidDeleteObject(env, jHeader);
    AndroidDeleteObject(env, jPrompt1);
    AndroidDeleteObject(env, jPrompt2);
    AndroidDeleteObject(env, myClass);

    return iRetVal;
}

void AndroidReleaseString(JNIEnv* env, jstring jniString, const char* strValue)
{
    if((jniString != NULL) && (strValue != NULL)) {
        env->ReleaseStringUTFChars(jniString, strValue);
        env->DeleteLocalRef(jniString);
    }
}

void AndroidDeleteObject(JNIEnv* env, jobject jobj)
{
    if(jobj != NULL)
        env->DeleteLocalRef(jobj);
}

void AndroidDeleteObject(JNIEnv* env, jstring jobj)
{
    if(jobj != NULL)
        env->DeleteLocalRef(jobj);
}

void AndroidDeleteObject(JNIEnv* env, jbyteArray jobj)
{
    if(jobj != NULL)
        env->DeleteLocalRef(jobj);
}

void AndroidReleaseByteArray(JNIEnv* env, jbyteArray jbyteObj, jbyte* byteVal)
{
    if((jbyteObj != NULL) && (byteVal != NULL))
        env->ReleaseByteArrayElements(jbyteObj, byteVal, JNI_ABORT);
}

void CriticalErrorHandler(int signal, siginfo_t *si, void *arg)
{
    // TODO: JNI calls to Java will not work as java calls are not async-signal-safe
    //
    // My suggestion is redirect the stack trace to /data/data/com.amobilepayment.tsys/files/crash/error.log.
    // App will look for this file on every activity load as a sign of native crash.
    // If error.log is present, apologise to user then send the log to us.
    // Delete the log file after to signify successful crash handling.
    exit(EXIT_FAILURE);
}