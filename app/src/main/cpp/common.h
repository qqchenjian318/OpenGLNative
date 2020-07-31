//
// Created by ChenJian on 2020/7/1.
//

#ifndef MEDIASDKDEMO_COMMON_H
#define MEDIASDKDEMO_COMMON_H

#include <android/log.h>
#define TAG "common"


#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)


#define GO_CHECK_GL_ERROR(...)   LOGE("CHECK_GL_ERROR %s glGetError = %d, line = %d, ",  __FUNCTION__, glGetError(), __LINE__)



#endif //MEDIASDKDEMO_COMMON_H

