package com.amobilepayment.demo.Flow;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.math.BigDecimal;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Locale;

import AmpBaseInterface.AmpBaseInterface;

public class AmountEntryRegularActivity extends BaseActivity implements OnClickListener {

    private final String TAG = AmountEntryRegularActivity.class.getSimpleName();

    EditText txtamt;
    DecimalFormat decimalFormatter;
    DecimalFormat minMaxDecimalFormatter;

    // TODO: use $sFieldFormat parameter and translate to format expected by DecimalFormatter
    public final static String AMOUNT_PATTERN = "###,##0.00";
    public final static String MIN_MAX_AMOUNT_PATTERN = "#";
    public short mMinimum = 0;
    public short mMaximum = 0;

    private TheTextWatcher mTheTextWatcher;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_amountentry_regular);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);

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

        txtamt.setSelection(txtamt.getText().length());

        mTheTextWatcher = new TheTextWatcher();

        txtamt.addTextChangedListener(mTheTextWatcher);

        txtamt.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                txtamt.setSelection(txtamt.getText().length());
            }
        });

        txtamt.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int i, KeyEvent keyEvent) {
                boolean handled = false;
                if(i == EditorInfo.IME_ACTION_GO) {
                    handled = true;
                    buttonEnterPressed(txtamt.getText().toString());
                }
                return handled;
            }
        });
    }

    private class TheTextWatcher implements TextWatcher {
        @Override
        public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
        }

        @Override
        public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {

        }

        @Override
        public void afterTextChanged(Editable editable) {
            txtamt.removeTextChangedListener(this);
            fixAppend(editable.toString());
            txtamt.addTextChangedListener(this);
        }

        private void fixAppend(String i) {
            if(!isMaxAmount(false)) {
                Number newAmount;
                try {
                    String input = i.toString().replaceAll("[,.]", "");
                    newAmount = decimalFormatter.parse(input);
                } catch (ParseException e) {
                    e.printStackTrace();
                    return;
                }

                // fix new input
                String updatedAmount = decimalFormatter.format(newAmount.doubleValue()/100);

                txtamt.setText(updatedAmount);
                txtamt.setSelection(updatedAmount.length());
            }
            else {
                Number newAmount;
                // rollback the last input
                String _input = i.toString().replaceAll("[,.]", "");
                String input = _input.substring(0, _input.length()-1);

                try {
                    newAmount = decimalFormatter.parse(input);
                } catch (ParseException e) {
                    e.printStackTrace();
                    return;
                }

                // fix new input
                String updatedAmount = decimalFormatter.format(newAmount.doubleValue()/100);

                txtamt.setText(updatedAmount);
                txtamt.setSelection(updatedAmount.length());
            }
        }
    }

    @Override
    public void onClick(View view) {
        SettingsUtil.triggerBeep(this);
        StringBuilder displayStr = new StringBuilder(txtamt.getText().toString());

        switch (view.getId()) {
            case R.id.btnenter:
                buttonEnterPressed(displayStr.toString());
                break;
            case R.id.btncancel:
                cancelTransaction();
                break;
        }
    }

    private void buttonEnterPressed(String sAmount) {
        Number newAmount = null;
        BigDecimal bd = null;
        long amount = 0L;
        try {
            newAmount = decimalFormatter.parse(sAmount);
            bd = new BigDecimal(newAmount.toString());
            amount = convertToLong(bd);
        } catch (ParseException e) {
            e.printStackTrace();
        }

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

            if(flag) {
                if (input.length() >= mMaximum) return true;
            }
            else {
                if (input.length() > mMaximum) return true;
            }

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
