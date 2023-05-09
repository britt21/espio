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
* File       	 : 		AMPAgnosAndroidIF.cpp
* Library	 	 : 		AMPEMVL2
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
#include "AMPAgnosEMV.h"
#include "AMPReturnCodes.h"
#include "AMPEmvSizes.h"
#include "CoreAgnosEMVTrans.h"
#include "CoreAgnosEmvFunc.h"
#include "CoreAgnosEmvCtlsFunc.h"
#include "CoreTransObj.h"
#include "CoreCardUtils.h"
#include <android/log.h>
#include "AmpEmvL2AndroidIF.h"
#include "AmpBaseAndroidIF.h"
#include "android_adapter.h"
#include <sep.h>
#include <gpihsm.h>
#include <CoreScreens.h>

/***************************************************************************
* Perprocessor Defines
**************************************************************************/

#define DEVCARD_MSR		(1<<0)
#define DEVCARD_CTLS	(1<<1)
#define DEVCARD_ICC		(1<<2)
#define DEVCARD_MANUAL	(1<<3)
#define DEVCARD_ALL		(DEVCARD_MSR|DEVCARD_CTLS|DEVCARD_ICC|DEVCARD_MANUAL)


#define PIN_SUCCESS             0
#define PIN_CANCEL              2014    /*ENTER_CANCEL*/
#define PIN_TIMEOUT             2015    /*TIMEOUT*/
#define PIN_ERROR               2002    /*ERROR*/
#define PIN_NOT_ENTERED         2013    /*NO_PIN*/

/***************************************************************************
* Local Functions
**************************************************************************/
cTransObj1* g_TransObj1 = new cTransObj1();
unsigned short	AgnosCBDisplayMessage(unsigned char bClearScreen, unsigned char LangId, const char *szMessage, unsigned char MessageId);
unsigned short	AgnosCBSelectItemFromList(const char *arrItems[], unsigned char arrCount, const char *Title, int TimeOut, unsigned char *SelectedId);
unsigned short	AgnosCBGpiSwitchLED (unsigned char Led, unsigned char Flag, unsigned char Colour);
void			AgnosCBDisplayPinEntryPrompt (unsigned char bClearScreen, unsigned char LangId, const char *szMessage);
unsigned short	AgnosCBOnlinePinEntry (const char *PAN, int PANlen, unsigned char *PinBlock, int *PinBlockLen);
unsigned short  AgnosOfflinePinEntry (char bEnciphered, unsigned int lan, int timeout, tEMVPubKey* pubkey, unsigned char *IccRandom, unsigned char *RespData);
unsigned short	PerformAgnosCBDisplayMessage(const char *szMessage, int beep, int timeout);

/***************************************************************************
* Globals
**************************************************************************/
static AMPAGNOS_CB gAgnosCB =
{
		NULL,		// AgnosCBAppSelection

		NULL,		//AgnosCBLangSelection

		AgnosCBDisplayMessage,

		AgnosCBSelectItemFromList,

		AgnosCBGpiSwitchLED,

		AgnosCBDisplayPinEntryPrompt,

		AgnosCBOnlinePinEntry,

        NULL,
		NULL,
		NULL,
		NULL,
        AgnosOfflinePinEntry
};

static jobject	g_obj  = NULL;
static JavaVM* g_JavaVM = NULL;

/***************************************************************************
* JNI Functions
**************************************************************************/

