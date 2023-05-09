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

import com.pos.device.apdu.CommandApdu;
import com.pos.device.apdu.ResponseApdu;
import com.pos.device.icc.ContactCard;
import com.pos.device.icc.IccReader;
import com.pos.device.icc.IccReaderCallback;
import com.pos.device.icc.OperatorMode;
import com.pos.device.icc.SlotType;
import com.pos.device.icc.VCC;

public class FragICCard extends Fragment implements OnClickListener{

	private static final String TAG="MYDEBUG";
	private IccReader iccReader;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
		View view=inflater.inflate(R.layout.frag_iccard, container, false);
		((Button) view.findViewById(R.id.bStartSearch)).setOnClickListener(this);
		((Button) view.findViewById(R.id.bStop)).setOnClickListener(this);
		return view;
	}

	@Override
	public void onActivityCreated(Bundle savedInstanceState) {
		super.onActivityCreated(savedInstanceState);
		iccReader= IccReader.getInstance(SlotType.USER_CARD);
		FragmentsProvider.hideFragment(FragmentsProvider.FRAG_TAG.IC_CARD,getFragmentManager());
	}


	@Override
	public void onClick(View v) {
		switch(v.getId()){
		case R.id.bStartSearch:
			startICCard();
			break;

		case R.id.bStop:
			stopICCard();
			break;
		}
	}

	public void startICCard(){
		eraseEditTexts();
		if (iccReader==null)
			iccReader= IccReader.getInstance(SlotType.USER_CARD);
		try {
			//int timeout=Integer.valueOf((((EditText) getView().findViewById(R.id.etTimeout)).getText().toString()));
			int timeout=30;
			iccReader.startSearchCard(timeout*1000, iccReaderCallback);
			setStatus(ICCARD_STATUS.READY_TO_INSERT);
			Log.d(TAG, "search ICC Reader STARTED");
		} catch (SDKException e) {
			Log.d(TAG, "iccReader.startSearchCard SDKException "+e.getMessage());
			e.printStackTrace();
		}
	}

	public void stopICCard(){
		if(iccReader!=null){
			try {
				iccReader.stopSearchCard();
				setStatus(ICCARD_STATUS.STOPPED);
				Log.d(TAG, "search ICC Reader STOPPED");
			} catch (SDKException e) {
				Log.e(TAG,"SDKException iccReader.stopSearchCard() "+e.getMessage());
				e.printStackTrace();

			}

		}
	}

	public void bReleaseIccReader(View view){
		if(iccReader!=null){
			iccReader.disconnectCard();
			iccReader.release();
			iccReader=null;
			Log.d(TAG, "ICC Reader RELEASD");
		}
	}

	private IccReaderCallback iccReaderCallback=new IccReaderCallback() {

		@Override
		public void onSearchResult(final int arg0) {
			//Log.d(TAG, "IccReaderCallback onResult");
			String str= "IccReaderCallback: "+arg0;
			//toastOnUI(str);

			if (arg0== IccReaderCallback.SUCCESS){
				ContactCard card=null;
				try {
					card=iccReader.connectCard(VCC.VOLT_5, OperatorMode.EMV_MODE);
					if (card!=null){
						byte[] apdu= UtilUI.hexStringToByteArray("00A4040008A00000033301010100");
						setEditText(R.id.etAPDU, "00A4040008A00000033301010100");
						CommandApdu cmdApdu=new CommandApdu(apdu);

						boolean cardPresent=iccReader.isCardPresent();


						if (!cardPresent){
							str="CARD IS NOT PRESENT";
							Log.d(TAG,str);
							//toastOnUI(str);
							return; 
						}else{
							Log.d(TAG, "CARD IS PRESENT ...");
						}


						ResponseApdu responseApdu=iccReader.transmit(card, cmdApdu);
						if (responseApdu!=null){
							str="RESPONSE APDU: "+ UtilUI.bytesToHex(responseApdu.getBytes());
							String response= UtilUI.bytesToHex(responseApdu.getBytes());
							setEditText(R.id.etResponse, response);
								
							Log.d(TAG, str);
							//toastOnUI(str);
						}else{
							str="responseApdu is null";
							Log.d(TAG, str);
							//toastOnUI(str);
						}

					}
				} catch (SDKException e) {
					Log.d(TAG, "iccReader.connectCard SDKException "+e.getMessage());
					e.printStackTrace();
				}
			}
			getActivity().runOnUiThread(new Runnable() {
				@Override
				public void run() {
					stopICCard();
				}
			});
			
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
	
	void setEditText(final int id,final String text){
		if (text==null)
			return;
		getActivity().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				((EditText) getView().findViewById(id)).setText(text);
			}
		});
	}
	
	void setStatus(ICCARD_STATUS status){
		switch(status){
		case STOPPED:
			//UtilFitText.fitTextView(getActivity(), getResources().getString(R.string.textICCard), (TextView)  getView().findViewById(R.id.tvICCardStatus));
			((TextView)  getView().findViewById(R.id.tvICCardStatus)).setText(getResources().getString(R.string.textICCard));
			break;

		case READY_TO_INSERT:
			//UtilFitText.fitTextView(getActivity(), getResources().getString(R.string.textInsertCard), (TextView)  getView().findViewById(R.id.tvICCardStatus));
			((TextView)  getView().findViewById(R.id.tvICCardStatus)).setText(getResources().getString(R.string.textInsertCard));
			break;
		}
	}

	private enum ICCARD_STATUS{
		STOPPED,
		READY_TO_INSERT;
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
			return "READER_CLOSED";

		default:
			return "";
		}
	}
	
	private void eraseEditTexts(){
		((EditText) getView().findViewById(R.id.etAPDU)).setText("");
		((EditText) getView().findViewById(R.id.etResponse)).setText("");
	}
	
}
