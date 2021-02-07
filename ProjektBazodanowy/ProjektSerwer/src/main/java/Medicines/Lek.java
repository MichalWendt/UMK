package Medicines;

import Apointment.Wizyta;
import Doctors.Lekarz;
import Patients.Pacjent;
import utils.BaseEntity;

import javax.persistence.*;
import java.util.List;

@Entity
public class Lek extends BaseEntity {

    private String nazwa;
    private String sklad;

    @ManyToMany(mappedBy = "leki", fetch = FetchType.LAZY)
    private List<Pacjent> pacjenci;

    @ManyToMany(mappedBy = "leki", fetch = FetchType.LAZY,
            cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    private List<Wizyta> wizyty;

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

    public void addPacjent(Pacjent pacjent) {
        this.pacjenci.add(pacjent);
        pacjent.getLeki().add(this);
    }

    public void removePacjent(Pacjent pacjent) {
        this.pacjenci.remove(pacjent);
        pacjent.getLeki().remove(this);
    }

    public List<Pacjent> getPacjenci() {
        return pacjenci;
    }

    public void setPacjenci(List<Pacjent> pacjenci) {
        this.pacjenci = pacjenci;
    }

    @Override
    public String toString() {
        return  "id=" + id +
                ", nazwa='" + nazwa + '\'' +
                ", sklad='" + sklad + '\'' +
                '}' + "\n";
    }
}
