#include <iostream>
#include <cstdio>
#include <cstring>
#include<bits/stdc++.h>
using namespace std;

int main() {
int i=0,j=0, k=0, l=0, o=0, space, extra, len=0, num[1000], leng[1000];
char c;
string line, word, words[1000];

c=getchar();
while(c!=EOF) {
line += c;
c=getchar();
}


stringstream iss(line);

while(iss >> word) {
    words[i] = word;
    i++;
}

while(l<i) {

while(true) {
len += words[l+j].length();
j++;
if((len + words[l+j].length()) > (60-j)) break;
if(words[l+j].length() == 0) break;
}
num[k] = j;
leng[k] = len;
k++;

l+=j;
j=0;
len=0;
}
k--;

for(int m=0; m<k; m++) {
space = ((60-leng[m])/(num[m]-1));
extra = ((60-leng[m])%(num[m]-1));

for(int n=0; n<num[m]; n++){
    cout << words[o+n];
    if(n<(num[m]-1)) {
        for(int p=0; p<space; p++) {
            cout << " ";
        }

    if((num[m]-n-1)<=extra) cout << " ";
    }
}
o+=num[m];
cout << endl;
}

cout << words[o];

for(int r=1; r<num[k]; r++) {
    cout << " " << words[o+r];
}
cout << endl;
}
