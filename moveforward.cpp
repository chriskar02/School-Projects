#include <iostream>
using namespace std;

class list {
public:
    list();
    bool empty();
    int size();
    void add(int k, int x);
    int get (int k);
    void remove(int k);
    int searchMF(int x);

private:
    long long int data[999999];
    int top;
    int pos;
};

list::list() {
top=0;
}

bool list::empty() {
return top == 0;
}

int list::size() {
return top;
}

void list::add(int k, int x) {
for(int i=0; i<k; i++) {
    data[top-i+1] = data[top-i];
}
data[top-k+1]=x;
top++;
}

int list::get(int k) {
return data[top-k];
}

void list::remove(int k) {
top--;

for(int i=k; i>1; i--) {
    data[top-i+1] = data[top-i+2];
}

}

int list::searchMF(int x) {
pos = 0;

do {
    pos++;
} while((list::get(pos) != x)&&(pos!=(top+1)));

if(pos == (top+1)) pos=0;

if(pos > 1) {
    list::remove(pos);
    list::add(1, x);
}

return pos;

}

int main() {
list l;
int N, K, X, M;
long long int sum=0;

cin >> N;

for(int i=0; i<N; i++) {
    cin >> K;
    cin >> X;
    l.add(K,X);
}

cin >> M;

for(int i=0; i<M; i++) {
    cin >> X;
    sum+=l.searchMF(X);
}

cout << sum << endl;

}
