/*Michal Wendt - smok wawelski*/
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class wisla
{
    public:
	int ilosc_wody = 1000000;
};

class smok
{
    public:
	int pojemnosc_brzucha = 70000;
	string kolor_skory = "zielony";
	string wielkosc = "wielki";
	string dlugosc_ogona = "10 metrow";
	string stan = "zywy";
	int ilosc_zebow = 102;
	int zjedz(string kto, int waga);
	int czyobudzony;
	string umrzyj()
	{
	    cout << zarycz() << endl;
	    cout << "Smok: ";
        return "UMIERAM!!!";
	}
	string zarycz()
	{
	    cout << "Smok: ";
	    return "RYYYYYYYYYYK";
	}
	string pojaw_sie()
	{
	    cout << "Smok: ";
		return "Pojawiam sie";
	}
	int pij(int lyk_smoka, wisla *wisla1);
};

class rycerz
{
	public:
			string sprobuj_pokonac_smoka()
			{
			    cout << "Rycerz: ";
			    return "Walcz ze mna smoku!!";
			}
			string smiej_sie(string kto)
			{
			    cout << "Rycerz_" << kto << ": ";
			    if(kto == "1")
                {
                    return  "Patrzcie go, smialek sie znalazl";
                }
			    if(kto == "2")
                {
                    return  "Nie wiesz, ze smoka nikt nie jest w stanie pokonac?";
                }
			    if(kto == "3")
                {
                    return  "Zabic juz wielu wybitnych wojakow! Jak mozesz sie z nimi rownac?";
                }
			}
			string umrzyj()
			{
			    cout << "Rycerz: ";
			    return "Umieram za krola!!!";
			}
};

class owca
{
    public:
    int waga = 100;
	string umrzyj()
	{
	    cout << "Owca: ";
	    return "be....";
	}
	string becz()
	{
	    cout << "Owca: ";
	    return "beeeee";
	}
};

class szewczyk
{
    public:
	int napchaj_owce(owca owca1)
	{
	    cout << "Szewczyk: Owca napchana siarka" << endl;
	    return owca1.waga = owca1.waga + 50;
	}
	string zabij_owce()
	{
	    cout << "Szewczyk: ";
	    return "Owca zabita";
	}
	string podloz_owce()
	{
	    cout << "Szewczyk: ";
	    return "Owca podlozna pod grote";
	}
	string przemow()
	{
	    cout << "Szewczyk: ";
	    return "Panie moj, mysle, ze jestem w stanie pokonac dreczacego Was smoka";
	}
	string poklon_sie()
	{
	    cout << "Szewczyk: ";
	    return "Klaniam sie krolu";
	}
};

class wiesniak
{
    public:
	string umrzyj()
	{
	    cout << "Wiesniak: ";
	    return "Aaaaaaaaaaaaaa to boli!!!";
	}
	string wystrasz_sie()
	{
	    cout << "Wiesniak: ";
	    return "Aaaaaaaaaaaaaa to smok!!!";
	}
	string uciekaj()
	{
	    cout << "Wiesniak: ";
	    return "Uciekam";
	}
};

class krowa
{
    public:
    int waga;
	string mucz()
	{
	    cout << "Krowa: ";
	    return "muuuuu";
	}
	int ilosc_bydla = 100;
};

class krol
{
	public:
		string rzadz()
		{
		    cout << "Krol: ";
			return "Rzadze";
		}
		string zgodz_sie()
		{
		    cout << "Krol: ";
		    return "Dobrze, szewczyku. Pokonaj smoka, a zostaniesz sowicie nagrodzony";
		}
};

int smok::zjedz(string kto, int waga)
{
	    rycerz rycerz1;
		if(kto == "krowa")
		{
		    cout << "Smok zjadl: " << waga << "kg krow" << endl;
			return pojemnosc_brzucha = pojemnosc_brzucha - waga;
		}
		if(kto == "owca")
        {
            stan = "spragniony";
            return pojemnosc_brzucha = pojemnosc_brzucha - waga;
        }
        if(kto == "rycerz")
		{
		    cout << rycerz1.umrzyj() << endl;
			return pojemnosc_brzucha = pojemnosc_brzucha - waga;
		}
}

