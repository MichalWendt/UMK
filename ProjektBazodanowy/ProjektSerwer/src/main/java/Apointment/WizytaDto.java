package Apointment;

import Medicines.Lek;

import java.util.List;

public class WizytaDto {

    private Long id;
    private String lekarzNazw;
    private String pacjentImie;
    private String pacjentNazw;
    private String data;
    private String notatka;
    private List<Lek> leki;
    private String leki2;



    public WizytaDto(Long id, String lekarzNazw, String pacjentImie, String pacjentNazw, String data, String notatka, List<Lek> leki) {
        this.id = id;
        this.lekarzNazw = lekarzNazw;
        this.pacjentImie = pacjentImie;
        this.pacjentNazw = pacjentNazw;
        this.data = data;
        this.notatka = notatka;
        this.leki = leki;
    }

    public WizytaDto(Long id, String lekarzNazw, String pacjentImie, String pacjentNazw, String data, String notatka, String leki2) {
        this.id = id;
        this.lekarzNazw = lekarzNazw;
        this.pacjentImie = pacjentImie;
        this.pacjentNazw = pacjentNazw;
        this.data = data;
        this.notatka = notatka;
        this.leki2 = leki2;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public String getNotatka() {
        return notatka;
    }

    public void setNotatka(String notatka) {
        this.notatka = notatka;
    }

    public String getLekarzNazw() {
        return lekarzNazw;
    }

    public void setLekarzNazw(String lekarzNazw) {
        this.lekarzNazw = lekarzNazw;
    }

    public String getPacjentImie() {
        return pacjentImie;
    }

    public void setPacjentImie(String pacjentImie) {
        this.pacjentImie = pacjentImie;
    }

    public String getPacjentNazw() {
        return pacjentNazw;
    }

    public void setPacjentNazw(String pacjentNazw) {
        this.pacjentNazw = pacjentNazw;
    }

    public List<Lek> getLeki() {
        return leki;
    }

    public void setLeki(List<Lek> leki) {
        this.leki = leki;
    }

    @Override
    public String toString() {
        return "WizytaDto{" +
                "id=" + id +
                ", lekarzNazw='" + lekarzNazw + '\'' +
                ", pacjentImie='" + pacjentImie + '\'' +
                ", pacjentNazw='" + pacjentNazw + '\'' +
                ", data='" + data + '\'' +
                ", notatka='" + notatka + '\'' +
                ", leki=" + leki +
                '}';
    }
}
