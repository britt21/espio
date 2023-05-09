package com.amobilepayment.demo.Flow;

import android.app.Activity;
import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.TransactionContract;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.StatusUtil;
import com.amobilepayment.demo.Utils.TransObject;

public class SelectionAdapter extends RecyclerView.Adapter<SelectionAdapter.ViewHolder> {
    private final static String TAG = SelectionAdapter.class.getSimpleName();
    private final View.OnClickListener mOnClickListener = new TheOnClickListener();
    private RecyclerView mRecyclerView;
    private JSONArray items;
    private int SCREEN_TYPE = 0;
    private final Context mContext;

    // use this as return values
    // derived from AMPBaseConsole.h
    private int AMPKEY_MENU1 = 0x0081;
    private int AMPKEY_MENU2 = 0x0082;
    private int AMPKEY_MENU3 = 0x0083;
    private int AMPKEY_MENU4 = 0x0084;
    private int AMPKEY_MENU5 = 0x0085;
    private int AMPKEY_MENU6 = 0x0086;
    private int[] returnValues = {AMPKEY_MENU1,AMPKEY_MENU2,AMPKEY_MENU3,AMPKEY_MENU4,AMPKEY_MENU5,AMPKEY_MENU6};

    public static class ViewHolder extends RecyclerView.ViewHolder {
        public TextView mOptionItem;

        public ViewHolder(View v) {
            super(v);

            mOptionItem = v.findViewById(R.id.option_item);
        }
    }

    @Override
    public void onAttachedToRecyclerView(RecyclerView recyclerView) {
        super.onAttachedToRecyclerView(recyclerView);
        mRecyclerView = recyclerView;
    }

    public SelectionAdapter(JSONArray screenItems, Context context) {
        this.items = screenItems;
        mContext = context;
    }

    // Create new views (invoked by the layout manager)
    @Override
    public SelectionAdapter.ViewHolder onCreateViewHolder(ViewGroup parent,
                                                          int viewType) {
        // create a new view
        View v = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.selection_item, parent, false);

        v.setOnClickListener(mOnClickListener);

        ViewHolder vh = new ViewHolder(v);
        return vh;
    }

    public void setScreenType(int st) {
        SCREEN_TYPE = st;
    }

    // Replace the contents of a view (invoked by the layout manager)
    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        // - get element from your dataset at this position
        // - replace the contents of the view with that element
        try {
            holder.mOptionItem.setText(items.getString(position));
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    // Return the size of your dataset (invoked by the layout manager)
    @Override
    public int getItemCount() {
        return items.length();
    }

    private class TheOnClickListener implements View.OnClickListener {
        @Override
        public void onClick(View view) {
            SettingsUtil.triggerBeep(mContext);

            switch(SCREEN_TYPE) {
                case BaseActivity.SCREEN_VOID_SELECT_HOW: {
                    JSONArray dataToSend = new JSONArray();
                    int position = mRecyclerView.getChildLayoutPosition(view);
                    // start index expected by flow controller is 1
                    dataToSend.put(StatusUtil.prepareStatusObject(position + 1));
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                    break;
                }
                case BaseActivity.SCREEN_PROMPT_ENTRY_CANCEL: {
                    JSONArray dataToSend = new JSONArray();
                    int position = mRecyclerView.getChildLayoutPosition(view);
                    int returnCode = 1;
                    if (position == 1) {
                        returnCode = StatusUtil.AMP_CANCEL;
                    }
                    dataToSend.put(StatusUtil.prepareStatusObject(returnCode));
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                    break;
                }
                case BaseActivity.SCREEN_CARD_TYPE_SELECTION:
                case BaseActivity.SCREEN_CARD_ENTRY: {
                    JSONArray dataToSend = new JSONArray();
                    int position = mRecyclerView.getChildLayoutPosition(view);
                    JSONObject data = new JSONObject();
                    TextView option_item = view.findViewById(R.id.option_item);
                    try {
                        data.put("id", "clickedposition");
                        data.put("type", 1);
                        data.put("value", option_item.getText().toString());
                        dataToSend.put(data);
                        dataToSend.put(StatusUtil.prepareStatusObject(position+1));
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                    break;
                }
                case BaseActivity.SCREEN_THREE_BUTTON_SELECTION: {
                    if(mContext instanceof BaseActivity) {
                        BaseActivity activity = (BaseActivity) mContext;
                        if(!activity.hasTimedOut)
                            activity.isUserDone = true;
                        else
                            return;
                    }
                    JSONArray dataToSend = new JSONArray();
                    int position = mRecyclerView.getChildLayoutPosition(view);
                    JSONObject data = new JSONObject();
                    TextView option_item = view.findViewById(R.id.option_item);
                    try {
                        data.put("id", "clickedposition");
                        data.put("type", 1);
                        data.put("value", option_item.getText().toString());
                        dataToSend.put(data);
                        dataToSend.put(StatusUtil.prepareStatusObject(returnValues[position]));
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                    break;
                }
            }
        }
    }
}