//! Initialize AMPEMVL2 Framework
JNIEXPORT void JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_InitAmpEmvL2
	(JNIEnv *env, jclass, jobject m_obj, jstring AgnosIniPath, jstring AgnosConfigPath, jstring)
{

    const char *pAgnosIniPath = env->GetStringUTFChars(AgnosIniPath, 0);
    const char *pAgnosConfigPath = env->GetStringUTFChars(AgnosConfigPath, 0);
    const char *pAgnosLibPath = "";

	InitAmpEmvL2(pAgnosIniPath, pAgnosConfigPath, pAgnosLibPath, &gAgnosCB);
    env->GetJavaVM(&g_JavaVM);
    g_obj = env->NewGlobalRef(m_obj);

    //Agnos library
    jni_init(env, m_obj);
    setListenerClass("AmpEmvL2Android/AmpEmvCBIF");

    cAMPAgnos *pAgnos = cAMPAgnos::get_Instance();
    pAgnos->SetCTLSDetectDelayTimeOut(1500);

    AndroidReleaseString(env, AgnosIniPath, pAgnosIniPath);
    AndroidReleaseString(env, AgnosConfigPath, pAgnosConfigPath);
}

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvCardEntryPolling
	(JNIEnv *, jclass, jlong TimeOut)
{
    cAMPAgnos *pAgnos = cAMPAgnos::get_Instance();
    unsigned short ucReadKey = 0;

    pAgnos->SetSupprtdCardEntry(DEVCARD_CTLS|DEVCARD_ICC|DEVCARD_MSR);

    return  pAgnos->CardEntryPolling((unsigned int) TimeOut, &ucReadKey);
}

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvReadMagstripe
        (JNIEnv *, jclass)
{
    cAMPAgnos *pAgnos = cAMPAgnos::get_Instance();
    int iRetVal = AMP_ERROR;

#ifdef ENCRYPT_SENSITIVE_DATA
	CARD_TRACK_DATA *pCardData = pAgnos->GetCardTrackData(CARD_ENTRY_SWIPE);
	if(pCardData != NULL)
	{
		memcpy(TRANS_OBJ1->szTrack1, pCardData->Track1Masked, strlen(pCardData->Track1Masked));
		memcpy(TRANS_OBJ1->szTrack2, pCardData->Track2Masked, strlen(pCardData->Track2Masked));
		memcpy(TRANS_OBJ1->szTrack1Enc, pCardData->Track1Encrypt, strlen(pCardData->Track1Encrypt));
		memcpy(TRANS_OBJ1->szTrack2Enc, pCardData->Track2Encrypt, strlen(pCardData->Track2Encrypt));

		//Check if track 2 data is present
		if (strlen((char*)TRANS_OBJ1->szTrack2) != 0) {
			PutMSRTrackDataToTransObj(TRANS_OBJ1);
			iRetVal = AMP_SUCCESS;
		}
		else
			iRetVal = AMP_ERROR;
	}
#else
    unsigned char byTrack1[255] = {0};
    unsigned char byTrack2[255] = {0};
    unsigned char byTrack3[255] = {0};
    int Track1Len = 0;
    int Track2Len = 0;
    int Track3Len = 0;

    iRetVal = pAgnos->ReadMagstripe(byTrack1, &Track1Len, byTrack2, &Track2Len, byTrack3,
                                     &Track3Len);

    ClearMSRTrackData(TRANS_OBJ1);

    if(Track1Len > 0)
        memcpy(TRANS_OBJ1->szTrack1, byTrack1, sizeof(byTrack1));
    if(Track2Len > 0)
        memcpy(TRANS_OBJ1->szTrack2, byTrack2, sizeof(byTrack2));

    if(Track3Len > 0)
        memcpy(TRANS_OBJ1->szTrack3, byTrack3, sizeof(byTrack3));

    PutMSRTrackDataToTransObj(TRANS_OBJ1);
#endif

    return iRetVal;
}

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpCloseDevices
        (JNIEnv *, jclass)
{
    cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();

    return pAgnosEmv->CloseGpiDeviceReader(DEVICE_CARD_ALL);
}


JNIEXPORT void JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvSetTagCollection
	(JNIEnv *env, jclass, jbyteArray TagList, jint TagListLen)
{
    jbyte *pTagList = env->GetByteArrayElements(TagList, NULL);
    unsigned char* m_TagList = (unsigned char*)malloc(TagListLen*sizeof(unsigned char));

    for(int i = 0; i<TagListLen; i++)
        m_TagList[i] = (unsigned char)pTagList[i];

    cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();
    pAgnosEmv->SetTagListCollection(m_TagList, TagListLen);

    AndroidReleaseByteArray(env, TagList, pTagList);
}


