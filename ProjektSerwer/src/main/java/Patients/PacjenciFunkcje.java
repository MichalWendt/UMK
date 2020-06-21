package Patients;

import Doctors.Lekarz;
import Medicines.Lek;

import javax.persistence.*;
import java.sql.SQLException;
import java.util.List;

public class PacjenciFunkcje{

    private static final EntityManagerFactory FACTORY = Persistence.createEntityManagerFactory("MyUnit");

    public List<Pacjent> wypiszAll() throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        List<Pacjent> lista = entitymanager.createQuery("SELECT l FROM Pacjent l", Pacjent.class).getResultList();
        return lista;
    }

    public List<Pacjent> wypiszfiltr(String imie, String nazwisko, String plec) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Pacjent> lista = entitymanager.createQuery
                ("SELECT l FROM Pacjent l  WHERE l.imie LIKE :imie and l.nazwisko LIKE :nazwisko and l.plec LIKE :plec")
                .setParameter("imie", "%"+imie+"%").setParameter( "nazwisko", "%"+nazwisko+"%").setParameter("plec", "%"+plec+"%").getResultList();
        return lista;
    }

    public List<Pacjent>  wypiszid(String imie, String nazwisko) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Pacjent> pacjent = entitymanager.createQuery
                ("SELECT l FROM Pacjent l  WHERE l.imie LIKE :imie and l.nazwisko LIKE :nazwisko")
                .setParameter("imie", "%"+imie+"%").setParameter( "nazwisko", "%"+nazwisko+"%").getResultList();
        return pacjent;
    }

    public List<Pacjent> szukajId(Long id) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Pacjent> pacjent = entitymanager.createQuery
                ("SELECT l FROM Pacjent l  WHERE l.id = :id")
                .setParameter("id", id).getResultList();
        return pacjent;
    }

    public  List<Pacjent>  szukajPacjenta(String imie, String nazwisko) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Pacjent> pacjent = entitymanager.createQuery
                ("SELECT l FROM Pacjent l  WHERE l.imie LIKE :imie and l.nazwisko LIKE :nazwisko")
                .setParameter("imie", "%"+imie+"%").setParameter( "nazwisko", "%"+nazwisko+"%").getResultList();
        return pacjent;
    }

    public void dodajPacjenta(String imie, String nazwisko, String plec, List<Lekarz> lekarz, List<Lek> leki) throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        List<Pacjent> pom = wypiszAll();
        transaction.begin();
        Pacjent pacjent = new Pacjent();
        pacjent.setImie(imie);
        pacjent.setNazwisko(nazwisko);
        pacjent.setPlec(plec);
        pacjent.setLekarze(lekarz);
        pacjent.setLeki(leki);
        entitymanager.merge(pacjent);
        transaction.commit();
        entitymanager.close();
    }

    public void edytujPacjenta(Long id, String imie, String nazwisko, String plec,List<Lek> leki) throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        Pacjent pacjent = entitymanager.find(Pacjent.class,id);
        transaction.begin();
        pacjent.setImie(imie);
        pacjent.setNazwisko(nazwisko);
        pacjent.setPlec(plec);
        pacjent.setLeki(leki);
        entitymanager.merge(pacjent);
        transaction.commit();
        entitymanager.close();
    }

    public boolean usunPacjenta(Long id) throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        Pacjent pacjent = entitymanager.find(Pacjent.class,id);
        transaction.begin();
        entitymanager.remove(pacjent);
        transaction.commit();
        entitymanager.close();
        return true;
    }
}
