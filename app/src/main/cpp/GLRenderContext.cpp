//
// Created by ChenJian on 2020/7/21.
//

#include <ImageDef.h>
#include <TextureMapSample.h>
#include <NV21TextureMapSample.h>
#include "GLES3/gl3.h"
#include "common.h"
#include "GLRenderContext.h"

GLRenderContext* GLRenderContext::m_pContext  = nullptr;

GLRenderContext::GLRenderContext() {
    m_pCurSample = new NV21TextureMapSample();
    m_pBeforeSample = nullptr;
}

GLRenderContext::~GLRenderContext() {
    if(m_pCurSample){
        delete m_pCurSample;
        m_pCurSample = nullptr;
    }

    if(m_pBeforeSample){
        delete m_pBeforeSample;
        m_pBeforeSample = nullptr;
    }
}

void GLRenderContext::setImageData(int format, int width, int height, uint8_t *pData) {
    LOGE("GLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p", format, width, height, pData);
    NativeImage nativeImage;
    nativeImage.format = format;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = pData;

    switch (format){
        case IMAGE_FORMAT_NV12:
        case IMAGE_FORMAT_NV21:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            break;
        case IMAGE_FORMAT_I420:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
            break;
        default:
            break;
    }
    if(m_pCurSample){
        m_pCurSample->loadImage(&nativeImage);
    }
}

void GLRenderContext::onSurfaceCreated() {
    glClearColor(1.0f,1.0f,1.0f, 1.0f);
}

void GLRenderContext::onSurfaceChanged(int width, int height) {
    glViewport(0,0,width,height);
    m_screenW = width;
    m_screenH = height;
}

void GLRenderContext::onDrawFrame() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if (m_pBeforeSample){
        m_pBeforeSample->destroy();
        delete m_pBeforeSample;
        m_pBeforeSample = nullptr;
    }

    if(m_pCurSample){
        m_pCurSample->init();
        m_pCurSample->draw(m_screenW,m_screenH);
    }
}
GLRenderContext *GLRenderContext::getInstance() {
    if(m_pContext == nullptr){
        m_pContext = new GLRenderContext();
    }
    return m_pContext;
}

void GLRenderContext::destroyInstance() {
    if(m_pContext){
        delete m_pContext;
        m_pContext = nullptr;
    }
}

