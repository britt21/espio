package com.amobilepayment.androidunattendeddemo;

import android.content.Context;
import android.util.Log;
import android.util.TypedValue;
import android.view.ViewTreeObserver.OnGlobalLayoutListener;
import android.widget.Button;
import android.widget.TextView;

public class UtilFitText {

	private static final String TAG="MYDEBUG";
	private static final boolean DEBUG_MODE=false;
	
	public static int getFitTextSizeSP(Context context,String str,int viewWidth, int viewHeight,int currenttextSizePixels){
		TextView tv=new TextView(context);
		tv.setText(str);

		int currentSizeSP=pixelToSP(context,currenttextSizePixels);
		tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,currentSizeSP );
		
		if (DEBUG_MODE) Log.d(TAG, "String: "+str+"    View width: "+viewWidth+"  Height: "+viewHeight +"  current size SP: "+currentSizeSP);
		
		boolean increase=isTextDimensionsExceeds(tv, viewWidth, viewHeight,currentSizeSP)?false:true;

		if (increase){
			////////////////////////increase by 5 ///////////////////////////////////////
			currentSizeSP+=5;
			tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,currentSizeSP );
			while (!isTextDimensionsExceeds(tv,viewWidth, viewHeight,currentSizeSP)){
				currentSizeSP+=5;
				tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,currentSizeSP );
			}
			///////////////////////////////////////////////////////////////

			//////////////////////// decrease by 1 //////////////////////////////////////
			currentSizeSP--;
			tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,currentSizeSP );
			while (isTextDimensionsExceeds(tv,viewWidth, viewHeight,currentSizeSP)){
				currentSizeSP--;
				tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,currentSizeSP );
			}
			return currentSizeSP;
		}
		else{
			////////////////////////decrease by 5 ///////////////////////////////////////
			currentSizeSP-=5;
			tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,currentSizeSP );
			while (isTextDimensionsExceeds(tv,viewWidth, viewHeight,currentSizeSP) && currentSizeSP>5){
				currentSizeSP-=5;
				tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,currentSizeSP );
			}
			///////////////////////////////////////////////////////////////
			
			if (currentSizeSP<1){
				currentSizeSP=1;
			}
			
			//////////////////////// increase by 1 //////////////////////////////////////
			currentSizeSP++;
			tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,currentSizeSP );
			while (!isTextDimensionsExceeds(tv,viewWidth, viewHeight,currentSizeSP)){
				currentSizeSP++;
				tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,currentSizeSP );
			}
			return currentSizeSP-1;
		}
	}
	
	public static int getSPFitTextGroup(Context context, TextView... textViews ){
		int[] spSizes=new int [textViews.length];
		
		for (int i=0;i<spSizes.length;i++){
			spSizes[i]=getFitTextSizeSP(context, textViews[i].getText().toString(), textViews[i].getWidth(), textViews[i].getHeight(), (int) textViews[i].getTextSize());
		}
		
		return min(spSizes);
	}
	
	public static void fitTextGroup(Context context, TextView... textViews){
		int fontSizeSP=getSPFitTextGroup(context, textViews);
		if (DEBUG_MODE) Log.d(TAG, "GROUP FONT SIZE: "+fontSizeSP+"sp");
		for (int i=0;i<textViews.length;i++){
			textViews[i].setTextSize(TypedValue.COMPLEX_UNIT_SP, fontSizeSP);
		}
	}
	
	public static int getSPFitTextGroupButton(Context context, Button... buttons ){
		int[] spSizes=new int [buttons.length];
		
		for (int i=0;i<spSizes.length;i++){
			spSizes[i]=getFitTextSizeSP(context, buttons[i].getText().toString(), buttons[i].getWidth(), buttons[i].getHeight(), (int) buttons[i].getTextSize());
		}
		
		return min(spSizes);
	}
	
	public static void fitTextGroupButtons(Context context, Button... buttons){
		int fontSizeSP=getSPFitTextGroup(context, buttons);
		if (DEBUG_MODE) Log.d(TAG, "GROUP FONT SIZE: "+fontSizeSP+"sp");
		for (int i=0;i<buttons.length;i++){
			buttons[i].setTextSize(TypedValue.COMPLEX_UNIT_SP, fontSizeSP);
		}
	}
	
	private static int min(int... args) {
        int m = Integer.MAX_VALUE;
        for (int a : args) {
            m = Math.min(m, a);
        }
        return m;
    }
	
	private static int pixelToSP(Context context,int pixel){
		return (int)(( 160.00 /(double) context.getResources().getDisplayMetrics().densityDpi ) * pixel);   
	}

	private static boolean isTextDimensionsExceeds(TextView tv,int viewWidth, int viewHeight,int currentSP){
		tv.measure(0, 0);       //must call measure!
		int height=tv.getMeasuredHeight(); //get height
		int width=tv.getMeasuredWidth(); 
		if (DEBUG_MODE) Log.d(TAG, "//// getTextDimensions text Width: "+width+ "   height:"+height + "  TEXT Size SP: "+currentSP);
		return (width>viewWidth || height>viewHeight);
	}
	
	public static void fitTextButtonAfterMeasured(final Context context,final Button b){
		b.getViewTreeObserver().addOnGlobalLayoutListener(new OnGlobalLayoutListener() {
			@SuppressWarnings("deprecation")
			@Override
			public void onGlobalLayout() {
				if (DEBUG_MODE) Log.d(TAG, "b in onGlobalLayout");
				if (b.getWidth()>0 && b.getHeight()>0){
					if (DEBUG_MODE) Log.d(TAG, "b Measured ....");
					b.setTextSize(TypedValue.COMPLEX_UNIT_SP, getFitTextSizeSP(context, b.getText().toString(), b.getWidth(), b.getHeight(), (int) b.getTextSize()));
					b.getViewTreeObserver().removeGlobalOnLayoutListener(this);
				}
				else{
					if (DEBUG_MODE) Log.d(TAG, "b Not measured yet");
				}
			}
		});
	}
	
	public static void fitTextViewAfterMeasured(final Context context,final TextView tv){
		tv.getViewTreeObserver().addOnGlobalLayoutListener(new OnGlobalLayoutListener() {
			@SuppressWarnings("deprecation")
			@Override
			public void onGlobalLayout() {
				if (DEBUG_MODE) Log.d(TAG, "tv in onGlobalLayout");
				if (tv.getWidth()>0 && tv.getHeight()>0){
					if (DEBUG_MODE) Log.d(TAG, "tv Measured ....");
					tv.setTextSize(TypedValue.COMPLEX_UNIT_SP, getFitTextSizeSP(context, tv.getText().toString(), tv.getWidth(), tv.getHeight(), (int) tv.getTextSize()));
					tv.getViewTreeObserver().removeGlobalOnLayoutListener(this);
				}
				else{
					if (DEBUG_MODE) Log.d(TAG, "tv Not measured yet");
				}
			}
		});
	}
	
	public static void fitTextViewAfterCreatedGroup(final Context context,final TextView...textViews){
		textViews[0].getViewTreeObserver().addOnGlobalLayoutListener(new OnGlobalLayoutListener() {
			
			@Override
			public void onGlobalLayout() {
				if (DEBUG_MODE) Log.d(TAG, "Group tv in onGlobalLayout");
				if (isTextViewsCreated(textViews)){
					if (DEBUG_MODE) Log.d(TAG, "TextViews are Measured ...");
					fitTextGroup(context, textViews);
				}
				else{
					if (DEBUG_MODE) Log.d(TAG, "textViews has not been created yet");
				}
			}
		});
	}
	
	private static boolean isTextViewsCreated(TextView...textViews){
		for (int m=0;m<textViews.length;m++){
			if (textViews[m].getWidth()==0 || textViews[m].getHeight()==0)
				return false;
		}
		return true;
	}
	
	public static void fitTextButtonsAfterCreatedGroup(final Context context,final Button... buttons){
		buttons[0].getViewTreeObserver().addOnGlobalLayoutListener(new OnGlobalLayoutListener() {
			
			@Override
			public void onGlobalLayout() {
				if (DEBUG_MODE) Log.d(TAG, "Group buttons in onGlobalLayout");
				if (isButtonViewsCreated(buttons)){
					if (DEBUG_MODE) Log.d(TAG, "Buttons are Measured ...");
					fitTextGroupButtons(context, buttons);
				}
				else{
					if (DEBUG_MODE) Log.d(TAG, "buttons has not been created yet");
				}
			}
		});
	}
	
	private static boolean isButtonViewsCreated(Button...buttons){
		for (int m=0;m<buttons.length;m++){
			if (buttons[m].getWidth()==0 || buttons[m].getHeight()==0)
				return false;
		}
		return true;
	}
	
	public static void fitTextView(Context context,String str, TextView tv){
		tv.setText(str);
		tv.setTextSize(TypedValue.COMPLEX_UNIT_SP, getFitTextSizeSP(context, str, tv.getWidth(), tv.getHeight(), (int) tv.getTextSize()));
	}
}
