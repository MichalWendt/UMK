package Doctors;

import java.sql.SQLException;
import java.util.List;

public interface LekarzeRepository {

    public boolean zaloguj(String email, String haslo) throws SQLException;

    public boolean czyrejestrowac(String email) throws SQLException;

    public void rejestruj(String imie, String nazwisko, String email, String haslo, String plec, List<String>  specyfikacje) throws SQLException;

    public List<Lekarz> wypiszAll() throws SQLException;

    public List<Lekarz> wypiszfiltr(String imie, String nazwisko, String email, List<String> specyfikacje) throws SQLException;

    public void edytujLekarza(Long id, String imie, String nazwisko, String email, String haslo, String plec, List<String> specyfikacje) throws SQLException;

    public void usunLekarza(Long id) throws SQLException;
}
