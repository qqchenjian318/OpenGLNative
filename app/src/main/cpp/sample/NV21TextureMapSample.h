//
// Created by ChenJian on 2020/7/22.
//

#ifndef OPENGLNATIVE_NV21TEXTUREMAPSAMPLE_H
#define OPENGLNATIVE_NV21TEXTUREMAPSAMPLE_H


#include "GLSampleBase.h"
#include "../utils/ImageDef.h"

class NV21TextureMapSample : public GLSampleBase{
public:
    NV21TextureMapSample(){
        m_yTextureId = GL_NONE;
        m_uvTextureId = GL_NONE;

        m_ySamplerLoc = GL_NONE;
        m_uvSamplerLoc = GL_NONE;
    }

    virtual ~NV21TextureMapSample(){
        NativeImageUtil::FreeNativeImage(&m_RenderImage);
    }

    virtual void loadImage(NativeImage *pImage);

    virtual void init();

    virtual void draw(int screenW,int screenH);

    virtual void destroy();

private:
    GLuint m_yTextureId;
    GLuint m_uvTextureId;

    GLint m_ySamplerLoc;
    GLint m_uvSamplerLoc;

    NativeImage m_RenderImage;
};


#endif //OPENGLNATIVE_NV21TEXTUREMAPSAMPLE_H
