package com.viddup.openglnative.render;

/**
 * author:chenjian
 * date:2020/7/6
 * email:chenjian@xiaoxiekeji.cn
 * desc:底层的渲染
 */
public class NativeRender {
    static {
        System.loadLibrary("native_lib");
    }

    public native void nInit();

    public native void nUnInit();

    public native void setImageData(int format,int width,int height,byte[] bytes);

    public native void nSurfaceCreated();

    public native void nSurfaceChanged(int width,int height);

    public native void nDrawFrame();
}
