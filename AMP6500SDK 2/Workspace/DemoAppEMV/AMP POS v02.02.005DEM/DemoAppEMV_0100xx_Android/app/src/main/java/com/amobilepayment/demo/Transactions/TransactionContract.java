package com.amobilepayment.demo.Transactions;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.R;

public class TransactionContract {

public enum TransactionType
    {
        //Transaction Name      //menu.xml                  //icon                              //title         //description    //transactionID
        TRANS_NONE              ("MENU_NONE",               0,                                  "",                              "",                                  0),
        TRANS_TRANSACTIONS      ("MENU_TRANSACTIONS",       R.drawable.menu_item_transactions,  "Transaction",  "Purchase",      -1),
        TRANS_SALE              ("MENU_SALE",               R.drawable.menu_item_trxn_sale,     "Purchase",     "",              0x20000001);

        private String mMenuName;
        private long mTransactionId;
        private int mMenuIcon;
        private String mMenuDescription;
        private String mMenuTitle;

        TransactionType(String menuName, int menuIcon, String menuTitle, String menuDescription, long transactionId) {
            mMenuName = menuName;
            mMenuIcon = menuIcon;
            mMenuDescription = menuDescription;
            mMenuTitle = menuTitle;
            mTransactionId = transactionId;
        }

        public String getMenuName() {
            return mMenuName;
        }

        public long getTransactionId() {
            return mTransactionId;
        }

        public int getMenuIcon() {
            return mMenuIcon;
        }

        public String getMenuDescription() {
            return mMenuDescription;
        }

        public String getMenuTitle() {
            return mMenuTitle;
        }

        /**
         * This will be used by Menu Adapter to show or hide supported menu items.
         * @return Whether the current menu item is supported or not, usually based
         *         on Industry code
         */
        public boolean isMenuItemSupported() {

            // TODO: boolean flag = AmpBaseInterface.GetCfgBool("MENU_SALE")

            return true;
        }
    }

    public static TransactionContract.TransactionType determineTransactionType(long transID) {
        for(TransactionContract.TransactionType item : TransactionContract.TransactionType.values()) {
            if(transID == item.getTransactionId()) return item;
        }
        return null;
    }

    public static TransactionContract.TransactionType determineTransactionTypeFromMenuXML(String menuKey) {
        for(TransactionContract.TransactionType item : TransactionContract.TransactionType.values()) {
            if(item.getMenuName().equals(menuKey)) return item;
        }
        return null;
    }

    // TODO: cleanup!

    public final static String CRTDATA_ACQUIRER_INDEX = "AcquirerIdx";
    public final static String CRTDATA_ACQUIRER_NAME = "AcquirerName";
    public final static String CRTDATA_ISSUER_INDEX = "IssuerIdx";
    public final static String CRTDATA_ISSUER_NAME = "IssuerName";
    public final static String CRTDATA_ISSUER_TYPE = "IssuerType";
    public final static String CRTDATA_ISSAID_INDEX = "IssAidIndx";
    public final static String CRTDATA_BINRANGE_INDEX = "BinRangeIndx";

    public final static String CRTDATA_TRANSNAME = "TransName";
    public final static String CRTDATA_TRANSTYPE = "TransType";
    public final static String CRTDATA_EMVTRANSTYPE = "EmvTransType";
    public final static String CRTDATA_TRANSDATE = "TransDate";
    public final static String CRTDATA_TRANSTIME = "TransTime";
    public final static String CRTDATA_POSENTRYMODE = "PosEntryMode";
    public final static String CRTDATA_DEVICEFALLBACK = "DeviceFallback";
    public final static String CRTDATA_RESPONSECODE = "RespCode";
    public final static String CRTDATA_BUSINESSDATE = "BusinessDate";
    public final static String CRTDATA_PINRETRYCOUNT = "PinRetryCounts";
    public final static String CRTDATA_MERCHANTCATCODE = "MerchCatCode";
    public final static String CRTDATA_CUSTOMERLANG = "CustomerLang";
    public final static String CRTDATA_TAXIDNUMBER = "TaxIDNumber";
    public final static String CRTDATA_DESCRIPTORCODE = "DescriptorCodes";
    public final static String CRTDATA_POSCONDCODE = "POSCondCode";
    public final static String CRTDATA_ADDLRESPDATA = "AddlRespData";
    public final static String CRTDATA_AUTHZIP = "AuthZip";
    public final static String CRTDATA_AUTHPHONE = "AuthPhone";
    public final static String CRTDATA_BANKRESPCODE = "BankRespCode";
    public final static String CRTDATA_TOTALREVERSAL = "TotalReversals";
    public final static String CRTDATA_PREPRINTEDBID = "PrePrintedBIN";
    public final static String CRTDATA_ACQREFEDATA = "AcqRefData";
    public final static String CRTDATA_TRBREADCRUMBS = "TrBreadCrumbs";
    public final static String CRTDATA_ACCOUNTTTYPE = "AccountType";
    public final static String CRTDATA_AUTHRESPTXT = "AuthResponseText";

