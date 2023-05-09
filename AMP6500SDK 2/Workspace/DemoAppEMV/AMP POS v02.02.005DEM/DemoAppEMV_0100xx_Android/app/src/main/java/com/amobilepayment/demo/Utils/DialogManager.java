package com.amobilepayment.demo.Utils;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;

import org.json.JSONArray;

import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.Transaction;

/**
 * Created by Symbol Tabios on 11/10/2017.
 */

public class DialogManager
{
    public interface Listener {
        void onDialogButtonPositiveClick();
        void onDialogButtonNegativeClick();
        void onDialogButtonNeutralClick();
    }

    public static void onCancelAlert(final Context context, String message)
    {
        AlertDialog alertDialog = new AlertDialog.Builder(context).create();
        alertDialog.setTitle("");
        alertDialog.setMessage(message);
        alertDialog.setButton(AlertDialog.BUTTON_POSITIVE,
                context.getResources().getString(R.string.dialog_yes),
                new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        SettingsUtil.triggerBeep(context);

                        if(context instanceof Listener)
                            ((Listener) context).onDialogButtonPositiveClick();
                    }
                });
        alertDialog.setButton(AlertDialog.BUTTON_NEGATIVE,
                context.getResources().getString(R.string.dialog_no),
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        SettingsUtil.triggerBeep(context);

                        if(context instanceof Listener)
                            ((Listener) context).onDialogButtonNegativeClick();
                    }
                });
        alertDialog.show();
    }

    public static void showNotification(final Context context, String message) {
        AlertDialog alertDialog = new AlertDialog.Builder(context).create();
        alertDialog.setTitle("");
        alertDialog.setMessage(message);
        alertDialog.setButton(AlertDialog.BUTTON_NEUTRAL,
                context.getResources().getString(R.string.dialog_ok),
                new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                if(context instanceof Listener)
                    ((Listener) context).onDialogButtonNeutralClick();
            }
        });
        alertDialog.show();

    }

    public static void showAlert(final Context context, String message)
    {
        AlertDialog alertDialog = new AlertDialog.Builder(context).create();
        alertDialog.setTitle("");
        alertDialog.setMessage(message);
        alertDialog.setButton(AlertDialog.BUTTON_NEUTRAL,
                context.getResources().getString(R.string.dialog_ok),
                new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        Transaction.trxCtr = -1;
                        new Transaction(context, Transaction.transID).performTransaction();
                    }
                });
        alertDialog.show();
    }
}
