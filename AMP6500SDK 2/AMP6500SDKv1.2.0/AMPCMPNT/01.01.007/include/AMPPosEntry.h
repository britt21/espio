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
* File       	 : 		AMPPosEntry.h
* Library	 	 : 		AMP Component
* Date Coded  : 		08/27/2015
**************************************************************************/

#ifndef AMPPOSENTRY_H_
#define AMPPOSENTRY_H_

#include "AMPUIDisplay.h"
#include "AMPUtils.h"


// Definitions for AMP POS Entry Input Methods

#define INP_METH_NUM_ONLY		0x00
#define INP_METH_NUM_WITH_PUNC	0x01
#define INP_METH_NUM_WITH_DOT	0x02
#define INP_METH_ALPHA_ONLY		0x03
#define INP_METH_ALPHA_NUMERIC	0x04
#define INP_METH_ALL_KEYS		0x05
#define INP_METH_BINARY_ONLY	0x06
#define INP_METH_HEX_ONLY		0x07
#define INP_METH_CUSTOMKEY_MAP	0x08
#define INP_METH_AMOUNT			0x09
#define INP_METH_CARD_NUMBER	0x0A
#define INP_METH_PASSWORD		0x80	// Shows the number (or letter) entered, then updates into mask character (*) after a few seconds
#define INP_METH_PW_STRICT_MASK	0x40	// Shows only mask character (*). Hides the number/letter entered completely

#define CUR_SYMBOL_SIZE			3		/* USD for $, PND for Pound       */

typedef UBYTE INPUT_METHOD;

typedef enum
{
	CHAR_NULL = 0,
	CHAR_ADD_CHAR,
	CHAR_REPLACE_CHAR
}
KEYMAP_CHAR;


#define MAX_ALPNUM_KEYS		10	// representing the 10 keys of AMP POS terminal
#define CHAR_PER_KEY		36	// up to 35 chars per key, extra byte for null, 35 + 1 = 10

// Input Box Default Coordinates and Dimensions
#define DEF_INPUTBOX_X_ROW		10
#define DEF_INPUTBOX_Y_COL		160//140
#define DEF_INPUTBOX_WIDTH		300
#define DEF_INPUTBOX_HEIGHT		35//40

// Input Box Default Border Width
#define DEF_INPUTBOX_BORDER_WIDTH	0

// Input Box Default Font and Size
#define DEF_INPUTBOX_FONT_NAME	"../fonts/courbd.ttf"
#define DEF_INPUTBOX_FONT_SIZE	18

// Input Box Default Timeout
#define DEF_INPUTBOX_TIMEOUT	30

// Handle Key return values
#define POSENTRY_CONTINUE		-1000
#define POSENTRY_NO_KEY_UPDATE	-1001
#define POSENTRY_EXIT			-2000
#define POSENTRY_CANCEL			AMP_CANCEL

// Inter character delay/timer
#define POSENTRY_INTERCHAR_DELAY	2000	// in milliseconds

// Default Character Mask
#define DEFAULT_CHAR_MASK		'*'

#if 0
class cAMPPosEntry {

  public:
	//! Constructor
	cAMPPosEntry(char *szInputStr, INPUT_METHOD InputMethod, int MaxLength, int MinLength, 
				char *FieldFormat, char Mask, char *CurrSymbol, ALIGNMENT CurrSymbolAlign, ALIGNMENT align,
				char *CustomKeyMap[MAX_ALPNUM_KEYS][CHAR_PER_KEY],
				long TimeOut = DEF_INPUTBOX_TIMEOUT,								// Default timeout (in SECONDS) for Input box
				AMPFont *pFont = NULL, 												// Default font pointer is NULL
				int X = DEF_INPUTBOX_X_ROW, int Y = DEF_INPUTBOX_Y_COL,				// Default values for X and Y coordinates of Input box
				int Width = DEF_INPUTBOX_WIDTH, int Height = DEF_INPUTBOX_HEIGHT);	// Default Width and Height of Input box

	//! Destructor
	virtual ~cAMPPosEntry();

	//! Runs the entry object
	virtual void Run();

	//! Setup the key map
	virtual int SetupKeyMap();

	//! Gets the result
	int GetResult();

	//! Gets the entered text
	void GetFieldText(char *szBuffer);
	

  protected:
	//! Constructor  	
	cAMPPosEntry();
	
