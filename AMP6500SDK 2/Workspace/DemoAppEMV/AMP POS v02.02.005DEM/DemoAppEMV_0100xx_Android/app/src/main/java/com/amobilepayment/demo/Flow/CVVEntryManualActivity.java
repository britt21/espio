package com.amobilepayment.demo.Flow;

import android.annotation.SuppressLint;
import android.os.Bundle;
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
import java.text.DecimalFormatSymbols;
import java.text.NumberFormat;
import java.util.Locale;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.TransactionContract;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;

public class CVVEntryManualActivity extends BaseActivity implements OnClickListener {

    private final String TAG = CVVEntryManualActivity.class.getSimpleName();

    TextView txtamt;
    DecimalFormat decimalFormatter;
    String numberPattern = "###";
    DecimalFormatSymbols separator;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cvventry_manual);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

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
        findViewById(R.id.btn00).setOnClickListener(this);
        findViewById(R.id.btnclr).setOnClickListener(this);
        findViewById(R.id.btnenter).setOnClickListener(this);
        findViewById(R.id.btncancel).setOnClickListener(this);

        NumberFormat nf = NumberFormat.getInstance(Locale.US);
        if (nf instanceof DecimalFormat) {
            decimalFormatter = (DecimalFormat) nf;
            decimalFormatter.setDecimalSeparatorAlwaysShown(true);
            decimalFormatter.applyPattern(numberPattern);
            separator = decimalFormatter.getDecimalFormatSymbols();
            separator.setGroupingSeparator(' ');
            decimalFormatter.setDecimalFormatSymbols(separator);
        }

        txtamt = findViewById(R.id.txtAmount);
        setTitle("Amount Entry");

        TextView screenTitle = findViewById(R.id.screen_title);
        screenTitle.setText("Enter CVV Code");
        Button button_enter = findViewById(R.id.btnenter);
        button_enter.setText("OK");
        Button button_cancel = findViewById(R.id.btncancel);
        button_cancel.setText("CANCEL");
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
            case R.id.btn00:
                fixAppend(displayStr, "00", true);
                break;
            case R.id.btnenter:
                String cvv = displayStr.toString();
                JSONArray dataToSend = new JSONArray();
                JSONObject data = new JSONObject();
                try {
                    data.put("id", TransactionContract.CRTDATA_CARDCVV2);
                    data.put("type", 1);
                    data.put("value", cvv);
                    dataToSend.put(data);
                    dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                StatusUtil.notifyCurrentTransaction(dataToSend);
                break;
            case R.id.btnclr:
                if(displayStr.length() > 0) {
                    displayStr.deleteCharAt(displayStr.length() - 1);
                    fixDelete(displayStr);
                }
                break;
            case R.id.btncancel:
                cancelTransaction();
                break;
        }
    }

    private void fixDelete(StringBuilder displayStr) {
        String currentAmount = displayStr.toString();
        if(!currentAmount.isEmpty()) {
            BigDecimal newAmount = new BigDecimal(currentAmount.replace(" ", ""));
            String updatedAmount = decimalFormatter.format(newAmount);
            txtamt.setText(updatedAmount);
        }
        else {
            txtamt.setText("");
        }
    }

    private void fixAppend(StringBuilder displayStr, String digit) {
        fixAppend(displayStr, digit, false);
    }

    private void fixAppend(StringBuilder displayStr, String digit, boolean flag) {
        if(!isMaxAmount(flag)) {
            displayStr.append(digit);

            BigDecimal newAmount;
            String currentAmount = displayStr.toString();
            newAmount = new BigDecimal(currentAmount.replace(" ", ""));

            String updatedAmount = decimalFormatter.format(newAmount);
            txtamt.setText(updatedAmount);
        }
    }

    private boolean isMaxAmount(boolean flag) {
        if(flag) return txtamt.length() > numberPattern.length()-2;
        return txtamt.length() > numberPattern.length()-1;
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
}
