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
        LOG_INTERNAL("init failed");
    }

    unsigned char data[10];
    memset(data, 0, 10);
    SonixCam_AsicRegisterRead(0x9fe, data, 1);
    LOG_INTERNAL("read 0x9fe data: %x", data[0]);

    SonixCam_AsicRegisterRead(0x9FF, data, 1);
    LOG_INTERNAL("read 0x9FF data: %x", data[0]);

    SonixCam_AsicRegisterRead(0xA00, data, 1);
    LOG_INTERNAL("read 0xA00 data: %x", data[0]);

    SonixCam_AsicRegisterRead(0xA01, data, 1);
    LOG_INTERNAL("read 0xA01 data: %x", data[0]);

    SonixCam_AsicRegisterRead(0xA02, data, 1);
    LOG_INTERNAL("read 0xA02 data: %x", data[0]);


    SonixCam_AsicRegisterRead(0x101f, data, 1);

    SonixCam_AsicRegisterRead(0x1003, data, 1);
    LOG_INTERNAL("read data: %x", data[0]);

    data[0] = 0xFE;

    SonixCam_AsicRegisterWrite(0x1003, data, 1);
    LOG_INTERNAL("write data: %x", data[0]);

    SonixCam_AsicRegisterRead(0x1003, data, 1);
    LOG_INTERNAL("read data: %x", data[0]);

    env->ReleaseByteArrayElements(data_, data1, 0);

}
JNIEXPORT void JNICALL
Java_com_braincs_attrsc_sonixcameraae_jni_SonixFaceAE_autoExplosure(JNIEnv *env, jclass type,
                                                                    jint startX, jint startY,
                                                                    jint width, jint height) {

    int div = 256;
    jbyte x_high = static_cast<jbyte>(startX / div);
    jbyte x_low = static_cast<jbyte>(startX % div);
    jbyte y_high = static_cast<jbyte>(startY / div);
    jbyte y_low = static_cast<jbyte>(startY % div);

    jbyte w_high = static_cast<jbyte>(width / div);
    jbyte w_low = static_cast<jbyte>(width % div);
    jbyte h_high = static_cast<jbyte>(height / div);
    jbyte h_low = static_cast<jbyte>(height % div);


    LOG_INTERNAL("write x_high: %x, x_low: %x", x_high, x_low);
    LOG_INTERNAL("write y_high: %x, y_low: %x", y_high, y_low);
    LOG_INTERNAL("write w_high: %x, w_low: %x", w_high, w_low);
    LOG_INTERNAL("write h_high: %x, h_low: %x", h_high, h_low);


}

#ifdef __cplusplus
}
#endif