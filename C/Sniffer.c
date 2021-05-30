/* Michal Wendt - sniffer */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/ether.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/* Struktury do przechowywania danych o pakietach */

struct wlasny_RIP
{
    unsigned char polecenie;    /* Polecenie */
    unsigned char wersja;       /* Wersja protokolu */
    unsigned short nieuzywany1;
	unsigned short rodzina;     /* Identyfikator rodziny adresow (AFI) */
	unsigned short nieuzywany2;
    unsigned char ip_1;         /* Adres IP*/
	unsigned char ip_2;
	unsigned char ip_3;
	unsigned char ip_4;
	unsigned int nieuzywany3;
	unsigned int nieuzywany4;
	unsigned int metryka;       /* calkowity koszt dotarcia pakietu do odbiorcy */
};

struct wlasny_DNS
{
    unsigned short id;          /* identyfikator */
    unsigned char qr :1;        /* zapyatnie = 1 || odpowiedz = 0 */
	unsigned char opcode :4;    /* typ zapytania (standardowe,odwrotne,zadanie stanu serwera, 3-15 = rezerwacja na przyszlosc */
    unsigned char aa :1;        /* wiarygodnosc */
    unsigned char tc :1;        /* czy obcieta wiadomosc */
    unsigned char rd :1;        /* czy rekursja */
    unsigned char ra :1;        /* rekursja wymagana */
	unsigned char z :3;         /* rezerwacja */
	unsigned char rcode :4;     /* kod odpowiedzi */
    unsigned short q_count;     /* liczba wpisow pytan */
    unsigned short ancount;     /* liczba pozycji odpowiedzi */
    unsigned short nscount;     /* liczba wpisow uprawnien */
    unsigned short adcount;     /* liczba dodatkowych rekordow */
};

struct wlasny_DHCP
{
    unsigned char operacja;     /* Operacja zapytania lub odpowiedzi */
	unsigned char sprzet;       /* Typ sprzetu */
	unsigned char dlugosc;      /* Dlugosc adresu sprzetowego */
	unsigned char skoki;        /* Liczba skokow */
    unsigned int xid;           /* Identyfikator transakcji */
	unsigned short sekundy;     /* Liczba sekund */
	unsigned short flagi;       /* Pole flag */
	unsigned char klient_1;     /* Adres klienta */
	unsigned char klient_2;
	unsigned char klient_3;
	unsigned char klient_4;
	unsigned char przydzielony_1;   /* Adres przydzielony */
	unsigned char przydzielony_2;
	unsigned char przydzielony_3;
	unsigned char przydzielony_4;
	unsigned char serwer_1;         /* Adres serwera */
	unsigned char serwer_2;
	unsigned char serwer_3;
	unsigned char serwer_4;
    unsigned char router_1;         /* Adres routera */
	unsigned char router_2;
	unsigned char router_3;
	unsigned char router_4;
    unsigned char q;                /* Adress MAC klienta */
	unsigned char w;
	unsigned char e;
	unsigned char r;
	unsigned char t;
	unsigned char y;
	unsigned char u;
	unsigned char i;
	unsigned char serwer[64];       /* Nazwa serwera */
	unsigned char startowy[128];    /* Plik startowy */
	unsigned char producent;        /* Opcje producenta */
};

struct wlasny_ICMP4
{
	unsigned char typ;          /* Typ protokolu */
	unsigned char kod;          /* Kod protokolu */
	unsigned char checksum;     /* Suma kontrolna */
	unsigned char id;           /* Identyfikator */
	unsigned char seq;          /* Sekwencja */
};

struct wlasny_ICMPv6
{
    unsigned char typ;          /* Typ protokolu */
    unsigned char kod;          /* Kod protokolu */
    unsigned char checksum;     /* Suma kontrolna */
};

