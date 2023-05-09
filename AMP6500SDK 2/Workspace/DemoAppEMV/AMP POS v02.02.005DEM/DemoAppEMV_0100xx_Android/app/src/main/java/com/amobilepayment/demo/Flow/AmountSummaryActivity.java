package com.amobilepayment.demo.Flow;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Locale;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.TransactionContract;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;


public class AmountSummaryActivity extends BaseActivity {

    private final static String TAG = AmountSummaryActivity.class.getSimpleName();

    private String mTotal;

    private final int iBaseAmt = 0;
    private final int iTipAmt = 1;
    private final int iCBAmt = 2;
    private final int iTaxAmt = 3;
    private final int iTotalSCAmt = 4;
    private final int iTotalPreAuthAmt = 5;
    private final int iTotalAmt = 6;

    private DecimalFormat decimalFormatter;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_amount_summary);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        mScreenType = getIntent().getIntExtra(ARG_KEY, BaseActivity.SCREEN_SL_CONFIRM_TOTAL);
        mParameters = getIntent().getStringArrayExtra(PARAM_KEY);

        TextView txtSummary = findViewById(R.id.screen_title);
        switch(mScreenType) {
            case BaseActivity.SCREEN_SL_CONFIRM_TOTAL:
                txtSummary.setText("Purchase"/*AmpBaseInterface.GetScrMsg("AMOUNTSUMMARYACTIVITY.TITLE.SALE")*/);
                break;
//            case BaseActivity.SCREEN_RF_CONFIRM_TOTAL:
//                txtSummary.setText(AmpBaseInterface.GetScrMsg("AMOUNTSUMMARYACTIVITY.TITLE.REFUND"));
//                break;
//            case BaseActivity.SCREEN_FP_CONFIRM_TOTAL:
//                txtSummary.setText(AmpBaseInterface.GetScrMsg("AMOUNTSUMMARYACTIVITY.TITLE.FORCEPOST"));
//                break;
//            case TRANS_PREAUTH_COMP:
//                txtSummary.setText(getString(R.string.completion_transaction)+ " " + txtSummary.getText());
//                break;
//            case TRANS_PREAUTH_PURCHASE:
//                txtSummary.setText(getString(R.string.preauth_transaction)+ " " + txtSummary.getText());
//                break;
            default:
                break;
        }

        TextView label_amount       = findViewById(R.id.label_amount);
        TextView label_tip          = findViewById(R.id.label_tip);
        TextView label_cashback     = findViewById(R.id.label_cashback);
        TextView label_surcharge    = findViewById(R.id.label_surcharge);
        TextView label_total        = findViewById(R.id.label_total);

//        label_amount.setText(AmpBaseInterface.GetScrMsg("BASEAMOUNT"));
//        label_tip.setText(AmpBaseInterface.GetScrMsg("TIPAMOUNT"));
//        label_cashback.setText(AmpBaseInterface.GetScrMsg("CASHBACKAMOUNT"));
//        label_surcharge.setText(AmpBaseInterface.GetScrMsg("SURCHARGEAMOUNT"));
//        label_total.setText(AmpBaseInterface.GetScrMsg("TOTALAMOUNT"));

        Button button_ok     = findViewById(R.id.button_ok);
        Button button_cancel = findViewById(R.id.button_cancel);
        //button_ok.setText(AmpBaseInterface.GetScrMsg("OK"));
        //button_cancel.setText(AmpBaseInterface.GetScrMsg("CANCEL"));
        button_ok.setText("OK");
        button_cancel.setText("CANCEL");

        TextView tv_amount       = findViewById(R.id.amount);
        TextView tv_tip          = findViewById(R.id.tip);
        TextView tv_cashback     = findViewById(R.id.cashback);
        TextView tv_surcharge    = findViewById(R.id.surcharge);
        TextView tv_total        = findViewById(R.id.total);

        LinearLayout ll_tp = findViewById(R.id.layout_tip);
        LinearLayout ll_cb = findViewById(R.id.layout_cashback);
        LinearLayout ll_sc = findViewById(R.id.layout_surcharge);

        String amount    = mParameters[iBaseAmt].trim();
        String tip       = mParameters[iTipAmt].trim();
        String cashback  = mParameters[iCBAmt].trim();
        String surcharge = mParameters[iTotalSCAmt].trim();
        mTotal     = mParameters[iTotalAmt].trim();
//        String tax       = mParameters[iTaxAmt];
//        String preauth   = mParameters[iTotalPreAuthAmt];

        // temporary as flow will always send data, never null/empty
        if(amount == null    || amount.isEmpty())      amount  = "0.00";
        if(tip == null       || tip.isEmpty())            tip  = "0.00";
        if(cashback == null  || cashback.isEmpty())  cashback  = "0.00";
        if(surcharge == null || surcharge.isEmpty()) surcharge = "0.00";
        if(mTotal == null    || mTotal.isEmpty())      mTotal  = "0.00";

        NumberFormat nf = NumberFormat.getInstance(Locale.US);
        if (nf instanceof DecimalFormat) {
            decimalFormatter = (DecimalFormat) nf;
            decimalFormatter.setDecimalSeparatorAlwaysShown(true);
            decimalFormatter.applyPattern(AmountEntryActivity.AMOUNT_PATTERN);
        }

        try {
            Number newTip = decimalFormatter.parse(tip);
            Number newCashback = decimalFormatter.parse(cashback);
            Number newSurcharge = decimalFormatter.parse(surcharge);
            if(!(newTip.doubleValue() > 0))       ll_tp.setVisibility(View.GONE);
            if(!(newCashback.doubleValue() > 0))  ll_cb.setVisibility(View.GONE);
            if(!(newSurcharge.doubleValue() > 0)) ll_sc.setVisibility(View.GONE);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        tv_amount.setText(amount);
        tv_tip.setText(tip);
        tv_cashback.setText(cashback);
        tv_surcharge.setText(surcharge);
        tv_total.setText(mTotal);
    }

    public void okButtonClicked(View view) {
        SettingsUtil.triggerBeep(this);

        long formattedTotal;
        try {
            Number newTotal = decimalFormatter.parse(mTotal);
            BigDecimal bd = new BigDecimal(newTotal.toString());
            formattedTotal = convertToLong(bd);
            mTotal = String.valueOf(formattedTotal);
        } catch (ParseException e) {
            e.printStackTrace();
        }
        JSONArray dataToSend = new JSONArray();
        JSONObject data = new JSONObject();
        try {
            data.put("id", TransactionContract.CRTDATA_TOTAL_AMT);
            data.put("type", 1);
            data.put("value", mTotal);
            dataToSend.put(data);
            dataToSend.put(prepareStatusObject());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        StatusUtil.notifyCurrentTransaction(dataToSend);
    }

    private JSONObject prepareStatusObject() {
        JSONObject data = new JSONObject();
        try {
            data.put("id", "STATUS");
            data.put("type", 0);
            data.put("value", 0);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return data;
    }

    public void cancelButtonClicked(View view) {
        SettingsUtil.triggerBeep(this);
        cancelTransaction();
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

    private long convertToLong(BigDecimal amount) {
        Double fixedAmount = amount.doubleValue() * 100;
        return fixedAmount.longValue();
    }
}
