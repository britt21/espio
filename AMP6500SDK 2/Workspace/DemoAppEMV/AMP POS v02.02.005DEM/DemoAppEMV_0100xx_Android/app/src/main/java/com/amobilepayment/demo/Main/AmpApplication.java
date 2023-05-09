package com.amobilepayment.demo.Main;

import android.app.Activity;
import android.app.Application;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.View;
import android.widget.FrameLayout;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.pos.device.SDKManager;
import com.pos.device.SDKManagerCallback;
import com.pos.device.config.DevConfig;
import com.pos.device.ped.KeySystem;
import com.pos.device.ped.KeyType;
import com.pos.device.ped.MACMode;
import com.pos.device.ped.Ped;
import com.pos.device.printer.PrintCanvas;
import com.pos.device.printer.PrintTask;
import com.pos.device.printer.Printer;
import com.pos.device.printer.PrinterCallback;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Array;
import java.util.Arrays;

import AmpBaseInterface.AmpBaseCB;
import AmpBaseInterface.AmpBaseInterface;
import AmpEmvL2Android.AmpEmvCB;
import AmpEmvL2Android.AmpEmvL2IF;


public class AmpApplication extends Application implements Application.ActivityLifecycleCallbacks {
    private static final String TAG = AmpApplication.class.getSimpleName();

    public static boolean isSDKManagerInitDone = false;

    private Activity activity = null;

    static {
        //System.loadLibrary("sqlite3");
        System.loadLibrary("pos");
        System.loadLibrary("AMPEMVL2");
        System.loadLibrary("AMPCmpnt");
        System.loadLibrary("AmpEmvL2AndroidIF");
    }

