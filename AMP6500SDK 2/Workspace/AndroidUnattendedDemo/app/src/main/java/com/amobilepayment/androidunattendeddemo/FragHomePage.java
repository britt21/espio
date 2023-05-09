package com.amobilepayment.androidunattendeddemo;

import android.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

/**
 * Created by Rasa Vafaie on 2017-09-06.
 */

public class FragHomePage extends Fragment implements View.OnClickListener {




    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view=inflater.inflate(R.layout.frag_home_page,container,false);

        return view;
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        RecyclerView rv=(RecyclerView) getActivity().findViewById(R.id.rvHomePage);
        AdapterHomePage adapter=new AdapterHomePage();
        rv.setAdapter(adapter);
        rv.setLayoutManager(new GridLayoutManager(getActivity(),2));
    }

    @Override
    public void onClick(View v) {

    }


    private class AdapterHomePage extends RecyclerView.Adapter<AdapterHomePage.MyViewHolder>{

        //private final String[] texts={"NFC","MAGNETIC","IC CARD","SERIAL PORT"};
        //private final int[] imageIDs={R.mipmap.contactless,R.mipmap.magneticcard,R.mipmap.smartcard,R.mipmap.serialport};

        @Override
        public MyViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            LayoutInflater inflater=(LayoutInflater) getActivity().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            View view=inflater.inflate(R.layout.cardview_home_page,parent,false);
            MyViewHolder viewHolder=new MyViewHolder(view);
            return viewHolder;
        }

        @Override
        public void onBindViewHolder(MyViewHolder holder, int position) {
            holder.ivCardViewHomePage.setImageResource(FragmentsProvider.FRAG_TAG.getImageResIDByIndex(position));
            holder.tvCardViewHomePage.setText(FragmentsProvider.FRAG_TAG.getNameIDByIndex(position));
            holder.setIsRecyclable(false);
        }

        @Override
        public int getItemCount() {
            return FragmentsProvider.FRAG_TAG.values().length-1;
        }

        class MyViewHolder extends RecyclerView.ViewHolder{

            ImageView ivCardViewHomePage;
            TextView tvCardViewHomePage;

            public MyViewHolder(View itemView) {
                super(itemView);
                ivCardViewHomePage=(ImageView) itemView.findViewById(R.id.ivCardViewHomePage);
                tvCardViewHomePage=(TextView) itemView.findViewById(R.id.tvCardViewHomePage);

                ivCardViewHomePage.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        FragmentsProvider.displayFragment(FragmentsProvider.FRAG_TAG.getTagByIndex(getAdapterPosition()),getFragmentManager());
                    }
                });
            }
        }

    }


}
