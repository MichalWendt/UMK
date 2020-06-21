package org.example;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.*;
import java.net.Socket;

public class DodanieLekController {


    @FXML
    TextField nazwa;
    @FXML
    TextArea sklad;

    @FXML
    Button zamknijButton;


    @FXML
    private void zamknij() throws IOException {
        Stage stage = (Stage) zamknijButton.getScene().getWindow();
        stage.close();
    }

    @FXML
    private void DodanieLeki() throws IOException {
        App.setRoot("Leki");
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(13);
        bw.flush();
        String naz,skl;
        naz = nazwa.getText();
        skl = sklad.getText().replaceAll("\n", System.getProperty("line.separator"));;

        bw.write(naz + "\n");
        bw.flush();
        bw.write(skl + "\n");
        bw.flush();
        br.close();
        bw.close();
        socket.close();
        zamknij();
    }
}
