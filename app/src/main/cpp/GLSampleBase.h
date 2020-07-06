//
// Created by ChenJian on 2020/7/1.
//

#include "GLES3/gl3.h"

#ifndef MEDIASDKDEMO_GLSAMPLEBASE_H
#define MEDIASDKDEMO_GLSAMPLEBASE_H

#endif //MEDIASDKDEMO_GLSAMPLEBASE_H

class GLSampleBase{

public:
    GLSampleBase(){
        m_ProgramObj = 0;
        m_VertexShader = 0;
        m_FragmentShader = 0;

        m_SurfaceWidth = 0;
        m_SurfaceHeight = 0;
    }

    virtual ~GLSampleBase(){

    }

    virtual void init() = 0;

    virtual void draw(int screenW,int screenH) = 0;

    virtual void destroy() = 0;



protected:
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_ProgramObj;

    int m_SurfaceWidth;
    int m_SurfaceHeight;
};