struct wlasny_IGMP
{
	unsigned char wersja :4;    /* Wersja protokolu */
	unsigned char typ :4;       /* Typ protokolu */
	unsigned char nieuzywany5;
	unsigned char checksum;      /* Suma kontrolna */
	unsigned char ip_1;         /* Adres IP*/
	unsigned char ip_2;
	unsigned char ip_3;
	unsigned char ip_4;
};

static inline struct sockaddr_in Okresl_adres(u_int32_t _adres) /* Struktura okreslajaca adresy */
{
    struct sockaddr_in adres;
    memset(&adres, 0, sizeof(adres));
    adres.sin_addr.s_addr = _adres;
    return adres;
}

int arp = 0,ipv4 = 0 ,ipv6 = 0 ,inny = 0;   /* Liczniki ilosci przechwyconych protokolow */

/* ____________________________ Sekcja pakietow ____________________________*/
void wypisz(char *buff , int rozmiar)       /* Wypisujemy zawartosc protokolu */
{
    int i;

    printf(" ################ Przechwycony tekst ################\n");       /* Wypisujemy informacje */
    for(i = 0 ; i < rozmiar ; i++)
    {
        printf("%c",(unsigned char)buff[i]);
    }
	printf("\n ####################################################\n");
}

void wypisz_rip(char *buff, int rozmiar)    /* Dla protokolu bram wewnetrznych */
{
	struct wlasny_RIP *rip = (struct wlasny_RIP *) buff;    /* Tworzymy odpowiednie struktury */
	union
	{
        u_int8_t ip[4];
        u_int32_t ip2;
    } rip_ip;
    rip_ip.ip[0] = rip->ip_1;       /* Ustawiamy adres */
	rip_ip.ip[1] = rip->ip_2;
	rip_ip.ip[2] = rip->ip_3;
	rip_ip.ip[3] = rip->ip_4;
    printf(" ######################## RIP #######################\n");       /* Wypisujemy informacje */
    printf(" | Adres : %s\n", inet_ntoa(Okresl_adres(rip_ip.ip2).sin_addr));
    printf(" | Polecenie : %u\n", ntohs(rip->polecenie));
    printf(" | Wersja : %u\n",ntohs(rip->wersja));
	printf(" | Identyfikator rodziny adresow (AFI) : %u\n",ntohs(rip->rodzina));
	printf(" | Metryka : %u\n", ntohs(rip->metryka));
	printf(" ####################################################\n");
}

void wypisz_dns(char *buff, int rozmiar)        /* Dla protokolu systemu nazw domen */
{
	struct wlasny_DNS *dns = (struct wlasny_DNS *) buff;    /* Tworzymy odpowiednie struktury */
	printf(" ######################## DNS #######################\n");       /* Wypisujemy informacje */
    printf(" | Identyfikator : %u\n", ntohs(dns->id));
    printf(" | Rodzaj : %s\n", dns->qr == 0 ? "pytanie" : "odpowiedz");
    printf(" | Rodzaj zapytania : %u\n", ntohs(dns->opcode));
    printf(" | Autorytatywna odpowiedz : %u\n", dns->aa);
	printf(" | Zarezerwowana : %u\n", dns->z);
    printf(" | Ucieta wiadomosc : %u\n", dns->tc);
    printf(" | Rekursja dostepna: %u\n", dns->rd);
    printf(" | Rekursja wymagana : %u\n", dns->ra);
    printf(" | Kod odpowiedzi : %u\n", ntohs(dns->rcode));
    printf(" | Liczba zapytan : %u\n", ntohs(dns->q_count));
    printf(" | Liczba odpowiedzi : %u\n", ntohs(dns->ancount));
    printf(" | Liczba wpisow uprawnien : %u\n", ntohs(dns->nscount));
    printf(" | Liczba dodatkowych rekordow : %u\n", ntohs(dns->adcount));
    printf(" ####################################################\n");
}