JNIEXPORT jbyteArray JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvGetTagColData
	(JNIEnv *env, jclass)
{
	int iLen = 0;
    BYTE *TlvStream = (BYTE*)malloc(sizeof(BYTE)*MAX_STREAM_SIZE);
    memset(TlvStream, 0, sizeof(BYTE)*MAX_STREAM_SIZE);

    cAMPAgnos *pAgnos = cAMPAgnos::get_Instance();
    iLen = pAgnos->GetEMVTlvData( TlvStream, MAX_STREAM_SIZE );

    jbyteArray result;
    if(iLen > 0){
        result = env->NewByteArray(iLen);
        env->SetByteArrayRegion(result, 0, iLen, (jbyte*)TlvStream);
    } else {
        result = env->NewByteArray(0);
    }

    free(TlvStream);
    return result;
}


JNIEXPORT jbyteArray JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvGetTagData
	(JNIEnv *env, jclass, jlong TagName)
{
	int iLen = 0;
    BYTE *TagValue = (BYTE*)malloc(sizeof(BYTE)*EMV_MAX_DATA_SIZE);
    memset(TagValue, 0, sizeof(BYTE)*EMV_MAX_DATA_SIZE);

    cAMPAgnos *pAgnos= cAMPAgnos::get_Instance();
    iLen = pAgnos->EmvGetTag((unsigned long) TagName, TagValue, EMV_MAX_DATA_SIZE);

    jbyteArray result;
    if(iLen > 0){
        result = env->NewByteArray(iLen);
        env->SetByteArrayRegion(result, 0, iLen, (jbyte*)TagValue);
    } else {
        result = env->NewByteArray(0);
    }

    free(TagValue);
	return result;
}

JNIEXPORT jbyteArray JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvGetAIDInfo
    (JNIEnv *env, jclass)
{
    int iLen = 0;
    BYTE *TagValue = (BYTE*)malloc(sizeof(BYTE)*EMV_MAX_DATA_SIZE);
    memset(TagValue, 0, sizeof(BYTE)*EMV_MAX_DATA_SIZE);

    cAMPAgnos *pAgnos= cAMPAgnos::get_Instance();
    iLen =  pAgnos->EmvGetAIDInfo(TagValue, EMV_MAX_DATA_SIZE);

    jbyteArray result;
    if(iLen > 0){
        result = env->NewByteArray(iLen);
        env->SetByteArrayRegion(result, 0, iLen, (jbyte*)TagValue);
    } else {
        result = env->NewByteArray(0);
    }

    free(TagValue);
    return result;
}

JNIEXPORT jbyteArray JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvGetTransCategoryCode
        (JNIEnv *env, jclass)
{
    int iLen = 0;
    BYTE *TagValue = (BYTE*)malloc(sizeof(BYTE)*EMV_MAX_DATA_SIZE);
    memset(TagValue, 0, sizeof(BYTE)*EMV_MAX_DATA_SIZE);

    cAMPAgnos *pAgnos= cAMPAgnos::get_Instance();
    iLen = pAgnos->EmvGetTransCategoryCode(TagValue, EMV_MAX_DATA_SIZE);

    jbyteArray result;
    if(iLen > 0){
        result = env->NewByteArray(iLen);
        env->SetByteArrayRegion(result, 0, iLen, (jbyte*)TagValue);
    } else {
        result = env->NewByteArray(0);
    }

    free(TagValue);
    return result;
}

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvInitTrans
        (JNIEnv *, jclass, jint AgnosTransType)
{
    cAMPAgnos *pAgnos= cAMPAgnos::get_Instance();

    return pAgnos->InitTrans((AGN_TRANS_TYPE)AgnosTransType);
}

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvInitiateFlow
	(JNIEnv *, jclass)
{
    return DoAgnosEmvInitiateFlow(TRANS_OBJ1);
}

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvCompletion
	(JNIEnv *, jclass)
{
	return DoAgnosEmvCompletion(TRANS_OBJ1);
}

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvCtlsInitiateFlow
	(JNIEnv *, jclass)
{
    return DoAgnosEmvCtlsInitiateFlow(TRANS_OBJ1);
}

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvCtlsCompletion
	(JNIEnv *, jclass)
{
    return DoAgnosEmvCtlsCompletion(TRANS_OBJ1);
}

