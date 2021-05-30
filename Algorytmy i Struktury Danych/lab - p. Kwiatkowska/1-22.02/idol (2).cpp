#include <iostream>
#include <math.h>

using namespace std;

int main(){
	int n,m,idol;
	int licz=0;
	cin>>n;
	cin>>m;
	int t[m][2];
	for(int i=0;i<m;i++){
		for(int j=0;j<2;j++){
			cin>>t[i][j];
		}
	}
	idol=t[0][1];
	for(int i=0;i<m;i++){
		for(int j=0;j<2;j++){
			if(idol==t[i][0]){
				idol=t[i][1];
			}
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<2;j++){
			if(idol==t[i][0]){
				cout<<"Brak idola";
				return 0;
			}
			else if(t[i][j]==t[i][1]){
				if(idol==t[i][j]){
					licz++;
				}
			}
		}
	}
	if(licz==n-1){
		cout<<idol;
	}
	else{
		cout<<"Brak idola";
	}
	return 0;
}
