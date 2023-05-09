#ifndef TLV_H_
#define TLV_H_

/**
 * @file	tlv.h
 * @brief	BER-TLV Library
 * @author	Daniel Boucher (db@amadis.ca)
 * @date	Jul 16, 2014
 */

/**
 * @mainpage BER-TLV Library
 * @brief This library allows parsing of existing BER-TLV Data Object or create new ones
 * @section Content
 * - @ref constants	"Global Definitions"
 * - @ref cursor	"Cursor Functions"
 * - @ref selection "Selection Functions"
 * - @ref append    "Append Functions"
 * - @ref getters   "Getter Functions"
 */

/**
 * @defgroup constants Global Definitions
 * @brief Library Return Codes and Constants
 */
/*@{*/
// 'constants'

#if (defined(_WIN32) || defined(WIN32))
	#define DLLEXPORT	__declspec(dllexport)
#else
	#define DLLEXPORT
#endif

#define TLV_LIBRARY_VERSION	(char*)("1.0.8") //!< Current Version of this TLV Library

#define NEXT_OCCURRENCE		0	//!< Constant value for Next Occurrence from current Cursor Position

/// Definition of BER-TLV Tag Value data type
typedef unsigned long tag_value_t;
/// Definition of BER-TLV Tag Number data type
typedef unsigned long tag_number_t;
/// Definition of Length data type
typedef unsigned long length_t;
/// Definition of BYTE data type
typedef unsigned char byte_t;
/// Definition of Cursor data type
typedef struct _cursor_t  cursor_t;

///  Standard BER-TLV Tag Class
typedef enum
{
	CLASS_UNIVERSAL        = 0,		//!< Universal Class
	CLASS_APPLICATION      = 1,		//!< Application Class
	CLASS_CONTEXT_SPECIFIC = 2,		//!< Context Specific Class
	CLASS_PRIVATE          = 3		//!< Private Class
} tag_class_t;

#include "tlvdefs.h"

/// Return Codes of the BER-TLV Library Functions
typedef enum
{
	TLV_NO_ERROR,                      //!< Successful execution
	TLV_ERR_BAD_PARAMETER,             //!< Invalid Parameters passed in Function call
	TLV_ERR_END_REACHED,               //!< Unexpected end of cursor buffer reached
	TLV_ERR_WRONG_STATE,               //!< Wrong Cursor State to perform Operation
	TLV_ERR_TAG_TOO_LONG,              //!< Tag encoding is longer than supported
	TLV_ERR_LENGTH_TOO_LONG,           //!< Length coding is longer than supported
	TLV_ERR_REMAINING_TOO_SHORT,       //!< Actual content of Value is shorter than Length
	TLV_ERR_BAD_TAG,                   //!< Tag inconsistent with BER-TLV encoding rules
	TLV_ERR_BAD_LENGTH,                //!< Length inconsistent with BER-TLV encoding rules
	TLV_ERR_INSUFFICIENT_MEMORY,       //!< Insufficient memory in Cursor Buffer to perform Operation
	TLV_ERR_TAG_NOT_FOUND,             //!< Tag not found while performing Search Operation
	TLV_ERR_INVALID_CONSTRUCTED_DO_TAG //!< Tag is not a valid Constructed Tag
} tlv_retcode_t;

/*@}*/
// End 'constants'

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup cursor Cursor Functions
 * @brief Functions for creating and managing BER-TLV Data Object Cursors
 */
/*@{*/
// 'cursor'

/**
 * Create a new Cursor BER-TLV Data Object from a buffer
 * @param[in] buffer		Buffer with BER-TLV Data Object
 * @param[in] max			Maximum available memory in buffer
 * @param[in] content_size	Size of current BER-TLV Data Object in buffer (0 for empty DO)
 * @param[out] cursor		Destination Cursor to be initialized
 * @retval TLV_NO_ERROR 				@copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER 		@copybrief TLV_ERR_BAD_PARAMETER
 * @retval TLV_ERR_INSUFFICIENT_MEMORY 	@copybrief TLV_ERR_INSUFFICIENT_MEMORY
 * @sa Other return values from tlvResetCursor()
 * @note If buffer contains a BER-TLV Data Object then @b content_size shall be set accordingly
 */
