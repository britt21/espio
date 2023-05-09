package com.amobilepayment.demo.Main;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Transactions.TransactionContract;
import com.amobilepayment.demo.Utils.InternalConfig;

import org.dom4j.Element;
import org.dom4j.Node;

import java.util.List;

import AmpBaseInterface.AmpBaseInterface;

public class MenuSubSubAdapter extends BaseAdapter {
    private final static String TAG = MenuSubSubAdapter.class.getSimpleName();

    // Menu type
    private static final int MENU_TYPE_MAIN = 0;
    private static final int MENU_TYPE_DESKTOP = 1;
    private static final int MENU_TYPE_SUB_MAIN = 2;
    private static final int MENU_TYPE_SUB_SUB_MAIN = 3;    // all submenu (multi-level)
                                                            // of the first submenu belongs here

    private Context mContext;
    private final Node mMenuXml;

    public MenuSubSubAdapter(Context c, Node menuXml) {
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
        View retView = null;

        // if this is a recycled view, re-use it
        if(convertView == null) {
            retView = LayoutInflater.from(mContext).inflate(R.layout.menu_sub_sub_item, parent, false);
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

        return retView;
    }

    private String getKeyFromXML(int pos) {
        Element item = (Element) mMenuXml.selectNodes("./item").get(pos);
        Element name = (Element) item.selectSingleNode("name");
        return name.getText();
    }

    @Override
    public int getItemViewType(int position) {
        return 0;
    }

//    /**
//     * Always load from the original menu xml passed to this adapter so can reshow hidden
//     * fields and vice versa. This is an important component so we can hide/show menu items
//     * on-the-fly.
//     * IMPORTANT: This won't support on-the-fly hide/show for main menu items! I don't think
//     * it is happening anyways. In fact, this is only useful for Admin -> Sign In Operator and
//     * Admin -> Sign Out Operator menu options as of this writing.
//     * @param mOriginalMenuString contains the original menu string containing the hidden and
//     *                            shown fields
//     * @return the xml node with hidden fields removed from DOM
//     */
//    private void loadShowableElements(String mOriginalMenuString) {
//        Node menu = XMLUtil.parseString(mOriginalMenuString);
//
//        // traverse all items in menu
//        List<Node> nodes = mMenuXml.selectNodes("./item");
//        for(int i = 0; i < nodes.size(); i++) {
//            Node node = nodes.get(i);
//            // show / hide this item based on InternalCfg.xml
//            Node name = node.selectSingleNode("./name");
//            String show = name.valueOf("@show");
//            String showValue = AmpBaseInterface.GetCfgData(show);
//            if("N".equals(showValue)) node.detach();
//        }
//
//        // update the parent node that came from MenuActivity by
//        // so it will know the repositioned items
//        $element.add(node.detach());
//
//        // lastly trigger notifyDataSetChanged()!
//    }
}