    public final static String CRTDATA_CLERKID = "ClerkID";
    public final static String CRTDATA_CASHIERID = "CashierID";
    public final static String CRTDATA_OPERATORID = "OperatorID";
    public final static String CRTDATA_ACCOUNTID = "AccountID";
    public final static String CRTDATA_PO_NUMBER = "PONumber";
    public final static String CRTDATA_TABLE_NUMBER = "TableNumber";
    public final static String CRTDATA_ECRSEQ_NUMBER = "ECRSeqNumber";
    public final static String CRTDATA_PWDLEVEL = "PasswordLevel";
    public final static String CRTDATA_AGENTNUMBER = "AgentNumber";
    public final static String CRTDATA_CHAINNUMBER = "ChainNumber";
    public final static String CRTDATA_STORENUMBER = "StoreNumber";
    public final static String CRTDATA_TELLERID = "TellerID";
    public final static String CRTDATA_CUSTOMERNO = "CustomerNumber";
    public final static String CRTDATA_SUPPLIERNO = "SupplierNumber";
    public final static String CRTDATA_TAXEXEMPT = "TaxExemptIndicator";
    public final static String CRTDATA_REQUESTERNAME = "RequesterName";

    public final static String CRTDATA_TERMINALID = "TerminalID";
    public final static String CRTDATA_MERCHANTID = "MerchantID";
    public final static String CRTDATA_REFERENCENUMB = "ReferenceNumber";
    public final static String CRTDATA_PREAUTHREFNUMB = "PreAuthRefNumber";
    public final static String CRTDATA_SHIFTNO = "ShiftNumber";
    public final static String CRTDATA_INVOICENO = "InvoiceNumber";
    public final static String CRTDATA_CUSTREFNO = "CustomerRefNumber";
    public final static String CRTDATA_TRACENUMBER = "TraceNumber";
    public final static String CRTDATA_BATCHSEQNO = "BatchSeqNumber";
    public final static String CRTDATA_AUTHNUMBER = "AuthNumber";
    public final static String CRTDATA_ORIGTRACENUMBER = "OrigTraceNumber";
    public final static String CRTDATA_ORIGTRANSNUMBER = "OrigTransNumber";
    public final static String CRTDATA_RESPBATCHNUMBER = "RespBatchNumber";
    public final static String CRTDATA_FCSNUMBER = "FCSNumber";
    public final static String CRTDATA_TILLNUMBER = "TillNumber";
    public final static String CRTDATA_TRANSSEQNUMBER = "TransSeqNumber";

    public final static String CRTDATA_TPDU = "TPDU";
    public final static String CRTDATA_MSGTYPE = "MsgType";
    public final static String CRTDATA_MSGBITMAP = "MsgBitmap";
    public final static String CRTDATA_MSGEXTBITMAP = "MsgExtBitmap";
    public final static String CRTDATA_HOSTMSGID = "HostMsgID";
    public final static String CRTDATA_PROCESSINGCODE = "ProcessingCode";
    public final static String CRTDATA_NII = "NII";
    public final static String CRTDATA_HOSTTYPE = "HostType";

    public final static String CRTDATA_CARDTYPE = "CardType";
    public final static String CRTDATA_CARDTYPE_LABEL = "CardTypeLabel";
    public final static String CRTDATA_PAN = "CardPAN";
    public final static String CRTDATA_PANSEQUENCENO = "PANSeqNumber";
    public final static String CRTDATA_CARDHOLDERNAME = "CardHolderName";
    public final static String CRTDATA_CARDSVCCODE = "CardSvcCode";
    public final static String CRTDATA_CARDEXPIRY = "CardExpiry";
    public final static String CRTDATA_TRACK1 = "Track1";
    public final static String CRTDATA_TRACK2 = "Track2";
    public final static String CRTDATA_TRACK3 = "Track3";
    public final static String CRTDATA_DISCDATA1 = "DiscData1";
    public final static String CRTDATA_DISCDATA2 = "DiscData2";
    public final static String CRTDATA_DISCDATA3 = "DiscData3";
    public final static String CRTDATA_CARDCVV2 = "CVV2";
    public final static String CRTDATA_REASONCODE = "ReasonCode";

