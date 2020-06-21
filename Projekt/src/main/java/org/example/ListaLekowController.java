package org.example;

import com.fasterxml.jackson.databind.ObjectMapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.json.JSONObject;

import java.io.*;
import java.net.Socket;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;
import java.util.stream.Collectors;

public class ListaLekowController implements Initializable {

    @FXML
    TableView<Lek> spisLekow;

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
            bw.write(28);
            bw.flush();
            if(AppState.getInstance().isCzypac())
            {
                bw.write(1);
                bw.flush();
                bw.write(AppState.getInstance().getIDpacjenta().toString() + "\n");
                bw.flush();
            }
            else
            {
                bw.write(0);
                bw.flush();
                bw.write(AppState.getInstance().getIDwizyty().toString() + "\n");
                bw.flush();
            }

            List<Lek> lista = new ArrayList<>();

            ObjectMapper mapper = new ObjectMapper();
            String obiekt = br.readLine();
            JSONObject jsonIn = new JSONObject(obiekt);
            lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lek[].class)).collect(Collectors.toList());
            ObservableList<Lek> pom = FXCollections.observableArrayList();

            TableColumn LEK_ID = new TableColumn("ID");
            TableColumn LEK_NAZWA = new TableColumn("NAZWA");
            TableColumn SKLAD = new TableColumn("SKŁAD");

            spisLekow.getColumns().addAll(LEK_ID, LEK_NAZWA, SKLAD);

            for(int i = 0; i < lista.size(); ++i)
            {
                pom.add(new Lek(lista.get(i).getId(),lista.get(i).getNazwa(),lista.get(i).getSklad()));
                spisLekow.setItems(pom);
            }
            LEK_ID.setCellValueFactory(new PropertyValueFactory<Lek, Long>("id"));
            LEK_NAZWA.setCellValueFactory(new PropertyValueFactory<Lek, String>("nazwa"));
            SKLAD.setCellValueFactory(new PropertyValueFactory<Lek, String>("sklad"));

            br.close();
            bw.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
