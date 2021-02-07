package Medicines;

import Doctors.Lekarz;
import Patients.Pacjent;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class LekiFunkcje{

    private static final EntityManagerFactory FACTORY = Persistence.createEntityManagerFactory("MyUnit");

    public List<Lek> wypiszAll() throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        List<Lek> lista = entitymanager.createQuery("SELECT l FROM Lek l", Lek.class).getResultList();
        return lista;
    }

    public List<Lek> wypiszfiltr(String nazwa, String sklad) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Lek> lista = entitymanager.createQuery
                ("SELECT l FROM Lek l  WHERE l.nazwa LIKE :nazwa and l.sklad LIKE :sklad")
                .setParameter("nazwa", "%"+nazwa+"%").setParameter( "sklad", "%"+sklad+"%").getResultList();
        return lista;
    }

    public List<Lek> szukajId(Long id) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Lek> leki = new ArrayList<>();
        leki = entitymanager.createQuery
                ("SELECT l FROM Lek l WHERE l.id = :id")
                .setParameter("id", id).getResultList();
        return leki;
    }

    public List<Lek> idnaleki(List<String> lista) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Lek> leki = new ArrayList<>();
        for(int i = 0; i < lista.size(); ++i)
        {
            Lek lek = (Lek)entitymanager.createQuery
                    ("SELECT l FROM Lek l  WHERE l.nazwa LIKE :lista.get(i)")
                    .setParameter("lista.get(i)", lista.get(i)).getSingleResult();  //cos nie tak
            leki.add(lek);
        }
        return leki;
    }


    public void dodajLek(String nazwa, String sklad) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        transaction.begin();
        Lek lek = new Lek();
        lek.setNazwa(nazwa);
        lek.setSklad(sklad);
        entitymanager.merge(lek);
        transaction.commit();
        entitymanager.close();
    }

    public void edytujLek(Long id, String nazwa, String sklad) throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        Lek lek = entitymanager.find(Lek.class,id);
        transaction.begin();
        lek.setNazwa(nazwa);
        lek.setSklad(sklad);
        entitymanager.merge(lek);
        transaction.commit();
        entitymanager.close();
    }

    public void usunLek(Long id) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        Lek lek = entitymanager.find(Lek.class,id);
        transaction.begin();
        entitymanager.remove(lek);
        transaction.commit();
        entitymanager.close();
    }
}
