package Admins;

import Doctors.Lekarz;

import javax.persistence.*;
import java.sql.SQLException;
import java.util.List;

public class AdminFunkcje {

    private static final EntityManagerFactory FACTORY = Persistence.createEntityManagerFactory("MyUnit");

    public List<Admin> zaloguj(String email, String haslo) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Admin> lista = entitymanager.createQuery
                ("SELECT l FROM Admin l WHERE l.email LIKE :email AND l.haslo LIKE :haslo")
                .setParameter("email", email).setParameter( "haslo", haslo).getResultList();
        return lista;
    }

    public boolean czyrejestrowac(String email) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        Query query = entitymanager.createQuery("SELECT l FROM Admin l WHERE l.email LIKE :email").setParameter("email", email);
        List<Admin> lista = query.getResultList();
        if(lista.isEmpty())
        {
            return true;
        }
        return false;
    }

    public void rejestruj(String imie, String nazwisko, String email, String haslo, String plec) throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        transaction.begin();
        Admin admin = new Admin();
        admin.setImie(imie);
        admin.setNazwisko(nazwisko);
        admin.setEmail(email);
        admin.setHaslo(haslo);
        admin.setPlec(plec);
        entitymanager.merge(admin);
        transaction.commit();
        entitymanager.close();
    }

    public void edytujAdmina(Long id, String imie, String nazwisko, String email, String haslo, String plec) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        Admin admin = entitymanager.find(Admin.class,id);
        transaction.begin();
        admin.setImie(imie);
        admin.setNazwisko(nazwisko);
        admin.setEmail(email);
        admin.setHaslo(haslo);
        admin.setPlec(plec);
        entitymanager.merge(admin);
        transaction.commit();
        entitymanager.close();
    }

}
