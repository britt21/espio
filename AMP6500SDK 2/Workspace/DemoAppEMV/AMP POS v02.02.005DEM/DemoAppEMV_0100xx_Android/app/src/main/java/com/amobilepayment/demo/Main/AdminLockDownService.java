package com.amobilepayment.demo.Main;

import android.app.IntentService;
import android.content.Intent;

//import static AmpBaseInterface.AmpBaseInterface.GetCfgData;

final class AdminLockDownService extends IntentService {

    public AdminLockDownService() {
        super("AdminLockDownService");
    }

    @Override
    protected void onHandleIntent(Intent workIntent) {

        //String _lockTime = GetCfgData("TERMINAL.PASSWORDOPTION.PASSINFO.LOCKTIME");
        int lockTime = 30;//Integer.parseInt(_lockTime);

        try {
            Thread.sleep(lockTime*1000);  // i.e. 30*1000
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        if(PasswordAdminDialogFragment.MERCHANT_PASSWORD_RETRY == 0)
            PasswordAdminDialogFragment.MERCHANT_PASSWORD_RETRY = -1;
        if(PasswordAdminDialogFragment.PROCESSOR_PASSWORD_RETRY == 0)
            PasswordAdminDialogFragment.PROCESSOR_PASSWORD_RETRY = -1;
    }
}
