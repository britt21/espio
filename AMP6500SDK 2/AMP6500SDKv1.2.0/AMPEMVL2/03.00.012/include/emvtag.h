// NAME.......  emvtag.h
// PURPOSE....  This module defines EMV tags in order to retrieve them in a smart way in term of performances
//
//	Rules for tags' update conditions are:
//
// 		- Update conditions are used only for adding tags in AgnosDB during contactless processing
// 		- Update conditions are AND'ed with berParseAndStoreBERTLV caller's rule (either 0xF8/RA or 0xF7/ACT)
//		- Update conditions values are:
//
// 			0x00: tag is skipped and not updated in AgnosDB
// 			0x01: tag updated on K in AgnosDB (modulo berParseAndStoreBERTLV caller's rule)
// 			0x07: tag updated K/ACT/DET in AgnosDB (modulo berParseAndStoreBERTLV caller's rule)
// 			0x08: tag updated RA in AgnosDB (modulo berParseAndStoreBERTLV caller's rule)
// 			0x09: tag updated K/RA in AgnosDB (modulo berParseAndStoreBERTLV caller's rule)
// 			0x0F: tag is always updated in AgnosDB
//
// 		`	Built from bitmap:
//								b8	b7	b6	b5	b4	b3	b2	b1
//							N/A	0	0	0	0	x	x	x	x
//							K	x	x	x	x	x	x	x	1
//							ACT	x	x	x	x	x	x	1	x
//							DET	x	x	x	x	x	1	x	x
//							RA	x	x	x	x	1	x	x	x
//
// PROJECT....  AGNOSDB
// REFERENCES.
//
// Copyright ©2005-2016 - 9164-4187 QUEBEC INC (“AMADIS”), All Rights Reserved
//

#ifndef EMVTAG_H_
#define EMVTAG_H_

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------
//			Include Files
//---------------------------------------------------------
//---- Global Headers ----
#include "gpi_agnos_framework_globals.h"

//---------------------------------------------------------
//			Definitions
//---------------------------------------------------------
#define	DATA_ELEMENT_NOT_FOUND					-1
#define	INVALID_EMV_TAG							0xFF

// All strategies
// EMVCo contact
#define	STANDARD					0x00
// EMVCo Cx
#define	C1							0x01
#define	MASTERCARD_PAYPASS			0x02
#define	VISA_PAYWAVE				0x03
#define	AMEX_EXPRESSPAY				0x04
#define	JCB_JSPEEDY					0x05
#define	DISCOVER_DPAS				0x06
#define	CUP_QUICKPASS				0x07

#define	DISCOVER_ZIP				0x0C
#define	INTERAC_FLASH				0x41
#define	PAYMENTS_AUSTRALIA_EFTPOS	0x42
#define	GEMALTO_PURE				0x43

#define	EMVCO_ENTRY_POINT_TESTING   0xFF


typedef unsigned short 	tEmvTag;

enum DataElementIndex {
	_42,	// Issuer Identification Number (IIN)
	_4F,	// Application Identifier (AID) 
	_50,	// Application Label 
	_56,	// Track 1 Data
	_57,	// Track 2 Equivalent Data 
	_5A,	// Application Primary Account Number (PAN) 
	_61,	// Application Template 
	_6F,	// File Control Information (FCI) Template 
	_70,	// READ RECORD Response Message Template 
	_71,	// Issuer Script 1
	_72,	// Issuer Script 2
	_73,	// Directory Discretionary Template 
	_77,	// Response Message Template Format 2 
	_80,	// Response Message Template Format 1 
	_81,	// Amount, Authorized (Binary)
	_82,	// Application Interchange Profile 
	_84,	// Dedicated File (DF) Name 
	_87,	// Application Priority Indicator 
	_88,	// Short File Identifier (SFI) 
	_8A,	// Authorization Response Code 
	_8C,	// Card Risk Management Data Object List 1  (CDOL1) 
	_8D,	// Card Risk Management Data Object List 2  (CDOL2) 
	_8E,	// Cardholder Verification Method (CVM) List 
	_8F,	// Certification Authority Public Key Index 
	_90,	// Issuer Public Key Certificate 
	_91,	// Issuer Authentication Data
	_92,	// Issuer Public Key Remainder 
	_93,	// Signed Static Application Data  
	_94,	// Application File Locator (AFL) 
	_95,	// Transaction Verification Results (TVR) 
	_97,	// Transaction Certificate Data Object List (TDOL) 
	_98,	// Transaction Certificate (TC) Hash Value
	_99,	// Transaction Personal Identification Number (PIN) Data 
	_9A,	// Transaction Date
	_9B,	// Transaction Status Information 
	_9C,	// Transaction Type
	_9D,	// Directory Definition File (DDF) Name 
	_A5,	// File Control Information (FCI) Proprietary Template,
	_C1,	// Derivation Key Index (Interac)
	_C2,	// Card Total Contactless Spend Limit (Interac)
	_C3,	// Proprietary tag
	_C4,	// CDOL1 Related Data Length (Interac)
	_C5,	// CRM Currency Code (?) or Proprietary tag or Lower Total Contactless Offline Amount Limit (Interac)
	_C6,	// Upper Total Contactless Offline Amount Limit (Interac)
	_C7,	// Terminal Transaction Processing Information (TTPI) (PURE) or Proprietary tag
	_CD,	// Contactless Cryptogram Information Data (CCID) (PURE)
	_D1,	// Offline Balance (Discover) or Test Flags (EntryPoint Testing)
	_D2,	// VIUDS Scheme Directory or Starting Point (EntryPoint Testing)
	_D3,	// Entry Point Select SW1SW2
	_D4,	// Entry Point Outcome
	_D5,	// Entry Point UI Request on Outcome
	_D6,	// Entry Point UI Request on Restart
	_E1,	// Entry Point Data Record Present

