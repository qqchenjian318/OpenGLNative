//
// Created by ChenJian on 2020/7/6.
//

#include <jni.h>
#include "GLRenderContext.h"

extern "C" {

JNIEXPORT void JNICALL
Java_com_viddup_openglnative_render_NativeRender_nInit(JNIEnv *env, jobject thiz) {
    GLRenderContext::getInstance();
}

JNIEXPORT void JNICALL
Java_com_viddup_openglnative_render_NativeRender_nUnInit(JNIEnv *env, jobject thiz) {
    GLRenderContext::destroyInstance();
}

JNIEXPORT void JNICALL
Java_com_viddup_openglnative_render_NativeRender_setImageData(JNIEnv *env, jobject thiz,
                                                              jint format, jint width, jint height,
                                                              jbyteArray bytes) {
    int len = env->GetArrayLength(bytes);
    auto* buf = new uint8_t[len];
    env->GetByteArrayRegion(bytes, 0, len, reinterpret_cast<jbyte*>(buf));
    GLRenderContext::getInstance()->setImageData(format,width,height,buf);
    delete[] buf;
    env->DeleteLocalRef(bytes);
}

JNIEXPORT void JNICALL
Java_com_viddup_openglnative_render_NativeRender_nSurfaceCreated(JNIEnv *env, jobject instance) {
    GLRenderContext::getInstance()->onSurfaceCreated();
}

JNIEXPORT void JNICALL
Java_com_viddup_openglnative_render_NativeRender_nSurfaceChanged(JNIEnv *env, jobject thiz,
                                                                 jint width, jint height) {
    GLRenderContext::getInstance()->onSurfaceChanged(width, height);
}

JNIEXPORT void JNICALL
Java_com_viddup_openglnative_render_NativeRender_nDrawFrame(JNIEnv *env, jobject thiz) {
    GLRenderContext::getInstance()->onDrawFrame();
}

}

