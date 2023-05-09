package com.amobilepayment.androidunattendeddemo;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.Gravity;
import android.widget.Toast;

/**
 * Created by Rasa Vafaie on 2017-09-25.
 */

public class UtilUI {

    private static volatile UtilUI soleInstance;
    private Context context;
    Handler handler=new Handler(Looper.getMainLooper());

    static UtilUI getInstance(){
        if (soleInstance==null){
            synchronized (UtilUI.class){
                if (soleInstance==null){
                    soleInstance=new UtilUI();
                }
            }
        }
        return soleInstance;
    }

    void init(Context context){
        soleInstance.context=context;
    }

    void toast(final String str){
        Log.d("MYDEBUG","TOAST MESSAGE: "+str);
        if (soleInstance==null || soleInstance.context==null){
            return;
        }
        handler.post(new Runnable() {
            @Override
            public void run() {
                Toast toast=Toast.makeText(soleInstance.context,str,Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.CENTER,0,0);
                toast.show();
            }
        });

    }

    public static String showAsHex(byte value) {
        return String.format("0x%02X", value);
    }

    public static String showAsHex(byte[] array){
        if (array==null || array.length==0)
            return "[null array]";

        StringBuffer str=new StringBuffer();
        str.append("Len= "+array.length+"  {");
        for(int i=0; i<array.length;i++){
            str.append(showAsHex(array[i]));
            if (i!=(array.length-1))
                str.append(", ");
        }
        return str.append("}").toString();

    }

    public static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i+1), 16));
        }
        return data;
    }

    private final static char[] hexArray = "0123456789ABCDEF".toCharArray();
    public static String bytesToHex(byte[] bytes) {
        char[] hexChars = new char[bytes.length * 2];
        for ( int j = 0; j < bytes.length; j++ ) {
            int v = bytes[j] & 0xFF;
            hexChars[j * 2] = hexArray[v >>> 4];
            hexChars[j * 2 + 1] = hexArray[v & 0x0F];
        }
        return new String(hexChars);
    }

}
