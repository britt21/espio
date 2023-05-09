package AmpEmvL2Android;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.amobilepayment.demo.Flow.BaseActivity;
import com.amobilepayment.demo.Flow.NotifierActivity;
import com.amobilepayment.demo.Flow.NotifierEMVActivity;
import com.amobilepayment.demo.Flow.SelectionEMVActivity;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.pos.device.SDKException;
import com.pos.device.beeper.Beeper;
import com.pos.device.ped.KeySystem;
import com.pos.device.ped.Ped;
import com.pos.device.ped.PedRetCode;
import com.pos.device.ped.PinBlockFormat;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.CountDownLatch;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.Flow.CardEntryActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Security.OfflineRSA;
import com.amobilepayment.demo.Security.PinInfo;
import com.amobilepayment.demo.Security.PinpadListener;
import com.amobilepayment.demo.Security.PinpadManager;
import com.amobilepayment.demo.Transactions.Transaction;
import com.amobilepayment.demo.Transactions.TransactionContract;
import com.amobilepayment.demo.Utils.LogUtil;
import com.amobilepayment.demo.Utils.StringUtil;
import com.amobilepayment.demo.Utils.TransObject;

import static com.amobilepayment.demo.Utils.AmpReturnCodes.AMP_ERROR;

public class AmpEmvCB
{
    private static final String TAG = AmpEmvCB.class.getSimpleName();

    private static final int MSG_CB_DISPLAY_PROMPT  = 1;
    private static final int MSG_CB_DISPLAY_LIST    = 2;
    private static final int MSG_CB_DISPLAY_LED     = 3;
    private static final int MSG_CB_MAGREAD_DATA    = 7;

    // TODO: itemPos is public; this is a quickfix only
    public static int itemPos = AMP_ERROR;
    private static CountDownLatch mLatch ;
    private static OfflineRSA rsa = new OfflineRSA();
    private static byte[] EMVResponseCode = new byte[2];

    @SuppressLint("StaticFieldLeak")
    private static Context context = null;

    public static AmpEmvCB instance = null;

    private AmpEmvCB()
    {
    }

    public void SetContext(Context ctx)
    {
        this.context = ctx;
    }

    public static AmpEmvCB GetInstance()
    {
        if(instance == null) {
            instance = new AmpEmvCB();
        }
        return instance;
    }

