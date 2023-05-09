// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpidisplay.h
// PURPOSE....  Generic Platform Interface - Display
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS�?, All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//      Complete Function List
//==================================================================================================================
// * gpiInitializeDisplay
// * gpiGetCurrentDisplayLine
// * gpiGetLastDisplayLine
// * gpiGetNbLanguage
// * gpiGetLanguage
// * gpiGetIdOfLanguageCode
// * gpiGetLanguageCodeOfId
// * gpiGetIdFromManualLanguageSelection
// * gpiGetIdFromManualLanguageSelectionByID
// * gpiGetString
// * gpiDisplayMessage
// * gpiDisplayMessageByID
// * gpiDisplayMessageXY
// * gpiDisplayMessageXYByID
// * gpiDisplayMessageReverseXY
// * gpiDisplayMessageReverseXYByID
// * gpiClearScreen
// * gpiClearLine
// * gpiSwitchLCDBacklight
// * gpiDisplayDelay
// * gpiReverseDisplay
// * gpiAdvancedDisplay
// * gpiAdvancedDisplayAsOutcome
// * gpiSwitchLED
// * gpiSetPollingMessage
// * gpiDisplayPollingMessage
// *
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPIDISPLAY_H_
#define GPIDISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//      INCLUDES
//==================================================================================================================
//---- GPI Headers ----
#include "gpi.h"

//==================================================================================================================
//      MACROS + DEFINES
//==================================================================================================================
//See standard messages, EMVCo Book IV, section 11.2
#define	NO_MESSAGE						0x00
#define	AMOUNT							0x01
#define	AMOUNT_OK						0x02
#define	APPROVED						0x03
#define	CALL_YOUR_BANK					0x04
#define	CANCEL_OR_ENTER					0x05
#define	CARD_ERROR						0x06
#define	DECLINED						0x07
#define	ENTER_AMOUNT					0x08
#define	ENTER_PIN						0x09
#define	INCORRECT_PIN					0x0A
#define	INSERT_CARD						0x0B
#define	NOT_ACCEPTED					0x0C
#define	PIN_OK							0x0D
#define	PLEASE_WAIT						0x0E
#define	PROCESSING_ERROR				0x0F
#define	REMOVE_CARD						0x10
#define	USE_CHIP_READER					0x11
#define	USE_MAGSTRIPE					0x12
#define TRY_AGAIN						0x13

#define	WELCOME							0x14
#define PRESENT_CARD					0x15
#define PROCESSING						0x16
#define CARD_READ_OK					0x17
#define PLEASE_INSERT_OR_SWIPE			0x18
#define PLEASE_PRESENT_ONE_CARD			0x19
#define APPROVED_PLEASE_SIGNED			0x1A
#define AUTHORIZING						0x1B
#define ERROR_USE_OTHER_CARD			0x1C
#define PLEASE_INSERT_CARD				0x1D
#define	CLEAR_DISPLAY					0x1E
//#define	RFU							0x1F
#define	SEE_PHONE						0x20
#define	PRESENT_CARD_AGAIN				0x21
#define	INSERT_SWIPE_OR_OTHER_CARD		0x22
#define LAST_PIN_TRY					0x23
#define	RETRY							0x24

#define	SELECT_ACCOUNT					0x81
#define	USING_MAGSTRIPE					0x82
#define	LANGUAGE						0x83
#define	TRANSACTION_CANCELLED   		0x84
#define	SWIPE_CARD						0x85
#define	TRANSACTION_FAILED				0x86
#define	CASH_BACK						0x87
#define	CASH_BACK_OK					0x88
#define	REFERRAL     					0x89
#define	THANKS	     					0x8A
#define	TXN_NOT_PERMITTED	     		0x8B
#define	SELECT	     					0x8C
#define	SELECT_APP	     				0x8C
#define	DEFAULT_ACCOUNT	     			0x8D
#define	SAVINGS_ACCOUNT		     		0x8E
#define	CHECKING_ACCOUNT		     	0x8F
#define	CREDIT_ACCOUNT		     		0x90
#define CARD_EXPIRED					0x91
#define PIN_REQUIRED_SEE_ATTENDANT		0x92
#define PIN_REQUIRED_CL_NOT_PROCESSED	0x93
#define PASSCODE_REQUIRED_SEE_MDA		0x94
#define TOO_MANY_TAPS					0x95
#define PAYMENT_TYPE_NOT_ACCEPTED		0x96
#define PURCHASE						0x97
#define REFUND							0x98
#define NO_CARD							0x99
#define NO_KEY_INJECTED					0x9A

