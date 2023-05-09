package com.amobilepayment.demo.Utils;

import com.amobilepayment.demo.Main.MenuActivity;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class StatusUtil {
    final static int TYPE_INT = 0;
    final static int TYPE_STR = 1;
    final static int TYPE_LNG = 2;

    public final static int AMP_ENTER       =  1;       // Return for ENTER key press
    public final static int AMP_SUCCESS     =  0;       // Generic SUCCESS
    public final static int AMP_ERROR       = -1;       // Generic ERROR
    public final static int AMP_FAILURE     = AMP_ERROR;// Generic FAILURE
    public final static int AMP_TIMEOUT     = -2;       // Return for TIMEOUT expires
    public final static int AMP_CANCEL      = -3;       // Return for CANCEL key press
    public final static int AMP_CLEAR       = -4;       // Return for BACKSPACE key press
    public final static int AMP_BACKSPACE   = AMP_CLEAR;

    /* Keyboard Codes */
    public final static int AMPKEY_POWER	= 0xF00A;
    public final static int AMPKEY_UP		= 0xF002;
    public final static int AMPKEY_DOWN		= 0xF003;
    public final static int AMPKEY_LEFT		= AMPKEY_UP;
    public final static int AMPKEY_RIGHT	= AMPKEY_DOWN;
    public final static int AMPKEY_MENU		= 0xF204;
    public final static int AMPKEY_FUNC		= 0xF202;
    public final static int AMPKEY_ALPHA	= 0xF201;
    public final static int AMPKEY_ENTER	= 0x000D;
    public final static int AMPKEY_CLEAR	= 0x0008;
    public final static int AMPKEY_CANCEL	= 0x001B;
    public final static int AMPKEY_0		= 0x0030;
    public final static int AMPKEY_1		= 0x0031;
    public final static int AMPKEY_2		= 0x0032;
    public final static int AMPKEY_3		= 0x0033;
    public final static int AMPKEY_4		= 0x0034;
    public final static int AMPKEY_5		= 0x0035;
    public final static int AMPKEY_6		= 0x0036;
    public final static int AMPKEY_7		= 0x0037;
    public final static int AMPKEY_8		= 0x0038;
    public final static int AMPKEY_9		= 0x0039;

    public final static int AMPKEY_MENU1	= 0x0081;
    public final static int AMPKEY_MENU2	= 0x0082;
    public final static int AMPKEY_MENU3	= 0x0083;
    public final static int AMPKEY_MENU4	= 0x0084;
    public final static int AMPKEY_MENU5	= 0x0085;
    public final static int AMPKEY_MENU6	= 0x0086;

    public static JSONObject prepareStatusObject(int status) {
        JSONObject data = new JSONObject();
        try {
            data.put("id", "STATUS");
            data.put("type", TYPE_INT);
            data.put("value", status);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return data;
    }

    public static void notifyCurrentTransaction(JSONArray data) {
        MenuActivity.currentTransaction.notifyTransaction(data);
    }

    public static void endCurrentTransaction() {
        MenuActivity.currentTransaction.endTransaction();
    }

    public static void setCurrentTransactionStatus(int status) {
        MenuActivity.currentTransaction.setTransactionStatus(status);
    }
}
