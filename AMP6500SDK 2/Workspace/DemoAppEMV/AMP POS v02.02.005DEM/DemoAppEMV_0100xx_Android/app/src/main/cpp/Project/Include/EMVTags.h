
#ifndef EMVTAGS_H_
#define EMVTAGS_H_

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
* File       	 : 		EMVTags.h
* Application	 : 		AMP Component
* Date Coded  : 		08/31/2015
**************************************************************************/

#include <AMPDataTypes.h>

// Tag and Tag Length Macro
#define TL(a)	a, sizeof(a)

static const BYTE     TAG_42_ISSUER_ID_NUM          [] = { 0x42 };
static const BYTE     TAG_4F_AID                    [] = { 0x4f };
static const BYTE     TAG_50_APPL_LABEL             [] = { 0x50 };
static const BYTE     TAG_52_CMD_TO_PERFORM         [] = { 0x52 };
static const BYTE     TAG_56_TRACK1_EQ_DATA         [] = { 0x56 };
static const BYTE     TAG_57_TRACK2_EQ_DATA         [] = { 0x57 };
static const BYTE     TAG_5A_APPL_PAN               [] = { 0x5a };
static const BYTE     TAG_5F20_CARDHOLDER_NAME      [] = { 0x5f, 0x20 };
static const BYTE     TAG_5F24_EXPIRY_DATE          [] = { 0x5f, 0x24 };
static const BYTE     TAG_5F25_EFFECT_DATE          [] = { 0x5f, 0x25 };
static const BYTE     TAG_5F28_ISSUER_COUNTY_CODE   [] = { 0x5f, 0x28 };
static const BYTE     TAG_5F2A_TRANS_CURCY_CODE     [] = { 0x5f, 0x2a };
static const BYTE     TAG_5F2D_LANG_PREFERENCE      [] = { 0x5f, 0x2d };
static const BYTE     TAG_5F30_SERVICE_CODE         [] = { 0x5f, 0x30 };
static const BYTE     TAG_5F34_APPL_PAN_SEQNUM      [] = { 0x5f, 0x34 };
static const BYTE     TAG_5F36_TRANS_CURR_EXP       [] = { 0x5f, 0x36 };
static const BYTE     TAG_5F50_ISSUER_URL           [] = { 0x5F, 0x50 };
static const BYTE     TAG_5F53_INT_BANK_ACC_NO      [] = { 0x5F, 0x53 };
static const BYTE     TAG_5F54_BANK_ID_CODE         [] = { 0x5F, 0x54 };
static const BYTE     TAG_5F55_ISSUER_COUNTRY_CODE  [] = { 0x5F, 0x55 };
static const BYTE     TAG_5F56_ISSUER_COUNTRY_CODE  [] = { 0x5F, 0x56 };
static const BYTE     TAG_5F57_ACCOUNT_TYPE         [] = { 0x5F, 0x57 };

static const BYTE     TAG_APPL_TEMPL_61             [] = { 0x61 };
static const BYTE     TAG_FCI_TEMPL_6F              [] = { 0x6F };

