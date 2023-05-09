package com.amobilepayment.demo.Main;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.FragmentManager;
import android.util.Log;
import android.util.Xml;
import android.view.View;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.Toast;

import org.dom4j.Element;
import org.dom4j.Node;

import java.io.IOException;
import java.io.InputStream;
import java.util.Locale;

import com.amobilepayment.demo.Flow.NoticeDialogFragment;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.Transaction;
import com.amobilepayment.demo.Transactions.TransactionContract;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.Storage;
import com.amobilepayment.demo.Utils.XMLUtil;

public class MenuActivity extends SessionActivity
        implements NoticeDialogFragment.NoticeDialogListener,
                    UserLoginTask.LoginTaskListener,
                    PasswordAdminSetDialogFragment.OnAdminPasswordUpdateListener {

    public enum USER_TYPE {
        OPERATOR,
        MERCHANT,
        PROCESSOR
    }

    private final String TAG = MenuActivity.class.getSimpleName();

    static final String INTENT_DATA = "menu_data";
    static final String INTENT_DATA_DESKTOP = "menu_data_as_desktop";
    private boolean isAtMainMenu = false;
    public static Transaction currentTransaction;
    private Locale currentLocale = null;
    private BaseAdapter mMenuAdapter;
    private Node xmlMenu;
    private int mSelectedPosition;
    private boolean startSettingsPage = false;
    private USER_TYPE mUserType = USER_TYPE.OPERATOR;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);

        GridView gridView;

        // If the intent has extra string data, it means that this menu is a submenu or a desktop menu.
        if(getIntent().hasExtra(INTENT_DATA)) {
            isAtMainMenu = false;
            String intentData = getIntent().getStringExtra(INTENT_DATA);
            Node _xmlmenu = null;
            try {
                _xmlmenu = XMLUtil.parseString(intentData);
            } catch (Exception e) {
                e.printStackTrace();
            }

            xmlMenu = _xmlmenu;

            // we have 3 types of sub-menus
            //      1. main sub-menu
            //      2. sub (and so on) sub-menu with 2 options only
            //      3. sub (and so on) sub-menu with 3+ options
            //
            // Sub-menus should be directly related to the main menu items, but easy to identify as a different
            // set of options. To achieve this, the cards are scaled down to 2/3 height, this provides the same
            // scrolling list with a visual differentiation for the more specific options (Figure 3). If one of more
            // menu screens persist after the initial sub-menu, the cards should shrink vertically and become a
            // wide button list with only text labels. If there are two or less options, these should be center
            // aligned (Figure 4), and if there are three or more the list should begin from the top of the page
            // (Figure 5).

            // UI of sub menu vs sub sub menu is very different. Let's load the correct xml layout here.
            if(isSubSubMenu()) {
                int menuItemCount = xmlMenu.selectNodes("./item").size();
                if(menuItemCount < 3)
                    setContentView(R.layout.activity_sub_sub_menu);
                else
                    setContentView(R.layout.activity_sub_sub_menu_three_plus);
            }
            else {
                setContentView(R.layout.activity_menu);
            }

            gridView = findViewById(R.id.gridView);

            if(getIntent().hasExtra(INTENT_DATA_DESKTOP)) {
                isAtMainMenu = getIntent().getBooleanExtra(INTENT_DATA_DESKTOP, false);

                gridView.setNumColumns(2);
            }
            // two differences between main menu vs sub menu
            //      1. vertical spacing (fixed here)
            //      2. height of each card (fixed in MenuMainAdapter.getView())
            else if(isSubMenu()) {
                gridView.setVerticalSpacing((int)getResources().getDimension(R.dimen.menu_sub_vertical_spacing));
            }
        }
        else {
            isAtMainMenu = true;
            xmlMenu = readMenuAsset();
            setContentView(R.layout.activity_menu);
            gridView = findViewById(R.id.gridView);
        }

        // read header logo
        ImageView imageView_header = findViewById(R.id.header_logo);
        Storage.setImageFromDownloads(this, imageView_header, "header_logo");

        // setup adapter for menu cards that look the same (desktop, main, sub)
        if(!isSubSubMenu()) {
            mMenuAdapter = new MenuMainAdapter(this, xmlMenu);
        }
        else {
            mMenuAdapter = new MenuSubSubAdapter(this, xmlMenu);
        }

        gridView.setAdapter(mMenuAdapter);
        gridView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View v,
                                    int position, long id) {
                SettingsUtil.triggerBeep(MenuActivity.this);

                mSelectedPosition = position;
                mUserType = USER_TYPE.OPERATOR;

                validateUser();
            }
        });

    }

    private final static String PASS_NONE      = "NONE";
    private final static String PASS_OPERATOR  = "OPERATORPASS";
    private final static String PASS_MERCHANT  = "MERCHANTPASS";
    private final static String PASS_PROCESSOR = "PROCESSORPASS";
    private final static String PASS_BYPASS    = "MERCHBYPASS";

    /**
     * Checks the password requirements from InternalCfg.xml
     */
    private void validateUser() {
        // get the permission level needed by this transaction
        Node clickedItem = xmlMenu.selectNodes("./item").get(mSelectedPosition);
        String attribute = clickedItem.valueOf("@permission");
        String permission = PASS_NONE;

        switch (permission) {
            case PASS_OPERATOR:
                {
                    // TODO: check login from AcctMgt.cpp->OperatorPassword()

                    boolean flag = false;
                    String _data = "Y";//AmpBaseInterface.GetCfgData("TERMINAL.PROCESSINGOPTION.OPERATORID.ENABLED");
                    if("Y".equals(_data)) flag = true;

                    // if not yet signed in, ask for password
                    if(flag && !SettingsUtil.operatorAlreadySignedIn(this)) {
                        PasswordOperatorDialogFragment dialog_operator = new PasswordOperatorDialogFragment();
                        dialog_operator.setListener(this);
                        dialog_operator.setCallingActivity(this);
                        FragmentManager fm = getSupportFragmentManager();
                        dialog_operator.show(fm, "PasswordOperatorDialogFragment");
                    }
                    // else do the action without the need for password
                    else {
                        determineWhatToDo();
                    }
                }
                break;
            case PASS_BYPASS:
                // If bypassable, let's ask for merchant password first.
                // If it does not match, try the processor password to do the actual bypass.
                // This actual process is implemented in UserLoginTask class.
                mUserType = USER_TYPE.MERCHANT;
                showAdminPasswordDialog(PasswordAdminDialogFragment.TYPE_MERCHANT, true);
                break;
            case PASS_MERCHANT:
                mUserType = USER_TYPE.MERCHANT;
                showAdminPasswordDialog(PasswordAdminDialogFragment.TYPE_MERCHANT);
                break;
            case PASS_PROCESSOR:
                mUserType = USER_TYPE.PROCESSOR;
                showAdminPasswordDialog(PasswordAdminDialogFragment.TYPE_PROCESSOR);
                break;
            case PASS_NONE:
            default:
                mUserType = USER_TYPE.OPERATOR;
                determineWhatToDo();
                break;
        }
    }

    /**
     * This function determines what to do with menu item click. The action is either
     * load the submenu or proceed with the selected transaction.
     */
    private void determineWhatToDo() {
        Node submenu = null;

        // identify which node item was clicked
        Node clickedItem = xmlMenu.selectNodes("./item").get(mSelectedPosition);

        // get the clicked item's children nodes
        submenu = clickedItem.selectSingleNode("./menu");

        if(submenu == null) {
            // Complete the transaction
            performTransaction(clickedItem);
        }
        else {
            // Launch the submenu by passing the <menu> tag with <item>s inside;
            // This should be able to support unlimited number of submenus;
            Intent intent = new Intent(getApplicationContext(), MenuActivity.class);
            intent.putExtra(INTENT_DATA, submenu.asXML());
            startActivity(intent);
        }
    }

    private void performTransaction(Node clickedItem) {
        // identify the key
        String keyFromXML = null;
        Element name = (Element) clickedItem.selectSingleNode("name");
        keyFromXML = name.getText();

        if(keyFromXML == null) return;

        // now that we have the key, determine the transaction ID
        TransactionContract.TransactionType transactionType = TransactionContract.determineTransactionTypeFromMenuXML(keyFromXML);
        long trxId = transactionType.getTransactionId();

        MenuActivity.currentTransaction = new Transaction(this, trxId);
        MenuActivity.currentTransaction.performTransaction();
    }

    @Override
    protected void onResume() {
        // keep the keyboard hidden after password cancel (PasswordOperatorDialogFragment)
        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_MODE_CHANGED);

        // if locale has changed, schedule activity for recreation
        Locale newLocale = SettingsUtil.getCurrentLocale(this);
        if(currentLocale != null && !newLocale.equals(currentLocale)) {
            SettingsUtil.updateActivityLang(this);
            Handler handler = new Handler();
            handler.postDelayed(new Runnable()
            {
                @Override
                public void run()
                {
                    // TODO: This is necessary if RTL languages are supported.
                    //       Note that this will cause an activity flicker due to recreation process
                    //
                    // recreate();
                    //
                    //       Meanwhile, string refresh is sufficient.
                    mMenuAdapter.notifyDataSetChanged();
                }
            }, 100);
        }
        currentLocale = newLocale;

        super.onResume();
    }

    // returns NULL if menu asset is not readable;
    // returns the child nodes of root menu which
    // are multiple <item>s, thus returning NodeList
    private Node readMenuAsset() {
        Node retData = null;
        InputStream is = null;

        try {
            is = getAssets().open("menu.xml");
            retData = XMLUtil.parseFile(is);
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        finally {
            try {
                if(is != null) is.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return retData;
    }

    @Override
    public void onBackPressed() {
        SettingsUtil.triggerBeep(this);

        super.onBackPressed();
    }

    @Override
    public void onDialogPositiveClick(DialogFragment dialog) {
        logOff();
    }

    @Override
    public void onDialogNegativeClick(DialogFragment dialog) {

    }

    public void settingsButtonClicked(View view) {
        startSettingsPage = true;
        mUserType = USER_TYPE.MERCHANT;

        SettingsUtil.triggerBeep(this);

        String permission = null;//AmpBaseInterface.GetCfgData("TERMINAL.PASSWORDOPTION.MENU.DEVICESETTING");
        if(permission == null) permission = PASS_NONE;

        // settings page is password protected
        switch (permission) {
            case PASS_BYPASS:
                showAdminPasswordDialog(PasswordAdminDialogFragment.TYPE_MERCHANT, true);
                break;
            default:
                showAdminPasswordDialog(PasswordAdminDialogFragment.TYPE_MERCHANT);
        }
    }

    @Override
    public void onLoginTaskCompleted() {

        // after successful login of merchant/processor,
        // ask to reset password if password is default value
        if((mUserType == USER_TYPE.MERCHANT && SettingsUtil.isMerchantPasswordDefault()) ||
                (mUserType == USER_TYPE.PROCESSOR && SettingsUtil.isProcessorPasswordDefault())) {
            // update merchant pwd
            SettingsUtil.showMerchantSetPasswordDialog(this, this, mUserType);

            // do not allow merchant/processor to proceed without changing the default password
            return;
        }

        determineWhatToDo();
    }

    @Override
    public void onLoginTaskCancelled() {
        // nothing to do
    }

    @Override
    public void onLoginTaskIncorrect() {
        Toast.makeText(this,
                "Incorrect Password",
                Toast.LENGTH_LONG).show();
    }

    @Override
    public void onLoginTaskStarted() {
    }

    private void showAdminPasswordDialog(short type) {
        showAdminPasswordDialog(type, false);
    }

    private void showAdminPasswordDialog(short type, boolean enableByPass) {

        if(SettingsUtil.isAdminPasswordMaxRetry(this, type)) return;

        PasswordAdminDialogFragment dialog = new PasswordAdminDialogFragment();
        dialog.setDialogType(type);
        dialog.enableByPass(enableByPass);
        dialog.setListener(this);
        dialog.setCallingActivity(this);
        FragmentManager fm = getSupportFragmentManager();
        dialog.show(fm, "PasswordAdminDialogFragment");
    }

    @Override
    public void onUpdateCompleted() {
        String msg = "Password changed successfully<";
        Toast.makeText(this, msg, Toast.LENGTH_LONG).show();

        // now that merchant password has been updated, proceed to selected transaction a while back
        onLoginTaskCompleted();
    }

    private boolean isSubMenu() {
        boolean flag = false;
        String s = ((Element)xmlMenu).attribute("type").getValue();
        if("smenu".equals(s)) flag = true;
        return flag;
    }

    private boolean isSubSubMenu() {
        boolean flag = false;
        String s = ((Element)xmlMenu).attribute("type").getValue();
        if("ssmenu".equals(s)) flag = true;
        return flag;
    }
}
