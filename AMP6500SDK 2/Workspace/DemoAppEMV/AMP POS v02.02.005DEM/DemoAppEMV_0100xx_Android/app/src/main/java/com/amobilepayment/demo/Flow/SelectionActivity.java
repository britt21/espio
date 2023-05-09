package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.JSONArray;


import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.Storage;

public class SelectionActivity extends BaseActivity {

    private static String TAG = SelectionActivity.class.getSimpleName();

    private RecyclerView mRecyclerView;
    private RecyclerView.LayoutManager mLayoutManager;
    private RecyclerView.Adapter mAdapter;
    private JSONArray screenItems = new JSONArray();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_selection);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        mScreenType = getIntent().getIntExtra(ARG_KEY, 0);

        switch(mScreenType) {
            case SCREEN_THREE_BUTTON_SELECTION:
                initializeAsThreeButtonSelection();
                break;
            case SCREEN_CARD_TYPE_SELECTION:
                initializeAsCardTypeSelection();
                break;
            default:
                initializeAsDefaultSelection();
                break;
        }

        mRecyclerView = findViewById(R.id.recycler_view);

        // use this setting to improve performance if you know that changes
        // in content do not change the layout size of the RecyclerView
        mRecyclerView.setHasFixedSize(true);

        mLayoutManager = new LinearLayoutManager(this);
        mRecyclerView.setLayoutManager(mLayoutManager);

        // specify an adapter (see also next example)
        mAdapter = new SelectionAdapter(screenItems, this);
        ((SelectionAdapter)mAdapter).setScreenType(mScreenType);
        mRecyclerView.setAdapter(mAdapter);
    }

    private void initializeAsThreeButtonSelection() {
        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);

        String sTitle = params[0];
        String sPrompt1 = params[1];
        String sPrompt2 = params[2];
        String nSelectionButtons = params[3];
        String sBtnMsg1 = params[4];
        String sBtnMsg2 = params[5];
        String sBtnMsg3 = params[6];
        String iTimeout = params[7];
        String iBeep = params[8];

        TextView screenTitle = findViewById(R.id.screen_title);
        TextView prompt1 = findViewById(R.id.prompt1);
        TextView prompt2 = findViewById(R.id.prompt2);
        if(sTitle != null && !sTitle.isEmpty()) {
            screenTitle.setVisibility(View.VISIBLE);
            screenTitle.setText(sTitle);
        }
        if(sPrompt1 != null && !sPrompt1.isEmpty()) {
            prompt1.setVisibility(View.VISIBLE);
            prompt1.setText(sPrompt1);
            View line_divider = findViewById(R.id.line_divider);
            line_divider.setVisibility(View.VISIBLE);
        }
        if(sPrompt2 != null && !sPrompt2.isEmpty()) {
            prompt2.setVisibility(View.VISIBLE);
            prompt2.setText(sPrompt2);
            View line_divider = findViewById(R.id.line_divider);
            line_divider.setVisibility(View.VISIBLE);
        }

        if(sBtnMsg1 != null && !sBtnMsg1.isEmpty()) {
            screenItems.put(sBtnMsg1);
        }
        if(sBtnMsg2 != null && !sBtnMsg2.isEmpty()) {
            screenItems.put(sBtnMsg2);
        }
        if(sBtnMsg3 != null && !sBtnMsg3.isEmpty()) {
            screenItems.put(sBtnMsg3);
        }
        if(iTimeout != null && !iTimeout.isEmpty()) {
            startActivityTimeOut(Long.valueOf(iTimeout));
        }

        if(iBeep != null && !iBeep.isEmpty()) {
            int type = Integer.valueOf(iBeep);
            SettingsUtil.triggerBeepType(this, type);
        }
    }

    private void initializeAsCardTypeSelection() {
        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);

        String sTitle = params[0];
        TextView screenTitle = findViewById(R.id.screen_title);
        if(sTitle != null && !sTitle.isEmpty()) {
            screenTitle.setVisibility(View.VISIBLE);
            screenTitle.setText(sTitle);
        }

        // TODO: we are disregarding the default selection for now (last string param)
        for(int i=1; i<params.length; i++) {
            screenItems.put(params[i]);
        }
    }

    private void initializeAsDefaultSelection() {
        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);

        // screen_title is hidden
        // prompts 1 and 2 are hidden

        // fill-up the list
        for(String s : params) {
            screenItems.put(s);
        }
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
        isUserDone = true;
        hasTimedOut = true;
        super.onDialogButtonPositiveClick();
    }
}
