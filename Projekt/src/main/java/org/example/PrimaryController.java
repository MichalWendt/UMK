package org.example;

import java.io.*;

import javafx.fxml.FXML;

public class PrimaryController{
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
}