void wypisz_dhcp(char *buff, int rozmiar)   /* Dla protokolu dynamicznego konfigurowania hostow */
{
	struct wlasny_DHCP *dhcp = (struct wlasny_DHCP *) buff;
	union
	{
        u_int8_t ip[4];
        u_int32_t ip2;
    } dhcp_ip;
    printf(" ####################### DHCP #######################\n");       /* Wypisujemy informacje */
    printf(" | Adres routera : %s\n", inet_ntoa(Okresl_adres(dhcp_ip.ip2).sin_addr));
	printf(" | Adres MAC klienta : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X:%.2X:%.2X", ntohs(dhcp->q), ntohs(dhcp->w), ntohs(dhcp->e), ntohs(dhcp->r), ntohs(dhcp->t), ntohs(dhcp->y), ntohs(dhcp->u), ntohs(dhcp->i));
	printf(" | Nazwa serwera : %s\n", dhcp->serwer);
	printf(" | Plik startowy : %s\n", dhcp->startowy);
	printf(" | Opcje producenta : %u\n", ntohl(dhcp->producent));
    printf(" | Operacja : %s\n", ntohs(dhcp->operacja) == 1 ? "BOOTREQUEST" : (ntohs(dhcp->operacja) == 2 ? "BOOTREPLY" : "nieznana"));
    printf(" | Typ sprzetu : %u\n",ntohs(dhcp->sprzet));
	printf(" | Dlugosc adresu sprzetowego : %u\n",ntohs(dhcp->dlugosc));
	printf(" | Liczba skokow : %u\n",ntohs(dhcp->skoki));
	printf(" | Identyfikator transakcji : %u\n",ntohs(dhcp->xid));
	printf(" | Liczba sekund : %u\n",ntohs(dhcp->sekundy));
	printf(" | Flaga BROADCAST : %s\n",(ntohs(dhcp->flagi) & 1) ? "TAK" : "NIE");
	dhcp_ip.ip[0] = dhcp->klient_1;
	dhcp_ip.ip[1] = dhcp->klient_2;
	dhcp_ip.ip[2] = dhcp->klient_3;
	dhcp_ip.ip[3] = dhcp->klient_4;
	printf(" | Adres klienta : %s\n", inet_ntoa(Okresl_adres(dhcp_ip.ip2).sin_addr));
	dhcp_ip.ip[0] = dhcp->przydzielony_1;
	dhcp_ip.ip[1] = dhcp->przydzielony_2;
	dhcp_ip.ip[2] = dhcp->przydzielony_3;
	dhcp_ip.ip[3] = dhcp->przydzielony_4;
	printf(" | Adres przydzielony : %s\n", inet_ntoa(Okresl_adres(dhcp_ip.ip2).sin_addr));
	dhcp_ip.ip[0] = dhcp->serwer_1;
	dhcp_ip.ip[1] = dhcp->serwer_2;
	dhcp_ip.ip[2] = dhcp->serwer_3;
	dhcp_ip.ip[3] = dhcp->serwer_4;
	printf(" | Adres serwera : %s\n", inet_ntoa(Okresl_adres(dhcp_ip.ip2).sin_addr));
	dhcp_ip.ip[0] = dhcp->router_1;
	dhcp_ip.ip[1] = dhcp->router_2;
	dhcp_ip.ip[2] = dhcp->router_3;
	dhcp_ip.ip[3] = dhcp->router_4;
	printf(" ####################################################\n");
}