	// !!! Last 1 byte long tag !!! See etgSizeOfTag for maintenance !!!

	_5F20,	// Cardholder Name  
	_5F21,	// RFU
	_5F24,	// Application Expiration Date  
	_5F25,	// Application Effective Date  
	_5F28,	// Issuer Country Code  
	_5F2A,	// Transaction Currency Code
	_5F2D,	// Language Preference
	_5F30,	// Service Code  
	_5F34,	// Application Primary Account (PAN) Sequence Number  
	_5F36,	// Transaction Currency Exponent
	_5F50,	// Issuer URL 
	_5F53,	// International Bank Account Number (IBAN) 
	_5F54,	// Bank Identifier Code (BIC) 
	_5F55,	// Issuer Country Code (alpha2 format)  
	_5F56,	// Issuer Country Code (alpha3 format)
	_5F57,	// Account Type 
	_9F01,	// Acquirer Identifier
	_9F02,	// Amount, Authorized (Numeric)
	_9F03,	// Amount, Other (Numeric)
	_9F04,	// Amount, Other (Binary)
	_9F05, 	// Application Discretionary Data 
	_9F06, 	// Application Identifier
	_9F07, 	// Application Usage Control 
	_9F08, 	// Application Version Number 
	_9F09,	// Application Version Number
	_9F0B, 	// Cardholder Name Extended 
	_9F0D, 	// Issuer Action Code - Default 
	_9F0E, 	// Issuer Action Code - Denial 
	_9F0F, 	// Issuer Action Code - Online 
	_9F10, 	// Issuer Application Data 
	_9F11, 	// Issuer Code Table Index 
	_9F12, 	// Application Preferred Name 
	_9F13, 	// Last Online Application Transaction Counter (ATC) Register 
	_9F14, 	// Lower Consecutive Offline Limit 
	_9F15, 	// Merchant Category Code 
	_9F16, 	// Merchant Identifier 
	_9F17, 	// Personal Identification Number (PIN) Try Counter 
	_9F1A,	// Terminal Country Code
	_9F1B,	// Terminal Floor Limit
	_9F1C,	// Terminal Identification
	_9F1D,	// Terminal Risk Management Data
	_9F1E,	// IFD Serial Number
	_9F1F, 	// Track 1 Discretionary Data 
	_9F20, 	// Track 2 Discretionary Data 
	_9F21,	// Transaction Time 
	_9F22,	// CA PKI fDDA (Visa)
	_9F23, 	// Upper Consecutive Offline Limit 
	_9F24, 	// Payment Account Reference
	_9F26,	// Application Cryptogram 
	_9F27,	// Cryptogram Information Data
	_9F29,	// Extended Selection
	_9F2A,	// Kernel Identifier
	_9F2D,	// Integrated Circuit Card (ICC) PIN  Encipherment Public Key Certificate 
	_9F2E,	// Integrated Circuit Card (ICC) PIN  Encipherment Public Key Exponent 
	_9F2F,	// Integrated Circuit Card (ICC) PIN  Encipherment Public Key Remainder 
	_9F32,	// Issuer Public Key Exponent 
	_9F33,	// Terminal Capabilities
	_9F34,	// Cardholder Verification Method (CVM) Results
	_9F35,	// Terminal Type
	_9F36,	// Application Transaction Counter 
	_9F37,	// Unpredictable Number 
	_9F38,	// Processing Option Data Object List (PDOL) 
	_9F39,	// POS Entry Mode 
	_9F3A,	// Amount Reference Currency  
	_9F3B,	// Application Reference Currency  
	_9F3C,	// Transaction Reference Currency Code  
	_9F3D,	// Transaction Reference Currency Exponent
	_9F40,	// Additional Terminal Capabilities 
	_9F41,	// Transaction Sequence Counter 
	_9F42,	// Application Currency Code 
	_9F43,	// Application Reference Currency Exponent 
	_9F44,	// Application Currency Exponent 
	_9F45,	// Data Authentication Code 
	_9F46,	// Issuer Circuit Card (ICC) Public Key Certificate 
	_9F47,	// Issuer Circuit Card (ICC) Public Key Exponent 
	_9F48,	// Issuer Circuit Card (ICC) Public Key Remainder 
	_9F49,	// Dynamic Data Authentication Data Object List (DDOL)
	_9F4A,	// Static Data Authentication Tag List  
	_9F4B,	// Signed Dynamic Application Data  
	_9F4C,	// ICC Dynamic Number  
	_9F4D,	// Log Entry  
	_9F4E,	// Merchant Name And Location
	_9F4F,	// Log Format

