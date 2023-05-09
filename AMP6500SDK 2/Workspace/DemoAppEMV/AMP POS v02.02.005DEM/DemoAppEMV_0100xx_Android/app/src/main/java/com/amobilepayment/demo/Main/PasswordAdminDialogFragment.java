package com.amobilepayment.demo.Main;

import android.app.Activity;
import android.app.Dialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
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
import android.widget.EditText;
import android.widget.TextView;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;

public class PasswordAdminDialogFragment extends DialogFragment {

    private final static String TAG = PasswordAdminDialogFragment.class.getSimpleName();

    private UserLoginTask.LoginTaskListener mListener;
    private EditText password_field;
    private Activity parentActivity;
    private boolean enableByPass = false;

    public final static short TYPE_PROCESSOR = 1;
    public final static short TYPE_MERCHANT  = 2;
    private short DIALOG_TYPE = 0;
    private short mDialogType = DIALOG_TYPE;

    public static int ADMIN_PASSWORD_DEFAULT_RETRY = -1;
    public static int MERCHANT_PASSWORD_RETRY = ADMIN_PASSWORD_DEFAULT_RETRY;
    public static int PROCESSOR_PASSWORD_RETRY = ADMIN_PASSWORD_DEFAULT_RETRY;

    public PasswordAdminDialogFragment() {

        if(MERCHANT_PASSWORD_RETRY == ADMIN_PASSWORD_DEFAULT_RETRY) {
            try {
//                String _mMerchantPasswordRetry = AmpBaseInterface
//                        .GetCfgData("TERMINAL.PASSWORDOPTION.PASSINFO.MRCHNT.RETRY");
//                MERCHANT_PASSWORD_RETRY = Integer.parseInt(_mMerchantPasswordRetry);
            } catch (NumberFormatException e) {}
        }
        if(PROCESSOR_PASSWORD_RETRY == ADMIN_PASSWORD_DEFAULT_RETRY) {
            try {
//                String _mProcessorPasswordRetry = AmpBaseInterface
//                        .GetCfgData("TERMINAL.PASSWORDOPTION.PASSINFO.PRCSSR.RETRY");
//                PROCESSOR_PASSWORD_RETRY = Integer.parseInt(_mProcessorPasswordRetry);
            } catch (NumberFormatException e) {}
        }
    }

    public void setDialogType(short type) {
        DIALOG_TYPE = type;
    }

    public void enableByPass(boolean flag) {
        enableByPass = flag;
    }

    public void setListener(UserLoginTask.LoginTaskListener listener) {
        mListener = listener;
    }

    public void setCallingActivity(Activity activity) {
        parentActivity = activity;
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
        View layout = inflater.inflate(R.layout.fragment_password_admin_entry, null);
        password_field = layout.findViewById(R.id.fragment_password_field);
        switch(DIALOG_TYPE) {
            case TYPE_MERCHANT:
//                Log.d(TAG, AmpBaseInterface.GetScrMsg("DIALOGS.MERCHANTPW"));
//                password_field.setHint(AmpBaseInterface.GetScrMsg("DIALOGS.MERCHANTPW"));
                break;
            case TYPE_PROCESSOR:
            default:
//                Log.d(TAG, AmpBaseInterface.GetScrMsg("DIALOGS.PROCESSORPW"));
//                password_field.setHint(AmpBaseInterface.GetScrMsg("DIALOGS.PROCESSORPW"));
                break;
        }

        // save dialog type
        mDialogType = DIALOG_TYPE;

        // reset flag
        DIALOG_TYPE = 0;

        builder.setView(layout)
                .setPositiveButton(("OK"), new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        SettingsUtil.triggerBeep(getContext());

                        doAuthenticate();
                    }
                })
                .setNegativeButton(("CANCEL"), new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        SettingsUtil.triggerBeep(getContext());
                    }
                });
        password_field.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            private boolean handled = false;
            @Override
            public boolean onEditorAction(TextView textView, int actionId, KeyEvent keyEvent) {
                if(actionId == EditorInfo.IME_ACTION_GO) {
                    SettingsUtil.triggerBeep(getContext());

                    handled = true;
                    dismiss();
                    doAuthenticate();
                }
                return handled;
            }
        });
        password_field.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                SettingsUtil.triggerBeep(getActivity());

                // restart timer manually;
                // this has to be done because SessionActivity.onUserActivity is not triggered
                // on keyboard presses
                if(parentActivity != null && parentActivity instanceof SessionActivity) {
                    ((SessionActivity)parentActivity).restartTimeOutHandler();
                }
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });
        return builder.create();
    }

    private void doAuthenticate() {
        if(password_field != null) {
            String password = password_field.getText().toString();
            UserLoginTask mAuthTask =
                    new UserLoginTask(mListener, "admin", password);
            mAuthTask.setUserType(mDialogType);
            mAuthTask.enableByPass(enableByPass);
            mAuthTask.execute(getActivity());
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }
}