int smok::pij(int lyk_smoka, wisla *wisla1)
{
    cout << "Smok wypil: " << lyk_smoka << " litrow wody na lyk" << endl;
    wisla1->ilosc_wody = wisla1->ilosc_wody - lyk_smoka;
    return pojemnosc_brzucha = pojemnosc_brzucha - lyk_smoka;
}

 class narrator
{
    public:
    string opowiadaj(int moment)
    {
        cout << "Narrator: ";
        switch(moment)
        {
            case 1:
            return "Dawno temu, gdy polskimi ziemiami rzadzil krol Krak";

            case 2:
            return "W Krakowie pojawil sie smok";

            case 3:
            return "Smok zadomowil sie w jamie pod zamkiem i zadal, aby raz w tygodniu skladano mu ofiare w postaci krowy. Jezeli nie spelniono jego zachcianki, porywal ludzi";

            case 4:
            return "Na mieszkancow Krakowa padl blady strach, jednak znalazlo sie kilku smialkow, ktorzy twierdzili, ze zdolaja pokonac smoka.";

            case 5:
            return "Zarowno krol, jak i poddani stracili juz nadzieje na ratunek";

            case 6:
            return "Co tydzien stada bydla bolesnie sie kurczyly, gdyz smok wymagal zawsze najdorodniejszych sztuk. Martwiono sie, co bedzie, gdy pozre juz wszystkie krowy.";

            case 7:
            return "Gdy wydawalo sie, ze wszystko juz stracone i lud Krakowa czeka zaglada, na dworze Kraka pojawil sie ubogi szewczyk. ";

            case 8:
            return "W krolewskiej sali rozbrzmialy smiechy rycerzy.";

            case 9:
            return "Szewczyk odszedl, obmyslajac swoj plan. Niebawem wszystko mial juz przygotowane";

            case 10:
            return "Najciszej jak tylko potrafil zakradl sie do samego wejscia";

            case 11:
            return "Wkrotce z groty wyszedl smok, zwabiony zapachem swiezego miesa i dostrzegajac owce, natychmiast ja pozarl";

            case 12:
            return "Siarka ukryta w zwierzeciu od razu zaczela dzialac, powodujac u smoka ogromne pragnienie.";

            case 13:
            return "Smok rzucil sie w kierunku Wisly";

            case 14:
            return "I wtedy nagle rozlegl sie ogromny huk. Smok wypil tak duzo wody, ze po prostu pekl. ";

            case 15:
            return "Pomyslowy chlopiec zostal bohaterem calego miasta, a krol sowicie go wynagrodzil.";

            case 16:
            return "W Krakowie zas do dzis, u stop Wawelu, mozna zobaczyc Smocza Jame i ziejaca ogniem figure wawelskiego smoka, upamietniajaca bohaterski czyn szewczyka.";

            case 17:
            return "Smok wstal dzis wczesniej";

            case 18:
            return "Smok byl nienajedzony wiec pozarl tez przypadkowego wiesniaka";

            case 19:
            return "I tak kolejny dzien minal";
        }
    }
};

