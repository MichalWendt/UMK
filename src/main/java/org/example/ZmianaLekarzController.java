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

public class ZmianaLekarzController implements Initializable {

    @FXML
    TextField imieLekarz;
    @FXML
    TextField nazwiskoLekarz;
    @FXML
    TextField login;
    @FXML
    PasswordField haslo;
    @FXML
    ChoiceBox plecLekarz;
    @FXML
    TextArea specyfikacje;

    @FXML
    Button zamknijButton;


    @Override
    public void initialize(URL url, ResourceBundle resourceBundle){

        Socket socket = null;
        try {
            socket = new Socket("localhost", 8080);
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            bw.write(19);
            bw.flush();
            bw.write(AppState.getInstance().getIDlekarza().toString() + "\n");
            bw.flush();

            List<Lekarz> lista = new ArrayList<>();
            ObjectMapper mapper = new ObjectMapper();
            String obiekt = br.readLine();
            JSONObject jsonIn = new JSONObject(obiekt);
            lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lekarz[].class)).collect(Collectors.toList());

            imieLekarz.setText(lista.get(0).getImie());
            nazwiskoLekarz.setText(lista.get(0).getNazwisko());
            login.setText(lista.get(0).getEmail());
            haslo.setText(lista.get(0).getHaslo());
            plecLekarz.setValue(lista.get(0).getPlec());
            specyfikacje.setText(lista.get(0).getSpecyfikacja());


            br.close();
            bw.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    @FXML
    private void zamknij() throws IOException {
        Stage stage = (Stage) zamknijButton.getScene().getWindow();
        stage.close();
    }

    @FXML
    private void edycjaLekarz() throws IOException {
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(9);
        bw.flush();
        String im,nazw,ema,spec,ple,has;
        im = imieLekarz.getText();
        nazw = nazwiskoLekarz.getText();
        ema = login.getText();
        spec = specyfikacje.getText().replaceAll("\n", System.getProperty("line.separator"));;
        ple = (String) plecLekarz.getSelectionModel().getSelectedItem();
        has = haslo.getText();

        bw.write(AppState.getInstance().getIDlekarza()+"\n");
        bw.flush();
        bw.write(im + "\n");
        bw.flush();
        bw.write(nazw + "\n");
        bw.flush();
        bw.write(ema + "\n");
        bw.flush();
        bw.write(ple + "\n");
        bw.flush();
        bw.write(has + "\n");
        bw.flush();
        bw.write(spec + "\n");
        bw.flush();
        br.close();
        bw.close();
        socket.close();
        zamknij();
    }

}
