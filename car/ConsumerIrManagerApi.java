package com.example.car;

import android.annotation.TargetApi;
import android.content.Context;
import android.os.Build;

public class ConsumerIrManagerApi {
    private static ConsumerIrManagerApi instance;
    private static android.hardware.ConsumerIrManager service;
    @TargetApi(Build.VERSION_CODES.KITKAT)
    private ConsumerIrManagerApi(Context context) {
        //Android4.4才开始支持红外功能
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT){
            // 获取系统的红外遥控服务
            service = (android.hardware.ConsumerIrManager) context.getApplicationContext().getSystemService(Context.CONSUMER_IR_SERVICE);
        }
    }

    public static ConsumerIrManagerApi getConsumerIrManager(Context context){
        if(instance == null){
            instance = new ConsumerIrManagerApi(context);
        }
        return instance;
    }

    /**
     * 手机是否有红外功能
     * @return
     */
    public static boolean hasIrEmitter() {
        //android4.4及以上版本&有红外功能
        if(service!=null){
            return service.hasIrEmitter();
        }
        //android4.4以下及4.4以上没红外功能
        return false;
    }

    /**
     * 发射红外信号
     * @param carrierFrequency 红外频率
     * @param pattern
     */
    public static void transmit(int carrierFrequency, int[] pattern) {
        if(service!=null){
            service.transmit(carrierFrequency, pattern);
        }
    }

    /**
     * 获取可支持的红外信号频率
     * @return
     */
    public static android.hardware.ConsumerIrManager.CarrierFrequencyRange[] getCarrierFrequencies() {
        if(service!=null){
            return service.getCarrierFrequencies();
        }
        return null;
    }
}
