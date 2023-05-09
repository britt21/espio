package com.amobilepayment.androidunattendeddemo;

import android.app.Activity;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;

import com.pos.device.SDKException;
import com.pos.device.SDKManager;
import com.pos.device.SDKManagerCallback;
import com.pos.device.beeper.Beeper;
import com.pos.device.config.DevConfig;
import com.pos.device.led.Led;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        if (savedInstanceState == null){
            FragmentManager manager=getFragmentManager();
            FragmentTransaction transaction=manager.beginTransaction();
            transaction.add(R.id.fragContainer, new FragHomePage(),FragmentsProvider.FRAG_TAG.HOMEPAGE.name());
            transaction.add(R.id.fragContainer, new FragNFC(),FragmentsProvider.FRAG_TAG.NFC.name());
            transaction.add(R.id.fragContainer, new FragMagnetic(),FragmentsProvider.FRAG_TAG.MAGNETIC.name());
            transaction.add(R.id.fragContainer, new FragICCard(),FragmentsProvider.FRAG_TAG.IC_CARD.name());
            transaction.add(R.id.fragContainer, new FragSerialPort(),FragmentsProvider.FRAG_TAG.SERIAL_PORT.name());
            transaction.commit();
        }


        SDKManager.init(this,sdkManagerCallback);

    }

    private SDKManagerCallback sdkManagerCallback=new SDKManagerCallback() {
        @Override
        public void onFinish() {
            try {
                Beeper.getInstance().beep(1600,1000);
                Led.setLight(Led.LED_NFC_1,Led.LED_ON);
                Led.setLight(Led.LED_NFC_2,Led.LED_ON);
                Led.setLight(Led.LED_NFC_3,Led.LED_ON);
                Led.setLight(Led.LED_NFC_4,Led.LED_ON);
            } catch (SDKException e) {
                e.printStackTrace();
            }
        }
    };

    public void bHomePage(View view){
        FragmentsProvider.displayFragment(FragmentsProvider.FRAG_TAG.HOMEPAGE,getFragmentManager());
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        SDKManager.release();
        Led.setLight(Led.LED_NFC_1,Led.LED_OFF);
        Led.setLight(Led.LED_NFC_2,Led.LED_OFF);
        Led.setLight(Led.LED_NFC_3,Led.LED_OFF);
        Led.setLight(Led.LED_NFC_4,Led.LED_OFF);
    }
}
