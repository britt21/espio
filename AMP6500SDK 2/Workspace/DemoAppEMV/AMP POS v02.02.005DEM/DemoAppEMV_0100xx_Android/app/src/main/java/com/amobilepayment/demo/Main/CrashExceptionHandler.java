package com.amobilepayment.demo.Main;

import android.content.Context;
import android.util.Log;

import com.amobilepayment.demo.Utils.SettingsUtil;

import java.io.PrintWriter;
import java.io.StringWriter;

public final class CrashExceptionHandler implements
        java.lang.Thread.UncaughtExceptionHandler {

    private final static String TAG = CrashExceptionHandler.class.getSimpleName();

    private final Context mContext;

    public CrashExceptionHandler(Context ctx) {
        mContext = ctx;
    }

    public void uncaughtException(Thread thread, Throwable exception) {

        StringWriter stackTrace = new StringWriter();
        exception.printStackTrace(new PrintWriter(stackTrace));

        // TODO: send $stackTrace to our server for analysis
        Log.d(TAG, stackTrace.toString());

        SettingsUtil.restartAppNow(mContext);
    }
}
