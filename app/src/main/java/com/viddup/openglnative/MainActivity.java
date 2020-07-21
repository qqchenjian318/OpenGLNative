package com.viddup.openglnative;

import androidx.appcompat.app.AppCompatActivity;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.View;

import com.viddup.openglnative.render.MyRender;
import com.viddup.openglnative.render.NativeRender;

public class MainActivity extends AppCompatActivity {
    GLSurfaceView surfaceView;
    NativeRender nativeRender = new NativeRender();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        surfaceView = findViewById(R.id.gl_view);
        nativeRender.nInit();
        surfaceView.setEGLContextClientVersion(3);
        surfaceView.setRenderer(new MyRender(nativeRender));

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        nativeRender.nUnInit();
    }
}