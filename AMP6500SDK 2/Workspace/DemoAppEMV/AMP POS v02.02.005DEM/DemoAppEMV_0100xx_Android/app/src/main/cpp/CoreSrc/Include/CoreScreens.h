#ifndef CORE_SCREENS_H_
#define CORE_SCREENS_H_

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
* File       	 : 		CoreScreens.h
* Library	 	 : 		AMP-BaseApp
* Date Coded  : 		09/09/2015
**************************************************************************/

// AMP Includes
#include <AMPPosEntry.h>

// Project Includes
#include "CoreTransObj.h"

//4 Screen Definitions
//! Screen Size
#define AMP_SCREEN_WIDTH			320
#define AMP_SCREEN_HEIGHT			216

//! Font Definitions
#define APP_FONTS_PATH				"../fonts/"
#define BOLD_FONT_FILE				APP_FONTS_PATH "arialbd.ttf"
#define NORMAL_FONT_FILE			APP_FONTS_PATH "arial.ttf"
#define NORMAL_FONT_SIZE			14
#define TITLE_FONT_FILE				APP_FONTS_PATH "arial.ttf"
#define TITLE_FONT_SIZE				20
#define BUTTON_FONT_FILE			APP_FONTS_PATH "arial.ttf"
#define BUTTON_FONT_SIZE			18
#define PROMPT_FONT_SIZE			18
#define MEDIUM_FONT_SIZE			16
#define ICON_LABEL_FONT_FILE		APP_FONTS_PATH "arial.ttf"
#define ICON_LABEL_FONT_SIZE		12
#define DEMO_LABEL_FONT_FILE		APP_FONTS_PATH "arialbd.ttf"
#define DEMO_LABEL_FONT_SIZE		18
#define COURIER_FONT_FILE			APP_FONTS_PATH "cour.ttf"
#define COURIER_BOLD_FONT_FILE		APP_FONTS_PATH "courbd.ttf"
#define IDLEMSG_FONT_SIZE			26

#define PIN_ENTRY_DEF_WIDTH			210
#define PIN_ENTRY_DEF_HEIGHT		40
#define PIN_ENTRY_DEF_X				(AMP_SCREEN_WIDTH-PIN_ENTRY_DEF_WIDTH)/2
#define PIN_ENTRY_DEF_Y				140

//! Image Definitions
#define APP_IMAGES_PATH				"../images/"
#define IMG_AMP_LOGO				APP_IMAGES_PATH "AMPLogo.png"
#define IMG_BUTTON_RED				APP_IMAGES_PATH "button_red.png"
#define IMG_BUTTON_GREEN			APP_IMAGES_PATH "button_green.png"

#define IMG_BUTTON_CANCEL			APP_IMAGES_PATH "buttons/Cancel - a.png"
#define IMG_BUTTON_CLEAR			APP_IMAGES_PATH "buttons/Clear - a.png"
#define IMG_BUTTON_ENTER			APP_IMAGES_PATH "buttons/Enter - a.png"
#define IMG_BUTTON_YES				APP_IMAGES_PATH "buttons/Yes.png"
#define IMG_BUTTON_NO				APP_IMAGES_PATH "buttons/No.png"

#define IMG_CONTACTLESS_LOGO		APP_IMAGES_PATH "Tap.png"
#define IMG_PASSTOCUSTOMER_LOGO		APP_IMAGES_PATH "PassTerminal.png"

#define IMG_BUTTON_GENERIC			APP_IMAGES_PATH "button_choice.png"

#define IMG_TELEPHONE_ICON			APP_IMAGES_PATH "Telephone.png"
#define IMG_EMAIL_ICON				APP_IMAGES_PATH "Email.png"

#define IDLE_IMAGE_FILENAME			APP_IMAGES_PATH "idle_image.png"

#define IMG_SAMSUNGPAYV_LOGO		APP_IMAGES_PATH "SamsungPay-V.png"
#define IMG_SAMSUNGPAYH_LOGO		APP_IMAGES_PATH "SamsungPay-H.png"