void obsluga_protokolow(char *buff, int port_zrodlo, int port_docelowy, int rozmiar)
{
    int port;
	if(port_docelowy > port_zrodlo)
    {
		port = port_zrodlo;
	}
	else
	{
		port = port_docelowy;
	}
	printf(" ################ Obsluga protokolow ################\n"); /* Wypisujemy informacje */
    switch (port)
    {
        case 7:
            printf(" ___ Echo ___\n");
            wypisz(buff, rozmiar);
            break;
        case 20:
            printf(" ___ FTP - przesyl danych ___\n");
            break;
        case 21:
            printf(" ___ FTP - przesyl polecen ___\n");
            break;
        case 22:
            printf(" ___ SSH ___\n");
            break;
        case 23:
            printf(" ___ Telnet ___\n");
            wypisz(buff, rozmiar);
            break;
		case 25:
            printf(" ___ SMTP ___\n");
            break;
        case 53:
            printf(" ___ DNS ___\n");
            wypisz_dns(buff, rozmiar);
            break;
        case 67:
            printf(" ___ DHCP - serwer ___\n");
			wypisz_dhcp(buff, rozmiar);
            break;
        case 68:
            printf(" ___ DHCP - klient ___\n");
			wypisz_dhcp(buff, rozmiar);
            break;
        case 69:
            printf(" ___ TFTP ___\n");
            break;
        case 70:
            printf(" ___ Gopher ___\n");
            break;
        case 79:
            printf(" ___ Finger ___\n");
			wypisz(buff, rozmiar);
            break;
        case 80:
            printf(" ___ HTTP ___\n");
            wypisz(buff, rozmiar);
            break;
		case 110:
            printf(" ___ POP3 ___\n");
            break;
		case 119:
            printf(" ___ NNTP/USENET ___\n");
            break;
		case 123:
            printf(" ___ NTP ___\n");
            break;
		case 137:
            printf(" ___ SMB ___\n");
            break;
		case 138:
            printf(" ___ SMB ___\n");
            break;
		case 139:
            printf(" ___ SMB ___\n");
            break;
		case 143:
            printf(" ___ IMAP ___\n");
            break;
		case 161:
            printf(" ___ SNMP ___\n");
            break;
		case 179:
            printf(" ___ BGP ___\n");
            break;
        case 220:
            printf(" ___ IMAP3 ___\n");
            break;
		case 389:
            printf(" ___ LDAP ___\n");
            break;
		case 433:
            printf(" ___ NNSP ___\n");
            break;
        case 443:
            printf(" ___ HTTPS ___\n");
			break;
        case 514:
            printf(" ___ Syslog ___\n");
			break;
		case 520:
            printf(" ___ RIP ___\n");
			wypisz_rip(buff, rozmiar);
            break;
		case 546:
            printf(" ___ DHCPv6 ___\n");
			wypisz_dhcp(buff, rozmiar);
            break;
        case 547:
            printf(" ___ DHCPv6 ___\n");
            wypisz_dhcp(buff, rozmiar);
			break;
		case 563:
            printf(" ___ TLS ___\n");
            break;
		case 587:
            printf(" ___ SMTP ___\n");
            break;
        case 636:
            printf(" ___ LDAPS ___\n");
            break;
        case 873:
            printf(" ___ Rsync ___\n");
            break;
        case 995:
            printf(" ___ POP3S ___\n");
            break;
		case 2049:
            printf(" ___ NFS ___\n");
            break;
		case 2427:
            printf(" ___ MGCP ___\n");
            break;
        case 3306:
            printf(" ___ MySQL ___\n");
            break;
        case 5432:
            printf(" ___ PostgreSQL ___\n");
            break;
        default:
            printf(" ___ Protokol o numerze: %d nieokreslony ___\n", port);
    }
}

/* ____________________________Sekcja pakietow____________________________ */
void prot_icmp4(char *buff, int rozmiar)          /* Dla protokolow komunikatów kontrolnych */
{
    struct wlasny_ICMP4 *icmp = (struct wlasny_ICMP4 *) buff;    /* Tworzymy odpowiednie struktury */
    printf(" ################### Pakiet ICMP4 ###################\n");   /* Wypisujemy informacje */
    printf(" | ID : %d\n",ntohs(icmp->id));
    printf(" | Typ : %d\n",(unsigned int)(icmp->typ));
    printf(" | Kod : %d\n", (unsigned int)(icmp->kod));
    printf(" | Sekwencja : %d\n",ntohs(icmp->seq));
    printf(" | Suma kontrolna : %d\n", ntohs(icmp->checksum));
    printf(" ####################################################\n");
}