    public static AmpEmvCBIF listener = new AmpEmvCBIF() {

        Queue<String> qeue_key = new LinkedList<>();
        PinInfo info = null;

        @Override
        public synchronized void AgnosCBDisplayMessage(String strMessage, int beep, int timeout) {
            Log.d(TAG, "AgnosCBDisplayMessage [START] strMessage=" + strMessage);

            Message message = new Message();
            message.what = MSG_CB_DISPLAY_PROMPT;
            message.obj = strMessage;
            mHandler.sendMessage(message);
            try {
                Thread.sleep(1200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Log.d(TAG, "AgnosCBDisplayMessage [END]");
        }

        @Override
        public int AgnosCBSelectItemFromList( String strTitle, String[] astrItems) {
            Log.d(TAG, "AgnosCBSelectItemFromList [START] Title=" + strTitle);

            for(int i=0; i<astrItems.length; i++)
                Log.d(TAG, "AgnosCBSelectItemFromList astrItems[" + i + "]= " + astrItems[i]);

            int iRetVal;
            Message message = new Message();
            message.what = MSG_CB_DISPLAY_LIST;
            message.obj = astrItems;
            mHandler.sendMessage(message);

            while(true) {
               if(itemPos != AMP_ERROR) {
                   iRetVal = itemPos;
                   break;
               }
            }

            Log.d(TAG, "AgnosCBSelectItemFromList [END] iRetVal=" + iRetVal);
            itemPos = AMP_ERROR;
            return iRetVal;
        }

        @Override
        public void AgnosCBGpiSwitchLED (byte bLed, byte bFlag, byte bColor) {
            Log.d(TAG, "AgnosCBGpiSwitchLED [START] Led=" + bLed + " Flag=" + bFlag + " Colour=" + bColor);
            Message message = new Message();
            message.what = MSG_CB_DISPLAY_LED;
            mHandler.sendMessage(message);
            Log.d(TAG, "AgnosCBGpiSwitchLED [END]");
        }

        @Override
        public int	AgnosCBOnlinePinEntry (byte[] Pan, int PanLen) {
            Log.d(TAG, "AgnosCBOnlinePinEntry [START]");

            String szPAN = StringUtil.hexString(Pan);
            Log.d(TAG, "AgnosCBOnlinePinEntry PAN=" + szPAN);

            String KeyMgtType =  "DUKPT";//AmpBaseInterface.GetCfgData("ACQS._1.SECURITY.MKEY.PIN.TYPE");
            int keyIndex = 0;

//            if(KeyMgtType.equals("DUKPT"))
//                keyIndex = AmpBaseInterface.GetCfgInt("ACQS._1.SECURITY.MKEY.PIN.INDEX");
//            else if(KeyMgtType.equals("MASTERSESSION"))
//                keyIndex = AmpBaseInterface.GetCfgInt("ACQS._1.SECURITY.WKEY.PIN.INDEX");
//            else
//                keyIndex = AmpBaseInterface.GetCfgInt("ACQS._1.SECURITY.WKEY.PIN.INDEX");

            final Ped ped = Ped.getInstance();
            byte[] KSN = null;

            if(KeyMgtType.equals("DUKPT")) {
                KSN = ped.getDukptKsn(keyIndex);
                LogUtil.LogHexBuffer("KSN", KSN, KSN.length);
            }

            info = getPinpadOnlinePin(60, String.valueOf(Transaction.baseAmount), szPAN);
            if(info.isNoPin()) {
                AgnosCBDisplayMessage("No PIN Entered!", 0, 0);
            }
            else if( (info.isResultFlag()) && (info.getErrno() == 0) ) {
                byte[] PinBlk = info.getPinblock();

//                if(KeyMgtType.equals("DUKPT")) {
//                    TransObject.PutData(TransactionContract.CRTDATA_KSN, KSN, KSN.length);
//                }
//                TransObject.PutData(TransactionContract.CRTDATA_PINBLOCK, PinBlk, PinBlk.length);
//                TransObject.SetFlag(TransactionContract.CRTDATA_FLAG_PINENTRYDONE, true);

                int PinRetryCount = 3;
//                if(TransObject.isPresent(TransactionContract.CRTDATA_PINRETRYCOUNT))
//                    PinRetryCount = TransObject.GetInt(TransactionContract.CRTDATA_PINRETRYCOUNT);
//                else
//                    PinRetryCount = AmpBaseInterface.GetCfgInt("TERMINAL.EMVOPTION.PINRETRY");
//                Log.d(TAG, "Pin Retry Count = " + PinRetryCount);
//                if(PinRetryCount > 0)
//                    PinRetryCount -= 1;
//                else
//                    PinRetryCount = 0;
//                TransObject.SetInt(TransactionContract.CRTDATA_PINRETRYCOUNT, PinRetryCount);

//                if(KeyMgtType.equals("DUKPT")) {
//                    LogUtil.LogHexBuffer("Get KSN", TransObject.GetData("PedKSN", 10), 10);
//                }
//
//                LogUtil.LogHexBuffer("Get PINBLK", TransObject.GetData("PinBlock", 8), 8);
            }
            Log.d(TAG, "AgnosCBOnlinePinEntry [END] errno="+info.getErrno());
            return info.getErrno();
        }

        @Override
        public byte[] AgnosCBGetEMVResponseCode(){
            return EMVResponseCode;
        }

        @Override
        public int	AgnosCBOfflinePinEntry (byte bEnciphered, int Language, int timeout, byte[] mod, byte modlen, byte[] exp, byte explen, byte[] IccRandom) {
            Log.d("AgnosCBOfflinePinEntry", "[START]");

            PinInfo info;
            int iRetVal;
            int remainingTries = 1;

            if(bEnciphered == 1) {
                LogUtil.LogHexBuffer("exp", exp, explen);
                LogUtil.LogHexBuffer("mod", mod, modlen);
                LogUtil.LogHexBuffer("ICC Random", IccRandom, 8);
                rsa.setExp(exp);
                rsa.setExpLen(explen);
                rsa.setMod(mod);
                rsa.setModLen(modlen);
                rsa.setIccRandom(IccRandom);
            }

            if(bEnciphered == 1)
                info = getPinpadOfflinePin(timeout, bEnciphered, rsa, remainingTries);
            else
                info = getPinpadOfflinePin(timeout, bEnciphered, null, remainingTries);

            iRetVal = info.getErrno();

            if (iRetVal == 0)
            {
                EMVResponseCode = info.getPinblock();
                LogUtil.LogHexBuffer("EMVResponseCode", EMVResponseCode, 2);
            }

            Log.d("AgnosCBOfflinePinEntry", "[END] iRetVal=" + iRetVal);
            return iRetVal;
        }

        @Override
        public void AgnosCBSetTrackData(byte[] track1, int track1sz, byte[] track2, int track2sz, byte[] track3, int track3sz) {
            Log.d("AgnosCBSetTrackData ", "[START] track1=" + Arrays.toString(track1) + " track2=" + Arrays.toString(track2) + " track3=" + Arrays.toString(track3));
            Message message = new Message();
            message.what = MSG_CB_MAGREAD_DATA;
            mHandler.sendMessage(message);
            Log.d("AgnosCBSetTrackData ", "[END]");
        }

        @Override
        public int kbGetKey_9210() {
            Log.d(TAG, "kbGetKey_9210");
            if(CardEntryActivity.gKeyPress != -1) {
                int Key = CardEntryActivity.gKeyPress;
                CardEntryActivity.gKeyPress = -1;
                return Key;
            }
            else
                return 0;
        }
        @Override
        public int kbhit_9210() {
            //Log.d(TAG, "kbhit_9210");
            if(CardEntryActivity.gKeyPress != -1)
                return 1;
            else
                return 0;
        }

        @Override
        public void kbFlush_9210() {
            Log.d(TAG, "kbFlush_9210");
            CardEntryActivity.gKeyPress = -1;
        }

        @Override
        public byte[] AgnosGetPinBlock() {
            if( (info.isResultFlag()) && (info.getErrno() == 0)) {
                byte[] PinBlock = info.getPinblock();

                if( (PinBlock != null) && (PinBlock.length == 8) ) {
                    return PinBlock;
                }
            }
            return null;
        }

        @Override
        public void AndroidBeep(int frequency, int durationMs) {
            Beeper beeper = Beeper.getInstance();

            try {
                beeper.beep(frequency, durationMs);
            } catch( SDKException ex ) {
                Log.e(TAG, "Exception = " + ex.toString());
            }
        }
    };

    @SuppressLint("HandlerLeak")
    private static Handler mHandler = new Handler()
    {
        @SuppressLint("SetTextI18n")
        public void handleMessage(Message msg)
        {
            Log.d(TAG, "handleMessage [START] Messages = " + msg.toString());

            switch (msg.what) {
                case MSG_CB_DISPLAY_PROMPT : {

                    Log.d(TAG, "launching NotifierEMVActivity");

                    Intent intent = new Intent(context, NotifierEMVActivity.class);
                    intent.putExtra(BaseActivity.PARAM_KEY, msg.obj.toString());
                    context.startActivity(intent);

                    break;
                }
                case MSG_CB_DISPLAY_LIST:

                    Log.d(TAG, "launching SelectionEMVActivity");

                    ArrayList<String> params = new ArrayList<>();
                    String[] values = (String[])msg.obj;
                    Collections.addAll(params, values);
                    Intent intent = new Intent (context, SelectionEMVActivity.class);
                    intent.putExtra(BaseActivity.PARAM_KEY, params);
                    intent.putStringArrayListExtra(BaseActivity.PARAM_KEY, params);
                    context.startActivity(intent);


//                    String[] values = (String[])msg.obj;
//                    final ArrayList<String> list = new ArrayList<String>();
//                    Collections.addAll(list, values);
//                    ArrayAdapter adapter = new ArrayAdapter<>(context, R.layout.activity_listview, list);
//                    lv.setAdapter(adapter);
//
//                    lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
//                        @Override
//                        public void onItemClick(AdapterView<?> adapterView, View view, int position, long id) {
//                            itemPos = position;
//                        }}
//                    );
                    break;

                case MSG_CB_DISPLAY_LED:
                    break;

                default:
                    break;
            }
        }
    };

    private static PinInfo getPinpadOnlinePin(int timeout, String amount, String cardNo) {
        Log.d("getPinpadOnlinePin","[START]");
        mLatch = new CountDownLatch(1);
        final PinInfo pinInfo = new PinInfo();

        PinpadManager pinpadManager = PinpadManager.getInstance();

        int iPinFormat;

        // Key Management Type
        String KeyMgtType =  "DUKPT";//AmpBaseInterface.GetCfgData("ACQS._1.SECURITY.MKEY.PIN.TYPE");

//        if(KeyMgtType.equals("DUKPT")) {
//            PinpadManager.keySystem = KeySystem.DUKPT_DES;
//            PinpadManager.keyIndex = AmpBaseInterface.GetCfgInt("ACQS._1.SECURITY.MKEY.PIN.INDEX");
//        }
//        else if(KeyMgtType.equals("MASTERSESSION")) {
//            PinpadManager.keySystem = KeySystem.MS_DES;
//            PinpadManager.keyIndex = AmpBaseInterface.GetCfgInt("ACQS._1.SECURITY.WKEY.PIN.INDEX");
//        }
//        else {
//            PinpadManager.keySystem = KeySystem.MS_DES;
//            PinpadManager.keyIndex = AmpBaseInterface.GetCfgInt("ACQS._1.SECURITY.WKEY.PIN.INDEX");
//        }
        PinpadManager.keyIndex = 0;
        PinpadManager.keySystem = KeySystem.DUKPT_DES;

        Log.d("getPinpadOnlinePin", "keySystem="+PinpadManager.keySystem);
        Log.d("getPinpadOnlinePin", "KeyIndex="+PinpadManager.keyIndex);

        // Pinblock Format
        iPinFormat = 0;//AmpBaseInterface.GetCfgInt("ACQS._1.SECURITY.PINFORMAT");

        if(iPinFormat == 0)
            PinpadManager.pinBlockFormat = PinBlockFormat.PIN_BLOCK_FORMAT_0;
        else if(iPinFormat == 1)
            PinpadManager.pinBlockFormat = PinBlockFormat.PIN_BLOCK_FORMAT_1;
        else if(iPinFormat == 2)
            PinpadManager.pinBlockFormat = PinBlockFormat.PIN_BLOCK_FORMAT_2;
        else if(iPinFormat == 3)
            PinpadManager.pinBlockFormat = PinBlockFormat.PIN_BLOCK_FORMAT_3;
        else if(iPinFormat == 4)
            PinpadManager.pinBlockFormat = PinBlockFormat.PIN_BLOCK_FORMAT_4;
        else if(iPinFormat == 5)
            PinpadManager.pinBlockFormat = PinBlockFormat.PIN_BLOCK_FORMAT_EPS;
        else
            PinpadManager.pinBlockFormat = PinBlockFormat.PIN_BLOCK_FORMAT_0;

        Log.d("getPinpadOnlinePin", "pinFormat="+PinpadManager.pinBlockFormat);

        // Pin Length
        String PinLen = "4";//AmpBaseInterface.GetCfgData("ACQS._1.SECURITY.PINLEN");
        //if(PinLen == null)
        PinpadManager.pinLength = PinLen;

        Log.d("getPinpadOnlinePin", "pinLength="+PinpadManager.pinLength);

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
            mLatch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Log.d("getPinpadOnlinePin","[END]");
        return pinInfo ;
    }


    private static PinInfo getPinpadOfflinePin(int timeout, int i, OfflineRSA key, int counts) {
        Log.d("getPinpadOfflinePin", "[START]");
        mLatch = new CountDownLatch(1);
        final PinInfo pinInfo = new PinInfo();
        PinpadManager pinpadManager = PinpadManager.getInstance();

        Log.d(TAG, "Timeout = " + timeout);
        try {
            Ped.getInstance().setPinEntryTimeout(timeout);
        } catch (SDKException e) {
            e.printStackTrace();
        }

        // Pin Length
       // String PinLen = AmpBaseInterface.GetCfgData("ACQS._1.SECURITY.PINLEN");
        //if(PinLen == null)
            String PinLen = "4";

        PinpadManager.pinLength = PinLen;
        Log.d("getPinpadOfflinePin", "pinLength="+PinpadManager.pinLength);

        pinpadManager.getOfflinePin(i,key,counts,new PinpadListener() {
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
            mLatch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Log.d("getPinpadOfflinePin", "[END]");
        return pinInfo ;
    }

}
