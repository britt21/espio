package com.amobilepayment.androidunattendeddemo;

import android.app.Fragment;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;
import com.pos.device.uart.SerialPort;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

/**
 * Created by Rasa Vafaie on 2017-09-11.
 */

public class FragSerialPort extends Fragment implements View.OnClickListener {

    private Handler handler=new Handler(Looper.getMainLooper());
    private Executor singleThreadExecutor;

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view= inflater.inflate(R.layout.frag_serialport,container,false);
        view.findViewById(R.id.bSerialPortSendData).setOnClickListener(this);
        return view;
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        FragmentsProvider.hideFragment(FragmentsProvider.FRAG_TAG.SERIAL_PORT,getFragmentManager());

        singleThreadExecutor=Executors.newSingleThreadExecutor();

        Thread receivedDataThread=new Thread(receivedRunnable);
        receivedDataThread.start();
    }

    @Override
    public void onClick(View v) {
        switch(v.getId()){
            case R.id.bSerialPortSendData:
                sendData();
                break;
        }
    }

    Runnable receivedRunnable=new Runnable() {
        @Override
        public void run() {
            SerialPort serialPort = SerialPort.getInstance(SerialPort.DEFAULT_CFG, SerialPort.TTY_USB0); //SerialPort.TTY_S3
            if (serialPort == null) {
                Handler handler=new Handler(Looper.getMainLooper());
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(getActivity(),"Serial port is null !!!",Toast.LENGTH_SHORT).show();
                    }
                });
                Log.e("MYDEBUG", "serialPort == null");
                return;
            }
            InputStream is = serialPort.getInputStream();
            if (is==null){
                Handler handler=new Handler(Looper.getMainLooper());
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(getActivity(),"Input stream is null !!!",Toast.LENGTH_SHORT).show();
                    }
                });
                Log.e("MYDEBUG", "inputstream == null");
                return;
            }

            final byte[] buffer=new byte[1024];
            int count;
            while(true){
                try {
                    count=is.read(buffer);
                    if (count>0){
                        appendReceivedData(Arrays.copyOfRange(buffer,0,count));
                    }
                } catch (IOException e) {
                    Log.e("MYDEBUG", "Serial port receivedRunnable IOException "+e.getMessage());
                    e.printStackTrace();
                }
            }
        }
    };

    private void appendReceivedData(final byte[] receivedData){
        handler.post(new Runnable() {
            @Override
            public void run() {
                ( (TextView) getView().findViewById(R.id.tvSerialPortReceivedData)).append(UtilUI.showAsHex(receivedData)+"\n");
                ( (ScrollView) getView().findViewById(R.id.svReceivedData)).post(new Runnable() {
                    public void run() {
                        ( (ScrollView) getView().findViewById(R.id.svReceivedData)).fullScroll(( (ScrollView) getView().findViewById(R.id.svReceivedData)).FOCUS_DOWN);
                    }
                });
            }
        });
    }

    private void sendData(){
        final String writeData= ((EditText) getView().findViewById(R.id.etWriteSerialPort)).getText().toString();
        if (writeData!=null && writeData.length()>0){
            singleThreadExecutor.execute(new Runnable() {
                @Override
                public void run() {
                    SerialPort serialPort = SerialPort.getInstance(SerialPort.DEFAULT_CFG, SerialPort.TTY_USB0);
                    Log.d("MYDEBUG","serial port get Instance");

                    if (serialPort == null) {
                        Log.e("MYDEBUG", "serialPort == null");
                        return;
                    }
                    OutputStream os = serialPort.getOutputStream();
                    if (os==null){
                        Log.e("MYDEBUG", "OutputStream == null");
                        return;
                    }

                    try {
                        os.write(writeData.getBytes());
                        os.flush();
                    } catch (IOException e) {
                        Log.e("MYDEBUG", "Serial port sendRunnable IOException "+e.getMessage());
                        e.printStackTrace();
                    }
                }
            });
        }
    }
}
