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
* File       	 : 		AMPUIDisplay.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/22/2015
**************************************************************************/

#ifndef AMPUIDISPLAY_H_
#define AMPUIDISPLAY_H_

#include "AMPDataTypes.h"

typedef struct
{
	UBYTE R;
	UBYTE G;
	UBYTE B;

}	RGB_COLOR;

// Led ID
typedef enum {
	LED1	= 0x01,
	LED2	= 0x02,
	LED3	= 0x03,
	LED4	= 0x04,
	LEDALL	= 0x05,
} LED_ID;

typedef enum {
	LEDOFF	= 0x00,
	LEDON	= 0x01,
	LEDFLASH = 0x02,
} LED_STATUS;

typedef enum {
	LEDNONE = 0x00,
	LEDBLUE = 0x01,
	LEDYELLOW = 0x02,
	LEDRED = 0x03,
	LEDGREEN = 0x04,
} LED_COLOR;


//!Text/Image/Icon Alignment Definitions
#define ALIGN_NONE			0x0000
#define ALIGN_ABSOLUTE_X	0x0001
#define ALIGN_ABSOLUTE_Y	0x0002
#define ALIGN_LEFT			0x0004
#define ALIGN_CENTER		0x0008
#define ALIGN_RIGHT			0x0010
#define ALIGN_TOP			0x0020
#define ALIGN_BOTTOM		0x0040
#define ALIGN_VCENTER		0x0080

typedef uint16_t ALIGNMENT;

#define MAX_IMGFILENAME_LEN		60
#if 0
typedef struct
{
	char *szFileName;
	IMGPROV *pImgProv;
	SURFACE *pImgSurface;

} IMAGE_SCREEN_DATA;

const RGB_COLOR RGB_BLACK		= {0x00, 0x00, 0x00};
const RGB_COLOR RGB_BLUE		= {0x00, 0x80, 0xFF};
const RGB_COLOR RGB_GREEN		= {0x00, 0xFF, 0x00};
const RGB_COLOR RGB_RED			= {0xFF, 0x00, 0x00};
const RGB_COLOR RGB_BLUE_DARK	= {0x00, 0x00, 0xFF};
const RGB_COLOR RGB_YELLOW		= {0xFF, 0xFF, 0x00};
const RGB_COLOR RGB_GREEN_DARK	= {0x10, 0x60, 0x10};
const RGB_COLOR RGB_GREEN_BKGD	= {0x40, 0xFF, 0x40};
const RGB_COLOR RGB_GREEN_LIGHT	= {0x60, 0xFF, 0x60};
const RGB_COLOR RGB_GRAY		= {0x60, 0x60, 0x60};
const RGB_COLOR RGB_BLUE_LIGHT	= {0x80, 0xB0, 0xFF};
const RGB_COLOR RGB_WHITE		= {0xFF, 0xFF, 0xFF};


#define DISP_NOBACKGROUND	0x2000	//  display without background rectangle (TRANSPARENT)

class cAMPUIDisplay 
{
  public:
	static cAMPUIDisplay* getDisplayObj();
	
	//!Destructor
	virtual ~cAMPUIDisplay();

	//! Turns ON the display backlight
	void BacklightON(void);
	//! Turns OFF the display backlight
	void BacklightOFF(void);
	//! Gets the current size (Width and Height) of the Hardware Screen
	void GetScreenSize(int *nWidth, int *nHeight);
	//! Clears the entire screen (application screen and including the LED Display bar)
	void ClearAllScreen(void);
	//! Clears the screen
	void ClearScreen();
	//! Clears the line nRow
	void ClearLine(int nRow);
	//! Clears the area with Width and Height input, at X and Y coordinates
	void ClearArea(int X, int Y, int Width, int Height);
	//! Clears the area with RECT input
	void ClearArea(RECT rect);
	//! Sets the Background color
	void SetBackgroundColor(RGB_COLOR color);
	//! Sets the Foreground color
	void SetForegroundColor(RGB_COLOR color);
	//! Gets pointer to the font
	AMPFont* GetFont(const char *FontFileName, int FontSize);
	//! Sets the display font
	void SetFont(AMPFont *pFont);
	//! Sets the display font using filename (with Character Set)
	void SetFont(const char *FontFileName, const char *CharSet, int FontSize);
	//! Displays text at nCol and nRow coordinates
	void DisplayTextAt(int nCol, int nRow, const char *pText);
	//! Displays justified text at nRow
	void DisplayJustifiedText(int nRow, int nAlignment, int nMargin, const char *pText);
	//! Displays text at absolute X and Y coordinates
	void DisplayTextAtXY(int X, int Y, const char *pText);
	//! Displays justified text at absolute Y
	void DisplayJustifiedTextAtY(int Y, int nAlignment, int nMargin, const char *pText);
	//! Displays justified text at X, Y, Width, Height
	void DisplayText(int X, int Y, int Width, int Height, ALIGNMENT Alignment, const char *pText, RGB_COLOR TXTcolor);
	//! Displays justified text at RECT rcText
	void DisplayText(RECT rect, ALIGNMENT Alignment, const char *pText, RGB_COLOR TXTcolor);

