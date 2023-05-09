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

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.TransactionContract;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;
import com.amobilepayment.demo.Utils.TransObject;

public class CardEntryManualActivity extends BaseActivity implements OnClickListener {

    private final String TAG = CardEntryManualActivity.class.getSimpleName();

    TextView tv_card_number;
    String m_szPAN = "";
    int m_nMin = 0;
    int m_nMax = 0;

    @SuppressLint("SetTextI18n")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cardentry_manual);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        mScreenType = getIntent().getIntExtra(ARG_KEY, SCREEN_CARD_ENTRY);

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
        findViewById(R.id.btnenter).setOnClickListener(this);
        findViewById(R.id.btncancel).setOnClickListener(this);

        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);

        String sTitle = params[0];
        String sPrompt1 = params[1];
        String sPrompt2 = params[2];
        String sMax = params[3];
        String sMin = params[4];
        String sFieldFormat = params[5];
        String sMask = params[6];
        String sCurrSymbol = params[7];
        String sInpMethod = params[8];
        String siTimeout = params[9];

        // There is 11th parameter which is used in other screens such as AmountEntryActivity
        // to show default amount. But we don't do this for card numbers. So we ignore.

        TextView screenTitle = findViewById(R.id.screen_title);
        TextView prompt1 = findViewById(R.id.prompt1);
        TextView prompt2 = findViewById(R.id.prompt2);

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

        if(siTimeout != null && !siTimeout.isEmpty()) {
            startActivityTimeOut(Long.valueOf(siTimeout));
        }

        Button button_enter = findViewById(R.id.btnenter);
        button_enter.setText("OK");
        Button button_cancel = findViewById(R.id.btncancel);
        button_cancel.setText("CANCEL");


        tv_card_number = findViewById(R.id.tv_card_number);
        m_nMin = Integer.parseInt(sMin);
        m_nMax = Integer.parseInt(sMax);
    }

    @Override
    public void onClick(View view) {
        SettingsUtil.triggerBeep(this);

        switch (view.getId()) {
            case R.id.btn1:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "1";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btn2:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "2";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btn3:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "3";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btn4:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "4";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btn5:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "5";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btn6:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "6";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btn7:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "7";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btn8:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "8";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btn9:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "9";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btn0:
                if(m_szPAN.length() <= m_nMax) {
                    m_szPAN += "0";
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btnBack:
                int nLen = m_szPAN.length();
                if(nLen > 0) {
                    m_szPAN = m_szPAN.substring(0, nLen - 1);
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btnenter:
                if(!hasTimedOut) {
                    isUserDone = true;
                    if( (m_szPAN.length() >= m_nMin) && (m_szPAN.length() <= m_nMax) ) {
                        //TransObject.SetString(TransactionContract.CRTDATA_PAN, m_szPAN);
                        determineWhatToDo();
                    }
                }
            break;
            case R.id.btnclr:
                m_szPAN = "0";
                int nnLen = m_szPAN.length();
                if(nnLen > 0) {
                    m_szPAN = m_szPAN.substring(0, nnLen - 1);
                    DisplayFormat(m_szPAN);
                }
                break;
            case R.id.btncancel:
                cancelTransaction();
                break;
        }
    }

    private void determineWhatToDo() {
        switch(mScreenType) {
            case SCREEN_CARD_ENTRY:
                JSONArray dataToSend = new JSONArray();
                JSONObject data = new JSONObject();
                try {
                    // TODO: cleanup unnecessary keys
                    data.put("id", "dummy");
                    data.put("type", 1);
                    data.put("value", /*tv_card_number.getText().toString()*/ m_szPAN);
                    dataToSend.put(data);

                    dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                StatusUtil.notifyCurrentTransaction(dataToSend);
                break;
            case SCREEN_REPPASTREC_ACCOUNT:
            case SCREEN_RECALL_ACCOUNT:
//                TODO: StatusUtil.notifyCurrentTransaction(dataToSend);
                break;
        }
    }

    private void DisplayFormat(String szPAN)
    {
        String szDisplayBuffer = "";
        int nLen = szPAN.length();

        for(int i = 0, j = 0; i < nLen; i+=4, j++)
        {
            szDisplayBuffer += szPAN.substring(i, ((i+4)>nLen ? (nLen-i)+(j*4) : (i+4)));
            if((i+4) < nLen){
                szDisplayBuffer += " ";
            }
        }

        if(szDisplayBuffer.length() < 19)
        {
            nLen = szDisplayBuffer.length();
            for(int i = 0; i < (19 - nLen); i++)
                szDisplayBuffer += " ";
        }

        tv_card_number.setText(szDisplayBuffer);
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
}