#define	LED_1	     					0x01
#define	LED_2	     					0x02
#define	LED_3	     					0x03
#define	LED_4	     					0x04
#define	LED_ALL	     					0x05

#define LED_OFF							0x00
#define LED_ON							0x01
#define LED_FLASH						0x02

#define	BLUE							0x01
#define	ORANGE							0x02
#define	RED								0x03
#define	GREEN							0x04

//! Code returned by gpiGetLanguage() when no match is found
#define LANGUAGE_NOT_FOUND				0xFF

/*
typedef enum {
	laDEFAULT,
	laENGLISH,
	laFRENCH
} tLanguage;
*/

typedef enum {
	siNONE,                  //!< siNONE
	siNOT_READY,             //!< siNOT_READY
	siIDLE,                  //!< siIDLE
	siREADY_TO_READ,         //!< siREADY_TO_READ
	siPROCESSING,            //!< siPROCESSING
	siCARD_READ_SUCCESSFULLY,//!< siCARD_READ_SUCCESSFULLY
	siPROCESSING_ERROR       //!< siPROCESSING_ERROR
} tStatusIdentifier;

typedef enum {
	vqNONE,
	vqAMOUNT,
	vqBALANCE
} tValueQualifier;

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct {
	unsigned char 		mMessage;
	tStatusIdentifier 	mStatus;
	unsigned long		mHoldTime;
	unsigned char 		mLanguagePreference[8];
	unsigned char 		mLanguagePreferenceLen;
//	tLanguage 			mLanguage;
	unsigned char		mLanguage;
	tValueQualifier		mValueQualifier;
	unsigned char		mValue[6];
	unsigned short 		mCurrencyCode;
} tUIRequestData;
#ifdef PACKING
#pragma pack()
#endif


//! Structure for GPI Callback functions
typedef struct 
{
	unsigned short (*cbGpiDisplayMessage)(unsigned char clearScreen, unsigned char langId, const char *message, unsigned char MessageId);
	unsigned short (*cbGpiSelectItemFromList) (const char *arrItems[], unsigned char arrCount, const char *title, int timeout, unsigned char *selectedId);
	unsigned short (*cbGpiSwitchLED) (unsigned char led, unsigned char flag, unsigned char colour);
	void           (*cbGpiDisplayPinEntryPrompt) (unsigned char clearScreen, unsigned char langId, const char *message);
	unsigned short (*cbGpiOnlinePinEntry) (const char *PAN, int PANlen, unsigned char *PINBlock, int *PINBlockLen);
	void		   (*cbGpiPinRetries) (int PinRetries);

#if !defined(ANDROID)
	void           (*cbGpiCardEntryDisplay) (const unsigned char SupportedEntryMethod);
#endif

#if defined(ANDROID)
	unsigned short (*cbGpiOfflinePinEntry) (char bEnciphered, unsigned int lan, int timeout, tEMVPubKey* pubkey, unsigned char *IccRandom, unsigned char *RespData);
#endif	
	
}tGpiDisplayCallBack;



