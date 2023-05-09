package com.amobilepayment.demo.Utils;

import android.graphics.Paint;
import android.util.Log;

/**
 * Created by Symbol Tabios on 09/01/2018.
 */

public class PrintUtils {

    public static int getLimit(Paint paint, String text) {
        return (Math.round(paint.measureText(text)));
    }

    public static int getPosition(Paint paint, String text, int position) {
        if(position == 1) // center
            return (370-getLimit(paint, text))/2;
        else if (position == 2) // right
            return (370-getLimit(paint, text));
        else
            return 0;
    }

}
