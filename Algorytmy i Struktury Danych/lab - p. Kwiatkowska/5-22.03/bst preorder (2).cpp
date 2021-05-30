#include <iostream>

using namespace std;

struct wezel{
    int klucz;
    wezel *lewy;
    wezel *prawy;
};

wezel *korzen = NULL;

int suma = 0;

void dodawanie(wezel *&korzen, int klucz){
    if(korzen == NULL){
        korzen = new wezel;
        korzen -> klucz = klucz;
        korzen -> lewy = NULL;
        korzen -> prawy = NULL;
    }
    else{
        if(klucz >= korzen->klucz) dodawanie(korzen->prawy, klucz);
        if(klucz < korzen->klucz) dodawanie(korzen->lewy, klucz);
    }
}

void preorder(wezel *korzen){
    if(korzen != NULL){
        cout<<korzen->klucz<<" ";
        preorder(korzen -> lewy);
        preorder(korzen -> prawy);
         if(korzen->lewy ==NULL && korzen->prawy ==NULL)
        {
        	suma= suma + korzen->klucz;
		}
    }
}

int main()
{
    int n, m;
    cout <<"Ile elementow ma miec drzewo?"<< endl;
    cin>>n;
    cout <<"Podaj "<<n<<" elementow :"<<endl;
    for(int i = 0; i < n; i++){
        cin>>m;
        dodawanie(korzen, m);

    }
    cout<<"BST w porzadku preoerder"<<endl;
    preorder(korzen);
    cout<<"Suma lisci "<<suma;

    return 0;
}
