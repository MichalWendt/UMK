package Patients;

public class PacjentDto {

    private Long id;
    private String imie;
    private String nazwisko;
    private String plec;
    private String leki;

    public PacjentDto(Long id, String imie, String nazwisko, String plec) {
        this.id = id;
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.plec = plec;
    }

    public PacjentDto(String imie, String nazwisko, String plec) {
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.plec = plec;
    }

    public PacjentDto(Long id, String imie, String nazwisko, String plec, String leki) {
        this.id = id;
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.plec = plec;
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
        return "PacjentDto{" +
                "id=" + id +
                ", imie='" + imie + '\'' +
                ", nazwisko='" + nazwisko + '\'' +
                ", plec='" + plec + '\'' +
                '}';
    }
}
