package castelli_montanari.android_code;

import android.util.Log;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class TCPClient {
    private static String TAG = "TCPClient";
    private String serverIP = "192.168.4.1";
    private long startTime = 01;
    private int serverPort = 9000;
    private Socket connectionSocket;

    private SendRunnable sendRunnable;
    private Thread sendThread;
    byte[] dataToSend;

    private ReceiveRunnable receiveRunnable;
    private Thread receiveThread;
    boolean receiveThreadRunning = false;


    private void startSending(){
        sendRunnable = new SendRunnable(connectionSocket);
        sendThread = new Thread(sendRunnable);
        sendThread.start();
    }

    private void startReceiving(){
        receiveRunnable = new ReceiveRunnable(connectionSocket);
        receiveThread = new Thread(receiveRunnable);
        receiveThread.start();
    }

    private void stopThreads(){
        if (receiveThread != null){
            receiveThread.interrupt();
        }
        if (sendThread != null){
            sendThread.interrupt();
        }
    }

    public void Disconnect(){
        stopThreads();
        try{
            connectionSocket.close();
            Log.d(TAG, "Disconnesso!");
        } catch (IOException e) {}
    }

    private boolean isConnected(){ //se nun è connesso così vojo vedè
        return connectionSocket != null && connectionSocket.isConnected() && !connectionSocket.isClosed();
    }

    public class ConnectRunnable implements Runnable {
        public void run(){
            try{
                Log.d(TAG, "C: Sto connettendo....");
                InetAddress serverAddr = null;

                serverAddr = InetAddress.getByName(serverIP);
                startTime = System.currentTimeMillis();

                connectionSocket = new Socket();

                connectionSocket.connect(new InetSocketAddress(serverAddr,serverPort), 5000);

                long time = System.currentTimeMillis() - startTime;
                Log.d(TAG, "Connesso, durata attuale: " + time + "ms");
            } catch (Exception e){
                Log.d(TAG, "oh no, qualcosa è andato storto...");
            }
            Log.d(TAG, "Connection thread stopped");
        }

        public void Connect(String ip, int port){
            serverIP = ip;
            serverPort = port;
            dataToSend = null;
            new Thread(new ConnectRunnable()).start();
        }
    }


    public class SendRunnable implements Runnable {
        byte[] data;
        private OutputStream out;
        private boolean hasMessage = false; // data pending to be sent
        int dataType = 1;


        //constructor
        public SendRunnable(Socket server){
            try{
                this.out = server.getOutputStream();
            } catch (IOException e){}
        }

        public void Send(byte[] bytes){
            this.data = bytes;
            dataType = TCPCommands.TYPE_FILE_CONTENT;
            this.hasMessage = true;
        }

        public void SendCMD(byte[] bytes){
            this.data = bytes;
            dataType = TCPCommands.TYPE_CMD;
            this.hasMessage = true;
        }


        @Override
        public void run(){
            Log.d(TAG, "startsending");
            while(!Thread.currentThread().isInterrupted() && isConnected()){ //finchè stamo conneessi
                if(this.hasMessage){
                    startTime = System.currentTimeMillis();
                    try{
                        //lunghezza messaggio
                        this.out.write(ByteBuffer.allocate(4).putInt(data.length).array());
                        //tipo messaggio
                        this.out.write(ByteBuffer.allocate(4).putInt(dataType).array());
                        //messaggio
                        this.out.write(data, 0, data.length);
                        //flush dat shit
                        this.out.flush();
                    } catch (IOException e){
                    }
                    this.hasMessage = false;
                    this.data = null;
                    long time = System.currentTimeMillis() - startTime;
                    Log.d(TAG, "Comando inviato, durata: " + time + "ms");
                    if (!receiveThreadRunning){
                        startReceiving(); //se non c'è già un thread per ricevere avvialo
                    }
                }
            }
            Log.d(TAG, "stopsending");
        }

    }

    public class ReceiveRunnable implements Runnable {
        private Socket sock;
        private InputStream input;

        //constructor
        public ReceiveRunnable(Socket server){
            sock = server;
            try {
                input = sock.getInputStream();
            } catch (IOException e) {}
        }

        public void run(){
            while(!Thread.currentThread().isInterrupted() && isConnected()){
                if(!receiveThreadRunning) receiveThreadRunning = true;

                try{
                    byte[] data = new byte[4];
                    //leggiamo primo intero che definisce lunghezza messaggio
                    input.read(data,0, data.length);
                    int length = ByteBuffer.wrap(data).order(ByteOrder.LITTLE_ENDIAN).getInt();
                    //leggiamo secondo intero, tipo messaggio
                    input.read(data, 0 , data.length);
                    int type = ByteBuffer.wrap(data).order(ByteOrder.LITTLE_ENDIAN).getInt();

                    int read = 0;
                    int downloaded = 0;

                    if(type == TCPCommands.TYPE_CMD) {
                        //mi aspetto un comando

                        data = new byte[length];
                        StringBuilder sb = new StringBuilder();
                        InputStream bis = new BufferedInputStream(input);

                        while ((read = bis.read(data)) != -1) {
                            downloaded += read;
                            sb.append(new String(data, 0, read, "UTF-8"));
                            if (downloaded == length)
                                break; // break perchè se il bitrate di download fosse maggiore di quello
                            // di upload potremmo finire di leggere prima che il messaggio sia
                            // finito perchè bis.read(data) == -1 se non c'è roba nello stream
                        }
                    }
                    else if (type == TCPCommands.TYPE_FILE_CONTENT){
                        byte[] inputData = new byte[2048];
                        InputStream bis = new BufferedInputStream(input);

                        while ((read = bis.read(inputData))!= -1){
                            downloaded += read;
                            if (downloaded == length) {
                                break;
                            }
                        }
                    }
                    long time = System.currentTimeMillis() - startTime;
                    Log.d(TAG, "Data received, took: " + time + "ms and got:  " + (downloaded +8 ) + "bytes");

                    stopThreads();
                }catch (Exception e){
                    Disconnect(); // se qualcosa va storto
                }

            }
            receiveThreadRunning = false;
            Log.d(TAG, "receiving stopped");

        }
    }
}



