package AmpEmvL2Android;

/**
 * Created by Alainsky on 9/24/2017.
 */

public interface AmpEmvCBIF {
    public void AgnosCBDisplayMessage(String strMessage, int beep, int timeout);
    public int AgnosCBSelectItemFromList(String Title, String[] Items);
    public void AgnosCBGpiSwitchLED(byte Led, byte Flag, byte Colour);
    public int AgnosCBOnlinePinEntry (byte[] Pan, int PanLen);
    public int AgnosCBOfflinePinEntry (byte bEnciphered, int Language, /*byte VerifyOnly,*/ int timeout, byte[] mod, byte modlen, byte[] exp, byte explen, byte[] IccRandom);
    public byte[] AgnosCBGetEMVResponseCode();
    public void AgnosCBSetTrackData(byte[] track1, int track1sz, byte[] track2, int track2sz, byte[] track3, int track3sz);
    public byte[] AgnosGetPinBlock();

    //Agnos Keys
    public int kbGetKey_9210();
    public int kbhit_9210();
    public void kbFlush_9210();
    public void AndroidBeep(int frequency, int durationMs);
}