/***************************************************************************
* Native Functions
**************************************************************************/
unsigned short	AgnosCBDisplayMessage
        (unsigned char, unsigned char LangId, const char *szMessage, unsigned char MessageId)
{

    int iRetVal = admNO_ERROR;
    char szHeader[MAX_HEADER_SIZE+1] = { 0 };
    int TagDataLen = 0;
    BYTE TagData[EMV_MAX_DATA_SIZE];
    cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();

    if((MessageId != 0x03) &&	// 0x03 - Approved Message ( Handled by DoDisplayHostRespCode(TRANS_OBJ) )
       (MessageId != 0x07) &&	// 0x07 - Declined Message ( Handled by DoDisplayHostRespCode(TRANS_OBJ) )
       (MessageId != 0x84)	&&  // 0x84 - Cancel Message ( Handled by DoCardEntry() )
       (MessageId != 0xFF))	// 0xFF - Language Not Found (e.g. Card Balance - should not be shown)
    {
        if(MessageId == 0x1E)
        {
            // Agnos Library Limitation: Kernel always return "REMOVE CARD" instead of "CARD READ OK - REMOVE CARD" if Ctls card was successfully read
            if((LangId == 0x00) || (LangId == 0x01)  || (LangId == 0x06) || (LangId == 0x07))
                PerformAgnosCBDisplayMessage("CARD READ OK - REMOVE CARD", BEEP_NONE, 1000);
            else
                PerformAgnosCBDisplayMessage(szMessage, BEEP_NONE, 1000);
        }
        else if((MessageId == 0x10) || // 0x10 - Remove Card for Contact Transactions
                (MessageId == 0x19) || // 0x19 - Present One Card Only
                (MessageId == 0x22)	|| // 0x22 - Insert/Swipe/Try Other Card
                (MessageId == 0x0A) || // 0x0A - Incorrect PIN
                (MessageId == 0x23)	)  // 0x23 - Last Pin Try
        {
            PerformAgnosCBDisplayMessage(szMessage, BEEP_WARN, 1000);
        }
        else if(MessageId == 0x20)	// 0x20 - See Phone (Hold time should be set to 13 seconds)
        {
            PerformAgnosCBDisplayMessage(szMessage, BEEP_NONE, 13000);
        }
        else if(MessageId == 0x13)	// 0x13 - Try Again
        {
            PerformAgnosCBDisplayMessage(szMessage, BEEP_NONE, 0);
        }
        else if((MessageId == 0x1C) && 	// 0x1C - Error Use Another Card
                (!pAgnosEmv->IsCardBlocked()) && // Unknown AID Checking
                (pAgnosEmv->IsMutualListEmpty()))
        {
            PerformAgnosCBDisplayMessage("NOT ACCEPTED", BEEP_WARN, 1000);
        }
        else
        {
            PerformAgnosCBDisplayMessage(szMessage, BEEP_NONE, 1000);
        }
    }

    // Not Accepted Message if TVR Requested service not allowed for card product
    TagDataLen = pAgnosEmv->EmvGetTag(0x95, TagData, sizeof(TagData));

    if((MessageId == 0x07) &&
       (((TagDataLen = pAgnosEmv->EmvGetTag(0x95, TagData, sizeof(TagData))) > 0) &&
        ((TagData[1] & 0xF0) == 0x10))
            )
    {
        PerformAgnosCBDisplayMessage("NOT ACCEPTED", BEEP_WARN, 1000);
    }

    return (unsigned short) iRetVal;
}

