package com.amobilepayment.demo.Transactions;

import android.app.AlertDialog;
import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import java.io.File;
import java.util.ArrayList;

import org.json.JSONArray;

public class Transaction {

    private final static String TAG = Transaction.class.getSimpleName();

    public interface Listener {
        void onTransactionEnd(int status);
    }

    ArrayList<Listener> mListenersList = new ArrayList<>();

    public static int trxCtr = 0;
    public static long transID;
    public static long trxApprovalCode;
    public static double baseAmount = 0;
    public static int PINType = 0;
    public static String PAN;

    public final static int DEFAULT_TRANSACTION_STATUS = 1000;
    private int mTransactionStatus = DEFAULT_TRANSACTION_STATUS;
    private Context context;

    public static String AID;
    public static String TVR;
    public static String IAD;
    public static String TSI;
    public static String ARC;

    public static int CardEntryMode = 0;

    public Transaction(Context context, long transID) {
        this.context = context;
        Transaction.transID = transID;
    }

    // SettingsActivity is the only one listening
    public void registerListener(Listener listener) {
        mListenersList.add(listener);
    }

    // SettingsActivity is the only one listening
    public void unregisterListener(Listener listener) {
        mListenersList.remove(listener);
    }

    public void setTransactionStatus(int status) {
        mTransactionStatus = status;

        // notify the SettingsActivity
        Handler handler = new Handler(Looper.getMainLooper());
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                for(Listener l : mListenersList) {
                    l.onTransactionEnd(mTransactionStatus);
                }
            }
        };
        handler.postDelayed(runnable, 300);
    }

    public int getTransactionStatus() {
        return mTransactionStatus;
    }

    public void notifyTransaction(JSONArray value) {
        Log.d(TAG, "[START] notifyTransaction string="+value+" transID="+transID);
        WaiterThreads.getInstance().notifyWaiters(value);
    }

    public void endTransaction() {
        WaiterThreads.getInstance().endProcess();
    }

    public void performTransaction() {
        Log.d(TAG, "[START] performTransaction");

        TransactionContract.TransactionType transactionType = TransactionContract.determineTransactionType(transID);

        Log.d(TAG, "transactionType "+transactionType);
        switch (transactionType) {

            case TRANS_SALE:
                // start legacy codes
                WaiterThreads.getInstance()
                    .setContext(context)
                    .setTransactionType(transactionType)
                    .startProcess();
                break;
            default:
                AlertDialog.Builder builder = new AlertDialog.Builder(context);
                builder.setMessage("Transaction not supported");
                builder.setPositiveButton("OK", null);
                AlertDialog dialog = builder.create();
                dialog.show();
                break;

        }

        Log.d(TAG, "[END] performTransaction");
    }
}
