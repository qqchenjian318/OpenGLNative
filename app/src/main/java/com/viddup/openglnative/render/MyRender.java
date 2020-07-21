package com.viddup.openglnative.render;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * author:chenjian
 * date:2020/7/6
 * email:chenjian@xiaoxiekeji.cn
 * desc:
 */
public class MyRender implements GLSurfaceView.Renderer {

    private NativeRender mRender;
    public MyRender(NativeRender render){
        mRender = render;
    }
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        if (mRender != null){
            mRender.nSurfaceCreated();
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if (mRender != null){
            mRender.nSurfaceChanged(width, height);
        }
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        if (mRender != null){
            mRender.nDrawFrame();
        }
    }
}
