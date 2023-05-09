package com.amobilepayment.demo.Utils;

import android.content.Context;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.util.Log;

import com.pos.device.printer.PrintCanvas;
import com.pos.device.printer.PrintTask;
import com.pos.device.printer.Printer;
import com.pos.device.printer.PrinterCallback;

public class PrintManager {

    private static PrintManager mInstance ;
    private PrintTask mPrintTask;
    private PrintCanvas mPrintCanvas;
    private Paint mPaint;
    private Printer mPrinter;
    private static Context mContext ;
    private float mTextSize = 17F;
    private boolean isStart = true;

    private int mLineNumber = 1;
    private int mStartPos = 0;
    private int mEndPos = 0;

    public PrintManager(){
        mPrintTask = new PrintTask();
        mPrintCanvas = new PrintCanvas();
        mPaint = new Paint();
        mPrinter = new Printer();
    }

    public static PrintManager getInstance(Context c){
        mContext = c ;
        if(null == mInstance){
            mInstance = new PrintManager();
        }
        return mInstance ;
    }

    public int DoCheckPrinterStatus() {
        return mPrinter.getStatus();
    }

    public static Printer getPrinterObject() {
        return Printer.getInstance();
    }

    public int printData() {

        mPrintTask.setPrintCanvas(mPrintCanvas);

        int ret = mPrinter.getStatus();
        if (ret != Printer.PRINTER_OK)
            return ret;

        mPrinter.startPrint(mPrintTask, new PrinterCallback() {
            @Override
            public void onResult(int i, PrintTask printTask) {
            }
        });
        return ret;
    }

    private int checkPrinterStatus() {

        long t0 = System.currentTimeMillis();
        int ret ;

        while (true) {

            if (System.currentTimeMillis() - t0 > 30000) {
                ret = -1 ;
                break;
            }

            ret = mPrinter.getStatus();

            if (ret == Printer.PRINTER_OK)
                break;
            else if (ret == Printer.PRINTER_STATUS_PAPER_LACK)
                break;
            else if (ret == Printer.PRINTER_STATUS_BUSY) {
                try {
                    Thread.sleep(200);
                }
                catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            else
                break;
        }
        return ret;
    }

    public void setFontSize(int size){
        switch (size) {
            case 0 : break;
            case 1 : mTextSize = 16F; break;
            case 2 : mTextSize = 22F; break;
            case 3 : mTextSize = 30F; break;
            default: break;
        }
        mPaint.setTextSize(mTextSize);
    }

    public void setTypeface(int typeface) {
        mPaint.setTypeface(Typeface.defaultFromStyle(typeface));
    }

    public void printLine(int y){
        String line = "----------------------------------------------------------------";
        setFontSize(1);
        setTypeface(Typeface.BOLD);
        drawText(line, 0, y);
    }

    public void drawText(String strText, int x, int y) {
        mPaint.setTextSize(mTextSize);
        Log.d("PrintManager", "text="+strText+" y="+y);
        setX(x);
        setY(y);
        mPrintCanvas.drawText(strText, mPaint);
        isStart = false;
    }

    public void nextLine() {
        mPrintCanvas.drawText("\n", mPaint);
    }

    public int getStringSize(String text) {return PrintUtils.getLimit(mPaint, text);}

    public void setX(int x) {
        mPrintCanvas.setX(x);
    }

    public int getPosition(String text, int position) {
        return PrintUtils.getPosition(mPaint, text, position); }

    public void setY(int y) {

        Log.d("PrintManager", "mLineNumber="+mLineNumber+" y="+y);

        if(isStart)
        {
           mStartPos = 0;
           mEndPos = (int)mTextSize*y;
        }
        else
        {
            if(mLineNumber != y) {
                if(y-mLineNumber == 1)
                    mStartPos = mEndPos;
                else
                    mStartPos = mEndPos + ((int) mTextSize * (y - mLineNumber));

                mEndPos = mStartPos + ((int) mTextSize);
                mLineNumber = y;
            }
        }

        Log.d("PrintManager", "startPos="+mStartPos+" endPos="+mEndPos);
        mPrintCanvas.setY(mStartPos);
    }

}
