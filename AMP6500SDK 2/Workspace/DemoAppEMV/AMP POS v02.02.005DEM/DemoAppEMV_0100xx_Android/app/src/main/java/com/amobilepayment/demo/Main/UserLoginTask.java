package com.amobilepayment.demo.Main;

import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;

import java.util.HashMap;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.Utils.SettingsUtil;

/**
 * Represents an asynchronous login task used to authenticate
 * the user.
 */
public class UserLoginTask extends AsyncTask<Context, Void, String> {

    private final String TAG = UserLoginTask.class.getSimpleName();

    public interface LoginTaskListener {
        void onLoginTaskStarted();
        void onLoginTaskCompleted();
        void onLoginTaskCancelled();
        void onLoginTaskIncorrect();
    }

    private Context mContext;

    private final String mEmail;
    private final String mPassword;
    private LoginTaskListener mListener;
    private boolean mEnableByPass;

    // specific to PasswordAdminDialogFragment
    private int mUserType = 0;

    UserLoginTask(LoginTaskListener listener, String email, String password) {
        mListener = listener;
        mEmail = email;
        mPassword = password;
    }

    // specific to PasswordAdminDialogFragment
    public void setUserType(int ut) {
        mUserType = ut;
    }

    public void enableByPass(boolean flag) {
        mEnableByPass = flag;
    }

    @Override
    protected void onPreExecute() {
        super.onPreExecute();
        mListener.onLoginTaskStarted();
    }

    @Override
    protected String doInBackground(Context... context) {

        mContext = context[0];

        if(SettingsUtil.isDemoMode(context[0])) {
            return mEmail;
        }

        // specific to PasswordAdminDialogFragment
        if(mUserType != 0) {
            switch(mUserType) {
                case PasswordAdminDialogFragment.TYPE_MERCHANT:
                    if(doMerchantLogin()) return mEmail;
                    break;
                case PasswordAdminDialogFragment.TYPE_PROCESSOR:
                    if(doProcessorLogin()) return mEmail;
                    break;
            }
        }
        // else do Operator credentials lookup
        else {
            if(doOperatorLogin()) return mEmail;
        }

        return null;
    }

    private boolean doOperatorLogin() {
        HashMap<String,String> credentials = SettingsUtil.getOperatorCredentialsFromConfig();
        String pwd = credentials.get(mEmail);
        if(pwd != null && !pwd.isEmpty() && pwd.equals(mPassword)) {
            // save operatorID into InternalCfg.xml
//            AmpBaseInterface.PutCfgData("TERMINAL.OPERATOR.SIGNED_IN.OPERATORID", mEmail);
//            AmpBaseInterface.PutTMSData("TERMINAL.OPERATOR.SIGNED_IN.OPERATORID", mEmail);
//            AmpBaseInterface.PutCfgData("TERMINAL.OPERATOR.SIGNED_IN.PW_ENTERED", "Y");
//            AmpBaseInterface.PutTMSData("TERMINAL.OPERATOR.SIGNED_IN.PW_ENTERED", "Y");

            return true;
        }
        return false;
    }

    private boolean doMerchantLogin() {
//        String merchantPassword = AmpBaseInterface.GetCfgData("TERMINAL.PASSWORDOPTION.ADMINPASS.MERCHANT");
//        if(merchantPassword != null) {
//            if(merchantPassword.equals(mPassword)) {
//
//                // reset for every correct password
//                PasswordAdminDialogFragment.MERCHANT_PASSWORD_RETRY =
//                    PasswordAdminDialogFragment.ADMIN_PASSWORD_DEFAULT_RETRY;
//
//                return true;
//            }
//        }

        // maybe user is doing a password override? check admin passwords
        if(mEnableByPass) {
            // is overriding allowed?
//            String overRide = AmpBaseInterface.GetCfgData("TERMINAL.PASSWORDOPTION.PWOVERRIDE");
//            if("Y".equals(overRide))
//                if (doProcessorLogin()) return true;
        }

        PasswordAdminDialogFragment.MERCHANT_PASSWORD_RETRY--;

        if(PasswordAdminDialogFragment.MERCHANT_PASSWORD_RETRY == 0)
            enableAdminLockDown();

        return false;
    }

    private boolean doProcessorLogin() {
//        String processorPassword = AmpBaseInterface.GetCfgData("TERMINAL.PASSWORDOPTION.ADMINPASS.PROCESSOR");
//        if(processorPassword != null) {
//            if(processorPassword.equals(mPassword)) {
//
//                // reset for every correct password
//                PasswordAdminDialogFragment.PROCESSOR_PASSWORD_RETRY =
//                        PasswordAdminDialogFragment.ADMIN_PASSWORD_DEFAULT_RETRY;
//
//                return true;
//            }
//        }

        PasswordAdminDialogFragment.PROCESSOR_PASSWORD_RETRY--;

        if(PasswordAdminDialogFragment.MERCHANT_PASSWORD_RETRY == 0)
            enableAdminLockDown();

        return false;
    }

    private void enableAdminLockDown() {
        Intent intent = new Intent(mContext, AdminLockDownService.class);
        mContext.startService(intent);
    }

    @Override
    protected void onPostExecute(final String success) {
        if (success != null) {
            mListener.onLoginTaskCompleted();
        } else {
            mListener.onLoginTaskIncorrect();
        }
    }

    @Override
    protected void onCancelled() {
        mListener.onLoginTaskCancelled();
    }
}