	// EMV Proprietary tags
	_9F50,	// Offline Accumulator Balance (Mastercard) or Cardholder Verification Status (JCB)
	_9F51,	// DR DOL (Mastercard) or Application Currency Code (Visa) or Application Currency Code (CUP) or Lower Cumulative Offline Limit  (Interac)
	_9F52,	// Terminal Capability Indicator (TCI) (JCB) or Merchant Type Indicator Limits (Interac)
	_9F53,	// Transaction Category Code (Mastercard) or Consecutive Transaction Counter International Limit (CTTIL) (Visa) or Terminal Interchange Profile (TIP) (JCB)
	_9F54,	// DS ODS Card (Mastercard) or Cumulative Total Transaction Amount Limit (CTTAL) (Visa) or CTTAL (CUP) or Merchant Type Indicator Limits (Interac)
	_9F55,	// Merchant Type Indicator Limits (Interac)
	_9F56,	// Merchant Type Indicator Limits (Interac)
	_9F57,	// Merchant Type Indicator Limits (Interac)
	_9F58,	// Merchant Type Indicator (Interac)
	_9F59,	// Terminal Transaction Information (TTI) (Interac)
	_9F5A,	// Application Program Identifier (Visa) or Terminal Transaction Type (TTT) (Interac)
	_9F5B,	// DSDOL (Mastercard) or Issuer Script Results (Visa)
	_9F5C,	// DS Requested Operator ID (Mastercard) or Cumulative Total Counter Upper Limit (CTCUL) (Visa) or Magstripe DOL (MDOL) (JCB) or Cumulative Offline Transaction Amount Upper Limit COTAUL (CUP) or Upper Cumulative Offline Limit (Interac)
	_9F5D,	// Application Capabilities Information (Mastercard) or Available Offline Spending Amount (AOSA) (Visa) or Application Currency Code (CUP) or  Terminal Contactless Receipt Required Limit (Interac)
	_9F5E,	// DS ID (Mastercard) or Consecutive Transaction International Upper Limit (CTIUL) (Visa) or Terminal Option Status (TOS) (Interac)
	_9F5F,	// DS Slot Availability (Mastercard) or Offline Balance (JCB) or Terminal Contactless Floor Limit (Interac)
	_9F60,	// CVC3 (Track1) or Issuer Update Parameter (JCB)
	_9F61,	// CVC3 (Track2)  (Mastercard)
	_9F62,	// PCVC3 (Track1) (Mastercard) or Card Product Code (Interac)
	_9F63,	// PUNATC (Track1) (Mastercard) or Offline Counter Initial Value (Visa) or Product Identification Information (CUP)
	_9F64,	// NATC (Track1) (Mastercard)
	_9F65,	// PCVC3 (Track2) (Mastercard)
	_9F66,	// PUNATC (Track2) (Mastercard) or Terminal Transaction Qualifiers (TTQ) (Visa)
	_9F67,	// NATC (Track2) (Mastercard) or MSD Offset (Visa)
	_9F68,	// Card Additional Processes (CAP) (CUP)
	_9F69,	// UDOL (Mastercard) or Card Authentication Related Data (Visa)
	_9F6A,	// Unpredictable Number (Numeric) (Mastercard)
	_9F6B,	// Track 2 Data (Mastercard) or Card CVM Limit (Visa) or Card CVM Limit (CUP)
	_9F6C,	// Card Transaction Qualifiers (CTQ) (Visa) or Application Version Number (Mastercard)
	_9F6D,	// Magstripe Application Version Number (Reader) (Mastercard) or Modified Terminal Capabilities (AMEX) or EC Reset Threshold (CUP)
	_9F6E,	// Third Party Data (Mastercard) or Form Factor Indication (FFI) (Visa)
	_9F6F,	// DS Slot Management Control (Mastercard)
	_9F70,	// Protected Data Envelope 1 (Mastercard) or Card Interface Capabilities (AMEX) or Get Data Data Object List (GDDOL) (PURE) or Form Factor Indicator (Interac)
	_9F71,	// Protected Data Envelope 2 (Mastercard) or Card Processing Requirements (Discover) or GDDOL Result Buffer (PURE)
	_9F72,	// Protected Data Envelope 3 (Mastercard)
	_9F73,	// Protected Data Envelope 4 (Mastercard) or Currency Conversion Parameters (Visa) or Issuer Script Result (PURE)
	_9F74,	// Protected Data Envelope 5 (Mastercard) or Data Element Update Result (PURE) or EC Issuer Authorization Code (CUP)
	_9F75,	// Unprotected Data Envelope 1 (Mastercard) or ECHO Identifier (PURE)
	_9F76,	// Unprotected Data Envelope 2 (Mastercard) or Transaction Related Data (PURE)
	_9F77,	// Unprotected Data Envelope 3 (Mastercard) or VLP Funds Limit (Visa) or Terminal Dedicated Data (PURE) or Electronic Cash Balance Limit (CUP)
	_9F78,	// Unprotected Data Envelope 4 (Mastercard) or VLP Single Transaction Limit (Visa) or EC Single Transaction Limit (CUP)
	_9F79,	// Unprotected Data Envelope 5 (Mastercard) or VLP Available Funds (Visa) or Electronic Cash Balance (CUP)
	_9F7C,	// Merchant Custom Data (Mastercard) or Customer Exclusive Data (CED) (Visa)
	_9F7D,	// DS Summary 1 (Mastercard) or Application Version Number (Discover)
	_9F7E,	// DCVV version 1 (Discover) or Mobile Support Indicator (Mastercard)
	_9F7F,	// DS Unpredictable (Mastercard)
	_9F80,	// DCVV version 2 (Discover)
	_BF0C,	// File Control Information (FCI) Issuer Discretionary Data
	_BF5F,	// Scheme Data Template
	_BF70,	// Memory Slot Update Template (PURE)

