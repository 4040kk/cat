package com.example.car;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class meau extends AppCompatActivity {


    private Button ire,control,esp;
    @Override
    protected void onCreate (Bundle savedInstanceState) {
        super.onCreate ( savedInstanceState );
        setContentView ( R.layout.activity_meau );
        ire=(Button) findViewById ( R.id.ire );
        control=(Button) findViewById ( R.id.control );
        esp=(Button) findViewById ( R.id.esp );
        esp.setOnClickListener ( new View.OnClickListener ( ) {
            @Override
            public void onClick (View view) {
                Intent intent=new Intent (meau.this,send.class);
                startActivity ( intent );
            }
        } );

        control.setOnClickListener ( new View.OnClickListener ( ) {
            @Override
            public void onClick (View view) {
                Intent intent =new Intent ( meau.this,MainActivity.class );
                startActivity ( intent );
            }
        } );

        ire.setOnClickListener ( new View.OnClickListener ( ) {
            @Override
            public void onClick (View view) {
                Intent intent =new Intent ( meau.this,ire.class );
                startActivity ( intent );
            }
        } );
    }
}