package com.amobilepayment.demo.Main;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import org.dom4j.Element;
import org.dom4j.Node;

import java.util.List;

import AmpBaseInterface.AmpBaseInterface;
import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.TransactionContract;
import com.amobilepayment.demo.Utils.InternalConfig;

public class MenuMainAdapter extends BaseAdapter {
    private final static String TAG = MenuMainAdapter.class.getSimpleName();

    // Menu type
    private static final int MENU_TYPE_MAIN = 0;
    private static final int MENU_TYPE_DESKTOP = 1;
    private static final int MENU_TYPE_SUB_MAIN = 2;
    private static final int MENU_TYPE_SUB_SUB_MAIN = 3;    // all submenu (multi-level)
                                                            // of the first submenu belongs here

    private Context mContext;
    private final Node mMenuXml;

    public MenuMainAdapter(Context c, Node menuXml) {
        mContext = c;
        mMenuXml = menuXml;
    }

    @Override
    public int getCount() {
        return mMenuXml.selectNodes("./item").size();
    }

    @Override
    public Object getItem(int i) {
        return null;
    }

    @Override
    public long getItemId(int i) {
        return 0L;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        int layout_id = -1;
        View retView = null;

        // Choose the layout type: main menu OR sub menu
        int menuType = getItemViewType(position);
        switch (menuType) {
            case MENU_TYPE_MAIN:
                layout_id = R.layout.menu_mainitem;
                break;
            case MENU_TYPE_DESKTOP:
                layout_id = R.layout.menu_desktop_item;
                break;
            case MENU_TYPE_SUB_MAIN:
                layout_id = R.layout.menu_sub_item;
                break;
        }

        // if this is a recycled view, re-use it
        if(convertView == null) {
            retView = LayoutInflater.from(mContext).inflate(layout_id, parent, false);
        }
        else {
            retView = convertView;
        }

        // set menu item's text, description, and icon
        String menuXMLKey = getKeyFromXML(position);
        // determine which enum value
        TransactionContract.TransactionType transactionType =
                TransactionContract.determineTransactionTypeFromMenuXML(menuXMLKey);
        // title
        TextView tv_menuname = retView.findViewById(R.id.menu_name);
        tv_menuname.setText(transactionType.getMenuTitle());
        // description
        TextView tv_menudesc = retView.findViewById(R.id.menu_description);
        String menuDescription = transactionType.getMenuDescription();

        if("".equals(menuDescription) && tv_menudesc != null) {
            tv_menudesc.setVisibility(View.GONE);
        }
        else if(tv_menudesc != null){
            tv_menudesc.setText(menuDescription);
        }
        // icon
        ImageView tv_menuicon = retView.findViewById(R.id.menu_image);
        tv_menuicon.setImageResource(transactionType.getMenuIcon());

        return retView;
    }

    private String getKeyFromXML(int pos) {
        Element item = (Element) mMenuXml.selectNodes("./item").get(pos);
        Element name = (Element) item.selectSingleNode("name");
        return name.getText();
    }

    @Override
    public int getItemViewType(int position) {
        int retType = MENU_TYPE_MAIN;

        String s = ((Element)mMenuXml).attribute("type").getValue();

        if("desktop".equals(s)) retType = MENU_TYPE_DESKTOP;
        else if("mmenu".equals(s)) retType = MENU_TYPE_MAIN;
        else if("smenu".equals(s)) retType = MENU_TYPE_SUB_MAIN;
        else if("ssmenu".equals(s))retType = MENU_TYPE_SUB_MAIN;

        return retType;
    }
}
