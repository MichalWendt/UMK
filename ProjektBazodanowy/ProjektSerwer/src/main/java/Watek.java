import Admins.Admin;
import Admins.AdminFunkcje;
import Apointment.Wizyta;
import Apointment.WizytaDto;
import Apointment.WizytaFunkcje;
import Doctors.Lekarz;
import Doctors.LekarzDto;
import Doctors.LekarzeFunkcje;
import Medicines.Lek;
import Medicines.LekDto;
import Medicines.LekiFunkcje;
import Patients.PacjenciFunkcje;
import Patients.Pacjent;
import Patients.PacjentDto;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.json.JSONObject;

import java.io.*;
import java.net.Socket;
import java.sql.SQLException;
import java.util.*;
import java.util.stream.Collectors;

public class Watek extends Thread {

    private Socket socket;

    public Watek(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            int wybor = br.read();
            switch(wybor) {
                case 1:         //logowanie
                {
                    LekarzeFunkcje baza = new LekarzeFunkcje();
                    AdminFunkcje baza2 = new AdminFunkcje();
                    List<Lekarz> lekarz;
                    List<Admin> admin;

                    String login = br.readLine();
                    String haslo = br.readLine();

                    lekarz = baza.zaloguj(login, haslo);
                    admin = baza2.zaloguj(login, haslo);
                    if(!(lekarz.isEmpty())) {
                        bw.write(1);
                        bw.flush();
                        bw.write(lekarz.get(0).getId().toString());
                        bw.flush();
                    }
                    else if(!(admin.isEmpty())) {
                        bw.write(2);
                        bw.flush();
                        bw.write(admin.get(0).getId().toString());
                        bw.flush();
                    }
                    else{
                        bw.write(0);
                        bw.flush();
                        bw.write("7");
                        bw.flush();
                    }
                    break;
                }
                case 2:         //rejestracja
                {
                    LekarzeFunkcje baza = new LekarzeFunkcje();

                    String login = br.readLine();

                    if(baza.czyrejestrowac(login))
                    {
                        bw.write(1);
                        bw.flush();
                        String imie = br.readLine();
                        String nazwisko = br.readLine();
                        String haslo = br.readLine();
                        String plec = br.readLine();
                        String spec = br.readLine();

                        baza.rejestruj(imie,nazwisko,login,haslo,plec,spec);
                    }
                    else
                    {
                        bw.write(0);
                    }
                    break;
                }
                case 14:        //rejestracja Admina
                {
                    AdminFunkcje baza = new AdminFunkcje();

                    String login = br.readLine();

                    if(baza.czyrejestrowac(login))
                    {
                        bw.write(1);
                        bw.flush();
                        String imie = br.readLine();
                        String nazwisko = br.readLine();
                        String haslo = br.readLine();
                        String plec = br.readLine();

                        baza.rejestruj(imie,nazwisko,login,haslo,plec);
                    }
                    else
                    {
                        bw.write(0);
                    }
                    break;
                }
                case 3:         //wypisanie lekarzy
                {
                    LekarzeFunkcje baza = new LekarzeFunkcje();
                    List<LekarzDto> lista = new ArrayList<>();
                    List<Lekarz> pom = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    pom = baza.wypiszAll();
                    for(int i = 0; i < pom.size(); ++i)
                    {
                        LekarzDto pomlek = new LekarzDto(pom.get(i).getId(),pom.get(i).getImie(),pom.get(i).getNazwisko(),pom.get(i).getEmail(),pom.get(i).getHaslo(),pom.get(i).getPlec(),pom.get(i).getSpecyfikacja());
                        lista.add(pomlek);
                    }
                    lista.sort(Comparator.comparing(LekarzDto::getId));

                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();

                    break;
                }
                case 4:         //wypisanie pacjentow
                {
                    PacjenciFunkcje baza = new PacjenciFunkcje();
                    List<PacjentDto> lista = new ArrayList<>();
                    List<Pacjent> pom = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    pom = baza.wypiszAll();
                    for(int i = 0; i < pom.size(); ++i)
                    {
                        PacjentDto pompac = new PacjentDto(pom.get(i).getId(),pom.get(i).getImie(),pom.get(i).getNazwisko(),pom.get(i).getPlec());
                        lista.add(pompac);
                    }
                    lista.sort(Comparator.comparing(PacjentDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    break;
                }
                case 5:         //wypisanie leków
                {
                    LekiFunkcje baza = new LekiFunkcje();
                    List<LekDto> lista = new ArrayList<>();
                    List<Lek> pom = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    pom = baza.wypiszAll();
                    for(int i = 0; i < pom.size(); ++i)
                    {
                        LekDto pomlek = new LekDto(pom.get(i).getId(),pom.get(i).getNazwa(),pom.get(i).getSklad());
                        lista.add(pomlek);
                    }
                    lista.sort(Comparator.comparing(LekDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    break;
                }
                case 15:         //wypisanie wizyt
                {
                    WizytaFunkcje baza = new WizytaFunkcje();
                    PacjenciFunkcje baza2 = new PacjenciFunkcje();
                    LekarzeFunkcje baza3 = new LekarzeFunkcje();
                    List<WizytaDto> lista = new ArrayList<>();
                    List<Wizyta> pom = new ArrayList<>();
                    List<LekDto> leki = new ArrayList<>();
                    List<List<LekDto>> leki2 = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();

                    Long id = Long.parseLong(br.readLine());

                    pom = baza.wypiszAll(id);

                    StringBuilder builder = new StringBuilder();

                    for (int i = 0; i < pom.size(); ++i) {
                        WizytaDto pomwiz = new WizytaDto(pom.get(i).getId(),pom.get(i).getLekarz().getNazwisko(),pom.get(i).getPacjent().getImie(),
                                pom.get(i).getPacjent().getNazwisko(),pom.get(i).getData(),pom.get(i).getNotatka(),pom.get(i).getLeki().toString());
                        lista.add(pomwiz);
                    }
                    lista.sort(Comparator.comparing(WizytaDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();

                    break;
                }
                case 27:         //wypisanie wizyt admina
                {
                    WizytaFunkcje baza = new WizytaFunkcje();
                    PacjenciFunkcje baza2 = new PacjenciFunkcje();
                    LekarzeFunkcje baza3 = new LekarzeFunkcje();
                    List<WizytaDto> lista = new ArrayList<>();
                    List<Wizyta> pom = new ArrayList<>();
                    List<LekDto> leki = new ArrayList<>();
                    List<List<LekDto>> leki2 = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();


                    pom = baza.wypiszAll();

                    StringBuilder builder = new StringBuilder();

                    for (int i = 0; i < pom.size(); ++i) {
                        WizytaDto pomwiz = new WizytaDto(pom.get(i).getId(),pom.get(i).getLekarz().getNazwisko(),pom.get(i).getPacjent().getImie(),
                                pom.get(i).getPacjent().getNazwisko(),pom.get(i).getData(),pom.get(i).getNotatka(),pom.get(i).getLeki().toString());
                        lista.add(pomwiz);

                    }
                    lista.sort(Comparator.comparing(WizytaDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();

                    break;
                }
                case 6:         //filtrowanie lekarzy
                {
                    LekarzeFunkcje baza = new LekarzeFunkcje();
                    List<LekarzDto> lista = new ArrayList<>();
                    List<Lekarz> pom = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    String imie="",nazwisko="",email="",spec="";

                    imie = br.readLine();
                    nazwisko = br.readLine();
                    email = br.readLine();
                    spec = br.readLine();

                    pom = baza.wypiszfiltr(imie, nazwisko, email,spec);

                    for(int i = 0; i < pom.size(); ++i)
                    {
                        LekarzDto pomlek = new LekarzDto(pom.get(i).getId(),pom.get(i).getImie(),pom.get(i).getNazwisko(),
                                pom.get(i).getEmail(),pom.get(i).getHaslo(),pom.get(i).getPlec(),pom.get(i).getSpecyfikacja());
                        lista.add(pomlek);
                    }
                    lista.sort(Comparator.comparing(LekarzDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    bw.write(lista.toString());
                    break;
                }
                case 7:         //filtrowanie pacjentow
                {
                    PacjenciFunkcje baza = new PacjenciFunkcje();
                    List<PacjentDto> lista = new ArrayList<>();
                    List<Pacjent> pom = new ArrayList<>();
                    String imie,nazwisko,plec;         //dodaj filtrowanie po lekarzu

                    imie = br.readLine();
                    nazwisko = br.readLine();
                    plec = br.readLine();

                    pom = baza.wypiszfiltr(imie,nazwisko,plec);

                    for(int i = 0; i < pom.size(); ++i)
                    {
                        PacjentDto pompac = new PacjentDto(pom.get(i).getId(),pom.get(i).getImie(),pom.get(i).getNazwisko(),pom.get(i).getPlec());
                        lista.add(pompac);
                    }
                    ObjectMapper mapper = new ObjectMapper();
                    lista.sort(Comparator.comparing(PacjentDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    bw.write(lista.toString());
                    break;
                }
                case 8:         //filtrowanie lekow
                {
                    LekiFunkcje baza = new LekiFunkcje();
                    List<LekDto> lista = new ArrayList<>();
                    List<Lek> pom = new ArrayList<>();
                    String nazwa, sklad;

                    nazwa = br.readLine();
                    sklad = br.readLine();

                    pom = baza.wypiszfiltr(nazwa,sklad);
                    for(int i = 0; i < pom.size(); ++i)
                    {
                        LekDto pomlek = new LekDto(pom.get(i).getId(),pom.get(i).getNazwa(),pom.get(i).getSklad());
                        lista.add(pomlek);
                    }

                    ObjectMapper mapper = new ObjectMapper();
                    lista.sort(Comparator.comparing(LekDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    bw.write(lista.toString());
                    break;
                }
                case 16:         //filtrowanie wizyt
                {
                    WizytaFunkcje baza = new WizytaFunkcje();
                    PacjenciFunkcje baza2 = new PacjenciFunkcje();
                    LekarzeFunkcje baza3 = new LekarzeFunkcje();
                    List<WizytaDto> lista = new ArrayList<>();
                    List<Wizyta> pom = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    String pacjentimie, pacjentnazwisko, data, notatka;
                    List<Pacjent> pacjent;
                    Long lekarzid;

                    lekarzid = Long.parseLong(br.readLine());
                    pacjentimie = br.readLine();
                    pacjentnazwisko = br.readLine();
                    data = br.readLine();
                    notatka = br.readLine();

                    pacjent = baza2.wypiszid(pacjentimie,pacjentnazwisko);
                    if(pacjent.isEmpty())
                    {
                        pacjent = baza2.wypiszAll();
                    }
                    pom = baza.wypiszfiltr(lekarzid, pacjent, data,notatka);


                    StringBuilder builder = new StringBuilder();

                    for(int i = 0; i < pom.size(); ++i)
                    {
                        WizytaDto pomwiz = new WizytaDto(pom.get(i).getId(),pom.get(i).getLekarz().getNazwisko(),pom.get(i).getPacjent().getImie(),
                                pom.get(i).getPacjent().getNazwisko(),pom.get(i).getData(),pom.get(i).getNotatka(),pom.get(i).getLeki().toString());
                        lista.add(pomwiz);
                    }
                    lista.sort(Comparator.comparing(WizytaDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    bw.write(lista.toString());
                    break;
                }
                case 26:         //edycja admina
                {
                    AdminFunkcje baza = new AdminFunkcje();
                    String imie,nazwisko,email,plec,haslo;
                    Long id;

                    id = Long.parseLong(br.readLine());
                    imie = br.readLine();
                    nazwisko = br.readLine();
                    email = br.readLine();
                    plec = br.readLine();
                    haslo = br.readLine();

                    baza.edytujAdmina(id, imie, nazwisko, email,haslo,plec);
                    break;
                }
                case 9:         //edycja lekarza
                {
                    LekarzeFunkcje baza = new LekarzeFunkcje();
                    String imie,nazwisko,email,plec,haslo,spec;
                    Long id;

                    id = Long.parseLong(br.readLine());
                    imie = br.readLine();
                    nazwisko = br.readLine();
                    email = br.readLine();
                    plec = br.readLine();
                    haslo = br.readLine();
                    spec = br.readLine();

                    baza.edytujLekarza(id, imie, nazwisko, email,haslo,plec,spec);
                    break;
                }
                case 10:        //edycja pacjenta
                {
                    PacjenciFunkcje baza = new PacjenciFunkcje();
                    String imie,nazwisko,plec;
                    List<Lek> leki;
                    Long id;

                    id = Long.parseLong(br.readLine());
                    imie = br.readLine();
                    nazwisko = br.readLine();
                    plec = br.readLine();

                    ObjectMapper mapper = new ObjectMapper();
                    String obiekt = br.readLine();
                    JSONObject jsonIn = new JSONObject(obiekt);
                    leki = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lek[].class)).collect(Collectors.toList());

                    baza.edytujPacjenta(id, imie,nazwisko,plec,leki);
                    break;
                }
                case 11:        //edycja leku
                {
                    LekiFunkcje baza = new LekiFunkcje();
                    String nazwa, sklad;
                    Long id;

                    id = Long.parseLong(br.readLine());
                    nazwa = br.readLine();
                    sklad = br.readLine();

                    baza.edytujLek(id,nazwa,sklad);
                    break;
                }
                case 18:        //edycja wizyty
                {
                    WizytaFunkcje baza = new WizytaFunkcje();
                    PacjenciFunkcje pom = new PacjenciFunkcje();
                    LekarzeFunkcje pom2 = new LekarzeFunkcje();
                    LekiFunkcje pom3 = new LekiFunkcje();

                    String lekarznazw,pacjentimie, pacjentnazwisko, data, notatka;
                    List<Pacjent> pacjent;
                    Lekarz lekarz;
                    Long id;

                    id = Long.parseLong(br.readLine());
                    lekarznazw = br.readLine();
                    pacjentimie = br.readLine();
                    pacjentnazwisko = br.readLine();
                    data = br.readLine();
                    notatka = br.readLine();

                    List<Lekarz> pomlista = new ArrayList<>();
                    pomlista = pom2.szukajLekarzaNazw(lekarznazw);
                    lekarz = pomlista.get(0);

                    pacjent = pom.szukajPacjenta(pacjentimie,pacjentnazwisko);
                    List<Lek> lista = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    String obiekt = br.readLine();
                    JSONObject jsonIn = new JSONObject(obiekt);
                    lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lek[].class)).collect(Collectors.toList());

                    baza.edytujWizyte(id,lekarz,pacjent.get(0),data,notatka,lista);
                    break;
                }
                case 12:        //dodanie pacjenta
                {
                    PacjenciFunkcje baza = new PacjenciFunkcje();
                    LekarzeFunkcje baza2 = new LekarzeFunkcje();
                    Long id;
                    String imie,nazwisko,plec;
                    List<Lekarz> lekarz;
                    List<Lek> leki;

                    id = Long.valueOf(br.readLine());
                    imie = br.readLine();
                    nazwisko = br.readLine();
                    plec = br.readLine();

                    lekarz = baza2.szukajLekarza(id);

                    ObjectMapper mapper = new ObjectMapper();
                    String obiekt = br.readLine();
                    JSONObject jsonIn = new JSONObject(obiekt);
                    leki = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lek[].class)).collect(Collectors.toList());

                    baza.dodajPacjenta(imie,nazwisko,plec,lekarz,leki);
                    break;
                }
                case 13:        //dodanie leku
                {
                    LekiFunkcje baza = new LekiFunkcje();
                    String nazwa, sklad;

                    nazwa = br.readLine();
                    sklad = br.readLine();

                    baza.dodajLek(nazwa,sklad);
                    break;
                }
                case 17:        //dodanie wizyty
                {
                    WizytaFunkcje baza = new WizytaFunkcje();
                    PacjenciFunkcje pom = new PacjenciFunkcje();
                    LekarzeFunkcje pom2 = new LekarzeFunkcje();
                    LekiFunkcje pom3 = new LekiFunkcje();

                    String pacjentimie, pacjentnazwisko, data, notatka,lekarznazw;;
                    List<Pacjent> pacjent;
                    Lekarz lekarz;

                    lekarznazw = br.readLine();
                    pacjentimie = br.readLine();
                    pacjentnazwisko = br.readLine();
                    data = br.readLine();
                    notatka = br.readLine();

                    List<Lekarz> pomlista = new ArrayList<>();
                    pomlista = pom2.szukajLekarzaNazw(lekarznazw);
                    lekarz = pomlista.get(0);
                    pacjent = pom.szukajPacjenta(pacjentimie,pacjentnazwisko);


                    List<Lek> lista = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    String obiekt = br.readLine();
                    JSONObject jsonIn = new JSONObject(obiekt);
                    lista = Arrays.stream(mapper.readValue(jsonIn.getString("lista"), Lek[].class)).collect(Collectors.toList());

                    baza.stworzWizyte(lekarz,pacjent.get(0),data,notatka,lista);
                    break;
                }
                case 19:        //szukanie lekarza po id
                {
                    LekarzeFunkcje pom2 = new LekarzeFunkcje();

                    List<Lekarz> pom = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    Long lekarzid;

                    lekarzid = Long.parseLong(br.readLine());
                    pom = pom2.szukajLekarza(lekarzid);

                    List<LekarzDto> lista = new ArrayList<>();


                    for(int i = 0; i < pom.size(); ++i)
                    {
                        LekarzDto pomlek = new LekarzDto(pom.get(i).getId(),pom.get(i).getImie(),pom.get(i).getNazwisko(),
                                pom.get(i).getEmail(),pom.get(i).getHaslo(),pom.get(i).getPlec(),pom.get(i).getSpecyfikacja());
                        lista.add(pomlek);
                    }
                    lista.sort(Comparator.comparing(LekarzDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    bw.write(lista.toString());

                    break;
                }
                case 20:        //szukanie wizyty po id
                {
                    WizytaFunkcje pom2 = new WizytaFunkcje();

                    List<Wizyta> pom = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    Long wizytaid;

                    wizytaid = Long.parseLong(br.readLine());
                    pom = pom2.szukajWizyta(wizytaid);

                    List<WizytaDto> lista = new ArrayList<>();


                    for(int i = 0; i < pom.size(); ++i)
                    {
                        WizytaDto pomwiz = new WizytaDto(pom.get(i).getId(),pom.get(i).getLekarz().getNazwisko(),pom.get(i).getPacjent().getImie(),
                                pom.get(i).getPacjent().getNazwisko(),pom.get(i).getData(),pom.get(i).getNotatka(),pom.get(i).getLeki().toString());
                        lista.add(pomwiz);
                    }

                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    bw.write(lista.toString());

                    break;
                }
                case 21:        //usuwanie lekarza
                {
                    LekarzeFunkcje baza = new LekarzeFunkcje();

                    Long id;

                    id = Long.parseLong(br.readLine());

                    try{
                        baza.usunLekarza(id);
                    }
                    catch(Exception e)
                    {
                        bw.write(0);
                        bw.flush();
                    }
                    bw.write(1);
                    bw.flush();
                    break;
                }
                case 22:        //usuwanie pacjenta
                {

                    PacjenciFunkcje baza = new PacjenciFunkcje();

                    Long id;

                    id = Long.parseLong(br.readLine());

                    try{
                        baza.usunPacjenta(id);
                    }
                    catch(Exception e)
                    {
                        bw.write(0);
                        bw.flush();
                        break;
                    }
                    bw.write(1);
                    bw.flush();
                    break;
                }
                case 23:        //usuwanie leku
                {
                    LekiFunkcje baza = new LekiFunkcje();

                    Long id;

                    id = Long.parseLong(br.readLine());

                    try{
                        baza.usunLek(id);
                    }
                    catch(Exception e)
                    {
                        bw.write(0);
                        bw.flush();
                        break;
                    }
                    bw.write(1);
                    bw.flush();
                    break;
                }
                case 24:        //szukanie leku po id
                {
                    LekiFunkcje pom2 = new LekiFunkcje();

                    List<Lek> pom = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    Long lekid;

                    lekid = Long.parseLong(br.readLine());
                    pom = pom2.szukajId(lekid);

                    List<LekDto> lista = new ArrayList<>();

                    for(int i = 0; i < pom.size(); ++i)
                    {
                        LekDto pomlek = new LekDto(pom.get(i).getId(),pom.get(i).getNazwa(),pom.get(i).getSklad());
                        lista.add(pomlek);
                    }
                    lista.sort(Comparator.comparing(LekDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    bw.write(lista.toString());

                    break;
                }
                case 25:        //szukanie pacjenta po id
                {
                    PacjenciFunkcje pom2 = new PacjenciFunkcje();

                    List<Pacjent> pom = new ArrayList<>();
                    ObjectMapper mapper = new ObjectMapper();
                    Long pacjentid;

                    pacjentid = Long.parseLong(br.readLine());
                    pom = pom2.szukajId(pacjentid);

                    List<PacjentDto> lista = new ArrayList<>();


                    for(int i = 0; i < pom.size(); ++i)
                    {
                        PacjentDto pompac = new PacjentDto(pom.get(i).getId(),pom.get(i).getImie(),pom.get(i).getNazwisko(), pom.get(i).getPlec(),pom.get(i).getLeki().toString());
                        lista.add(pompac);
                    }

                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    bw.write(lista.toString());

                    break;
                }
                case 28:        //szukanie listy lekow po id pacjenta/wizyty
                {
                    PacjenciFunkcje baza = new PacjenciFunkcje();
                    WizytaFunkcje baza2 = new WizytaFunkcje();
                    List<Lek> pom = new ArrayList<>();

                    ObjectMapper mapper = new ObjectMapper();
                    Long id;
                    int czypac;

                    czypac = br.read();
                    id = Long.parseLong(br.readLine());
                    if(czypac == 1)
                    {
                        Pacjent pacjent = baza.szukajId(id).get(0);
                        pom =  pacjent.getLeki();           //tutaj po pacjencie szukamy
                    }
                    else
                    {
                        Wizyta wizyta = baza2.szukajWizyta(id).get(0);
                        pom =  wizyta.getLeki();     //tutaj po wizycie szukamy
                    }

                    List<LekDto> lista = new ArrayList<>();

                    for(int i = 0; i < pom.size(); ++i)
                    {
                        LekDto pomlek = new LekDto(pom.get(i).getId(),pom.get(i).getNazwa(),pom.get(i).getSklad());
                        lista.add(pomlek);
                    }
                    lista.sort(Comparator.comparing(LekDto::getId));
                    JSONObject listaJSON = new JSONObject();

                    listaJSON.put("lista", mapper.writeValueAsString(lista));
                    bw.write(listaJSON.toString());
                    bw.flush();
                    bw.write(lista.toString());

                    break;
                }
            }
            bw.close();
            br.close();
            socket.close();
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
