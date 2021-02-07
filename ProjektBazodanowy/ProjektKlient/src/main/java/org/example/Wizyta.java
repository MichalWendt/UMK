package org.example;

import java.util.List;

public class Wizyta {

    private Long id;
    private String lekarzNazw;
    private String pacjentImie;
    private String pacjentNazw;
    private String data;
    private String notatka;
    private List<Lek> idleki;
    private String leki;

    public Wizyta(Long id, String lekarzNazw, String pacjentImie, String pacjentNazw, String data, String notatka, String leki) {
        this.id = id;
        this.lekarzNazw = lekarzNazw;
        this.pacjentImie = pacjentImie;
        this.pacjentNazw = pacjentNazw;
        this.data = data;
        this.notatka = notatka;
        this.leki = leki;
    }

    public Wizyta(Long id, String lekarzNazw, String pacjentImie, String pacjentNazw, String data, String notatka, List<Lek> idleki) {
        this.id = id;
        this.lekarzNazw = lekarzNazw;
        this.pacjentImie = pacjentImie;
        this.pacjentNazw = pacjentNazw;
        this.data = data;
        this.notatka = notatka;
        this.idleki = idleki;
    }

    public Wizyta() {
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

    public List<Lek> getIdleki() {
        return idleki;
    }

    public void setIdleki(List<Lek> idleki) {
        this.idleki = idleki;
    }

    public String getLeki() {
        return leki;
    }

    public void setLeki(String leki) {
        this.leki = leki;
    }


}
