import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Serwer {

    public static void main(String[] args) {
        ServerSocket server = null;
        try {
            server = new ServerSocket(8080);
            while(true) {
                Socket socket = server.accept();
                Watek w = new Watek(socket);
                w.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}