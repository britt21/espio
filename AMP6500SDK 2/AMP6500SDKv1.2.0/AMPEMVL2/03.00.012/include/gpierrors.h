// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpierrors.h
// PURPOSE....  Generic Platform Interface - Encoding of GPI errors
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPIERRORS_H_
#define GPIERRORS_H_

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//      INCLUDES
//==================================================================================================================

//==================================================================================================================
//      MACROS + DEFINES
//==================================================================================================================
////////////////////////////////////////////////
// Errors' Module encoding
// Module	0 0		= GPI 
// Module	0 1 	= Agnos
// Module	1 0 	= Atmos
// Module	1 1 	= Payment (Application level)

// Errors' Severity encoding
// Severity	0 0		= Event 
// Severity	0 1 	= EMV error
// Severity	1 0 	= System error
// Severity	1 1 	= RFU

typedef unsigned short	tGPIError;

////////////////////////////////////////////////
// GPI Errors for Interface to card reader
//			HIGH BYTE			LOW BYTE
// Module	0 0 
// Interface   0 0 0 0 0 0
// Severity						x x 
// Code                            x x x x x x
#define scrNO_ERROR						0x0000
#define scrCARD_INSERTED				0x0001
#define scrAPDU_ERROR					0x0040
#define scrSYSTEM_ERROR					0x0080
#define scrINTERRUPTED					0x00A0

////////////////////////////////////////////////
// GPI Errors for Interface to logger
//			HIGH ERROR			LOW ERROR
// Module	0 0 
// Interface   0 0 0 0 0 1
// Severity						x x 
// Code        						x x	x x x x
#define logNO_ERROR						0x0100
#define logSYSTEM_ERROR					0x0180

////////////////////////////////////////////////
// GPI Errors for Interface to administration
//			HIGH ERROR			LOW ERROR
// Module	0 0 
// Interface   0 0 0 0 1 0
// Severity						x x 
// Code                            x x x x x x
#define admNO_ERROR						0x0200
#define admSYSTEM_ERROR					0x0280
#define admNOT_IMPLEMENTED				0x0281
#define admNOT_SUPPORTED				0x0282

////////////////////////////////////////////////
// GPI Errors for Interface to cryptographic
//			HIGH ERROR			LOW ERROR
// Module	0 0 
// Interface   0 0 0 0 1 1
// Severity						x x 
// Code                             x x	x x x x
#define	cryNO_ERROR						0x0300
#define	cryRSA_MODLN					0x0341 // Public key modulus length too big
#define	cryRSA_EXPLN					0x0342 // Public key exponent length too big
#define	cryRSA_DATA						0x0343 // Data greater than key modulus
#define	cryNOT_FOUND					0x0344
#define	cryFOUND						0x0345
#define	cryERROR						0x0346

////////////////////////////////////////////////
// GPI Errors for Interface to PIN management
//			HIGH ERROR			LOW ERROR
// Module	0 0 
// Interface   0 0 0 1 0 0
// Severity						x x 
// Code         					x x	x x x x
#define	pinNO_ERROR						0x0400
#define	pinPINPAD_MALFUNCTIONING		0x0441
#define	pinPIN_BLOCK_RECOVERY_FAILED    0x0442
#define	pinNO_REMAINING_PIN_TRIES		0x0443
#define	pinPIN_BLOCKED					0x0444
#define	pinPROCESSFAILED				0x0445
#define	pinBYPASS       				0x0446
#define	pinABORT               			0x0447
#define	pinTIMEOUT                      0x0448
#define	pinPIN_ENTERED                  0x0449
#define	pinRANDOM_NUMBER_ERROR          0x0450

////////////////////////////////////////////////
// GPI Errors for Interface to magstripe reader
//			HIGH ERROR			LOW ERROR
// Module	0 0 
// Interface   0 0 0 1 0 1
// Severity						x x 
// Code        						x x	x x x x
#define	msrNO_ERROR						0x0500
#define	msrNO_SWIPE						0x0501
#define msrCARD_SWIPED					0x0502
#define	msrSYSTEM_ERROR					0x0580

////////////////////////////////////////////////
// GPI Errors for Interface to file management
//			HIGH ERROR			LOW ERROR
// Module	0 0 
// Interface        0 0 0 1 1 0 	
// Severity						x x 
// Code                             x x	x x x x
#define	filNO_ERROR						0x0600
#define	filNOT_FOUND					0x0601
#define	filALREADY_OPENED				0x0602
#define filFAILURE                      0x0603
#define	filSYSTEM_ERROR					0x0680

