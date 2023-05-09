package com.amobilepayment.androidunattendeddemo;

import android.app.Fragment;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import com.pos.device.SDKException;
import com.pos.device.beeper.Beeper;
import com.pos.device.picc.EmvContactlessCard;
import com.pos.device.picc.MifareClassic;
import com.pos.device.picc.PiccReader;
import com.pos.device.picc.PiccReaderCallback;

/**
 * Created by Rasa Vafaie on 2017-09-07.
 */

public class FragNFC extends Fragment {

    private static final String TAG="MYDEBUG";

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view=inflater.inflate(R.layout.frag_nfc, container, false);

        return view;
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        FragmentsProvider.hideFragment(FragmentsProvider.FRAG_TAG.NFC,getFragmentManager());
        startPICCard();
    }


    private void startPICCard() {
        try {
            PiccReader.getInstance().reset();
            PiccReader.getInstance().startSearchCard(0, piccReaderCallback);
            setStatus(PICCARD_STATUS.READY_TO_PROXIMATE);
        } catch (SDKException e) {
            e.printStackTrace();
        }
    }

    private PiccReaderCallback piccReaderCallback=new PiccReaderCallback() {

        @Override
        public void onSearchResult(int result, int cardType) {

            Log.d(TAG, "Picc search result is " + result + " ==> "+getStatusDescription(result));

            if (result == PiccReaderCallback.SUCCESS) {


                try {
                    Beeper.getInstance().beep(1600,200);
                } catch (SDKException e) {
                    e.printStackTrace();
                }


                eraseEditTexts();

                String cardTypeName=getCardtypeDescription(cardType);
                Log.d(TAG, "The card searched is " + cardType + " ==> "+cardTypeName);

                setTextView(R.id.tvNFCCardType, getCardtypeDescription(cardType)  );


                //CPU card
                if ((cardType == PiccReader.MIFARE_PRO) || (cardType == PiccReader.MIFARE_PRO_S50) || (cardType == PiccReader.MIFARE_PRO_S70) || (cardType == PiccReader.MIFARE_DESFIRE)) {
                    Log.d(TAG, "cardType == PiccReader.MIFARE_PRO) || (cardType == PiccReader.MIFARE_PRO_S50) || (cardType == PiccReader.MIFARE_PRO_S70 || || (cardType == PiccReader.MIFARE_DESFIRE)");

                    try {
                        EmvContactlessCard emvContactlessCard = EmvContactlessCard.connect();
                        Log.d(TAG, "after connect");
                        if (emvContactlessCard != null) {

                            Log.d(TAG, "emvContactlessCard != null");

                            try {
                                Beeper.getInstance().beep();
                            } catch (SDKException e1) {
                                e1.printStackTrace();
                            }

                            byte[] uid = emvContactlessCard.getUID();
                            if (uid!=null){
                                Log.d(TAG, "emvContactlessCard.getUID() "+UtilUI.showAsHex(uid));
                                setEditText(R.id.etUIDNFC, UtilUI.showAsHex(uid));
                            }
                            else{
                                Log.d(TAG, "UID is null");
                                setEditText(R.id.etUIDNFC, "UID is null");
                            }

                            byte[] apdu = {0x00, (byte) 0xa4, 0x04, 0x00, 0x09, (byte) 0xA0, 0x00, 0x00, 0x00, 0x03, (byte) 0x86, (byte) 0x98, 0x07, 0x01};
                            setEditText(R.id.etAPDUNFC, UtilUI.showAsHex(apdu));

                            byte[] response = emvContactlessCard.transmit(apdu);
                            if (response!=null){
                                Log.d(TAG, UtilUI.showAsHex(response));
                                setEditText(R.id.etResponseNFC,UtilUI.showAsHex(response) );
                            }


                            emvContactlessCard.deactive(new EmvContactlessCard.DeactiveCallback() {// must be called this method if you want to operate the card any more.
                                @Override
                                public void onFinish(int i) {
                                    Log.d(TAG, "Remove Card ok");
                                }
                            });

                        } else {
                            Log.d(TAG, "emvContactlessCard == null ==> Connect card failed!");
                        }
                    } catch (SDKException e) {
                        Log.d(TAG, "My error SDKException "+e.getMessage());
                        e.printStackTrace();
                    }
                } else if ((cardType == PiccReader.MIFARE_ONE_S50) || (cardType == PiccReader.MIFARE_ONE_S70) ) {//Mifare Card
                    Log.d(TAG,"(cardType == PiccReader.MIFARE_ONE_S50) || (cardType == PiccReader.MIFARE_ONE_S70) ");

                    try {
                        MifareClassic mifareClassic = MifareClassic.connect();
                        if (mifareClassic != null) {
                            Log.d(TAG, "Mifare Classic connect success!");
                            byte[] uid = mifareClassic.getUID();
                            if (uid!=null){
                                Log.d(TAG, UtilUI.showAsHex(uid));
                                setEditText(R.id.etUIDNFC, UtilUI.showAsHex(uid));
                            } else {
                                Log.d(TAG, "Card type "+cardType + " UID is null");
                            }
                            //byte[] info = mifareClassic.getInfo();
                            //if (info!=null){
                            //	Log.d(TAG, StringUtil.hexString(info));
                            //	setEditText(R.id.etResponse, StringUtil.hexString(info));
                            //}
                        } else {
                            Log.d(TAG, "MifareClassic.connect() returns null");
                        }
                    } catch (SDKException e) {
                        e.printStackTrace();
                    }
                }
            }
            else{
                Log.d(TAG, "==> Picc search result is NOT SUCCESS ");
                toastOnUI("==> Picc search result is NOT SUCCESS ");
            }
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    startPICCard();
                }
            });



        }
    };

    private void setTextView(final int resID, final String text){
        if (text==null)
            return;
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ((TextView) getView().findViewById(resID)).setText(text);
            }
        });
    }

    private void setEditText(final int id,final String text){
        if (text==null)
            return;
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ((EditText) getView().findViewById(id)).setText(text);
            }
        });
    }

    private void eraseEditTexts(){
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ((EditText) getView().findViewById(R.id.etUIDNFC)).setText("");
                ((EditText) getView().findViewById(R.id.etAPDUNFC)).setText("");
                ((EditText) getView().findViewById(R.id.etResponseNFC)).setText("");
            }
        });

    }

    private void toastOnUI(final String str){
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(getActivity(), str, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void setStatus(PICCARD_STATUS status){
        switch(status){
            case STOPPED:
                ((TextView)  getView().findViewById(R.id.tvPICCardStatus)).setText(getResources().getString(R.string.textPICCard));
                break;

            case READY_TO_PROXIMATE:
                ((TextView)  getView().findViewById(R.id.tvPICCardStatus)).setText(getResources().getString(R.string.textProximity));
                break;
        }
    }

    private enum PICCARD_STATUS{
        STOPPED,
        READY_TO_PROXIMATE;
    }

    private String getStatusDescription(int status){
        switch (status){
            case 0:
                return "SUCCESS";

            case 1:
                return "USER_CANCEL";

            case 2:
                return "TIMEOUT_ERROR";

            case 3:
                return "UNSUPPORTED_CARD";

            default:
                return "";
        }
    }

    private String getCardtypeDescription(int cardType){
        switch (cardType) {
            case 0:
                return "MIFARE_ONE_S50";

            case 1:
                return "MIFARE_ONE_S70";

            case 2:
                return "MIFARE_ULTRALLIGHT";

            case 3:
                return "MIFARE_DESFIRE";

            case 4:
                return "MIFARE_PRO";

            case 5:
                return "MIFARE_PRO_S50";

            case 6:
                return "MIFARE_PRO_S70";

            case 7:
                return "TYPEB";

            case 8:
                return "TYPEB_TCL";

            case 9:
                return "SONY_FELICA";

            case 10:
                return "UNKNOWN_TYPEA";

            default:
                return "";
        }
    }

}

/*public class FragNFC extends Fragment implements View.OnClickListener{

    private static final String TAG="MYDEBUG";

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view=inflater.inflate(R.layout.frag_nfc, container, false);
        //((Button) view.findViewById(R.id.bStartSearch)).setOnClickListener(this);
        //((Button) view.findViewById(R.id.bStop)).setOnClickListener(this);
        return view;
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        //fitText();
        FragmentsProvider.hideFragment(FragmentsProvider.FRAG_TAG.NFC,getFragmentManager());
        startPICCard();
    }

    private void fitText(){
        UtilFitText.fitTextButtonsAfterCreatedGroup(getActivity(),
                (Button) getView().findViewById(R.id.bStartSearch),
                (Button) getView().findViewById(R.id.bStop));

        UtilFitText.fitTextViewAfterMeasured(getActivity(), (TextView) getView().findViewById(R.id.tvPICCardStatus));
        //UtilFitText.fitTextViewAfterMeasured(getActivity(), (TextView) getView().findViewById(R.id.tvTimeout));

        UtilFitText.fitTextViewAfterCreatedGroup(getActivity(),
                (TextView) getView().findViewById(R.id.tvUid),
                (TextView) getView().findViewById(R.id.tvApdu),
                (TextView) getView().findViewById(R.id.tvResponse));
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.bStartSearch:
                startPICCard();
                break;

            case R.id.bStop:
                stopPICCard();
                break;
        }
    }

    private void startPICCard() {
        //eraseEditTexts();
        try {
            PiccReader.getInstance().reset();
            PiccReader.getInstance().startSearchCard(0, piccReaderCallback);
            setStatus(PICCARD_STATUS.READY_TO_PROXIMATE);
        } catch (SDKException e) {
            e.printStackTrace();
        }
    }

    private void stopPICCard() {
        PiccReader.getInstance().stopSearchCard();
        setStatus(PICCARD_STATUS.STOPPED);
    }

    private PiccReaderCallback piccReaderCallback=new PiccReaderCallback() {

        @Override
        public void onSearchResult(int result, int cardType) {
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    try {
                        Beeper.getInstance().beep(1600,200);
                    } catch (SDKException e) {
                        e.printStackTrace();
                    }
                }
            });

            eraseEditTexts();


            Log.d(TAG, "Picc search result is " + result + " ==> "+getStatusDescription(result));
            Log.d(TAG, "The card searched is " + cardType + " ==> "+getCardtypeDescription(cardType));
            if (result == PiccReaderCallback.SUCCESS) {

                Log.d(TAG, "The card searched is " + cardType + " ==> "+getCardtypeDescription(cardType));

                //CPU card
                if ((cardType == PiccReader.MIFARE_PRO) || (cardType == PiccReader.MIFARE_PRO_S50) || (cardType == PiccReader.MIFARE_PRO_S70) || (cardType == PiccReader.MIFARE_DESFIRE)) {
                    Log.d(TAG, "cardType == PiccReader.MIFARE_PRO) || (cardType == PiccReader.MIFARE_PRO_S50) || (cardType == PiccReader.MIFARE_PRO_S70 || || (cardType == PiccReader.MIFARE_DESFIRE)");

                    try {
                        EmvContactlessCard emvContactlessCard = EmvContactlessCard.connect();
                        Log.d(TAG, "after connect");
                        if (emvContactlessCard != null) {

                            Log.d(TAG, "emvContactlessCard != null");

                            try {
                                Beeper.getInstance().beep();
                            } catch (SDKException e1) {
                                e1.printStackTrace();
                            }

                            byte[] uid = emvContactlessCard.getUID();
                            if (uid!=null){
                                Log.d(TAG, UtilUI.bytesToHex(uid));
                                setEditText(R.id.etUID, UtilUI.bytesToHex(uid));
                            }
                            else{
                                Log.d(TAG, "UID is null");
                                setEditText(R.id.etUID, "UID is null");
                            }

                            byte[] apdu = {0x00, (byte) 0xa4, 0x04, 0x00, 0x09, (byte) 0xA0, 0x00, 0x00, 0x00, 0x03, (byte) 0x86, (byte) 0x98, 0x07, 0x01};
                            setEditText(R.id.etAPDU, UtilUI.bytesToHex(apdu));

                            byte[] response = emvContactlessCard.transmit(apdu);
                            if (response!=null){
                                Log.d(TAG, UtilUI.bytesToHex(response));
                                setEditText(R.id.etResponse,UtilUI.bytesToHex(response) );
                            }


                            emvContactlessCard.deactive(new EmvContactlessCard.DeactiveCallback() {// must be called this method if you want to operate the card any more.
                                @Override
                                public void onFinish(int i) {
                                    Log.d(TAG, "Remove Card ok");
                                }
                            });

                        } else {
                            Log.d(TAG, "emvContactlessCard == null ==> Connect card failed!");
                        }
                    } catch (SDKException e) {
                        Log.d(TAG, "My error SDKException "+e.getMessage());
                        e.printStackTrace();
                    }
                } else if ((cardType == PiccReader.MIFARE_ONE_S50) || (cardType == PiccReader.MIFARE_ONE_S70) ) {//Mifare Card
                    Log.d(TAG,"(cardType == PiccReader.MIFARE_ONE_S50) || (cardType == PiccReader.MIFARE_ONE_S70) ");

                    try {
                        MifareClassic mifareClassic = MifareClassic.connect();
                        if (mifareClassic != null) {
                            Log.d(TAG, "Mifare Classic connact success!");
                            byte[] uid = mifareClassic.getUID();
                            if (uid!=null){
                                Log.d(TAG, UtilUI.bytesToHex(uid));
                                setEditText(R.id.etUID, UtilUI.bytesToHex(uid));
                            } else {
                                Log.d(TAG, "Card type "+cardType + " UID is null");
                            }
                            //byte[] info = mifareClassic.getInfo();
                            //if (info!=null){
                            //	Log.d(TAG, StringUtil.hexString(info));
                            //	setEditText(R.id.etResponse, StringUtil.hexString(info));
                            //}
                        } else {
                            Log.d(TAG, "MifareClassic.connect() returns null");
                        }
                    } catch (SDKException e) {
                        e.printStackTrace();
                    }
                }
            }
            else{
                Log.d(TAG, "==> Picc search result is NOT SUCCESS ");
                toastOnUI("==> Picc search result is NOT SUCCESS ");
            }
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    startPICCard();
                    //stopPICCard();
                }
            });



        }
    };

    private void setEditText(final int id,final String text){
        if (text==null)
            return;
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ((EditText) getView().findViewById(id)).setText(text);
            }
        });
    }

    private void eraseEditTexts(){
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ((EditText) getView().findViewById(R.id.etUID)).setText("");
                ((EditText) getView().findViewById(R.id.etAPDU)).setText("");
                ((EditText) getView().findViewById(R.id.etResponse)).setText("");
            }
        });

    }

    private void toastOnUI(final String str){
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(getActivity(), str, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void setStatus(PICCARD_STATUS status){
        switch(status){
            case STOPPED:
                //UtilFitText.fitTextView(getActivity(), getResources().getString(R.string.textPICCard), (TextView)  getView().findViewById(R.id.tvPICCardStatus));
                ((TextView)  getView().findViewById(R.id.tvPICCardStatus)).setText(getResources().getString(R.string.textPICCard));
                break;

            case READY_TO_PROXIMATE:
                //UtilFitText.fitTextView(getActivity(), getResources().getString(R.string.textProximity), (TextView)  getView().findViewById(R.id.tvPICCardStatus));
                ((TextView)  getView().findViewById(R.id.tvPICCardStatus)).setText(getResources().getString(R.string.textProximity));
                break;
        }
    }

    private enum PICCARD_STATUS{
        STOPPED,
        READY_TO_PROXIMATE;
    }

    private String getStatusDescription(int status){
        switch (status){
            case 0:
                return "SUCCESS";

            case 1:
                return "USER_CANCEL";

            case 2:
                return "TIMEOUT_ERROR";

            case 3:
                return "UNSUPPORTED_CARD";

            default:
                return "";
        }
    }

    private String getCardtypeDescription(int cardType){
        switch (cardType) {
            case 0:
                return "MIFARE_ONE_S50";

            case 1:
                return "MIFARE_ONE_S70";

            case 2:
                return "MIFARE_ULTRALLIGHT";

            case 3:
                return "MIFARE_DESFIRE";

            case 4:
                return "MIFARE_PRO";

            case 5:
                return "MIFARE_PRO_S50";

            case 6:
                return "MIFARE_PRO_S70";

            case 7:
                return "TYPEB";

            case 8:
                return "TYPEB_TCL";

            case 9:
                return "SONY_FELICA";

            case 10:
                return "UNKNOWN_TYPEA";

            default:
                return "";
        }
    }

}*/







/*
package com.amobilepayment.androidunattendeddemo;

import android.app.Fragment;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.pos.device.SDKException;

import com.pos.device.beeper.Beeper;
import com.pos.device.picc.EmvContactlessCard;
import com.pos.device.picc.MifareClassic;
import com.pos.device.picc.PiccReader;
import com.pos.device.picc.PiccReaderCallback;

*/
/**
 * Created by Rasa Vafaie on 2017-09-07.
 *//*


public class FragNFC extends Fragment implements View.OnClickListener{

    private static final String TAG="MYDEBUG";

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view=inflater.inflate(R.layout.frag_nfc, container, false);
        ((Button) view.findViewById(R.id.bStartSearch)).setOnClickListener(this);
        ((Button) view.findViewById(R.id.bStop)).setOnClickListener(this);
        return view;
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        //fitText();
        FragmentsProvider.hideFragment(FragmentsProvider.FRAG_TAG.NFC,getFragmentManager());
    }

    private void fitText(){
        UtilFitText.fitTextButtonsAfterCreatedGroup(getActivity(),
                (Button) getView().findViewById(R.id.bStartSearch),
                (Button) getView().findViewById(R.id.bStop));

        UtilFitText.fitTextViewAfterMeasured(getActivity(), (TextView) getView().findViewById(R.id.tvPICCardStatus));
        //UtilFitText.fitTextViewAfterMeasured(getActivity(), (TextView) getView().findViewById(R.id.tvTimeout));

        UtilFitText.fitTextViewAfterCreatedGroup(getActivity(),
                (TextView) getView().findViewById(R.id.tvUid),
                (TextView) getView().findViewById(R.id.tvApdu),
                (TextView) getView().findViewById(R.id.tvResponse));
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.bStartSearch:
                startPICCard();
                break;

            case R.id.bStop:
                stopPICCard();
                break;
        }
    }

    private void startPICCard() {
        eraseEditTexts();
        try {
            //int timeout=Integer.valueOf((((EditText) getView().findViewById(R.id.etTimeout)).getText().toString()));
            int timeout=30;
            PiccReader.getInstance().reset();
            PiccReader.getInstance().startSearchCard(timeout * 1000, piccReaderCallback);
            setStatus(PICCARD_STATUS.READY_TO_PROXIMATE);
        } catch (SDKException e) {
            e.printStackTrace();
        }
    }

    private void stopPICCard() {
        PiccReader.getInstance().stopSearchCard();
        setStatus(PICCARD_STATUS.STOPPED);
    }

    private PiccReaderCallback piccReaderCallback=new PiccReaderCallback() {

        @Override
        public void onSearchResult(int result, int cardType) {
            Log.d(TAG, "Picc search result is " + result + " ==> "+getStatusDescription(result));
            Log.d(TAG, "The card searched is " + cardType + " ==> "+getCardtypeDescription(cardType));
            if (result == PiccReaderCallback.SUCCESS) {

                Log.d(TAG, "The card searched is " + cardType + " ==> "+getCardtypeDescription(cardType));

                //CPU card
                if ((cardType == PiccReader.MIFARE_PRO) || (cardType == PiccReader.MIFARE_PRO_S50) || (cardType == PiccReader.MIFARE_PRO_S70) || (cardType == PiccReader.MIFARE_DESFIRE)) {
                    Log.d(TAG, "cardType == PiccReader.MIFARE_PRO) || (cardType == PiccReader.MIFARE_PRO_S50) || (cardType == PiccReader.MIFARE_PRO_S70 || || (cardType == PiccReader.MIFARE_DESFIRE)");

                    try {
                        EmvContactlessCard emvContactlessCard = EmvContactlessCard.connect();
                        Log.d(TAG, "after connect");
                        if (emvContactlessCard != null) {

                            Log.d(TAG, "emvContactlessCard != null");

                            try {
                                Beeper.getInstance().beep();
                            } catch (SDKException e1) {
                                e1.printStackTrace();
                            }

                            byte[] uid = emvContactlessCard.getUID();
                            if (uid!=null){
                                Log.d(TAG, UtilUI.bytesToHex(uid));
                                setEditText(R.id.etUID, UtilUI.bytesToHex(uid));
                            }
                            else{
                                Log.d(TAG, "UID is null");
                                setEditText(R.id.etUID, "UID is null");
                            }

                            byte[] apdu = {0x00, (byte) 0xa4, 0x04, 0x00, 0x09, (byte) 0xA0, 0x00, 0x00, 0x00, 0x03, (byte) 0x86, (byte) 0x98, 0x07, 0x01};
                            setEditText(R.id.etAPDU, UtilUI.bytesToHex(apdu));

                            byte[] response = emvContactlessCard.transmit(apdu);
                            if (response!=null){
                                Log.d(TAG, UtilUI.bytesToHex(response));
                                setEditText(R.id.etResponse,UtilUI.bytesToHex(response) );
                            }


                            emvContactlessCard.deactive(new EmvContactlessCard.DeactiveCallback() {// must be called this method if you want to operate the card any more.
                                @Override
                                public void onFinish(int i) {
                                    Log.d(TAG, "Remove Card ok");
                                }
                            });

                        } else {
                            Log.d(TAG, "emvContactlessCard == null ==> Connect card failed!");
                        }
                    } catch (SDKException e) {
                        Log.d(TAG, "My error SDKException "+e.getMessage());
                        e.printStackTrace();
                    }
                } else if ((cardType == PiccReader.MIFARE_ONE_S50) || (cardType == PiccReader.MIFARE_ONE_S70) ) {//Mifare Card
                    Log.d(TAG,"(cardType == PiccReader.MIFARE_ONE_S50) || (cardType == PiccReader.MIFARE_ONE_S70) ");

                    try {
                        MifareClassic mifareClassic = MifareClassic.connect();
                        if (mifareClassic != null) {
                            Log.d(TAG, "Mifare Classic connact success!");
                            byte[] uid = mifareClassic.getUID();
                            if (uid!=null){
                                Log.d(TAG, UtilUI.bytesToHex(uid));
                                setEditText(R.id.etUID, UtilUI.bytesToHex(uid));
                            } else {
                                Log.d(TAG, "Card type "+cardType + " UID is null");
                            }
                            //byte[] info = mifareClassic.getInfo();
                            //if (info!=null){
                            //	Log.d(TAG, StringUtil.hexString(info));
                            //	setEditText(R.id.etResponse, StringUtil.hexString(info));
                            //}
                        } else {
                            Log.d(TAG, "MifareClassic.connect() returns null");
                        }
                    } catch (SDKException e) {
                        e.printStackTrace();
                    }
                }
            }
            else{
                Log.d(TAG, "==> Picc search result is NOT SUCCESS ");
                toastOnUI("==> Picc search result is NOT SUCCESS ");
            }
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    stopPICCard();
                }
            });



        }
    };

    private void setEditText(final int id,final String text){
        if (text==null)
            return;
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ((EditText) getView().findViewById(id)).setText(text);
            }
        });
    }

    private void eraseEditTexts(){
        ((EditText) getView().findViewById(R.id.etUID)).setText("");
        ((EditText) getView().findViewById(R.id.etAPDU)).setText("");
        ((EditText) getView().findViewById(R.id.etResponse)).setText("");
    }

    private void toastOnUI(final String str){
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(getActivity(), str, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void setStatus(PICCARD_STATUS status){
        switch(status){
            case STOPPED:
                //UtilFitText.fitTextView(getActivity(), getResources().getString(R.string.textPICCard), (TextView)  getView().findViewById(R.id.tvPICCardStatus));
                ((TextView)  getView().findViewById(R.id.tvPICCardStatus)).setText(getResources().getString(R.string.textPICCard));
                break;

            case READY_TO_PROXIMATE:
                //UtilFitText.fitTextView(getActivity(), getResources().getString(R.string.textProximity), (TextView)  getView().findViewById(R.id.tvPICCardStatus));
                ((TextView)  getView().findViewById(R.id.tvPICCardStatus)).setText(getResources().getString(R.string.textProximity));
                break;
        }
    }

    private enum PICCARD_STATUS{
        STOPPED,
        READY_TO_PROXIMATE;
    }

    private String getStatusDescription(int status){
        switch (status){
            case 0:
                return "SUCCESS";

            case 1:
                return "USER_CANCEL";

            case 2:
                return "TIMEOUT_ERROR";

            case 3:
                return "UNSUPPORTED_CARD";

            default:
                return "";
        }
    }

    private String getCardtypeDescription(int cardType){
        switch (cardType) {
            case 0:
                return "MIFARE_ONE_S50";

            case 1:
                return "MIFARE_ONE_S70";

            case 2:
                return "MIFARE_ULTRALLIGHT";

            case 3:
                return "MIFARE_DESFIRE";

            case 4:
                return "MIFARE_PRO";

            case 5:
                return "MIFARE_PRO_S50";

            case 6:
                return "MIFARE_PRO_S70";

            case 7:
                return "TYPEB";

            case 8:
                return "TYPEB_TCL";

            case 9:
                return "SONY_FELICA";

            case 10:
                return "UNKNOWN_TYPEA";

            default:
                return "";
        }
    }

}
*/
