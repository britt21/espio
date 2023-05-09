package com.amobilepayment.demo.Main;

import android.app.Activity;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.design.widget.TextInputLayout;
import android.support.v4.app.DialogFragment;
import android.support.v7.app.AlertDialog;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import AmpBaseInterface.AmpBaseInterface;

public class PasswordAdminSetDialogFragment extends DialogFragment {

    private final static String TAG = PasswordAdminSetDialogFragment.class.getSimpleName();

    private OnAdminPasswordUpdateListener mListener;
    private EditText new_password_field;
    private EditText new_password_again_field;
    private Activity parentActivity;
    private MenuActivity.USER_TYPE mUserType = null;

    final int INPUT_MIN_LENGTH = 8;
    public final static String MERCHANT_DEFAULT_PWD = "56789012";
    public final static String PROCESSOR_DEFAULT_PWD = "14725836";

    public interface OnAdminPasswordUpdateListener {
        void onUpdateCompleted();
    }

    public PasswordAdminSetDialogFragment() {
        // Required empty public constructor
    }

    public void setListener(OnAdminPasswordUpdateListener listener) {
        mListener = listener;
    }

    public void setCallingActivity(Activity activity) {
        parentActivity = activity;
    }

    public void setUserType(MenuActivity.USER_TYPE ut) {
        mUserType = ut;
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        getDialog().getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_VISIBLE);
        return super.onCreateView(inflater, container, savedInstanceState);
    }

    @NonNull
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        LayoutInflater inflater = getActivity().getLayoutInflater();
        View layout = inflater.inflate(R.layout.fragment_admin_password_set, null);

//        TextView textView = layout.findViewById(R.id.title);
//        textView.setText(AmpBaseInterface.GetScrMsg("PASSWORDCHANGEREQUIRED"));
//
//        TextInputLayout til1 = layout.findViewById(R.id.til_new_password);
//        TextInputLayout til2 = layout.findViewById(R.id.til_new_password_again);
//        til1.setHint(AmpBaseInterface.GetScrMsg("ENTERPASSWORD"));
//        til2.setHint(AmpBaseInterface.GetScrMsg("REENTERPASSWORD"));
//
//        new_password_field = layout.findViewById(R.id.new_password);
//        new_password_again_field = layout.findViewById(R.id.new_password_again);
//
//        builder.setView(layout)
//                .setPositiveButton(AmpBaseInterface.GetScrMsg("OK"), new DialogInterface.OnClickListener() {
//                    public void onClick(DialogInterface dialog, int id) {
//                        SettingsUtil.triggerBeep(getContext());
//                    }
//                })
//                .setNegativeButton(AmpBaseInterface.GetScrMsg("CANCEL"), new DialogInterface.OnClickListener() {
//                    public void onClick(DialogInterface dialog, int id) {
//                        SettingsUtil.triggerBeep(getContext());
//                    }
//                });

        setupListeners();

        return builder.create();
    }

    @Override
    public void onResume() {
        super.onResume();

        final AlertDialog dialog = (AlertDialog) getDialog();

        // This will override the default behavior of Dialog to close on click.
        // Let doActionGo() handle the closing of Dialog.
        Button positiveButton = dialog.getButton(Dialog.BUTTON_POSITIVE);
        positiveButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v) {
                doActionGo();
            }
        });
    }

    private void doActionGo() {
        if(validateInput()) {
            dismiss();
            updateAdminPassword();

            if(mListener != null) mListener.onUpdateCompleted();
        }
    }

    private boolean validateInput() {

        String input_new = new_password_field.getText().toString();
        String input_again = new_password_again_field.getText().toString();

        // if empty
        if(input_new.isEmpty()) {
            showError((short)1);
            return false;
        }

        // if does not contain valid characters
        String _pattern_letters = "[A-Za-z]";
        String _pattern_numbers = "[0-9]";
        Pattern pattern_letters = Pattern.compile(_pattern_letters);
        Pattern pattern_numbers = Pattern.compile(_pattern_numbers);
        Matcher matcher_letters = pattern_letters.matcher(input_new);
        Matcher matcher_numbers = pattern_numbers.matcher(input_again);
        if(!matcher_letters.find() || !matcher_numbers.find()) {
            Log.d(TAG, input_new);
            showError((short)1);
            return false;
        }

        // if input is too short
        if(input_new.length() < INPUT_MIN_LENGTH) {
            showError((short)2);
            return false;
        }

        // if not equals
        if(!input_new.equals(input_again)) {
            showError((short)3);
            return false;
        }

        return true;
    }

    private void showError(short type) {
        switch (type) {
//            case 1:
//                // Password should contain combination of numbers and letters
//                String passwordShouldContain = AmpBaseInterface.GetScrMsg("PASSWORDCONTAIN");
//                String lettersAndNumbers = AmpBaseInterface.GetScrMsg("LETTERSANDNUMBERS");
//                new_password_again_field.setError(passwordShouldContain+" "+lettersAndNumbers);
//                break;
//            case 2:
//                // Input too short
//                new_password_again_field.setError(AmpBaseInterface.GetScrMsg("USERINPUTENTRYACTIVITY.INPUTTOOSHORT"));
//                break;
//            case 3:
//                // Password not matched!
//                new_password_again_field.setError(AmpBaseInterface.GetScrMsg("PASSWORDNOTMATCH"));
//                break;
        }
    }

    private void onTextChangedAction() {
        SettingsUtil.triggerBeep(getActivity());

        // restart timer manually;
        // this has to be done because SessionActivity.onUserActivity is not triggered
        // on keyboard presses
        if(parentActivity != null && parentActivity instanceof SessionActivity) {
            ((SessionActivity)parentActivity).restartTimeOutHandler();
        }
    }

    private void updateAdminPassword() {
        String new_pwd = new_password_field.getText().toString();
//        if(mUserType == MenuActivity.USER_TYPE.MERCHANT) {
//            AmpBaseInterface.PutCfgData("TERMINAL.PASSWORDOPTION.ADMINPASS.MERCHANT", new_pwd);
//            AmpBaseInterface.PutCfgData("TERMINAL.PASSWORDOPTION.PASSINFO.MRCHNT.INIT", "N");
//        }
//        else {
//            AmpBaseInterface.PutCfgData("TERMINAL.PASSWORDOPTION.ADMINPASS.PROCESSOR", new_pwd);
//            AmpBaseInterface.PutCfgData("TERMINAL.PASSWORDOPTION.PASSINFO.PRCSSR.INIT", "N");
//        }
    }

    private void setupListeners() {
        new_password_again_field.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int actionId, KeyEvent keyEvent) {
                if(actionId == EditorInfo.IME_ACTION_GO) {
                    doActionGo();
                }
                return true;
            }
        });
        new_password_field.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                onTextChangedAction();
            }

            @Override
            public void afterTextChanged(Editable editable) {}
        });
        new_password_again_field.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                onTextChangedAction();
            }

            @Override
            public void afterTextChanged(Editable editable) {}
        });
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }
}
