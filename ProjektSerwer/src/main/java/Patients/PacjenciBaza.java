package Patients;

import Doctors.Lekarz;

import java.sql.SQLException;
import java.util.List;

public interface PacjenciBaza {

    public static List<Pacjent> wypiszAll() throws SQLException {
        return null;
    }

    public List<Pacjent> wypiszfiltr(String imie, String nazwisko, String plec, List<String> leki) throws SQLException;

    public static void dodajPacjenta(String imie, String nazwisko, String plec, List<String> leki) throws SQLException {

    }

    public static void edytujPacjenta(String imie, String nazwisko, String plec, List<String> leki) throws SQLException {

    }

    public void usunPacjenta(Long id) throws SQLException;
}
