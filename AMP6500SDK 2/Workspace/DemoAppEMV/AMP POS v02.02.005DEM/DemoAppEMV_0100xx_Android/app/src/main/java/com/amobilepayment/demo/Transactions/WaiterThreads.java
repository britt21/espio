package com.amobilepayment.demo.Transactions;

import android.content.Context;
import android.util.Log;

import org.json.JSONArray;

import AmpBaseInterface.AmpBaseInterface;
import AmpBaseInterface.AmpBaseCB;
import AmpEmvL2Android.AmpEmvCB;

import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.service.BaseChannel;

public class WaiterThreads {

    private String TAG = getClass().getSimpleName();

    private static WaiterThreads instance;
    private boolean processing = false;
    ClientWaiterThread clientWaiterThread;
    private Object objectLock = new Object();
    private Context context;
    TransactionContract.TransactionType transactionType;

    private WaiterThreads() {
    }

    public static WaiterThreads getInstance() {
        if(instance == null) {
            synchronized (WaiterThreads.class) {
                if(instance == null) {
                    instance = new WaiterThreads();
                }
            }
        }
        return instance;
    }

    public WaiterThreads setContext(Context ctx) {
        context = ctx;
        return this;
    }

    public WaiterThreads setTransactionType(TransactionContract.TransactionType transactionType) {
        this.transactionType = transactionType;
        return this;
    }

    public void startProcess() {
        if(processing == false) {
            processing = true;

            // start transaction flow controlled by .cpp codes
            new ServerWaiterThread().start();

            // start waiting for replies from client UIs
            clientWaiterThread = new ClientWaiterThread();
            clientWaiterThread.start();
        }
    }

    public void endProcess() {
        synchronized (objectLock) {
            if (processing) {
                processing = false;
                transactionType = null;

                // notify still so we won't leave it hanging around, $clientReply is null anyways
                objectLock.notify();
                clientWaiterThread = null;
            }
        }
    }

    JSONArray clientReply = null;

    public void notifyWaiters(JSONArray value) {
        synchronized (objectLock) {
            clientReply = value;
            objectLock.notify();
        }
    }

    private class ClientWaiterThread extends Thread {
        @Override
        public void run() {
            synchronized (objectLock) {
                Log.d(TAG, "ClientWaiterThread [START]");
                while (processing) {
                    try {
                        objectLock.wait();
                        if(clientReply != null) AmpBaseCB.informListener(clientReply);
                        clientReply = null;
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                Log.d(TAG, "ClientWaiterThread [END]");
            }
        }
    }

    private class ServerWaiterThread extends Thread {

        public ServerWaiterThread() {
            BaseChannel.getInstance().setContext(context);
            AmpEmvCB.GetInstance().SetContext(context);
        }

        @Override
        public void run() {
            Log.d(TAG, "ServerWaiterThread [START]");
            int status = AmpBaseInterface.PerformTransaction(transactionType.getTransactionId());
            StatusUtil.setCurrentTransactionStatus(status);
            Log.d(TAG, "ServerWaiterThread [END] ");
        }
    }
}
