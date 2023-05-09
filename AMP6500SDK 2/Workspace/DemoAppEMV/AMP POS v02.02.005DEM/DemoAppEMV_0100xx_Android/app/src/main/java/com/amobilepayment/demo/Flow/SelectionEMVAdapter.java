package com.amobilepayment.demo.Flow;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.amobilepayment.demo.Main.MenuActivity;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.StatusUtil;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import AmpEmvL2Android.AmpEmvCB;

public class SelectionEMVAdapter extends RecyclerView.Adapter<SelectionEMVAdapter.ViewHolder> {
    private final static String TAG = SelectionEMVAdapter.class.getSimpleName();

    private final View.OnClickListener mOnClickListener = new TheOnClickListener();
    private RecyclerView mRecyclerView;
    private JSONArray items;
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

    public SelectionEMVAdapter(JSONArray screenItems, Context context) {
        this.items = screenItems;
        mContext = context;
    }

    // Create new views (invoked by the layout manager)
    @Override
    public SelectionEMVAdapter.ViewHolder onCreateViewHolder(ViewGroup parent,
                                                             int viewType) {
        // create a new view
        View v = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.selection_item, parent, false);

        v.setOnClickListener(mOnClickListener);

        ViewHolder vh = new ViewHolder(v);
        return vh;
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
            //SettingsUtil.triggerBeep(mContext);

            int position = mRecyclerView.getChildLayoutPosition(view);
            AmpEmvCB.itemPos = position;
        }
    }
}