////////////////////////////////////////////////
// GPI Errors for Interface to key management
//			HIGH ERROR			LOW ERROR
// Module	0 0 
// Interface   0 0 0 1 1 1
// Severity						x x 
// Code         					x x	x x x x
#define	keyNO_ERROR						0x0700
#define	keyNOT_LOADED					0x0701
#define	keyOUT_OF_RANGE					0x0702
#define	keyNO_PRIVILEGE					0x0703
#define	keyNOT_FOR_MAC					0x0704
#define	keyCORRUPTED					0x0705
#define	keyTYPE_ERROR					0x0706
#define	keySYSTEM_ERROR					0x0780

////////////////////////////////////////////////
// GPI Errors for Interface to Ethernet
//			HIGH ERROR			LOW ERROR
// Module	0 0 
// Interface    0 0 1 0 0 0
// Severity						x x 
// Code                            x x x x x x
#define	ethNO_ERROR						0x0800
#define	ethUNABLE_TO_REACH_HOST			0x0801
#define	ethNO_TRANSMISSION				0x0802
#define	ethNO_RECEPTION                 0x0803
#define	ethUNABLE_TO_CONNECT			0x0804
#define	ethTIMEOUT						0x0805
#define	ethSYSTEM_ERROR					0x0880

////////////////////////////////////////////////
// GPI Errors for Interface to SSL
//			HIGH ERROR			LOW ERROR
// Module	0 0
// Interface    0 0 1 0 0 1
// Severity						x x
// Code                            x x x x x x
#define	sslNO_ERROR						0x0900
#define	sslBIO_OBJECT_ERROR				0x0901
#define	sslCONNECTION_ERROR				0x0902
#define	sslHANDSHAKE_ERROR				0x0903
#define	sslNO_DATA_ERROR				0x0904
#define	sslREAD_FAILED_ERROR			0x0905
#define	sslSYSTEM_ERROR					0x0980

////////////////////////////////////////////////
// GPI Errors for Interface to contacless card reader
//			HIGH ERROR			LOW ERROR
// Module	0 0
// Interface    0 0 1 0 1 0
// Severity						x x
// Code                            x x x x x x
#define	clcNO_ERROR						0x0A00
#define clcCARD_PRESENTED				0x0A01
#define	clcEMV_CARD						0x0A02
#define	clcCOLLISION					0x0A03
#define	clcOTHER_CARD					0x0A04
#define	clcSYSTEM_ERROR					0x0A80

////////////////////////////////////////////////
// GPI Errors for Interface to INI Services
//			HIGH ERROR			LOW ERROR
// Module	0 0
// Interface    0 0 1 0 1 1
// Severity						x x
// Code                            x x x x x x
#define iniNO_ERROR						0x0B00
#define iniUPDATE_ERROR					0x0B01
#define iniCALLBACK_ERROR				0x0B02

////////////////////////////////////////////////
// GPI Errors for Interface to Technology Polling
//			HIGH ERROR			LOW ERROR
// Module	0 0
// Interface    0 0 1 1 0 0
// Severity						x x
// Code                            x x x x x x
#define polNO_ERROR						0x0C00
#define polTIMEOUT						0x0C01
#define polSYSTEM_ERROR					0x0C80

////////////////////////////////////////////////
// GPI Errors for Interface to List Selection
//			HIGH ERROR			LOW ERROR
// Module	0 0
// Interface    0 0 1 1 0 1
// Severity						x x
// Code                            x x x x x x
#define lstNO_ERROR						0x0D00
#define lstTIMEOUT						0x0D01
#define lstCANCEL						0x0D02
#define lstSYSTEM_ERROR					0x0D80

////////////////////////////////////////////////
// GPI Errors for Interface to Platform
//			HIGH ERROR			LOW ERROR
// Module	0 0
// Interface    0 0 1 1 1 0
// Severity						x x
// Code                            x x x x x x
#define pltNO_ERROR						0x0E00
#define pltTIMEOUT						0x0E01
#define pltSYSTEM_ERROR					0x0E80

//==================================================================================================================
//      PRIMITIVES
//==================================================================================================================

#ifdef __cplusplus
}
#endif

#endif /*GPIERRORS_H_*/
