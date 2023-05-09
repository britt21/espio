package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.support.v4.view.GestureDetectorCompat;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.json.JSONArray;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;

public class TransactionDetailsActivity extends BaseActivity
         {

    private static String TAG = TransactionDetailsActivity.class.getSimpleName();
    private GestureDetectorCompat mDetector;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_transaction_details_print);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        mScreenType = getIntent().getIntExtra(ARG_KEY, SCREEN_DETAILS_CONFIRMATION);
        switch(mScreenType) {
            case SCREEN_DETAILS_CONFIRMATION: {
                    LinearLayout layout_twoButton = findViewById(R.id.layout_two_button);
                    layout_twoButton.setVisibility(View.VISIBLE);

                    Button button_ok = layout_twoButton.findViewById(R.id.btnenter);
                    Button button_cancel = layout_twoButton.findViewById(R.id.btncancel);
                    button_ok.setText("OK");
                    button_cancel.setText("CANCEL");

                    button_ok.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            SettingsUtil.triggerBeep(TransactionDetailsActivity.this);

                            if (!hasTimedOut) {
                                isUserDone = true;

                                JSONArray dataToSend = new JSONArray();
                                dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMPKEY_ENTER));
                                StatusUtil.notifyCurrentTransaction(dataToSend);
                            }
                        }
                    });
                    button_cancel.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            SettingsUtil.triggerBeep(TransactionDetailsActivity.this);

                            if (!hasTimedOut) {
                                isUserDone = true;

                                JSONArray dataToSend = new JSONArray();
                                dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMPKEY_CANCEL));
                                StatusUtil.notifyCurrentTransaction(dataToSend);
                            }
                        }
                    });
            }
                break;
            case SCREEN_DETAILS_SELECTION: {
                    LinearLayout layout_threeButton = findViewById(R.id.layout_three_button);
                    layout_threeButton.setVisibility(View.VISIBLE);

                    TextView tv_summary_previous = layout_threeButton.findViewById(R.id.tv_summary_previous);
                    TextView tv_summary_next = layout_threeButton.findViewById(R.id.tv_summary_next);
                    TextView tv_summary_cancel = layout_threeButton.findViewById(R.id.tv_summary_cancel);
                    tv_summary_previous.setText("PREVIOUS");
                    tv_summary_next.setText("NEXT");
                    tv_summary_cancel.setText("SELECT");

                    tv_summary_previous.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            SettingsUtil.triggerBeep(TransactionDetailsActivity.this);

                            browseLeft();
                        }
                    });
                    tv_summary_next.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            SettingsUtil.triggerBeep(TransactionDetailsActivity.this);

                            browseRight();
                        }
                    });
                    tv_summary_cancel.setOnClickListener(new View.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            SettingsUtil.triggerBeep(TransactionDetailsActivity.this);

                            if (!hasTimedOut) {
                                isUserDone = true;

                                JSONArray dataToSend = new JSONArray();
                                dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMPKEY_MENU3));
                                StatusUtil.notifyCurrentTransaction(dataToSend);
                            }
                        }
                    });

                    mDetector = new GestureDetectorCompat(this, new MyGestureListener());
                }
                break;
        }

        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);
        String regex = ".*:";
        String sTransaction = params[0];
        String sInvoiceNum = params[1];
        sInvoiceNum = sInvoiceNum.replaceAll(regex, "");
        String sCardNum = params[2];
        String sPRN = params[3];
        sPRN = sPRN.replaceAll(regex, "");
        String sAmount = params[4];
        String sAuthNum = params[5];
        sAuthNum = sAuthNum.replaceAll(regex, "");
        String sDateTime = params[6];
        String sVoided = params[7];
        sVoided = sVoided.replaceAll(regex, "");
        String sTitle = params[8];
        String sTimeout = params[9];

        TextView screenTitle = findViewById(R.id.screen_title);

        // labels
        TextView label_transaction  = findViewById(R.id.label_transaction);
        TextView label_invoice_num  = findViewById(R.id.label_invoice_number);
        TextView label_card_number  = findViewById(R.id.label_card_number);
        TextView label_prn          = findViewById(R.id.label_prn);
        TextView label_amount       = findViewById(R.id.label_amount);
        TextView label_auth_number  = findViewById(R.id.label_auth_number);
        TextView label_date_time    = findViewById(R.id.label_date_time);
        TextView label_voided       = findViewById(R.id.label_voided);
        screenTitle.setText(sTitle);
