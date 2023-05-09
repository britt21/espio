package AmpEmvL2Android;

import android.annotation.SuppressLint;
import android.content.Context;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import com.amobilepayment.demo.Utils.Defines;

/**
 * Created by Alainsky on 9/23/2017.
 */

public class AmpEmvL2IF {

    //To get track data for magstripe
    private static byte[] Track1;
    private static byte[] Track2;
    private static byte[] Track3;

    private static byte[] TagValue;

    public native static void InitAmpEmvL2(AmpEmvCBIF obj, String AgnosInitPath, String AgnosConfigPath, String AgnosLibPath);
    public native static int AmpEmvCardEntryPolling(long TimeOut);
    public native static void AmpEmvSetTagCollection(byte[] TagList, int TagListLen);
    public native static byte[] AmpEmvGetTagColData();
    public native static byte[] AmpEmvGetTagData(long TagName);
    public native static byte[] AmpEmvGetAIDInfo();
    public native static byte[] AmpEmvGetTransCategoryCode();

    public native static int AmpEmvInitTrans(int AgnosTransType);
    public native static int AmpEmvInitiateFlow();
    public native static int AmpEmvCompletion();

    public native static int AmpEmvCtlsInitiateFlow();
    public native static int AmpEmvCtlsCompletion();

    public native static int AmpEmvReadMagstripe();

    public native static int AmpCloseDevices();

    @SuppressLint("SdCardPath")
    public static void  SetUpAmpEmvL2Files(Context myContext){

        copyApkFromAssets(myContext, "agnos.ini",       "/AMPBaseApp/agnos.ini",        false, true);
        copyApkFromAssets(myContext, "lang.ini",        "/AMPBaseApp/lang.ini",         false, true);
        copyApkFromAssets(myContext, "QuickChip.cfg",   "/AMPBaseApp/QuickChip.cfg",    false, true);
        copyApkFromAssets(myContext, "USDebit.cfg",     "/AMPBaseApp/USDebit.cfg",      false, true);
        copyApkFromAssets(myContext, "CAKeys.xml",      "/AMPBaseApp/CAKeys.xml",       false,true);

        copyApkFromAssets(myContext, "CAKeys",          "/AGNOS/CAKeys",           false, true);
        copyApkFromAssets(myContext, "ENTRY_POINT",     "/AGNOS/ENTRY_POINT",      false, true);
        copyApkFromAssets(myContext, "PROCESSING",      "/AGNOS/PROCESSING",       false, true);
        copyApkFromAssets(myContext, "TERMINAL",        "/AGNOS/TERMINAL",         false, true);

        copyApkFromAssets(myContext, "apps",                 "/AGNOS/apps",        false, true);
        copyApkFromAssets(myContext, "libJSpeedy.so",        "/AGNOS/libJSpeedy.so", true, true);
        //copyApkFromAssets(myContext, "libEMVCo.so",          "/AGNOS/libEMVCo.so", true, true);
        copyApkFromAssets(myContext, "libPayPass.so",      	"/AGNOS/libPayPass.so", true, true);
        copyApkFromAssets(myContext, "libPayWave.so",      	"/AGNOS/libPayWave.so", true, true);
        copyApkFromAssets(myContext, "libXPressPay.so",    "/AGNOS/libXPressPay.so", true, true);
        copyApkFromAssets(myContext, "libDPAS.so",         "/AGNOS/libDPAS.so",true, true);
        copyApkFromAssets(myContext, "libFlash.so",          "/AGNOS/libFlash.so", true, true);

        copyApkFromAssets(myContext, "appsd",                 "/AGNOS/appsd",        false, true);
        copyApkFromAssets(myContext, "libJSpeedyd.so",        "/AGNOS/libJSpeedyd.so", true, true);
        //copyApkFromAssets(myContext, "libEMVCo.so",          "/AGNOS/libEMVCo.so", true, true);
        copyApkFromAssets(myContext, "libPayPassd.so",      	"/AGNOS/libPayPassd.so", true, true);
        copyApkFromAssets(myContext, "libPayWaved.so",      	"/AGNOS/libPayWaved.so", true, true);
        copyApkFromAssets(myContext, "libXPressPayd.so",    "/AGNOS/libXPressPayd.so", true, true);
        copyApkFromAssets(myContext, "libDPASd.so",         "/AGNOS/libDPASd.so",true, true);
        copyApkFromAssets(myContext, "libFlashd.so",          "/AGNOS/libFlashd.so", true, true);
    }

    public static void copyApkFromAssets(Context context, String fileName, String toPath, Boolean Overwrite, Boolean WriteToAppDir)
    {
         try {
            InputStream is = context.getAssets().open(fileName);

            String targetPath;
            if(WriteToAppDir)
                targetPath = context.getFilesDir() + toPath;
            else
                targetPath = toPath;

            File file = new File(targetPath);

            if(file.exists() && (!Overwrite))
                return;

            FileOutputStream fos = new FileOutputStream(file);

            byte[] temp = new byte[1024];
            int i;
            while ((i = is.read(temp)) > 0) {
                fos.write(temp, 0, i);
            }
            fos.close();
            is.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
