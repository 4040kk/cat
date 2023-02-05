package com.example.car;

import static android.content.ContentValues.TAG;

import static java.lang.Thread.sleep;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity {
    private Button find;
    private Button link,dislink,stop;
    private TextView angleXY_Text, levelXY_Text,angleZ_Text,levelZ_Text,status;
    private  String angleXY,levelXY,angleZ,levelZ,ip;
    private String[] fs = {"0","0","0","0"};
    private EditText send_ip,send_po;
    private ExecutorService mThreadPool,rThreadPool;
    private Socket socket;
    private BufferedReader br;
    private OutputStream outputStream;
    private Handler mMainHandler;
    private  int port;
    private Switch sw_find;
    @Override
    protected void onCreate (Bundle savedInstanceState) {
        super.onCreate ( savedInstanceState );
        setContentView ( R.layout.activity_main );
        angleXY_Text=(TextView)findViewById ( R.id.angleXY_Tex );
        levelXY_Text=(TextView)findViewById ( R.id.levelXY_Text );
        angleZ_Text=(TextView)findViewById ( R.id.angleZ ) ;
        levelZ_Text=(TextView)findViewById ( R.id.levelZ ) ;
        find=(Button)findViewById ( R.id.find );
        mThreadPool = Executors.newCachedThreadPool();
        link=(Button)findViewById ( R.id.link );
        send_ip=(EditText)findViewById ( R.id.ip );
        send_po=(EditText)findViewById ( R.id.port );
        status=(TextView)findViewById ( R.id.status );
        setRequestedOrientation( ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);//设置屏幕为横屏, 设置后会锁定方向
        MyRockerView mRockerViewXY = (MyRockerView) findViewById ( R.id.rockerXY_View );//8方向
        MyRockerView mRockerViewZ = (MyRockerView) findViewById ( R.id.rockerZ_View );//2方向
        stop=(Button)findViewById ( R.id.m_stop );
        sw_find=(Switch)findViewById ( R.id.sw_find );
        levelZ="0";
        fs[3]=levelZ;

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.hide();
        }
        send_po.setText ( "8080" );
        send_ip.setText ( "192.168.4.1" );
        if (Build.VERSION.SDK_INT > 8) {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder ( ).permitAll ( ).build ( );
            StrictMode.setThreadPolicy ( policy );
        }

        stop.setOnClickListener ( new View.OnClickListener ( ) {
            @Override
            public void onClick (View view) {
                fs[1]="0";
                fs[2]="0";
                fs[3]="0";
            }
        } );
        sw_find.setOnCheckedChangeListener ( new CompoundButton.OnCheckedChangeListener ( ) {
            @Override
            public void onCheckedChanged (CompoundButton compoundButton, boolean b) {
                if(b){fs[1]="3";}else {fs[1]="0";}
            }
        } );

        link.setOnClickListener ( new View.OnClickListener ( ) {
            @Override
            public void onClick (View view) {
                ip=send_ip.getText ().toString ();
                try {
                    port = Integer.valueOf ( send_po.getText ( ).toString ( ) );
                } catch (Exception a) {

                    a.printStackTrace ( );
                    return;
                }

                mThreadPool.execute ( new Runnable ( ) {
                    @Override
                    public void run ( ) {
                        try {
                            // 创建Socket对象 & 指定服务端的IP 及 端口号
                            socket = new Socket ( ip, port );
                            // 判断客户端和服务器是否连接成功
                            System.out.println(socket.isConnected());
                            if (socket.isConnected ()){
                                Message msg = Message.obtain();
                                msg.what = 1;
                                mMainHandler.sendMessage(msg);
                                send();
                            }

                        } catch (IOException e) {
                            e.printStackTrace();
                        }

                    }
                } );




            }
        } );
        mMainHandler = new Handler () {
            @Override
            public void handleMessage(Message msg) {
                switch (msg.what) {
                    case 0: send ();
                        break;
                    case 1:    status.setText ( "已连接" );
                        break;
                }
            }
        };

        mRockerViewXY.setOnAngleChangeListener(new MyRockerView.OnAngleChangeListener() {
            @Override
            public void onStart() {

                Log.e(TAG, "XY轴"+angleXY);
                angleXY_Text.setText(angleXY);
            }

            @Override
            public void angle(double angle) {
                angleXY = (""+angle);
               Log.e(TAG, "XY轴"+angleXY);
               if(angle>165&&angle<201) fs[1]="1";
               if ((angle>=330||angle<=25)) fs[1]="2";
                angleXY_Text.setText(angleXY);
            }

            @Override
            public void onFinish() {
                angleXY="0";
                angleXY_Text.setText("0");
                levelXY_Text.setText("0");
            }
        });
//级别
        mRockerViewXY.setOnDistanceLevelListener(new MyRockerView.OnDistanceLevelListener() {
            @Override
            public void onDistanceLevel(int level) {
                if (level<=3){levelXY="0";fs[1]="0";}else {
                    levelXY= ((level-3)+"");
                    //fs[1]=levelXY+"";
                }
               // Log.e(TAG, "XY轴"+levelXY);
                levelXY_Text.setText(levelXY);
            }
        });


        mRockerViewZ.setOnAngleChangeListener(new MyRockerView.OnAngleChangeListener() {
            @Override
            public void onStart() {
                angleZ="0";
                Log.e(TAG, "Z轴"+angleZ);
                angleZ_Text.setText(angleZ);
            }

            @Override
            public void angle(double angle) {
                angleZ = (""+angle);
                Log.e(TAG, "Z轴"+angleZ);
                if(angle<=110&&angle>=80){fs[2]="1";}
                else {fs[2]="0";}
                angleZ_Text.setText(angleZ);
            }

            @Override
            public void onFinish() {
                angleZ="0";
                angleZ_Text.setText("0");
                levelZ_Text.setText("0");
            }
        });
//级别
        mRockerViewZ.setOnDistanceLevelListener(new MyRockerView.OnDistanceLevelListener() {
            @Override
            public void onDistanceLevel(int level) {
                if (level<=3){levelZ="0";fs[3]="0";}else {
                    levelZ = ((level-3)+"");
                    fs[3]=levelZ+"";
                }

                // Log.e(TAG, "XY轴"+levelXY);
                levelZ_Text.setText(levelZ);

            }




        });

    }

    void send(){

        mThreadPool.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    sleep(400);//休眠
                } catch (InterruptedException e) {
                    e.printStackTrace ( );
                }
                if(socket.isConnected ()){
                    String m="";
                        for (int i=0;i<4;i++){
                            m+=fs[i];
                        }
                    try {
                        outputStream = socket.getOutputStream ( );
                        outputStream.write ( (m+ "\n").getBytes ( StandardCharsets.US_ASCII ) );
                        outputStream.flush ( );
                    } catch (IOException e) {
                        e.printStackTrace ( );
                    }
                }
                Message msg = Message.obtain();
                msg.what = 0;
                mMainHandler.sendMessage(msg);
            }
        });


    }

}