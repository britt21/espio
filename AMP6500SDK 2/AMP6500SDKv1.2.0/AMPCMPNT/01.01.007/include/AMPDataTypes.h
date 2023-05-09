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
* File       	 : 		AMPDataTypes.h
* Library	 	 : 		AMP Component
* Date Coded  : 		03/24/2015
**************************************************************************/

#ifndef AMPDATATYPES_H_
#define AMPDATATYPES_H_

#include <sys/poll.h>
#include <stdint.h>
//#include <Directfb.h>

// NULL
#ifndef NULL
#define NULL (unsigned char)0
#endif

// BOOL, TRUE, FALSE
//#ifndef BOOL
//#define BOOL unsigned char
typedef unsigned char BOOL;
//#endif
#ifndef TRUE
#define TRUE (BOOL)1
#endif
#ifndef FALSE
#define FALSE (BOOL)0
#endif

//#ifndef UCHAR
typedef unsigned char UCHAR;
//#endif

//#ifndef UBYTE
typedef uint8_t UBYTE;
//#endif

//#ifndef BYTE
typedef uint8_t BYTE;
//#endif

//#ifndef USHORT
typedef unsigned short USHORT;
//#endif

//#ifndef UWORD
typedef uint16_t UWORD;
//#endif

//#ifndef UINT
typedef uint32_t UINT;
//#endif

typedef uint32_t UINT32;

typedef uint64_t UINT64;

//#ifndef ULONG
typedef unsigned long ULONG;
//#endif

//! Type Definition of AMPFont
//typedef IDirectFBFont AMPFont;

//! For IPC Comms
//typedef int IPC_HANDLE;

//! Handle for Events Queue (File Descriptor)
//typedef int EVT_HANDLE;

//! For polling file descriptors
//typedef struct pollfd POLL_FD;

typedef long DWORD;
typedef void *LPVOID;

//! Comms Handle
typedef long COMM_HANDLE;


//typedef DFBRectangle RECT;
//typedef DFBPoint POINT;
//typedef IDirectFBImageProvider IMGPROV;
//typedef IDirectFBSurface SURFACE;

#endif /* AMPDATATYPES_H_ */
