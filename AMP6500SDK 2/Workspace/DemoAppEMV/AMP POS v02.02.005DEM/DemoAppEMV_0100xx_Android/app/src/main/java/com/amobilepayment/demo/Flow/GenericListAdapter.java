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

public class GenericListAdapter extends RecyclerView.Adapter<GenericListAdapter.ViewHolder> {
    private final static String TAG = GenericListAdapter.class.getSimpleName();
    private final View.OnClickListener mOnClickListener = new TheOnClickListener();
    private RecyclerView mRecyclerView;
    private JSONArray items;
    private int SCREEN_TYPE = 0;
    private final Context mContext;

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

    public GenericListAdapter(JSONArray screenItems, Context context) {
        this.items = screenItems;
        mContext = context;
    }

    // Create new views (invoked by the layout manager)
    @Override
    public GenericListAdapter.ViewHolder onCreateViewHolder(ViewGroup parent,
                                                            int viewType) {
        // create a new view
        View v = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.generic_list_item, parent, false);

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

            JSONArray dataToSend = new JSONArray();
            int position;
            switch(SCREEN_TYPE) {
                case BaseActivity.SCREEN_SETTINGS_SHOW_OPERATORS:

                        Log.d(TAG, "TODO: settings operations not yet supported");
                        if(mContext instanceof Activity)
                            ((Activity) mContext).finish();
                    break;
                case BaseActivity.SCREEN_ACCT_SELECT:
                    {
                        TextView option_item = view.findViewById(R.id.option_item);
                        String val = option_item.getText().toString();
                        JSONObject data = new JSONObject();
                        try {
                            data.put("id", TransactionContract.CRTDATA_ACCOUNTTTYPE);
                            data.put("type", 1);
                            data.put("value", val);
                            dataToSend.put(data);
                            dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                    break;
                case BaseActivity.SCREEN_CARD_TYPE_SELECT:
                    {
                        Log.d(TAG, "SCREEN_CARD_TYPE_SELECT");
                        TextView option_item = view.findViewById(R.id.option_item);
                        String val = option_item.getText().toString();
                        //TransObject.SetString(TransactionContract.CRTDATA_CARDTYPE_LABEL, val);
                        Log.d(TAG, "Card Type Selected = " + val);
                        JSONObject data = new JSONObject();
                        try {
                            data.put("id", TransactionContract.CRTDATA_CARDTYPE_LABEL);
                            data.put("type", 1);
                            data.put("value", val);
                            dataToSend.put(data);
                            dataToSend.put(StatusUtil.prepareStatusObject(StatusUtil.AMP_SUCCESS));
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    }
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                    break;
                case BaseActivity.SCREEN_VOID_SELECT_HOW:
                    position = mRecyclerView.getChildLayoutPosition(view);
                    // start index expected by flow controller is 1
                    dataToSend.put(StatusUtil.prepareStatusObject(position+1));
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                    break;
                case BaseActivity.SCREEN_PROMPT_ENTRY_CANCEL:
                    position = mRecyclerView.getChildLayoutPosition(view);
                    int returnCode = 1;
                    if(position == 1) {
                        returnCode = StatusUtil.AMP_CANCEL;
                    }
                    dataToSend.put(StatusUtil.prepareStatusObject(returnCode));
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                    break;
                case BaseActivity.SCREEN_SELECT_ECI:
                case BaseActivity.SCREEN_SELECT_2_RECALL:
                case BaseActivity.SCREEN_CARD_PRESENT:
                case BaseActivity.SCREEN_SELECT_3_RECALL:
                case BaseActivity.SCREEN_SELECT_BILLPAYT:
                default:
                    position = mRecyclerView.getChildLayoutPosition(view);
                    dataToSend.put(StatusUtil.prepareStatusObject(position));
                    StatusUtil.notifyCurrentTransaction(dataToSend);
                    break;
            }
        }
    }
}