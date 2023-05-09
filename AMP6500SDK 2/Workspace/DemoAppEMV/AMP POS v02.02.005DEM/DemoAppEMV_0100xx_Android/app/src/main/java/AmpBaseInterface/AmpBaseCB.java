package AmpBaseInterface;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.util.Log;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.service.BaseChannel;
import com.amobilepayment.demo.service.BaseChannelContract;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.Iterator;

/**
 * Created by Symbol Tabios on 29/01/2018.
 */

public class AmpBaseCB {

    private static final String TAG = AmpBaseCB.class.getSimpleName();
    private static boolean FLAG_IS_ENTERED = false;
    private static int OPERATION_RESULT = -1;
    private static String OPERATION_DATA = null;

    public final static int INP_METH_NUM_ONLY		= 0x00;
    public final static int INP_METH_NUM_WITH_PUNC	= 0x01;
    public final static int INP_METH_NUM_WITH_DOT	= 0x02;
    public final static int INP_METH_ALPHA_ONLY		= 0x03;
    public final static int INP_METH_ALPHA_NUMERIC	= 0x04;
    public final static int INP_METH_ALL_KEYS		= 0x05;
    public final static int INP_METH_BINARY_ONLY	= 0x06;
    public final static int INP_METH_HEX_ONLY		= 0x07;
    public final static int INP_METH_CUSTOMKEY_MAP	= 0x08;
    public final static int INP_METH_AMOUNT			= 0x09;
    public final static int INP_METH_CARD_NUMBER	= 0x0A;
    public final static int INP_METH_PASSWORD		= 0x80;	// Shows the number (or letter) entered, then updates into mask character (*) after a few seconds
    public final static int INP_METH_PW_STRICT_MASK	= 0x40;	// Shows only mask character (*). Hides the number/letter entered completely

    public final static short TIP_SELECTED_NONE     = 2;
    public final static short TIP_SELECTED_AMOUNT	= 1;
    public final static short TIP_SELECTED_PERCENT	= 0;

    private static Context context = null;
    public static AmpBaseCB instance = null;
    private final static short SLEEP_TIME = 100;

    public AmpBaseCB()
    {
    }

    public void SetContext(Context ctx) { this.context = ctx; }

    public static AmpBaseCB GetInstance()
    {
        if(instance == null) {
            instance = new AmpBaseCB();
        }
        return instance;
    }

