package com.amobilepayment.demo.Flow;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;

import AmpBaseInterface.AmpBaseInterface;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;

import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Locale;

public class AmountEntryActivity extends BaseActivity implements OnClickListener {

    private final String TAG = AmountEntryActivity.class.getSimpleName();

    TextView txtamt;
    DecimalFormat decimalFormatter;
    DecimalFormat minMaxDecimalFormatter;

    // TODO: use $sFieldFormat parameter and translate to format expected by DecimalFormatter
    public final static String AMOUNT_PATTERN = "###,##0.00";
    public final static String MIN_MAX_AMOUNT_PATTERN = "#";
    public short mMinimum = 0;
    public short mMaximum = 0;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_amountentry);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);

        for(String s: params)
        {
            Log.d(TAG, "param="+s);
        }

        String sTitle = params[0];
        String sPrompt1 = params[1];
        String sPrompt2 = params[2];
        mMaximum = Short.valueOf(params[3]);
        mMinimum = Short.valueOf(params[4]);
        String sFieldFormat = params[5];
        String sMask = params[6];
        String sCurrSymbol = params[7];
        String sInpMethod = params[8];
        String siTimeout = params[9];

        String sDefaultValue = null;
        if(params.length>10){
            sDefaultValue = params[10];
            if(sDefaultValue != null && sDefaultValue.isEmpty()) {
                sDefaultValue = getString(R.string.enter_amount_default_amount);
            }
        }

        TextView screenTitle = findViewById(R.id.screen_title);
        TextView prompt1 = findViewById(R.id.prompt1);
        TextView prompt2 = findViewById(R.id.prompt2);
        TextView currency = findViewById(R.id.currency);

        if(sTitle != null && !sTitle.isEmpty()) {
            screenTitle.setVisibility(View.VISIBLE);
            screenTitle.setText(sTitle);
        }
        if(sPrompt1 != null && !sPrompt1.isEmpty()) {
            prompt1.setVisibility(View.VISIBLE);
            prompt1.setText(sPrompt1);
        }
        if(sPrompt2 != null && !sPrompt2.isEmpty()) {
            prompt2.setVisibility(View.VISIBLE);
            prompt2.setText(sPrompt2);
        }
        if(sCurrSymbol != null && !sCurrSymbol.isEmpty()) {
            currency.setVisibility(View.VISIBLE);
            currency.setText(sCurrSymbol);
        }

        if(siTimeout != null && !siTimeout.isEmpty()) {
            startActivityTimeOut(Long.valueOf(siTimeout));
        }

        findViewById(R.id.btn1).setOnClickListener(this);
        findViewById(R.id.btn2).setOnClickListener(this);
        findViewById(R.id.btn3).setOnClickListener(this);
        findViewById(R.id.btn4).setOnClickListener(this);
        findViewById(R.id.btn5).setOnClickListener(this);
        findViewById(R.id.btn6).setOnClickListener(this);
        findViewById(R.id.btn7).setOnClickListener(this);
        findViewById(R.id.btn8).setOnClickListener(this);
        findViewById(R.id.btn9).setOnClickListener(this);
        findViewById(R.id.btn0).setOnClickListener(this);
        findViewById(R.id.btnBack).setOnClickListener(this);
        findViewById(R.id.btnclr).setOnClickListener(this);
        Button buttonEnter = findViewById(R.id.btnenter);
        Button buttonCancel = findViewById(R.id.btncancel);
        buttonEnter.setOnClickListener(this);
        buttonCancel.setOnClickListener(this);
        //buttonEnter.setText(AmpBaseInterface.GetScrMsg("OK"));
        //buttonCancel.setText(AmpBaseInterface.GetScrMsg("CANCEL"));
        buttonEnter.setText("OK");
        buttonCancel.setText("CANCEL");

        NumberFormat nf = NumberFormat.getInstance(Locale.US);
        if (nf instanceof DecimalFormat) {
            decimalFormatter = (DecimalFormat) nf;
            decimalFormatter.setDecimalSeparatorAlwaysShown(true);
            decimalFormatter.applyPattern(AMOUNT_PATTERN);
        }

        // minimum and maximum checker
        NumberFormat _nf = NumberFormat.getInstance(Locale.US);
        if (_nf instanceof DecimalFormat) {
            minMaxDecimalFormatter = (DecimalFormat) _nf;
            minMaxDecimalFormatter.applyPattern(MIN_MAX_AMOUNT_PATTERN);
        }

        txtamt = findViewById(R.id.txtAmount);

        if(sDefaultValue != null) {
            txtamt.setText(sDefaultValue);
        }
    }

    @Override
    public void onClick(View view) {
        SettingsUtil.triggerBeep(this);
        StringBuilder displayStr = new StringBuilder(txtamt.getText().toString());

        switch (view.getId()) {
            case R.id.btn1:
                fixAppend(displayStr, "1");
                break;
            case R.id.btn2:
                fixAppend(displayStr, "2");
                break;
            case R.id.btn3:
                fixAppend(displayStr, "3");
                break;
            case R.id.btn4:
                fixAppend(displayStr, "4");
                break;
            case R.id.btn5:
                fixAppend(displayStr, "5");
                break;
            case R.id.btn6:
                fixAppend(displayStr, "6");
                break;
            case R.id.btn7:
                fixAppend(displayStr, "7");
                break;
            case R.id.btn8:
                fixAppend(displayStr, "8");
                break;
            case R.id.btn9:
                fixAppend(displayStr, "9");
                break;
            case R.id.btn0:
                fixAppend(displayStr, "0");
                break;
            case R.id.btnBack:
                displayStr.deleteCharAt(displayStr.length() - 1);
                fixDelete(displayStr);
                break;
            case R.id.btnenter:
                Number newAmount = null;
                BigDecimal bd = null;
                long amount = 0L;
                try {
                    newAmount = decimalFormatter.parse(displayStr.toString());
                    bd = new BigDecimal(newAmount.toString());
                    amount = convertToLong(bd);
                } catch (ParseException e) {
                    e.printStackTrace();
                }

                // check if input.length >= $mMinimum
                try {
                    Number n = minMaxDecimalFormatter.parse(txtamt.getText().toString().replaceAll("[.,]", ""));
                    String input = String.valueOf(n);
                    if(input.length() < mMinimum) return;
                } catch (ParseException e) {
                    e.printStackTrace();
                }

                if(!hasTimedOut) {
                    isUserDone = true;
                    prepareAndSendData(amount);
                }
                break;
            case R.id.btnclr:
                displayStr = new StringBuilder("0.00");
                displayStr.deleteCharAt(displayStr.length() - 1);
                fixDelete(displayStr);
                break;
            case R.id.btncancel:
                cancelTransaction();
                break;
        }
    }

    private void prepareAndSendData(long amt) {
        String amount = "";
        if(amt > 0)
            amount = String.valueOf(amt);
        JSONArray dataToSend = new JSONArray();
        JSONObject data = new JSONObject();
        try {
            data.put("id", "dummy");
            data.put("type", 1);
            data.put("value", amount);
            dataToSend.put(data);

            dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
        } catch (JSONException e) {
            e.printStackTrace();
        }
        StatusUtil.notifyCurrentTransaction(dataToSend);
    }

    private void fixDelete(StringBuilder displayStr) {
        try {
            Number newAmount = decimalFormatter.parse(displayStr.toString());
            BigDecimal bd = new BigDecimal(newAmount.toString());
            bd = bd.movePointLeft(1);
            String updatedAmount = decimalFormatter.format(bd.doubleValue());
            txtamt.setText(updatedAmount);
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    private void fixAppend(StringBuilder displayStr, String digit) {
        fixAppend(displayStr, digit, false);
    }

    private void fixAppend(StringBuilder displayStr, String digit, boolean flag) {
        if(!isMaxAmount(flag)) {
            displayStr.append(digit);
            Number newAmount;
            try {
                newAmount = decimalFormatter.parse(displayStr.toString());
            } catch (ParseException e) {
                e.printStackTrace();
                return;
            }

            // fix new input
            newAmount = newAmount.doubleValue() * 10.00;
            if("00".equals(digit)) newAmount = newAmount.doubleValue() * 10.00;
            String updatedAmount = decimalFormatter.format(newAmount);
            txtamt.setText(updatedAmount);
        }
    }

    private boolean isMaxAmount(boolean flag) {
        try {
            Number n = minMaxDecimalFormatter.parse(txtamt.getText().toString().replaceAll("[.,]", ""));
            String input = String.valueOf(n);

            if(input.length() >= mMaximum) return true;
            if(flag)
                if(input.length() >= mMaximum-1) return true;

        } catch (ParseException e) {
            e.printStackTrace();
        }

        return false;
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

    @Override
    public void onDialogButtonPositiveClick() {
        isUserDone = true;
        hasTimedOut = true;
        super.onDialogButtonPositiveClick();
    }
}
