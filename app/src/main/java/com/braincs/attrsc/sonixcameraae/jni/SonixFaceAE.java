package com.braincs.attrsc.sonixcameraae.jni;

/**
 * Created by Shuai
 * 2020-05-18.
 */
public class SonixFaceAE {
    static {
        System.loadLibrary("sonix-jni");
    }

    public native static void sonixCamRegRead(byte[] data);
}
