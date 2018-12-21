/*
 * Copyright (C) 2018 Koichi Hatakeyama
 * All rights reserved.
 */
package net.seeeno.deeplearning;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.File;
import java.io.IOException;

public class MainActivity extends Activity implements View.OnClickListener {

    static {
        System.loadLibrary("nnabla_android");
    }

    private static final String TAG = "MainActivity";

    private native String stringFromJNI();
    private native void nativeInitNeuralNetwork(String nppPath, String networkName);
    //private native float[] nativePredict(float imageData[]);
    private native float[] nativePredict(String pgm_path);

    private android.content.Context mContext;
    //private final static String FILE_NNP = "lenet_010000.nnp";
    private final static String FILE_NNP = "mnist0_9_result_train.nnp";
    private final static String NETWORK_NAME = "Executor";
    private final static String PGM_FILE = "5.pgm";

    private void copyAssetsToLocal() {
        try {
            InputStream inputStream = getAssets().open(FILE_NNP);
            FileOutputStream fileOutputStream  = new FileOutputStream(new File(mContext.getFilesDir() + "/" + FILE_NNP), false);
            byte[] buffer = new byte[1024];
            int length = 0;
            while ((length = inputStream.read(buffer)) >= 0) {
                fileOutputStream.write(buffer, 0, length);
            }
            fileOutputStream.close();
            inputStream.close();

            inputStream = getAssets().open(PGM_FILE);
            fileOutputStream  = new FileOutputStream(new File(mContext.getFilesDir() + "/" + PGM_FILE), false);
            buffer = new byte[1024];
            length = 0;
            while ((length = inputStream.read(buffer)) >= 0) {
                fileOutputStream.write(buffer, 0, length);
            }
            fileOutputStream.close();
            inputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.analyze).setOnClickListener(this);
        findViewById(R.id.clear).setOnClickListener(this);

        mContext = getApplicationContext();
        copyAssetsToLocal();
        nativeInitNeuralNetwork(
                mContext.getFilesDir() + "/" + FILE_NNP,
                NETWORK_NAME
        );
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.analyze:
                // TODO
                float predictArray[] = nativePredict(mContext.getFilesDir() + "/" + PGM_FILE);
                int index = 0;
                float score = 0;
                for(int i=0; i < predictArray.length; i++) {
                    Log.v(TAG, i + ": " + predictArray[i]);
                    if (score < predictArray[i]) {
                        score = predictArray[i];
                        index = i;
                    }
                }

                ((TextView)findViewById(R.id.result)).setText(Integer.toString(index));
                break;
            case R.id.clear:
                ((TextView)findViewById(R.id.result)).setText("");
                ((SurfaceView)findViewById(R.id.surface_view)).clearCanvas();
                break;
            default:
                break;
        }
    }
}