DLLEXPORT tlv_retcode_t tlvInitCursor(
		const byte_t *buffer,
		const length_t max,
		const length_t content_size,
		cursor_t *cursor);

/**
 * Reset the Cursor context to the beginning of the BER-TLV Data Object Buffer,
 * it also resets the Cursor's state
 * @param[in] cursor		Input Cursor
 * @retval TLV_NO_ERROR 				@copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER		@copybrief TLV_ERR_BAD_PARAMETER
 */
DLLEXPORT tlv_retcode_t tlvResetCursor(
		cursor_t *cursor);

/**
 * Initialize a Cursor reference to the Constructed Data Object currently selected
 * @param[in] cursor		Input Cursor with constructed element selected
 * @param[out] constructed	Destination Cursor
 * @retval TLV_NO_ERROR					@copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER		@copybrief TLV_ERR_BAD_PARAMETER
 * @retval TLV_ERR_WRONG_STATE			@copybrief TLV_ERR_WRONG_STATE
 * @retval TLV_ERR_INVALID_CONSTRUCTED_DO_TAG @copybrief TLV_ERR_INVALID_CONSTRUCTED_DO_TAG
 * @sa Other return values from tlvInitCursor()
 * @note This functions requires that the current element of @b cursor has a valid Constructed Tag
 */
DLLEXPORT tlv_retcode_t tlvGetConstructedCursor(
		const cursor_t    *cursor,
		cursor_t          *constructed);

/**
 * Get the Cursor reference over the currently selected Constructed DO Element
 * @param[in] cursor		Input Cursor with constructed element selected
 * @param[in] buffer		Buffer with constructed BER-TLV Data Object
 * @param[in] max			Maximum available memory in buffer
 * @param[out] constructed  Destination Cursor to be initialized
 * @retval TLV_NO_ERROR						@copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER			@copybrief TLV_ERR_BAD_PARAMETER
 * @retval TLV_ERR_WRONG_STATE				@copybrief TLV_ERR_WRONG_STATE
 * @retval TLV_ERR_INVALID_CONSTRUCTED_DO_TAG @copybrief TLV_ERR_INVALID_CONSTRUCTED_DO_TAG
 * @retval TLV_ERR_INSUFFICIENT_MEMORY		@copybrief TLV_ERR_INSUFFICIENT_MEMORY
 * @sa Other return values from tlvInitCursor()
 * @note This functions requires that the current element of @b cursor has a valid Constructed Tag
 * @note Content of @b buffer will be overwritten
 */
DLLEXPORT tlv_retcode_t tlvInitConstructedCursor(
		cursor_t          *cursor,
		byte_t            *buffer,
		const length_t    max,
		cursor_t          *constructed);

/*@}*/
// End 'cursor'

/**
 * @defgroup selection Selection Functions
 * @brief Functions for searching and selecting BER-TLV Elements in BER-TLV Data Objects
 */
/*@{*/
// 'selection'

/**
 * Read the next BER-TLV Element from the current Cursor Position
 * @param[in] cursor        Input Cursor
 * @param[out] tag          BER-TLV Tag read
 * @param[out] length       Number of bytes of BER-TLV Value field
 * @param[out] value        BER-TLV Value read
 * @retval TLV_NO_ERROR                     @copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER            @copybrief TLV_ERR_BAD_PARAMETER
 * @sa Other return values from tlvReadNextTag(), tlvReadNextLength(), tlvReadNextValue()
 * @note The @b length returned is the number of bytes (not in BER-TLV Length representation)
 */
DLLEXPORT tlv_retcode_t tlvReadNextElement(
		cursor_t *cursor,
		tag_value_t *tag,
		length_t *length,
		byte_t **value);