    public final static String CRTDATA_TOTAL_AMT = "TotalAmt";
    public final static String CRTDATA_BASE_AMT = "BaseAmt";
    public final static String CRTDATA_ORG_AMT = "OrigAmt";
    public final static String CRTDATA_OLD_AMT = "OldAmt";
    public final static String CRTDATA_TIP_AMT = "TipAmt";
    public final static String CRTDATA_OLD_TIP_AMT = "OldTipAmt";
    public final static String CRTDATA_TAX_AMT = "TaxAmt";
    public final static String CRTDATA_BAR_AMT = "BarAmt";
    public final static String CRTDATA_DUAL_AMT = "DualAmt";
    public final static String CRTDATA_CASHBK_AMT = "CashbkAmt";
    public final static String CRTDATA_SURCHRG_AMT = "SrchrgAmt";
    public final static String CRTDATA_MERCHSURCHRG_AMT = "MerchantSrchrgAmt";
    public final static String CRTDATA_CASHBACKSURCHRG_AMT = "CashbackSrchrgAmt";
    public final static String CRTDATA_NETWORKSURCHRG_AMT = "NetworkSrchrgAmt";
    public final static String CRTDATA_CURREVERSAL_AMT = "CurrReversalAmt";
    public final static String CRTDATA_AUTHORIZED_AMT = "AuthorizedAmt";
    public final static String CRTDATA_BALANCEAFTERTRANS = "BalAfterTrans";
    public final static String CRTDATA_TOTALPREAUTHAMT = "TotalPreAuthAmt";
    public final static String CRTDATA_TOTALAUTHORIZED_AMT = "TotalAuthorizedAmt";

    public final static String CRTDATA_AVRRESPCODE = "AVRespCode";
    public final static String CRTDATA_AVRRESPCODEADDRMATCH = "AVRespCodeAddrMatch";
    public final static String CRTDATA_AVRRESPCODEZIPMATCH = "AVRespCodeZipMatch";
    public final static String CRTDATA_AVSMAILADDRESS = "AVSMailAddress";
    public final static String CRTDATA_AVSZIPCODE = "AVSZIPCode";

    public final static String CRTDATA_AMEX4DIGITBATCHCODE = "AMEX4DigitBatchCode";
    public final static String CRTDATA_AMEXSOCNUMBER = "AMEXSOCNumber";
    public final static String CRTDATA_AMEXSHIPTOZIPCODE = "AMEXShipToZipCode";

    public final static String CRTDATA_VIS2AUTHSRC = "VISA2AuthSource";
    public final static String CRTDATA_VIS2RESPCODE = "VISA2ResponseCode";
    public final static String CRTDATA_VIS2POSENTRYMODE = "VISA2POSEntryMode";
    public final static String CRTDATA_VIS2RESPCODE2 = "VISA2ResponseCode2";
    public final static String CRTDATA_VISDEBITNTWKID = "VISADebitNetworkID";
    public final static String CRTDATA_VISDEBITSETTLEDATE = "VISADebitSettleDate";
    public final static String CRTDATA_VISDEBITSTAN = "VISADebitSTAN";
    public final static String CRTDATA_VISCARDLVLRESP = "VISACardLevelResponse";
    public final static String CRTDATA_VISMARKETSPECID = "VISAMarketSpecIdentifier";
    public final static String CRTDATA_VISDEBITRESPCODE = "VISADebitResponseCode";
    public final static String CRTDATA_VISDEBITRRN = "VISADebitRRN";
    public final static String CRTDATA_VISDEBITORIGTRANDATE = "VISAOrigTransDate";
    public final static String CRTDATA_VISDEBITORIGTRANTIME = "VISAOrigTransTime";

