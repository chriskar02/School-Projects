#include <iostream>

using namespace std;

void change(int &x, int &y) {
int z = x;
x = y;
y = z;
}

int main() {

int N,x;
cin >> N;

int a[N][N],b[N][N], sumrow[N], sumcol[N], dia_1=0, dia_2=0, row=0, col=0;
bool check=true;

for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
        cin >> a[i][j];
        b[i][j] = a[i][j];
    }
}

for(int k=0; k<N; k++) {
for(int l=0; l<N; l++) {
    x= l+1;
    for(int m = k; m<N; m++) {
        for(int n = x; n<N; n++) {
            if(b[k][l] > b[m][n]) {
            change(b[k][l] , b[m][n]);
        }
    }
    x=0;
}
}
}

int o=0;
int p=0;

for(int c=0; c<N; c++) {
    for(int d=0;d<N;d++) {
        if(b[c][d] == o) {p++;}
        o++;
    }
}
if(p != (N*N)) {check = false;}


for(int e=0; e<N; e++){
    sumrow[e]=sumcol[e]=0;

    for(int f=0; f<N; f++){
    sumrow[e]+=a[e][f];
    sumcol[e]+=a[f][e];
    }

    if(sumrow[0] != sumrow[e]) {check = false;}
    if(sumcol[0] != sumcol[e]) {check = false;}
}

    for(int g=0; g<N;g++) {
        dia_1+=a[g][g];
        dia_2+=a[g][N-1-g];
    }

    if(dia_1 != dia_2) {check = false;}



if(check) {cout << "yes" << endl;}
else{cout << "no" << endl;}

}
