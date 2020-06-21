package org.example;

import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.io.*;
import java.net.Socket;

public class RejestracjaAdminController {

    @FXML
    TextField imie;
    @FXML
    TextField nazwisko;
    @FXML
    TextField login;
    @FXML
    PasswordField haslo;
    @FXML
    ChoiceBox plec;
    @FXML
    Label status;

    String log;
    String has;
    String imi;
    String nazw;
    String ple;

    public void getImie() {
        imi = imie.getText();
    }

    public void getNazwisko() {
        nazw = nazwisko.getText();
    }

    private void getLogin() {
        log =  login.getText();
    }

    private void getHaslo() {
        has = haslo.getText();
    }

    public void getPlec() {
        ple = (String) plec.getSelectionModel().getSelectedItem();
    }


    @FXML
    private void doLogowania() throws IOException {
        App.setRoot("logowanie");
    }

    @FXML
    private void doRejestracji() throws IOException {
        App.setRoot("rejestracja");
    }

    @FXML
    private void zarejestrujAdmin() throws IOException {
        getImie();
        getNazwisko();
        getLogin();
        getHaslo();
        getPlec();
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(14);
        bw.flush();
        bw.write(log + "\n");
        bw.flush();
        int odp = br.read();
        if(odp == 1)
        {
            bw.write(imi + "\n");
            bw.flush();
            bw.write(nazw + "\n");
            bw.flush();
            bw.write(has + "\n");
            bw.flush();
            bw.write(ple + "\n");
            bw.flush();

            br.close();
            bw.close();
            socket.close();
            App.setRoot("logowanie");       //moge tu dodac okienko z specem "Zarejestrowano pomyślnie"
        }
        else
        {
            bw.write(0);
            status.setText("Adres email jest już zajęty");
            br.close();
            bw.close();
            socket.close();
        }
    }
}
