//
// Created by ChenJian on 2020/7/1.
//

#ifndef MEDIASDKDEMO_TRIANGLESAMPLE_H
#define MEDIASDKDEMO_TRIANGLESAMPLE_H


#include "GLSampleBase.h"

class TriangleSample : public GLSampleBase{
public:
    TriangleSample();

    virtual ~TriangleSample();

    virtual void init();

    virtual void draw(int screenW,int screenH);

    virtual void destroy();


};


#endif //MEDIASDKDEMO_TRIANGLESAMPLE_H
