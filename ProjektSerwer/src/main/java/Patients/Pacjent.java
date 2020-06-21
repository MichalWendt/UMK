package Patients;

import Apointment.Wizyta;
import Doctors.Lekarz;
import Medicines.Lek;
import utils.BaseEntity;

import javax.persistence.*;
import java.util.List;

@Entity
public class Pacjent extends BaseEntity {

    private String imie;
    private String nazwisko;
    private String plec;

    @ManyToMany
    @JoinTable(
            name = "PacjenciLekarza",
            joinColumns = @JoinColumn(name = "pacjent_id"),
            inverseJoinColumns = @JoinColumn(name = "lekarz_id")
    )
    private List<Lekarz> lekarze;

    @ManyToMany(cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    @JoinTable(
            name = "LekiPacjenta",
            joinColumns = {@JoinColumn(name = "pacjent_id")},
            inverseJoinColumns = {@JoinColumn(name = "lek_id")}
    )
    private List<Lek> leki;

    @OneToMany(mappedBy = "pacjent",fetch = FetchType.LAZY)
    private List<Wizyta> wizyty;

    public void addLekarz(Lekarz lekarz) {
        this.lekarze.add(lekarz);
        lekarz.getPacjenci().add(this);
    }

    public void removeLekarz(Lekarz lekarz) {
        this.lekarze.remove(lekarz);
        lekarz.getPacjenci().remove(this);
    }

    public void addLek(Lek lek) {
        this.leki.add(lek);
        lek.getPacjenci().add(this);
    }

    public void removeLek(Lek lek) {
        this.leki.remove(lek);
        lek.getPacjenci().remove(this);
    }

    public List<Lek> getLeki() {
        return leki;
    }

    public List<Lekarz> getLekarze() {
        return lekarze;
    }

    public void setLekarze(List<Lekarz> lekarze) {
        this.lekarze = lekarze;
    }

    public void setLeki(List<Lek> leki) {
        this.leki = leki;
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

    @Override
    public String toString() {
        return "Pacjent{" +
                "id=" + id +
                ", imie='" + imie + '\'' +
                ", nazwisko='" + nazwisko + '\'' +
                ", plec='" + plec + '\'' +
                '}';
    }
}