unsigned short	PerformAgnosCBDisplayMessage(const char *szMessage, int beep, int timeout)
{

    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    jstring strMessage = env->NewStringUTF(szMessage);
	jclass myClass = 	env->FindClass("AmpEmvL2Android/AmpEmvCBIF");
	jmethodID myMethod = env->GetMethodID(myClass, "AgnosCBDisplayMessage", "(Ljava/lang/String;II)V" );

	env->CallVoidMethod(g_obj, myMethod, strMessage, beep, timeout);
    AndroidDeleteObject(env, strMessage);
	AndroidDeleteObject(env, myClass);

	return admNO_ERROR;
}

unsigned short	AgnosCBSelectItemFromList
        (const char *arrItems[], unsigned char arrCount, const char *Title, int, unsigned char *SelectedId)
{

    unsigned short iRetVal;
	int selected = 0;

    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

	jstring strTitle = env->NewStringUTF(Title);
    jstring str;

    jobjectArray objItems = 0;
    int i=0;

    jclass myClass = env->FindClass("AmpEmvL2Android/AmpEmvCBIF");
    objItems = env->NewObjectArray(arrCount, env->FindClass("java/lang/String"), 0);

    for(i=0; i<arrCount; i++) {
        str = env->NewStringUTF(arrItems[i]);
        env->SetObjectArrayElement(objItems, i, str);
    }

    jmethodID myMethod = env->GetMethodID(myClass, "AgnosCBSelectItemFromList", "(Ljava/lang/String;[Ljava/lang/String;)I" );
	selected = env->CallIntMethod(g_obj, myMethod, strTitle, objItems);

    if(selected < 0) {
        iRetVal = lstCANCEL;
    } else {
        *SelectedId =selected;
        iRetVal=lstNO_ERROR;
    }

    AndroidDeleteObject(env, strTitle);
    AndroidDeleteObject(env, objItems);
    AndroidDeleteObject(env, myClass);
	return iRetVal;
}

unsigned short	AgnosCBGpiSwitchLED (unsigned char Led, unsigned char Flag, unsigned char Colour)
{
    unsigned short iRetVal = admNO_ERROR;

    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    jclass myClass = 	env->FindClass("AmpEmvL2Android/AmpEmvCBIF");
	jmethodID myMethod = env->GetMethodID(myClass, "AgnosCBGpiSwitchLED", "(BBB)V" );

	env->CallVoidMethod(g_obj, myMethod, Led, Flag, Colour);

	AndroidDeleteObject(env, myClass);
	return iRetVal;
}


void AgnosCBDisplayPinEntryPrompt (unsigned char bClearScreen, unsigned char LangId, const char *szMessage)
{
    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    jstring strMessage = env->NewStringUTF(szMessage);

    jclass myClass = 	env->FindClass("AmpEmvL2Android/AmpEmvCBIF");
	jmethodID myMethod = env->GetMethodID(myClass, "AgnosCBDisplayPinEntryPrompt", "(Ljava/lang/String;)V" );

	env->CallVoidMethod(g_obj, myMethod, strMessage);
    AndroidDeleteObject(env, strMessage);
    AndroidDeleteObject(env, myClass);
}