static const BYTE     TAG_ISUER_SCRPT_TEMPL_71      [] = { 0x71 };
static const BYTE     TAG_ISUER_SCRPT_TEMPL_72      [] = { 0x72 };
static const BYTE     TAG_DIR_DISCR_TEMPL_73        [] = { 0x73 };
static const BYTE     TAG_RESPMSG_FMT1_TEMPL_77     [] = { 0x77 };
static const BYTE     TAG_RESPMSG_FMT2_TEMPL_80     [] = { 0x80 };
static const BYTE     TAG_81_AMOUNT_AUTH            [] = { 0x81 };
static const BYTE     TAG_82_APPL_INTCHG_PROFILE  	[] = { 0x82 };
static const BYTE     TAG_83_CMD_TEMPLATE           [] = { 0x83 };
static const BYTE     TAG_84_DF_NAME                [] = { 0x84 };
static const BYTE     TAG_86_ISSUER_SCRIPT_CMD      [] = { 0x86 };
static const BYTE     TAG_87_APPL_PRIORITY_IND      [] = { 0x87 };
static const BYTE     TAG_88_SFI                    [] = { 0x88 };
static const BYTE     TAG_89_AUTH_CODE              [] = { 0x89 };
static const BYTE     TAG_8A_AUTH_RESP_CODE         [] = { 0x8a };
static const BYTE     TAG_8C_CDOL1                  [] = { 0x8c };
static const BYTE     TAG_8D_CDOL2                  [] = { 0x8d };
static const BYTE     TAG_8E_CVM_LIST             	[] = { 0x8e };
static const BYTE     TAG_8F_AUTH_PUBKEY_INDEX      [] = { 0x8f };
static const BYTE     TAG_90_ISS_PUBKEY_CERT        [] = { 0x90 };
static const BYTE     TAG_91_ISS_AUTH_DATA          [] = { 0x91 };
static const BYTE     TAG_92_ISS_PUBKEY_REM         [] = { 0x92 };
static const BYTE     TAG_93_SIGNED_SAD             [] = { 0x93 };
static const BYTE     TAG_94_AFL                    [] = { 0x94 };
static const BYTE     TAG_95_TVR                  	[] = { 0x95 };
static const BYTE     TAG_97_TDOL                   [] = { 0x97 };
static const BYTE     TAG_98_TC_HASH                [] = { 0x98 };
static const BYTE     TAG_99_PIN_DATA               [] = { 0x99 };
static const BYTE     TAG_9A_TRAN_DATE              [] = { 0x9a };
static const BYTE     TAG_9B_TSI                  	[] = { 0x9b };
static const BYTE     TAG_9C_TRAN_TYPE            	[] = { 0x9c };
static const BYTE     TAG_9D_DDF_NAME               [] = { 0x9d };        
static const BYTE     TAG_9F01_ACQ_ID               [] = { 0x9f, 0x01 };
static const BYTE     TAG_9F02_AMT_AUTH_NUM         [] = { 0x9f, 0x02 };
static const BYTE     TAG_9F03_AMT_OTHER_NUM        [] = { 0x9f, 0x03 };
static const BYTE     TAG_9F04_AMT_OTHER_BIN        [] = { 0x9f, 0x04 };
static const BYTE     TAG_9F05_APPL_DISC_DATA       [] = { 0x9f, 0x05 };
static const BYTE     TAG_9F06_APPL_ID              [] = { 0x9f, 0x06 };
static const BYTE     TAG_9F07_APPL_USE_CNTRL       [] = { 0x9f, 0x07 };
static const BYTE     TAG_9F08_APP_VER_NUM          [] = { 0x9f, 0x08 };
static const BYTE     TAG_9F09_TERM_VER_NUM         [] = { 0x9f, 0x09 };
static const BYTE     TAG_9F0B_CRDHLDRNAME_EXT      [] = { 0x9f, 0x0b };
static const BYTE     TAG_9F0D_IAC_DEFAULT          [] = { 0x9f, 0x0d };
static const BYTE     TAG_9F0E_IAC_DENIAL           [] = { 0x9f, 0x0e };
static const BYTE     TAG_9F0F_IAC_ONLINE           [] = { 0x9f, 0x0f };
static const BYTE     TAG_9F10_ISSUER_APP_DATA      [] = { 0x9f, 0x10 };
static const BYTE     TAG_9F11_ISSSUER_CODE_TBL     [] = { 0x9f, 0x11 };
static const BYTE     TAG_9F12_APPL_PRE_NAME        [] = { 0x9f, 0x12 };
static const BYTE     TAG_9F13_LAST_ONLINE_ATC      [] = { 0x9f, 0x13 };
static const BYTE     TAG_9F14_LC_OFFLINE_LMT       [] = { 0x9f, 0x14 };
static const BYTE     TAG_9F15_MER_CAT_CODE         [] = { 0x9f, 0x15 };
static const BYTE     TAG_9F16_MER_ID               [] = { 0x9f, 0x16 };
static const BYTE     TAG_9F17_PIN_TRY_COUNTER      [] = { 0x9f, 0x17 };
static const BYTE     TAG_9F18_ISSUER_SCRIPT_ID     [] = { 0x9f, 0x18 };
static const BYTE     TAG_9F1A_TERM_COUNTY_CODE     [] = { 0x9f, 0x1a };
static const BYTE     TAG_9F1B_TERM_FLOOR_LIMIT     [] = { 0x9f, 0x1b };
static const BYTE     TAG_9F1C_TEMR_ID              [] = { 0x9f, 0x1c };
static const BYTE     TAG_9F1D_TERM_RISKMGMT_DATA   [] = { 0x9f, 0x1d };
static const BYTE     TAG_9F1E_IFD_SER_NUM          [] = { 0x9f, 0x1e };
static const BYTE     TAG_9F1F_TRACK1_DISC_DATA     [] = { 0x9f, 0x1f };
static const BYTE     TAG_9F20_TRACK2_DISC_DATA     [] = { 0x9f, 0x20 };
static const BYTE     TAG_9F21_TRANS_TIME           [] = { 0x9f, 0x21 };
static const BYTE     TAG_9F22_CERT_PUBKEY_IND      [] = { 0x9f, 0x22 };
static const BYTE     TAG_9F23_UC_OFFLINE_LMT       [] = { 0x9f, 0x23 };
static const BYTE     TAG_9F26_APPL_CRYPTOGRAM      [] = { 0x9f, 0x26 };
static const BYTE     TAG_9F27_CRYPT_INFO_DATA      [] = { 0x9f, 0x27 };
static const BYTE     TAG_9F2D_ICC_PIN_CERT         [] = { 0x9f, 0x2d };
static const BYTE     TAG_9F2E_ICC_PIN_EXP          [] = { 0x9f, 0x2e };
static const BYTE     TAG_9F2F_ICC_PIN_REM          [] = { 0x9f, 0x2f };
static const BYTE     TAG_9F32_ISS_PUBKEY_EXP       [] = { 0x9f, 0x32 };
static const BYTE     TAG_9F33_TERM_CAP             [] = { 0x9f, 0x33 };
static const BYTE     TAG_9F34_CVM_RESULTS          [] = { 0x9f, 0x34 };
static const BYTE     TAG_9F35_TERM_TYPE            [] = { 0x9f, 0x35 };
static const BYTE     TAG_9F36_ATC                  [] = { 0x9f, 0x36 };
static const BYTE     TAG_9F37_UNPRED_NUM           [] = { 0x9f, 0x37 };
static const BYTE     TAG_9F38_PDOL                 [] = { 0x9f, 0x38 };
static const BYTE     TAG_9F39_POS_ENTRY_MODE       [] = { 0x9f, 0x39 };
static const BYTE     TAG_9F3A_AMT_REF_CURR         [] = { 0x9f, 0x3a };
static const BYTE     TAG_9F3B_APPL_REF_CURR        [] = { 0x9f, 0x3b };
static const BYTE     TAG_9F3C_TRANS_REF_CURR       [] = { 0x9f, 0x3c };
static const BYTE     TAG_9F3D_TRANS_REFCURR_EXP    [] = { 0x9f, 0x3d };
static const BYTE     TAG_9F40_TERM_ADTNAL_CAP      [] = { 0x9f, 0x40 };
static const BYTE     TAG_9F41_TRANS_SEQ_COUNTER    [] = { 0x9f, 0x41 };
static const BYTE     TAG_9F42_APPL_CURCY_CODE      [] = { 0x9f, 0x42 };
static const BYTE     TAG_9F43_APPL_REF_CURR_EXP    [] = { 0x9f, 0x43 };
static const BYTE     TAG_9F44_APPL_CURR_EXP        [] = { 0x9f, 0x44 };
static const BYTE     TAG_9F45_DATA_AUTH_CODE       [] = { 0x9f, 0x45 };
static const BYTE     TAG_9F46_ICC_PUBKEY_CERT      [] = { 0x9f, 0x46 };
static const BYTE     TAG_9F47_ICC_PUBKEY_EXP       [] = { 0x9f, 0x47 };
static const BYTE     TAG_9F48_ICC_PUBKEY_REM       [] = { 0x9f, 0x48 }; 
static const BYTE     TAG_9F49_DDOL                 [] = { 0x9f, 0x49 };
static const BYTE     TAG_9F4A_SDA_TAGLIST          [] = { 0x9f, 0x4a };
static const BYTE     TAG_9F4B_DYNAMIC_APPL_DATA    [] = { 0x9f, 0x4b };
static const BYTE     TAG_9F4C_ICC_DYNAMIC_NUM      [] = { 0x9f, 0x4c };
static const BYTE     TAG_9F4D_LOG_ENTRY            [] = { 0x9F, 0x4D };
static const BYTE     TAG_9F4E_MERCHANT_NAME_LOCN   [] = { 0x9F, 0x4E };
static const BYTE     TAG_9F4F_LOG_FORMAT           [] = { 0x9F, 0x4F };
static const BYTE     TAG_BF0C_FCI_DATA             [] = { 0xBF, 0x0C };
static const BYTE     TAG_FCI_PROPTRY_TEMPL_A5      [] = { 0xA5 };