	// Proprietary tags
	_DF01,	// DS Summary 2 (Mastercard)
	_DF02,	// DS Summary 3 (Mastercard)
	_DF03,	// Security Capabilities a.k.a 9F33's Byte3 (Mastercard)
	_DF04,	// Balance Read Before GAC (Mastercard)
	_DF05,	// Balance Read After GAC (Mastercard)
	_DF06,	// RFU
	_DF07,	// RFU
	_DF08,	// DS AC Type (Mastercard)
	_DF09,	// DS Input (Term) (Mastercard)
	_DF0A,	// DS ODS Info For Reader (Mastercard)
	_DF0B,	// DS Summary Status (Mastercard)
	_DF0C,	// Kernel ID (Mastercard)
	_DF0D,	// DSVN Term (Mastercard)
	_DF0E,	// Post-Gen AC Put Data Status (Mastercard)
	_DF0F,	// Pre-Gen AC Put Data Status (Mastercard)
	_DF10,	// Proceed To First Write Flag (Mastercard)
	_DF11,	// RFU
	_DF12,	// Tags To Read (Mastercard)
	_DF13,	// RFU
	_DF14,	// RFU
	_DF15,	// RFU
	_DF16,	// RFU
	_DF17,	// Card Data Input Capability a.k.a. 9F33's Byte1 (Mastercard)
	_DF18,	// CVM Capability - CVM Required a.k.a. 9F33's Byte2 (Mastercard)
	_DF19,	// CVM Capability - No CVM Required a.k.a. 9F33's Byte2 (Mastercard)
	_DF1A,	// Default UDOL (Mastercard)
	_DF1B,	// Kernel Configuration (Mastercard)
	_DF1C,	// Max Lifetime Torn Transaction (Mastercard)
	_DF1D,	// Max Number Torn Transaction (Mastercard)
	_DF1E,	// Magstripe CVM Capabilities - CVM Required (Mastercard)
	_DF20,	// TAC - Default (Mastercard)
	_DF21,	// TAC - Denial (Mastercard)
	_DF22,	// TAC - Online (Mastercard)
	_DF23,	// RCFL (Mastercard)
	_DF24,	// RCTL (No On-device CVM) (Mastercard)
	_DF25,	// RCTL (On-device CVM) (Mastercard)
	_DF26,	// RCRL (Mastercard)
	_DF27,	// Timeout Value (Mastercard)
	_DF28,	// IDS Status (Mastercard)
	_DF2C,	// Magstripe CVM Capabilities - No CVM Required (Mastercard)
	_DF2D,	// Message Holdtime (Mastercard)
	_DF30,	// Bitmap Entry Point (Visa) or Hold Time Value (Mastercard)
	_DF31,	// Online Tag List (Visa-IRWIN)
	_DF32,	// Status Zero Amount Allowed Flag (Visa) or Minimum Relay Resistance Grace Period (Mastercard)
	_DF33,	// Extended Selection Flag (?) or Maximum Relay Resistance Grace Period (Mastercard)
	_DF34,	// Mandatory Tag Object List (MTOL) (PURE) or Terminal Expected Transmission Time for Relay Resistance C-APDU (Mastercard)
	_DF35,	// Authentication Data Tag Object (ATDTOL) (PURE) or Terminal Expected Transmission Time for Relay Resistance R-APDU (Mastercard)
	_DF36,	// Relay Resistance Accuracy Threshold (Mastercard)
	_DF37,	// Relay Resistance Transmission Time Mismatch Threshold (Mastercard)
	_DF41,	// Measured Relay Resistance Processing Time (Mastercard)
	_DF4B,	// POS Cardholder Interaction Information (Mastercard)
	_DF51,	// Terminal Relay Resistance Entropy (Mastercard)
	_DF53,	// Device Relay Resistance Entropy (Mastercard)
	_DF54,	// Min Time For Processing Relay Resistance APDU (Mastercard)
	_DF55,	// Max Time For Processing Relay Resistance APDU (Mastercard)
	_DF56,	// Device Estimated Transmission Time For Relay Resistance R-APDU (Mastercard)
	_DF60,	// DS Input (Card) (Mastercard)
	_DF61,	// DS Digest H (Mastercard)
	_DF62,	// DS ODS Info (Mastercard)
	_DF63,	// DS ODS Term (Mastercard)
	_DF6E,	// Threshold Value for Biased Random Selection (JCB)
	_DF6F,	// Maximum Target Percentage (JCB)
	_DF70,	// Target Percentage (JCB)
	_DF71,	// RFU
	_DF72,	// Agnos TVR
	_FF02,	// Tags To Write Before GenAC (Mastercard)
	_FF03,	// Tags To Write After GenAC (Mastercard)
	// End of Proprietary