    @Override
    public void onCreate() {
        super.onCreate();

        File sdcardBaseDir = new File("/sdcard/AMPBaseApp");
        File sdcardAgnosDir = new File("/sdcard/AGNOS");

        if(sdcardBaseDir.isDirectory())
            sdcardBaseDir.delete();

        if(sdcardAgnosDir.isDirectory())
            sdcardAgnosDir.delete();

        // Prepare Directories for AMPBaseApp Configuration and Agnos Files
        String ApplDir = getApplicationContext().getFilesDir().toString();
        Log.d(TAG, "Application Directory = " + ApplDir);

        File BaseDir = new File(ApplDir + "/AMPBaseApp");
        File AgnosDir = new File(ApplDir + "/AGNOS");

        BaseDir.mkdirs();
        AgnosDir.mkdirs();

        String[] cmdAMPBaseApp  = {"chmod", "-R", "770", ApplDir + "/AMPBaseApp/"};
        String[] cmdAgnos       = {"chmod", "-R", "770", ApplDir + "/AGNOS/"};
        ProcessBuilder bldrAMPBaseApp = new ProcessBuilder(cmdAMPBaseApp);
        ProcessBuilder bldrAgnos = new ProcessBuilder(cmdAgnos);
        try {
            bldrAMPBaseApp.start();
            bldrAgnos.start();
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            bldrAMPBaseApp.start();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Initialize AMPBaseApp - Load InternalCfg.xml
        AmpBaseInterface.Initialize(AmpBaseCB.baseCBIF, amp.sdk.lib.AmpCmpnt.AmpCmpntCBIF,AmpApplication.this);


        // TODO: Check if SharedPreferences has the same Lang code as the InternalCfg.xml.
        //       If they are different, we need to sync the two.
        //       This is going to be useful for cases wherein we can modify the InternalCfg.xml
        //       from within the SDCard / Appdata.
        //       In the meantime, to sync them, just go to Settings page then
        //       update the Language.
        syncSettings();

        // Copy and Setup Agnos EMV Files and Configuration
        AmpEmvL2Android.AmpEmvL2IF.SetUpAmpEmvL2Files(getApplicationContext());

        try {
            bldrAMPBaseApp.start();
            bldrAgnos.start();
        } catch (IOException e) {
            e.printStackTrace();
        }

        String AgnosIniPath = ApplDir + "/AMPBaseApp/";
        String AgnosConfigPath = ApplDir + "/AGNOS/";
        String AgnosLibPath = "";

        Log.d(TAG, "AgnosIniPath: " + AgnosIniPath);
        Log.d(TAG, "AgnosConfigPath: " + AgnosConfigPath);

        // Initialize AMPEMVL2 Library
        AmpEmvL2IF.InitAmpEmvL2(AmpEmvCB.listener, AgnosIniPath, AgnosConfigPath, AgnosLibPath);

        SDKManager.init(this, new SDKManagerCallback() {
            // NPos SDKManager has finished its initialization process
            @Override
            public void onFinish() {

                // record this onFinish() event so other important app initializations can follow thru
                // such as disabling Home and RecentApp buttons
                isSDKManagerInitDone = true;

//                byte[] App_Key = {(byte)0xB6, (byte)0xF9, (byte)0xDD, (byte)0x1E,
//                        (byte)0xF3, (byte)0xE4, (byte)0x90, (byte)0xE5,
//                        (byte)0xDF, (byte)0x6D, (byte)0x61, (byte)0xFE,
//                        (byte)0x6A, (byte)0x44, (byte)0xF1, (byte)0x51};
//
//                byte[] App_Ksn = {(byte)0xFF, (byte)0xFF, (byte)0x5B, (byte)0x09,
//                        (byte)0x99, (byte)0x00, (byte)0x00, (byte)0x20,
//                        (byte)0x00, (byte)0x00};
//
//                int iRetVal = Ped.getInstance().createDukptKey(0, App_Key, App_Ksn);
//                Log.d(TAG, "Inject DUKPT Key = " + iRetVal);
//
//                iRetVal = Ped.getInstance().injectKey(KeySystem.FIXED_DES, KeyType.KEY_TYPE_FIXEAK, 1, App_Key);
//                Log.d(TAG, "Inject FixEAK Key = " + iRetVal);

                Log.d(TAG, "FW Version: " + DevConfig.getFirmwareVersion());
                Log.d(TAG, "SP Version: " + DevConfig.getSPVersion());
                Log.d(TAG, "PCI FW Version: " + DevConfig.getPCIFirmwareVersion());

                SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(getApplicationContext());

                boolean flag = prefs.getBoolean(getResources().getString(R.string.app_auto_start_set), false);

                // we only set this once;
                // setting the app_auto_start_set to true is also important so we can disable the
                // effect of BootBroadcastReceiver's onreceive action;
                if(!flag) {
                    SharedPreferences.Editor editor = prefs.edit();
                    editor.putBoolean(getResources().getString(R.string.app_auto_start_set), true);
                    editor.apply();

                    com.pos.device.sys.SystemManager
                            .writeLauncherPrioAppInfo("com.amobilepayment.demo",
                                    "com.amobilepayment.demo.Main.LoginActivity");
                }
            }
        });


        /**
         * SAMPLE CODE FOR PRINTING
         *

        int printerWidth = 383;
        int y = 0;
        int textsize = 17;
        String text = null;

        // Initialize objects needed for printing
        Paint paint = new Paint();
        PrintCanvas printCanvas = new PrintCanvas();
        Printer printer = Printer.getInstance();

        // Check if printer is available
        if(printer.getStatus() != Printer.PRINTER_OK)
        {
            Log.d("PRINTER", "Error="+printer.getStatus());
            return;
        }

        // Place items in the canvas

        // Left alignment
        text = "Sample text left aligned";
        paint.setTypeface(Typeface.defaultFromStyle(Typeface.NORMAL));
        paint.setTextSize(textsize);
        y += textsize;

        printCanvas.setX(0);
        printCanvas.setY(y);
        printCanvas.drawText(text, paint);

        // Center alignment
        textsize = 30;
        text = "Sample text center aligned";
        paint.setTypeface(Typeface.defaultFromStyle(Typeface.BOLD));
        paint.setTextSize(textsize);
        y += textsize;

        printCanvas.setX((int)((printerWidth - paint.measureText(text))/2));
        printCanvas.setY(y);
        printCanvas.drawText(text, paint);
        y += 17; // add offset if font is bold

        // Right alignment
        textsize = 17;
        text = "Sample text right aligned";
        paint.setTypeface(Typeface.defaultFromStyle(Typeface.NORMAL));
        paint.setTextSize(textsize);
        y += textsize;

        printCanvas.setX((int)(printerWidth - paint.measureText(text)));
        printCanvas.setY(y);
        printCanvas.drawText(text, paint);

        // Draw image
        Bitmap image = null ;

        try {
            InputStream is = getApplicationContext().getAssets().open("sample.png");
            image = BitmapFactory.decodeStream(is);
            is.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        printCanvas.drawBitmap(image, paint);

        // Make a printtask and assign a canvas
        PrintTask printTask = new PrintTask();
        printTask.setPrintCanvas(printCanvas);

        // Call print function
        printer.startPrint(printTask, new PrinterCallback() {
            @Override
            public void onResult(int i, PrintTask printTask) {
                Log.d(TAG,"startPrint result="+i);
            }
        });

        **/

        registerActivityLifecycleCallbacks(this);
    }

    // Sync SharedPreferences with values from InternalCfg.xml
    private void syncSettings () {
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        SharedPreferences.Editor editor = prefs.edit();

        // copy demo mode setting
        boolean newValueDemoMode = true;
        String demoMode = "Y";
        if("N".equals(demoMode)) newValueDemoMode = false;
        editor.putBoolean(getResources().getString(R.string.pref_gen_demo_key), newValueDemoMode);

        // save settings
        editor.commit();
    }

    @Override
    public void onActivityCreated(Activity activity, Bundle bundle) {
    }

    @Override
    public void onActivityStarted(Activity activity) {
        this.activity = activity;

        View _demoModeLayout = activity.findViewById(R.id.demo_mode_layout);
        if(SettingsUtil.isDemoMode(activity) && _demoModeLayout == null) {
            FrameLayout rootLayout = activity.findViewById(android.R.id.content);
            View.inflate(activity, R.layout.demo_mode, rootLayout);
        }
        else if(!SettingsUtil.isDemoMode(activity) && _demoModeLayout != null) {
            FrameLayout rootLayout = activity.findViewById(android.R.id.content);
            rootLayout.removeViewAt(rootLayout.getChildCount()-1);
        }
    }

    @Override
    public void onActivityResumed(Activity activity) {
    }

    @Override
    public void onActivityPaused(Activity activity) {
    }

    @Override
    public void onActivityStopped(Activity activity) {
        if(this.activity == activity) {
            this.activity = null;
        }
    }

    @Override
    public void onActivitySaveInstanceState(Activity activity, Bundle bundle) {
    }

    @Override
    public void onActivityDestroyed(Activity activity) {
    }
}
