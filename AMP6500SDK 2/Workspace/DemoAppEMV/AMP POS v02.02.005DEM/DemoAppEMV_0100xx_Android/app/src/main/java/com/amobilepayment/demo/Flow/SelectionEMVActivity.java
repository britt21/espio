package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.DialogManager;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.Storage;

import org.json.JSONArray;

import java.util.ArrayList;

import AmpBaseInterface.AmpBaseInterface;

public class SelectionEMVActivity extends BaseActivity {

    private static String TAG = SelectionEMVActivity.class.getSimpleName();

    private RecyclerView mRecyclerView;
    private RecyclerView.LayoutManager mLayoutManager;
    private RecyclerView.Adapter mAdapter;
    private JSONArray screenItems = new JSONArray();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_emv_selection);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        initializeAsDefaultSelection();

        mRecyclerView = findViewById(R.id.recycler_view);

        // use this setting to improve performance if you know that changes
        // in content do not change the layout size of the RecyclerView
        mRecyclerView.setHasFixedSize(true);

        mLayoutManager = new LinearLayoutManager(this);
        mRecyclerView.setLayoutManager(mLayoutManager);

        // specify an adapter (see also next example)
        mAdapter = new SelectionEMVAdapter(screenItems, this);
        mRecyclerView.setAdapter(mAdapter);
    }

    private void initializeAsDefaultSelection() {
        ArrayList<String> params = getIntent().getStringArrayListExtra(PARAM_KEY);

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


    }
}
