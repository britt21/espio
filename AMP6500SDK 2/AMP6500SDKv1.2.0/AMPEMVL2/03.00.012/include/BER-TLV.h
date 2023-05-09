
#ifndef __BER_TLV_H
#define __BER_TLV_H

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
* File       	 : 		BER-TLV.h
* Library	 	 : 		AMP Component
* Date Coded  : 		11/04/2015
**************************************************************************/

#include <stdlib.h>
//#include <AMPUtils.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef u_short ERROR_CODE;


// ERROR_CODEs returned by API functions below.
#define ERR_BER_TLV_BUFFER_OVERRUN			1
#define ERR_BER_TLV_FORMAT					2
#define ERR_BER_TLV_ELEMENT_NOT_PRESENT		3
#define ERR_BER_TLV_ELEMENT_NOT_EXPECTED	4



/* Masks on tag bytes. */
#define BER_TLV_TAG_MASK_CLASS	0xC0	/* 0b11000000. */
#define BER_TLV_TAG_MASK_FORM	0x20	/* 0b00100000. */
#define BER_TLV_TAG_MASK_NUMBER	0x1F	/* 0b00011111. */
#define BER_TLV_TAG_MASK_MORE	0x80	/* 0b10000000. */


/* Masks on first length byte. */
#define BER_TLV_LEN_MASK_MULTI	0x80	/* 0b10000000. */
#define BER_TLV_LEN_MASK_LENGTH	0x7F	/* 0b01111111. */


#define bIsConstructed(byTag)	((byTag & BER_TLV_TAG_MASK_FORM) != 0)
#define byTagClass(byTag)	(u_char) (((u_char) byTag & BER_TLV_TAG_MASK_CLASS) >> 6)

#define TAG_DET(abyT)	abyT, sizeof abyT

typedef enum
{
	LEN_OK = 0,
	LEN_INDEFINITE,
	LEN_INVALID

} LENGTH_STATUS;


#define BER_TLV_SIZE_TAG	4

typedef struct BER_TLV
{
	/*
	 * Tag, length and value triplet as in ISO8825.
	 *
	 * The length of the tag field is limited to the size of the abyTag array
	 * below (currently four bytes).  The handling code is written so that if
	 * extra space is required, increasing the size of this array is all that
	 * needs to be done.
	 *
	 * The length is limited to that which can be stored in four bytes (sizeof
	 * (u_long)) in this implementation, even though the standard allows a length
	 * specifier up to 127 bytes long.  This reduces the range of lengths from
	 * 2^1016-1 to just 2^32-1, which is still plenty (4GB) for all practical
	 * applications.
	 */
	u_char abyTag[BER_TLV_SIZE_TAG];
	u_long ulnLen;
	u_char *pbyValue;

	/*
	 * Constructed elements have zero or more child elements, each of which is a
	 * BER-TLV element and can have either simple or constructed form.
	 */
	struct BER_TLV *pstChild;

	/*
	 * When an element is a child of a constructed element, this pstNext will
	 * point to the next child element of the constructed element.
	 */
	struct BER_TLV *pstNext;

	/* The amount of memory allocated to the tag. */
	u_char byTagLen;

} BER_TLV;

typedef ERROR_CODE (*EL_VARIABLE_FN)(void *pvVar, BER_TLV *pstEl);

typedef enum
{
	AT_REQUIRED,
	AT_OPTIONAL

} ALLOW_TYPE;


typedef struct
{
	const u_char *pbyTag;
	u_char byTagLen;
	ALLOW_TYPE eReqd;
	EL_VARIABLE_FN pfnVarFn;

} ALLOW_ENTRY;


typedef struct
{
	const u_char *pbyTag;
	int nTagLen;
	const u_char *pbyTagEquiv;
	int nTagEquivLen;

} TAG_EQUIV;


typedef void *(*TLV_CALLOC)(size_t nmemb, size_t size);
typedef void (*TLV_FREE)(void *ptr);

void vTLV_set_calloc(TLV_CALLOC pfnCalloc, TLV_FREE pfnFree);