/**
 * Search for a specific BER-TLV Tag occurrence in a Cursor and select the corresponding Element
 * @param[in] tag           BER-TLV Tag of Element to be selected
 * @param[in] occurrence    Occurrence number of BER-TLV Tag in Cursor
 * @param[in] cursor		Input Cursor
 * @param[out] length       Number of bytes in following BER-TLV Value field of selected Element
 * @param[out] value        BER-TLV Value of selected Element
 * @retval TLV_NO_ERROR                     @copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER            @copybrief TLV_ERR_BAD_PARAMETER
 * @retval TLV_ERR_TAG_NOT_FOUND            @copybrief TLV_ERR_TAG_NOT_FOUND
 * @sa Other return values from tlvResetCursor(), tlvReadNextElement()
 */
DLLEXPORT tlv_retcode_t tlvSelectElement(
		const tag_value_t tag,
		const int occurrence,
		cursor_t *cursor,
		length_t *length,
		byte_t **value);

/**
 * Find a specific BER-TLV Tag occurrence in Input Cursor
 * @param[in] tag           BER-TLV Tag of Element to be found
 * @param[in] occurrence    Occurrence number of BER-TLV Tag in Cursor
 * @param[in] cursor        Input Cursor
 * @retval TLV_NO_ERROR                     @copybrief TLV_NO_ERROR
 * @sa Other return values from tlvSelectElement()
 * @note Information from current Element selected available from tlvGetTag(), tlvGetLength(), tlvGetValue()
 */
DLLEXPORT tlv_retcode_t tlvFindTag(
		const tag_value_t tag,
		const int occurrence,
		cursor_t *cursor);

/**
 * Find a Constructed BER-TLV Tag occurrence in Input Cursor and give reference to constructed value in destination Cursor
 * @param[in] tag           BER-TLV Tag of Element to be found
 * @param[in] occurrence    Occurrence number of BER-TLV Tag in Cursor
 * @param[in] cursor        Input Cursor
 * @param[out] constructed  Destination Cursor
 * @retval TLV_NO_ERROR                     @copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER            @copybrief TLV_ERR_BAD_PARAMETER
 * @retval TLV_ERR_INVALID_CONSTRUCTED_DO_TAG @copybrief TLV_ERR_INVALID_CONSTRUCTED_DO_TAG
 * @sa Other return values from tlvSelectElement(), tlvInitCursor()
 */
DLLEXPORT tlv_retcode_t tlvFindConstructed(
		const tag_value_t tag,
		const int         occurrence,
		cursor_t          *cursor,
		cursor_t          *constructed);

/**
 * Search for a constructed tag and create a new Cursor from resulting BER-TLV Constructed DO
 * @param[in] tag           Constructed BER-TLV Tag of Element to be found
 * @param[in] occurrence    Occurrence number of Constructed BER-TLV Tag in Cursor
 * @param[in] cursor        Input Cursor
 * @param[in] buffer		Buffer with BER-TLV Constructed Data Object
 * @param[in] max			Maximum available memory in buffer
 * @param[out] constructed  Destination Cursor to be initialized with BER-TLV Constructed Data Object
 * @retval TLV_NO_ERROR                     @copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER            @copybrief TLV_ERR_BAD_PARAMETER
 * @retval TLV_ERR_INVALID_CONSTRUCTED_DO_TAG @copybrief TLV_ERR_INVALID_CONSTRUCTED_DO_TAG
 * @sa Other return values from tlvFindTag(), tlvInitConstructedCursor()
 * @note Content of @b buffer will be overwritten
 */
DLLEXPORT tlv_retcode_t tlvFindAndInitConstructedCursor(
		const tag_value_t tag,
		const int         occurrence,
		cursor_t          *cursor,
		byte_t            *buffer,
		const length_t    max,
		cursor_t          *constructed);

