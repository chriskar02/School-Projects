#include <iostream>
#include <iomanip>

using namespace std;


class ChessBoardArray {
protected:
    int *data;
    int members;
    int baseRow;
    unsigned numRows;
    unsigned loc(int i, int j) const throw(out_of_range) {
    int di = i - baseRow;
    int dj = j - baseRow;
    if(di<0 || di >= numRows || dj<0 || dj >= numRows) throw out_of_range("invalid index");
    if((di+dj)%2!=0) throw out_of_range("black");
    return (di*numRows + dj)/2;
    }

    class Row {
    public:
    Row(ChessBoardArray &a, int i) : chessBoardArray(a) , row(i) {}
    int & operator [] (int i) const {
    return chessBoardArray.select(row, i);
    }

    private:
        ChessBoardArray &chessBoardArray;
        int row;
    };

    class ConstRow {
    public:
    ConstRow(const ChessBoardArray &a, int i) : chessBoardArray(a), row(i) {}
    int operator [] (int i) const {
    return chessBoardArray.select(row, i);
    }

    private:
        const ChessBoardArray &chessBoardArray;
        int row;
    };

public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0) : baseRow(base), numRows(size) {
    members = size*size/2 + (size%2);
    data = new int[members];
    for(int i=0; i<members; i++) data[i] = 0;
    }


    ChessBoardArray(const ChessBoardArray &a) : data(new int[a.members]), baseRow(a.baseRow), numRows(a.numRows) {
    for(int i=0; i< a.members; i++) {
        data[i] = a.data[i];
        }
    }

    ~ChessBoardArray() {
    delete []data;
    }

    ChessBoardArray & operator = (const ChessBoardArray &a) {
    delete []data;
    baseRow = a.baseRow;
    numRows = a.numRows;
    members = a.members;
    data = new int[a.members];
    for(unsigned i=0; i< a.members; i++) {
            data[i] = 0;
            data[i] = a.data[i];
    }
    return *this;
    }

    int & select(int i, int j) {
    return data[loc(i,j)];
    }
    int select(int i, int j) const {
    return data[loc(i,j)];
    }

    const Row operator [] (int i) {
    return Row(*this, i);
    }
    const ConstRow operator [] (int i) const {
    return ConstRow(*this, i);
    }

    friend ostream & operator << (ostream &out, const ChessBoardArray &a) {

    for(int i=a.baseRow; i < (a.numRows + a.baseRow); ++i) {
        for(int j=a.baseRow; j < (a.numRows + a.baseRow); ++j) {
        if((i+j)%2!=0) {
        cout << setw(4) << "0";
        continue;
        }
        cout << setw(4) << a.data[a.loc(i,j)];
        }
        cout << endl;
    }
    }
};

int main() {
ChessBoardArray a(4, 1); // size 4x4, rows and columns numbered from 1
a[3][1] = 42;
a[4][4] = 17;
try { a[2][1] = 7; }
catch(out_of_range &e) { cout << "a[2][1] is black" << endl; }
try { cout << a[1][2] << endl; }
catch(out_of_range &e) { cout << "and so is a[1][2]" << endl; }
ChessBoardArray b(4,1);
b = a;
cout << b;
}





