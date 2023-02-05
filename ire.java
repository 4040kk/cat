package com.example.car;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.TargetApi;
import android.content.Context;
import android.hardware.ConsumerIrManager;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.lang.reflect.Field;

public class ire extends AppCompatActivity {
    private static android.hardware.ConsumerIrManager service;

    private Button send;

    @Override
    protected void onCreate (Bundle savedInstanceState) {
        super.onCreate ( savedInstanceState );
        setContentView ( R.layout.activity_ire );
        Button send=(Button) findViewById ( R.id.ire_send );
        send.setOnClickListener ( new View.OnClickListener ( ) {
            @Override
            public void onClick (View view) {

            }
        } );
    }



    public static void transmit(int carrierFrequency, int[] pattern) {
        if(service!=null){
            service.transmit(carrierFrequency, pattern);
        }
    }
    public void transmit() {
        ConsumerIrManagerApi.transmit(38000,NecPattern.buildPattern(0X08,0XE6, 0X41));
    }

}