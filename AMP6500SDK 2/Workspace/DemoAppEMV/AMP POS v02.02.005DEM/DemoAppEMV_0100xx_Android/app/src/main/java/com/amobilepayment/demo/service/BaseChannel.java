package com.amobilepayment.demo.service;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import AmpBaseInterface.AmpBaseCB;
import com.amobilepayment.demo.Flow.*;
import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.Utils.PrintManager;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.StatusUtil;

public class BaseChannel {
    private final String TAG = BaseChannel.class.getSimpleName();

    private static BaseChannel instance = null;
    private Context mContext;

    private BaseChannel() {
    }

    public static BaseChannel getInstance() {
        if(instance == null) {
            synchronized (BaseChannel.class) {
                if(instance == null) instance = new BaseChannel();
            }
        }
        return instance;
    }

    public BaseChannel setContext(Context context) {
        mContext = context;
        return this;
    }

    /**
     * Transaction flow handler calls this method to inform about the current state
     * of the transaction. Activities behave based on current operation ID.
     * @param operationId The JSON Object created by each activity
     */
    public void informListeners(int operationId) {
        Log.d(TAG, "informListeners(int)");

        switch(operationId) {

            case BaseChannelContract.OPER_INVOICE_CONFIRM_TEXT:
                Log.d(TAG, "launching Invoice Confirm Text activity");
                startActivityFromMainThread(GenericListActivity.class, BaseActivity.SCREEN_INVOICE_CONFIRM);
                break;

            case BaseChannelContract.OPER_CARD_PRESENT:
                Log.d(TAG, "launching Card Present");
                startActivityFromMainThread(GenericListActivity.class, BaseActivity.SCREEN_CARD_PRESENT);
                break;

            case BaseChannelContract.OPER_DISPLAY_CARDTYPE_SELECT:
                Log.d(TAG, "launching Display cardtype select");
                startActivityFromMainThread(GenericListActivity.class, BaseActivity.SCREEN_CARD_TYPE_SELECT);
                break;

            case BaseChannelContract.OPER_ACCT_SELECTION:
                Log.d(TAG, "launching Account Selection");
                startActivityFromMainThread(GenericListActivity.class, BaseActivity.SCREEN_ACCT_SELECT);
                break;

            case BaseChannelContract.OPER_CHECK_PRINTER_STAT:
                Log.d(TAG, "Check Printer Status");
                PrintManager printManager = new PrintManager();
                int iRetVal = printManager.DoCheckPrinterStatus();
                JSONArray dataToSend = new JSONArray();
                JSONObject data = new JSONObject();
                try {
                    data.put("id", "STATUS");
                    data.put("type", 0);
                    data.put("value", iRetVal);
                    dataToSend.put(data);
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                break;

            case BaseChannelContract.OPER_END_TRANSACTION:
                Log.d(TAG, "received OPER_END_TRANSACTION. finishing current activity!");
                StatusUtil.endCurrentTransaction();
                finishTransaction();
                break;

            default:
                Log.d(TAG, "no default implementation for OperationID " + operationId);
                break;
        }
    }

    public void informListeners(int operationId, String[] data) {
        Log.d(TAG, "informListeners(int, String[])");

        switch(operationId) {
            case BaseChannelContract.OPER_TOTAL_AMT_CONFIRM:
                Log.d(TAG, "launching AmountSummaryActivity");
                startActivityFromMainThreadWithParam(AmountSummaryActivity.class, BaseActivity.SCREEN_SL_CONFIRM_TOTAL, data);
                break;
            case BaseChannelContract.OPER_PROMPT_ENTRY_CANCEL:
                Log.d(TAG, "launching Prompt Entry Cancel with GenericListActivity");
                startActivityFromMainThreadWithParam(GenericListActivity.class, BaseActivity.SCREEN_ENTER_INSTALL_SEQ_COUNT, data);
                break;
            case BaseChannelContract.OPER_DISPLAY_TEXT:
                Log.d(TAG, "launching OPER_DISPLAY_TEXT with NotificationActivity");
                startActivityFromMainThreadWithParam(NotificationActivity.class, data);
                break;
            default:
                Log.d(TAG, "no default implementation for OperationID " + operationId);
                break;
        }
    }

    public void performCardEntry(String szHeader, String szPrompt) {
        Log.d(TAG, "performCardEntry(header, prompt)");
        String[] data = {szHeader, szPrompt};
        startActivityFromMainThreadWithParam(CardEntryActivity.class, data);
    }

    public void askForUserInput(String szHeader, String szPrompt1, String szPrompt2, int iMax, int iMin,
                                String FieldFormat, char Mask, String CurrSymbol, int InpMethod, String defaultAmount, int iTimeout) {
        Log.d(TAG, "askForUserInput(...)");

        Log.d(TAG, "szHeader " + szHeader);
        Log.d(TAG, "szPrompt1 " + szPrompt1);
        Log.d(TAG, "szPrompt2 " + szPrompt2);
        Log.d(TAG, "iMax " + iMax);
        Log.d(TAG, "iMin " + iMin);
        Log.d(TAG, "FieldFormat " + FieldFormat);
        Log.d(TAG, "Mask " + Mask);
        Log.d(TAG, "CurrSymbol " + CurrSymbol);
        Log.d(TAG, "InpMethod " + InpMethod);
        Log.d(TAG, "DefaultAmount " + defaultAmount);
        Log.d(TAG, "iTimeout " + iTimeout);

        String[] data = {szHeader, szPrompt1, szPrompt2, String.valueOf(iMax), String.valueOf(iMin),
                FieldFormat, String.valueOf(Mask), CurrSymbol, String.valueOf(InpMethod),
                String.valueOf(iTimeout), defaultAmount};
        switch(InpMethod) {
            case AmpBaseCB.INP_METH_CARD_NUMBER:
                Log.d(TAG, "launching INP_METH_CARD_NUMBER with CardEntryManualActivity)");
                startActivityFromMainThreadWithParam(CardEntryManualActivity.class, data);
                break;
            case AmpBaseCB.INP_METH_AMOUNT:
                Log.d(TAG, "starting AmountEntryActivity");
                startActivityFromMainThreadWithParam(AmountEntryActivity.class, data);
                break;
            default:
                Log.d(TAG, "launching UserInputEntry from askForUserInput()");
                startActivityFromMainThreadWithParam(UserInputEntryActivity.class, data);
                break;
        }
    }

    public void askForCardType(String[] cardTypes) {
        Log.d(TAG, "askForCardType(String[])");

        for(String type : cardTypes) {
            Log.d(TAG, "type: " + type);
        }
        Log.d(TAG, "launching Card Type selection with GenericListActivity");
        startActivityFromMainThread(GenericListActivity.class, BaseActivity.SCREEN_CARD_TYPE_SELECT, cardTypes);
    }

    public void showNotification(String szHeader, String szPrompt1, String szPrompt2, String szPrompt3,
                                 String szPrompt4, int iBeep, int iDelayMS) {
        Log.d(TAG, "showNotification(...)");

        Log.d(TAG, "szHeader " + szHeader);
        Log.d(TAG, "szPrompt1 " + szPrompt1);
        Log.d(TAG, "szPrompt2 " + szPrompt2);
        Log.d(TAG, "szPrompt3 " + szPrompt3);
        Log.d(TAG, "szPrompt4 " + szPrompt4);
        Log.d(TAG, "iBeep " + iBeep);
        Log.d(TAG, "iDelayMS " + iDelayMS);

        Log.d(TAG, "launching NotifierActivity");
        String[] data = {szHeader, szPrompt1, szPrompt2, szPrompt3, szPrompt4, String.valueOf(iBeep), String.valueOf(iDelayMS)};
        startActivityFromMainThreadWithParam(NotifierActivity.class, data);
    }

    public void showNotificationWithEnterCancel(String szHeader, String szPrompt1, String szPrompt2, String szPrompt3,
                                 String szPrompt4, int iBeep, int iTimeout) {
        Log.d(TAG, "showNotificationWithEnterCancel(...)");

        Log.d(TAG, "szHeader " + szHeader);
        Log.d(TAG, "szPrompt1 " + szPrompt1);
        Log.d(TAG, "szPrompt2 " + szPrompt2);
        Log.d(TAG, "szPrompt3 " + szPrompt3);
        Log.d(TAG, "szPrompt4 " + szPrompt4);
        Log.d(TAG, "iBeep " + iBeep);
        Log.d(TAG, "iTimeout " + iTimeout);

        Log.d(TAG, "launching NotifierActivity");
        String[] data = {szHeader, szPrompt1, szPrompt2, szPrompt3, szPrompt4, String.valueOf(iBeep), String.valueOf(iTimeout)};
        startActivityFromMainThreadWithParam(NotifierActivity.class, BaseActivity.SCREEN_NOTIFIER_ENTER_CANCEL, data);
    }

    public void showNotificationWithCancel(String szHeader, String szPrompt1, String szPrompt2, String szPrompt3,
                                                String szPrompt4, int iBeep, int iTimeout) {

        Log.d(TAG, "showNotificationWithCancel(...)");

        Log.d(TAG, "szHeader " + szHeader);
        Log.d(TAG, "szPrompt1 " + szPrompt1);
        Log.d(TAG, "szPrompt2 " + szPrompt2);
        Log.d(TAG, "szPrompt3 " + szPrompt3);
        Log.d(TAG, "szPrompt4 " + szPrompt4);
        Log.d(TAG, "iBeep " + iBeep);
        Log.d(TAG, "iTimeout " + iTimeout);

        Log.d(TAG, "launching NotifierActivity");
        String[] data = {szHeader, szPrompt1, szPrompt2, szPrompt3, szPrompt4, String.valueOf(iBeep), String.valueOf(iTimeout)};
        startActivityFromMainThreadWithParam(NotifierActivity.class, BaseActivity.SCREEN_NOTIFIER_WITH_CANCEL, data);
    }

    public void askForUserInputSelection(String szHeader, String szPrompt1, String szPrompt2, int nSelectionButtons,
                                         String szBtnMsg1, String szBtnMsg2, String szBtnMsg3, int iTimeout, int iBeep) {

        Log.d(TAG, "askForUserInputSelection(...)");

        Log.d(TAG, "szHeader " + szHeader);
        Log.d(TAG, "szPrompt1 " + szPrompt1);
        Log.d(TAG, "szPrompt2 " + szPrompt2);
        Log.d(TAG, "nSelectionButtons " + nSelectionButtons);
        Log.d(TAG, "szBtnMsg1 " + szBtnMsg1);
        Log.d(TAG, "szBtnMsg2 " + szBtnMsg2);
        Log.d(TAG, "szBtnMsg3 " + szBtnMsg3);
        Log.d(TAG, "iTimeout " + iTimeout);
        Log.d(TAG, "iBeep " + iBeep);

        Log.d(TAG, "Launching SelectionActivity");

        String[] data = {szHeader, szPrompt1, szPrompt2, String.valueOf(nSelectionButtons), szBtnMsg1,
                szBtnMsg2, szBtnMsg3, String.valueOf(iTimeout), String.valueOf(iBeep)};
        startActivityFromMainThreadWithParam(SelectionActivity.class, BaseActivity.SCREEN_THREE_BUTTON_SELECTION, data);
    }

    public void showTransactionDetails(String transName, String invoiceNum, String cardNum, String RRN, String amount,
                                       String authNum, String dateTime, String isVoided, String szHeader, int iDisplayType, int iTimeout) {
        Log.d(TAG, "showTransactionDetails(...)");

        Log.d(TAG, "transName " + transName);
        Log.d(TAG, "invoiceNum " + invoiceNum);
        Log.d(TAG, "cardNum " + cardNum);
        Log.d(TAG, "RRN " + RRN);
        Log.d(TAG, "amount " + amount);
        Log.d(TAG, "authNum " + authNum);
        Log.d(TAG, "dateTime " + dateTime);
        Log.d(TAG, "isVoided " + isVoided);
        Log.d(TAG, "szHeader " + szHeader);
        Log.d(TAG, "iDisplayType " + iDisplayType);
        Log.d(TAG, "iTimeout " + iTimeout);

        String[] data = {transName, invoiceNum, cardNum, RRN, amount,
                authNum, dateTime, isVoided, szHeader, String.valueOf(iTimeout)};

        switch(iDisplayType) {
            case 0:
                Log.d(TAG, "launching SCREEN_DETAILS_CONFIRMATION with TransactionDetailsActivity");
                startActivityFromMainThreadWithParam(TransactionDetailsActivity.class, BaseActivity.SCREEN_DETAILS_CONFIRMATION, data);
                break;
            case 1:
                Log.d(TAG, "launching SCREEN_DETAILS_SELECTION with TransactionDetailsActivity");
                startActivityFromMainThreadWithParam(TransactionDetailsActivity.class, BaseActivity.SCREEN_DETAILS_SELECTION, data);
                break;
        }
    }

    public void askForChoice(String title, String[] cardTypeLabels, int defaultSelection) {
        Log.d(TAG, "askForChoice(...)");

        String[] arrayString = new String[cardTypeLabels.length+1];
        int index = 0;

        arrayString[index++] = title;

        for(String type : cardTypeLabels) {
            arrayString[index++] = type;
        }

        Log.d(TAG, "launching SelectionActivity");
        startActivityFromMainThreadWithParam(SelectionActivity.class, BaseActivity.SCREEN_CARD_TYPE_SELECTION, arrayString);
    }

    public void displayPassTerminal(String szHeader, String szPrompt1, String szPrompt2, char bWaitForKey) {
        Log.d(TAG, "displayPassTerminal(...)");

        String[] arrayString = new String[] {szHeader, szPrompt1, szPrompt2, String.valueOf(bWaitForKey)};

        Log.d(TAG, "launching TurnUnitCustomerActivity");
        startActivityFromMainThreadWithParam(TurnUnitCustomerActivity.class, arrayString);
    }

    public void startActivityFromMainThreadWithParam(final Class c, String[] param){
        startActivityFromMainThread(c, 0, param);
    }

    public void startActivityFromMainThread(final Class c, final int screenType) {
        startActivityFromMainThread(c, screenType, null);
    }

    public void startActivityFromMainThreadWithParam(final Class c, int screenType, String[] param){
        startActivityFromMainThread(c, screenType, param);
    }

    public void startActivityFromMainThread(final Class c, final int screenType, final String[] param) {
        Handler handler = new Handler(Looper.getMainLooper());
        handler.post(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent (mContext, c);
                if(screenType > 0) {
                    intent.putExtra(BaseActivity.ARG_KEY, screenType);
                }
                if(param != null && param.length > 0) {
                    intent.putExtra(BaseActivity.PARAM_KEY, param);
                }
                mContext.startActivity(intent);
            }
        });
    }

    public final static String BROADCAST_FINISH_TRANSACTION = "end_of_transaction_for_client_app";

    private void finishTransaction() {
        if(SettingsUtil.isStandAlone(mContext)) {
            Intent intent;
            intent = new Intent(mContext, MenuActivity.class);
            intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
            mContext.startActivity(intent);
        }
    }
}
