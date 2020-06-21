package org.example;

import com.fasterxml.jackson.databind.ObjectMapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
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

public class LekController implements Initializable {


    @FXML
    TextField id;
    @FXML
    TextField nazwa;
    @FXML
    TextField skład;
    @FXML
    Label status;

    @FXML
    TableView<Lek> listLeki;
    @FXML private TableColumn<Lek, Long> LEK_ID;
    @FXML private TableColumn<Lek, String> LEK_NAZWA;
    @FXML private TableColumn<Lek, String> SKLAD;


    @FXML
    private void wyloguj() throws IOException {
        App.setRoot("logowanie");
    }

    @FXML
    private void setPacjenci() throws IOException {
        App.setRoot("Pacjenci");
    }

    @FXML
    private void setLekarze() throws IOException {
        App.setRoot("Lekarze");
    }

    @FXML
    private void setLeki() throws IOException {
        App.setRoot("Leki");
    }

    @FXML
    private void setWizyty() throws IOException {
        App.setRoot("Wizyty");
    }

    @FXML
    private void setPacjenciAdmin() throws IOException {
        App.setRoot("PacjenciAdmin");
    }

    @FXML
    private void setLekarzeAdmin() throws IOException {
        App.setRoot("LekarzeAdmin");
    }

    @FXML
    private void setLekiAdmin() throws IOException {
        App.setRoot("LekiAdmin");
    }

    @FXML
    private void setWizytyAdmin() throws IOException {
        App.setRoot("WizytyAdmin");
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        Socket socket = null;
        try {
            socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(5);
        bw.flush();
        List<Lek> lista = new ArrayList<>();
        ObjectMapper mapper = new ObjectMapper();
        String obiekt = br.readLine();
        JSONObject jsonIn = new JSONObject(obiekt);
        lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lek[].class)).collect(Collectors.toList());
        ObservableList<Lek> pom = FXCollections.observableArrayList();

            listLeki.getColumns().clear();

        TableColumn LEK_ID = new TableColumn("ID");
        TableColumn LEK_NAZWA = new TableColumn("NAZWA");
        TableColumn SKLAD = new TableColumn("SKŁAD");

        listLeki.getColumns().addAll(LEK_ID, LEK_NAZWA, SKLAD);

        for(int i = 0; i < lista.size(); ++i)
        {

            pom.add(new Lek(lista.get(i).getId(),lista.get(i).getNazwa(),lista.get(i).getSklad()));
            listLeki.setItems(pom);

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

    @FXML
    private void setOknoLeki() throws IOException {
        try{
            AppState.getInstance().setIDlekU(listLeki.getSelectionModel().getSelectedItem().getId());

            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("ZmianaDanychLeki.fxml"));
            Parent root1 = (Parent) fxmlLoader.load();
            Stage stage = new Stage();
            stage.setTitle("Edycja Leku");
            stage.setScene(new Scene(root1));
            stage.show();
        }
        catch(NullPointerException e)
        {
            status.setText("Należy wybrać pole z listy");
        }

    }

    @FXML
    private void setDodajLeki() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("DodanieLeki.fxml"));
        Parent root1 = (Parent) fxmlLoader.load();
        Stage stage = new Stage();
        stage.setTitle("Dodanie Leku");
        stage.setScene(new Scene(root1));
        stage.show();
    }

    @FXML
    private void filtrLeki() throws IOException {
        String nazw =  nazwa.getText();
        String sklad = skład.getText().replaceAll("\n", System.getProperty("line.separator"));;
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(8);
        bw.flush();
        bw.write(nazw + "\n");
        bw.flush();
        bw.write(sklad + "\n");
        bw.flush();

        listLeki.getColumns().clear();


        List<Lek> lista = new ArrayList<>();
        ObjectMapper mapper = new ObjectMapper();
        String obiekt = br.readLine();
        JSONObject jsonIn = new JSONObject(obiekt);
        lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lek[].class)).collect(Collectors.toList());
        ObservableList<Lek> pom = FXCollections.observableArrayList();

        TableColumn LEK_ID = new TableColumn("ID");
        TableColumn LEK_NAZWA = new TableColumn("NAZWA");
        TableColumn SKLAD = new TableColumn("SKŁAD");

        listLeki.getColumns().addAll(LEK_ID, LEK_NAZWA, SKLAD);

        for(int i = 0; i < lista.size(); ++i)
        {

            pom.add(new Lek(lista.get(i).getId(),lista.get(i).getNazwa(),lista.get(i).getSklad()));
            listLeki.setItems(pom);

        }
        LEK_ID.setCellValueFactory(new PropertyValueFactory<Lek, Long>("id"));
        LEK_NAZWA.setCellValueFactory(new PropertyValueFactory<Lek, String>("nazwa"));
        SKLAD.setCellValueFactory(new PropertyValueFactory<Lek, String>("sklad"));

        br.close();
        bw.close();
        socket.close();
    }

    @FXML
    private void setOknoLekarz() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("ZmianaDanychLekarz.fxml"));
        Parent root1 = (Parent) fxmlLoader.load();
        Stage stage = new Stage();
        stage.setTitle("Edycja Lekarza");
        stage.setScene(new Scene(root1));
        stage.show();
    }

    @FXML
    private void usunLek() throws IOException {
        try
        {
            AppState.getInstance().setIDlekU(listLeki.getSelectionModel().getSelectedItem().getId());
        }
        catch(Exception e)
        {
            status.setText("Należy wybrać pole z listy");
            return;
        }
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            bw.write(23);
            bw.flush();

            bw.write(AppState.getInstance().getIDlekU()+"\n");
            bw.flush();

        int odp = br.read();

        if(odp == 0)
        {
            status.setText("Lek nie może być usunięty");
        }
        br.close();
        bw.close();
        socket.close();
    }
}
