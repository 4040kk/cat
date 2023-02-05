package com.example.car;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.pm.ActivityInfo;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class send extends AppCompatActivity {

    private TextView reserive,status;
    private InputStream is;
    private EditText mes,send_ip,send_k;
    private Button send_btn,link,dislink,shou;
    private String ip="192.168.4.1";
    private int port=8080;//电脑内未被占用的端口号
    private Socket socket;
    private BufferedReader br;
    private  OutputStream outputStream;
    private String re;
    private ExecutorService mThreadPool,rThreadPool;
    private Handler mMainHandler;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate ( savedInstanceState );
        setContentView ( R.layout.send );
        if (Build.VERSION.SDK_INT > 8) {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder ( ).permitAll ( ).build ( );
            StrictMode.setThreadPolicy ( policy );
        }
        init ( );
        mMainHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                switch (msg.what) {
                    case 0:
                        reserive.setText(re);
                        read();
                        break;
                }
            }
        };
        link.setOnClickListener ( new View.OnClickListener ( ) {
            @Override
            public void onClick (View view) {
                try {
                    port = Integer.valueOf ( send_k.getText ( ).toString ( ) );
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
                            if (socket.isConnected ()){status.setText ( "已连接" );
                            }else {status.setText ( "未连接" );}
                        } catch (IOException e) {
                            e.printStackTrace();
                        }

                    }
                } );

            }
        } );

        send_btn.setOnClickListener ( new View.OnClickListener ( ) {
            @Override
            public void onClick (View view) {

                try {
                    outputStream = socket.getOutputStream ( );
                    outputStream.write ( (mes.getText ( ).toString ( ) + "\n").getBytes ( StandardCharsets.US_ASCII ) );
                    outputStream.flush ( );
                } catch (IOException e) {
                    e.printStackTrace ( );
                }
            }
        } );
        dislink.setOnClickListener ( new View.OnClickListener ( ) {
            @Override
            public void onClick (View view) {

                try {
                    socket.close ( );
                   status.setText ( "未连接" );

                } catch (IOException e) {
                    e.printStackTrace ( );
                }
            }
        } );
shou.setOnClickListener ( new View.OnClickListener ( ) {
    @Override
    public void onClick (View view) {
        read ();
    }
} );
    }
    public void init() {
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);//设置屏幕为竖屏, 设置后会锁定方向
        send_k = (EditText) findViewById ( R.id.send_k );
        send_ip = (EditText) findViewById ( R.id.send_ip );
        mes = (EditText) findViewById ( R.id.send_m );
        send_btn = (Button) findViewById ( R.id.send_enter );
        link=(Button)findViewById ( R.id.send_link );
        reserive=(TextView)findViewById ( R.id.reserive );
        dislink=(Button)findViewById ( R.id.send_dislink );
        shou=(Button)findViewById ( R.id.shou );
        status=(TextView)findViewById ( R.id.link_status );
        re="无";
        send_k.setText ( "8080" );
        send_ip.setText ( "192.168.4.1" );
        try {
            port = Integer.valueOf ( send_k.getText ( ).toString ( ) );
        } catch (Exception a) {

            a.printStackTrace ( );
        }
        mThreadPool = Executors.newCachedThreadPool();
        rThreadPool=Executors.newCachedThreadPool ();
    }

    public void read(){

        mThreadPool.execute(new Runnable() {
            @Override
            public void run() {

                try {
                    is = socket.getInputStream();
                    InputStreamReader isr;
                    isr = new InputStreamReader(is, "UTF-8");
                    br = new BufferedReader(isr);
                    // 接收数据
                    re = br.readLine ();
                    // 通知主线程
                    Message msg = Message.obtain();
                    msg.what = 0;
                    mMainHandler.sendMessage(msg);
                    reserive.setText(re);
                    return;
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        });
    }




    }