package com.amobilepayment.androidunattendeddemo;

import android.app.Fragment;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.pos.device.SDKException;
import com.pos.device.magcard.MagCardCallback;
import com.pos.device.magcard.MagCardReader;
import com.pos.device.magcard.MagneticCard;

public class FragMagnetic extends Fragment implements OnClickListener{

	public static final String TAG="MYDEBUG";
	private MagCardReader magCardReader;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		View view=inflater.inflate(R.layout.frag_magnetic, container, false);
		((Button) view.findViewById(R.id.bStartSearch)).setOnClickListener(this);
		((Button) view.findViewById(R.id.bStop)).setOnClickListener(this);
		return view;
	}

	@Override
	public void onActivityCreated(Bundle savedInstanceState) {
		super.onActivityCreated(savedInstanceState);

		magCardReader= MagCardReader.getInstance();
		FragmentsProvider.hideFragment(FragmentsProvider.FRAG_TAG.MAGNETIC,getFragmentManager());
	}



	@Override
	public void onClick(View v) {
		switch(v.getId()){
		case R.id.bStartSearch:
			startMagCard();
			break;

		case R.id.bStop:
			stopMagCard();
			break;
		}
	}

	void startMagCard(){
		eraseEditTexts();
		if (magCardReader!=null){
			try {
				//int timeout=Integer.valueOf((((EditText) getView().findViewById(R.id.etTimeout)).getText().toString()));
				int timeout=30;
				magCardReader.startSearchCard(timeout*1000, magCardReaderCallback);
				setStatus(MAGNETIC_STATUS.READY_TO_SWIPE);
				Log.d(TAG, "search MAG CARD READER STARTED");
			} catch (SDKException e) {
				Log.d(TAG, "magCardReader.startSearchCard SDKException "+e.getMessage());
				e.printStackTrace();
			}
		}
	}

	void stopMagCard(){
		if(magCardReader!=null){
			try {
				magCardReader.stopSearchCard();
				setStatus(MAGNETIC_STATUS.STOPPED);
				Log.d(TAG, "search MAG CARD READER STOPPED");
			} catch (SDKException e) {
				Log.d(TAG, "magCardReader.stopSearchCard SDKException "+e.getMessage());
				e.printStackTrace();
			}
		}
	}

	private MagCardCallback magCardReaderCallback=new MagCardCallback() {

		@Override
		public void onSearchResult(int arg0, MagneticCard arg1) {
			if (arg1!=null){
				String statusTrack1=getStatusDescription(arg1.getTrackInfos(MagneticCard.TRACK_1).getState());
				if (statusTrack1!=null)
					((EditText) getView().findViewById(R.id.etTrack1Status)).setText(statusTrack1);

				String statusTrack2=getStatusDescription(arg1.getTrackInfos(MagneticCard.TRACK_2).getState());
				if (statusTrack2!=null)
					((EditText) getView().findViewById(R.id.etTrack2Status)).setText(statusTrack2);

				String statusTrack3=getStatusDescription(arg1.getTrackInfos(MagneticCard.TRACK_3).getState());
				if (statusTrack3!=null)
					((EditText) getView().findViewById(R.id.etTrack3Status)).setText(statusTrack3);

				String dataTrack1=arg1.getTrackInfos(MagneticCard.TRACK_1).getData();
				if (dataTrack1!=null)
					((EditText) getView().findViewById(R.id.etTrack1Data)).setText(dataTrack1);

				String dataTrack2=arg1.getTrackInfos(MagneticCard.TRACK_2).getData();
				if (dataTrack2!=null)
					((EditText) getView().findViewById(R.id.etTrack2Data)).setText(dataTrack2);

				String dataTrack3=arg1.getTrackInfos(MagneticCard.TRACK_3).getData();
				if (dataTrack3!=null)
					((EditText) getView().findViewById(R.id.etTrack3Data)).setText(dataTrack3);
			}
			stopMagCard();

			
			/*Log.d(TAG, "Magnetic Card Reader Callback onResult");
			String str="Magnetic Card Reader Callback onResult "+arg0+
					"\nTRACK1 state: "+arg1.getTrackInfos(MagneticCard.TRACK_1).getState()+
					"\nTRACK1 Data: "+arg1.getTrackInfos(MagneticCard.TRACK_1).getData()+
					"\nTRACK2 state: "+arg1.getTrackInfos(MagneticCard.TRACK_2).getState()+
					"\nTRACK2 Data: "+arg1.getTrackInfos(MagneticCard.TRACK_2).getData()+
					"\nTRACK3 state: "+arg1.getTrackInfos(MagneticCard.TRACK_3).getState()+
					"\nTRACK3 Data: "+arg1.getTrackInfos(MagneticCard.TRACK_3).getData()
					;
			Log.d(TAG, str);*/
			
			//toastOnUI(str);
		}
	};

	private void toastOnUI(final String str){
		getActivity().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Toast.makeText(getActivity(), str, Toast.LENGTH_SHORT).show();
			}
		});
	}

	private void setStatus(MAGNETIC_STATUS status){
		switch(status){
		case STOPPED:
			//UtilFitText.fitTextView(getActivity(), getResources().getString(R.string.textMagneticCard), (TextView)  getView().findViewById(R.id.tvMagneticStatus));
			((TextView)  getView().findViewById(R.id.tvMagneticStatus)).setText(getResources().getString(R.string.textMagneticCard));
			break;

		case READY_TO_SWIPE:
			//UtilFitText.fitTextView(getActivity(), getResources().getString(R.string.textSwipeCard), (TextView)  getView().findViewById(R.id.tvMagneticStatus));
			((TextView)  getView().findViewById(R.id.tvMagneticStatus)).setText(getResources().getString(R.string.textSwipeCard));
			break;
		}
	}

	private enum MAGNETIC_STATUS{
		STOPPED,
		READY_TO_SWIPE
	}

	String getStatusDescription(int status){
		switch (status){
		case 0:
			return "SUCCESS";

		case 1:
			return "USER_CANCEL";

		case 2:
			return "TIMEOUT_ERROR";

		case 3:
			return "UNKNOWN_ERROR";

		default:
			return "";
		}
	}

	void eraseEditTexts(){
		((EditText) getView().findViewById(R.id.etTrack1Status)).setText("");
		((EditText) getView().findViewById(R.id.etTrack2Status)).setText("");
		((EditText) getView().findViewById(R.id.etTrack3Status)).setText("");

		((EditText) getView().findViewById(R.id.etTrack1Data)).setText("");
		((EditText) getView().findViewById(R.id.etTrack2Data)).setText("");
		((EditText) getView().findViewById(R.id.etTrack3Data)).setText("");
	}

}
