package com.amp.tmsclientdemoapplication;

import android.app.Activity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.amobilepayment.android.tmslibrary.Constants;
import com.amobilepayment.android.tmslibrary.DownloadStatus;
import com.amobilepayment.android.tmslibrary.FirmwareUpdateStatus;
import com.amobilepayment.android.tmslibrary.IServerResponse;
import com.amobilepayment.android.tmslibrary.STATE;
import com.amobilepayment.android.tmslibrary.TMS;
import com.amobilepayment.android.tmslibrary.TMS_FILE_TYPE;
import com.amobilepayment.android.tmslibrary.UtilUI;
import com.amobilepayment.android.tmslibrary.amp360.pojo.AMP360Response;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;

public class MainActivity extends Activity {
    private static final String TAG = "TMSDemo_MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TMS.getInstance().init(this, iServerResponse);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "onDestroy called");
        TMS.getInstance().release();
    }

    public void bCheckForUpdates(View view) {
        TMS.getInstance().checkForUpdates();
    }

    public void bCancelCheckForUpdates(View view) {
        TMS.getInstance().cancelCheckForUpdates();
    }

    public void bCheckForUpdatesAndSilentInstall(View view) {
//        final Switch switchAutoRun = findViewById(R.id.switchAutoRun);
//        TMS.getInstance().checkForUpdatesAndSilentInstall(switchAutoRun.isChecked());
        Toast.makeText(this, "API deprecated", Toast.LENGTH_LONG).show();
    }

    public void bInstallApplication(View view) {
        final Spinner spinner = findViewById(R.id.spinnerInstallMode);
        final int selectPosition = spinner.getSelectedItemPosition();
        TMS.getInstance().installApplication(Constants.INSTALL_MODE.getByCode(selectPosition));
    }

    public void bSilentInstallLastAllDownloads(View view) {
        TMS.getInstance().silentInstallLastAllDownloads();
    }

    public void bInstallFirmware(View view) {
        TMS.getInstance().installFirmware();
    }

    public void bGetConfigurationParameters(View view) {
        TMS.getInstance().getConfigurationParameters();
    }

    public void bGetConfigurationParametersHash(View view) {
        TMS.getInstance().getConfigurationParametersHash();
    }

    public void bGetAdditionalFile(View view) {
        TMS.getInstance().getAdditionalFile();
    }

    public void bGetAdditionalFileHash(View view) {
        TMS.getInstance().getAdditionalFileHash();
    }

    public void bUploadFile(View view) {
        File file = createFileFromAssetsFolder();
        TMS.getInstance().uploadFile(file);
    }

    public void bGetLocation(View view) {
        TMS.getInstance().getLocation();
    }

    public void bSetCellularDownload(View view) {
        final Switch cellularDownloadSwitch = findViewById(R.id.switchCellularDownload);
        TMS.getInstance().setCellularDownload(cellularDownloadSwitch.isChecked());
    }

    public void bSetApplicationParam(View view) {
        final EditText etSetConfigPkgName = findViewById(R.id.etSetConfigPkgName);
        final EditText etSetConfigTag = findViewById(R.id.etSetConfigTag);
        final EditText etSetConfigValue = findViewById(R.id.etSetConfigValue);
        TMS.getInstance().setApplicationParameter(etSetConfigPkgName.getText().toString(),
                etSetConfigTag.getText().toString()
                , etSetConfigValue.getText().toString());
    }

    public void bGetApplicationParams(View view) {
        final EditText etGetConfigSN = findViewById(R.id.etGetConfigSN);
        final EditText etGetConfigPkgName = findViewById(R.id.etGetConfigPkgName);
        TMS.getInstance().getApplicationParameters(etGetConfigSN.getText().toString()
                , etGetConfigPkgName.getText().toString());
    }

    public void bSetATMSServerAddress(View view) {
        String aTMSServerAddress = ((EditText) findViewById(R.id.etATMSServerAddress)).getText().toString();
        TMS.getInstance().setATMSServerAddress(aTMSServerAddress);
    }

    public void bSetTerminalID(View view) {
        String terminalID = ((EditText) findViewById(R.id.etTerminalID)).getText().toString();
        if (terminalID == null || terminalID.length() == 0 || terminalID.length() > 15) {
            Toast.makeText(this, "Invalid terminal ID", Toast.LENGTH_SHORT).show();
            return;
        }
        TMS.getInstance().setTerminalID(terminalID);
    }

    public void bInternalStorageContent(View v) {
        String[] internalFiles = getFilesDir().list();
        Toast.makeText(this, "Internal Files count: " + internalFiles.length, Toast.LENGTH_LONG).show();
        for (String temp : internalFiles) {
            Toast.makeText(this, temp, Toast.LENGTH_LONG).show();
        }
    }

    public void bDeleteInternalStorage(View v) {
        TMS.getInstance().deleteInternalStorage();
    }

    private IServerResponse iServerResponse = new IServerResponse() {
        @Override
        public void onJobError(STATE state, String error, String debugError) {
            Log.d(TAG, "JOB ERROR:\n" + state.name() + "  " + error + "   " + debugError);
            appendText("JOB ERROR:\n" + state.name() + "  " + error + "   " + debugError);
        }

        @Override
        public void onJobCompleted() {
            Log.d(TAG, "onJobCompleted called");
            appendText("** JOB COMPLETED **");
        }

        @Override
        public void onDownloadStatus(final String applicationName, final String fileName, final DownloadStatus status) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    ((TextView) findViewById(R.id.tvDownloadStatus)).setText("Download Status: " + applicationName + "\n" + fileName + "\n" + status.name());
                }
            });
        }

        @Override
        public void onDownloadProgress(final String fileName, final int progressPercentage, final long fileLength, final long currentDownloadLength) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    ((TextView) findViewById(R.id.tvDownloadProgress)).setText("Download progress: " + progressPercentage + " %\n" +
                            UtilUI.humanReadableByteCount(currentDownloadLength, true) + "/" + UtilUI.humanReadableByteCount(fileLength, true));
                }
            });
        }

        @Override
        public void onDownloadJobNumber(final int currentJobNumber, final int totalNumberOfDownload) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    ((TextView) findViewById(R.id.tvDownloadJobNumber)).setText(currentJobNumber + "/" + totalNumberOfDownload);
                }
            });
        }

        @Override
        public void onFirmwareUpgradeStatus(final int ret) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(MainActivity.this, "OnFirmwareUpgradeStatus code: " + ret, Toast.LENGTH_SHORT).show();
                }
            });
        }

        @Override
        public void onKeyInjectionReturnCode(final int ret) {
            Log.d(TAG, "onKeyInjectionReturnCode: " + ret);
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(MainActivity.this, "ATMS KEY Injection Code: " + ret, Toast.LENGTH_SHORT).show();
                }
            });
        }

        @Override
        public void onRequestedFileNotFound(final TMS_FILE_TYPE tmsFileType) {
            if (tmsFileType == null) {
                Log.e(TAG, "onRequestedFileNotFound: Unknown type");
            } else {
                Log.d(TAG, "onRequestedFileNotFound: " + tmsFileType.name());
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this, "onRequestedFileNotFound: " + tmsFileType.name(), Toast.LENGTH_SHORT).show();
                    }
                });
            }
        }

        @Override
        public void onAdditionalFilesReceived() {
            Log.d(TAG, "onAdditionalFilesReceived");
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(MainActivity.this, "onAdditionalFilesReceived", Toast.LENGTH_SHORT).show();
                }
            });
        }

        @Override
        public void onAdditionalFilesHashReceived(String hashCode) {
            Log.d(TAG, "onAdditionalFilesHashReceived, hashCode = " + hashCode);
        }

        @Override
        public void onConfigurationParametersReceived() {
            Log.d(TAG, "onConfigurationParametersReceived");
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(MainActivity.this, "onConfigurationParametersReceived", Toast.LENGTH_SHORT).show();
                }
            });
        }

        @Override
        public void onConfigurationParametersHashReceived(String hashCode) {
            Log.d(TAG, "onConfigurationParametersHashReceived, hashCode = " + hashCode);
        }

        @Override
        public void onAppInstallCompleted(String appName, int installResult) {
            Log.d(TAG, "onAppInstallCompleted received, appName = " + appName + ", installResult = " + installResult);
            appendText("App '" + appName + "' install finished, result = " + installResult);
        }

        @Override
        public void onLocationDetected(String location) {
            Log.d(TAG, "onLocationDetected: " + location);
            appendText("onLocationDetected: " + location);
        }

        @Override
        public void onSilentInstallAllLastDownloadsFinished(FirmwareUpdateStatus status, int numberOfApkDownloaded
                , int numberOfApInstalled, ArrayList<String> installedApkList) {
            Log.d(TAG, "onSilentInstallAllLastDownloadsFinished called, status = " + status
                    + ", numberOfApkDownloaded = " + numberOfApkDownloaded + ", numberOfApkInstalled = " + numberOfApInstalled
                    + ", installedApkList = " + installedApkList);
            appendText("SilentInstallAllLastDownloadsComplete, firmware update status = " + status
                    + ", numberOfApkDownloaded = " + numberOfApkDownloaded + ", numberOfApkInstalled = " + numberOfApInstalled
                    + ", installedApkList = " + installedApkList);

        }

        @Override
        public void onCellularDownloadSet(boolean cellularDownloadSet) {
            Log.d(TAG, "onCellularDownloadSet: " + cellularDownloadSet);
            appendText("onCellularDownloadSet: " + cellularDownloadSet);
        }

        @Override
        public void onSetConfigurationParameterStatus(int respCode, String respDesc) {
            Log.d(TAG, "onSetConfigurationParameterStatus, respCode = " + respCode + ", respDesc = " + respDesc);
            appendText("onSetConfigurationParameterStatus, respCode = " + respCode + ", respDesc = " + respDesc);
        }

        @Override
        public void onDeleteInternalStorageFinished(boolean isAllFileDeleted, ArrayList<String> failList) {
            Log.d(TAG, "onDeleteInternalStorageFinished, isAllFileDeleted = " + isAllFileDeleted + ", failList = " + failList);
            appendText("onDeleteInternalStorageFinished, isAllFileDeleted = " + isAllFileDeleted + ", failList = " + failList);
        }

        @Override
        public void onGetApplicationParametersResponse(AMP360Response amp360Response) {
            Log.d(TAG, "onGetApplicationParametersResponse, amp360Response: " + amp360Response);
            appendText("** onGetApplicationParametersResponse **, amp360Response: " + amp360Response);
        }

        @Override
        public void onGetApplicationParametersFail(String errorDesc) {
            Log.d(TAG, "onGetApplicationParametersFail, errorDesc = " + errorDesc);
            appendText("** onGetApplicationParametersFail **, errorDesc = " + errorDesc);
        }

        @Override
        public void onSetApplicationParameterResponse(AMP360Response amp360Response) {
            Log.d(TAG, "onSetApplicationParameterResponse, amp360Response: " + amp360Response);
            appendText("** onSetApplicationParameterResponse **, amp360Response: " + amp360Response);
        }

        @Override
        public void onSetApplicationParameterFail(String errorDesc) {
            Log.d(TAG, "onSetApplicationParameterFail, errorDesc = " + errorDesc);
            appendText("** onSetApplicationParameterFail **, errorDesc = " + errorDesc);
        }

    };

    private void appendText(final String str) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                ((TextView) findViewById(R.id.tvResponse)).append(str + "\n");
                /*((ScrollView) findViewById(R.id.svResponse)).post(new Runnable() {
                    @Override
                    public void run() {
                        ((ScrollView) findViewById(R.id.svResponse)).fullScroll(ScrollView.FOCUS_DOWN);
                    }
                });*/
            }
        });
    }

    private File createFileFromAssetsFolder() {
        File file = new File(getFilesDir(), "sample_file.txt");
        if (!file.exists()) {
            try {
                InputStream is = getAssets().open("test_upload_file.txt");
                byte[] buffer = new byte[1024];
                int count = is.read(buffer);
                is.close();
                FileOutputStream fos = new FileOutputStream(file);
                fos.write(Arrays.copyOfRange(buffer, 0, count));
                fos.close();
                return file;
            } catch (IOException e) {
                Log.e(TAG, "createFileFromAssetsFolder " + e.getMessage());
                e.printStackTrace();
                return null;
            }
        } else {
            Log.d(TAG, "File already exists (no need to create)");
            return file;
        }
    }
}
