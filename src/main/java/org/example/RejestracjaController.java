package org.example;

import javafx.fxml.FXML;
import javafx.scene.control.*;

import java.io.*;
import java.net.Socket;

public class RejestracjaController {

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
    @FXML
    CheckBox check1, check2, check3,check4,check5,check6,check7,check8,check9,check10,check11,check12;  //sprawdzic jak zrobic dla 12 na raz

    String log;
    String has;
    String imi;
    String nazw;
    String ple;
    String spec = "";


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

    public void getSpecyfikacja() {
        if(check1.isSelected()){spec = spec + "Psychiatria" +  ",";}
        if(check2.isSelected()){spec = spec + "Pediatria" +  ",";}
        if(check3.isSelected()){spec = spec + "Okulistyka" +  ",";}
        if(check4.isSelected()){spec = spec + "Neurologia" +  ",";}
        if(check5.isSelected()){spec = spec + "Kardiologia" +  ",";}
        if(check6.isSelected()){spec = spec + "Epidemiologia" +  ",";}
        if(check7.isSelected()){spec = spec + "Chirurgia dziecięca" +  ",";}
        if(check8.isSelected()){spec = spec + "Anestezjologia" +  ",";}
        if(check9.isSelected()){spec = spec + "Chirurgia ogólna" +  ",";}
        if(check10.isSelected()){spec = spec + "Choroby zakaźne" +  ",";}
        if(check11.isSelected()){spec = spec + "Medycyna pracy" +  ",";}
        if(check12.isSelected()){spec = spec + "Ortopedia" +  ",";}
    }

    @FXML
    private void doLogowania() throws IOException {
        App.setRoot("logowanie");
    }

    @FXML
    private void doAdminRejestracja() throws IOException {
        App.setRoot("rejestracjaAdmin");
    }

    @FXML
    private void zarejestruj() throws IOException {
        getImie();
        getNazwisko();
        getLogin();
        getHaslo();
        getPlec();
        getSpecyfikacja();
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(2);
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
            bw.write(spec + "\n");
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
