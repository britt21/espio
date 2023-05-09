/*
 * tlvdefs.h
 *
 *  Created on: Jul 16, 2014
 *      Author: amadis
 */

#ifndef TLVDEFS_H_
#define TLVDEFS_H_

typedef enum
{
	CURSOR_IDLE,				 // Cursor in initial position (after initTlv() or resetCursor())
	CURSOR_TAG_READ,             // Cursor positioned at the end of the current Tag
	CURSOR_LENGTH_READ,          // Cursor positioned at the end of the current Length
	CURSOR_ELEMENT_SELECTED,     // Cursor positioned at the end of the current TLV Element
	CURSOR_ERROR                 // Cursor error due to inconsistent TLV Element
} cursor_state_t;

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct
{
	unsigned char number      : 5;
	unsigned char constructed : 1;
    unsigned char classe       : 2;
} tag_field_t;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct
{
	unsigned char number  : 7;
	unsigned char another : 1;
} subsequent_field_t;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
union _tag_first_u
{
	byte_t value;
	tag_field_t field;
};
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
union _subsequent_u
{
	byte_t value;
	subsequent_field_t field;
};
#ifdef PACKING
#pragma pack()
#endif


typedef union _tag_first_u  tag_first_t;
typedef union _subsequent_u tag_subsequent_t;
typedef union _subsequent_u length_first_t;

#ifdef PACKING
#pragma pack(1)
#endif
typedef struct
{
	tag_value_t   value;        //!< Original Value of the Tag (as read from data stream)
	int           size;         //!< Number of bytes encoding the Tag
	tag_first_t   first;        //!< First byte of the tag
	tag_number_t  number;       //!< Tag Number (index)
} tag_t;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct
{
	byte_t   *ptr;         //!< Pointer at beginning of current element
	tag_t    tag;          //!< Tag of the current element
	length_t length;       //!< Length of the current element
	byte_t   *value;       //!< Pointer to Value of the current element
} tlv_t;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
typedef struct
{
	byte_t   *ptr;         //<! Pointer on source buffer
	length_t max;          //<! Size of source buffer (space available for adding new tags)
	length_t content;      //<! Length of actual content
} data_t;
#ifdef PACKING
#pragma pack()
#endif


#ifdef PACKING
#pragma pack(1)
#endif
struct _cursor_t
{
	data_t         data;
	byte_t         *next;
	length_t       remaining;
	cursor_state_t state;
	tlv_t          tlv;
};
#ifdef PACKING
#pragma pack()
#endif


#endif /* TLVDEFS_H_ */
