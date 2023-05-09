
#ifndef INCLUDE_AMPJSONRECEIPT_H_
#define INCLUDE_AMPJSONRECEIPT_H_

#include "cJSON.h"
#include "AMPPrinter.h"

//3 AMP JSON Receipt Template Field Labels and Values
#define AMPJSON_FLD_LBL_CLASS			"class"
#define AMPJSON_FLD_LBL_DATA			"data"
#define AMPJSON_FLD_LBL_MERCHANT		"merchant"
#define AMPJSON_FLD_LBL_TYPE			"type"
#define AMPJSON_FLD_LBL_BOTTOM			"bottom"
#define AMPJSON_FLD_LBL_ITEMS			"items"
#define AMPJSON_FLD_LBL_SRC				"src"
#define AMPJSON_FLD_LBL_VALUE			"value"
#define AMPJSON_FLD_LBL_ALIGN			"align"
#define AMPJSON_FLD_LBL_SIZE			"size"
#define AMPJSON_FLD_LBL_FONT			"font"
#define AMPJSON_FLD_LBL_INVERSE			"inverse"
#define AMPJSON_FLD_LBL_CHECKBOX		"checkbox"
#define AMPJSON_FLD_LBL_MASKED			"masked"
#define AMPJSON_FLD_LBL_ENABLED 		"enabled"
#define AMPJSON_FLD_LBL_MODE			"mode"
#define AMPJSON_FLD_LBL_FIRST			"first"
#define AMPJSON_FLD_LBL_LAST			"last"
#define AMPJSON_FLD_LBL_MASKED_CHAR		"masked_ch"
#define AMPJSON_FLD_LBL_PREPRINT		"preprint"
#define AMPJSON_FLD_LBL_ASSERT			"assert"
#define AMPJSON_FLD_LBL_LAYOUT			"layout"
#define AMPJSON_FLD_LBL_FORMAT			"format"
#define AMPJSON_FLD_LBL_FONTMAXCHARS	"fontmaxchars"
#define AMPJSON_FLD_LBL_REGULAR			"regular"
#define AMPJSON_FLD_LBL_EMPHASIS		"emphasis"
#define AMPJSON_FLD_LBL_DETAIL			"detail"
#define AMPJSON_FLD_LBL_LINES			"lines"
#define AMPJSON_FLD_LBL_TXT				"txt"
#define AMPJSON_FLD_LBL_TXT1			"txt1"
#define AMPJSON_FLD_LBL_TXT2			"txt2"
#define AMPJSON_FLD_LBL_IMAGE			"image"

#define AMPJSON_FLD_VAL_CLASS			"AMPCoreReceiptImplementation"
#define AMPJSON_FLD_VAL_GROUP			"group"
#define AMPJSON_FLD_VAL_SEPARATOR		"separator"
#define AMPJSON_FLD_VAL_BORDER          "border"
#define AMPJSON_FLD_VAL_IMAGE			"image"
#define AMPJSON_FLD_VAL_LINE			"line"
#define AMPJSON_FLD_VAL_CUSTOM			"custom"
#define AMPJSON_FLD_VAL_CFG				"cfg"
#define AMPJSON_FLD_VAL_TXN				"txn"
#define AMPJSON_FLD_VAL_STR				"str"
#define AMPJSON_FLD_VAL_CENTER			"c"
#define AMPJSON_FLD_VAL_LEFTRIGHT		"lr"
#define AMPJSON_FLD_VAL_LEFT			"l"
#define AMPJSON_FLD_VAL_RIGHT			"r"
#define AMPJSON_FLD_VAL_BOLD			"bold"
#define AMPJSON_FLD_VAL_REGULAR			"regular"
#define AMPJSON_FLD_VAL_EMPHASIS		"emphasis"
#define AMPJSON_FLD_VAL_DEFAULT			"default"
#define AMPJSON_FLD_VAL_DETAIL			"detail"
#define AMPJSON_FLD_VAL_MASK			"mask"
#define AMPJSON_FLD_VAL_UNMASK			"unmask"
#define AMPJSON_FLD_VAL_NORMAL			"normal"
#define AMPJSON_FLD_VAL_CONDENSED		"condensed"
#define AMPJSON_FLD_VAL_NEXTLINE		"nextline"
#define AMPJSON_FLD_VAL_START           "start"
#define AMPJSON_FLD_VAL_END             "end"

