//
// Created by ChenJian on 2020/7/21.
//

#include "GLRenderContext.h"
#include "GLES3/gl3.h"
#include "common.h"

GLRenderContext* GLRenderContext::m_pContext  = nullptr;

GLRenderContext::GLRenderContext() {
    m_pCurSample = new TriangleSample();
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

