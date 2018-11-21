package castelli_montanari.android_code;

import android.os.AsyncTask;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class CmdSender extends  AsyncTask<Object, Void, Void>
{
    Socket s;
    DataOutputStream dos;
    PrintWriter pw;


    @Override
    protected Void doInBackground(Object ... params) {

        String message = (String) params[0];
        String ip = (String) params[1];
        int port = (int) params[2];

        try
        {
            s  = new Socket(ip,port);
            pw = new PrintWriter(s.getOutputStream());
            pw.write(message);
            pw.flush();
            pw.close();
            s.close();


        }catch (IOException e)
        {
            e.printStackTrace();
        }

        return null;
    }
}