//4 Beep Definitions for Display prompts
#define BEEP_NONE 0
#define BEEP_INFO 1
#define BEEP_WARN 2
#define BEEP_ERROR 3
#define BEEP_LOOP 4

//4 Amount formatting definitions
#define AMOUNT_FORMAT_SEPARATORS	".,"
#define AMOUNT_FORMAT_STR			"C sn,nnn,nnN.NN"
#define AMOUNT_FORMAT_NO_CURRENCY	"sn,nnn,nnN.NN"

//4 Button Yes/No
#define BUTTON_NO			0
#define BUTTON_YES			1

// PromptDisplay - prompts 2 line display message (delay is in millisec)
// szHeader - string header/title of screen
// szPrompt1 - string prompt message line 1
// szPrompt2 - string prompt message line 2
// szPrompt3 - string prompt message line 3
// szPrompt4 - string prompt message line 4
// iBeep - BEEP_NONE, BEEP_INFO, BEEP_WARN, BEEP_ERROR
// iDelayMS - delay in milliseconds
void PromptDisplay(const char* szHeader, const char* szPrompt1, const char* szPrompt2 = NULL, 
						const char* szPrompt3 = NULL, const char* szPrompt4 = NULL,
						int iBeep = BEEP_NONE, int iDelayMS = 0);


// PromptEnterCancel - prompts confirmation (Enter/Cancel) message
// returns AMP_ENTER or AMP_CANCEL or AMP_TIMEOUT
// szHeader - string header/title of screen
// szPrompt1 - string prompt message line 1
// szPrompt2 - string prompt message line 2
// szPrompt3 - string prompt message line 3
// szPrompt4 - string prompt message line 4
// iTimeout - timeout in seconds
// iBeep - BEEP_NONE, BEEP_INFO, BEEP_WARN, BEEP_ERROR
int PromptEnterCancel(const char* szHeader, const char* szPrompt1, const char* szPrompt2 = NULL, 
							 const char* szPrompt3 = NULL, const char* szPrompt4 = NULL,
							 int iTimeout = 0, int iBeep = BEEP_NONE);

// PromptYesNo - prompts confirmation (Yes/No) message
// returns BUTTON_NO or BUTTON_YES or AMP_TIMEOUT or AMP_CANCEL
// szHeader - string header/title of screen
// szPrompt1 - string prompt message line 1
// szPrompt2 - string prompt message line 2
// iTimeout - timeout in seconds
// iBeep - BEEP_NONE, BEEP_INFO, BEEP_WARN, BEEP_ERROR
int PromptYesNo(const char *szHeader, const char* szPrompt1, const char *szPrompt2, int iTimeOut, int iBeep);

// PromptSelection - prompts 2 or 3 button selection display
// returns AMPKEY_MENU1 or AMPKEY_MENU2 or AMPKEY_MENU3 or AMP_ENTER or AMP_CANCEL or AMP_TIMEOUT
// szHeader - string header/title of screen
// szPrompt1 - string prompt message line 1
// szPrompt2 - string prompt message line 2
// nSelectionButtons - number of buttons on screen (2 or 3 ONLY!)
// szButtonMsg1 - string message in Button 1
// szButtonMsg2 - string message in Button 2
// szButtonMsg3 - string message in Button 3
// iTimeout - timeout in seconds
// iBeep - BEEP_NONE, BEEP_INFO, BEEP_WARN, BEEP_ERROR
int PromptSelection(const char *szHeader, const char* szPrompt1, const char* szPrompt2, int nSelectionButtons,
					const char *szButtonMsg1, const char* szButtonMsg2, const char* szButtonMsg3, int iTimeout = 0, int iBeep = BEEP_NONE);

