package AmpBaseInterface;

import android.content.Context;
import amp.sdk.lib.IAmpCmpntCB;

/**
 * Created by Symbol Tabios on 29/01/2018.
 */

public class AmpBaseInterface {

    public static char FLAGTRUE = 'Y';
    public static char FLAGFALSE = 'N';

    public native static void Initialize(AmpBaseCBIF obj, IAmpCmpntCB AMPCmpntobj, Context context);

    public native static int PerformTransaction(long transID);

}

