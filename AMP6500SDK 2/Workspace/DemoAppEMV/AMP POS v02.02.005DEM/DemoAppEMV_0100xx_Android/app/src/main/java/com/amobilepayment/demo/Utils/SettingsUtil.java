package com.amobilepayment.demo.Utils;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.content.res.Resources;
import android.graphics.PixelFormat;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Build;
import android.os.Handler;
import android.os.Looper;
import android.preference.PreferenceManager;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.AppCompatActivity;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.Toast;

import com.amobilepayment.demo.Main.AmpApplication;
import com.amobilepayment.demo.Main.LoginActivity;
import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.Main.PasswordAdminDialogFragment;
import com.amobilepayment.demo.Main.PasswordAdminSetDialogFragment;
import com.pos.device.SDKException;
import com.pos.device.beeper.Beeper;

import java.lang.ref.WeakReference;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Locale;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.R;

import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

public class SettingsUtil {

    public final static String TAG = SettingsUtil.class.getSimpleName();

    public static void triggerBeep(Context context) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);

        // R.xml.pref_general/pref_gen_beep_key's default value is TRUE
        boolean flag = prefs.getBoolean(context.getString(R.string.pref_gen_beep_key), true);

        if(flag) {
            Beeper beeper = Beeper.getInstance();
            try {
                beeper.beep();
            } catch (SDKException e) {
                e.printStackTrace();
            }
        }
    }

    // Beep Definitions for Display prompts
    public final static int BEEP_NONE = 0;
    public final static int BEEP_INFO = 1;
    public final static int BEEP_WARN = 2;
    public final static int BEEP_ERROR = 3;
    public final static int BEEP_LOOP = 4;

    public static void forceTriggerBeepError() {
        Beeper beeper = Beeper.getInstance();
        int DEFAULT_FREQUENCY = 1600;
        int DEFAULT_DURATION = 35;

        try {
            beeper.beep(DEFAULT_FREQUENCY, DEFAULT_DURATION*10);
        } catch (SDKException e) {
            e.printStackTrace();
        }
    }

    public static void triggerBeepType(Context context, int type) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        boolean flag = prefs.getBoolean(context.getString(R.string.pref_gen_beep_key), true);

        if(!flag) return;

        // values from com.pos.device.beeper.Beeper
        int DEFAULT_FREQUENCY = 1600;
        int DEFAULT_DURATION = 35;

        Beeper beeper = Beeper.getInstance();

        switch(type) {
            case BEEP_NONE:
                break;
            case BEEP_INFO:
                try {
                    beeper.beep();
                } catch (SDKException e) {
                    e.printStackTrace();
                }
                break;
            case BEEP_WARN:
            case BEEP_ERROR:
                try {
                    beeper.beep(DEFAULT_FREQUENCY, DEFAULT_DURATION*10);
                } catch (SDKException e) {
                    e.printStackTrace();
                }
                break;
            case BEEP_LOOP:
                // TODO: what to do
                Log.d(TAG, "TODO: beep loop");
                break;
        }
    }

    public static boolean isDemoMode(Context context) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        boolean flag = prefs.getBoolean(context.getString(R.string.pref_gen_demo_key), false);

        return flag;
    }

    // force the activity to use the locale set in our settings page
    // note that Language setting is from InternalCfg.xml
    public static void updateActivityLang(Context context) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        String langCode = prefs.getString(context.getString(R.string.pref_gen_language_key), "");

        Resources resources = context.getResources();
        Configuration configuration = resources.getConfiguration();
        DisplayMetrics displayMetrics = resources.getDisplayMetrics();
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            configuration.setLocale(new Locale(langCode));
        }
        else {
            configuration.locale = new Locale(langCode);
        }
        resources.updateConfiguration(configuration,displayMetrics);
    }

    public static Locale getCurrentLocale(Context context) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        String langCode = prefs.getString(context.getString(R.string.pref_gen_language_key), "");

        return new Locale(langCode);
    }

    public static HashMap<String,String> getLanguageHashMap(Context context) {
        HashMap<String,String> languageHashMap;
        String[] values = context.getResources().getStringArray(R.array.world_lang_names);
        String[] keys = context.getResources().getStringArray(R.array.world_lang_codes);
        languageHashMap = new HashMap<>();
        for (int i = 0; i < Math.min(keys.length, values.length); ++i) {
            languageHashMap.put(keys[i], values[i]);
        }
        return languageHashMap;
    }

    public static HashMap<String,String> getOperatorCredentialsFromConfig() {
        DecimalFormat decimalFormatter = new DecimalFormat();
        decimalFormatter.applyPattern("0000");

        String splitter = ",";

        HashMap<String,String> operatorHashMap = new HashMap<>();
        int count = 1;//AmpBaseInterface.GetCfgInt("TERMINAL.OPERATOR.COUNT");

        StringBuilder sbID = new StringBuilder();
        StringBuilder sbPwd = new StringBuilder();

        for(int i=1; i <= count; i++) {
            String node = decimalFormatter.format(i);
//            String opId = AmpBaseInterface.GetCfgData("TERMINAL.OPERATOR._" + node + ".OPERATORID");
//            String pwd = AmpBaseInterface.GetCfgData("TERMINAL.OPERATOR._" + node + ".PASSWORD");
//
//            sbID.append(opId);
//            sbPwd.append(pwd);

            if(i<count)
            sbID.append(splitter);
            sbPwd.append(splitter);
        }

        String[] usernames = sbID.toString().split(splitter);
        String[] passwords = sbPwd.toString().split(splitter);

        for (int i = 0; i < Math.min(usernames.length, passwords.length); ++i) {
            operatorHashMap.put(usernames[i], passwords[i]);
        }

        return operatorHashMap;
    }

    public static boolean operatorAlreadySignedIn(Context context) {
        boolean flag = false;
//        String operatorID = AmpBaseInterface.GetCfgData("TERMINAL.OPERATOR.SIGNED_IN.OPERATORID");
//        if(operatorID != null && !operatorID.isEmpty()) {
//            String signedIn = AmpBaseInterface.GetCfgData("TERMINAL.OPERATOR.SIGNED_IN.PW_ENTERED");
//            if("Y".equals(signedIn)) flag = true;
//        }
        return flag;
    }

    /**
     * BaseApp can be used as stand alone or can be called from another client app to complete a
     * transaction. With this checker, we can determine how this app was started.
     * @return true if this app was started as standalone, false if started via Intent from a client app
     */
    public static boolean isStandAlone(Context context) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        boolean flag = prefs.getBoolean(context.getString(R.string.app_started_standalone), false);
        return flag;
    }

    public static void setAsStandAlone(Context context, boolean flag) {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(context);
        SharedPreferences.Editor editor = prefs.edit();
        editor.putBoolean(context.getString(R.string.app_started_standalone), flag);
        editor.commit();
    }

    public static String getTerminalTime() {
        Date date = Calendar.getInstance().getTime();
        SimpleDateFormat df = new SimpleDateFormat("HH:mm", Locale.US);
        return df.format(date);
    }

    public static String getTerminalDate() {
        Date date = Calendar.getInstance().getTime();
        SimpleDateFormat df = new SimpleDateFormat("MMMM dd, yyyy", Locale.US);
        return df.format(date);
    }

    public static void setTerminalTime(Context ctx, int h, int m) {

        // format date and time as yyyyMMddHHmmss

        String HH = String.valueOf(h);
        if(HH.length() == 1) {
            HH = "0" + HH;
        }

        String mm = String.valueOf(m);
        if(mm.length() == 1) {
            mm = "0" + mm;
        }

        // get current date
        final Calendar c = Calendar.getInstance();
        int year = c.get(Calendar.YEAR);
        int month = c.get(Calendar.MONTH);
        int day = c.get(Calendar.DAY_OF_MONTH);

        String yyyy = String.valueOf(year);
        // plus one because 0=January
        String MM = String.valueOf(month+1);
        String dd = String.valueOf(day);

        // format month
        if(MM.length() == 1) {
            MM = "0" + MM;
        }

        // format day
        if(dd.length() == 1) {
            dd = "0" + dd;
        }

        try {
            com.pos.device.rtc.RealTimeClock.set(yyyy+MM+dd+HH+mm+"00");
        } catch (SDKException e) {
            e.printStackTrace();
        }

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(ctx);
        SharedPreferences.Editor pref = prefs.edit();
        pref.putString(ctx.getResources().getString(R.string.pref_gen_man_time_key), HH+mm);
        pref.apply();
    }

    public static void setTerminalDate(Context ctx, int y, int m, int d) {

        // format date and time as yyyyMMddHHmmss

        String yyyy = String.valueOf(y);

        // Format month
        // We don't plus one here because we assume that the caller already fixed the 0=January.
        // Unlike in setTerminalDate(), we need to fix it from inside the function
        String MM = String.valueOf(m);
        if(MM.length() == 1) {
            MM = "0" + MM;
        }

        String dd = String.valueOf(d);
        if(dd.length() == 1) {
            dd = "0" + dd;
        }

        // get current time
        final Calendar c = Calendar.getInstance();
        int hour = c.get(Calendar.HOUR_OF_DAY);
        int minute = c.get(Calendar.MINUTE);

        String HH = String.valueOf(hour);
        if(HH.length() == 1) {
            HH = "0" + HH;
        }

        String mm = String.valueOf(minute);
        if(mm.length() == 1) {
            mm = "0" + mm;
        }

        try {
            com.pos.device.rtc.RealTimeClock.set(yyyy+MM+dd+HH+mm+"00");
        } catch (SDKException e) {
            e.printStackTrace();
        }

        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(ctx);
        SharedPreferences.Editor pref = prefs.edit();
        pref.putString(ctx.getResources().getString(R.string.pref_gen_man_date_key), yyyy+MM+dd);
        pref.apply();
    }

    private static WeakReference<View> weakView;

    // check for the number of remaining retries;
    // true, wait for TERMINAL.PASSWORDOPTION.PASSINFO.LOCKTIME to finish
    public static boolean isAdminPasswordMaxRetry(Context context, int type) {
        boolean flag = false;
        if(type == PasswordAdminDialogFragment.TYPE_MERCHANT) {
            if (PasswordAdminDialogFragment.MERCHANT_PASSWORD_RETRY !=
                    PasswordAdminDialogFragment.ADMIN_PASSWORD_DEFAULT_RETRY) {
                if(PasswordAdminDialogFragment.MERCHANT_PASSWORD_RETRY == 0) {
                    Toast.makeText(context,
                            "Merchant is locked. Please try again later.",
                            Toast.LENGTH_LONG).show();
                    flag = true;
                }
            }
        }
        if(type == PasswordAdminDialogFragment.TYPE_PROCESSOR) {
            if (PasswordAdminDialogFragment.PROCESSOR_PASSWORD_RETRY !=
                    PasswordAdminDialogFragment.ADMIN_PASSWORD_DEFAULT_RETRY) {
                if(PasswordAdminDialogFragment.PROCESSOR_PASSWORD_RETRY == 0) {
                    Toast.makeText(context,
                            "Processor is locked. Please try again later.",
                            Toast.LENGTH_LONG).show();
                    flag = true;
                }
            }
        }
        return flag;
    }

    public static boolean isMerchantPasswordDefault() {
        boolean flag = false;
//        String pwd = AmpBaseInterface.GetCfgData("TERMINAL.PASSWORDOPTION.ADMINPASS.MERCHANT");
//        if(PasswordAdminSetDialogFragment.MERCHANT_DEFAULT_PWD.equals(pwd)) {
//            flag = true;
//        }

        return flag;
    }

    public static boolean isProcessorPasswordDefault() {
        boolean flag = false;
//        String pwd = AmpBaseInterface.GetCfgData("TERMINAL.PASSWORDOPTION.ADMINPASS.PROCESSOR");
//        if(PasswordAdminSetDialogFragment.PROCESSOR_DEFAULT_PWD.equals(pwd)) {
//            flag = true;
//        }

        return flag;
    }

    public static void showMerchantSetPasswordDialog(
                        PasswordAdminSetDialogFragment.OnAdminPasswordUpdateListener listener,
                        AppCompatActivity activity,
                        MenuActivity.USER_TYPE userType) {
        PasswordAdminSetDialogFragment dialog = new PasswordAdminSetDialogFragment();
        dialog.setListener(listener);
        dialog.setCallingActivity(activity);
        dialog.setUserType(userType);
        FragmentManager fm = activity.getSupportFragmentManager();
        dialog.show(fm, "PasswordAdminSetDialogFragment");
    }

    public static void restartAppNow(Context context) {
        Intent intent = new Intent(context, LoginActivity.class);
        intent.addFlags(FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        context.startActivity(intent);
        if (context instanceof Activity) {
            ((Activity) context).finish();
        }

        Runtime.getRuntime().exit(0);
    }
}
