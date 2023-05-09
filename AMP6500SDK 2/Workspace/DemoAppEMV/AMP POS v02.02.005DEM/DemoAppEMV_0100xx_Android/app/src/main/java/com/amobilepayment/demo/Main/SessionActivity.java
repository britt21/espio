package com.amobilepayment.demo.Main;

import android.app.ActivityManager;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

import AmpBaseInterface.AmpBaseInterface;

public class SessionActivity extends AppCompatActivity {

    private final static String TAG = SessionActivity.class.getSimpleName();

    private Handler mHandler;
    private Runnable mRunnable;

    // TODO: this should be based on "TERMINAL.TIMEOUT.IDLE"
    private static final int TIMEOUT = 60000; // 30 seconds

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mHandler = new Handler();
        mRunnable = new Runnable() {
            @Override
            public void run() {
                logOff();
            }
        };
        startHandler();
    }

    @Override
    protected void onStart() {
        super.onStart();
        restartTimeOutHandler();
    }

    @Override
    protected void onStop() {
        super.onStop();
        stopHandler();
    }

    @Override
    public void onUserInteraction() {
        super.onUserInteraction();
        // user is still active, reset the session timer
        restartTimeOutHandler();
    }

    protected void stopHandler() {
        mHandler.removeCallbacks(mRunnable);
    }
    protected void startHandler() {
        mHandler.postDelayed(mRunnable, TIMEOUT);
    }

    protected void restartTimeOutHandler() {
        stopHandler();
        startHandler();
    }

    protected void logOff() {
        Intent intent = new Intent(getApplicationContext(), LoginActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
        startActivity(intent);
    }
}