/**
 * Select a BER-TLV Element contained within a BER-TLV Constructed Data Object
 * @param[in] tag           Constructed BER-TLV Tag of Element to be found
 * @param[in] occurrence    Occurrence number of Constructed BER-TLV Tag in Cursor
 * @param[in] elementTag    BER-TLV Tag to be found within selected Constructed DO
 * @param[in] elementOccurrence Occurrence number of @b elementTag within selected Constructed DO
 * @param[in] cursor        Input Cursor
 * @param[out] length       Number of bytes of following BER-TLV Value field
 * @param[out] value        BER-TLV Value field of selected Element within selected Constructed DO
 * @retval TLV_NO_ERROR                     @copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER            @copybrief TLV_ERR_BAD_PARAMETER
 * @sa Other return values from tlvFindConstructed(), tlvSelectElement()
 */
DLLEXPORT tlv_retcode_t tlvSelectConstructedElement(
		const tag_value_t tag,
		const int         occurrence,
		const tag_value_t elementTag,
		const int         elementOccurrence,
		cursor_t          *cursor,
		length_t          *length,
		byte_t            **value);

/*@}*/
// End 'selection'

/**
 * @defgroup append Append Functions
 * @brief Functions to append BER-TLV Elements at the end of a Cursor
 */
/*@{*/
// 'append'

/**
 * Append a BER-TLV Element at the end of a Cursor
 * @param[in] tag           BER-TLV Tag of element to be appended
 * @param[in] length        Number of bytes of following BER-TLV value field to be appended
 * @param[in] value         Pointer to content of BER-TLV value field to be appended
 * @param[in] select_new    Flag to auto-selection of new element appended
 * @param[out] cursor       Destination Cursor
 * @retval TLV_NO_ERROR                     @copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER            @copybrief TLV_ERR_BAD_PARAMETER
 * @retval TLV_ERR_BAD_TAG                  @copybrief TLV_ERR_BAD_TAG
 * @retval TLV_ERR_BAD_LENGTH               @copybrief TLV_ERR_BAD_LENGTH
 * @retval TLV_ERR_INSUFFICIENT_MEMORY      @copybrief TLV_ERR_INSUFFICIENT_MEMORY
 * @sa Other return values from tlvReadNextElement()
 */
DLLEXPORT tlv_retcode_t tlvAppendElement(
		const tag_value_t tag,
		const length_t length,
		const byte_t *value,
		const int select_new,
		cursor_t *cursor);

/**
 * Append a BER-TLV Constructed DO at the end of a Cursor
 * @param[in] tag           BER-TLV Tag of Constructed DO to be appended
 * @param[in] constructed   Input Cursor with Constructed DO (content of buffer)
 * @param[out] cursor       Destination Cursor
 * @retval TLV_NO_ERROR                     @copybrief TLV_NO_ERROR
 * @retval TLV_ERR_BAD_PARAMETER            @copybrief TLV_ERR_BAD_PARAMETER
 * @retval TLV_ERR_INVALID_CONSTRUCTED_DO_TAG @copybrief TLV_ERR_INVALID_CONSTRUCTED_DO_TAG
 * @sa Other return values from tlvAppendElement()
 */
DLLEXPORT tlv_retcode_t tlvAppendConstructed(
		const tag_value_t tag,
		const cursor_t    *constructed,
		cursor_t          *cursor);

/*@}*/
// End 'append'

/**
 * @defgroup getters Getter Functions
 * @brief Functions for getting various information from a Cursor
 */
/*@{*/
// 'getters'

/**
 * Indicates if a Cursor has a BER-TLV Element currently selected
 * @param[in] cursor        Input Cursor
 * @retval 0         No BER-TLV Element is selected
 * @retval 1         A BER-TLV Element is selected
 */
DLLEXPORT int tlvIsSelected(
		cursor_t *cursor);

/**
 * Indicates if the current BER-TLV Element has a Constructed Tag
 * @param[in] cursor        Input Cursor
 * @retval 0         Current Element is either invalid or not BER-TLV Constructed DO
 * @retval 1         Element is a valid BER-TLV Constructed DO Element
 */
