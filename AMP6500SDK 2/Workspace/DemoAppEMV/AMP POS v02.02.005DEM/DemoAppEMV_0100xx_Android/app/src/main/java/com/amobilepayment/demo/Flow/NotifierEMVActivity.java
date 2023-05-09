package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;

import org.json.JSONArray;

import AmpBaseInterface.AmpBaseInterface;

public class NotifierEMVActivity extends BaseActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_emv_notifier);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        String param = getIntent().getStringExtra(PARAM_KEY);

        TextView prompt = findViewById(R.id.prompt);

        if(param != null && !param.isEmpty()) {
            prompt.setVisibility(View.VISIBLE);
            prompt.setText(param);
        }
    }

    @Override
    public void onBackPressed() {
        // do not allow to manage its own lifecycle

        SettingsUtil.triggerBeep(this);
    }
}