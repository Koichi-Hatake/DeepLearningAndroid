/*
 * Copyright (C) 2018 Koichi Hatakeyama
 * All rights reserved.
 */
package net.seeeno.deeplearning;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.PixelFormat;
import android.graphics.PorterDuff.Mode;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;

public class SurfaceView extends android.view.SurfaceView implements Callback {

    private static final String TAG = "SurfaceView";

    private SurfaceHolder mHolder;

    private Paint mPaint;

    private Path mPath;

    private Bitmap mLastDrawBitmap;

    private Canvas mLastDrawCanvas;

    /** */
    static final private int PGM_WIDTH = 28;
    static final private int PGM_HEIGHT = 28;

    /** */
    static final private int LINE_WIDTH = 28;

    public SurfaceView(Context context) {
        super(context);
        init();
    }

    public SurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        mHolder = getHolder();

        setZOrderOnTop(true);
        mHolder.setFormat(PixelFormat.TRANSPARENT);

        mHolder.addCallback(this);

        mPaint = new Paint();
        mPaint.setColor(Color.BLACK);
        mPaint.setStyle(Paint.Style.STROKE);
        mPaint.setStrokeCap(Paint.Cap.ROUND);
        mPaint.setAntiAlias(true);
        mPaint.setStrokeWidth(LINE_WIDTH);
    }

    /** */
    public int[] getPgmArray() {

        // Rescale
        Log.v(TAG, "Original Size: " + mLastDrawBitmap.getWidth() + ":" + mLastDrawBitmap.getHeight());
        Bitmap resizeBitmap = Bitmap.createScaledBitmap(mLastDrawBitmap,
                PGM_WIDTH, PGM_HEIGHT,true);

        // Gray scale
        Log.v(TAG, "Size: " + resizeBitmap.getWidth() + ":" + resizeBitmap.getHeight());
        int[] grayArray = new int[PGM_WIDTH * PGM_HEIGHT];
        for(int i=0; i < PGM_HEIGHT; i++) {
            for(int j=0; j < PGM_WIDTH; j++) {
                int pixel = resizeBitmap.getPixel(j, i);
                int alpha = Color.alpha(pixel);
                int gray_rgb = Color.argb(0xFF, alpha, alpha, alpha);
                resizeBitmap.setPixel(j, i, gray_rgb);
                int index = j + i*PGM_WIDTH;
                //Log.v(TAG, "Location " + j + ":" + i + "->" + index + " 0x"+  Integer.toHexString(pixel) + "-> 0x" + Integer.toHexString(alpha));
                grayArray[index] = alpha;
            }
        }

        // Show converted image
        Canvas canvas = mHolder.lockCanvas();
        canvas.drawColor(0, Mode.CLEAR);
        android.graphics.Rect src = new android.graphics.Rect(0, 0, PGM_WIDTH, PGM_HEIGHT);
        android.graphics.Rect dst = new android.graphics.Rect(0, 0, mLastDrawBitmap.getWidth(), mLastDrawBitmap.getHeight());
        canvas.drawBitmap(resizeBitmap, src, dst,null);
        mHolder.unlockCanvasAndPost(canvas);

        return grayArray;
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        clearLastDrawBitmap();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        // TODO -- Calling recyle() in this timing will cause "java.lang.RuntimeException: Canvas".
        // It might need to call any api to free bitmap resources.
        //mLastDrawBitmap.recycle();
    }

    public void clearCanvas() {
        Canvas canvas = mHolder.lockCanvas();
        canvas.drawColor(0, Mode.CLEAR);
        mHolder.unlockCanvasAndPost(canvas);
        mLastDrawBitmap.recycle();
        mLastDrawBitmap = Bitmap.createBitmap(getWidth(), getHeight(),
                Config.ARGB_8888);
        mLastDrawCanvas = new Canvas(mLastDrawBitmap);
        mLastDrawCanvas.drawColor(0, Mode.CLEAR);
    }

    public Bitmap getBitmap() {
        return mLastDrawBitmap;
    }

    private void clearLastDrawBitmap() {
        if (mLastDrawBitmap == null) {
            mLastDrawBitmap = Bitmap.createBitmap(getWidth(), getHeight(),
                    Config.ARGB_8888);
        }

        if (mLastDrawCanvas == null) {
            mLastDrawCanvas = new Canvas(mLastDrawBitmap);
        }

        mLastDrawCanvas.drawColor(0, Mode.CLEAR);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                onTouchDown(event.getX(), event.getY());
                break;
            case MotionEvent.ACTION_MOVE:
                onTouchMove(event.getX(), event.getY());
                break;
            case MotionEvent.ACTION_UP:
                onTouchUp(event.getX(), event.getY());
                break;
            default:
                break;
        }
        return true;
    }

    private void onTouchDown(float x, float y) {
        mPath = new Path();
        mPath.moveTo(x, y);
    }

    private void onTouchMove(float x, float y) {
        mPath.lineTo(x, y);
        drawLine(mPath);
    }

    private void onTouchUp(float x, float y) {
        mPath.lineTo(x, y);
        drawLine(mPath);
        mLastDrawCanvas.drawPath(mPath, mPaint);
    }

    private void drawLine(Path path) {
        Canvas canvas = mHolder.lockCanvas();
        canvas.drawColor(0, Mode.CLEAR);
        canvas.drawBitmap(mLastDrawBitmap, 0, 0, null);
        canvas.drawPath(path, mPaint);
        mHolder.unlockCanvasAndPost(canvas);
    }

}