//        label_transaction.setText(AmpBaseInterface.GetScrMsg("TRANSACTIONDETAILSACTIVITY.TRANSTYPE"));
//        label_invoice_num.setText(AmpBaseInterface.GetScrMsg("TRANSACTIONDETAILSACTIVITY.INVOICENUM"));
//        label_card_number.setText(AmpBaseInterface.GetScrMsg("TRANSACTIONDETAILSACTIVITY.CARDNUM"));
//        label_prn        .setText(AmpBaseInterface.GetScrMsg("TRANSACTIONDETAILSACTIVITY.RRNNUM"));
//        label_amount     .setText(AmpBaseInterface.GetScrMsg("BASEAMOUNT"));
//        label_auth_number.setText(AmpBaseInterface.GetScrMsg("TRANSACTIONDETAILSACTIVITY.AUTHNUM"));
//        label_date_time  .setText(AmpBaseInterface.GetScrMsg("TRANSACTIONDETAILSACTIVITY.DATETIME"));
//        label_voided     .setText(AmpBaseInterface.GetScrMsg("TRANSACTIONDETAILSACTIVITY.VOIDED"));

        // values
        TextView tv_transaction  = findViewById(R.id.tv_transaction);
        TextView tv_invoice_num  = findViewById(R.id.tv_invoice_number);
        TextView tv_card_number  = findViewById(R.id.tv_card_number);
        TextView tv_prn          = findViewById(R.id.tv_prn);
        TextView tv_amount       = findViewById(R.id.tv_amount);
        TextView tv_auth_number  = findViewById(R.id.tv_auth_number);
        TextView tv_date_time    = findViewById(R.id.tv_date_time);
        TextView tv_voided       = findViewById(R.id.tv_voided);
        tv_transaction.setText(sTransaction);
        tv_invoice_num.setText(sInvoiceNum);
        tv_card_number.setText(sCardNum);
        tv_prn        .setText(sPRN);
        tv_amount     .setText(sAmount);
        tv_auth_number.setText(sAuthNum);
        tv_date_time  .setText(sDateTime);
        tv_voided     .setText(sVoided);

        if(sTimeout != null && !sTimeout.isEmpty()) {
            startActivityTimeOut(Long.valueOf(sTimeout));
        }
    }

    private void browseLeft() {
        if (!hasTimedOut) {
            isUserDone = true;

            JSONArray dataToSend = new JSONArray();
            dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMPKEY_MENU1));
            StatusUtil.notifyCurrentTransaction(dataToSend);
        }
    }

    private void browseRight() {
        if (!hasTimedOut) {
            isUserDone = true;

            JSONArray dataToSend = new JSONArray();
            dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMPKEY_MENU2));
            StatusUtil.notifyCurrentTransaction(dataToSend);
        }
    }

    @Override
    public void onBackPressed() {
        SettingsUtil.triggerBeep(this);

        cancelTransaction();
    }

    private void cancelTransaction() {
        DialogManager.onCancelAlert(this,
                /*AmpBaseInterface.GetScrMsg("DIALOGS.SUREWANTTOCANCEL")*/ "Are you sure you want to cancel?");
    }

    @Override
    public void onDialogButtonPositiveClick() {
        isUserDone = true;
        hasTimedOut = true;
        super.onDialogButtonPositiveClick();
    }

    @Override
    public boolean onTouchEvent(MotionEvent event){
        if(mDetector != null) mDetector.onTouchEvent(event);
        return super.onTouchEvent(event);
    }

    class MyGestureListener extends GestureDetector.SimpleOnGestureListener {
    final float THRESHOLD = 1000f;

        @Override
        public boolean onDown(MotionEvent event) {
            return true;
        }

        @Override
        public boolean onFling(MotionEvent event1, MotionEvent event2,
                            float velocityX, float velocityY) {
            if(Math.abs(velocityX) > Math.abs(velocityY)) {
                if(Math.abs(velocityX) > THRESHOLD) {
                    SettingsUtil.triggerBeep(TransactionDetailsActivity.this);

                    if(velocityX > 0) browseRight();
                    else browseLeft();
                }
            }
            return true;
        }
    }
}
