package org.example;

@SuppressWarnings("JpaAttributeTypeInspection")
public class Lekarz {

    private Long id;
    private String imie;
    private String nazwisko;
    private String email;
    private String haslo;
    private String plec;
    private String specyfikacja;

    public Lekarz() {
    }

    public Lekarz(Long id, String imie, String nazwisko, String email, String haslo, String plec, String specyfikacja) {
        this.id = id;
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.email = email;
        this.haslo = haslo;
        this.plec = plec;
        this.specyfikacja = specyfikacja;
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
        return "Main.Lekarz{" +
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
