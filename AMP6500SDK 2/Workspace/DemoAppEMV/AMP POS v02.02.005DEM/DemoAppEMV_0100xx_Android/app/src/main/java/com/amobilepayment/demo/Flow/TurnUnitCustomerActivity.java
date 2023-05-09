package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import org.json.JSONArray;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.Storage;

public class TurnUnitCustomerActivity extends BaseActivity {

    private final static String TAG = TurnUnitCustomerActivity.class.getSimpleName();

    private boolean waitForAnyKey = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_turn_unit_customer);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        initialize();
    }

    private void initializeAutoNotifier() {
        int TIMEOUT = 3000; // 3 second

        Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                JSONArray dataToSend = new JSONArray();
                dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
                StatusUtil.notifyCurrentTransaction(dataToSend);
            }
        }, TIMEOUT);

        TextView content  = findViewById(R.id.prompt1);
        content.setText("Turn unit towards the Customer");
    }

    private void initialize() {
        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);

        String sTitle = params[0];
        String sPrompt1 = params[1];
        String sPrompt2 = params[2];
        int sWaitKey = (int)params[3].charAt(0);

        TextView screenTitle = findViewById(R.id.screen_title);
        TextView prompt1 = findViewById(R.id.prompt1);
        TextView prompt2 = findViewById(R.id.prompt2);
        LinearLayout prompt2_layout = findViewById(R.id.press_any_key_layout);
        if(sTitle != null && !sTitle.isEmpty()) {
            screenTitle.setVisibility(View.VISIBLE);
            screenTitle.setText(sTitle);
        }
        if(sPrompt1 != null && !sPrompt1.isEmpty()) {
            prompt1.setVisibility(View.VISIBLE);
            prompt1.setText(sPrompt1);
        }
        if(sPrompt2 != null && !sPrompt2.isEmpty()) {
            prompt2_layout.setVisibility(View.VISIBLE);
            prompt2.setText(sPrompt2);
        }

        if(1 == sWaitKey)
            waitForAnyKey = true;
        else
            initializeAutoNotifier();
    }

    public void onLayoutClick(View view) {
        if(waitForAnyKey) {
            SettingsUtil.triggerBeep(this);

            JSONArray dataToSend = new JSONArray();
            dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
            StatusUtil.notifyCurrentTransaction(dataToSend);
        }
    }

    @Override
    public void onBackPressed() {
        // do not allow

        SettingsUtil.triggerBeep(this);
    }
}
