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
* File       	 : 		AMPPrinter.h
* Library	 	 : 		AMP Component
* Date Coded  : 		06/30/2015
**************************************************************************/

#ifndef AMPPRINTER_H_
#define AMPPRINTER_H_

//Project Header
#include "AMPDataTypes.h"
//#include "Directfb.h"
//#include <printer.h>
#include "AMPUIDisplay.h"
#include <jni.h>

#include "tinyxml2.h"

//! Printer Color Definitions
typedef enum
{
	PRINT_BLACK = 0,
	PRINT_WHITE
}
PRINTER_COLOR;

using namespace tinyxml2;

class cAMPConfig;

class cAMPPrinter
{
  public:

		//! Constructor
		cAMPPrinter();

		//! Destructor
		//! Surface/Drawing Release
		virtual ~cAMPPrinter();
		
//		void setPrinterObj(JNIEnv*, jobject, jobject);

		//! Initialization of Surface Description
		int Initialize(void);

		//! Open Printer Device
		int Open(void);

		//! Close Printer Device
		int Close(void);

		//! Check Printing Status
		int Status(void);
		int printStatus(void);

		//! Printing of Image/Logo
		void Logo(const char *Filename);

		//! Set Clear Surface
		void Clear(void);

		//! Set Font and Object color
		void SetColor(PRINTER_COLOR ColorID);

		//! Set Gray Value (Contrast - clear printing VS speed)
		void SetGray(int GrayValue);

		//! Surface Print String
		void PrintString(const char * Text, ALIGNMENT Alignment);

		void PrintStringColumn(const char *Text, ALIGNMENT Alignment);

		//! Customized Print String (Print starting point can be defined using variable fColStart : Value ranges from 1-100, based on percentage)
		void PrintStringCustomized(float fColStart, const char *Text, ALIGNMENT Alignment);

		//! Print String Next line Adjustment
		void NextLine(void);

		//! Print Border Line
		void BorderLine(void);

		//! Print Box
		void PrintCheckBox(int nRectStartX, int nRectStartY, int nRectWidth, int nRectHeight);

		//! Set Outside Border
		void StartOutsideBorder(void);

		//! End Outside Border
		void EndOutsideBorder(void);

		//! Inverse Text on top of the drawn rectangle and set the text color to white
		void SetInverse(BOOL bInverse);
		
		//! Set Text Font and Size
		void SetFont(const char *FontFileName, int nFontSize);

		//! Output the content of DirectFB Surface
		void Print(void);
		void PrintLast();
		void PrintLast(BOOL emailPdf, const char *FileName);

		//! Get Current Feed Data
		//int FeedGetData(int nfd, printer_lifetime_data_t *param);

		//! Check for Thermal Printer support and Get Current Feed Steps data
		int FeedGetStep(void);

		//! Feed an inch of paper
		void FeedPaper(void);

		//! Enable Receipt Printing
		void EnablePrinting(BOOL bEnable);

		//! Enable PDF Printing
		void EnablePDFPrinting(BOOL bEnable);

		//! Enable Auto Increment of PDF Page (Default value is TRUE)
		void SetPDFPageAutoIncrement(BOOL bAutoIncrement);

		//! Set the maximum height (for Auto Increment) of a PDF Page 
		void SetPDFPageMaxHeight(int nMaxHeight);

		//! Set PDF Printing to new page
		void SetNewPDFPage();

		//! Set LED Light
		void SetLedLight(int ledID, int ledStatus, int ledColor);

		// Set LED Light Success
		void SetLedSuccess();

		//! Get instance of Printer Object
		static cAMPPrinter* getPrinterObj();

  protected:
  	
		//! Get the string to be adjusted for next line printing based on the nearest space character that exist
		char * GetAdjustString(char *string, char *findChar);

		//! Find a specific character within the string (e.g. spaces)
		bool FindCharacter(char *string, char *findChar);
		
  protected:

		static cAMPPrinter* single_PrinterObj;
		
  private:

		//! DirectFB initialization that will manage the entire display windows
		//IDirectFB	*m_dfb;

		//! A reserved area of memory used to stored pixel data
		//IDirectFBSurface		*m_Surface;

		//! Set Surface Description
		//DFBSurfaceDescription	m_Surfdesc;

		//! Holds parameter for printer_get_param function
		//printer_param_t m_param;
		
		//! Holds parameter for printer_get_status function
		//printer_status_t m_status;

		//! Device File Number returned by printer_open function
		int m_ifd;

		//! Height Alignment
		int m_Current_YValue;
				
		//! Font Description Height
		int m_FontHeight;

		//! Flag for PrintString
		BOOL m_InverseFlag;

		//! Flag for Drawn Rectangle
		BOOL m_RectDrawn;

		//! Class Name Definition
		static char m_className[];

		//! Pointer for Font definition
		//AMPFont *pFont;

		//! Font Size global
		int m_gFontSize;

		//! Font Name
		const char* m_gFontFileName;

		//! Printer Current Feed length
		int m_CurFeedStep;

		//! XML object for building Printer instructions
		XMLDocument *m_pXMLStream;

};


#endif /* AMPPRINTER_H_ */
