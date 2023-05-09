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
* File       	 : 		AMPMenuBase.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/24/2015
**************************************************************************/

#ifndef AMPMENUBASE_H_
#define AMPMENUBASE_H_

// Project Header
#include "AMPDataTypes.h"
#include "AMPUIDisplay.h"

//4 ROOT MENU
#define MENU_MAIN					0x10000000
#define MENU_DESKTOP				0x10000001

//4 Return value identifier for menu function  (go back to Idle or go back to last menu)
#define RETURN_IDLE				1000
#define RETURN_LAST_MENU		2000
#define RETURN_DESKTOP			3000
#define RETURN_MAIN_MENU		4000

//4 Menu screen coordinates configuration
//! Number of menu items shown on screen
#define NUM_MENUITEMS_ONSCREEN		4
//! Height gap/interval between Menu Title and the first Menu item
#define Y_GAP_MENUTITLE				15
//! Height gap/interval between each menu items
#define Y_GAP_MENUITEMS				8
//! Width gap between the leftmost/rightmost screen
#define X_GAP_MENUITEMS				10

//4 Menu Levels (Stack)
#define MAX_MENU_LEVELS				15

#define MAX_MENU_STR_LEN			50
#define MAX_MENU_DIR_LEN			MAX_IMGFILENAME_LEN

//! Main Menu ID - Assign this Value to the main menu
//#define MENU_MAIN	0x1000


//! Menu items structure
typedef struct menu_item
{
	//! Enable function, return TRUE to Enable, FALSE to Disable
	BOOL ( *pEnableFunc ) ( void );	
	//! Check access function return TRUE to gain access, FALSE to deny access
	BOOL ( *pCheckAccessFunc ) ( void );
	//! Menu Item Text/String
	char MenuItemText[MAX_MENU_STR_LEN];
	//! Menu Item Picture/Background
	char MenuItemPic[MAX_MENU_DIR_LEN];
	//! Function pointer for this Menu Item
	//int ( *pEventFunc ) ( void );
	//! Function ID for this Menu Item
	ULONG EventID; 
}
MENU_ITEM;

//! Menu Entry structure
typedef struct menu_entry
{
	//! Menu id of this table from transdef.h
	ULONG menuID;			
	//! Overall Enable function return TRUE to Enable, FALSE to Disable
	BOOL ( *pEnableFunc ) ( void );
	//! Check access function return TRUE to gain access, FALSE to deny access
	BOOL ( *pCheckAccessFunc ) ( void );
	//! Draw sub menus as items inside a folder icon
	BOOL ( *pDrawSubMenusInFolder ) ( void );
	//! Menu Title
	char MenuTitle[MAX_MENU_STR_LEN];
	//! Pointer to the list of menu items on this menu
	MENU_ITEM *pMenuList;	 
	//! size in items of MENUITEM list pointed to by pMenuList
	UBYTE MenuSize;
	//! menu type as defined by enum MENU_TYPE
	//MENU_TYPE Type;				
}
MENU_ENTRY;


//! 
typedef int (*XCALL_T)(void);

//! Function Entry structure
typedef struct function_entry
{
    ULONG FUNCKEY;				// Function Key
    XCALL_T Func_Handler;		// Cross-Call action handler
    char FUNCTEXT[50];			// Transaction description
    UBYTE TRNOPT1;				// OPTIONS BYTE 1
    UBYTE TRNOPT2;				// OPTIONS BYTE 2
    UBYTE TRNOPT3;				// OPTIONS BYTE 3
    UBYTE TRNOPT4;				// OPTIONS BYTE 4
//    UWORD NEXTEVENT;			// trnkey for next triggered event
}
FUNCTION_ENTRY;


class cAMPMenuBase
{
  public:
	//!Constructor
	cAMPMenuBase();
	//!Destructor
	virtual ~cAMPMenuBase();