void prot_icmp6(char *buff, int rozmiar)          /* Dla protokolow komunikatów kontrolnych IPv6 */
{
    struct wlasny_ICMPv6 *icmp = (struct wlasny_ICMPv6 *) buff;    /* Tworzymy odpowiednie struktury */
    printf(" ################### Pakiet ICMP6 ###################\n");     /* Wypisujemy informacje */
    printf(" | Typ : %d\n",(unsigned int)(icmp->typ));
    printf(" | Kod : %d\n", (unsigned int)(icmp->kod));
    printf(" | Suma kontrolna : %d\n", ntohs(icmp->checksum));
    printf(" ####################################################\n");
}

void prot_igmp(char *buff, int rozmiar)           /* Dla protokolow zarzadzania grup */
{
    struct wlasny_IGMP *igmp = (struct wlasny_IGMP *) buff;     /* Tworzymy odpowiednie struktury */
    union {
        u_int8_t ip[4];
        u_int32_t ip2;
    } igmp_ip;
    igmp_ip.ip[0] = igmp->ip_1;
	igmp_ip.ip[1] = igmp->ip_2;
	igmp_ip.ip[2] = igmp->ip_3;
	igmp_ip.ip[3] = igmp->ip_4;
    printf(" #################### Pakiet IGMP ###################\n");    /* Wypisujemy informacje */
    printf(" | Typ : %d\n", ntohs(igmp->typ));
    printf(" | Wersja : %d\n",ntohs(igmp->wersja));
    printf(" | Adres : %s\n", inet_ntoa(Okresl_adres(igmp_ip.ip2).sin_addr));
    printf(" | Suma kontrolna : %d\n", ntohs(igmp->checksum));
	printf(" ####################################################\n");
}

void prot_udp(char *buff, int rozmiar)            /* Dla protokolow pakietow uzykownika */
{
    struct udphdr *udp = (struct udphdr*) buff;    /* Tworzymy odpowiednie struktury */
    printf(" #################### Pakiet UDP ####################\n");     /* Wypisujemy informacje */
    printf(" | Dlugosc naglowka : %d\n" , ntohs(udp->len));
    printf(" | Port zrodlowy: %u\n" , ntohs(udp->source));
    printf(" | Port docelowy : %u\n" , ntohs(udp->dest));
    printf(" | Suma kontorlna : %d\n" , ntohs(udp->check));
    printf(" ####################################################\n");
	obsluga_protokolow(buff + sizeof(struct udphdr), ntohs(udp->source), ntohs(udp->dest), rozmiar);
}

void prot_tcp(char *buff, int rozmiar)            /* Dla protokolow kontroli transmisji */
{
    struct tcphdr *tcp = (struct tcphdr*) buff;    /* Tworzymy odpowiednie struktury */
    printf(" #################### Pakiet TCP ####################\n");     /* Wypisujemy informacje */
	printf(" | Dlugosc naglowka : %d DWORDS albo %d bajtow\n",(unsigned int)tcp->doff, (unsigned int)tcp->doff * 4);
	printf(" | Rozmiar okna : %d\n", ntohs(tcp->window));
    printf(" | Wskaznik priorytetu : %d\n", tcp->urg_ptr);
    printf(" | Numer sekwencyjny : %u\n", ntohl(tcp->seq));
    printf(" | Numer przyznany : %u\n", ntohl(tcp->ack_seq));
    printf(" | Flagi:\n");
    printf("  - priorytetu : %d\n", (unsigned int)tcp->urg);
    printf("  - przyznania : %d\n", (unsigned int)tcp->ack);
    printf("  - wysylania : %d\n", (unsigned int)tcp->psh);
    printf("  - resetu : %d\n", (unsigned int)tcp->rst);
    printf("  - synchronizacji : %d\n", (unsigned int)tcp->syn);
    printf("  - konca : %d\n", (unsigned int)tcp->fin);
    printf(" | Port zrodlowy: %u\n", ntohs(tcp->source));
    printf(" | Port docelowy : %u\n", ntohs(tcp->dest));
    printf(" | Suma kontorlna : %d\n", ntohs(tcp->check));
    printf(" ####################################################\n");
	obsluga_protokolow(buff + (4 * tcp->doff), ntohs(tcp->source), ntohs(tcp->dest), rozmiar - (4 * tcp->doff));
}

