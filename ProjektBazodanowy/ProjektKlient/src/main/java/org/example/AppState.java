package org.example;

public class AppState {

    private static AppState ourInstance = new AppState();

    public static AppState getInstance() {
        return ourInstance;
    }


    private Long IDlekarza;
    private Long IDpacjenta;
    private Long IDlekU;
    private Long IDwizyty;
    private Long IDadmin;

    private boolean czypac;
    private boolean czyadmin;

    private String imie;
    private String nazwisko;
    private String email;
    private String haslo;
    private String plec;
    private String specyfikacja;


    public boolean isCzypac() {
        return czypac;
    }

    public void setCzypac(boolean czypac) {
        this.czypac = czypac;
    }

    public Long getIDadmin() {
        return IDadmin;
    }

    public void setIDadmin(Long IDadmin) {
        this.IDadmin = IDadmin;
    }

    public boolean getCzyadmin() {
        return czyadmin;
    }

    public void setCzyadmin(boolean czyadmin) {
        this.czyadmin = czyadmin;
    }

    public Long getIDlekarza() {
        return IDlekarza;
    }

    public void setIDlekarza(Long IDlekarza) {
        this.IDlekarza = IDlekarza;
    }

    public Long getIDpacjenta() {
        return IDpacjenta;
    }

    public void setIDpacjenta(Long IDpacjenta) {
        this.IDpacjenta = IDpacjenta;
    }

    public Long getIDlekU() {
        return IDlekU;
    }

    public void setIDlekU(Long IDlekU) {
        this.IDlekU = IDlekU;
    }

    public Long getIDwizyty() {
        return IDwizyty;
    }

    public void setIDwizyty(Long IDwizyty) {
        this.IDwizyty = IDwizyty;
    }

    public String getImie() {
        return imie;
    }

    public void setImie(String imie) {
        this.imie = imie;
    }

    public String getNazwisko() {
        return nazwisko;
    }

    public void setNazwisko(String nazwisko) {
        this.nazwisko = nazwisko;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getHaslo() {
        return haslo;
    }

    public void setHaslo(String haslo) {
        this.haslo = haslo;
    }

    public String getPlec() {
        return plec;
    }

    public void setPlec(String plec) {
        this.plec = plec;
    }

    public String getSpecyfikacja() {
        return specyfikacja;
    }

    public void setSpecyfikacja(String specyfikacja) {
        this.specyfikacja = specyfikacja;
    }
}
