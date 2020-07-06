//
// Created by ChenJian on 2020/7/1.
//
#include <jni.h>
#include "GLUtils.h"

GLuint GLUtils::LoadShader(GLenum shaderType, const char *pSource) {
    GLuint shader = 0;

    shader = glCreateShader(shaderType);
    if(shader){
        glShaderSource(shader,1,&pSource, nullptr);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
        if(!compiled){
            GLint infoLen = 0;
            glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infoLen);
            if(infoLen){
                char* buf = (char*)malloc(infoLen);
                if(buf){
                    glGetShaderInfoLog(shader,infoLen, nullptr,buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}
GLuint GLUtils::CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource, GLuint &vertexShaderHandle, GLuint &fragShaderHandle) {
    GLuint program = 0;
    vertexShaderHandle = LoadShader(GL_VERTEX_SHADER, pVertexShaderSource);
    if (!vertexShaderHandle) return program;
    fragShaderHandle = LoadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
    if (!fragShaderHandle) return program;

    program = glCreateProgram();
    if(program){
        glAttachShader(program, vertexShaderHandle);
        CheckGLError("glAttachShader");
        glAttachShader(program, fragShaderHandle);
        CheckGLError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        glDetachShader(program, vertexShaderHandle);
        glDeleteShader(vertexShaderHandle);
        vertexShaderHandle = 0;
        glDetachShader(program, fragShaderHandle);
        glDeleteShader(fragShaderHandle);
        fragShaderHandle = 0;

        if (linkStatus != GL_TRUE){
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = (char*) malloc((size_t)bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
//                    LOGCATE("GLUtils::CreateProgram Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint GLUtils::CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource) {
    return 0;
}

void GLUtils::CheckGLError(const char *pGLOperation) {
    for (GLint error = glGetError(); error; error = glGetError()){
//        LOGE("GLUtils::CheckGLError GL Operation %s() glError (0x%x)\n", pGLOperation, error);
    }
}
