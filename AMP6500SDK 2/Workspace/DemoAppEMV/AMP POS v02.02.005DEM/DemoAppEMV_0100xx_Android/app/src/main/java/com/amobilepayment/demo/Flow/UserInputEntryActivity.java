package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.text.Editable;
import android.text.InputFilter;
import android.text.InputType;
import android.text.Spanned;
import android.text.TextWatcher;
import android.text.method.DigitsKeyListener;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import AmpBaseInterface.AmpBaseInterface;
import AmpBaseInterface.AmpBaseCB;
import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;

public class UserInputEntryActivity extends BaseActivity {

    private final String TAG = UserInputEntryActivity.class.getSimpleName();

    private EditText mUserInput;
    private int inputMinimumLength = -1;
    private int inputMaximumLength = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_user_input_entry);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        mUserInput = findViewById(R.id.et_input);
        mUserInput.setOnEditorActionListener(new EditText.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int id, KeyEvent keyEvent) {
                boolean handled = false;
                if (id == EditorInfo.IME_ACTION_GO) {
                    handled = true;
                    prepareAndSendData();
                }
                return handled;
            }
        });

        mUserInput.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                // restart timer manually;
                // this has to be done because BaseActivity.onUserActivity is not triggered
                // on keyboard presses
                stopTimeoutHandler();
                startTimeoutHandler();
            }

            @Override
            public void afterTextChanged(Editable editable) {
            }
        });

        // save the current filters set for Edit Text then append the new ones
        ArrayList<InputFilter> curInputFilters = new ArrayList<>(Arrays.asList(mUserInput.getFilters()));


        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);

        String sTitle = params[0];
        String sPrompt1 = params[1];
        String sPrompt2 = params[2];
        inputMaximumLength = Integer.valueOf(params[3]);
        inputMinimumLength = Integer.valueOf(params[4]);
        String sFieldFormat = params[5];
        String sMask = params[6];
        String sCurrSymbol = params[7];
        String sInpMethod = params[8];
        String siTimeout = params[9];
        String sDefaultValue = params[10];

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
        if(sDefaultValue != null && !sDefaultValue.isEmpty()) {
            mUserInput.setText(sDefaultValue);
        }

        if(siTimeout != null && !siTimeout.isEmpty()) {
            startActivityTimeOut(Long.valueOf(siTimeout));
        }

        // set minimum and maximum allowable input length
        curInputFilters.add(new InputFilter.LengthFilter(inputMaximumLength));

        String alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        String numeric = "0123456789";
        String binary = "01";
        String dot = ".";

        final Pattern hexadecimalPattern = Pattern.compile("[0-9A-Fa-f]");

        int inputMethod1 = Integer.valueOf(sInpMethod) & 0x0F;
        int inputMethod2   = Integer.valueOf(sInpMethod) & 0xF0;

        // set input type
        switch(inputMethod1) {
            case AmpBaseCB.INP_METH_NUM_ONLY:
                mUserInput.setKeyListener(DigitsKeyListener.getInstance(numeric));
                mUserInput.setInputType(InputType.TYPE_CLASS_NUMBER);
                break;
            case AmpBaseCB.INP_METH_NUM_WITH_DOT:
                mUserInput.setKeyListener(DigitsKeyListener.getInstance(numeric+dot));
                break;
            case AmpBaseCB.INP_METH_ALPHA_ONLY:
                mUserInput.setInputType(InputType.TYPE_TEXT_VARIATION_PERSON_NAME | InputType.TYPE_CLASS_TEXT);
                curInputFilters.add(
                    new InputFilter() {
                        public CharSequence filter(CharSequence src, int start,
                                                   int end, Spanned dst, int dstart, int dend) {
                            if (src.equals("")) { // for backspace
                                return src;
                            }
                            if (src.toString().matches("[a-zA-Z]+")) {
                                return src;
                            }
                            return "";
                        }
                    }
                );
                break;
            case AmpBaseCB.INP_METH_ALPHA_NUMERIC:
                mUserInput.setInputType(InputType.TYPE_CLASS_TEXT);
                setKeyboardAlphaNumeric(curInputFilters);
                break;
            case AmpBaseCB.INP_METH_BINARY_ONLY:
                mUserInput.setKeyListener(DigitsKeyListener.getInstance(binary));
                break;
            case AmpBaseCB.INP_METH_HEX_ONLY:
                mUserInput.setInputType(InputType.TYPE_TEXT_VARIATION_VISIBLE_PASSWORD);
                curInputFilters.add(
                        new InputFilter() {
                            public CharSequence filter(CharSequence src, int start,
                                                       int end, Spanned dst, int dstart, int dend) {
                                if (src.length() > 0) {
                                    Matcher m = hexadecimalPattern.matcher(""+src.charAt(0));
                                    if(!m.find()) return "";
                                }
                                return null;
                            }
                        }
                );
                curInputFilters.add(new InputFilter.AllCaps());
                break;
            case AmpBaseCB.INP_METH_CUSTOMKEY_MAP:
                // TODO: for now, use default keyboard
            case AmpBaseCB.INP_METH_NUM_WITH_PUNC:
                // TODO: for now, use default keyboard
            case AmpBaseCB.INP_METH_ALL_KEYS:
            default:
                // show all input characters
                mUserInput.setInputType(InputType.TYPE_TEXT_VARIATION_NORMAL|InputType.TYPE_CLASS_TEXT);
                break;
        }

        switch(inputMethod2) {
            case AmpBaseCB.INP_METH_PW_STRICT_MASK:
            case AmpBaseCB.INP_METH_PASSWORD:
                int InpType = mUserInput.getInputType();
                if(InpType == InputType.TYPE_CLASS_NUMBER)
                    mUserInput.setInputType(InpType | InputType.TYPE_NUMBER_VARIATION_PASSWORD);
                else
                    mUserInput.setInputType(InpType | InputType.TYPE_TEXT_VARIATION_PASSWORD);
                break;
        }

        Button button_ok     = findViewById(R.id.btnenter);
        Button button_cancel = findViewById(R.id.btncancel);
        button_ok.setText("OK");
        button_cancel.setText("CANCEL");

        // save all the filters set for this Edit Text
        InputFilter[] newInputFilters = curInputFilters.toArray(new InputFilter[curInputFilters.size()]);
        mUserInput.setFilters(newInputFilters);
    }

    private void setKeyboardAlphaNumeric(ArrayList<InputFilter> curInputFilters) {
        curInputFilters.add(
            new InputFilter() {
                public CharSequence filter(CharSequence src, int start,
                                           int end, Spanned dst, int dstart, int dend) {
                    if (src.length() > 0 && !Character.isLetterOrDigit(src.charAt(0))) {
                        return "";
                    }
                    return null;
                }
            }
        );
    }

    private void prepareAndSendData() {
        if(hasTimedOut) {
            return;
        }
        isUserDone = true;

        int length = 0;
        String input = mUserInput.getText().toString();
        if(input != null && !input.isEmpty()) length = Integer.valueOf(input.length());
        if (length < inputMinimumLength) {
            mUserInput.setError("Input too short");
            return;
        }

        if(mScreenType == SCREEN_SETTINGS_ADD_OPERATOR ||
                mScreenType == SCREEN_SETTINGS_DELETE_OPERATOR ||
                mScreenType == SCREEN_SETTINGS_RESET_OPERATOR_PASSWORD) {
            Log.d(TAG, "TODO: settings operations not yet supported");
            finish();
            return;
        }
        JSONArray dataToSend = new JSONArray();
        JSONObject data = new JSONObject();
        try {
            data.put("id", "dummy");
            data.put("type", 0);
            data.put("value", mUserInput.getText().toString());
            dataToSend.put(data);

            dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
        } catch (JSONException e) {
            e.printStackTrace();
        }
        StatusUtil.notifyCurrentTransaction(dataToSend);
    }

    @Override
    public void onBackPressed() {
        cancelTransaction();
    }

    private void cancelTransaction() {
        DialogManager.onCancelAlert(this,
                /*AmpBaseInterface.GetScrMsg("DIALOGS.SUREWANTTOCANCEL")*/ "Are you sure you want to cancel?");
    }

    public void cancelButtonClicked(View view) {
        cancelTransaction();
    }

    public void okButtonClicked(View view) {
        prepareAndSendData();
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        if(event.getAction() == KeyEvent.ACTION_DOWN) {
            SettingsUtil.triggerBeep(this);
        }
        return super.dispatchKeyEvent(event);
    }

    @Override
    public void onDialogButtonPositiveClick() {
        if(mScreenType == SCREEN_SETTINGS_ADD_OPERATOR ||
                mScreenType == SCREEN_SETTINGS_DELETE_OPERATOR ||
                mScreenType == SCREEN_SETTINGS_RESET_OPERATOR_PASSWORD) {
            Log.d(TAG, "TODO: settings operations not yet supported");
            finish();
            return;
        }
        else {
            isUserDone = true;
            hasTimedOut = true;
            super.onDialogButtonPositiveClick();
        }
    }
}
