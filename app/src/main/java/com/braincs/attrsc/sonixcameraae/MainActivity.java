package com.braincs.attrsc.sonixcameraae;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.braincs.attrsc.sonixcameraae.jni.SonixFaceAE;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        byte[] data = new byte[10];
        SonixFaceAE.sonixCamRegRead(data);
    }
}
