package com.amobilepayment.demo.receiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

import com.amobilepayment.demo.Main.LoginActivity;
import com.amobilepayment.demo.R;

public class BootBroadcastReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        boolean flag = prefs.getBoolean(context.getResources().getString(R.string.app_auto_start_set), false);

        // if com.pos.device.sys.SystemManager.writeLauncherPrioAppInfo() has already been
        // executed, no need to do this;
        if(!flag) {
            Intent i = new Intent(context, LoginActivity.class);
            i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(i);
        }
    }
}
