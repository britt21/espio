package com.amobilepayment.demo.Settings;

import android.content.Context;
import android.preference.PreferenceCategory;
import android.util.AttributeSet;

import com.amobilepayment.demo.R;

public class AMPPreferenceCategory extends PreferenceCategory {
    public AMPPreferenceCategory(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        setLayoutResource(R.layout.settings_header);
    }

    public AMPPreferenceCategory(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        setLayoutResource(R.layout.settings_header);
    }

    public AMPPreferenceCategory(Context context, AttributeSet attrs) {
        super(context, attrs);
        setLayoutResource(R.layout.settings_header);
    }

    public AMPPreferenceCategory(Context context) {
        super(context);
        setLayoutResource(R.layout.settings_header);
    }
}
