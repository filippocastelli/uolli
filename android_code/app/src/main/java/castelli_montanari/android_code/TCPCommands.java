package castelli_montanari.android_code;

public class TCPCommands {
    public static int TYPE_CMD = 1;
    public static int TYPE_FILE_CONTENT = 2;

    public static String CMD_REQUEST_FILES = "server_get_files"; //When client request a list of files in that folder
    public static String CMD_REQUEST_FILES_RESPONSE = "server_get_files_response"; //When server respons with a list of files
    public static String CMD_REQUEST_FILE_DOWNLOAD = "server_download_file"; //When client request a file to be transfererad from the server.

}
