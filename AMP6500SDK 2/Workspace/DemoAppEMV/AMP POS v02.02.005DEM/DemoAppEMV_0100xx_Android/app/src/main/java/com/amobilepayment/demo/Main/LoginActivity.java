package com.amobilepayment.demo.Main;

import android.content.Intent;
import android.graphics.LinearGradient;
import android.graphics.Shader;
import android.graphics.drawable.PaintDrawable;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.RectShape;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import AmpBaseInterface.AmpBaseInterface;

import com.amobilepayment.demo.R;
import com.amobilepayment.demo.Utils.SettingsUtil;
import com.amobilepayment.demo.Utils.Storage;
import com.amobilepayment.demo.Utils.XMLUtil;

import org.dom4j.Node;

import java.io.IOException;
import java.io.InputStream;

import static com.amobilepayment.demo.Main.MenuActivity.INTENT_DATA;
import static com.amobilepayment.demo.Main.MenuActivity.INTENT_DATA_DESKTOP;

public class LoginActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        SettingsUtil.updateActivityLang(this);

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        Thread.setDefaultUncaughtExceptionHandler(new CrashExceptionHandler(getApplicationContext()));

        // set string resources via JNI
        TextView tv_welcome = findViewById(R.id.tv_welcome);
        tv_welcome.setText("Welcome");
        TextView tv_enteryour = findViewById(R.id.tv_enteryour);
        tv_enteryour.setText("Tap Anywhere to Start");

        TextView tv_menu = findViewById(R.id.tv_menu);
        tv_menu.setText("Main Menu");
        TextView tv_desktop = findViewById(R.id.tv_desktop);
        tv_desktop.setText("Desktop");

        // read desktop logo
        ImageView imageView_desktop = findViewById(R.id.desktop_logo);
        Storage.setImageFromDownloads(this, imageView_desktop, "desktop_logo");

        // Client app handling
        SettingsUtil.setAsStandAlone(this, true);

        drawBackgroundGradient(findViewById(R.id.home_layout));
    }

    public void startMenuActivity(View view) {
        SettingsUtil.triggerBeep(this);

        Intent intent = new Intent(getApplicationContext(), MenuActivity.class);
        startActivity(intent);
    }

    public void startMenuAsDesktop(View view) {
        SettingsUtil.triggerBeep(this);

        Node submenu = readMenuDesktopAsset();

        Intent intent = new Intent(getApplicationContext(), MenuActivity.class);
        intent.putExtra(INTENT_DATA, submenu.asXML());
        intent.putExtra(INTENT_DATA_DESKTOP, true);
        startActivity(intent);
    }

    // returns NULL if menu asset is not readable;
    // returns the child nodes of root menu which
    // are multiple <item>s, thus returning NodeList
    private Node readMenuDesktopAsset() {
        Node retData = null;
        InputStream is = null;

        try {
            is = getAssets().open("menu.xml");
            Node xml = XMLUtil.parseFile(is);
            retData = xml.selectSingleNode("./desktop/menu");
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

    private void drawBackgroundGradient(View bg) {
        ShapeDrawable.ShaderFactory sf = new ShapeDrawable.ShaderFactory() {
            @Override
            public Shader resize(int width, int height) {
                return new LinearGradient(width/2, 0, width/2, height,
                        new int[]{0xff50d2c2, 0xff50d2c2, 0xffffffff},
                        new float[]{0, 0.3f, 1},
                        Shader.TileMode.CLAMP);
            }
        };
        PaintDrawable pd = new PaintDrawable();
        pd.setShape(new RectShape());
        pd.setShaderFactory(sf);
        bg.setBackground(pd);
    }
}

