package com.amobilepayment.demo.Flow;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
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

public class NotifierActivity extends BaseActivity {

    private final static String TAG = NotifierActivity.class.getSimpleName();

    private boolean buttonClicked = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_notifier);

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, IMAGE_HEADER_FILENAME);

        mScreenType = getIntent().getIntExtra(ARG_KEY, 0);

        String[] params = getIntent().getStringArrayExtra(PARAM_KEY);

        String title = params[0];
        String sPrompt1 = params[1];
        String sPrompt2 = params[2];
        String sPrompt3 = params[3];
        String sPrompt4 = params[4];
        String sBeep    = params[5];

        // TODO: sDelay should be different from sTimeout
        // sDelay is meant for the time before sending AMP_SUCCESS back to CPP
        // sTimeout is meant for timeout while waiting for user button press in case of
        //      SCREEN_NOTIFIER_ENTER_CANCEL and SCREEN_NOTIFIER_WITH_CANCEL screens
        String sDelay = params[6];

        // for SCREEN_NOTIFIER_ENTER_CANCEL and SCREEN_NOTIFIER_WITH_CANCEL screens,
        // the 7th param is actually the timeout
        String sTimeout = null;
        if(mScreenType == SCREEN_NOTIFIER_ENTER_CANCEL ||
                mScreenType == SCREEN_NOTIFIER_WITH_CANCEL) sTimeout = params[6];

        TextView screenTitle = findViewById(R.id.screen_title);
        TextView prompt1 = findViewById(R.id.prompt1);
        TextView prompt2 = findViewById(R.id.prompt2);
        TextView prompt3 = findViewById(R.id.prompt3);
        TextView prompt4 = findViewById(R.id.prompt4);

        if(title != null && !title.isEmpty()) {
            screenTitle.setVisibility(View.VISIBLE);
            screenTitle.setText(title);
        }
        if(sPrompt1 != null && !sPrompt1.isEmpty()) {
            prompt1.setVisibility(View.VISIBLE);
            prompt1.setText(sPrompt1);
        }
        if(sPrompt2 != null && !sPrompt2.isEmpty()) {
            prompt2.setVisibility(View.VISIBLE);
            prompt2.setText(sPrompt2);
        }
        if(sPrompt3 != null && !sPrompt3.isEmpty()) {
            prompt3.setVisibility(View.VISIBLE);
            prompt3.setText(sPrompt3);
        }
        if(sPrompt4 != null && !sPrompt4.isEmpty()) {
            prompt4.setVisibility(View.VISIBLE);
            prompt4.setText(sPrompt4);
        }
        if(sPrompt4 != null && !sPrompt4.isEmpty()) {
            prompt4.setVisibility(View.VISIBLE);
            prompt4.setText(sPrompt4);
        }

        // for SCREEN_NOTIFIER_ENTER_CANCEL screen, the 7th param is actually the timeout
        if(mScreenType == SCREEN_NOTIFIER_ENTER_CANCEL ||
                mScreenType == SCREEN_NOTIFIER_WITH_CANCEL) {
            if(sTimeout != null && !sTimeout.isEmpty()) {
                startActivityTimeOut(Long.valueOf(sTimeout));
            }
        }
        else {
            if (sDelay != null && !sDelay.isEmpty()) {
                int delay = Integer.valueOf(sDelay);
                if(delay <= 0) delay = DEFAULT_TIMEOUT;
                Handler handler = new Handler();
                handler.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        JSONArray dataToSend = new JSONArray();
                        dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
                        StatusUtil.notifyCurrentTransaction(dataToSend);
                    }
                }, delay);
            }
        }

        switch(mScreenType) {
            case SCREEN_NOTIFIER_ENTER_CANCEL: {
                LinearLayout buttonsLayout = findViewById(R.id.buttons_layout);
                buttonsLayout.setVisibility(View.VISIBLE);
                View buttons_spacer = findViewById(R.id.buttons_spacer);
                buttons_spacer.setVisibility(View.VISIBLE);

                Button buttonOk = findViewById(R.id.btnenter);
                Button buttonCancel = findViewById(R.id.btncancel);
                buttonOk.setText("OK");
                buttonCancel.setText("CANCEL");
                break;
            }
            case SCREEN_NOTIFIER_WITH_CANCEL: {
                LinearLayout buttonsLayout = findViewById(R.id.buttons_layout);
                buttonsLayout.setVisibility(View.GONE);
                LinearLayout cancelLayout = findViewById(R.id.cancel_layout);
                cancelLayout.setVisibility(View.VISIBLE);

                Button buttonCancel = cancelLayout.findViewById(R.id.btncancel2);
                buttonCancel.setText("CANCEL");
                break;
            }
            default:
                // no buttons required
                break;
        }

        // if this needs user action, set screen as dialog style
        if(mScreenType == SCREEN_NOTIFIER_ENTER_CANCEL ||
                mScreenType == SCREEN_NOTIFIER_WITH_CANCEL) {

            View dimmer = findViewById(R.id.notification_dimmer);
            dimmer.setVisibility(View.VISIBLE);

            View dialog = findViewById(R.id.notification_dialog);
            dialog.setElevation(getResources().getDimension(R.dimen.dimmer_elevation));
        }

        if(sBeep != null && !sBeep.isEmpty()) {
            int type = Integer.valueOf(sBeep);
            SettingsUtil.triggerBeepType(this, type);
        }
    }

    public void okButtonClicked(View view) {
        SettingsUtil.triggerBeep(this);

        if(hasTimedOut) return;

        if(!buttonClicked) {
            isUserDone = true;
            JSONArray dataToSend = new JSONArray();
            dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_ENTER));
            StatusUtil.notifyCurrentTransaction(dataToSend);
            buttonClicked = true;
        }
    }

    public void cancelButtonClicked(View view) {
        SettingsUtil.triggerBeep(this);

        if(hasTimedOut) return;

        if(!buttonClicked) {
            isUserDone = true;
            JSONArray dataToSend = new JSONArray();
            dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_CANCEL));
            StatusUtil.notifyCurrentTransaction(dataToSend);
            buttonClicked = true;
        }
    }

    @Override
    public void onBackPressed() {
        // do not allow to manage its own lifecycle

        SettingsUtil.triggerBeep(this);
    }

    @Override
    public void onDialogButtonPositiveClick() {
        isUserDone = true;
        hasTimedOut = true;
        super.onDialogButtonPositiveClick();
    }
}