package Medicines;

import Doctors.Lekarz;

import java.sql.SQLException;
import java.util.List;

public interface LekiBaza {

    public static List<Lek> wypiszAll() throws SQLException {
        return null;
    }

    public static List<Lek> wypiszfiltr(String nazwa, List<String> sklad) throws SQLException {
        return null;
    }

    public static void dodajLek(Long id, String nazwa, List<String> sklad) throws SQLException {

    }

    public void edytujLek(Long id, String nazwa , List<String>sklad) throws SQLException;

    public void usunLek(Long id) throws SQLException;
}
