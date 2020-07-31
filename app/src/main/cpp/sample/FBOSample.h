//
// Created by ChenJian on 2020/7/30.
//

#ifndef OPENGLNATIVE_FBOSAMPLE_H
#define OPENGLNATIVE_FBOSAMPLE_H


#include "GLSampleBase.h"
#include "../utils/ImageDef.h"
#include "../../../../../../../Library/Android/sdk/ndk/21.1.6352462/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/GLES3/gl3.h"

class FBOSample : public GLSampleBase{
public:
    FBOSample();

    virtual ~FBOSample();

    virtual void loadImage(NativeImage *pImage);

    virtual void init();

    virtual void draw(int screenW,int screenH);

    virtual void destroy();

    bool createFrameBufferObj();

private:
    GLuint m_ImageTextureId;
    GLuint m_FboTextureId;
    GLuint m_FboId;
    GLuint m_VaoIds[2];
    GLuint m_VboIds[4];
    GLuint m_SamplerLoc;
    NativeImage m_RenderImage;
    GLuint m_FboProgramObj;
    GLuint m_FboVertexShader;
    GLuint m_FboFragmentShader;
    GLint m_FboSamplerLoc;
};


#endif //OPENGLNATIVE_FBOSAMPLE_H