static const BYTE     TAG_9F53_TERM_CAT_CODE        [] = { 0x9f, 0x53 };
static const BYTE     TAG_AEF_TEMPL_70              [] = { 0x70 };
static const BYTE     TAG_9F55_ISSUER_SCRPT_RESULTS [] = { 0x9F, 0x55 };

static const BYTE     TAG_9F79_EC_BALANCE           [] = { 0x9F, 0x79 };
static const BYTE     TAG_9F77_EC_BALANCE_LIMIT     [] = { 0x9F, 0x77 };
static const BYTE     TAG_9F74_EC_ISSUER_AUTH_CODE  [] = { 0x9F, 0x74 };
static const BYTE     TAG_9F78_EC_SINGLE_TXN_LIMIT  [] = { 0x9F, 0x78 };
static const BYTE     TAG_9F6D_EC_RESET_THRESHOLD   [] = { 0x9F, 0x6D };
static const BYTE     TAG_9F6E_EC_FORM_FACTOR_IND   [] = { 0x9F, 0x6E };
static const BYTE     TAG_9F7A_EC_TERM_SUPPORT_IND  [] = { 0x9F, 0x7A };
static const BYTE     TAG_9F7B_EC_TERM_TXN_LIMIT    [] = { 0x9F, 0x7B };