unsigned short	AgnosCBOnlinePinEntry (const char *PAN, int PANlen, unsigned char *PinBlock, int *PinBlockLen)
{
    int iRetVal = AMP_SUCCESS;
    cAMPAgnosEmv *pAgnosEmv = cAMPAgnosEmv::get_Instance();

    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);

    __android_log_print(ANDROID_LOG_INFO, "EMVL2", "AgnosCBOnlinePinEntry");

    jclass myClass = 	 env->FindClass("AmpEmvL2Android/AmpEmvCBIF");
    jmethodID myMethod = env->GetMethodID(myClass, "AgnosCBOnlinePinEntry", "([BI)I" );
    jmethodID PinBlkMethod = env->GetMethodID(myClass, "AgnosGetPinBlock", "()[B");

    jbyteArray retArray = env->NewByteArray(PANlen);

    void *temp = env->GetPrimitiveArrayCritical(retArray, 0);
    memcpy(temp, PAN, PANlen);

    env->ReleasePrimitiveArrayCritical(retArray, temp,0);

    iRetVal = env->CallIntMethod(g_obj, myMethod, retArray, PANlen);

    __android_log_print(ANDROID_LOG_INFO, "EMVL2", "AgnosCBOnlinePinEntry iRetVal[%d]", iRetVal);

    switch(iRetVal)
    {
        case PIN_SUCCESS: {
            jbyteArray PinBlk = (jbyteArray) env->CallObjectMethod(g_obj, PinBlkMethod);
            jbyte *bPinBlk = env->GetByteArrayElements(PinBlk, NULL);
            memcpy(PinBlock, bPinBlk, 8);
            *PinBlockLen = 8;
            AndroidDeleteObject(env, PinBlk);
            iRetVal = sepNO_ERROR;
            break;
        }
        case PIN_NOT_ENTERED:
            iRetVal = sepPIN_NOT_ENTERED;
            break;
        case PIN_CANCEL:
            iRetVal = sepCANCEL;
            pAgnosEmv->EmvSetExitStateFlow(asCVM);
            break;
        case PIN_TIMEOUT:
            iRetVal = sepTIME_OUT;
            pAgnosEmv->EmvSetExitStateFlow(asCVM);
            break;
        case PIN_ERROR:
        default:
            iRetVal = sepPROCESS_FAILED;
            break;
    }

    AndroidDeleteObject(env, retArray);
    AndroidDeleteObject(env, myClass);
    
    return iRetVal;
}

unsigned short  AgnosOfflinePinEntry (char bEnciphered, unsigned int lan, int timeout, tEMVPubKey* pubkey, unsigned char *IccRandom, unsigned char *RespData)
{
    int iRetVal = AMP_SUCCESS;

    JNIEnv *env;
    g_JavaVM->GetEnv((void**)&env, JNI_VERSION_1_6);


    jclass myClass = 	env->FindClass("AmpEmvL2Android/AmpEmvCBIF");
    jmethodID myMethodPinEntry = env->GetMethodID(myClass, "AgnosCBOfflinePinEntry", "(BII[BB[BB[B)I" );
    jmethodID myMethodGetRspCode = env->GetMethodID(myClass, "AgnosCBGetEMVResponseCode", "()[B");
    jbyteArray jbRespData = env->NewByteArray(2);

    if(bEnciphered == 1)
    {
        jbyteArray jbModulus = env->NewByteArray((jint)pubkey->modulusLn);
        env->SetByteArrayRegion(jbModulus, 0, (jint)pubkey->modulusLn, (jbyte *) pubkey->modulus);

        jbyteArray jbExponent = env->NewByteArray((jint)pubkey->exponentLn);
        env->SetByteArrayRegion(jbExponent, 0, (jint)pubkey->exponentLn, (jbyte *) pubkey->exponent);

        jbyteArray jbIccRandom = env->NewByteArray(8);
        env->SetByteArrayRegion(jbIccRandom, 0, 8, (jbyte *) IccRandom);


        iRetVal = env->CallIntMethod(g_obj, myMethodPinEntry, bEnciphered, lan, timeout, jbModulus, pubkey->modulusLn, jbExponent, pubkey->exponentLn,
                                        jbIccRandom);

        AndroidDeleteObject(env, jbModulus);
        AndroidDeleteObject(env, jbExponent);
        AndroidDeleteObject(env, jbIccRandom);

    } else {
        iRetVal = env->CallIntMethod(g_obj, myMethodPinEntry, bEnciphered, lan, timeout, NULL, 0, NULL, 0, NULL);
    }

    if (iRetVal == 0)
        jbRespData = (jbyteArray) env->CallObjectMethod(g_obj, myMethodGetRspCode);

    jbyte *pRespData = env->GetByteArrayElements(jbRespData, NULL);
    memcpy(RespData, pRespData, 2);

    AndroidDeleteObject(env, jbRespData);
    AndroidDeleteObject(env, myClass);

    return iRetVal;
}