/*
 * Interpret a string of bytes as an ISO8825 tag specifier.
 *
 * Returns,
 * Status of the interpretation.
 *
 * Parameters.
 * pstTLV Out.
 *   Tag-length-value-triplet-containing structure.  Tag length field used to
 *   indicate whether tag is valid.  It will be non-zero for a valid tag.
 *
 * pulnBufUsed Out.
 *  *pulnBufUsed is the number of bytes of the buffer used to make the tag.
 *  *pulnBufUsed is undefined if not successful.
 *
 * pbyBuf In.
 *   pbyBuf points to the start of the buffer.
 *
 * ulnBufLen In.
 *   Length of buffer (pointed to by pbyBuf) available.
 */
ERROR_CODE usnTLV_get_BER_tag
(
	BER_TLV *pstTLV,
	u_long *pulnBufUsed,
	u_char *pbyBuf,
	u_long ulnBufLen
);

ERROR_CODE usnTLV_parse_buffer
(
	BER_TLV *pstTLV,
	u_char *pbyBuf,
	u_long ulnBufLen
);

ERROR_CODE usnTLV_parse_buffer_includechild
(
	BER_TLV *pstTLV,
	u_char *pbyBuf,
	u_long ulnBufLen
);

ERROR_CODE usnTLV_flatten_element
(
	u_char *pbyBuf,
	u_long *pulnBufUsed,
	u_long ulnBufLen,
	BER_TLV *pstEl,
	u_char bFollow
);

BER_TLV *pstTLV_make_element(void);
BER_TLV *pstTLV_insert_element(BER_TLV *pstEl);
BER_TLV *pstTLV_append_element(BER_TLV *pstEl);
void vTLV_destroy_element(BER_TLV *pstEl);

void vTLV_print_element(BER_TLV *pstEl, u_char byLvl, u_char bFollow);
void vTLV_send_element(int nFD, BER_TLV *pstEl, u_char bFollow);

BER_TLV *pstTLV_find_element(BER_TLV *pstEl, const u_char *pbyTag, u_char byTagLen);
BER_TLV *pstTLV_find_element_includechild(BER_TLV *pstEl, const u_char *pbyTag, u_char byTagLen);

void vTLV_set_up_primitive_element
(
	BER_TLV *pstEl,
	const u_char *pbyTag,
	u_char byTagLen,
	u_char *pbyValue,
	u_long ulnLen
);

BER_TLV *pstTLV_make_primitive_element
(
	const u_char *pbyTag,
	u_char byTagLen,
	u_char *pbyValue,
	u_long ulnLen
);

void vTLV_remove_element(BER_TLV *pstEl);


/*
 * Check that all the required elements in the list of allowed elements are
 * present in the command and that all the elements in the command are present
 * in the list.
 */
ERROR_CODE usnTLV_check_tags(BER_TLV *pstCmd, const ALLOW_ENTRY *pstList);

/**
 *  Rafal_P2:
 *  Check that every required element is present in the template
 *  and every element from template is defined in the list
 *
 *  @param pBufMissing  buffer to store all missing tags
 *  @param pLenMissing  [in]  pointer to pLenMissing buf. length
 *                      [out] length of returned data in bytes
 *  @param pBufNotExpd  buffer to store all not expected tags
 *  @param pLenNotExpd  [in]  pointer to pBufNotExpd buf. length
 *                      [out] length of returned data in bytes
 */
ERROR_CODE usnTLV_check_all_tags
(
	BER_TLV *pstCmd, const ALLOW_ENTRY *pstList,
	u_char *pBufMissing, u_long *pLenMissing,
	u_char *pBufNotExpd, u_long *pLenNotExpd
);

/*
 * When using this function, make sure any memory allocated by the called
 * functions is freed after use in the calling function.
 */
ERROR_CODE usnTLV_fill_command_arguments
(
	void *pvVar,
	BER_TLV *pstCmd,
	const ALLOW_ENTRY *pstList
);