static const BYTE     TAG_9F7C_CUSTMR_EXCLSV_DATA   [] = { 0x9F, 0x7C };
static const BYTE     TAG_9F7E_APPL_LF_CYCL         [] = { 0x9F, 0x7E };
static const BYTE     TAG_9F55_ISSUER_AUTH_FLAG     [] = { 0x9F, 0x55 };

static const BYTE     TAG_9F56_APP_DATA                     [] = { 0x9F, 0x56 };
static const BYTE     TAG_9F50_OFFLINE_BAL                  [] = { 0x9F, 0x50 };
static const BYTE     TAG_9F52_APP_DATA                     [] = { 0x9F, 0x52 };
static const BYTE     TAG_9F57_APP_DATA                     [] = { 0x9F, 0x57 };
static const BYTE     TAG_BF5A_AIPAFLENT_TEMP               [] = { 0xBF, 0x5A };
static const BYTE     TAG_BF58_AMT_DATA_TEMPL               [] = { 0xBF, 0x58 };
static const BYTE     TAG_DF01_APPL_CAPAB                   [] = { 0xDF, 0x01 };
static const BYTE     TAG_9F51_APPL_CURR_CODE               [] = { 0x9F, 0x51 };
static const BYTE     TAG_BF5B_APPL_INT_DATA_TEMPL          [] = { 0xBF, 0x5B };
static const BYTE     TAG_9F5D_AVA_OFFLINE_SPEND_AMT        [] = { 0x9F, 0x5D };
static const BYTE     TAG_9F72_CONSEC_TRAN_CTR_INTLCNTLMT   [] = { 0x9F, 0x72 };
static const BYTE     TAG_9F5E_CONSEC_TRAN_INT_UPP_LMT      [] = { 0x9F, 0x5E };
static const BYTE     TAG_DF71_CONSEC_TRAN_INT_UPP_LMT      [] = { 0xDF, 0x71 };
static const BYTE     TAG_9F58_APP_DATA                     [] = { 0x9F, 0x58 };
static const BYTE     TAG_9F59_APP_DATA                     [] = { 0x9F, 0x59 };
static const BYTE     TAG_BF56_COUNT_DATA_TEMPL             [] = { 0xBF, 0x56 };
static const BYTE     TAG_BF57_INT_COUNT_DATA_TEMPL         [] = { 0xBF, 0x57 };
static const BYTE     TAG_9F73_CONV_CURR_CODE               [] = { 0x9F, 0x73 };
static const BYTE     TAG_9F54_APP_DATA                     [] = { 0x9F, 0x54 };
static const BYTE     TAG_9F5C_CUM_TXN_AMT_UPP_LMT          [] = { 0x9F, 0x5C };