	//! Draws a line
	void DrawLine(int X1, int Y1, int X2, int Y2, RGB_COLOR LineColor);
	void DrawLine(POINT a, POINT b, RGB_COLOR LineColor);
	//! Draws a rectangle at X and Y coordinates
	void DrawRectangle(int X, int Y, int Width, int Height, RGB_COLOR BorderColor, RGB_COLOR FillColor);
	//! Draws a rectangle at RECT rect
	void DrawRectangle(RECT rect, RGB_COLOR BorderColor, RGB_COLOR FillColor);
	//! Draws a 3D rectangle at RECT rect
	void Draw3dRectangle(RECT rect, RGB_COLOR Color1, RGB_COLOR Color2, RGB_COLOR FillColor);

	//! Gets the actual picture size (in pixels)
	int GetPictureSize(const char *FileName, int *Width, int *Height);
	//! Displays picture at X and Y coordinates
	void DisplayPicture(int X, int Y, int Width, int Height, const char *FileName);
	//! Displays picture at RECT rcPic
	void DisplayPicture(RECT rect, const char *FileName);

	//! Button Functions
	void ClearAllButtons(void);
	void AddButton(USHORT Key,  RECT rect);
	void AddTextButton(USHORT Key, RECT rect, const char *pText, RGB_COLOR BGcolor, RGB_COLOR TXTcolor, RGB_COLOR Bordercolor, int BorderWidth);
	void AddPictureButton(USHORT Key, RECT rect, const char *PicFileName, const char *pText, RGB_COLOR TXTcolor);
	void AddPictureButtonExt(USHORT Key, RECT rect, const char *PicFileName, const char *pText, RGB_COLOR TXTcolor,
							IMGPROV **ImgProv, SURFACE **ImgSurface);
	
	void UpdateTextButton(RECT rect, const char *pText, RGB_COLOR BGcolor, RGB_COLOR TXTcolor, RGB_COLOR Bordercolor, int BorderWidth);
	void UpdatePictureButton(RECT rect, const char *PicFileName, const char *pText, RGB_COLOR TXTcolor);
	void UpdatePictureButtonExt(RECT rect, const char *pText, RGB_COLOR TXTcolor, IMGPROV *ImgProv, SURFACE *ImgSurface);

	//! Adds picture to the memory
	void AddPictureExt(RECT rect, const char *PicFileName, IMGPROV **ImgProv, SURFACE **ImgSurface);
	//! Updates picture RECT to the memory
	void UpdatePictureExt(RECT rect, IMGPROV *ImgProv, SURFACE *ImgSurface);
	// Release picture from the memory
	void ReleasePictureExt(IMGPROV *ImgProv, SURFACE *ImgSurface);

	//! LED Functions

	//! Initialize LED Display for EMV Contactless
	void InitLed(void);
	//! Clears the LED Display bar
	void ClearLedScreen(void);
	//! Starts the timer for the LED Display update
	void StartLedTimer(void);
	//! Set Led Color
	void SetLedColor(unsigned char Led, unsigned char Status, unsigned char Colour);
	//! Get Status Bar Height
	int GetLedHeight(void);	
	//! Show Led Display and Re-start Timer
	void ShowLedDisplay(void);
	//! Hide Led Display and Clear Timer
	void HideLedDisplay(void);	

	//! Updates the Screen/Display
	void UpdateDisplay();

  protected:
	//!Constructor
	cAMPUIDisplay();
	static cAMPUIDisplay *createDisplayObj();

	DFBColor GetDFBColor(RGB_COLOR color);

	//! Pointer to Static cAMPUIDisplay Object
	static cAMPUIDisplay* UIDispObj;

  private:

	AMPFont *m_Font;

	int m_nScrnWidth, m_nScrnHeight;

	DFBColor m_bgColor;
	DFBColor m_fgColor;

	//! Pointer to class name
	static char m_className[];

};
#endif
#endif /* AMPUIDISPLAY_H_ */
