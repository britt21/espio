package com.amobilepayment.demo.Security;

import android.util.Log;

import com.amobilepayment.demo.Utils.ISOUtil;
import com.amobilepayment.demo.Utils.StringUtil;
import com.pos.device.SDKException;
import com.pos.device.icc.SlotType;
import com.pos.device.ped.IccOfflinePinApdu;
import com.pos.device.ped.KeySystem;
import com.pos.device.ped.Ped;
import com.pos.device.ped.PedRetCode;
import com.pos.device.ped.PinBlockCallback;
import com.pos.device.ped.PinBlockFormat;
import com.pos.device.ped.RsaPinKey;
import com.secure.api.PadView;

/**
 * Created by Symbol Tabios on 25/09/2017.
 */

public class PinpadManager {
    private static PinpadManager instance ;

    public static KeySystem keySystem;
    public static int keyIndex;
    public static PinBlockFormat pinBlockFormat;
    public static String pinLength;

    private PinpadManager(){}

    public static PinpadManager getInstance(){
        if(instance == null){
            instance = new PinpadManager();
        }
        return instance ;
    }

    private PinpadListener listener ;
    private String pinCardNo ;
    private int timeout ;

    public void getPin(int t, String amount , String c , PinpadListener l){
        Log.d("PinpadManager", "getPin [START]");
        this.listener = l ;
        this.timeout = t ;
        Log.d("getPin", "Timeout:" + this.timeout);
        this.pinCardNo = c ;
        final PinInfo info = new PinInfo();
        if(null == l){
            info.setResultFlag(false);
            listener.callback(info);
        }
        else if(pinCardNo == null || pinCardNo.equals("")){
            info.setResultFlag(false);
            listener.callback(info);
        }
        else {
            final Ped ped = Ped.getInstance() ;
            try {
                ped.setPinEntryTimeout(this.timeout);
            }
            catch (SDKException e) {
                e.printStackTrace();
            }

            pinCardNo = pinCardNo.substring(pinCardNo.length() - 13, pinCardNo.length() - 1);
            pinCardNo = ISOUtil.padleft(pinCardNo, pinCardNo.length() + 4, '0');
            PadView padView = new PadView();
            padView.setTitleMsg("SECURITY KEYBOARD");
            padView.setAmountTitle("AMOUNT:");
            padView.setAmount(StringUtil.TwoWei(amount));
            padView.setPinTips("PIN Entry Screen:");
            ped.setPinPadView(padView);
            new Thread(){
                @Override
                public void run() {

                    try {
                        ped.getPinBlock(PinpadManager.keySystem, PinpadManager.keyIndex,
                                PinpadManager.pinBlockFormat, PinpadManager.pinLength, pinCardNo,
                                new PinBlockCallback() {
                                    @Override
                                    public void onPinBlock(int i, byte[] bytes) {
                                        Log.d("PinpadManager","onPinBlock = " + i);
                                        switch (i){
                                            case PedRetCode.NO_PIN :
                                                info.setResultFlag(true);
                                                info.setNoPin(true);
                                                break;
                                            case PedRetCode.TIMEOUT:
                                                info.setResultFlag(false);
                                                info.setErrno(i);
                                                break;
                                            case PedRetCode.ENTER_CANCEL:
                                                info.setResultFlag(false);
                                                info.setErrno(i);
                                                break;
                                            case 0: // PIN OK
                                                info.setResultFlag(true);
                                                info.setPinblock(bytes);
                                                break;
                                            default:
                                                info.setResultFlag(false);
                                                info.setErrno(i);
                                                break;
                                        }
                                        listener.callback(info);
                                    }
                                });
                    } catch (IllegalStateException ex) {
                        info.setResultFlag(false);
                        info.setErrno(2255);
                        listener.callback(info);
                    }
                }
            }.start();
        }
    }

    public void getOfflinePin(int i , OfflineRSA key , int counts , PinpadListener l){
        Log.d("PinpadManager", "getOfflinePin [START]");

        this.listener = l ;
        Ped ped = Ped.getInstance() ;
        PadView padView = new PadView();
        final String pinTips ;
        padView.setTitleMsg("SECURITY KEYBOARD");
        pinTips = "Please enter offline PIN\n" + "Left "+counts +" times";

        final PinInfo info = new PinInfo();
        padView.setPinTips(pinTips);
        ped.setPinPadView(padView);
        IccOfflinePinApdu apdu = new IccOfflinePinApdu();

        // For Enciphered Offline
        if(i == 1){
            RsaPinKey rsaPinKey = new RsaPinKey();
            rsaPinKey.setIccrandom(key.getIccRandom());
            rsaPinKey.setModlen(key.getMod().length);
            rsaPinKey.setMod(key.getMod());
            rsaPinKey.setExplen(key.getExp().length);
            rsaPinKey.setExp(key.getExp());
            apdu.setRsakey( rsaPinKey );
        }
        apdu.setCla(0x00);
        apdu.setIns(0x20);
        apdu.setLe(0x00);
        apdu.setLeflg(0x00);
        apdu.setP1(0x00);
        apdu.setP2(i == 1 ? 0x88:0x80);

        Log.d("Ped ICC Slot", "getIccSlot="+ped.getIccSlot(SlotType.USER_CARD));

        try {
            ped.getOfflinePin(i == 1 ? KeySystem.ICC_CIPHER:KeySystem.ICC_PLAIN,
                    ped.getIccSlot(SlotType.USER_CARD), PinpadManager.pinLength, apdu,
                    new PinBlockCallback() {
                        @Override
                        public void onPinBlock(int i, byte[] bytes) {
                            Log.d("PinpadManager","onPinBlock = " + i);
                            switch (i){
                                case PedRetCode.NO_PIN :
                                    info.setResultFlag(true);
                                    info.setNoPin(true);
                                    break;
                                case PedRetCode.TIMEOUT:
                                    info.setResultFlag(false);
                                    info.setErrno(i);
                                    break;
                                case PedRetCode.ENTER_CANCEL:
                                    info.setResultFlag(false);
                                    info.setErrno(i);
                                    break;
                                case 0: // PIN OK
                                    info.setResultFlag(true);
                                    info.setPinblock(bytes);
                                    break;
                                default:
                                    info.setResultFlag(false);
                                    info.setErrno(i);
                                    break;
                            }
                            listener.callback(info);
                        }
                    });
        } catch (IllegalStateException ex) {
            info.setResultFlag(false);
            info.setErrno(2255);
            listener.callback(info);
        }

    }
}
