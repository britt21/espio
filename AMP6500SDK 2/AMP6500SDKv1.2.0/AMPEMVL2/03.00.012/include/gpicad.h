// -----------------------------------------------------------------------------------------------------------------
// NAME.......  gpicad.h
// PURPOSE....  Generic Platform Interface - Card Acceptance Device
// PROJECT....  GPI
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS�?, All Rights Reserved
//
// -----------------------------------------------------------------------------------------------------------------

//==================================================================================================================
//      Complete Function List
//==================================================================================================================
// * gpiTechnoPolling
// * gpiSetTechnoToDetect
// * gpiGetSerialNumber
// * gpiCardInserted
// * gpiExchangeAPDU
// * gpiPowerOn
// * gpiPowerOff
// * gpiGetCardStatus
// * gpiCardSwiped
// * gpiReadMagstripe
// * gpiGetLastErrorStatus
// * gpiInitPolling
// * gpiPolling
// * gpiRemovalProcedure
// * gpiResetContactless
// *
// -----------------------------------------------------------------------------------------------------------------

#ifndef GPICAD_H_
#define GPICAD_H_

#ifdef __cplusplus
extern "C" {
#endif

//==================================================================================================================
//      INCLUDES
//==================================================================================================================
//---- GPI Headers ----
#include "gpi.h"

#define CONTACT_READER_NAME     "CONTACT_READER"
#define CONTACTLESS_READER_NAME "CONTACTLESS_READER"
#define MAGSTRIPE_NAME          "MAGSTRIPE_READER"

//==================================================================================================================
//      MACROS + DEFINES
//==================================================================================================================
//Card status
typedef unsigned char tCardStatus;

//APDU management
#define MAX_APDU_LENGTH			(255 + 6) // Data + CLA' INS, P1, P2, Lc, Le bytes
#define	CARD_ACTIVATED			0x00
#define	CARD_NOT_PRESENT		0x01
#define	CARD_NOT_ACTIVATED		0x02
#define	CARD_MUTE				0x03

// Technology Polling
#define TECHNO_CL_TYPE_A		0x01
#define TECHNO_CL_TYPE_B		0x02
#define TECHNO_CL_TYPE_EMV		0x04
#define TECHNO_MANUAL			0x20
#define TECHNO_CONTACT			0x40
#define TECHNO_MAGSTRIPE		0x80

// EMV Card Reader Devices
#define DEVICE_CARD_CONTACT 		0x01
#define DEVICE_CARD_CONTACTLESS		0x02
#define DEVICE_CARD_MAGSTRIPE		0x04
#define DEVICE_CARD_ALL				DEVICE_CARD_CONTACT | DEVICE_CARD_CONTACTLESS | DEVICE_CARD_MAGSTRIPE
//==================================================================================================================
//      PRIMITIVES
//==================================================================================================================
// -----------------------------------------------------------------------------------------------------------------
//Interface to contact reader
// -----------------------------------------------------------------------------------------------------------------
/**
 * Poll for detectable card technologies
 * @param technologies Technologies to scan for
 * @param timeout Duration of the techno polling in seconds
 * @param technologyDetected (out) Technologies detected by the poll
 */
DLLEXPORT tGPIError gpiTechnoPolling(const unsigned char technologies, const unsigned int timeout, unsigned char *technologyDetected);

/**
 * Set technologies to detect
 * @param technologies Technologies to scan for
 */
DLLEXPORT tGPIError gpiSetTechnoToDetect(const unsigned char technologies);

/**
 * Return the device's serial number
 * @param serialNumBuf (out) Contains the CAD's serial number
 */
DLLEXPORT tGPIError gpiGetSerialNumber(unsigned char* serialNumBuf);

/**
* Returns the card reader device's file handle/descriptor
* @param CardReaderDevice = DEVICE_CARD_CONTACT | DEVICE_CARD_CONTACTLESS | DEVICE_CARD_MAGSTRIPE
*/
int gpiGetCardReaderHandle(unsigned char CardReaderDevice);


/**
 * Checks for a card insertion
 * @param smartcardReaderName Smartcard reader's name
 */
DLLEXPORT tGPIError gpiCardInserted(const char* smartcardReaderName);

/**
 * Power on an inserted card
 * @param smartcardReaderName Smartcard reader's name
 * @param status [out] Status of the card
 * @param ATRBuffer (out) ATR bytes received from card. Maybe NULL if not used by application level
 * @param ATRLen In: ATR buffer length, and Out: ATR length
 */
DLLEXPORT tGPIError gpiPowerOn(const char* smartcardReaderName, tCardStatus* status, unsigned char* ATRBuffer,unsigned char* ATRLen);

/**
 * Send an APDU request to a card reader and collect the card's response
 * @param smartcardReaderName Smartcard reader's name
 * @param apduReq CLA, INS, P1, P2, Lc, and dataIn (of Lc length)
 * @param Le Null when Le not present. Else 0x00.
 * @param apduResp (out)Must be a pointer to a MAX_APDU_LENGTH byte length
 * @param lenResp Last two bytes = SW1 SW2
 */
DLLEXPORT tGPIError gpiExchangeAPDU(const char* smartcardReaderName, unsigned char* apduReq,unsigned char* Le, unsigned char* apduResp, unsigned short* lenResp);

/**
 * Send an APDU request to a card reader and collect the card's response
 * @param smartcardReaderName Smartcard reader's name
 * @param apduReq [out] CLA, INS, P1, P2, Lc, and dataIn (of Lc length)
 * @param lenReq [out] Null when Le not present. Else 0x00.
 * @param apduResp [out] Must be a pointer to a MAX_APDU_LENGTH byte length
 * @param lenResp [out] Last two bytes = SW1 SW2
 */
DLLEXPORT tGPIError gpiGetLastExchangedAPDU(const char* smartcardReaderName, unsigned char* apduReq, unsigned short* lenReq, unsigned char* apduResp, unsigned short* lenResp);

/**
 * Power off an inserted card
 * @param device card reader's name
 */
DLLEXPORT tGPIError gpiPowerOff(const char* smartcardReaderName);

/**
 * Power off all devices
 */
DLLEXPORT tGPIError gpiPowerOffAllDevices(void);

/**
 * Retrieve card's status
 * @param smartcardReaderName Smartcard reader's name
 * @param status (out) Current status of the card in order to assess a fallback situation
 */
DLLEXPORT tGPIError gpiGetCardStatus(const char* smartcardReaderName, tCardStatus* status);

// -----------------------------------------------------------------------------------------------------------------
//Interface to magstripe reader
// -----------------------------------------------------------------------------------------------------------------
/**
 * Determine if a card was swiped
 * @param magstripeReaderName Magstripe card reader's name
 */
DLLEXPORT  tGPIError gpiCardSwiped(const char* magstripeReaderName);

/**
 * Read a magstripe's tracks
 * @param magstripeReaderName Magstripe card reader's name
 * @param track1Buffer (out) Track 1 data
 * @param track1Len (in/out) Tracks 1 buffer's length (in) and Track 1 length (out)
 * @param track2Buffer (out) Track 2 data
 * @param track2Len (in/out) Tracks 2 buffer's length (in) and Track 2 length (out)
 * @param track3Buffer (out) Track 3 data
 * @param track3Len (in/out) Tracks 3 buffer's length (in) and Track 3 length (out)
 */
DLLEXPORT tGPIError gpiReadMagstripe(
	const char* magstripeReaderName,
	unsigned char* track1Buffer, unsigned short* track1Len,
	unsigned char* track2Buffer, unsigned short* track2Len,
	unsigned char* track3Buffer, unsigned short* track3Len
);

/**
 * Read a magstripe error status
 * @param magstripeReaderName Magstripe card reader's name
 * @param track1Error (out) Track 1 error status
 * @param track2Error (out) Track 2 error status
 * @param track3Error (out) Track 3 error status
 */
DLLEXPORT  tGPIError gpiGetLastErrorStatus(const char* magstripeReaderName, unsigned char* track1Error, unsigned char* track2Error, unsigned char* track3Error);

// -----------------------------------------------------------------------------------------------------------------
//Interface to contactless reader
// -----------------------------------------------------------------------------------------------------------------
/**
 * Init contactless techno polling
 * @param contactlessCardReaderName Contactless card reader's name
 */
DLLEXPORT  tGPIError gpiInitPolling(const char* contactlessCardReaderName);

/**
 * Poll for contactless cards
 * @param contactlessCardReaderName Contactless card reader's name
 */
DLLEXPORT tGPIError gpiPolling(const char* contactlessCardReaderName,unsigned int timeout);

/**
 * Wait for card to be properly removed
 * @param contactlessCardReaderName Contactless card reader's name
 */
DLLEXPORT tGPIError gpiRemovalProcedure(const char* contactlessCardReaderName, unsigned char holdtime);

/**
 * Reset contactless card reader
 * @param contactlessCardReaderName Contactless card reader's name
 */
DLLEXPORT tGPIError gpiResetContactless(const char* contactlessCardReaderName);

/**
 * Force CAD to contactless processing state
 */
DLLEXPORT tGPIError gpiSetContactlessTransactionInProgress(void);

/**
 * Returns the FCI response data from Select application APDU command
 * @param smartcardReaderName Smartcard reader's name
 * @param apduResp [out] Must be a pointer to a MAX_APDU_LENGTH byte length
 * @param lenResp [out] Last two bytes = SW1 SW2
 */
tGPIError gpiGetFCIRespAPDU(	const char* smartcardReaderName,
									unsigned char* apduFCIResp,
									unsigned short* lenFCIResp);


/**
 * Returns the FCI response data (SW1SW2 = 6283 Card blocked) from Select application APDU command
 * @param smartcardReaderName Smartcard reader's name
 * @param apduResp [out] Must be a pointer to a MAX_APDU_LENGTH byte length
 * @param lenResp [out] Last two bytes = SW1 SW2
 */
tGPIError gpiGetFCIRespAPDU6283(	const char* smartcardReaderName,
									unsigned char* apduFCIResp,
									unsigned short* lenFCIResp);



/**
 * Sets the card entry techonolgies tha will be used in gpiPolling
 * @param technologies see Technology Polling definition 
 */
void gpiSetTechnologies(unsigned char technologies);

/**
 * Returns the card entry techonologies
 */
unsigned char gpiGetTechnologies(void);

#define CTLS_DETECT_DELAY

#ifdef CTLS_DETECT_DELAY
/**
 * Enables the card swipe detection when card has CTLS data
 * Sets the card swipe detection timeout when card with CTLS data is tapped
 */
void gpiEnableCTLSDetectDelay(unsigned char bEnable);
void gpiSetCTLSDetectDelayTimeOut(int nTimeOutMS);
#endif

void gpiEnableFarePodMode(unsigned char bFarePodMode);

/**
 * Bypasses the gpiRemovalProcedure of contactless
 */
void gpiSetCTLSBypassRemoveCard(unsigned char bBypass);

/**
 * Allows the application to detect the card entry prior to calling gpiTechnoPolling()
 * This is intended for card entry OnIdle scenario
 */
void gpiPreTechnoPolling(void);


int gpiOpenCardReader(unsigned char CardReaderDevice);


#ifdef __cplusplus
}
#endif

#endif /* GPICAD_H_ */