    public final static String CRTDATA_CURRRECINDEX = "CurrencyRecordIndex";
    public final static String CRTDATA_ISSDCCOPTINDEX = "IssuerDCCOptionsIndex";
    public final static String CRTDATA_FOREIGNCURRCODE  = "ForeignCurrCode";
    public final static String CRTDATA_CURRIDNUMBER = "CurrencyIDNum";
    public final static String CRTDATA_FOREIGNORIGAMOUNT = "ForeignCardHldrOrigAm";
    public final static String CRTDATA_FOREIGNCONVRATE = "ForeignConversionRate";
    public final static String CRTDATA_FOREIGNCURREXP = "ForeignCurrExponent";
    public final static String CRTDATA_LASBINTABLIDX = "DCCLastBINTableIndex";
    public final static String CRTDATA_LASTBINDATE = "DCCLastBINDate";
    public final static String CRTDATA_FOREIGNTIP = "ForeignTip";
    public final static String CRTDATA_FOREIGNINVRSCONVRATE = "ForeignInverseConvRate";
    public final static String CRTDATA_FOREIGNINVRSRATEEXP = "ForeignInverseRateExp";
    public final static String CRTDATA_RATEDESIGNATOR = "DCCRateDesignator";
    public final static String CRTDATA_WHOLSALERATE = "DCCWholesaleRate";
    public final static String CRTDATA_WHOLSALERATEEXP = "DCCWholesaleRateExp";
    public final static String CRTDATA_DCCSERVICEFEE = "DCCServiceFee";
    public final static String CRTDATA_FXASSUREDMARKUP = "DCCFXAssuredMarkup";
    public final static String CRTDATA_FXASSUREDMARKUPEXP = "DCCFXAssuredMarkupExp";
    public final static String CRTDATA_FXASSUREDMARKUPIND = "DCCFXAssuredMarkupInd";
    public final static String CRTDATA_FOREIGNBAR = "ForeignBAR";
    public final static String CRTDATA_FOREIGNTAX = "ForeignTax";
    public final static String CRTDATA_MCPORIGAMT = "MCPORIGAMT";
    public final static String CRTDATA_FOREIGNOPTAMT = "ForeignOPTAMT";
    public final static String CRTDATA_PYCRATEMARKUPSIGN = "PYCRateMarkupSign";
    public final static String CRTDATA_PYCRATEMARKUP = "PYCRateMarkup";
    public final static String CRTDATA_ECGINDICATOR = "ECGIndicator";

    public final static String CRTDATA_LOYALTYCURRPTS = "LoyaltyCurrentPoints";
    public final static String CRTDATA_LOYALTYPREVPTS = "LoyaltyPreviousPoints";
    public final static String CRTDATA_LOYALTYPTSAMT = "LoyaltyPointsAmount";
    public final static String CRTDATA_LOYALTYLASTPTSAMT = "LoyaltyLastPointsAmount";
    public final static String CRTDATA_GIFTCARDAVAILABLE = "GiftCardAvailBalance";
    public final static String CRTDATA_GIFTCARDPREVBALANCE = "GiftCardPreviousBalance";
    public final static String CRTDATA_LOYALTYGIFTTRANSFLAG = "LoyaltyGiftTransFlag";

    public final static String CRTDATA_EBTAVAILABLEBAL = "EBTBalance";
    public final static String CRTDATA_EBTOPTIONS = "EBTOptions";
    public final static String CRTDATA_EBTTRANSCOUNT = "EBTTransCount";
    public final static String CRTDATA_EBTBATCHCLOSEDATETIME = "EBTBatchCloseDateTime";
    public final static String CRTDATA_EBTPENDINGTRANSCOUNT = "EBTPendingTransCount";
    public final static String CRTDATA_EBTHOSTNETAMOUNT = "EBTHostNetAmount";
    public final static String CRTDATA_EBTFOODSTAMPID = "EBTFoodStampID";
    public final static String CRTDATA_EBTEVOUCHERSN = "EBTEVoucherSN";
    public final static String CRTDATA_EBTEVOUCHERPIN = "EBTEVoucherPin";

    public final static String CRTDATA_PINBLOCK = "PinBlock";
    public final static String CRTDATA_MACBLOCK  = "MacBlock";
    public final static String CRTDATA_KSN = "PedKSN";

    public final static String CRTDATA_TRE2EESEC = "TRE2EESEC";
    public final static String CRTDATA_TRE2EE = "TRE2EE";

