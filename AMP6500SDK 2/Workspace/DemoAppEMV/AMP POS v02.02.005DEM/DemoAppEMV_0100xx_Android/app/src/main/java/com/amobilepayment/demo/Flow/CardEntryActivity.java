package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.Locale;

import AmpBaseInterface.AmpBaseInterface;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.TransactionContract;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.Storage;
import com.amobilepayment.demo.Utils.TransObject;


public class CardEntryActivity extends BaseActivity {
    private String TAG = getClass().getSimpleName();

    public static int gKeyPress = -1;
    private int mKeyPress = -1;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("AMPEMVL2");
        System.loadLibrary("AmpEmvL2AndroidIF");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        Log.d(TAG, "onCreate");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_card_entry);
        //getSupportActionBar().setBackgroundDrawable(new ColorDrawable(Color.parseColor("#035073")));

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);
        String sTitle = params[0];
        String sPrompt = params[1];

        Number lnAmount = 0; //TransObject.GetLong(TransactionContract.CRTDATA_TOTAL_AMT);

        if(lnAmount.doubleValue() > 0) {
            DecimalFormat decimalFormatter;

            NumberFormat nf = NumberFormat.getInstance(Locale.US);
            //if (nf instanceof DecimalFormat) {
            decimalFormatter = (DecimalFormat) nf;
            decimalFormatter.setDecimalSeparatorAlwaysShown(true);
            decimalFormatter.applyPattern(AmountEntryActivity.AMOUNT_PATTERN);
            //}
            String FormattedAmt = decimalFormatter.format(lnAmount.doubleValue() / 100);

            TextView textView = findViewById(R.id.txtCardAmount);
            textView.setText(FormattedAmt);
        }
        else {
            View amountHolder = findViewById(R.id.amount_holder);
            amountHolder.setVisibility(View.INVISIBLE);
        }

        mKeyPress = -1; // means no key was pressed yet

        TextView screenTitle = findViewById(R.id.screen_title);
        screenTitle.setText(sTitle);
        TextView prompt = findViewById(R.id.prompt);
        prompt.setText(sPrompt);
    }

    @Override
    public void onBackPressed() {
        SettingsUtil.triggerBeep(this);

        DialogManager.onCancelAlert(this,
                /*AmpBaseInterface.GetScrMsg("DIALOGS.SUREWANTTOCANCEL")*/ "Are you sure you want to cancel?");

        mKeyPress = 18;     // Same as Cancel Key was pressed
    }

    public void onKeyboardClick(View view)
    {
        SettingsUtil.triggerBeep(this);

        gKeyPress = 17; // KEY_ENTER (means Manual Entry was invoked)
    }

    @Override
    public void onDialogButtonPositiveClick() {
        gKeyPress = mKeyPress;
        mKeyPress = -1;

        // Let AmpEmvCB manage its own destruction
        //super.onDialogButtonPositiveClick();
    }
}