//3 AMP JSON Max Data Size Definitions
#define MAX_PRINT_LINE_SZ		1024
#define MAX_JSON_NODE_VAL_SZ	256

#define MAX_CHARS_PER_LINE_EMPHASIS		19
#define MAX_CHARS_PER_LINE_NORMAL     24
#define MAX_CHARS_PER_LINE_CONDENSED    34
#define MAX_CHARS_PER_LINE_DETAIL		42

//3 AMP JSON Font File and Size Definitions
#define FONT_FILE_PATH		"../fonts/"
#define FONT_FILE_ROBOTO_MONO_REGU	FONT_FILE_PATH "roboto_mono_regular.ttf"
#define FONT_FILE_ROBOTO_MONO_BOLD	FONT_FILE_PATH "roboto_mono_bold.ttf"

#define FONT_SIZE_EMPHASIS  34
#define FONT_SIZE_REGULAR   26

#define FONT_SIZE_CONDENSED 18
#define FONT_SIZE_DETAIL    15

//3 AMP JSON Receipt Template Type
typedef enum  {
	AMPJSON_RCPT_TEMPLATE_ROOT = 1,
	AMPJSON_RCPT_TEMPLATE_OVERRIDE = 2,
} AMPJsonRcptTemplateType;

//3 AMP JSON Error Codes
enum AMPJSONError {
    AMPJSON_SUCCESS = 0,
    AMPJSON_NO_ERROR = 0,
	AMPJSON_ERROR_WRONG_FORMAT,
    AMPJSON_ERROR_WRONG_CLASS,
	AMPJSON_ERROR_WRONG_GROUP,
	AMPJSON_ERROR_WRONG_TYPE,
	AMPJSON_ERROR_NO_ITEMS,
	AMPJSON_ERROR_WRONG_NODE,
	AMPJSON_ERROR_EMPTY_ARRAY,
	AMPJSON_ERROR_ARRAY_OUTOFBOUNDS,
	AMPJSON_ERROR_NO_SRC,
	AMPJSON_ERROR_NO_VALUE,
	AMPJSON_ERROR_INVALID_VALUE,
	AMPJSON_ERROR_WRONG_LENGTH,
	
    AMPJSON_NO_ATTRIBUTE,
    AMPJSON_WRONG_ATTRIBUTE_TYPE,
    AMPJSON_ERROR_FILE_NOT_FOUND,
    AMPJSON_ERROR_FILE_COULD_NOT_BE_OPENED,
    AMPJSON_ERROR_FILE_READ_ERROR,
    AMPJSON_ERROR_ELEMENT_MISMATCH,
    AMPJSON_ERROR_PARSING_ELEMENT,
    AMPJSON_ERROR_PARSING_ATTRIBUTE,
    AMPJSON_ERROR_IDENTIFYING_TAG,
    AMPJSON_ERROR_PARSING_TEXT,
    AMPJSON_ERROR_PARSING_CDATA,
    AMPJSON_ERROR_PARSING_COMMENT,
    AMPJSON_ERROR_PARSING_DECLARATION,
    AMPJSON_ERROR_PARSING_UNKNOWN,
    AMPJSON_ERROR_EMPTY_DOCUMENT,
    AMPJSON_ERROR_MISMATCHED_ELEMENT,
    AMPJSON_ERROR_PARSING,
    AMPJSON_CAN_NOT_CONVERT_TEXT,
    AMPJSON_NO_TEXT_NODE,

	AMPJSON_ERROR_COUNT
};

//3 AMP JSON Data Types/Structures
typedef enum {
	AMPJSON_RCPTFMT_NORMAL  = 1,
	AMPJSON_RCPTFMT_CONDENSED = 2,
} AMPJsonRcptFmt;

