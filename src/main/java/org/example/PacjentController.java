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

public class PacjentController implements Initializable{

    @FXML
    TextField imiePacjent;
    @FXML
    TextField nazwiskoPacjent;
    @FXML
    TextField plecPacjent;

    @FXML
    Label status;

    @FXML
    TableView<Pacjent> listPacjenci;
    @FXML private TableColumn<Pacjent, Long> PACJENT_ID;
    @FXML private TableColumn<Pacjent, String> PACJENT_IMIE;
    @FXML private TableColumn<Pacjent, String> PACJENT_NAZWISKO;
    @FXML private TableColumn<Pacjent, String> PACJENT_PLEC;

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
        bw.write(4);
        bw.flush();
        List<Pacjent> lista = new ArrayList<>();
        ObjectMapper mapper = new ObjectMapper();
        String obiekt = br.readLine();
        JSONObject jsonIn = new JSONObject(obiekt);
        lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Pacjent[].class)).collect(Collectors.toList());
        ObservableList<Pacjent> pom = FXCollections.observableArrayList();

            listPacjenci.getColumns().clear();

        TableColumn PACJENT_ID = new TableColumn("ID");
        TableColumn PACJENT_IMIE = new TableColumn("IMIĘ");
        TableColumn PACJENT_NAZWISKO = new TableColumn("NAZWISKO");
        TableColumn PACJENT_PLEC = new TableColumn("PŁEĆ");

        listPacjenci.getColumns().addAll(PACJENT_ID, PACJENT_IMIE, PACJENT_NAZWISKO, PACJENT_PLEC);

        for(int i = 0; i < lista.size(); ++i)
        {
            pom.add(new Pacjent(lista.get(i).getId(),lista.get(i).getImie(),lista.get(i).getNazwisko(),lista.get(i).getPlec()));
            listPacjenci.setItems(pom);
        }
        PACJENT_ID.setCellValueFactory(new PropertyValueFactory<Pacjent, Long>("id"));
        PACJENT_IMIE.setCellValueFactory(new PropertyValueFactory<Pacjent, String>("imie"));
        PACJENT_NAZWISKO.setCellValueFactory(new PropertyValueFactory<Pacjent, String>("nazwisko"));
        PACJENT_PLEC.setCellValueFactory(new PropertyValueFactory<Pacjent, String>("plec"));

        br.close();
        bw.close();
        socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void setOknoPacjent() throws IOException {
        try {
            AppState.getInstance().setIDpacjenta(listPacjenci.getSelectionModel().getSelectedItem().getId());
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("ZmianaDanychPacjent.fxml"));
            Parent root1 = (Parent) fxmlLoader.load();
            Stage stage = new Stage();
            stage.setTitle("Edycja Pacjenta");
            stage.setScene(new Scene(root1));
            stage.show();
        }
        catch(NullPointerException e)
        {
            status.setText("Należy wybrać pole z listy");
        }
    }

    @FXML
    private void setDodajPacjent() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("DodaniePacjent.fxml"));
        Parent root1 = (Parent) fxmlLoader.load();
        Stage stage = new Stage();
        stage.setTitle("Dodanie Pacjenta");
        stage.setScene(new Scene(root1));
        stage.show();
    }

    @FXML
    private void filtrPacjenci() throws IOException {
        String imi = imiePacjent.getText();
        String nazw =  nazwiskoPacjent.getText();
        String plec = plecPacjent.getText();
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(7);
        bw.flush();
        bw.write(imi + "\n");
        bw.flush();
        bw.write(nazw + "\n");
        bw.flush();
        bw.write(plec + "\n");
        bw.flush();

        List<Pacjent> lista = new ArrayList<>();
        ObjectMapper mapper = new ObjectMapper();
        String obiekt = br.readLine();
        JSONObject jsonIn = new JSONObject(obiekt);
        lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Pacjent[].class)).collect(Collectors.toList());
        ObservableList<Pacjent> pom = FXCollections.observableArrayList();

        listPacjenci.getColumns().clear();

        TableColumn PACJENT_ID = new TableColumn("ID");
        TableColumn PACJENT_IMIE = new TableColumn("IMIĘ");
        TableColumn PACJENT_NAZWISKO = new TableColumn("NAZWISKO");
        TableColumn PACJENT_PLEC = new TableColumn("PŁEĆ");

        listPacjenci.getColumns().addAll(PACJENT_ID, PACJENT_IMIE, PACJENT_NAZWISKO, PACJENT_PLEC);

        for(int i = 0; i < lista.size(); ++i)
        {
            pom.add(new Pacjent(lista.get(i).getId(),lista.get(i).getImie(),lista.get(i).getNazwisko(),lista.get(i).getPlec()));
            listPacjenci.setItems(pom);
        }
        PACJENT_ID.setCellValueFactory(new PropertyValueFactory<Pacjent, Long>("id"));
        PACJENT_IMIE.setCellValueFactory(new PropertyValueFactory<Pacjent, String>("imie"));
        PACJENT_NAZWISKO.setCellValueFactory(new PropertyValueFactory<Pacjent, String>("nazwisko"));
        PACJENT_PLEC.setCellValueFactory(new PropertyValueFactory<Pacjent, String>("plec"));

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
    private void usunPacjent() throws IOException {

        try {
            AppState.getInstance().setIDpacjenta(listPacjenci.getSelectionModel().getSelectedItem().getId());
        }
        catch(Exception e)
        {
            status.setText("Należy wybrać pole z listy");
            return;
        }
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(22);
        bw.flush();

        bw.write(AppState.getInstance().getIDpacjenta() + "\n");
        bw.flush();

        int odp = br.read();

        if(odp == 0)
        {
            status.setText("Main.Pacjent nie może być usunięty");
        }
        br.close();
        bw.close();
        socket.close();
    }

    @FXML
    private void wypiszLeki() throws IOException {
        try {
            AppState.getInstance().setIDpacjenta(listPacjenci.getSelectionModel().getSelectedItem().getId());
            AppState.getInstance().setCzypac(true);
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("ListaLekow.fxml"));
            Parent root1 = (Parent) fxmlLoader.load();
            Stage stage = new Stage();
            stage.setTitle("Lista Lekow");
            stage.setScene(new Scene(root1));
            stage.show();
        }
        catch(NullPointerException e)
        {
            status.setText("Należy wybrać pole z listy");
        }
    }

}
