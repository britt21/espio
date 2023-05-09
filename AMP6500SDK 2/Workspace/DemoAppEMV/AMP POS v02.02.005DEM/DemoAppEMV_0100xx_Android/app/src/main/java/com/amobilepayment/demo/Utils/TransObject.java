package com.amobilepayment.demo.Utils;

/**
 * Created by Symbol Tabios on 23/11/2017.
 */

public class TransObject {

    public static native byte[] GetData(String key, int buffer_len);
    public static native int PutData(String key, byte[] data_buffer, int buffer_len);

    public static native String GetString(String key);
    public static native int SetString(String key, String data_buffer);

    public static native int GetInt(String key);
    public static native int SetInt(String key, int buffer_value);

    public static native boolean GetFlag(String key);
    public static native int SetFlag(String key, boolean buffer_len);

    public static native long GetLong(String key);
    public static native int SetLong(String key, long buffer_len);

    public static native char GetChar(String key);
    public static native int SetChar(String key, char buffer_value);

    public static native boolean isPresent(String key);
    public static native void ClearContents();

    public static native String EmvColxnGetStr(byte[] tag, int tagLen);
    public static native byte[] EmvColxnGetBin(byte[] tag, int tagLen);
    public static native int EmvColxnPutBin(byte[] tag, int tagLen, byte[] value, int value_len);

    public static native byte[] BuildRequestPacket();
    public static native int ParseResponsePacket(byte[] ResponseBuff, int ResponseLen);

    public static native int DoSetTransTraceNum();
    public static native int DoIncrementTransTraceNum();
}