    public final static String CRTDATA_FLAG_NEEDREVERSAL = "TransNeedsReversal";
    public final static String CRTDATA_FLAG_WASREVERSED  = "TransWasReversed";
    public final static String CRTDATA_FLAG_MANUALREVERSAL = "ManualReversal";
    public final static String CRTDATA_FLAG_NEEDADVICE = "TransNeedsAdvice";
    public final static String CRTDATA_FLAG_VOIDED = "TransVoided";
    public final static String CRTDATA_FLAG_ADJUSTED = "TransAdjusted";
    public final static String CRTDATA_FLAG_SETTLED = "TransSettled";
    public final static String CRTDATA_FLAG_PREAUTHCOMPLETED = "PreAuthCompleted";
    public final static String CRTDATA_FLAG_PREAUTHINCREMENTED = "PreAuthIncremented";
    public final static String CRTDATA_FLAG_FALLBACKDONE = "ChipFallback";
    public final static String CRTDATA_FLAG_CARDNOTPRESENT = "CardNotPresent";
    public final static String CRTDATA_FLAG_RECEIPTCAPTURED = "ReceiptCaptured";
    public final static String CRTDATA_FLAG_OFFLINEAPPROVED = "OfflineApproved";
    public final static String CRTDATA_FLAG_TIP_PROMPTED = "TipPrompted";
    public final static String CRTDATA_FLAG_CASHBACK_PROMPTED = "CashbackPrompted";
    public final static String CRTDATA_FLAG_TAX_PROMPTED = "TaxPrompted";
    public final static String CRTDATA_FLAG_SURCHARGE_PROMPTED = "SurchargePrompted";
    public final static String CRTDATA_FLAG_NEED_AMT_CONFIRM = "NeedAmountConfirmation";
    public final static String CRTDATA_FLAG_EMV_TRANS = "EmvTransaction";
    public final static String CRTDATA_FLAG_PARTIALREVERSAL = "PartialReversal";
    public final static String CRTDATA_FLAG_EMVMERCHFORCEONLINE = "EmvMerchForceOnline";
    public final static String CRTDATA_FLAG_MANUALPANENTRYDONE = "ManualPANEntryDone";
    public final static String CRTDATA_FLAG_EXPDATEENTRYDONE =    "ExpiryDateEntryDone";
    public final static String  CRTDATA_FLAG_CARDENTRYDONE = "CardEntryDone";

    public final static String CRTDATA_FLAG_CARDPROCOPT_PIN = "AllowPinEntry";
    public final static String CRTDATA_FLAG_CARDPROCOPT_FALLBACK = "AllowFallback";
    public final static String CRTDATA_FLAG_CARDPROCOPT_CASHBACK = "AllowCashback";
    public final static String CRTDATA_FLAG_CARDPROCOPT_MANUAL = "AllowManualEntry";
    public final static String CRTDATA_FLAG_CARDPROCOPT_CARDPRESENT = "AllowCardPresentEntry";
    public final static String CRTDATA_FLAG_CARDPROCOPT_CARDIMPRINT  = "AllowCardImprintEntry";
    public final static String CRTDATA_FLAG_CARDPROCOPT_MOD10CHECK = "Mod10Check";
    public final static String CRTDATA_FLAG_CARDPROCOPT_VERIFYLAST4 = "VerifyLast4";
    public final static String CRTDATA_FLAG_CARDPROCOPT_IGNORETRACK1 = "IgnoreTrack1";
    public final static String CRTDATA_FLAG_CARDPROCOPT_VERIFYCVV2 = "VerifyCVV2";
    public final static String CRTDATA_FLAG_CARDPROCOPT_TRXREFUND = "AllowTransRefund";
    public final static String CRTDATA_FLAG_CARDPROCOPT_TRXVOID = "AllowTransVoid";
    public final static String CRTDATA_FLAG_CARDPROCOPT_TRXAUTH = "AllowTransAuth";
    public final static String CRTDATA_FLAG_CARDPROCOPT_TRXADJUST = "AllowTransAdjust";
    public final static String CRTDATA_FLAG_CARDPROCOPT_TRXAUTHCOMPLETE = "AllowTransAuthComplete";
    public final static String CRTDATA_FLAG_CARDPROCOPT_TRXOFFLINE = "AllowOfflineTrans";
    public final static String CRTDATA_FLAG_CARDPROCOPT_TRXEBT = "AllowEBTTrans";
    public final static String CRTDATA_FLAG_CARDPROCOPT_AVSMAILADDRESS = "AllowAVSMailAddressEntry";
    public final static String CRTDATA_FLAG_CARDPROCOPT_AVSZIPCODE = "AllowAVSZIPCodeEntry";
    public final static String CRTDATA_FLAG_CARDPROCOPT_AVS = "AllowAVS";

