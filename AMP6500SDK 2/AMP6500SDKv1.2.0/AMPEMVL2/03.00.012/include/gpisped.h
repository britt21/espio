// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpisped.h
// PURPOSE....  Generic Platform Interface - Secured PIN Encrypted Device (SPED)
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS�?, All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//						Complete Function List 
//==================================================================================================================
// * gpiSetKeypadTimeout
// * gpiGetKeyIn
// * gpiScanKeyIn
// * gpiIsKeyIn
// * gpiDeactivateKeyIn
// * gpiActivateKeyIn
// * gpiIsKeyInActivated
// * gpiCancelledTransaction
// * gpiEmptyKeyPadCache
// * gpiBeep
// * gpiSound
// * gpiPINPadStatus
// * gpiPINEnter
// * gpiPINVerifyPlaintext
// * gpiPINVerifyCiphered
// * gpiClearList
// * gpiAddItemInList
// * gpiSelectItemFromList
// * gpiSelectItemFromListID
// * 
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPISPED_H_
#define GPISPED_H_

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//			INCLUDES
//==================================================================================================================
//---- GPI Headers ----
#include "gpi.h"

//==================================================================================================================
//			MACROS + DEFINES
//==================================================================================================================
// -----------------------------------------------------------------------------------------------------------------
// Keypad services macros
// -----------------------------------------------------------------------------------------------------------------
//#define	CANCEL				0x00
#define	gpiKEY_0				0x00
#define	gpiKEY_1				0x01
#define	gpiKEY_2				0x02
#define	gpiKEY_3				0x03
#define	gpiKEY_4				0x04
#define	gpiKEY_5				0x05
#define	gpiKEY_6				0x06
#define	gpiKEY_7				0x07
#define	gpiKEY_8				0x08
#define	gpiKEY_9				0x09
#define	gpiKEY_F1				0x0A
#define	gpiKEY_F2				0x0B
#define	gpiKEY_F3				0x0C
#define	gpiKEY_F4				0x0D
#define	gpiENTER				0x0E
#define	gpiCLEAR               	0x0F
#define gpiKEY_UP				0x10
#define gpiKEY_RIGHT			0x11
#define gpiKEY_DOWN				0x12
#define gpiKEY_LEFT				0x13
#define gpiCANCEL				0xCC
#define gpiUNKNOWN_KEY			0xFE
#define	gpiNO_KEY              	0xFF

#define gpiKEY_ALPHA			0xF1
#define gpiKEY_FUNC				0xF2
#define gpiKEY_MENU				0xF4
#define gpiKEY_POWER			0xFA
#define gpiKEY_FEED				0xF9


// -----------------------------------------------------------------------------------------------------------------
// PIN management services macros
// -----------------------------------------------------------------------------------------------------------------
#define	TIMEOUT_DEFAULT        	10  // Timeout default value

// -----------------------------------------------------------------------------------------------------------------
// List Selection Management macros
// -----------------------------------------------------------------------------------------------------------------
#define ID_NO_SELECTION		0xFF

// -----------------------------------------------------------------------------------------------------------------
// Beep management
// -----------------------------------------------------------------------------------------------------------------
#define NO_FREQUENCY	0
#define BEEP_OK			1
#define BEEP_NOK		0

//==================================================================================================================
//			PRIMITIVES
//==================================================================================================================
// -----------------------------------------------------------------------------------------------------------------
//			PED Keypad Interface (keypad.c)
// -----------------------------------------------------------------------------------------------------------------
/**
 * Sets the PED input timeout
 * @param timeout	Keypad timeout (seconds)
 */
DLLEXPORT tGPIError gpiSetKeypadTimeout(
	int timeout
);

/**
* Wait for the next keypress and return the pressed key
* @param key  [out] Pressed key code
*/
DLLEXPORT tGPIError gpiGetKeyIn(
	unsigned char* key
);

/**
* Returns key code of pressed key if available
* @note Not implemented
* @param key  [out] Pressed key code
*/
DLLEXPORT tGPIError gpiScanKeyIn(
	unsigned char* key
);

/**
* Check to see if a key was pressed (?)
* @param flag  [out] 1 if yes, 0 if not
*/
DLLEXPORT tGPIError gpiIsKeyIn(
	unsigned char* flag
);

/**
* Deactivates key input
*/
DLLEXPORT tGPIError  gpiDeactivateKeyIn(void);

/**
* Activates key input
*/
DLLEXPORT tGPIError gpiActivateKeyIn(void);

/**
* Returns whether or not key input is active
* @param flag [out] 		KeyIn state
*/
DLLEXPORT tGPIError gpiIsKeyInActivated(
	unsigned char* flag
);

/**
* Returns whether or not stop button has been pressed
*/
DLLEXPORT unsigned char gpiCancelledTransaction(void);

