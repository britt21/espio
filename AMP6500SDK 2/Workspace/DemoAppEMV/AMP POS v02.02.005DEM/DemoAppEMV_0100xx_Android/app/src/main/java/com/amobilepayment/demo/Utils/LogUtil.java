package com.amobilepayment.demo.Utils;

import android.util.Log;

/**
 * Created by ping_ocampo on 11/16/2017.
 */

public class LogUtil {

    public static void LogHexBuffer(String szTitle, byte[] Data, int DataLen)
    {
        Log.d(szTitle, "["+ DataLen + "]");
        for(int offset = 0; offset < DataLen;)
        {
            if( (offset+16) < DataLen)
            {
                LogHexData(Data, 16, offset);
                offset += 16;
            }
            else
            {
                LogHexData(Data, DataLen-offset, offset);
                offset += (DataLen-offset);
            }
        }
    }

//    private static void LogHexData(byte[] Data, int NumBytes, int offset)
//    {
//        String szOffset;
//        StringBuilder sb = new StringBuilder();
//        for( int i=0; i<NumBytes; i++)
//        {
//            sb.append(String.format("%02X ", Data[offset+i] & 0xff));
//        }
//        sb.setLength(sb.length() - 1);
//        szOffset = String.format("%04X", offset);
//        Log.d(szOffset, sb.toString());
//    }

    private static void LogHexData(byte[] Data, int NumBytes, int offset)
    {
        String szOffset;
        StringBuilder sb = new StringBuilder();
        StringBuilder sc = new StringBuilder();
        for( int i=0; i<NumBytes; i++)
        {
            sb.append(String.format("%02X ", Data[offset+i] & 0xff));
            if( ((Data[offset+i] & 0xff) >= 0x20) && ((Data[offset+i] & 0xff) <= 0x7f) )
                sc.append(String.format("%c", Data[offset+i] & 0xff));
            else
                sc.append(".");
        }
        sb.setLength(sb.length() - 1);
        //sc.setLength(sc.length() - 1);
        szOffset = String.format("%04X", offset);
        Log.d(szOffset, sb.toString() + " - " + sc.toString());
    }

}
