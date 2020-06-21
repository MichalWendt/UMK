package Apointment;

import Doctors.Lekarz;
import Medicines.Lek;
import Patients.Pacjent;
import utils.BaseEntity;

import javax.persistence.*;
import java.util.List;

@Entity
public class Wizyta extends BaseEntity {

    private String data;
    private String notatka;

    @ManyToOne(fetch = FetchType.LAZY, cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    @JoinColumn(name = "pacjent_id")
    private Pacjent pacjent;

    @ManyToOne(fetch = FetchType.LAZY, cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    @JoinColumn(name = "lekarz_id")
    private Lekarz lekarz;

    @ManyToMany(cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    @JoinTable(
            name = "LekiWizyty",
            joinColumns = {@JoinColumn(name = "wizyta_id")},
            inverseJoinColumns = {@JoinColumn(name = "lek_id")}
    )
    private List<Lek> leki;


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

    public Pacjent getPacjent() {
        return pacjent;
    }

    public void setPacjent(Pacjent pacjent) {
        this.pacjent = pacjent;
    }

    public Lekarz getLekarz() {
        return lekarz;
    }

    public void setLekarz(Lekarz lekarz) {
        this.lekarz = lekarz;
    }

    public List<Lek> getLeki() {
        return leki;
    }

    public void setLeki(List<Lek> leki) {
        this.leki = leki;
    }

    @Override
    public String toString() {
        return "Wizyta{" +
                "id=" + id +
                ", data='" + data + '\'' +
                ", notatka='" + notatka + '\'' +
                ", pacjent=" + pacjent +
                ", lekarz=" + lekarz +
                ", leki=" + leki +
                '}';
    }
}