/* ____________________________ Sekcja glownych protokolow ____________________________ */
void ipv4_info(char *buff, int rozmiar)            /* Dla protokolow IPv4 */
{
    struct iphdr *ip4 = (struct iphdr *) buff;      /* Tworzymy odpowiednie struktury */
    printf(" ####################### IPv4 #######################\n");       /* Wypisujemy informacje */
    printf(" | Wersja IP : %d\n", (unsigned int)ip4->version);
	printf(" | Protokol : %d\n", (unsigned int)ip4->protocol);
	printf(" | Dlugosc naglowka : %d DWORDS albo %d bajtow\n", ((unsigned int)(ip4->ihl)), ((unsigned int)(ip4->ihl)) * 4);
	printf(" | Typ uslugi : %d\n", (unsigned int)ip4->tos);
	printf(" | Identyfikator : %d\n", ntohs(ip4->id));
    printf(" | Odsuniecie fragmentu:  %#x\n", ntohs(ip4->frag_off) & IP_OFFMASK);
	printf(" | Max czas zycia : %d\n", (unsigned int)ip4->ttl);
    printf(" | Max rozmiar pakietu : %d bajtow\n", ntohs(ip4->tot_len));
	printf(" | Flagi:\n");
    printf(" | RF: %u ", (ntohs(ip4->frag_off) & IP_RF) != 0);
    printf(" DF: %u ", (ntohs(ip4->frag_off) & IP_DF) != 0);
    printf(" MF: %u\n", (ntohs(ip4->frag_off) & IP_MF) != 0);
    printf(" | Zrodlowe IP : %s\n", inet_ntoa(Okresl_adres(ip4->saddr).sin_addr));
    printf(" | Docelowe IP : %s\n", inet_ntoa(Okresl_adres(ip4->daddr).sin_addr));
    printf(" | Suma kontorlna : %d\n", ntohs(ip4->check));
    printf(" ####################################################\n");
	switch (ip4->protocol)      /* Okreslamy rodzaj protokolu */
	{
        case IPPROTO_TCP:
            prot_tcp(buff + (ip4->ihl * 4), ntohs(ip4->tot_len) - ip4->ihl * 4);
            break;
        case IPPROTO_UDP:
            prot_udp(buff + (ip4->ihl * 4), ntohs(ip4->tot_len) - ip4->ihl * 4);
            break;
        case IPPROTO_ICMP:
            prot_icmp4(buff + (ip4->ihl * 4), rozmiar);
            break;
		case 2:
            prot_igmp(buff + (ip4->ihl * 4), rozmiar);
            break;
        default:
            printf("ERROR: Pakiet o numerze : %d nieokreslony lub nie istnieje\n", ip4->protocol);
    }
}

