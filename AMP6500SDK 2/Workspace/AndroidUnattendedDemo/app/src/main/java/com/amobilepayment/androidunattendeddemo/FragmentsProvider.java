package com.amobilepayment.androidunattendeddemo;

import android.app.FragmentManager;
import android.app.FragmentTransaction;

/**
 * Created by Rasa Vafaie on 2017-09-06.
 */

public class FragmentsProvider {

    enum FRAG_TAG{
        HOMEPAGE,
        NFC(0,"NFC",R.mipmap.contactless256),
        MAGNETIC(1,"Magnetic Card",R.mipmap.magnetic256),
        IC_CARD(2,"IC CARD",R.mipmap.emv256),
        SERIAL_PORT(3,"Serial Port",R.mipmap.serial256);

        int index;
        String name;
        int imageResID;

        FRAG_TAG(){
            this.index=-500;
            this.name=null;
            this.imageResID=-501;
        }

        FRAG_TAG(int index, String name, int imageResID){
            this.index=index;
            this.name=name;
            this.imageResID=imageResID;
        }

        static int getImageResIDByIndex(int index){
            for (FRAG_TAG tag: FRAG_TAG.values()){
                if (tag.index==index){
                    return tag.imageResID;
                }
            }
            return -1;
        }

        static String getNameIDByIndex(int index){
            for (FRAG_TAG tag: FRAG_TAG.values()){
                if (tag.index==index){
                    return tag.name;
                }
            }
            return null;
        }

        static FRAG_TAG getTagByIndex(int index){
            for (FRAG_TAG tag: FRAG_TAG.values()){
                if (tag.index==index){
                    return tag;
                }
            }
            return null;
        }

    }

    static void displayFragment(FRAG_TAG fragmentTag, FragmentManager manager){
        hideAllFragments(manager);
        FragmentTransaction transaction=manager.beginTransaction();
        //transaction.setCustomAnimations(R.animator.card_flip_left_in, R.animator.card_flip_left_out);
        transaction.setCustomAnimations(android.R.animator.fade_in, android.R.animator.fade_out);
        if ( manager.findFragmentByTag(fragmentTag.name())!=null  ){
            //Log.d(TAG, "fragment is NOT null ==> show "+fragmentTag.name());
            transaction.show(manager.findFragmentByTag(fragmentTag.name()));
        } else {
            //Log.d(TAG, "ERROR fragment is null ==> add "+fragmentTag.name());
        }
        transaction.commit();
    }

    static void hideAllFragments(FragmentManager manager){
        FragmentTransaction transaction=manager.beginTransaction();

        for (FRAG_TAG tag: FRAG_TAG.values()){
            //Log.d(TAG, "hideAllFragments for loop: "+tag.name());
            if (manager.findFragmentByTag(tag.name())!=null && manager.findFragmentByTag(tag.name()).isVisible()){
                //Log.d(TAG, "hideAllFragments trying to hide: "+tag.name() +"   not null && visible");
                transaction.hide(manager.findFragmentByTag(tag.name()));
            }
        }
        transaction.commit();
    }

    static void hideFragment(FRAG_TAG fragmentTag, FragmentManager manager){
        FragmentTransaction transaction=manager.beginTransaction();
        if (manager.findFragmentByTag(fragmentTag.name())!=null){
            transaction.hide(manager.findFragmentByTag(fragmentTag.name()));
        }
        transaction.commit();
    }
}