	//!Prepares the menu for use.
	virtual int Initialize(MENU_ENTRY *pMenuEntryTbl, int nMenuCount, FUNCTION_ENTRY *pFuncEntryTbl, int nFuncCount) = 0;
	//!Pass an event into this method to process it using the currently selected menu.
	virtual int ProcessEvent(long lnEventCode) = 0;
	//!Executes the menu to the point where it is ready to process events.
	virtual int RunMenu(int RunCode) = 0;
	//!Builds the menu display by selecting items by MenuID.
	virtual int SelectMenu(ULONG MenuID) = 0;
	//!Redisplays the current Menu ID (useful for scenarios wherein current Menu needs to be redisplayed)
	virtual int RefreshDisplay(void) = 0;
	//!Add an item to the menu display with a pointer to the item.
//	virtual int AddMenuItem(long MsgID, void *MenuItem);

	//!Gets a pointer to a specific menu entry from the list
	MENU_ENTRY* GetMenu(ULONG MenuID);
	//!Draws the selected menu
	virtual void DrawMenu() = 0;
	//!Sets the text for the menu title.
	virtual int SetMenuTitle(char * MsgText);
	//!Sets the menu font file
	virtual void SetMenuFont(const char *FontFileName, int FontSize);
	//!Sets the font for menu items
	virtual void SetMenuItemFont(const char *FontFileName, int FontSize);
	//! Sets the alignment of Menu Items (ALIGN_LEFT / ALIGN_CENTER / ALIGN_RIGHT)
	virtual void SetAlignItems(ALIGNMENT Align);

	//!Pushes the current menu ID in the menu stack
	virtual int PushMenu();
	//!Pops the menu ID from the menu stack
	virtual int PopMenu();

	//!Returns TRUE if the Function ID exists in the Function Table
	virtual BOOL IsFunction(ULONG FunctionID);
	//!Gets a pointer to a specific function entry from the Function Table
	FUNCTION_ENTRY* GetFunction(ULONG FuncID);

	//!Sets the Demo Mode to Enabled/Disabled (to display or not to display "Demo Mode" on the menu screen)
	virtual void EnableDemoMode(BOOL bEnable) = 0;

	//! Gets the current Menu ID displayed
	virtual ULONG GetCurrentMenuID(void);
	
  protected:

	//! Menu Entries List
	MENU_ENTRY *m_MenuEntryTbl;
	//! Number of Menu Entries in the list
	int m_nMenuCount;
	//! Holds the current menu ID of menu displayed
	ULONG m_lnCurrentMenuID;
	//! Holds the ID of the current menu item to be displayed first
	int m_nCurrentMenuItemID;
	//! Index of the currently highlighted item
	int m_nCursorIndex;

	//4 Handles the Menu Stack
	//! Holds the stack of menu IDs and items for user browsing of menus (idx0=MenuID, idx1=MenuItemID, idx3=MenuCursorIndex)
	ULONG m_nStackMenuIDs[MAX_MENU_LEVELS][3];
	//! Holds the current stack level for menu
	int m_nStackMenuLevel;

	//! Function Table
	FUNCTION_ENTRY *m_FuncEntryTbl;
	//! Number of Function Entries in the list
	int m_nFuncCount;

	//! Menu Font
	//AMPFont *m_MenuFontTitle;
	//AMPFont *m_MenuFontItems;

	//! Menu Font Filenames
	char *m_MenuFontFileTitle;
	char *m_MenuFontFileItems;

	//! Menu Font Size
	int m_MenuFontSizeTitle;
	int m_MenuFontSizeItems;

	//! Alignment of Menu Items - ALIGN_LEFT / ALIGN_CENTER / ALIGN_RIGHT
	ALIGNMENT m_nAlignItems;

	//! Holds the highlight colors
	//RGB_COLOR m_bgHighLite;
	//RGB_COLOR m_fgHighLite;

	//! Demo Mode Enabled/Disabled
	BOOL m_bDemoMode;

  private:

	//! Pointer to class name
	static char m_className[];
};

#endif /* AMPMENUBASE_H_ */