void ipv6_info(char *buff, int rozmiar)        /* Dla protokolow IPv6 */
{
    struct ip6_hdr *ip6 = (struct ip6_hdr *) (buff);    /* Tworzymy odpowiednie struktury */
	char wiadomosc[INET6_ADDRSTRLEN];
    printf(" ####################### IPv6 #######################\n");       /* Wypisujemy informacje */
    printf(" | Wersja IP: %u\n", (ntohl(ip6->ip6_flow) & 0xf0000000) >> 28);
    printf(" | Klasa ruchu : %u\n", (ntohl(ip6->ip6_flow) & 0xff00000) >> 20);
    printf(" | Etykieta przeplywu : %u\n", ntohl(ip6->ip6_flow) & 0xfffff);
    printf(" | Dlugosc danych : %u\n", ntohs(ip6->ip6_plen));
    printf(" | Nastepny naglowek: %u\n", ip6->ip6_nxt);
    printf(" | Limit HOP : %u\n", ip6->ip6_hops);
    inet_ntop(AF_INET6, &(ip6->ip6_src), wiadomosc, INET6_ADDRSTRLEN);
    printf(" | Zrodlowe IP: %s\n", wiadomosc);
    inet_ntop(AF_INET6, &(ip6->ip6_dst), wiadomosc, INET6_ADDRSTRLEN);
    printf(" | Docelowe IP : %s\n", wiadomosc);
    printf(" ####################################################\n");
    switch (ip6->ip6_nxt)
    {
        case IPPROTO_TCP:
            prot_tcp(buff + sizeof(struct ip6_hdr), ntohs(ip6->ip6_plen));
            break;
        case IPPROTO_UDP:
            prot_udp(buff + sizeof(struct ip6_hdr), ntohs(ip6->ip6_plen));
            break;
        case IPPROTO_ICMPV6:
            prot_icmp6(buff + sizeof(struct ip6_hdr), rozmiar);
            break;
        default:
            printf("ERROR: Pakiet o numerze : %d nieokreslony lub nie istnieje\n", ip6->ip6_nxt);
    }
}

void arp_info(char *buff, int rozmiar)       /* Dla protokolow ARP */
{
	struct ether_arp *arp = (struct ether_arp *) buff;  /* Tworzymy odpowiednie struktury */
	int i;
	union
	{
        u_int8_t ip[4];
        u_int32_t ip2;
    } arp_ip;
	for (i = 0; i < 4; i++)             /* Przeliczamy adres nadawcy */
    {
        arp_ip.ip[i] = arp->arp_spa[i];
    }
    printf(" ######################## ARP #######################\n");        /* Wypisujemy informacje */
    printf(" | Typ sprzetu : %u\n", ntohs(arp->arp_hrd));
    printf(" | Typ protokolu : 0x%04x\n", ntohs(arp->arp_pro));
    printf(" | Dlugosc adresu sprzetowego : %u\n", arp->arp_hln);
    printf(" | Dlugosc adresu protokolu : %u\n", arp->arp_pln);
    printf(" | Operacja : %u\n", ntohs(arp->arp_op));
    printf(" | Adres sprzetu nadawcy : %s\n", ether_ntoa((struct ether_addr *) arp->arp_sha));
    printf(" | Adres protokolu nadawcy : %s\n", inet_ntoa(Okresl_adres(arp_ip.ip2).sin_addr));
    printf(" | Adres sprzetu odbiorcy : %s\n", ether_ntoa((struct ether_addr *) arp->arp_tha));
    for (i = 0; i < 4; i++)            /* Przeliczamy adres odbiorcy */
    {
         arp_ip.ip[i] = arp->arp_tpa[i];
    }
    printf(" | Adres protokolu odbiorcy : %s\n", inet_ntoa(Okresl_adres(arp_ip.ip2).sin_addr));
    printf(" ####################################################\n");
}

