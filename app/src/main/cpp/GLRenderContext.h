//
// Created by ChenJian on 2020/7/21.
// native的OpenGL的绘制实例
//

#ifndef OPENGLNATIVE_GLRENDERCONTEXT_H
#define OPENGLNATIVE_GLRENDERCONTEXT_H


#include "sample/TriangleSample.h"

class GLRenderContext {
    GLRenderContext();

    ~GLRenderContext();

public:
    void setImageData(int format,int width,int height,uint8_t *pData);

    void onSurfaceCreated();

    void onSurfaceChanged(int width,int height);

    void onDrawFrame();

    static GLRenderContext* getInstance();

    static void destroyInstance();

private:
    static GLRenderContext *m_pContext;
    GLSampleBase *m_pBeforeSample;
    GLSampleBase *m_pCurSample;

    int m_screenW;
    int m_screenH;
};


#endif //OPENGLNATIVE_GLRENDERCONTEXT_H
