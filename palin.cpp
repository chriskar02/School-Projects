#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {

    int N, c, k=0, x=0, count=0, pal=0;
    char a[20], b[20];
    float percent;

    cin >> N;
    cin.clear();


    for(int i=0; i<N; i++) {

        x=0;

        do {
            c = getchar();
            a[x] = c;
            x++;
        } while(c != '\n');

        if(x==1) {cout << "empty" << endl; goto end;}
        if(x>20) {cout << "error" << endl; goto end;}


        for(int j=0; j<x; j++) {

            b[j] = a[x-j];
        }

        if(a == b) {cout << "yes" << endl; pal++;}
        else {cout << "no" << endl;}

        end:;
        count++;
    }

    percent = pal/count*100;
    cout << setprecision(3) << percent << endl;


}
