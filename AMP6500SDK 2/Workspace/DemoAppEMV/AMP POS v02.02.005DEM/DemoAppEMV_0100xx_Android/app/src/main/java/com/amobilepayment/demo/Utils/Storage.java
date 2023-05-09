package com.amobilepayment.demo.Utils;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.widget.ImageView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class Storage {
    private final static String TAG = Storage.class.getSimpleName();

    public static boolean setImageFromDownloads(Context context, ImageView imageView, String filename){
        boolean flag = false;

        File directory = context.getFilesDir();
        File image = new File(directory, "/appcfg/" + filename + ".png");
        try {
            Bitmap b = BitmapFactory.decodeStream(new FileInputStream(image));
            imageView.setImageBitmap(b);
            flag = true;
        } catch (FileNotFoundException e) {
            Log.i(TAG, "appcfg/ has no image. Using default " + filename + " image.");
        }

        return flag;
    }
}