void okresl_naglowek(char *buff, int rozmiar)   /* Okreslanie typu przechwyconego pakietu */
{
    struct ethhdr *naglowek = (struct ethhdr*) buff;   /* Pobieramy informacje o typie */

    printf("\n\n\nMam nowy pakiet!\n");
	printf(" ____________________________________________________\n"); /* Wypisujemy fizyczne adresy kart sieciowych adresata i odbiorcy pakietu */
	printf(" | Adres MAC odbiorcy(docelowy) : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X |\n", naglowek->h_dest[0] , naglowek->h_dest[1] , naglowek->h_dest[2] , naglowek->h_dest[3] , naglowek->h_dest[4] , naglowek->h_dest[5] );
	printf(" | Adres MAC nadawcy(zrodlowy)  : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X |\n", naglowek->h_source[0] , naglowek->h_source[1] , naglowek->h_source[2] , naglowek->h_source[3] , naglowek->h_source[4] , naglowek->h_source[5] );
	printf(" |__________________________________________________|\n");

	switch (ntohs(naglowek->h_proto))   /* Sprawdzamy co przechwycilismy */
	{
	    case ETH_P_ARP:             /* Jezeli jest to ARP */
	        arp++;
            arp_info(buff + sizeof(struct ethhdr), rozmiar);      /* Wypisujemy ARP */
            break;
        case ETH_P_IP:              /* Jezeli jest to IPv4 */
            ipv4++;
            ipv4_info(buff + sizeof(struct ethhdr), rozmiar);      /* Wypisujemy IPv4 */
            break;
        case ETH_P_IPV6:            /* Jezeli jest to IPv6 */
            ipv6++;
            ipv6_info(buff + sizeof(struct ethhdr), rozmiar);      /* Wypisujemy IPv6 */
            break;
        default:                    /* Domyslnie nie znamy typu */
            inny++;
            printf("ERROR: Nie udalo sie okreslic typu EtherType: %d\n", ntohs(naglowek->h_proto));
    }
    printf("\nLacznie przechwycilem: ARP: %d, IPv4: %d, IPV6: %d, Inne: %d\n",arp,ipv4,ipv6,inny);  /* Wypisujemy ilosc pakietow zgodnie z ich typem */
    printf("Przechodze do kolejnego pakietu\n");        /* Konczymy przechwytywanie tego pakietu */
    printf("Aby zakonczyc prosze nacisnac Ctrl^C\n");
}

int main(int argc, char **argv)
{
    int rozmiar_adresu;
    int sniff;          /* Gniazdo */
    int pakiet;
    struct ifreq ifr ;
    struct sockaddr adres_sieci;
    if(argc != 2)
    {
        printf("ERROR: Niewlasciwa liczba argumentow!\n");          /* Obslugujemy bledna liczbe argumentow */
        printf("Prosze uzyc: [nazwa pliku].c <karta sieciowa>\n");
        return -1;
    }
    char *buff = ( char *) malloc(1 << 16);     /* Alokujemy miejsce na przechwycone dane */

    if(buff == NULL)   /* Obslugujemy blad alokacji */
	{
		printf("ERROR: Blad funckji malloc()!\n");
		return -1;
	}

	sniff = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL));   /* Tworzymy surowe gniazdo */
    if(sniff == -1)
    {
        printf("ERROR: Nie udalo sie utworzyc surowego gniazda!\n");      /* Obslugujemy blad gniazda */
        return -1;
    }
    printf("Utworzono surowe gniazdo!\n");

    strncpy((char*)ifr.ifr_name, argv[1] , IFNAMSIZ);   /* Ustawiamy karte sieciowa na promisc */
    ifr.ifr_flags |= IFF_PROMISC;
    if(ioctl(sniff, SIOCSIFFLAGS, &ifr ) != 0 )
    {
        printf("ERROR: Blad przejscia w tryb nasluchu!\n");        /* Obslugujemy blad nasluchu */
        return -1;
    }

    printf("Zaczynam weszyc!\n");
    while(1)    /* Dopoki otrzymujemy pakiety */
    {
        rozmiar_adresu = sizeof adres_sieci;

        pakiet = recvfrom(sniff , buff , 1 << 16 , 0 , &adres_sieci , (socklen_t*)&rozmiar_adresu);   /* Przechwytujemy pakiet i pobieramy wiadomosc z soketu */
        if(pakiet > 0)
        {
            okresl_naglowek(buff , pakiet);     /* Sprawdzamy inforamcje o przechwyconym pakiecie */
        }
        else if(pakiet < 0)    /* Sprawdzamy czy przechwycony pakiet nie jest pusty */
        {
            printf("ERROR: Nie udalo sie przechwycic pakietu\n");   /* Obslugujemy blad przechwytywania */
            printf("Koncze weszyc\n");   /* Konczymy przechwytywanie */
            return 1;
        }
    }
    free(buff);     /* Czyscimy zaalokowana pamiec */
    close(sniff);   /* Zamykamy gniazdo */
    return 0;
}