/*
 * Convert the tag field of a BER_TLV structure according to the specified tag
 * equivalent table.
 *
 * Returns,
 * AMP_SUCCESS if conversion is successful. Oherwise an error code is returned.
 *
 * Parameters.
 * pbyTags Out.
 *   Tag-length-value-triplet-containing structure to be updated.
 *
 * pstTagEquivTable In.
 *   Table of BER-TLV tags with equivalent tags for conversion purposes.
 *
 *   Sample Table.
 *
 *   static const uint8_t abyDF01[] = { 0xDF, 0x01 };
 *   static const uint8_t abyDF02[] = { 0xDF, 0x02 };
 *   static const uint8_t abyDF8101[] = { 0xDF, 0x81, 0x01 };
 *   static const uint8_t abyDF8102[] = { 0xDF, 0x81, 0x02 };
 *
 *   static const TAG_EQUIV astTagConvTable[] =
 *   {
 *       { TAG_DET(abyDF01), TAG_DET(abyDF8101) },
 *       { TAG_DET(abyDF02), TAG_DET(abyDF8102) },
 *
 *       { NULL, 0, NULL, 0 } // NB: This entry is required.
 *   };
 *
 * bReverse In.
 *   If bReverse is FALSE, tags in the input BER_TLV string found in column 1
 *   of the conversion table will be converted to the equivalent tag from
 *   column 2. Setting bReverse will reverse the procedure.
 *
 * Example.
 *   Using the above table, the input string
 *
 *       DF01 01 AA DF03 01 BB DF02 02 CCDD
 *
 *   is converted to
 *
 *       DF8101 01 AA DF03 01 BB DF8102 02 CCDD
 *
 *	assuming bReverse is FALSE.
 *
 *  Settng bReverse will convert the output back to the original input again.
 *
 */
ERROR_CODE usnTLV_convert_BER_tags
(
	BER_TLV *pstTags,
	const TAG_EQUIV *pstTagEquivTable,
	u_char bReverse
);


/*
 * Convert the tag field of a BER_TLV string according to the specified tag
 * equivalent table.
 *
 * Returns,
 * AMP_SUCCESS if conversion is successful. Oherwise an error code is returned.
 *
 * Parameters.
 * pbyOutTags Out.
 *   The resulting BER-TLV string.
 *
 * pulnOutTagLen Out.
 *   The resulting BER-TLV string length.
 *
 * ulnMaxOutTagLen In.
 *   The maximum allowed output BER-TLV string length.
 *
 * pbyInTags In.
 *   The BER_TLV string to be converted.
 *
 * ulnInTagLen In.
 *   Length of the BER_TLV string to be converted.
 *
 * pstTagEquivTable In.
 *   Table of BER-TLV tags with equivalent tags for conversion purposes.
 *
 *   Sample Table.
 *
 *   static const uint8_t abyDF01[] = { 0xDF, 0x01 };
 *   static const uint8_t abyDF02[] = { 0xDF, 0x02 };
 *   static const uint8_t abyDF8101[] = { 0xDF, 0x81, 0x01 };
 *   static const uint8_t abyDF8102[] = { 0xDF, 0x81, 0x02 };
 *
 *   static const TAG_EQUIV astTagConvTable[] =
 *   {
 *       { TAG_DET(abyDF01), TAG_DET(abyDF8101) },
 *       { TAG_DET(abyDF02), TAG_DET(abyDF8102) },
 *
 *       { NULL, 0, NULL, 0 } // NB: This entry is required.
 *   };
 *
 * bReverse In.
 *   If bReverse is FALSE, tags in the input BER_TLV string found in column 1
 *   of the conversion table will be converted to the equivalent tag from
 *   column 2. Setting bReverse will reverse the procedure.
 *
 * Example.
 *   Using the above table, the input string
 *
 *       DF01 01 AA DF03 01 BB DF02 02 CCDD
 *
 *   is converted to
 *
 *       DF8101 01 AA DF03 01 BB DF8102 02 CCDD
 *
 *	assuming bReverse is FALSE.
 *
 *  Settng bReverse will convert the output back to the original input again.
 *
 */
u_short usnTLV_convert_tags
(
	u_char *pbyOutTags,
	u_long *ulnOutTagLen,
	u_long ulnMaxOutTagLen,
	u_char *pbyInTags,
	u_long ulnInTagLen,
	const TAG_EQUIV *pstTagEquivTable,
	u_char bReverse
);

#ifdef __cplusplus
}
#endif

#endif /* __BER_TLV_H */

