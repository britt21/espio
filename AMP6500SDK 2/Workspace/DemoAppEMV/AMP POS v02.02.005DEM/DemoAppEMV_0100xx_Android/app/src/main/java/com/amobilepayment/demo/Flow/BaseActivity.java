package com.amobilepayment.demo.Flow;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Handler;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import org.json.JSONArray;

import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.Transactions.Transaction;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.service.BaseChannel;

public class BaseActivity extends AppCompatActivity implements DialogManager.Listener {

    private final static String TAG = BaseActivity.class.getSimpleName();

    public final static String IMAGE_DESKTOP_FILENAME = "desktop_logo";
    public final static String IMAGE_HEADER_FILENAME = "header_logo";
    public final static String IMAGE_ICON_FILENAME = "icon_logo";

    public final static String ARG_KEY = "argument_key";
    public final static String PARAM_KEY = "param_key";

    final static int DEFAULT_TIMEOUT = 3000; // 3 seconds

    protected boolean hasTimedOut = false;
    protected boolean isUserDone = false;
    private Runnable timeoutRunnable;
    private Handler timeoutHandler;
    private long mTimeOut = 0L;

    protected int mScreenType = 0;
    protected String[] mParameters;

    // Purchase screens
    public final static int SCREEN_TIP                      = 1001;
    public final static int SCREEN_AMOUNT                   = 1002;
    public final static int SCREEN_CASHBACK                 = 1003;
    public final static int SCREEN_SURCHARGE                = 1004;

    public final static int SCREEN_TABLE_NUM                = 1006;
    public final static int SCREEN_CARD_PRESENT             = 1007;
    public final static int SCREEN_ACCT_SELECT              = 1008;
    public final static int SCREEN_CARD_ENTRY               = 1009;
    public final static int SCREEN_CARD_TYPE_SELECT         = 1010;
    public final static int SCREEN_TAX_AMOUNT               = 1011;
    public final static int SCREEN_SL_CONFIRM_TOTAL         = 1012;

    // Force Post screens
    public final static int SCREEN_FORCEPOST                = 2001;
    public final static int SCREEN_FP_CONFIRM_TOTAL         = 2002;

    // Refund screen
    public final static int SCREEN_REFUND                   = 3001;
    public final static int SCREEN_RF_CONFIRM_TOTAL         = 3002;

    // Recall screens
    public final static int SCREEN_RECALL_TRACE             = 4001;
    public final static int SCREEN_RECALL_AMOUNT            = 4002;
    public final static int SCREEN_RECALL_ACCOUNT           = 4003;
    public final static int SCREEN_RECALL_INVOICE           = 4004;
    public final static int SCREEN_RECALL_PREAUTH_INVOICE   = 4005;
    // NOTE: RECALL_ALL and RECALL_OPEN_PREAUTH
    //       don't require input from user
    //       so these probably will be left unused
    public final static int SCREEN_RECALL_PREAUTH_OPEN      = 5006;
    public final static int SCREEN_RECALL_ALL               = 5007;
    public final static int SCREEN_SELECT_3_RECALL          = 5008;
    public final static int SCREEN_SELECT_2_RECALL          = 5009;
    public final static int SCREEN_SELECT_BILLPAYT          = 5010;
    public final static int SCREEN_SELECT_ECI               = 5011;
    public final static int SCREEN_ENTER_INSTALL_SEQ_NUM    = 5012;
    public final static int SCREEN_ENTER_INSTALL_SEQ_COUNT  = 5013;
    public final static int SCREEN_PROMPT_ENTRY_CANCEL      = 5014;
    public final static int SCREEN_ENTRY_TRANS_ID           = 5015;

    // Reprint screens
    public final static int SCREEN_REPPASTREC_TRACE         = 6001;
    public final static int SCREEN_REPPASTREC_AMOUNT        = 6002;
    public final static int SCREEN_REPPASTREC_ACCOUNT       = 6003;
    public final static int SCREEN_REPPASTREC_INVOICE       = 6004;
    public final static int SCREEN_REPPASTREC_PREAUTH       = 6005;
    // NOTE: REPRINT_LAST_RECEIPT and
    //       REPRINT_LAST_SETTLEMINT_REPORT don't require
    //       input from user so these probably will be
    //       left unused
    public final static int SCREEN_REPRINT_LAST_RECEIPT     = 6006;
    public final static int SCREEN_REPRINT_LAST_SETTLE      = 6007;

    // Void screens
    public final static int SCREEN_VOID_SELECT_HOW          = 7001;
    public final static int SCREEN_INVOICE_ENTRY            = 7002;
    public final static int SCREEN_AUTH_NUM_ENTRY           = 7003;
    public final static int SCREEN_REF_NUM_ENTRY            = 7004;

    public final static int SCREEN_INVOICE_CONFIRM          = 8001;

