//
// Created by Shuai on 2020-05-18.
//
#include <android/log.h>
#include <jni.h>
#include <string>

#define LOG_INTERNAL(...) \
    __android_log_print(ANDROID_LOG_ERROR, "sonix", __VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

#include <SonixCamera.h>

JNIEXPORT void JNICALL
Java_com_braincs_attrsc_sonixcameraae_jni_SonixFaceAE_sonixCamRegRead(JNIEnv *env, jclass type,
                                                                      jbyteArray data_) {
    jbyte *data1 = env->GetByteArrayElements(data_, NULL);

    if(TRUE != SonixCam_Init(0)){
        fprintf(stderr, "Could not find/open sonix device\n");
    }

    unsigned char data[10];
    memset(data, 0, 10);
    SonixCam_AsicRegisterRead(0x101f, data, 1);
    LOG_INTERNAL("read data: %x", data[0]);

    SonixCam_AsicRegisterRead(0x1003, data, 1);
    LOG_INTERNAL("read data: %x", data[0]);

    data[0] = 0xFE;

    SonixCam_AsicRegisterWrite(0x1003, data, 1);
    LOG_INTERNAL("write data :%x\n", data[0]);

    SonixCam_AsicRegisterRead(0x1003, data, 1);
    LOG_INTERNAL("read data :%x\n\n", data[0]);

    env->ReleaseByteArrayElements(data_, data1, 0);

}
#ifdef __cplusplus
}
#endif