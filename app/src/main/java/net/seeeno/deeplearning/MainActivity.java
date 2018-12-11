package net.seeeno.deeplearning;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends Activity implements View.OnClickListener {

    static {
        //System.loadLibrary("archive");
        //System.loadLibrary("nnabla");
        //System.loadLibrary("nnabla_utils");
        System.loadLibrary("nnabla_android");
    }

    public native String stringFromJNI();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.analyze).setOnClickListener(this);
        findViewById(R.id.clear).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.analyze:
                // TODO
                break;
            case R.id.clear:
                //((TextView)findViewById(R.id.result)).setText("");
                ((TextView)findViewById(R.id.result)).setText(stringFromJNI());
                ((SurfaceView)findViewById(R.id.surface_view)).clearCanvas();
                break;
            default:
                break;
        }
    }
}
