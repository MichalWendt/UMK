#include <iostream>

using namespace std;

int query(int a, int b, int *w, int M){
    int va = M+a;
    int vb = M+b;
    int mini = 101;

    int wyn = w[va];
    if(va!=vb){
        wyn = wyn + w[vb];
    }
    while(va/2 != vb/2){
        if(va%2 == 0){
            if(w[va+1]>mini){
                  mini = w[va+1];
            }

        }
        if(vb%2 == 1){
         if(w[vb-1]>mini){
                  mini = w[vb-1];
            }
    }
    return wyn;
}
}

int main()
{
    int M;
    int a, b;
    cin>>M;

    int w[2*M];
    for(int i=0; i<2*M; i++){
        w[i]=0;
    }
    for(int i=M; i<2*M; i++){
        cin>>w[i];
    }
   int v=M-1;

   /* while(v!=0){
        w[v]=w[v*2]+w[(v*2)+1];
        v=v-1;
    }*/
    while(v!=0){
        if(w[2*v]<w[(2*v)+1]){
            w[v]=w[2*v];
        }
        else{
            w[v]=w[(2*v)+1]
        }
        v=v-1;
    }
    for(int i=1; i<2*M; i++){
        cout<<w[i]<<" ";
    }
    cout<<endl<<"Przedzial ";
    cin>>a>>b;
    cout<<"Minimum"<<query(a, b, w, M);
    return 0;
}
