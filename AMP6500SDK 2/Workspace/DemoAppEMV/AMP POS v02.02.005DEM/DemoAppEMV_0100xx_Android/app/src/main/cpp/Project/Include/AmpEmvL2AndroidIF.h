#ifndef AMPAGNOSANDROID_H_
#define AMPAGNOSANDROID_H_

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
* File       	 : 		AMPAgnosAndroidIF.h
* Library	 	 : 		AMPEMVL2
* Date Coded  : 		09/18/2017
**************************************************************************/

#include <jni.h>

#ifdef __cplusplus
extern "C"
{
#endif

//! Initialize AMPEMVL2 Framework
JNIEXPORT void JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_InitAmpEmvL2
	(JNIEnv *, jclass, jobject, jstring AgnosInitPath, jstring AgnosConfigPath, jstring AgnosLibPath);

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvCardEntryPolling
	(JNIEnv *, jclass, jlong TimeOut);

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvReadMagstripe(JNIEnv *env, jclass type);

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpCloseDevices(JNIEnv *env, jclass type);

//! Set Tag Collections
JNIEXPORT void JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvSetTagCollection
	(JNIEnv *, jclass, jbyteArray TagList, jint TagListLen);

//! Get TLV Tag Collection Result
JNIEXPORT jbyteArray JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvGetTagColData
	(JNIEnv *, jclass);

//! Get Tag Value
JNIEXPORT jbyteArray JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvGetTagData
	(JNIEnv *, jclass, jlong TagName);

//! Get AID Info
JNIEXPORT jbyteArray JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvGetAIDInfo
	(JNIEnv *, jclass);

//! Get Trans Category Code
JNIEXPORT jbyteArray JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvGetTransCategoryCode
		(JNIEnv *, jclass);

//2 EMV Transaction Flow API

JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvInitTrans
	(JNIEnv *, jclass, jint);

//! Select Application, Language, Initiate to 1stGenAC
JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvInitiateFlow
	(JNIEnv *, jclass);


//! 2nd GenAC
JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvCompletion
	(JNIEnv *, jclass);

//2 EMV Contactless Flow API

//! Execute Entry Point
JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvCtlsInitiateFlow
	(JNIEnv *, jclass);

//! 2nd GenAC
JNIEXPORT jint JNICALL Java_AmpEmvL2Android_AmpEmvL2IF_AmpEmvCtlsCompletion
	(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif

#endif