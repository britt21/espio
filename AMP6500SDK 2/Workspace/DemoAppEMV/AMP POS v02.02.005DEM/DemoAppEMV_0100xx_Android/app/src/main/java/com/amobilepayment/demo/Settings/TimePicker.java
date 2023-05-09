package com.amobilepayment.demo.Settings;

import android.app.Dialog;
import android.app.TimePickerDialog;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.text.format.DateFormat;

import com.amobilepayment.demo.Utils.SettingsUtil;

import java.util.Calendar;

public class TimePicker extends DialogFragment implements TimePickerDialog.OnTimeSetListener {

    private final String TAG = TimePicker.class.getSimpleName();

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        // Use the current time as the default values for the picker
        final Calendar c = Calendar.getInstance();
        int hour = c.get(Calendar.HOUR_OF_DAY);
        int minute = c.get(Calendar.MINUTE);

        return new TimePickerDialog(
                getActivity(),
                this,
                hour,
                minute,
                true);
    }

    @Override
    public void onTimeSet(android.widget.TimePicker timePicker, int h, int m) {
        SettingsUtil.setTerminalTime(getActivity(), h, m);
    }
}
