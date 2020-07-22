//
// Created by ChenJian on 2020/7/21.
// 纹理使用示例
//

#ifndef OPENGLNATIVE_TEXTUREMAPSAMPLE_H
#define OPENGLNATIVE_TEXTUREMAPSAMPLE_H


#include <ImageDef.h>
#include "GLSampleBase.h"

class TextureMapSample : public GLSampleBase{
public:
    TextureMapSample();

    virtual ~TextureMapSample();

    virtual void loadImage(NativeImage *pImage);

    virtual void init();

    virtual void draw(int screenW,int screenH);

    virtual void destroy();

private:
    GLuint m_TextureId;
    GLint m_SamplerLoc;
    NativeImage m_RenderImage;
};


#endif //OPENGLNATIVE_TEXTUREMAPSAMPLE_H
