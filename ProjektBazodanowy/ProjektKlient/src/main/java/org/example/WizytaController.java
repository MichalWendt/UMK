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

public class WizytaController implements Initializable {

    @FXML
    TextField imiePacjentwiz;
    @FXML
    TextField nazwiskoPacjentwiz;
    @FXML
    TextField data;
    @FXML
    TextField notatka;

    @FXML
    Label status;

    @FXML
    TableView<Wizyta> listWizyty;
    @FXML private TableColumn<Wizyta, Long> WIZYTA_ID;
    @FXML private TableColumn<Wizyta, String> LEKARZ_NAZWISKO;
    @FXML private TableColumn<Wizyta, String> PACJENT_IMIE;
    @FXML private TableColumn<Wizyta, String> PACJENT_NAZWISKO;
    @FXML private TableColumn<Wizyta, String> DATA;
    @FXML private TableColumn<Wizyta, String> NOTATKA;

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
        if(AppState.getInstance().getCzyadmin())
        {
            bw.write(27);
            bw.flush();
        }
        else
        {
            bw.write(15);
            bw.flush();
            bw.write(AppState.getInstance().getIDlekarza() + "\n");
            bw.flush();
        }
        List<Wizyta> lista = new ArrayList<>();
        ObjectMapper mapper = new ObjectMapper();
        String obiekt = br.readLine();
        JSONObject jsonIn = new JSONObject(obiekt);
        lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Wizyta[].class)).collect(Collectors.toList());
        ObservableList<Wizyta> pom = FXCollections.observableArrayList();

            listWizyty.getColumns().clear();

        TableColumn WIZYTA_ID = new TableColumn("ID");
        TableColumn LEKARZ_NAZWISKO = new TableColumn("LEKARZ");
        TableColumn PACJENT_IMIE = new TableColumn("IMIĘ PACJENTA");
        TableColumn PACJENT_NAZWISKO = new TableColumn("NAZWISKO_PACJENT");
        TableColumn NOTATKA = new TableColumn("NOTATKA");
        TableColumn DATA = new TableColumn("DATA");

        listWizyty.getColumns().addAll(WIZYTA_ID, LEKARZ_NAZWISKO, PACJENT_IMIE, PACJENT_NAZWISKO , DATA, NOTATKA);

        for(int i = 0; i < lista.size(); ++i)
        {
            pom.add(new Wizyta(lista.get(i).getId(),lista.get(i).getLekarzNazw(),lista.get(i).getPacjentImie(),lista.get(i).getPacjentNazw(),lista.get(i).getData(),lista.get(i).getNotatka(),lista.get(i).getIdleki()));
            listWizyty.setItems(pom);
        }
        WIZYTA_ID.setCellValueFactory(new PropertyValueFactory<Wizyta, Long>("id"));
        LEKARZ_NAZWISKO.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("lekarzNazw"));
        PACJENT_IMIE.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("pacjentImie"));
        PACJENT_NAZWISKO.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("pacjentNazw"));
        NOTATKA.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("notatka"));
        DATA.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("data"));

        br.close();
        bw.close();
        socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void setDodajWizyta() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("DodanieWizyta.fxml"));
        Parent root1 = (Parent) fxmlLoader.load();
        Stage stage = new Stage();
        stage.setTitle("Dodanie Wizyty");
        stage.setScene(new Scene(root1));
        stage.show();
    }


    @FXML
    private void setOknoWizyta() throws IOException {
        try {
            AppState.getInstance().setIDwizyty(listWizyty.getSelectionModel().getSelectedItem().getId());
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("ZmianaDanychWizyta.fxml"));
            Parent root1 = (Parent) fxmlLoader.load();
            Stage stage = new Stage();
            stage.setTitle("Edycja Wizyty");
            stage.setScene(new Scene(root1));
            stage.show();
        }
        catch(NullPointerException e)
        {
            status.setText("Należy wybrać pole z listy");
        }
    }

    @FXML
    private void filtrWizyty() throws IOException {
        String imi = imiePacjentwiz.getText();
        String nazw =  nazwiskoPacjentwiz.getText();
        String dat =  data.getText();
        String nota = notatka.getText();
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(16);
        bw.flush();
        bw.write(AppState.getInstance().getIDlekarza()+"\n");
        bw.flush();
        bw.write(imi + "\n");
        bw.flush();
        bw.write(nazw + "\n");
        bw.flush();
        bw.write(dat + "\n");
        bw.flush();
        bw.write(nota + "\n");
        bw.flush();
        List<Wizyta> lista = new ArrayList<>();
        ObjectMapper mapper = new ObjectMapper();
        String obiekt = br.readLine();
        JSONObject jsonIn = new JSONObject(obiekt);
        lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Wizyta[].class)).collect(Collectors.toList());
        ObservableList<Wizyta> pom = FXCollections.observableArrayList();

        listWizyty.getColumns().clear();
        listWizyty.getItems().clear();

        TableColumn WIZYTA_ID = new TableColumn("ID");
        TableColumn LEKARZ_NAZWISKO = new TableColumn("LEKARZ");
        TableColumn PACJENT_IMIE = new TableColumn("IMIĘ PACJENTA");
        TableColumn PACJENT_NAZWISKO = new TableColumn("NAZWISKO_PACJENT");
        TableColumn NOTATKA = new TableColumn("NOTATKA");
        TableColumn DATA = new TableColumn("DATA");

        listWizyty.getColumns().addAll(WIZYTA_ID, LEKARZ_NAZWISKO, PACJENT_IMIE, PACJENT_NAZWISKO, DATA, NOTATKA);

        for(int i = 0; i < lista.size(); ++i)
        {
            pom.add(new Wizyta(lista.get(i).getId(),lista.get(i).getLekarzNazw(),lista.get(i).getPacjentImie(),lista.get(i).getPacjentNazw(),lista.get(i).getData(),lista.get(i).getNotatka(),lista.get(i).getIdleki()));
            listWizyty.setItems(pom);
        }
        WIZYTA_ID.setCellValueFactory(new PropertyValueFactory<Wizyta, Long>("id"));
        LEKARZ_NAZWISKO.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("lekarzNazw"));
        PACJENT_IMIE.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("pacjentImie"));
        PACJENT_NAZWISKO.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("pacjentNazw"));
        NOTATKA.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("notatka"));
        DATA.setCellValueFactory(new PropertyValueFactory<Wizyta, String>("data"));

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
    private void wypiszLeki() throws IOException {
        try {
            AppState.getInstance().setIDwizyty(listWizyty.getSelectionModel().getSelectedItem().getId());
            AppState.getInstance().setCzypac(false);
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