static const BYTE     TAG_5F84_APPL_PAN_SEQ_NUM             [] = { 0x5F, 0x84 };
static const BYTE     TAG_9F60_CVC3_TRACK1					[] = { 0x9F, 0x60 };
static const BYTE     TAG_9F61_CVC3_TRACK2					[] = { 0x9F, 0x61 };
static const BYTE     TAG_9F61_APPL_DEF_ACTION              [] = { 0x9F, 0x61 };
static const BYTE     TAG_9F62_ISS_AUTH_INDICATOR           [] = { 0x9F, 0x62 };
static const BYTE     TAG_9F63_CRD_ACT_ANYS_SUPP_INFO       [] = { 0x9F, 0x63 };
static const BYTE     TAG_9F64_CUM_TOT_TXN_AMT              [] = { 0x9F, 0x64 };
static const BYTE     TAG_9F65_TXN_CURR_CONV_TABLE          [] = { 0x9F, 0x65 };
static const BYTE     TAG_9F66_CRD_ACTION_CODE              [] = { 0x9F, 0x66 };
static const BYTE     TAG_9F5A_LOW_CONSEC_INT_OFFLN_LIMIT   [] = { 0x9F, 0x5A };
static const BYTE     TAG_9F5B_MAX_DOMST_OFFL_TXN_AMT       [] = { 0x9F, 0x5B };
static const BYTE     TAG_9F5B_ISSUER_SCRPT_RESULTS       	[] = { 0x9F, 0x5B };

static const BYTE     TAG_9F66_VISA_TTQ              [] = { 0x9F, 0x66 };
static const BYTE     TAG_9F67_NATC_TRACK2		     [] = { 0x9F, 0x67 };
static const BYTE     TAG_9F6B_TRACK2_DATA           [] = { 0x9F, 0x6B };

static const BYTE     TAG_9F70_FLASH_FORM_FACTOR_IND	 [] = { 0x9F, 0x70 };
static const BYTE     TAG_9F59_FLASH_TTI                [] = { 0x9F, 0x59 };



static const BYTE     TAG_71_SCRIPT_71               [] = { 0x71 };
static const BYTE     TAG_72_SCRIPT_72               [] = { 0x72 };

static const BYTE     TAG_DF0A_EMV_CONTACT_SUPPORTED 	[] = { 0xDF, 0x0A };
static const BYTE     TAG_DF20_TAC_DEFAULT		 		[] = { 0xDF, 0x20 };
static const BYTE     TAG_DF21_TAC_DENIAL				[] = { 0xDF, 0x21 };
static const BYTE     TAG_DF22_TAC_ONLINE		 		[] = { 0xDF, 0x22 };
static const BYTE     TAG_DF55_EMV_CTLS_SUPPORTED 	 	[] = { 0xDF, 0x55 };
static const BYTE     TAG_DF6E_THRESHOLD_AMOUNT 	 	[] = { 0xDF, 0x6E };
static const BYTE     TAG_DF6F_MAX_TARGET_PERCENT 	 	[] = { 0xDF, 0x6F };
static const BYTE     TAG_DF78_DEVICE_SERIAL_NUMBER  	[] = { 0xDF, 0x78 };
static const BYTE     TAG_DF79_EMV_KERNEL_VERSION    	[] = { 0xDF, 0x79 };