typedef enum {
	AMPJSON_DATATYPE_INVALID	= 0,
	AMPJSON_DATATYPE_GROUP		= 1,
	AMPJSON_DATATYPE_SEPARATOR	= 2,
	AMPJSON_DATATYPE_IMAGE		= 3,
	AMPJSON_DATATYPE_LINE		= 4,
	AMPJSON_DATATYPE_CUSTOM		= 5,
	AMPJSON_DATATYPE_BORDER		= 6,
} AMPJsonDataType;

typedef struct _LineValues {
	char szSrc[MAX_JSON_NODE_VAL_SZ];
	char szValue[MAX_JSON_NODE_VAL_SZ];
	char szAlign[MAX_JSON_NODE_VAL_SZ];
	char szSize[MAX_JSON_NODE_VAL_SZ];
	char szFont[MAX_JSON_NODE_VAL_SZ];
	BOOL bInverse;
	BOOL bCheckbox;
} AMPJsonLineValues;

typedef struct _MaskSettings {
	BOOL bEnabled;
	char szMode[MAX_JSON_NODE_VAL_SZ];
	int  iFirst;
	int  iLast;
	char cMaskChar;
} AMPJsonMaskValues;

//3 AMP JSON Data Type
typedef cJSON cAMPJSON;

//3 Get String Value Callback Definition
typedef char* (*AMPJsonGetStrValCB)(const char *szSrc, const char *szValue, void *pTransData);

//3 Print Custom Fields Callback Definition
typedef int (*AMPJsonPrintCustomCB)(const char *szName, void *pTransData);

//3 Assert to Process Group Callback Definition
typedef BOOL (*AMPJsonAssertProcGrpCB)(const char *szGrpName, void *pTransData);

class cAMPJSONReceipt
{
public:
	//! Constructor
	cAMPJSONReceipt();
		
	//! Destructor
	~cAMPJSONReceipt();

	//! Get instance of Printer Object
	static cAMPJSONReceipt* getJSONReceiptObj();

	void Initialize();
	void Open(void *pTransData);
	void Close();
	int  Status();
	void Print(const char *szGroup, const char *szPdfFileName = NULL);
	void Print(const char *szGroup, BOOL bPrePrint, const char *szPdfFileName = NULL);
	void ResetPrint();

	//! Clears the current JSON Root/Override Template
	void Clear(AMPJsonRcptTemplateType iType);

	//! Set Gray Value (Contrast - clear printing VS speed)
	void SetGray(int GrayValue);

	//! Loads/Unloads the JSON Receipt template
	int  LoadReceiptTemplate(const char *szFileName, AMPJsonRcptTemplateType iType);
	void UnloadReceiptTemplate(AMPJsonRcptTemplateType iType);

	//! Sets the Receipt Format (Normal or Condensed)
	void SetFormat(AMPJsonRcptFmt Format);

	//! Gets the Receipt Format (Normal or Condensed)
	AMPJsonRcptFmt GetFormat(void);

	//! Sets the callback function to get the actual string value for printing based on "src" and "value"
	void Set_GetStrValCB(AMPJsonGetStrValCB cbFunction);

	//! Sets the callback function to print "custom" fields
	void Set_PrintCustomFieldsCB(AMPJsonPrintCustomCB cbFunction);

	//! Sets the callback function to assert if the group should be processed
	void Set_AssertProcessGrpCB(AMPJsonAssertProcGrpCB cbFunction);

	//! Sets Pre-Print Mode to TRUE/FALSE
	void SetPrePrintMode(BOOL bPrePrintMode);

	//! Sets the Paper Receipt Output to TRUE/FALSE
	void SetPaperReceiptOutput(BOOL bPaperReceipt);

	//! Sets PDF Receipt Output to TRUE/FALSE
	void SetPDFReceiptOutput(BOOL bPDFReceipt);

	//! Sets the JSON Receipt Output to TRUE/FALSE
	void SetJSONReceiptOutput(BOOL bJSONReceipt);

	//! Initializes and Deinitializes the JSON Receipt Output
	void JsonRcptOutputInit();
	void JsonRcptOutputDeInit();

