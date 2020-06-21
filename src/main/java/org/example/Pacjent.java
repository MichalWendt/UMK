package org.example;

public class Pacjent {

    private Long id;
    private String imie;
    private String nazwisko;
    private String plec;
    private String leki;

    public Pacjent(Long id, String imie, String nazwisko, String plec) {
        this.id = id;
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.plec = plec;
    }

    public Pacjent(Long id, String imie, String nazwisko, String plec, String leki) {
        this.id = id;
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.plec = plec;
        this.leki = leki;
    }

    public Pacjent() {
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
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

    public String getPlec() {
        return plec;
    }

    public void setPlec(String plec) {
        this.plec = plec;
    }

    public String getLeki() {
        return leki;
    }

    public void setLeki(String leki) {
        this.leki = leki;
    }


    @Override
    public String toString() {
        return "Main.Pacjent{" +
                "id=" + id +
                ", imie='" + imie + '\'' +
                ", nazwisko='" + nazwisko + '\'' +
                ", plec='" + plec + '\'' +
                ", leki='" + leki + '\'' +
                '}';
    }
}
