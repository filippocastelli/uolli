package castelli_montanari.android_code;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    EditText e1, e2, e3;
    String ip, message;
    int port;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        e1 = (EditText) findViewById(R.id.cmdfield);
        e2 = (EditText) findViewById(R.id.ipfield);
        e3 = (EditText) findViewById(R.id.portfield);

    }

    public void send(View v)
    {
        message = e1.getText().toString();
        ip = e2.getText().toString();
        port = Integer.parseInt(e3.getText().toString());

        CmdSender cmdsend = new CmdSender();
        cmdsend.execute(message, ip, port);
    }
}
