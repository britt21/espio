package com.amobilepayment.demo.Security;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.pos.device.SDKException;
import com.pos.device.icc.SlotType;
import com.pos.device.ped.IccOfflinePinApdu;
import com.pos.device.ped.KeySystem;
import com.pos.device.ped.Ped;
import com.pos.device.ped.PinBlockCallback;
import com.pos.device.ped.RsaPinKey;
import com.secure.api.PadView;

import java.text.DecimalFormat;
import java.util.concurrent.CountDownLatch;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.Transaction;

public class PinEntryActivity extends AppCompatActivity {
    static final int PIN_SUCCESS = 1;
    static final int PIN_NOT_ENTER = 2;
    static final int PIN_CANCEL = 3;
    static final int PIN_ERROR = 4;

    private CountDownLatch mLatch ;
    protected boolean isPinExist = false;// 是否有密码
    protected String PIN; // 52

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d("PinEntryActivity","onCreate");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.pin_entry);

        PinInfo info = null;
        int iRetVal = -1;
        byte[] pinBlock =  new byte[16];
        byte[] pinBlockLen = new byte[16];

        switch (Transaction.PINType)
        {
            case 1:
                info = getPinpadOnlinePin(3000, String.valueOf(Transaction.baseAmount), "22236000089020329");
                break;
            case 2:
                iRetVal =  getOfflinePin(0, null, pinBlockLen, pinBlock);
                Log.d("offlinePIN", "iRetVal="+iRetVal);
                break;
            default:
                // Show Error Messages!
                //iRetVal =  getOfflinePin(0, null, pinBlockLen, pinBlock);
                //info = getPinpadOnlinePin(3000, String.valueOf(Transaction.baseAmount), "22236000089020329");
                break;
        }
    }


    public PinInfo getPinpadOnlinePin(int timeout, String amount, String cardNo) {
        Log.d("Masterctl","getPinpadOnlinePin");
        this.mLatch = new CountDownLatch(1);
       // mHandler.sendEmptyMessage(MSG_INPUT_PIN);
        final PinInfo pinInfo = new PinInfo();

        PinpadManager pinpadManager = PinpadManager.getInstance();
        pinpadManager.getPin(timeout,amount,cardNo, new PinpadListener() {
            @Override
            public void callback(PinInfo info) {
                pinInfo.setResultFlag(info.isResultFlag());
                pinInfo.setErrno(info.getErrno());
                pinInfo.setNoPin(info.isNoPin());
                pinInfo.setPinblock(info.getPinblock());
                mLatch.countDown();
            }
        });
        try {
            this.mLatch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return pinInfo ;
    }

    private int offlinePinTryCnt = Integer.MAX_VALUE;
    public int pinVerifyResult(int tryCount) {
        offlinePinTryCnt= tryCount;
        return 0;
    }
    //	i: 1 enciphered PIN,0:plaintext PIN
    //	bytes : pinblock Len
    //  bytes1: pinblock data

    //ReentrantLock pinLock = new ReentrantLock()

    public int getOfflinePin(int i, RsaPinKey rsaPinkey, final byte[] bytes, final byte[] bytes1) {
        Ped ped = Ped.getInstance() ;
        PadView padView = new PadView();
        long amount = 10000;
        final int[] mErrorCode = new int[1];
        if (amount >= 0) {
            double amt = (double)amount/(double)100;
            DecimalFormat df = new DecimalFormat("0.00");
            padView.setAmount(df.format(amt));
            padView.setAmountTitle("TO DO");
        }
        try {
            ped.setPinEntryTimeout(60);
        } catch (SDKException e) {
            e.printStackTrace();
        }

        if(offlinePinTryCnt == Integer.MAX_VALUE)
            padView.setTitleMsg("Amount");
        else {
            String temp = "PINPAD";
            String strTip = String.format(temp, offlinePinTryCnt);
            padView.setTitleMsg(strTip);
        }

        padView.setPinTips("PLS ENTER OFFLINE PIN");
        ped.setPinPadView(padView);

        KeySystem ks;
        if (i == 1)
            ks = KeySystem.ICC_CIPHER;
        else
            ks = KeySystem.ICC_PLAIN;
        int fd = ped.getIccSlot(SlotType.USER_CARD);
        Log.d("offline pin", "fd="+fd);
        String pinLenLimit = "0,4,5,6,7,8,9,10,11,12";

        IccOfflinePinApdu apdu = new IccOfflinePinApdu();
        if (i == 1) {
            apdu.setRsakey(rsaPinkey);
        }
        apdu.setCla(0x00);
        apdu.setIns(0x20);
        apdu.setLe(0x00);
        apdu.setLeflg(0x00);
        apdu.setP1(0x00);
        apdu.setP2((i == 1)?0x88:0x80);

       // status.set(false);
        mErrorCode[0] = -1;
        try{
            ped.setPinEntryTimeout(60);}
        catch(SDKException ex)
        {

        }
        ped.getOfflinePin(ks, fd, pinLenLimit, apdu, new PinBlockCallback() {
            @Override
            public void onPinBlock(int result, byte[] pinBlock) {

                if (result != 0) {
                    mErrorCode[0] = result;
                } else { //success
                    if (pinBlock != null && bytes != null && bytes1 != null) {
                        bytes[0] = (byte)pinBlock.length;
                        System.arraycopy(pinBlock, 0, bytes1, 0, bytes[0]);
                        mErrorCode[0] = 0;
                    }
                }
              //  status.set(true);
              //  releaseLock(offlinePinLock);
            }
        });
       // tryLock(offlinePinLock, TIME_OUT);

        return mErrorCode[0];
    }
}
