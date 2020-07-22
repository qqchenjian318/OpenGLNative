//
// Created by ChenJian on 2020/7/21.
//加载图片数据
//

#include <GLUtils.h>
#include "TextureMapSample.h"

TextureMapSample::TextureMapSample() {
    m_TextureId = 0;
}

TextureMapSample::~TextureMapSample() {
    NativeImageUtil::FreeNativeImage(&m_RenderImage);
}

void TextureMapSample::init() {
    if (m_ProgramObj != 0) {
        return;
    }
    //create RGBA texture
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);//创建一个2D纹理
    //设置s轴的拉伸方式为截取（s轴 横轴）
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //设置t轴的拉伸方式为截取（t轴 纵轴）
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //设置纹理的采样方式 线性采样
    // (GL_LINEAR:相邻的若干像素点 加权平均计算,
    // GL_NEAREST:使用纹理中坐标最接近的一个像素的颜色作为需要绘制的像素颜色)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    char vShaderStr[] =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 a_position;   \n"
            "layout(location = 1) in vec2 a_texCoord;   \n"
            "out vec2 v_texCoord;                       \n"
            "void main()                                \n"
            "{                                          \n"
            "   gl_Position = a_position;               \n"
            "   v_texCoord = a_texCoord;                \n"
            "}                                          \n";

    char fShaderStr[] =
            "#version 300 es                                     \n"
            "precision mediump float;                            \n"
            "in vec2 v_texCoord;                                 \n"
            "layout(location = 0) out vec4 outColor;             \n"
            "uniform sampler2D s_TextureMap;                     \n"
            "void main()                                         \n"
            "{                                                   \n"
            "  outColor = texture(s_TextureMap, v_texCoord);     \n"
            "}                                                   \n";

    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr, m_VertexShader, m_FragmentShader);

    if (m_ProgramObj) {
        m_SamplerLoc = glGetUniformLocation(m_ProgramObj, "s_TextureMap");
    } else {
        LOGE("TextureMapSample::Init create program fail");
    }
}

void TextureMapSample::draw(int screenW, int screenH) {
    LOGD("TextureMapSample::Draw()");

    if (m_ProgramObj == GL_NONE || m_TextureId == GL_NONE) {
        LOGE("TextureMapSample::Draw() m_ProgramObj == GL_NONE || m_TextureId == GL_NONE ");
        return;
    }

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    //渲染坐标系
    GLfloat verticesCoords[] = {
            -1.0f, 0.5f, 0.0f,//position 0
            -1.0f, -0.5f, 0.0f,//position 1
            1.0f, -0.5f, 0.0f,//position 2
            1.0f, 0.5f, 0.0f//position 3
    };
    //纹理坐标系
    GLfloat textureCoords[] = {
            0.0f, 0.0f,//texCoord 0
            0.0f, 1.0f,//texCoord 1
            1.0f, 1.0f,//texCoord 2
            1.0f, 0.0f,//texCoord 3
    };

    GLushort indices[] = {0, 1, 2, 0, 2, 3};
    LOGD("TextureMapSample::Draw()  %p,w=%d,h=%d", m_RenderImage.ppPlane[0], m_RenderImage.width,
         m_RenderImage.height);
    //upload rgba image data;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_RenderImage.width, m_RenderImage.height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, m_RenderImage.ppPlane[0]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    //use the program object
    glUseProgram(m_ProgramObj);

    //load the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), verticesCoords);

    //load the texture coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), textureCoords);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //bind the rgba map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    //set the rgba map sampler to texture unit to 0
    glUniform1i(m_SamplerLoc, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

}

void TextureMapSample::loadImage(NativeImage *pImage) {
    LOGE("TextureMapSample::loadImage pImage=%p", pImage);
    if (pImage) {
        m_RenderImage.width = pImage->width;
        m_RenderImage.height = pImage->height;
        m_RenderImage.format = pImage->format;
        NativeImageUtil::CopyNativeImage(pImage, &m_RenderImage);
    }
}

void TextureMapSample::destroy() {
    if (m_ProgramObj) {
        glDeleteProgram(m_ProgramObj);
        glDeleteTextures(1, &m_TextureId);
        m_ProgramObj = GL_NONE;
    }
}