    public static AmpBaseCBIF baseCBIF = new AmpBaseCBIF() {

        @Override
        public int BaseCBPerformOperation(int operID) {
            Log.d("AmpBaseCB", "BaseCBPerformOperation="+operID);
            Log.d("AmpBaseCB", "[1]");
            return BasePerformOperation(operID, new String[]{});
        }

        private int BasePerformOperation(int operID, String[] params) {
            Log.d("AmpBaseCB", "[LOCAL]");
            if(params != null && params.length>0)
                BaseChannel.getInstance().informListeners(operID, params);
            else
                BaseChannel.getInstance().informListeners(operID);

            if(operID != BaseChannelContract.OPER_END_TRANSACTION) {
                while (true) {
                    if (FLAG_IS_ENTERED) {
                        FLAG_IS_ENTERED = false;
                        break;
                    }
                    try {
                        Thread.sleep(SLEEP_TIME);
                    }
                    catch (InterruptedException ignored) {
                    }
                }
            }
            else {
                OPERATION_RESULT = 0;
            }
            return OPERATION_RESULT;
        }

        @Override
        public void BaseCBPerformCardEntry(String szHeader, String szPromptLang1, String szPromptLang2, char bDisplayIcon)
        {
            Log.d(TAG, "[BaseCBPerformCardEntry]");
            Log.d(TAG, "header " + szHeader);
            Log.d(TAG, "prompt1 " + szPromptLang1);
            Log.d(TAG, "prompt2 " + szPromptLang2);
            BaseChannel.getInstance().performCardEntry(szHeader, szPromptLang1);
        }

        @Override
        public int BaseCBPerformOperation(int operID, String id) {
            Log.d("AmpBaseCB", "BaseCBPerformOperation="+operID+" id="+id);
            Log.d("AmpBaseCB", "[2]");
            String[] data = {id};
            return BasePerformOperation(operID, data);
        }

        @Override
        public int BaseCBPerformOperation(int operID, byte[] szTransName, byte[] szCardNum, byte[] szAmount,
                                          byte[] szAuthNum, byte[] szInvoiceNum, byte[] szRRN, byte[] szTraceNum,
                                          byte[] szDate, byte[] szTime, byte[] szVoided) {
            Log.d("AmpBaseCB", "BaseCBPerformOperation="+operID);
            Log.d("AmpBaseCB", "[3]");

            String TransName = new String(szTransName);
            String CardNum = new String(szCardNum);
            String Amount = new String(szAmount);
            String AuthNum = new String(szAuthNum);
            String InvoiceNum = new String(szInvoiceNum);
            String RRN = new String(szRRN);
            String TraceNum = new String(szTraceNum);
            String Date = new String(szDate);
            String Time = new String(szTime);
            String Voided = new String(szVoided);

            String[] data = {
                    TransName, CardNum, Amount,
                    AuthNum, InvoiceNum,
                    RRN, TraceNum, Date, Time, Voided
            };

            return BasePerformOperation(operID, data);
        }

        @Override
        public int BaseCBPerformOperation(int operID, byte[] szBaseAmt, byte[] szTipAmt, byte[] szCBAmt,
                                          byte[] szTaxAmt, byte[] szSCAmt,
                                          byte[] szTotalPreAuthAmt, byte[] szTotalAmt) {
            Log.d("AmpBaseCB", "BaseCBPerformOperation="+operID);
            Log.d("AmpBaseCB", "[4]");

            String BaseAmt = new String(szBaseAmt);
            String TipAmt = new String(szTipAmt);
            String CBAmt = new String(szCBAmt);
            String TaxAmt = new String(szTaxAmt);
            String SCAmt = new String(szSCAmt);
            String TotalPreAuthAmt = new String(szTotalPreAuthAmt);
            String TotalAmt = new String(szTotalAmt);

            String[] data = {
                    BaseAmt, TipAmt, CBAmt,
                    TaxAmt, SCAmt,
                    TotalPreAuthAmt, TotalAmt
            };
            return BasePerformOperation(operID, data);
        }

        @Override
        public int BaseCBPerformEntryOperation(String szHeader, String szPrompt1, String szPrompt2, int iMax, int iMin,
                                               String FieldFormat, char Mask, String CurrSymbol, int InpMethod, String defaultAmount, int FontSize, int iTimeout) {
            Log.d(TAG, "BaseCBPerformEntryOperation");

            // ask for input
            BaseChannel.getInstance().askForUserInput(szHeader, szPrompt1, szPrompt2, iMax, iMin, FieldFormat, Mask, CurrSymbol, InpMethod, defaultAmount,iTimeout);

            // wait for input from user
            while (true) {
                if (FLAG_IS_ENTERED) {
                    FLAG_IS_ENTERED = false;
                    break;
                }
                try {
                    Thread.sleep(SLEEP_TIME);
                }
                catch (InterruptedException ignored) {
                }
            }

            return OPERATION_RESULT;
        }

        @Override
        public int BaseCBPerformTipEntryOperation(String szHeader, String szPrompt1, String szPrompt2, int iMax, int iMin, String FieldFormat, char Mask,
                                                  String CurrSymbol, int InpMethod, int FontSize, int iTimeout, String item1, String item2, String item3, int tipType) {
            Log.d(TAG, "not supported");

            return 0;
        }

        @Override
        public void BaseCBPerformDisplayOperation(String szHeader, String szPrompt1, String szPrompt2, String szPrompt3, String szPrompt4, int iBeep, int iDelayMS) {
            Log.d(TAG, "BaseCBPerformDisplayOperation");

            // ask for input
            BaseChannel.getInstance().showNotification(szHeader, szPrompt1, szPrompt2, szPrompt3, szPrompt4, iBeep, iDelayMS);

            // wait for input from user
            while (true) {
                if (FLAG_IS_ENTERED) {
                    FLAG_IS_ENTERED = false;
                    break;
                }
                try {
                    Thread.sleep(SLEEP_TIME);
                }
                catch (InterruptedException ignored) {
                }
            }
        }

        @Override
        public String BaseCBPerformGetEntryValueOperation() {
            String _data = OPERATION_DATA;
            OPERATION_DATA = null;
            return _data;
        }

        @Override
        public int BaseCBPerformSelectionOperation(String szHeader, String szPrompt1, String szPrompt2, int nSelectionButtons,
                                                   String szBtnMsg1, String szBtnMsg2, String szBtnMsg3, int iTimeout, int iBeep) {
            Log.d(TAG, "BaseCBPerformSelectionOperation");

            // ask for input
            BaseChannel.getInstance().askForUserInputSelection(szHeader, szPrompt1, szPrompt2, nSelectionButtons,
                    szBtnMsg1, szBtnMsg2, szBtnMsg3, iTimeout, iBeep);

            // wait for input from user
            while (true) {
                if (FLAG_IS_ENTERED) {
                    FLAG_IS_ENTERED = false;
                    break;
                }
                try {
                    Thread.sleep(SLEEP_TIME);
                }
                catch (InterruptedException ignored) {
                }
            }
            return OPERATION_RESULT;
        }

        @Override
        public void BaseCBPerformSwitchLedOperation(int ledID, int ledStatus, int ledColor) {
            /*
            typedef enum {
                LED1	= 0x01,
                LED2	= 0x02,
                LED3	= 0x03,
                LED4	= 0x04,
                LEDALL	= 0x05,
            } LED_ID;

            typedef enum {
                LEDOFF	= 0x00,
                LEDON	= 0x01,
                LEDFLASH = 0x02,
            } LED_STATUS;

            typedef enum {
                LEDNONE = 0x00,
                LEDBLUE = 0x01,
                LEDYELLOW = 0x02,
                LEDRED = 0x03,
                LEDGREEN = 0x04,
            } LED_COLOR;
            */
        }

        @Override
        public int BaseCBPerformCardTypeSelectionOperation(String[] CardTypeLabels) {
            Log.d(TAG, "BaseCBPerformCardTypeSelectionOperation");
            // ask for input
            BaseChannel.getInstance().askForCardType(CardTypeLabels);

            // wait for input from user
            while (true) {
                if (FLAG_IS_ENTERED) {
                    FLAG_IS_ENTERED = false;
                    break;
                }
                try {
                    Thread.sleep(SLEEP_TIME);
                }
                catch (InterruptedException ignored) {
                }
            }

            Log.d(TAG, "selected: " + OPERATION_DATA);

            return OPERATION_RESULT;
        }

        @Override
        public int BaseCBPerformChoiceSelectionOperation(String Title, String[] CardTypeLabels, int defaultSelection) {
            Log.d(TAG, "BaseCBPerformChoiceSelectionOperation");
            // ask for input
            BaseChannel.getInstance().askForChoice(Title, CardTypeLabels, defaultSelection);

            // wait for input from user
            while (true) {
                if (FLAG_IS_ENTERED) {
                    FLAG_IS_ENTERED = false;
                    break;
                }
                try {
                    Thread.sleep(SLEEP_TIME);
                }
                catch (InterruptedException ignored) {
                }
            }

            Log.d(TAG, "selected: " + OPERATION_DATA);

            return OPERATION_RESULT;
        }

        @Override
        public int BaseCBPerformDisplayBalanceOperation(String szPrompt, String szCurrencySymbol, String szFmtAvailableBalAmt) {
            Log.d(TAG, "not supported");

            return 0;
        }

        @Override
        public int BaseCBPerformDisplayPassTerminal(String szHeader, String szPrompt1, String szPrompt2, char bWaitForKey) {
            Log.d(TAG, "BaseCBPerformDisplayPassTerminal szHeader="+szHeader+" szPrompt1="+szPrompt1+" szPrompt2="+szPrompt2+" bWaitForKey="+(int)bWaitForKey);

            // display message to user
            BaseChannel.getInstance().displayPassTerminal(szHeader, szPrompt1, szPrompt2, bWaitForKey);

            // wait for input from user
            while (true) {
                if (FLAG_IS_ENTERED) {
                    FLAG_IS_ENTERED = false;
                    break;
                }
                try {
                    Thread.sleep(SLEEP_TIME);
                }
                catch (InterruptedException ignored) {
                }
            }

            Log.d(TAG, "selected: " + OPERATION_DATA);

            return OPERATION_RESULT;
        }

        @Override
        public int BaseCBPerformEnterCancelOperation(String szHeader, String szPrompt1, String szPrompt2, String szPrompt3, String szPrompt4, int iBeep, int iTimeout) {
            Log.d(TAG, "BaseCBPerformEnterCancelOperation");

            // ask for input
            BaseChannel.getInstance().showNotificationWithEnterCancel(szHeader, szPrompt1, szPrompt2, szPrompt3, szPrompt4, iBeep, iTimeout);

            // wait for input from user
            while (true) {
                if (FLAG_IS_ENTERED) {
                    FLAG_IS_ENTERED = false;
                    break;
                }
                try {
                    Thread.sleep(SLEEP_TIME);
                }
                catch (InterruptedException ignored) {
                }
            }

            Log.d(TAG, "selected: " + OPERATION_DATA);

            return OPERATION_RESULT;
        }

        @Override
        public int BaseCBPerformCancelOperation(String szHeader, String szPrompt1, String szPrompt2, String szPrompt3, String szPrompt4, int iBeep, int iTimeout) {
            Log.d(TAG, "BaseCBPerformCancelOperation");

            // ask for input
            BaseChannel.getInstance().showNotificationWithCancel(szHeader, szPrompt1, szPrompt2, szPrompt3, szPrompt4, iBeep, iTimeout);

            // wait for input from user
            while (true) {
                if (FLAG_IS_ENTERED) {
                    FLAG_IS_ENTERED = false;
                    break;
                }
                try {
                    Thread.sleep(SLEEP_TIME);
                }
                catch (InterruptedException ignored) {
                }
            }

            Log.d(TAG, "selected: " + OPERATION_DATA);

            return OPERATION_RESULT;
        }

        @Override
        public int BaseCBPerformDisplayTransDetailsOperation(String transName, String invoiceNum, String cardNum, String RRN, String amount,
                                                             String authNum, String dateTime, String isVoided, String szHeader, int iDisplayType, int iTimeout) {
            Log.d(TAG, "BaseCBPerformDisplayTransDetailsOperation");

            // ask for input
            BaseChannel.getInstance().showTransactionDetails(transName, invoiceNum, cardNum, RRN, amount,
                    authNum, dateTime, isVoided, szHeader, iDisplayType, iTimeout);

            // wait for input from user
            while (true) {
                if (FLAG_IS_ENTERED) {
                    FLAG_IS_ENTERED = false;
                    break;
                }
                try {
                    Thread.sleep(SLEEP_TIME);
                }
                catch (InterruptedException ignored) {
                }
            }

            Log.d(TAG, "selected: " + OPERATION_DATA);

            return OPERATION_RESULT;
        }

        @Override
        public int BaseCBPerformDisplayParamDetailsOperation(String strName, String strVal) {
            Log.d(TAG, "BaseCBPerformDisplayParamDetailsOperation");
            return 0;
        }

        @Override
        public void BaseCBPerformBeepOperation() {
            // used for void transaction list, when end of list is reached
            SettingsUtil.forceTriggerBeepError();
        }

        @Override
        public void BaseCBPerformSetDateTimeOperation(String datetime) {
            SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
            boolean auto = prefs.getBoolean(context.getResources().getString(R.string.pref_gen_auto_date_key), false);

            if(!auto && datetime != null && datetime.length() == "yyyyMMddHHmmSS".length()) {
                String date = datetime.substring(0, 8);
                String date_yyyy = date.substring(0,4);
                String date_MM = date.substring(4,6);
                String date_dd = date.substring(6,8);
                String time = datetime.substring(8,12);
                String time_HH = time.substring(0,2);
                String time_mm = time.substring(2, 4);

                SettingsUtil.setTerminalDate(
                        context,
                        Integer.parseInt(date_yyyy),
                        Integer.parseInt(date_MM),
                        Integer.parseInt(date_dd));
                SettingsUtil.setTerminalTime(
                        context,
                        Integer.parseInt(time_HH),
                        Integer.parseInt(time_mm));
            }
        }
    };

    public static void informListener(JSONArray arrdata) {
        int iRetVal = 0;
        boolean isStatus = false;
        try {
            for(int i = 0; i < arrdata.length(); i++) {
                JSONObject jsonObject = arrdata.optJSONObject(i);
                Log.d(TAG, "informListener jsonObject="+jsonObject);
                Iterator keys = jsonObject.keys();

                if("STATUS".equals(jsonObject.getString("id"))) {
                    iRetVal = jsonObject.getInt("value");
                    Log.d(TAG, "informListener retval="+iRetVal);
                    isStatus = true;
                }
                else {
                    // we are only interested in "value" param
                    // id is dummy
                    // type is dummy
                    OPERATION_DATA = jsonObject.getString("value");
                }

                while(keys.hasNext()) {
                    String curKey = (String) keys.next();
                    Log.d(TAG, "informListener curKey="+curKey);
                }

                if(isStatus == false)
                    iRetVal = -1;
            }

        } catch (JSONException e) {
            e.printStackTrace();
        }

        /*if(iRetVal == 0)
            OPERATION_RESULT = 0;
        else
            OPERATION_RESULT = -1;
            */
        OPERATION_RESULT = iRetVal;
        FLAG_IS_ENTERED = true;
    }
}