DLLEXPORT int tlvIsConstructed(
		cursor_t *cursor);

/**
 * Indicates if the Cursor is in Error State
 * @param[in] cursor        Input Cursor
 * @retval 0         Cursor under normal operation
 * @retval 1         Cursor in Error State
 */
DLLEXPORT int tlvIsInErrorState(
		cursor_t *cursor);

/**
 * Return the size of the entire BER-TLV DO content of a Cursor
 * @param[in] cursor        Input Cursor
 * @retval 0         Cursor error or content is empty
 * @retval <size>    Size of Cursor's BER-TLV DO
 */
DLLEXPORT length_t tlvGetContentSize(
		cursor_t *cursor);

/**
 * Return pointer on the BER-TLV DO of a Cursor
 * @param[in] cursor         Input Cursor
 * @retval NULL      Cursor error or content is empty
 * @retval <ptr>     Pointer of Cursor's BER-TLV DO
 */
DLLEXPORT byte_t *tlvGetContentData(
		cursor_t *cursor);

/**
 * Return the total space allocated to a Cursor
 * @param[in] cursor        Input Cursor
 * @retval 0         Cursor error or Cursor's buffer as no allocated memory
 * @retval <length_t>    Maximum allocated space of Cursor's buffer
 */
DLLEXPORT length_t tlvGetContentMax(
		cursor_t *cursor);

/**
 * Return BER-TLV Tag of the selected element in Cursor
 * @param[in] cursor        Input Cursor
 * @retval 0        Cursor error or no element selected
 * @retval <tag_value_t>    BER-TLV Tag of selected element in Cursor
 */
DLLEXPORT tag_value_t tlvGetTag(
		cursor_t *cursor);

/**
 * Return BER-TLV Tag Number of the selected element in Cursor
 * @param[in] cursor        Input Cursor
 * @retval 0        Cursor error or no element selected
 * @retval <tag_number_t> Tag number of BER-TLV Tag of selected element in Cursor
 */
DLLEXPORT tag_number_t tlvGetTagNumber(
		cursor_t *cursor);

/**
 * Return BER-TLV Tag Class of the selected element in Cursor
 * @param[in] cursor        Input Cursor
 * @retval 0        Cursor error or no element selected
 * @retval <tag_class_t> Tag Class of BER-TLV Tag of selected element in Cursor
 */
DLLEXPORT tag_class_t tlvGetTagClass(
		cursor_t *cursor);

/**
 * Return the number of bytes in the BER-TLV Tag of the selected element in Cursor
 * @param[in] cursor        Input Cursor
 * @retval 0         Cursor error or no element selected
 * @retval <size>    Number of byte composing the BER-TLV Tag of selected element in Cursor
 */
DLLEXPORT int tlvGetTagSize(
		cursor_t *cursor);

/**
 * Return the BER-TLV Length of the value of the selected element in Cursor
 * @param[in] cursor        Input Cursor
 * @retval 0         Cursor error, no element selected or empty value field
 * @retval <length_t> Number of bytes of BER-TLV Value field of selected element in Cursor
 */
DLLEXPORT length_t tlvGetLength(
		cursor_t *cursor);

/**
 * Return the pointer to the BER-TLV Value of the selected element in Cursor
 * @param[in] cursor        Input Cursor
 * @retval NULL      Cursor error, no element selected or empty value field
 * @retval <ptr>     Pointer to BER-TLV Value fied of selected element in Cursor
 */
DLLEXPORT byte_t *tlvGetValue(
		cursor_t *cursor);

/**
 * Return the Current Version of this Library
 * @return @ref TLV_LIBRARY_VERSION	@copybrief TLV_LIBRARY_VERSION
 */
DLLEXPORT char *tlvGetLibraryVersion(void);

#ifdef __cplusplus
}
#endif

/*@}*/
// End 'getters'

#endif /* TLV_H_ */
