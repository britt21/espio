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

public class PasswordOperatorDialogFragment extends DialogFragment {

    private final static String TAG = PasswordOperatorDialogFragment.class.getSimpleName();

    private UserLoginTask.LoginTaskListener mListener;
    private EditText password_field;
    private EditText username_field;
    private Activity parentActivity;

    public PasswordOperatorDialogFragment() {
        // Required empty public constructor
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
        View layout = inflater.inflate(R.layout.fragment_password_operator_entry, null);
        password_field = layout.findViewById(R.id.fragment_password_field);
        username_field = layout.findViewById(R.id.fragment_username_field);

        // set the current operator id user
        String signedInOperatorID = "0001";//AmpBaseInterface.GetCfgData("TERMINAL.OPERATOR.SIGNED_IN.OPERATORID");
        if(signedInOperatorID != null && !signedInOperatorID.isEmpty()) {
            username_field.setText(signedInOperatorID);
            password_field.requestFocus();
        }
        // if no available user, ask for input from user
        else {
            username_field.setEnabled(true);
            username_field.requestFocus();
        }

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
        username_field.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
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
            // TODO: get the operator id from InternalCfg.xml
            UserLoginTask mAuthTask =
                    new UserLoginTask(mListener, username_field.getText().toString(), password);
            mAuthTask.execute(getActivity());
        }
    }

    @Override
    public void onDetach() {
        super.onDetach();
        mListener = null;
    }
}