	//! Setup AMPPOS Entry
	virtual void SetupEntry(char *szInputStr, INPUT_METHOD InputMethod, int MaxLength, int MinLength,
				char *FieldFormat, char Mask,  char *CurrSymbol, ALIGNMENT CurrSymbolAlign, ALIGNMENT align,
				char *CustomKeyMap[MAX_ALPNUM_KEYS][CHAR_PER_KEY],
				long TimeOut = DEF_INPUTBOX_TIMEOUT,								// Default timeout (in SECONDS) for Input box
				AMPFont *pFont = NULL, 												// Default font pointer is NULL
				int X = DEF_INPUTBOX_X_ROW, int Y = DEF_INPUTBOX_Y_COL, 			// Default values for X and Y coordinates of Input box
				int Width = DEF_INPUTBOX_WIDTH, int Height = DEF_INPUTBOX_HEIGHT);	// Default Width and Height of Input box

	//! Setup the font to use
	virtual void SetupFont(AMPFont *pFont=NULL);

	//! Process the entered key (updates the FieldText and the DisplayBuffer)
	virtual int HandleKey(unsigned short Key);

	//! Initialize Display
	virtual void InitDisplay();

	//! Updates the entry object display
	virtual void UpdateDisplay(BOOL bUpdateForPasswordChar=FALSE);

	//! Perform display update for special cases
	virtual BOOL UpdateDisplaySpecialCase(void);

	//! Sets the initial value of Input Box
	void SetFieldText(char *szInputStr);
	//! Sets the field format
	void SetFieldFormat(char *format);
	//! Sets the field mask
	void SetFieldMask(char mask);
	//! Sets the currency symbol
	void SetCurrencySymbol(char *curr);

	//! Gets a character from the KeyMap based on the keypressed, returns the status if CHAR_NULL, CHAR_SAME_CHAR, or CHAR_NEW_CHAR
	KEYMAP_CHAR GetCharFromKeyMap(unsigned char Key, char *Char);
	//! Updates the IsFieldTextFull status
	void UpdateFldTextFullState();
	//! Adds a character to FieldText
	void AddFieldChar(unsigned char Char);
	//! Removes the last character from FieldText
	void RemoveFieldChar();
	//! Replaces the last character from FieldText
	void ReplaceLastFieldChar(unsigned char Char);
	//! Updates CurrentKey and KeyMapCharIndex when ALPHA key is pressed
	void UpdateCurrKeyMapCharIndex(void);
	
	virtual void EntryBeep();

  protected:
  	
	//! Holds the field data
	char *FieldText;
	//! Holds the field mask
	char FieldMask;
	//! Indicates the input method for the field
	INPUT_METHOD FieldInputMethod;
	//! Minimum field length
	int FieldMinLength;
	//! Maximum field length
	int FieldMaxLength;
	//! Timeout value (in seconds)
	long TimeOut;

	//! Holds the field format (Amount format or Normal entry-NULL)
	char *FieldFormat;
	//!Holds the field currency symbol
	char *CurrencySymbol;
	//! Currency symbol alignment
	ALIGNMENT CurrSymbolAlign;
	//! Left/Center/Right justified text during entry
	ALIGNMENT Justification;

	//! Holds the value of current Key pressed
	unsigned short CurrentKey;
	//! Char index holder for the KeyMap
	int KeyMapCharIndex;
	//!Current string length of FieldText
	int CharOffset;
	//! TRUE if Text Field reached max length
	BOOL IsFieldTextFull;
	//! Pointer to display buffer
	char *DisplayBuffer;
	
	//! Clear on invalid entry flag
	BOOL ClearOnInvalid;
	//! Indicates whether the field has been modified TRUE/FALSE
	BOOL IsModified;

	//! Holds the allowable key presses KeyMap
	char *LocalKeyMap[MAX_ALPNUM_KEYS][CHAR_PER_KEY];
	//! Holds the custom key map
	char *CustomKeyMap[MAX_ALPNUM_KEYS][CHAR_PER_KEY];

	//! Length of data entry field
	int EntryResult;

	//! Font filename used for entry
	char FontFile[MAX_STR_SZ];
	//! Font size used for entry
	int FontSize;
	//! X coordinate of input box
	int X;
	//! Y coordinate of input box
	int Y;
	//! Width of input box
	int Width;
	//! Height of input box
	int Height;
	
  private:
	//! Pointer to the font used for AMPPOS entry
	AMPFont *m_Font;
	
	//! Pointer to class name
	static char m_className[];
};
#endif
#endif /* AMPPOSENTRY_H_ */