    // Preauth screens
    public final static int SCREEN_ENTER_RENT_DURATION      = 9001;
    public final static int SCREEN_ENTER_STAY_DURATION      = 9002;

    // PIN / Password screens
    public final static int SCREEN_ENTER_PIN                = 1101;
    public final static int SCREEN_ENTER_NEW_PASSWORD       = 1102;
    public final static int SCREEN_ENTER_NEW_PASSWORD_AGAIN = 1103;
    public final static int SCREEN_PASSWORD_OPERATOR        = 1104;

    // Transaction Details screens
    public final static int SCREEN_DETAILS_PRINT            = 1201;
    public final static int SCREEN_DETAILS_VOID             = 1202;
    public final static int SCREEN_DETAILS_SELECTION        = 1203;
    public final static int SCREEN_DETAILS_CONFIRMATION     = 1204;

    // TSYS Admin screens
    public final static int SCREEN_TSYS_ADMIN_LOGIN         = 1301;

    // screen was requested from Settings page
    public final static int SCREEN_OPERATOR_ID_ENTRY        = 1401;
    public final static int SCREEN_SETTINGS_ADD_OPERATOR    = 1402;
    public final static int SCREEN_SETTINGS_RESET_OPERATOR_PASSWORD = 1403;
    public final static int SCREEN_SETTINGS_DELETE_OPERATOR = 1404;
    public final static int SCREEN_SETTINGS_SHOW_OPERATORS  = 1405;

    // Selection activity
    public final static int SCREEN_THREE_BUTTON_SELECTION   = 1501;
    public final static int SCREEN_CARD_TYPE_SELECTION      = 1502;

    // TurnUnitCustomer activity
    public final static int SCREEN_TURN_UNIT_PRESS_KEY      = 1601;

    // Notifier activity
    public final static int SCREEN_NOTIFIER_ENTER_CANCEL    = 1701;
    public final static int SCREEN_NOTIFIER_WITH_CANCEL     = 1702;

    protected void startActivityTimeOut(long to) {
        // setup timeout
        mTimeOut = to;
        if(mTimeOut>0) {
            timeoutHandler = new Handler();
            timeoutRunnable = new Runnable() {
                @Override
                public void run() {
                    if (!isUserDone) {
                        hasTimedOut = true;
                        JSONArray dataToSend = new JSONArray();
                        dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_TIMEOUT));
                        StatusUtil.notifyCurrentTransaction(dataToSend);
                    }
                }
            };
            timeoutHandler.postDelayed(timeoutRunnable, Long.valueOf(mTimeOut));
        }
    }

    protected void stopTimeoutHandler() {
        if(timeoutHandler != null)
            timeoutHandler.removeCallbacks(timeoutRunnable);
    }
    protected void startTimeoutHandler() {
        if(timeoutHandler != null)
            timeoutHandler.postDelayed(timeoutRunnable, mTimeOut);
    }

    // Client App handling
    // Note that all started/stopped activities will receive this broadcast
    // thus sending multiple results to calling app. With this in mind, we have
    // modified ClientIntentHandlerActivity to extend BaseActivity class.
    // Another alternative is to call registerReceiver on onStart and call the corresponding
    // unregister on onStop.
    private final BroadcastReceiver endTransactionReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {

            Intent resultIntent = new Intent();
            Bundle extras = intent.getExtras();
            resultIntent.putExtras(extras);

            // wait for the correct result code before finishing all activities
            while(Transaction.DEFAULT_TRANSACTION_STATUS ==
                    MenuActivity.currentTransaction.getTransactionStatus()) {
                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) { }
            }
            if (MenuActivity.currentTransaction.getTransactionStatus() == StatusUtil.AMP_SUCCESS)
                BaseActivity.this.setResult(RESULT_OK, resultIntent);
            else
                BaseActivity.this.setResult(RESULT_CANCELED, resultIntent);
            finish();
        }
    };

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        registerReceiver(endTransactionReceiver, new IntentFilter(BaseChannel.BROADCAST_FINISH_TRANSACTION));
    }

    @Override
    protected void onDestroy() {
        unregisterReceiver(endTransactionReceiver);

        super.onDestroy();
    }

    @Override
    public void onUserInteraction() {
        super.onUserInteraction();

        if(timeoutRunnable != null) {
            // restart timeout
            stopTimeoutHandler();
            startTimeoutHandler();
        }
    }

    private void confirmTransactionCancel() {
        JSONArray dataToSend = new JSONArray();
        dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_CANCEL));
        StatusUtil.notifyCurrentTransaction(dataToSend);
    }

    @Override
    public void onDialogButtonPositiveClick() {
        confirmTransactionCancel();
    }

    @Override
    public void onDialogButtonNegativeClick() {
        // nothing to do
    }

    @Override
    public void onDialogButtonNeutralClick() {
        // nothing to do
    }
}
