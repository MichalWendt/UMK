package org.example;

import com.fasterxml.jackson.databind.ObjectMapper;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.stage.Stage;
import org.json.JSONObject;

import java.io.*;
import java.net.Socket;
import java.net.URL;
import java.util.*;
import java.util.stream.Collectors;

public class ZmianaLekController implements Initializable {

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

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle){

        Socket socket = null;
        try {
            socket = new Socket("localhost", 8080);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            bw.write(24);
            bw.flush();
            bw.write(AppState.getInstance().getIDlekU().toString() + "\n");
            bw.flush();

            List<Lek> lista = new ArrayList<>();
            ObjectMapper mapper = new ObjectMapper();
            String obiekt = br.readLine();
            JSONObject jsonIn = new JSONObject(obiekt);
            lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lek[].class)).collect(Collectors.toList());

            nazwa.setText(lista.get(0).getNazwa());
            sklad.setText(lista.get(0).getSklad());


            br.close();
            bw.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    @FXML
    private void edycjaLeki() throws IOException {
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(11);
        bw.flush();
        String naz,skl;

        Long lekid = AppState.getInstance().getIDlekU();
        naz = nazwa.getText();
        skl = sklad.getText().replaceAll("\n", System.getProperty("line.separator"));;

        bw.write(lekid + "\n");
        bw.flush();
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
