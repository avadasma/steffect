#ifndef _ST_UTILS_H__
#define _ST_UTILS_H__

#include <sys/time.h>
#include <time.h>
#include <jni.h>
#include "st_mobile_sticker.h"
#include "st_mobile_face_attribute.h"


#include <jni.h>
#include <android/log.h>

#define LOGGABLE 0

#define LOGI(...) if(LOGGABLE) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif

static inline jfieldID getHandleField(JNIEnv *env, jobject obj)
{
    jclass c = env->GetObjectClass(obj);
    // J is the type signature for long:
    return env->GetFieldID(c, "nativeHandle", "J");
}

template <typename T>
T *getHandle(JNIEnv *env, jobject obj)
{
    jlong handle = env->GetLongField(obj, getHandleField(env, obj));
    return reinterpret_cast<T *>(handle);
}

template <typename T>
void setHandle(JNIEnv *env, jobject obj, T *t)
{
    jlong handle = reinterpret_cast<jlong>(t);
    env->SetLongField(obj, getHandleField(env, obj), handle);
}

long getCurrentTime();
int getImageStride(const st_pixel_format &pixel_format, const int &outputWidth);
// convert c object to java object
jobject convert2STRect(JNIEnv *env, const st_rect_t &object_rect);
jobject convert2HumanAction(JNIEnv *env, const st_mobile_human_action_t &human_action);
jobject convert2MobileFace106(JNIEnv *env, const st_mobile_106_t &mobile_106);
jobject convert2FaceAttribute(JNIEnv *env, const st_mobile_attribute_t &faceAttribute);
jobject convert2Image(JNIEnv *env, const st_image_t &image);
jobject convert2HandAction(JNIEnv *env, const st_mobile_hand_action_t &hand_action);
jobject convert2FaceExtraInfo(JNIEnv *env, const st_mobile_face_extra_info_t *face_extra_info);

// convert java object to c object
bool convert2st_rect_t(JNIEnv *env, jobject rectObject, st_rect_t &rect);
bool convert2human_action(JNIEnv *env, jobject humanActionObject, st_mobile_human_action_t &human_action);
bool convert2mobile_106(JNIEnv *env, jobject face106, st_mobile_106_t &mobile_106);
bool convert2Image(JNIEnv *env, jobject image, st_image_t &background);
bool convert2HandAction(JNIEnv *env, jobject handActionObject, st_mobile_hand_action_t &hand_action);
bool convert2st_mobile_face_extra_info_t(JNIEnv *env, jobject faceExtraInfoObj, st_mobile_face_extra_info_t &face_extra_info);

#endif // _ST_UTILS_H__