//==================================================================================================================
//      PRIMITIVES
//==================================================================================================================
/**
 * Load Language String from inifile into an internal String Table
 *
 * 	    Content of Ini File file
 * 		[Language]
 * 			1=l1
 * 			2=l2
 * 		[l1]
 * 			01=String1
 * 			02=String2
 *
 * @param inifile	Ini File containing Language String Definitions
 * @param count [out] Number of Languages loaded into the String Table
 */
DLLEXPORT tGPIError gpiInitializeDisplay(const char* inifile, unsigned char * count, void* arg);

/**
 * Returns the Current Line Index available for display
 * @param line [out] Current Line Index available on the SPED's Screen
 */
DLLEXPORT tGPIError gpiGetCurrentDisplayLine(int * line);

/**
 * Returns the Last Line available for display
 * @param line [out] Last Line Index available on the SPED's Screen
 */
DLLEXPORT tGPIError gpiGetLastDisplayLine(int * line);

/**
 * Returns the number of languages supported by the Terminal
 * @param count [out] Number of languages loaded in memory
 */
DLLEXPORT tGPIError gpiGetNbLanguage(unsigned char * count);

/**
 * Tries to match a Language from languagePreference and the languages supported by the Terminal (ISO 639-1)
 * @param languagePreference	List of languages requested by the payment application
 * @param languagePreferenceLen	Length of the list (2, 4, 6, 8)
 * @param lang [out] Language ID of the language matched, otherwise returns LANGUAGE_NOT_FOUND
 */
DLLEXPORT tGPIError gpiGetLanguage(const unsigned char *languagePreference, const unsigned char languagePreferenceLen, unsigned char * lang);

/**
 * Returns the Language ID corresponding to languageCode passed in parameter
 * @param languageCode	Language Code in ISO639-1 Format
 * @param id [out] Language ID of language matched, otherwise returns LANGUAGE_NOT_FOUND
 */
DLLEXPORT tGPIError gpiGetIdOfLanguageCode(const char *languageCode, unsigned char * id);

/**
 * Returns the ISO 639-1 formatted Language Code of the Language ID passed in parameter
 * @param langId	Language ID of the language
 * @param code [out] ISO639-1 Code of langId, otherwise return ""
 */
DLLEXPORT tGPIError gpiGetLanguageCodeOfId(const unsigned char langId, const char ** code);

/**
 * Returns the Language ID after selection from the list of language available on the Terminal
 * @param message	Message to be displayed ("" indicates no message)
 * @param timeout	Timeout (in seconds)
 * @param id [out] Language ID of language matched, otherwise returns LANGUAGE_NOT_FOUND
 */
DLLEXPORT tGPIError gpiGetIdFromManualLanguageSelection(char *message, int timeout, unsigned char * id);

/**
 * Returns the Language ID after selection from the list of language available on the Terminal
 * @param langId	Language ID of the message to be returned
 * @param stringId	String ID of the message to be returned
 * @param timeout	Timeout (in seconds)
 * @param id [out] Language ID of language matched, otherwise returns LANGUAGE_NOT_FOUND
 */
DLLEXPORT tGPIError gpiGetIdFromManualLanguageSelectionByID(unsigned char lanId, unsigned char stringId, int timeout, unsigned char * id);

/**
 * Returns the String corresponding the the String ID and Language ID parameters
 * @param langId	Language ID of the message to be returned
 * @param stringId	String ID of the message to be returned
 * @param string [out] Pointer to the message matched, otherwise returns "--"
 */
DLLEXPORT tGPIError gpiGetString(const unsigned char langId, const unsigned char stringId, char ** string);

/**
 * Displays a message on the SPED's Screen
 * @note	Unicode alphabet is supported
 * @note	Multiline available supported using '\' (ex: "LINE 1\LINE 2")
 * @param clearScreen	Clear the Screen before displaying the message
 * @param message		Message to be displayed
 */
DLLEXPORT tGPIError gpiDisplayMessage(unsigned char clearScreen, const char* message);

