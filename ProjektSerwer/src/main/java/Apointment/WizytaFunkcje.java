package Apointment;

import Doctors.Lekarz;
import Medicines.Lek;
import Patients.Pacjent;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class WizytaFunkcje {

    private static final EntityManagerFactory FACTORY = Persistence.createEntityManagerFactory("MyUnit");

    public void stworzWizyte(Lekarz lekarz, Pacjent pacjent, String data, String notatka, List<Lek> leki) throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        transaction.begin();
        Wizyta wizyta = new Wizyta();
        wizyta.setData(data);
        wizyta.setLekarz(lekarz);
        wizyta.setPacjent(pacjent);
        wizyta.setLeki(leki);
        wizyta.setNotatka(notatka);
        entitymanager.merge(wizyta);
        transaction.commit();
        entitymanager.close();
    }

    public List<Wizyta> wypiszAll(Long lekarzid) throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        List<Wizyta> lista = entitymanager.createQuery("SELECT l FROM Wizyta l WHERE l.lekarz.id = :lekarzid", Wizyta.class).setParameter("lekarzid", lekarzid).getResultList();
        return lista;
    }

    public List<Wizyta> wypiszAll() throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        List<Wizyta> lista = entitymanager.createQuery("SELECT l FROM Wizyta l", Wizyta.class).getResultList();
        return lista;
    }

    public List<Wizyta> wypiszfiltr(Long lekarzid, List<Pacjent> pacjentid, String data, String notatka) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Wizyta> lista = new ArrayList<>();
        List<Wizyta> pom = new ArrayList<>();
        for(int i = 0; i < pacjentid.size(); ++i)
        {
            pom =  entitymanager.createQuery
                    ("SELECT l FROM Wizyta l  WHERE l.lekarz.id = :lekarzid and l.pacjent.id = :pacjentid and l.data LIKE :data and l.notatka LIKE :notatka")
                    .setParameter("lekarzid", lekarzid).setParameter( "pacjentid", pacjentid.get(i).getId()).setParameter("data", "%"+data+"%")
                    .setParameter("notatka", "%"+notatka+"%").getResultList();
            for(int j = 0; j < pom.size(); ++j)
            {
                lista.add(pom.get(j));
            }
        }

         return lista;
    }

    public void edytujWizyte(Long id, Lekarz lekarz, Pacjent pacjent, String data, String notatka, List<Lek> leki) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        Wizyta wizyta = entitymanager.find(Wizyta.class,id);
        transaction.begin();
        wizyta.setLekarz(lekarz);
        wizyta.setPacjent(pacjent);
        wizyta.setData(data);
        wizyta.setLeki(leki);
        wizyta.setNotatka(notatka);
        entitymanager.merge(wizyta);
        transaction.commit();
        entitymanager.close();
    }

    public List<Wizyta> szukajWizyta(Long id) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Wizyta> wizyta = entitymanager.createQuery
                ("SELECT l FROM Wizyta l  WHERE l.id = :id")
                .setParameter("id", id).getResultList();
        return wizyta;
    }
}
