package org.example;


public class Lek {

    private Long id;
    private String nazwa;
    private String sklad;

    public Lek(Long id, String nazwa, String sklad) {
        this.id = id;
        this.nazwa = nazwa;
        this.sklad = sklad;
    }

    public Lek() {
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getNazwa() {
        return nazwa;
    }

    public void setNazwa(String nazwa) {
        this.nazwa = nazwa;
    }

    public String getSklad() {
        return sklad;
    }

    public void setSklad(String sklad) {
        this.sklad = sklad;
    }

    @Override
    public String toString() {
        return "id=" + id +
                ", nazwa='" + nazwa + '\'' +
                ", sklad='" + sklad + '\'' +
                '}' + "\n";
    }
}