	NUMBER_OF_DATA_ELEMENT
};

//---------------------------------------------------------
//			Public Primitives
//---------------------------------------------------------
DLLEXPORT tEmvTag etgGetDataElementEMVTag( // Return the tag value from the idx of DataElementIndex
	enum DataElementIndex idx	
);

DLLEXPORT enum DataElementIndex etgFindDataElementIndex( // Return the index from a tag value
	tEmvTag tag
);

DLLEXPORT char* etgGetDataElementComment( // Return tag's label
	enum DataElementIndex idx
);

DLLEXPORT unsigned char etgSizeOfTag( // Return tag's length in bytes
	const enum DataElementIndex idx
);

DLLEXPORT char etgGetDataElementFormat( // Return Tag format from the idx of DataElementIndex
	enum DataElementIndex idx
);

DLLEXPORT char etgGetDataElementSource( // Return Tag source from the idx of DataElementIndex
	enum DataElementIndex idx
);

DLLEXPORT void etgSetDataElementSource(  // Set Tag source from the idx of DataElementIndex
	enum DataElementIndex idx,
	char value
);

DLLEXPORT unsigned char etgGetDataElementUpdateCondition( // Return Tag update condition from the idx of DataElementIndex
	enum DataElementIndex idx
);

DLLEXPORT void etgSetDataElementUpdateCondition( // Set Tag update condition from the idx of DataElementIndex
	enum DataElementIndex idx,
	unsigned char value
);

DLLEXPORT void etgSetUpdateCondition( // Set a specific update conditions to overload standard contactless update conditions
	unsigned char* updateCondition,
	unsigned char updateConditionSize
);

DLLEXPORT unsigned char* etgGetUpdateCondition( // Get the specific update conditions overloading standard contactless update conditions
	void
);

#ifdef __cplusplus
}
#endif

#endif /*EMVTAG_H_*/
