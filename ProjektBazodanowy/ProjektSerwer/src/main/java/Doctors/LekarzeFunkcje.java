package Doctors;

import javax.persistence.*;
import java.sql.SQLException;
import java.util.List;

public class LekarzeFunkcje{

    private static final EntityManagerFactory FACTORY = Persistence.createEntityManagerFactory("MyUnit");


    public List<Lekarz> zaloguj(String email, String haslo) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Lekarz> lista = entitymanager.createQuery
                ("SELECT l FROM Lekarz l WHERE l.email LIKE :email AND l.haslo LIKE :haslo")
                .setParameter("email", email).setParameter( "haslo", haslo).getResultList();
        return lista;
    }

    public boolean czyrejestrowac(String email) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        Query query = entitymanager.createQuery("SELECT l FROM Lekarz l WHERE l.email LIKE :email").setParameter("email", email);
        List<Lekarz> lista = query.getResultList();
        if(lista.isEmpty())
        {
            return true;
        }
        return false;
    }

    public void rejestruj(String imie, String nazwisko, String email, String haslo, String plec, String specyfikacje) throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        transaction.begin();
        Lekarz lekarz = new Lekarz();
        lekarz.setImie(imie);
        lekarz.setNazwisko(nazwisko);
        lekarz.setEmail(email);
        lekarz.setHaslo(haslo);
        lekarz.setPlec(plec);
        lekarz.setSpecyfikacja(specyfikacje);
        entitymanager.merge(lekarz);
        transaction.commit();
        entitymanager.close();
    }

    public List<Lekarz> wypiszAll() throws SQLException {

        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        List<Lekarz> lista = entitymanager.createQuery("SELECT l FROM Lekarz l", Lekarz.class).getResultList();
        return lista;
    }

    public List<Lekarz> wypiszfiltr(String imie, String nazwisko, String email, String specyfikacja) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Lekarz> lista = entitymanager.createQuery
                ("SELECT l FROM Lekarz l WHERE l.imie LIKE :imie and l.nazwisko LIKE :nazwisko and l.email LIKE :email and l.specyfikacja LIKE :specyfikacja")
                .setParameter("imie", "%"+imie+"%").setParameter( "nazwisko", "%"+nazwisko+"%").setParameter("email", "%"+email+"%").setParameter("specyfikacja", "%"+specyfikacja+"%").getResultList();
        return lista;
    }


    public List<Lekarz> szukajLekarza(Long id) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Lekarz> lekarz = entitymanager.createQuery
                ("SELECT l FROM Lekarz l  WHERE l.id = :id")
                .setParameter("id", id).getResultList();
        return lekarz;
    }

    public List<Lekarz> szukajLekarzaNazw(String nazwisko) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        List<Lekarz> lekarz = entitymanager.createQuery
                ("SELECT l FROM Lekarz l  WHERE l.nazwisko LIKE :nazwisko")
                .setParameter("nazwisko", nazwisko).getResultList();
        return lekarz;
    }

    public void edytujLekarza(Long id, String imie, String nazwisko, String email, String haslo, String plec, String specyfikacje) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        Lekarz lekarz = entitymanager.find(Lekarz.class,id);
        transaction.begin();
        lekarz.setImie(imie);
        lekarz.setNazwisko(nazwisko);
        lekarz.setEmail(email);
        lekarz.setHaslo(haslo);
        lekarz.setPlec(plec);
        lekarz.setSpecyfikacja(specyfikacje);
        entitymanager.merge(lekarz);
        transaction.commit();
        entitymanager.close();
    }

    public void usunLekarza(Long id) throws SQLException {
        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        Lekarz lekarz = entitymanager.find(Lekarz.class,id);
        transaction.begin();
        entitymanager.remove(lekarz);
        transaction.commit();
        entitymanager.close();
    }
}

    /*public void wypelnij()
    {
        EntityManager entitymanager = FACTORY.createEntityManager();
        EntityTransaction transaction = entitymanager.getTransaction();
        transaction.begin();
        String[] tab = {"Psychiatria", "Pediatria", "Okulistyka", "Neurologia", "Kardiologia" ,"Epidemiologia" ,
                "Chirurgia dziecięca" ,"Anestezjologia" ,"Chirurgia ogólna" ,"Choroby zakaźne" ,"Medycyna pracy" ,"Ortopedia"};
        for(int i = 0; i < 12; ++i)
        {
            Specyfikacje spec = new Specyfikacje();
            spec.setNazwa(tab[i]);
            entitymanager.merge(spec);
            transaction.commit();
        }
        entitymanager.close();
    }*/

//WYPISZ ALL
/*Query q = entityManager.createQuery("select d from Lekarz d where id = max(id) AND d.imie LIKE :name").setParameter("name",name);
        for(long i = 1; i < q; ++i)
        {
            Lekarz lekarz = entitymanager.find(Lekarz.class,i);
            list.add(lekarz);
        }

        @Query("SELECT u FROM User u WHERE LOWER(CONCAT(u.firstName , ' ', u.lastName)) LIKE :name")
        fun( "%" + imie + "%" +  nazwisko + "%");



        Session session = SessionFactory.getSessionFactory().getCurrentSession();
        session.beginTransaction();

        List<Lekarz> list = session.createQuery("from Lekarz", Lekarz.class).list();
        session.getTransaction().commit();

        return list;

        try
        {
            return sessionFactory.getCurrentSession().createCriteria(Lekarz.class).list();
        } catch (Exception e) {
            return new ArrayList<>();
        }
        CriteriaBuilder cb = session.getCriteriaBuilder();
        CriteriaQuery<Lekarz> cq = cb.createQuery(Lekarz.class);
        cq.from(Lekarz.class);
        //List<Lekarz> data = session.createQuery(cq).getResultList();
        return session.createQuery(cq).getResultList();

        Root<Lekarz> rootEntry = cq.from(Lekarz.class);
        CriteriaQuery<Lekarz> all = cq.select(rootEntry);

        TypedQuery<Student> allQuery = session.createQuery(all);
        return allQuery.getResultList();

        EntityManager entityManager = FACTORY.createEntityManager();
        Query q = entityManager.createQuery("select d from Lekarz d");
        List<Lekarz> list = q.getResultList();
        return list;*/