// Prompts Input entry with 2 line display message
// returns AMP_ENTER or AMP_CANCEL or AMP_TIMEOUT
//
// szHeader - string header/title of screen
// szPrompt1 - string prompt message line 1
// szPrompt2 - string prompt message line 2
// iMax - maximum number of characters for input
// iMin - minimum number of characters for input
// FieldFormat - format of display output
// Mask - mask character for Password input
// CurrSymbol - currency symbol for amount inputs (up to 3 characters only)
//
// INPUT_METHOD possible values is as follows:
// INP_METH_NUM_ONLY - Numbers only
// INP_METH_NUM_WITH_PUNC	 - Numbers with all punctuations (keyed from 0 key)
// INP_METH_NUM_WITH_DOT	- Numbers with dot only (keyed from 0 key)
// INP_METH_ALPHA_ONLY - Alphabet only (no numbers)
// INP_METH_ALPHA_NUMERIC	- Alphabet and numeric only (no punctuations)
// INP_METH_ALL_KEYS - All keys (alphabet, numeric, punctuations)
// INP_METH_BINARY_ONLY - Binary keys only (0 and 1)
// INP_METH_HEX_ONLY - Hex keys only (0 - 9 and A - E)
// INP_METH_CUSTOMKEY_MAP	- Used only when using a custom key map
// INP_METH_PASSWORD - Flag for Password entry (with *). Shows the number (or letter) entered, then updates into mask character (*) after a few seconds
// INP_METH_PW_STRICT_MASK - Flag for Password entry (with *). Shows only mask character (*). Hides the number/letter entered completely
//
// ALIGNMENT values: ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT
// szOutBuffer - buffer for data input (may assign an initial value for data entry)
// FontSize - font size for data input display
// iTimeout - timeout in seconds
int PromptEntry(const char* szHeader, const char* szPrompt1, const char* szPrompt2, int iMax, int iMin,
					char* FieldFormat, char Mask, char *CurrSymbol,
					INPUT_METHOD InpMethod, ALIGNMENT InpAlign, 
					char* szOutBuffer, int FontSize, int iTimeout);

int PromptTipEntry(const char* szHeader, const char* szPrompt1, const char* szPrompt2, int iMax, int iMin,
					char* FieldFormat, char Mask, char *CurrSymbol,
					INPUT_METHOD InpMethod, ALIGNMENT InpAlign, 
					char* szOutBuffer, int FontSize, int iTimeout, const char* szitem1, const char* szitem2, const char* szitem3, int tipType);

//! Prompts the Inser/Swipe/Tap/Enter Card entry
void DisplayCardEntryPrompt(const char *szHeader, const char *szPromptLang1, const char *szPromptLang2, BOOL bDisplayIcon = TRUE);

//! Prompts the Pass the terminal to Customer display
int DisplayPassTerminalToCustomer(const char *szHeader, const char *szPrompt1, const char *szPrompt2, BOOL bWaitForKey = FALSE);
int PromptCancel(const char* szHeader, const char* szPrompt1, const char* szPrompt2 = NULL,
				 const char* szPrompt3 = NULL, const char* szPrompt4 = NULL,
				 int iTimeout = 0, int iBeep = BEEP_NONE);

//! Clears the LED Display bar
void ClearLedDisplay(void);

//! Starts the LED Display Timer for EMV Contactless
void StartLedDisplayTimer(void);

//! Customized Led Switching based on Led ID, Led Status, Led Color
//
// LED_ID: LED1 / LED2 / LED3 / LED4
// LED_STATUS:
//		LEDON - Switch Led to ON
//		LEDOFF - Switch Led to OFF
// 		LEDFLASH - Blink Led
// LED_COLOR: LEDBLUE / LEDYELLOW / LEDGREEN / LEDRED
void SwitchLedColor(unsigned char Led, unsigned char Status, unsigned char Colour);

//! Switch Led to ON based on specified color (Option for multi-colored Led)
//
// Led Colors: LEDBLUE / LEDYELLOW / LEDGREEN / LEDRED
// LEDBLUE - Assigned to first LED (LED1)
// LEDYELLOW - Assigned to second LED (LED2)
// LEDGREEN - Assigned to third LED (LED3)
// LEDRED - Assigned to fourth LED (LED4)
void LedsON(LED_COLOR color);

//! Switch All Leds to OFF
void LedsOFF(void);
#endif /* CORE_SCREENS_H_ */