int main()
{
    srand(time(NULL));
    int czymu;
    int czybe;
    int ile_krow;
    int lyk_smoka;
    int aktualna;
    string kto;

    narrator narr1;
	krol krol1;
    smok smok1;
    rycerz rycerz1;
    rycerz rycerz2;
    rycerz rycerz3;
    krowa krowa1;
    szewczyk szewczyk1;
    owca owca1;
    wiesniak wiesniak1;
    wisla *wisla1;

    cout << narr1.opowiadaj(1) << endl;
    cout << krol1.rzadz() << endl;
    cout << narr1.opowiadaj(2) << endl;
    cout << smok1.pojaw_sie() << endl;
    cout << "specyfikacja smoka: " << endl;
    cout << "dlugosc ogona: " << smok1.dlugosc_ogona << endl;
    cout << "ilosc zebow: " << smok1.ilosc_zebow << endl;
    cout << "kolor skory: " << smok1.kolor_skory << endl;
    cout << "pojemnosc brzucha: " << smok1.pojemnosc_brzucha << " litrow" << endl;
    cout << "wielkosc: " << smok1.wielkosc << endl;
    cout << narr1.opowiadaj(3) << endl;
    cout << narr1.opowiadaj(4) << endl;
    cout << rycerz1.sprobuj_pokonac_smoka() << endl;
    cout << smok1.zarycz() << endl;
    kto = "rycerz";
    smok1.zjedz(kto, 100);
    cout << narr1.opowiadaj(5) << endl;
    kto = "krowa";
    cout << narr1.opowiadaj(6) << endl;
    while(smok1.stan == "zywy")
    {
        smok1.pojemnosc_brzucha = smok1.pojemnosc_brzucha + 1000;
        if(czymu = (rand()%2))
        {
            cout << krowa1.mucz() << endl;
        }
        if(czybe = (rand()%2))
        {
            cout << owca1.becz() << endl;
        }
        krowa1.waga = ((rand()%250) + 700);
        ile_krow = ((rand()%5) + 1);
        smok1.zjedz(kto, krowa1.waga * ile_krow);
        krowa1.ilosc_bydla = krowa1.ilosc_bydla - ile_krow;
        cout << "Pozostalo: " << krowa1.ilosc_bydla << " krow" << endl;
        if(smok1.czyobudzony = (rand()%2))
        {
            cout << narr1.opowiadaj(17) << endl;
            cout << wiesniak1.wystrasz_sie() << endl;
            cout << wiesniak1.uciekaj() << endl;
            if(krowa1.waga < 900)
            {
                cout << narr1.opowiadaj(18) << endl;
                cout << wiesniak1.umrzyj() << endl;
            }
        }
        if(krowa1.ilosc_bydla < 10)
        {
            cout << narr1.opowiadaj(7) << endl;
            cout << szewczyk1.poklon_sie() << endl;
            cout << szewczyk1.przemow() << endl;
            cout << narr1.opowiadaj(8) << endl;
            cout << rycerz2.smiej_sie("1") << endl;
            cout << rycerz3.smiej_sie("2") << endl;
            cout << rycerz2.smiej_sie("3") << endl;
            cout << krol1.zgodz_sie() << endl;
            cout << szewczyk1.poklon_sie() << endl;
            cout << narr1.opowiadaj(9) << endl;
            cout << szewczyk1.zabij_owce() << endl;
            cout << owca1.umrzyj() << endl;
            owca1.waga = szewczyk1.napchaj_owce(owca1);
            cout << narr1.opowiadaj(10) << endl;
            cout << szewczyk1.podloz_owce() << endl;
            cout << narr1.opowiadaj(11) << endl;
            kto = "owca";
            smok1.zjedz(kto, owca1.waga);
            cout << narr1.opowiadaj(12) << endl;
            smok1.stan = "spragniony";
            cout << narr1.opowiadaj(13) << endl;
            cout << smok1.zarycz() << endl;
            while(smok1.stan == "spragniony")
            {
                lyk_smoka = ((rand()%1000) + 550);
                smok1.pij(lyk_smoka, wisla1);
                if(wisla1->ilosc_wody < -1000000)
                {
                    cout << "Smok wypil cala wisle!!!" << endl;
                    cout << "Lud Kraka zginal!!!" << endl;
                    return -1;
                }
                if(smok1.pojemnosc_brzucha < 0)
                {
                    cout << narr1.opowiadaj(14) << endl;
                    cout << smok1.umrzyj() << endl;
                    break;
                }
            }
        }
        cout << narr1.opowiadaj(19) << endl;
    }
    cout << narr1.opowiadaj(15) << endl;
    cout << narr1.opowiadaj(16) << endl;
	return 0;
}
