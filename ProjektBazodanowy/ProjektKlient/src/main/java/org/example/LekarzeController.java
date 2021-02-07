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

public class LekarzeController implements Initializable {


    @FXML
    TextField imieLekarz;
    @FXML
    TextField nazwiskoLekarz;
    @FXML
    TextField email;
    @FXML
    TextField spec;

    @FXML
    Label status;


    @FXML
    TableView<Lekarz> listLekarze;
    @FXML private TableColumn<Lekarz, Long> LEKARZ_ID;
    @FXML private TableColumn<Lekarz, String> LEKARZ_IMIE;
    @FXML private TableColumn<Lekarz, String> LEKARZ_NAZWISKO;
    @FXML private TableColumn<Lekarz, String> EMAIL;
    @FXML private TableColumn<Lekarz, String> LEKARZ_PLEC;
    @FXML private TableColumn<Lekarz, String> SPECYFIKACJA;

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
        bw.write(3);
        bw.flush();
        List<Lekarz> lista = new ArrayList<>();
        ObjectMapper mapper = new ObjectMapper();
        String obiekt = br.readLine();
        JSONObject jsonIn = new JSONObject(obiekt);
        lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lekarz[].class)).collect(Collectors.toList());
        ObservableList<Lekarz> pom = FXCollections.observableArrayList();

            listLekarze.getColumns().clear();

        TableColumn LEKARZ_ID = new TableColumn("ID");
        TableColumn LEKARZ_IMIE = new TableColumn("IMIĘ");
        TableColumn LEKARZ_NAZWISKO = new TableColumn("NAZWISKO");
        TableColumn EMAIL = new TableColumn("EMAIL");
        TableColumn LEKARZ_PLEC = new TableColumn("PŁEĆ");
        TableColumn SPECYFIKACJA = new TableColumn("SPECYFIKACJA");

        listLekarze.getColumns().addAll(LEKARZ_ID, LEKARZ_IMIE, LEKARZ_NAZWISKO, EMAIL,LEKARZ_PLEC,SPECYFIKACJA);

        for(int i = 0; i < lista.size(); ++i)
        {
            pom.add(new Lekarz(lista.get(i).getId(),lista.get(i).getImie(),lista.get(i).getNazwisko(),lista.get(i).getEmail(),lista.get(i).getHaslo(),lista.get(i).getPlec(),lista.get(i).getSpecyfikacja()));
            listLekarze.setItems(pom);
        }
        LEKARZ_ID.setCellValueFactory(new PropertyValueFactory<Lekarz, Long>("id"));
        LEKARZ_IMIE.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("imie"));
        LEKARZ_NAZWISKO.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("nazwisko"));
        EMAIL.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("email"));
        LEKARZ_PLEC.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("plec"));
        SPECYFIKACJA.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("specyfikacja"));

        br.close();
        bw.close();
        socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void filtrLekarze() throws IOException {
        String imi = imieLekarz.getText();
        String nazw =  nazwiskoLekarz.getText();
        String log =  email.getText();
        String specyfikacja = spec.getText();
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(6);
        bw.flush();
        bw.write(imi + "\n");
        bw.flush();
        bw.write(nazw + "\n");
        bw.flush();
        bw.write(log + "\n");
        bw.flush();
        bw.write(specyfikacja + "\n");
        bw.flush();
        List<Lekarz> lista = new ArrayList<>();
        ObjectMapper mapper = new ObjectMapper();
        String obiekt = br.readLine();
        JSONObject jsonIn = new JSONObject(obiekt);
        lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lekarz[].class)).collect(Collectors.toList());

        listLekarze.getColumns().clear();

        ObservableList<Lekarz> pom = FXCollections.observableArrayList();

        TableColumn LEKARZ_ID = new TableColumn("ID");
        TableColumn LEKARZ_IMIE = new TableColumn("IMIĘ");
        TableColumn LEKARZ_NAZWISKO = new TableColumn("NAZWISKO");
        TableColumn EMAIL = new TableColumn("EMAIL");
        TableColumn LEKARZ_PLEC = new TableColumn("PŁEĆ");
        TableColumn SPECYFIKACJA = new TableColumn("SPECYFIKACJA");

        listLekarze.getColumns().addAll(LEKARZ_ID, LEKARZ_IMIE, LEKARZ_NAZWISKO, EMAIL,LEKARZ_PLEC,SPECYFIKACJA);

        for(int i = 0; i < lista.size(); ++i)
        {
            pom.add(new Lekarz(lista.get(i).getId(),lista.get(i).getImie(),lista.get(i).getNazwisko(),lista.get(i).getEmail(),lista.get(i).getHaslo(),lista.get(i).getPlec(),lista.get(i).getSpecyfikacja()));
            listLekarze.setItems(pom);
        }
        LEKARZ_ID.setCellValueFactory(new PropertyValueFactory<Lekarz, Long>("id"));
        LEKARZ_IMIE.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("imie"));
        LEKARZ_NAZWISKO.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("nazwisko"));
        EMAIL.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("email"));
        LEKARZ_PLEC.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("plec"));
        SPECYFIKACJA.setCellValueFactory(new PropertyValueFactory<Lekarz, String>("specyfikacja"));

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
    private void usunLekarza() throws IOException {
        Socket socket = new Socket("localhost", 8080);
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        bw.write(21);
        bw.flush();
        AppState.getInstance().setIDlekarza(listLekarze.getSelectionModel().getSelectedItem().getId());
        bw.write(AppState.getInstance().getIDlekarza()+"\n");
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

}