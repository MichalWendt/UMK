section .data           ; sekcja komunikatow programu oraz ich dlugosci
PodajLiczbe     db      "Podaj liczbe N: ", 0xa
PodajLiczbeLen equ $ - PodajLiczbe
PoprWynik       db      "Liczba pentagonalna dla N wynosi: ", 0xa
PoprWynikLen equ $ - PoprWynik
ZleWejscie      db      "Nie podano prawidlowej liczby ", 0xa
ZleWejscieLen equ $ - ZleWejscie
ZleWyjscie      db      "Wynik jest niepoprawny ", 0xa
ZleWyjscieLen equ $ -   ZleWyjscie

SECTION .bss
pom1    RESQ    1       ; rezerwujemy miejsce na zmienne
pom2    RESQ    2
i       RESQ    1
wynik	RESB    24
liczba  RESB    1
doub    RESD    1

SECTION .text
global  _start

_start:         ; glowna czesc programu

; Zapytanie uzytkownika o liczbe
    mov     rdx, PodajLiczbeLen ; dlugosc wiadomosci poczatkowej
    mov     rcx, PodajLiczbe    ; przekazanie wiadomosci do wyswietlenia
    mov     rbx, 1              ; ustawienie deskryptora
    mov     rax, 4              ; wypisanie na ekran
    int 80h                     ; wywolanie jadra

; Funkcja wczytujaca napis
    mov     rdx, 12         ; ilosc bajtow do przeczytania
    mov     rcx, liczba     ; przestrzen zarezerwowana na pobrane dane(buffor)
    mov     rbx, 2          ; ustawienie deskryptora
    mov     rax, 3          ; pobranie z konsoli
    int     80h             ; wywolanie jadra

; Konwersja napisu na liczbe typu long
	mov qword [i], 0
	mov rsi, 0
iterate:                ; poczatek iteracji
	cmp byte [liczba + rsi + 1], 0
	je iterated         ; skok do poczatku iteracji
	mov rax, [i]
	imul rax, 10        ; mnozenie zmiennej przez 10
	mov [i], rax
	movzx rax, byte[liczba + rsi]

	cmp rax, 48         ; porownanie cyfry z dolnym zakresem ASCII
	jl FunkZleWejscie   ; skok w przypadku zbyt malej cyfry na wejsciu
	cmp rax, 58         ; porownanie cyfry z gornym zakresem ASCII
	jg FunkZleWejscie   ; skok w przypadku zbyt duzej cyfry na wejsciu
	sub rax, 48         ; odejmowanie liczb
	add [i], rax      ; dodawanie liczb
	inc rsi
	jmp iterate         ; skok do poczatku iteracji
iterated:               ; koniec iteracji

; Walidacja liczby poprzez ograniczenie zakresu
	mov rax, [i]      ; zapisanie liczby w pamieci
	cmp rax , 1
	jl FunkZleWejscie   ; skok w przypadku zbyt malej liczby
	cmp rax , 99999
	jg FunkZleWejscie   ; skok w przypadku zbyt duzej liczby

; Pierwszy sposob obliczenia piramidalnych liczb pentagonalnych
    mov qword[pom1], 0
	mov rsi, 0

pentaloop:              ; poczatek petli
	cmp rsi, [i]      ; porownanie zmiennych
	jg endloop          ; skok do konca petli
	mov rax, rsi
	imul rax,  rsi      ; mnozenie zmiennych
	imul rax, 3         ; mnozenie zmiennej przez 3
	sub rax , rsi       ; odejmowanie
	sar rax, 1

	add qword[pom1], rax    ; dodawanie
	inc rsi             ; inkrementacja o 1
	jmp pentaloop       ; powrot do poczatku petli
endloop:                ; zakonczenie petli

; Drugi sposob obliczenia piramidalnych liczb pentagonalnych
    mov rax,[i]
	mov rsi, rax
	mov rdi, rax
	inc rdi,            ; inkrementacja o 1
	imul rax, rsi       ; mnozenie zmiennych
	imul rax, rdi
	sar rax, 1
	mov qword[pom2], rax

; Walidacja wynikow i ewentualne wyswietlenie komunikatu bledu
	cmp [pom1], rax     ; porownanie wartosci wynikow
	jne FunkZleWyjscie  ; ewentualny skok do zakonczenia z bledem

; Konwersja liczby typu long na napis mozliwy do wyswietlenia
	mov rax, [pom1]
	mov dword[doub], 0  ; przeniesienie 0 do dword
	mov rdi, wynik      ; przeniesienie wyniku do pamieci
	add rdi, 24         ; dodanie 24
	mov rdx, 0
decToStringLoop:        ; poczatek petli
	mov rbx, 10
	div rbx             ; podzielenie
	add rdx, 48         ; dodanie 48 (zmiana znaku ASCII)
	mov byte[rdi], dl
	dec rdi             ; dekrementacja o 1
	inc dword[doub]     ; inkrementacja o 1
	mov rdx, 0          ;
	cmp  rax, 0         ; porownanie wartosci z 0
	jne decToStringLoop ; skok na poczatek petli
	inc rdi             ; inkrementacja o 1

; Wyswietlenie informacji o poprawnym wyniku
	mov rdx, PoprWynikLen   ; dlugosc wiadomosci o poprawnym wyniku
    mov rcx, PoprWynik  ; przekazanie wiadomosci do wyswietlenia
	mov rbx, 1          ; ustawienie deskryptora
	mov rax, 4          ; wypisanie na ekran
	int 80h             ; wywolanie jadra

; Wypisanie wartosci wyniku na standardowe wyjscie
    mov rdx, [doub]     ; dlugosc wyniku
    mov rcx, rdi        ; przekazanie wyniku do wyswietlenia
    mov rbx, 1          ; ustawienie deskryptora
    mov rax, 4          ; wypisanie na ekran
    int 80h             ; wywolanie jadra

; Zakonczenie programu
exit:
	mov rbx, 0          ; zwrocenie kodu powodzenia
    mov rax, 1          ; zakonczenie programu
	int 80h             ; wywolanie jadra

; Wyswietlenie inforamcji o bledzie obliczen oraz zakonczenie programu
FunkZleWyjscie:
	mov rdx, ZleWyjscieLen  ; dlugosc wiadomosci bledu
    mov rcx, ZleWyjscie     ; przekazanie wiadomosci do wyswietlenia
	mov rbx, 1              ; ustawienie deskryptora
	mov rax, 4              ; wypisanie na ekran
	int 80h                 ; wywolanie jadra

	mov rbx, -1         ; zwrocenie kodu bledu
    mov rax, 1          ; zakonczenie programu
	int 80h             ; wywolanie jadra

; Wyswietlenie inforamcji o blednie prowadzonej liczbie oraz zakonczenie programu
FunkZleWejscie:
    mov rdx, ZleWejscieLen  ; dlugosc wiadomosci bledu
    mov rcx, ZleWejscie     ; przekazanie wiadomosci do wyswietlenia
    mov rbx, 1              ; ustawienie deskryptora
    mov rax, 4              ; wypisanie na ekran
    int 0x80                ; wywolanie jadra

    mov     rbx, -1     ; zwrocenie kodu bledu
    mov     rax, 1      ; zakonczenie programu
    int     80h         ; wywolanie jadra
