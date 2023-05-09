package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.os.Handler;
import android.widget.ImageView;
import android.widget.TextView;

import org.json.JSONArray;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;

public class NotificationActivity extends BaseActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_notification);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        mParameters = getIntent().getStringArrayExtra(PARAM_KEY);

        TextView notification = findViewById(R.id.tv_notification);
        notification.setText("notification activity");

        Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                JSONArray dataToSend = new JSONArray();
                dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
                StatusUtil.notifyCurrentTransaction(dataToSend);
            }
        }, 2000);
    }

    @Override
    public void onBackPressed() {
        // do not allow to manage its own lifecycle

        SettingsUtil.triggerBeep(this);
    }
}