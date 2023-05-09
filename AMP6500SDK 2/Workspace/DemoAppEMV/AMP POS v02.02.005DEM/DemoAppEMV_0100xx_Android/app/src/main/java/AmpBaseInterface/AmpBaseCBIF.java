package AmpBaseInterface;

/**
 * Created by Symbol Tabios on 29/01/2018.
 */

public interface AmpBaseCBIF {
    public int BaseCBPerformOperation(int operID);
   // public int BaseCBPerformOperation(int operID, String[] params);
    public int BaseCBPerformOperation(int operID, String id);
    public int BaseCBPerformOperation(int operID, byte[] szTransName, byte[] szCardNum, byte[] szAmount, byte[] szAuthNum,
                                      byte[] szInvoiceNum, byte[] szRRN, byte[] szTraceNum, byte[] szDate, byte[] szTime, byte[] szVoided);
    public int BaseCBPerformOperation(int operID, byte[] szBaseAmt, byte[] szTipAmt, byte[] szCBAmt, byte[] szTaxAmt,
                                      byte[] szSCAmt, byte[] szTotalPreAuthAmt, byte[] szTotalAmt);


    public void BaseCBPerformCardEntry(String szHeader, String szPromptLang1, String szPromptLang2, char bDisplayIcon);
    public int BaseCBPerformEntryOperation(String szHeader, String szPrompt1, String szPrompt2, int iMax, int iMin, String FieldFormat, char Mask,
                                           String CurrSymbol, int InpMethod, String inp, int FontSize, int iTimeout);

 public int BaseCBPerformTipEntryOperation(String szHeader, String szPrompt1, String szPrompt2, int iMax, int iMin, String FieldFormat, char Mask,
                                        String CurrSymbol, int InpMethod, int FontSize, int iTimeout, String item1, String item2, String item3, int tipType);

    public void BaseCBPerformDisplayOperation(String szHeader, String szPrompt1, String szPrompt2, String szPrompt3, String szPrompt4, int iBeep, int iDelayMS);
    public String BaseCBPerformGetEntryValueOperation();

    public int BaseCBPerformSelectionOperation(String szHeader, String szPrompt1, String szPrompt2, int nSelectionButtons, String szBtnMsg1,
                                               String szBtnMsg2, String szBtnMsg3, int iTimeout, int iBeep);

    public void BaseCBPerformSwitchLedOperation(int ledID, int ledStatus, int ledColor);

    public int BaseCBPerformCardTypeSelectionOperation(String[] CardTypeLabels);
    public int BaseCBPerformChoiceSelectionOperation(String Title, String[] CardTypeLabels, int defaultSelection);
    public int BaseCBPerformDisplayBalanceOperation(String szPrompt, String szCurrencySymbol, String szFmtAvailableBalAmt);
    public int BaseCBPerformDisplayPassTerminal(String szHeader, String szPrompt1, String szPrompt2, char bWaitForKey);

    public int BaseCBPerformEnterCancelOperation(String szHeader, String szPrompt1, String szPrompt2, String szPrompt3,
                                                 String szPrompt4, int iBeep, int iTimeout);

    public int BaseCBPerformCancelOperation(String szHeader, String szPrompt1, String szPrompt2, String szPrompt3,
                                                 String szPrompt4, int iBeep, int iTimeout);

    public int BaseCBPerformDisplayTransDetailsOperation(String transName, String invoiceNum, String cardNum, String RRN, String amount,
                                                         String authNum, String dateTime, String isVoided, String szHeader, int iDisplayType, int iTimeout);
    public int BaseCBPerformDisplayParamDetailsOperation(String strName, String strVal);
    public void BaseCBPerformBeepOperation();
    public void BaseCBPerformSetDateTimeOperation(String datetime);

}
