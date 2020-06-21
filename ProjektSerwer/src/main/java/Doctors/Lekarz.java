package Doctors;

import Apointment.Wizyta;
import Medicines.Lek;
import Patients.Pacjent;
import utils.BaseEntity;

import javax.persistence.*;
import java.util.List;

@SuppressWarnings("JpaAttributeTypeInspection")
@Entity
public class Lekarz extends BaseEntity {

    private String imie;
    private String nazwisko;
    private String email;
    private String haslo;
    private String plec;
    private String specyfikacja;

    @ManyToMany(mappedBy = "lekarze", fetch = FetchType.LAZY,   //pacjencilekarza
    cascade = {CascadeType.MERGE, CascadeType.PERSIST})
    private List<Pacjent> pacjenci;

    @OneToMany(mappedBy = "lekarz",fetch = FetchType.LAZY)
    private List<Wizyta> wizyty;

    public void addPacjent(Pacjent pacjent) {
        this.pacjenci.add(pacjent);
        pacjent.getLekarze().add(this);
    }

    public void removePacjent(Pacjent pacjent) {
        this.pacjenci.remove(pacjent);
        pacjent.getLekarze().remove(this);
    }

    public Lekarz() {
    }

    public List<Pacjent> getPacjenci() {
        return pacjenci;
    }

    public void setPacjenci(List<Pacjent> pacjenci) {
        this.pacjenci = pacjenci;
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

    @Override
    public String toString() {
        return "Lekarz{" +
                "id=" + id +
                ", imie='" + imie + '\'' +
                ", nazwisko='" + nazwisko + '\'' +
                ", email='" + email + '\'' +
                ", haslo='" + haslo + '\'' +
                ", plec='" + plec + '\'' +
                ", specyfikacja='" + specyfikacja + '\'' +
                '}';
    }
}