	//! Functions that add lines to the JSON Receipt Output
	void JsonRcptOutputAddLine(char *szAlign, char *szSize, char *szFont, char *szTxt, BOOL bInverse, BOOL bCheckBox=FALSE);
	void JsonRcptOutputAddLineLR(char *szSize, char *szFont, char *szTxt1, char *szTxt2, BOOL bInverse, BOOL bCheckBox=FALSE);
	void JsonRcptOutputAddImage(char *szAlign, char *szImage);
	void JsonRcptOutputAddSeparator(char *szTxt);
	void JsonRcptOutputAddNextLine();

	//! Returns the JSON format receipt output
	int  JsonRcptOutputGetLength(BOOL bFormatted = TRUE);
	int  JsonRcptOutputGetResult(char *szResult, BOOL bFormatted = TRUE);

protected:

	//! Loads a JSON Receipt Template to the memory
	int LoadFile(FILE *fp, AMPJsonRcptTemplateType iType);

	//! Iterate a Group
	int IterateGroup(cJSON *pParent, const char *szGroup, BOOL bPrePrint = FALSE);
	//int IterateGroup(cJSON *pParent, const char *szGroup);

	//! Functions for iterating the items in the JSON Receipt template
	cAMPJSON* GetItemsInGroup(cJSON *pParent, const char *szGroup);
	int GetItemName(cAMPJSON *pItems, int iIndex, char *szName);
	AMPJsonDataType GetDataType(const char *szName);

	//! Process/prints the separator type
	int ProcessSeparator(const char *szName);

	//! Process/prints the border type
	int ProcessBorder(const char *szName);

	//! Process/prints the image type
	int ProcessImage(const char *szName);

	//! Process/prints the line type
	int ProcessLine(const char *szName);

	//! Process/prints the custom type	
	int ProcessCustom(const char *szName);

	//! Process bottom field in group
	int ProcessBottom(const char *szName);

	//! Performs the actual printing (sending to Printer Canvass)
	int PrintLine(const char *szLbl, AMPJsonLineValues LineValues, AMPJsonMaskValues MaskValues);

	//! Retrieves the node values of each tag defined in structure AMPJsonLineValues
	void GetNodeTagValues(cAMPJSON *pNode, AMPJsonLineValues *pValues);

	//! Retrieves the masking settings/values of a line
	void GetNodeMaskSettings(cAMPJSON *pNode, AMPJsonMaskValues *pValues);

	//! Applies/sets the masking to the input string (based on the masking rules)
	void ApplyMaskValues(AMPJsonMaskValues MaskValues, char *szStrValue);

	//! Sets the font to be used
	void SetFont(AMPJsonLineValues LineValues);

protected:
	
	static cAMPJSONReceipt* single_JsonRcptObj;

private:
	//! Pointer to JSON Template Root
	cAMPJSON *m_pRoot;

	//! Pointer to Overriding JSON Template
	cAMPJSON *m_pOverride;

	//! JSON Receipt Current Format (Normal/Condensed)
	AMPJsonRcptFmt m_Format;

	//! Callback function for getting actual string value for printing
	AMPJsonGetStrValCB	m_fnGetStrValCB;

	//! Callback function to print custom fields
	AMPJsonPrintCustomCB m_fnPrintCustomCB;

	//! Callback function to assert if group should be processed
	AMPJsonAssertProcGrpCB m_fnAssertProcGrpCB;

	//! Pointer to Printer Object
	cAMPPrinter *m_pPrinter;

	//! Pre-Print Mode Indicator
	BOOL m_bPrePrintMode;

	//! PDF Receipt Output Indicator
	BOOL m_bPDFReceipt;

	//! JSON Receipt Output Indicator
	BOOL m_bJSONReceipt;

	// Pointer to JSON Receipt Output
	cAMPJSON *m_pJSONRcpt;

	//! Gray Value (Contrast) for Printing
	int m_nGrayValue;

	//! Border Started/Enabled
	BOOL m_bBorder;

	//! Pointer to the Transaction Data Object
	//! This data is used for printing custom fields and 
	//! getting transaction field values
	void *m_pTransData;
	
	//! Pointer to class name
	static char m_className[];
};

#endif // INCLUDE_AMPJSONRECEIPT_H_
