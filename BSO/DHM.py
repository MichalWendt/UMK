    P = 71
    M = 7

    x = 5
    A = mod(M^x,P))

    y = 12
    B = mod(M^y,P))

    sx = mod(B^x,P))

    sy = mod(A^y,P))

    print('Klucz prywatny dla osoby A to: %d'%(sx))
    print('Klucz prywatny dla osoby B to: %d'%(sy))
    #Jezeli klucze sa równe to algorytm zakoñczy³ siê powodzeniem

p=71;
m=7;
x=5;
y=12;
var("A","B","K1","K2");
#obliczamy A oraz B
A= mod(m^x,p);
B= mod(m^y,p);
#wymieniamy sie sie kluczami A i B
K1= mod(B^x,p);
K2= mod(A^y,p);
#sprawdzamy czy wynik poprawny K1 = K2
print("Klucz K1 jest równy K2")
print(K1 == K2);
print("Klucz tajny K");
print(K1);