DLLEXPORT char * gpiGetFirmwareVersion(void);

/**
 * Empties the keypad cache
*/
DLLEXPORT tGPIError gpiEmptyKeyPadCache(void);

// -----------------------------------------------------------------------------------------------------------------
//			Buzzer Interface (audio.c)
// -----------------------------------------------------------------------------------------------------------------
/**
* Emit a sound
* @param frequency  		Frequency of the sound (hertz)
* @param duration			Duration of the sound (* 10 millisecond)
*/
DLLEXPORT tGPIError gpiBeep(
	unsigned short duration, // in ms
	unsigned short frequency // hz
);

/**
* Emit a sound
*/
DLLEXPORT tGPIError gpiSound(
	const char* sound
);

// -----------------------------------------------------------------------------------------------------------------
//			PIN Management Interface (sped.c)
// -----------------------------------------------------------------------------------------------------------------
/**
* Detect whether Pinpad is malfunctioning or not
* @param pinPadName  		Name of the queried PINpad
*/
DLLEXPORT tGPIError gpiPINPadStatus(
	const char* pinPadName
);

/**
* Manage the Personal Identification Number (PIN) on an encrypting keyboard or pin-pad and provide the encrypted PIN
* for further verification performed online
* @param pinPadName 		Name of the used PINpad
* @param lan  				Language to use for feedback
* @param encryptedPIN  		[in] PAN. [out] PIN encrypted by the referenced key
* @param encryptedLen  		[in] Length of PAN. [out] Length of encryptedPIN
* @param timeout  			Maximum number of seconds to enter PIN. -1 = no limit
* @param sred  				SRED status. If true, PAN is clipped
*/
DLLEXPORT tGPIError gpiPINEnter(
	const char* pinPadName,
	unsigned int lan,
	unsigned char* encryptedPIN,
	unsigned char* encryptedLen,
	int timeout,
	unsigned char sred
);

/**
* Perform EMV offline PIN verification in plaintext mode
* @param deviceName			Smartcard reader's name
* @param pinPadName			PIN pad's name
* @param lan  				Language to use for feedback
* @param verifyOnly			Flag indicating that the PIN is already entered and provided in the encryptedPIN parameter
* @param timeout			Maximum number of seconds to enter PIN. -1 = no limit if verifyOnly is false
* @param remainingAttempt	Number of remaining tries before blocking of the card, or -1 if unknown if verifyOnly is false
*/
DLLEXPORT tGPIError gpiPINVerifyPlaintext(
	const char* deviceName,
	const char* pinPadName,
	unsigned int lan,
	char verifyOnly,
	int timeout,
	int remainingAttempt
);

/**
* Perform EMV offline PIN verification in ciphered mode
* @param deviceName			Smartcard reader's name
* @param pinPadName			PIN pad's name
* @param lan  				Language to use for feedback
* @param verifyOnly			Flag indicating that the PIN is already entered and provided in the encryptedPIN parameter
* @param key 				Public key to use for pin encipherment
* @param timeout			Maximum number of seconds to enter PIN. -1 = no limit if verifyOnly is false
* @param remainingAttempt	Number of remaining tries before blocking of the card, or -1 if unknown if verifyOnly is false
*/
DLLEXPORT tGPIError gpiPINVerifyCiphered(
	const char* deviceName,
	const char* pinPadName,
	unsigned int lan,
	char verifyOnly,
	tEMVPubKey* key,
	int timeout,
	int remainingAttempt
);

// -----------------------------------------------------------------------------------------------------------------
// List Selection Management Interface (select.c)
// -----------------------------------------------------------------------------------------------------------------
/**
* Empties the internal selection list
*/
DLLEXPORT tGPIError gpiClearList(void);

/**
* Adds an item to the internal selection list
* @param id  				ID associated with item
* @param name  				Item
*/
DLLEXPORT tGPIError gpiAddItemInList(
	const unsigned char id, 
	const char *name
);

/**
* Displays a list on screen and allow the user to select one of the choices
* @note Uses the internal selection list
* @param title				Menu title
* @param timeout  			Timeout delay on keypad input
* @param selectedId  		[out] Selection ID
*/
DLLEXPORT tGPIError gpiSelectItemFromList(
	const char *title,
	const int timeout,
	unsigned char *selectedId
);

/**
* Displays a list on screen and allow the user to select one of the choices
* @note Uses the internal selection list
* @param langId   			Current system language
* @param stringId  			String identifier
* @param timeout  			Timeout delay on keypad input
* @param selectedId  		[out] Selection ID
*/
DLLEXPORT tGPIError gpiSelectItemFromListByID(
	unsigned char langId,
	unsigned char stringId,
	const int timeout,
	unsigned char *selectedId
);

#ifdef __cplusplus
}
#endif

#endif /* GPISPED_H_ */