/**
 * Displays a message on the SPED's Screen
 * @note Unicode alphabet is supported
 * @note Multiline available supported using '\' (ex: "LINE 1\LINE 2")
 * @param clearScreen 	Clear the Screen before displaying the message
 * @param langId  		Current system language
 * @param stringId  	String identifier
 */
DLLEXPORT tGPIError gpiDisplayMessageByID(unsigned char clearScreen, unsigned char langId, unsigned char stringId);

/**
 * Displays a message at a specific location of the SPED's Screen
 * @param X				Character position
 * @param Y				Line number where the message is displayed
 * @param message		Message to be displayed
 */
DLLEXPORT tGPIError gpiDisplayMessageXY(unsigned char X, unsigned char Y, const char* message);

/**
 * Displays a message at a specific location of the SPED's Screen
 * @param X    			Character position
 * @param Y    			Line number where the message is displayed
 * @param langId  		Current system language
 * @param stringId  	String identifier
 */
DLLEXPORT tGPIError gpiDisplayMessageXYByID(unsigned char X, unsigned char Y, unsigned char langId, unsigned char stringId);

/**
 * Displays a message at a specific location of the SPED's Screen
 * @param X				Character position
 * @param Y				Line number where the message is displayed
 * @param message		Message to be displayed
 * @param reverse		Reverse video on or off
 */
DLLEXPORT tGPIError gpiDisplayMessageReverseXY(unsigned char X, unsigned char Y, const char* message, unsigned char reverse);

/**
 * Displays a message at a specific location of the SPED's Screen
 * @param X    			Character position
 * @param Y    			Line number where the message is displayed
 * @param langId  		Current system language
 * @param stringId  	String identifier
 * @param reverse  		Reverse video on or off
 */
DLLEXPORT tGPIError gpiDisplayMessageReverseXYByID(unsigned char X, unsigned char Y, unsigned char langId, unsigned char stringId, unsigned char reverse);

/**
 * Clear the Terminal's Screen
 */
DLLEXPORT tGPIError gpiClearScreen(void);

/**
 * Clear a specific Line on the SPED's Screen
 * @param y		Line number to be cleared on SPED's Screen
 */
DLLEXPORT tGPIError gpiClearLine(unsigned char y);

/**
 * Turns the SPED's Screen Backlight on/off
 * @param flag	0: Backlight Off, 1: Backlight On
 */
DLLEXPORT tGPIError gpiSwitchDisplayBacklight(unsigned char flag);

/*
 * Uncommented
 * TODO : comment
 */
DLLEXPORT tGPIError gpiDisplayDelay(unsigned long value);
DLLEXPORT tGPIError gpiReverseDisplay(unsigned char flag); // true or false
DLLEXPORT tGPIError gpiAdvancedDisplay(tUIRequestData* UIRequestData);
DLLEXPORT tGPIError gpiAdvancedDisplayAsOutcome(tUIRequestData* UIRequestData);
DLLEXPORT tGPIError gpiSwitchLED(unsigned char led, unsigned char flag, unsigned char colour);
DLLEXPORT tGPIError gpiSetPollingMessage(int Contactless, const char* prompt, const char* amount);

DLLEXPORT tGPIError gpiDisplayPollingMessage(void);

/*
 * Registers user defined display callback functions defined in tGpiDisplayCallback structure
 * @gpiDispCB holds the callback display functions
 * @return admNO_ERROR
 */
tGPIError gpiDisplayRegisterCallBack(tGpiDisplayCallBack *gpiDispCB);

/*
 * Returns private gGpiDispCallBack that holds the display callbacks functions
 * @return tGpiDisplayCallBack
 */
tGpiDisplayCallBack *gpiGetDisplayCallBackFunc(void);

/*
 * To set the language support by the calling application
 * @return admNO_ERROR
 * ex: "en, fr, nl, ru, ar"
 */
tGPIError gpiSetFilterLangSupport(const char *szLangCodes );



#ifdef __cplusplus
}
#endif

#endif /* GPIDISPLAY_H_ */
