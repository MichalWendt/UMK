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
import java.util.*;
import java.util.stream.Collectors;

public class ZmianaPacjentController implements Initializable {

    @FXML
    TextField imiePacjent;
    @FXML
    TextField nazwiskoPacjent;
    @FXML
    ChoiceBox plecPacjent;
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
            bw.write(25);
            bw.flush();
            bw.write(AppState.getInstance().getIDpacjenta().toString() + "\n");
            bw.flush();

            List<Pacjent> lista = new ArrayList<>();
            ObjectMapper mapper = new ObjectMapper();
            String obiekt = br.readLine();
            JSONObject jsonIn = new JSONObject(obiekt);
            lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Pacjent[].class)).collect(Collectors.toList());

            TableView.TableViewSelectionModel selectionModel= spisLekow.getSelectionModel();
            selectionModel.setSelectionMode(SelectionMode.MULTIPLE);

            imiePacjent.setText(lista.get(0).getImie());
            nazwiskoPacjent.setText(lista.get(0).getNazwisko());
            plecPacjent.setValue(lista.get(0).getPlec());

            br.close();
            bw.close();
            socket.close();
            socket = new Socket("localhost", 8080);
            bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            bw.write(5);
            bw.flush();
            List<Lek> lista2 = new ArrayList<>();
             mapper = new ObjectMapper();
             obiekt = br.readLine();
             jsonIn = new JSONObject(obiekt);
            lista2 = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lek[].class)).collect(Collectors.toList());
            ObservableList<Lek> pom = FXCollections.observableArrayList();

            TableColumn LEK_ID = new TableColumn("ID");
            TableColumn LEK_NAZWA = new TableColumn("NAZWA");
            TableColumn SKLAD = new TableColumn("SKŁAD");

            spisLekow.getColumns().addAll(LEK_ID, LEK_NAZWA, SKLAD);

            for(int i = 0; i < lista2.size(); ++i)
            {
                pom.add(new Lek(lista2.get(i).getId(),lista2.get(i).getNazwa(),lista2.get(i).getSklad()));
                spisLekow.setItems(pom);
            }
            LEK_ID.setCellValueFactory(new PropertyValueFactory<Lek, Long>("id"));
            LEK_NAZWA.setCellValueFactory(new PropertyValueFactory<Lek, String>("nazwa"));
            SKLAD.setCellValueFactory(new PropertyValueFactory<Lek, String>("sklad"));


            //jeszcze ustaw leki
            br.close();
            bw.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    @FXML
    private void edycjaPacjent() throws IOException {
        App.setRoot("Pacjenci");
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(10);
        bw.flush();
        String im,nazw,ple;
        im = imiePacjent.getText();
        nazw = nazwiskoPacjent.getText();
        ple = (String) plecPacjent.getSelectionModel().getSelectedItem();

        TableView.TableViewSelectionModel selectionModel= spisLekow.getSelectionModel();

        ObservableList<Lek> leki = selectionModel.getSelectedItems();

        Long pacjentid = AppState.getInstance().getIDpacjenta();

        bw.write(pacjentid + "\n");
        bw.flush();
        bw.write(im + "\n");
        bw.flush();
        bw.write(nazw + "\n");
        bw.flush();
        bw.write(ple + "\n");
        bw.flush();

        List<Lek> pom = new ArrayList<>();

        for(int i = 0; i < leki.size(); ++i)
        {
            Lek lek = new Lek(leki.get(i).getId(),leki.get(i).getNazwa(),leki.get(i).getSklad());
            pom.add(lek);
        }
        ObjectMapper mapper = new ObjectMapper();
        JSONObject listaJSON = new JSONObject();

        listaJSON.put("lista", mapper.writeValueAsString(pom));
        bw.write(listaJSON.toString());
        bw.flush();

        br.close();
        bw.close();
        socket.close();
        zamknij();
    }
}