static const BYTE     TAG_DF62_APPL_SELECTION_FLAG   	[] = { 0xDF, 0x62 };
static const BYTE     TAG_DF7E_APPL_SELECTION_IND   	[] = { 0xDF, 0x7E };
static const BYTE     TAG_DF11_TAC_IAC_SUPPORT_FLAG   	[] = { 0xDF, 0x11 };
static const BYTE     TAG_DF12_RANDOM_TRX_FLAG	   		[] = { 0xDF, 0x12 };
static const BYTE     TAG_DF13_VELOCITY_FLAG	   		[] = { 0xDF, 0x13 };
static const BYTE     TAG_DF14_FLOOR_LIMIT_FLAG	  	 	[] = { 0xDF, 0x14 };
static const BYTE     TAG_DF15_TAC_FLAG	   				[] = { 0xDF, 0x15 };
static const BYTE     TAG_DF01_DDOL_SUPPORT				[] = { 0xDF, 0x01 };
static const BYTE     TAG_DF02_TDOL_SUPPORT				[] = { 0xDF, 0x02 };
static const BYTE     TAG_DF70_TARGET_PERCENT			[] = { 0xDF, 0x70 };

static const BYTE	  TAG_DF71_DDOL						[] = { 0xDF, 0x71 };
static const BYTE	  TAG_DF72_TDOL						[] = { 0xDF, 0x72 };

static const BYTE	  TAG_DF0C_KERNELID					[] = { 0xDF, 0x0C };
static const BYTE	  TAG_DF23_CTLS_FLOOR_LIMIT			[] = { 0xDF, 0x23 };
static const BYTE	  TAG_DF24_CTLS_TRX_LIMIT			[] = { 0xDF, 0x24 };
static const BYTE	  TAG_DF25_ON_DEV_CTLS_TRX_LIMIT	[] = { 0xDF, 0x25 };
static const BYTE	  TAG_DF26_CTLS_CVM_LIMIT			[] = { 0xDF, 0x26 };
static const BYTE	  TAG_DF0F_TLV_STREAM				[] = { 0xDF, 0x0F };
static const BYTE	  TAG_DF17_CARD_DATA_INPUT			[] = { 0xDF, 0x17 };
static const BYTE	  TAG_DF18_CVM_REQ_CAPABILITIES		[] = { 0xDF, 0x18 };
static const BYTE	  TAG_DF19_NOCVM_REQ_CAPABILITIES	[] = { 0xDF, 0x19 };
static const BYTE	  TAG_DF03_SEC_CAPABILITIES			[] = { 0xDF, 0x03 };
static const BYTE	  TAG_DF30_BITMAP_ENTRY_POINT		[] = { 0xDF, 0x30 };
static const BYTE	  TAG_DF1B_KERNEL_CONFIG			[] = { 0xDF, 0x1B };

static const BYTE	  TAG_9F5F_FLASH_TRANS_LIMIT		[] = { 0x9F, 0x5F };
static const BYTE	  TAG_9F58_MERCHANT_TYPE_IND		[] = { 0x9F, 0x58 };
static const BYTE	  TAG_9F5E_INTERAC_TOS				[] = { 0x9F, 0x5E };

static const BYTE	  TAG_9F52_MTI_VALUES				[] = { 0x9F, 0x52 };
static const BYTE	  TAG_9F54_MTI_VALUES				[] = { 0x9F, 0x54 };
static const BYTE	  TAG_9F55_MTI_VALUES				[] = { 0x9F, 0x55 };
static const BYTE	  TAG_9F56_MTI_VALUES				[] = { 0x9F, 0x56 };
static const BYTE	  TAG_9F57_MTI_VALUES				[] = { 0x9F, 0x57 };
static const BYTE	  TAG_9F5D_INTERAC_RRL				[] = { 0x9F, 0x5D };






#endif /* EMVTAGS_H_ */