    public final static String CRTDATA_FLAG_CARDEXPIRED = "CardExpired";
    public final static String CRTDATA_FLAG_PREDIALDONE = "PreDialWasDone";
    public final static String CRTDATA_FLAG_BASEAMTENTRYDONE = "BaseAmtEntryDone";
    public final static String CRTDATA_FLAG_TIPENTRYDONE = "TipEntryDone";
    public final static String CRTDATA_FLAG_CASHBACKENTRYDONE = "CashbackEntryDone";
    public final static String CRTDATA_FLAG_SURCHARGEENTRYDONE = "SurchargeEntryDone";
    public final static String CRTDATA_FLAG_TAXENTRYDONE = "TaxEntryDone";
    public final static String CRTDATA_FLAG_CVV2ENTRYDONE = "CVV2EntryDone";
    public final static String CRTDATA_FLAG_PINENTRYDONE = "PinEntryDone";
    public final static String CRTDATA_FLAG_HOSTCOMMSDONE = "HostCommsDone";
    public final static String CRTDATA_FLAG_PRINTMERCHANTCOPY = "PrintMerchantCopy";
    public final static String CRTDATA_FLAG_PRINTCUSTOMERCOPY = "PrintCustomerCopy";
    public final static String CRTDATA_FLAG_PRINTBANKCOPY = "PrintBankCopy";
    public final static String CRTDATA_FLAG_SIGNATUREREQUIRED = "SignatureRequired";
    public final static String CRTDATA_FLAG_SKIPONLINEPIN = "SkipeOnlinePin";
    public final static String CRTDATA_FLAG_ONFALLBACK = "OnFallback";
    public final static String CRTDATA_FLAG_PRINTFROMJOURNAL = "PrintFromJournal";
    public final static String CRTDATA_FLAG_PINENTRYCANCELLED = "PinEntryCancelled";
    public final static String CRTDATA_FLAG_COMMERCIALCARD = "CommercialCard";
    public final static String CRTDATA_FLAG_CLIENTPRINTRECEIPT = "PrintReceipt";
    public final static String CRTDATA_FLAG_SEMIINTEGRATED = "SemiIntegratedBase";

    public final static String CRTDATA_SUPPENTRYMETHODS = "SuppEntryMethods";
    public final static String CRTDATA_CARDENTRYMETHOD = "CardEntryMethod";
    public final static String CRTDATA_EMVCARDRESULT = "EmvCardDecision";
    public final static String CRTDATA_EMVHOSTRESULT = "EmvHostDecision";
    public final static String CRTDATA_HOSTCOMMSRESULT = "HostCommsResult";

    public final static String CRTDATA_JOURNAL_RECID = "JournalRecID";

    // flag to determine if current amount entry is for Sale amount entry OR
    // for other amount entry such as cashback or
    public final static String CRTDATA_FLAG_SALEAMOUNT = "SaleAmountEntry";

    public final static int HOSTCOMM_RESULT_NOT_EXECUTED = 0;       // The function DoHostCommunication was not yet executed
    public final static int HOSTCOMM_RESULT_SUCCESS = 1;            // Successfull Connect, Tx, & Rx has beed done w/ the Host
    public final static int HOSTCOMM_RESULT_CONNECT_FAILED = 2;     // Connection attempts to host failed
    public final static int HOSTCOMM_RESULT_SEND_FAILED = 3;		// Sending of data to host failed
    public final static int HOSTCOMM_RESULT_RECEIVE_FAILED = 4;		// No data received from host (or timeout was reached)
    public final static int HOSTCOMM_RESULT_BUILDPKT_FAILED = 5;	// Error Occured on building the request packet e.g. mandatory field missing, etc.
    public final static int HOSTCOMM_RESULT_RESPONSEPKT_FAILED = 6;	// Error on Parsing of response packet from host e.g. unknownd field, etc.
    public final static int HOSTCOMM_RESULT_VERIFYMAC_FAILED = 7;	// Resonpse packet has incorrect MAC

    public final static String  CRTDATA_AID =  "AID";
    public final static String CRTDATA_TVR  = "TVR";
    public final static String CRTDATA_IAD   =  "IAD";
    public final static String CRTDATA_TSI    =  "TSI";
    public final static String  CRTDATA_ARC    =  "ARC";
    public final static String  CRTDATA_CVM    =  "CVM";
    public final static String  CRTDATA_APPNAME = "ApplicationName";
    public final static String  CRTDATA_RESPONSETEXT = "ResponseText";
    public final static String  CRTDATA_VOIDTYPE = "VoidType";
}
