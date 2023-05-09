package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.JSONArray;


import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.Storage;

public class GenericListActivity extends BaseActivity {

    private static String TAG = GenericListActivity.class.getSimpleName();

    private RecyclerView mRecyclerView;
    private RecyclerView.LayoutManager mLayoutManager;
    private RecyclerView.Adapter mAdapter;

    private final static String SETTINGS_SHOW_OPERATORS = "SHOW_OPERATORS";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_generic_list);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        mRecyclerView = findViewById(R.id.recycler_view);

        // this activity can be started either from MenuActivity or SettingsActivity;
        // if started from SettingsActivity, look for DataString in Intent
        // else look for IntExtra from Intent
        String intentData = getIntent().getDataString();
        if(intentData != null)
            switch(intentData) {
                case SETTINGS_SHOW_OPERATORS:
                    Log.d(TAG, "request show operators from settings");
                    mScreenType = SCREEN_SETTINGS_SHOW_OPERATORS;
                    break;
            }
        if(mScreenType == 0)
            mScreenType = getIntent().getIntExtra(ARG_KEY, SCREEN_CARD_PRESENT);
        mParameters = getIntent().getStringArrayExtra(PARAM_KEY);

        String screenTitle;
        JSONArray screenItems = new JSONArray();

        switch (mScreenType) {
//            case SCREEN_SETTINGS_SHOW_OPERATORS:
//                screenTitle = AmpBaseInterface.GetScrMsg("MENU.DEVICESETTINGS.OPERMGT.LIST");
//                screenItems.put("TODO");
//                screenItems.put("TODO");
//                break;
            case SCREEN_PROMPT_ENTRY_CANCEL:
                screenTitle = mParameters[0];
                screenItems.put("YES");
                screenItems.put("NO");
                break;
//            case SCREEN_ACCT_SELECT:
//                screenTitle = AmpBaseInterface.GetScrMsg("ENTEREXPIRYDATE");
//                screenItems.put(AmpBaseInterface.GetScrMsg("ACCOUNTTYPE.CHEQUING"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("ACCOUNTTYPE.SAVINGS"));
//                break;
//            case SCREEN_SELECT_3_RECALL:
//                screenTitle = AmpBaseInterface.GetScrMsg("SELECTTRANS");
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.TRANS.VOID"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.TRANS.COMPLETION") +
//                        "/" +
//                        AmpBaseInterface.GetScrMsg("MENU.MAIN.REPRINT"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.MAIN.REPRINT"));
//                break;
//            case SCREEN_SELECT_2_RECALL:
//                screenTitle = AmpBaseInterface.GetScrMsg("SELECTTRANS");
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.TRANS.VOID"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.MAIN.REPRINT"));
//                break;
//            case SCREEN_SELECT_ECI:
//            case SCREEN_SELECT_BILLPAYT:
//                screenTitle = AmpBaseInterface.GetScrMsg("SELECTTRANS");
//                screenItems.put(AmpBaseInterface.GetScrMsg("ECITYPEONETIME"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("ECITYPERECURRING"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("ECITYPEINSTALLMENT"));
//                break;
//            case SCREEN_VOID_SELECT_HOW:
//                screenTitle = AmpBaseInterface.GetScrMsg("MENU.TRANS.VOID");
//                // flow controller expects the following:
//                //      invoice   = 1
//                //      trace     = 2
//                //      reference = 3
//                //      auth      = 4
//                //      card #    = 5
//                // in adapter, we start the index at 1 instead of 0
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.TRANS.VOID.INVOICENUM"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.TRANS.VOID.TRACENUM"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.TRANS.VOID.RRN"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.TRANS.VOID.AUTHNUM"));
//                screenItems.put(AmpBaseInterface.GetScrMsg("MENU.TRANS.VOID.CARDNUM"));
//                break;
//            case SCREEN_CARD_TYPE_SELECT:
//                screenTitle = AmpBaseInterface.GetScrMsg("SELECTCARDTYPE");
//                for(String s : mParameters) {
//                    screenItems.put(s);
//                }
//                break;
            case SCREEN_CARD_PRESENT:
            case SCREEN_INVOICE_CONFIRM:
            default:
                screenTitle = "Card Present?";
                // flow controller expects NO == 0, YES == 1
                screenItems.put("NO");
                screenItems.put("YES");
                break;
        }

        TextView tvTitle = findViewById(R.id.screen_title);
        tvTitle.setText(screenTitle);

        // use this setting to improve performance if you know that changes
        // in content do not change the layout size of the RecyclerView
        mRecyclerView.setHasFixedSize(true);

        mLayoutManager = new LinearLayoutManager(this);
        mRecyclerView.setLayoutManager(mLayoutManager);

        // specify an adapter (see also next example)
        mAdapter = new GenericListAdapter(screenItems, this);
        ((GenericListAdapter)mAdapter).setScreenType(mScreenType);
        mRecyclerView.setAdapter(mAdapter);
    }

    @Override
    public void onBackPressed() {
        SettingsUtil.triggerBeep(this);

        cancelTransaction();
    }

    private void cancelTransaction() {
        DialogManager.onCancelAlert(this,
                /*AmpBaseInterface.GetScrMsg("DIALOGS.SUREWANTTOCANCEL")*/ "Are you sure you want to cancel?");
    }

    @Override
    public void onDialogButtonPositiveClick() {
        if(mScreenType == SCREEN_SETTINGS_SHOW_OPERATORS) {
            Log.d(TAG, "TODO: settings operations not yet supported");
            finish();
            return;
        }
        else
            super.onDialogButtonPositiveClick();
    }
}
