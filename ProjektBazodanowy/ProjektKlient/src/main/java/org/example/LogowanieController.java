package org.example;

import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.io.*;
import java.net.Socket;

public class LogowanieController {

    @FXML
    TextField login;
    @FXML
    PasswordField haslo;
    @FXML
    Label status;

    String log;
    String has;
    private void getLogin() {
        log =  login.getText();
    }

    private void getHaslo() {
        has = haslo.getText();
    }

    @FXML
    private void doRejestracji() throws IOException {
        App.setRoot("rejestracja");
    }

    @FXML
    private void zaloguj() throws IOException {
        getLogin();
        getHaslo();
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(1);
        bw.flush();
        bw.write(log + "\n");
        bw.flush();
        bw.write(has + "\n");
        bw.flush();
        int odp =  br.read();
        Long id = Long.valueOf(br.readLine());
        br.close();
        bw.close();
        socket.close();
        if(odp == 1)
        {
            AppState.getInstance().setIDlekarza(id);
            App.setRoot("primary");
        }
        else if(odp == 2)
        {
            AppState.getInstance().setCzyadmin(true);
            App.setRoot("primaryadmin");
        }
        else
        {
            status.setText("Nieprawidłowe dane logowania");
        }
    }
}
