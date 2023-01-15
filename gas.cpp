#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    struct street{
        int first,second;
        street(int a,int b):first(a),second(b){};
    };
    vector<street> *graph;
    int N;
public:
    Graph(int V) {
        N=V;
        graph = new vector<street>[N];
    }
    ~Graph() {
        delete [] graph;
    }
    vector<street> edges(int u)const{
        return graph[u];}
    void addEdge(int u, int v, int l) {
        graph[u].push_back(street(v,l));
        graph[v].push_back(street(u,l));
    }
    void help(int u, vector<bool> &current, int B, int &C, vector<int> &road,bool &found, vector<int> &trip)  {
        current[u] = 1;
        for (auto v: edges(u)) {
            if (v.second <= C){
            if (current[v.first] == 0) {
                if (B != v.first){
                    road.push_back(v.first);
                    trip.push_back(v.second);
                    help(v.first,current, B, C,road,found,trip);
                    if (found) return;
                }
                else {
                    road.push_back(v.first);
                    trip.push_back(v.second);
                    found = true;
                    return;
                }
            }
        }}
        current[u] = 1;
        road.pop_back();
        trip.pop_back();
    }
    void test(const int &A,const int &B,int fuel) {
        vector<int> road;
        vector<bool> status(N);
        for (int u = 0; u < N; ++u) {
            status[u] = 0;
        }
        bool found(false);
        int fills = 1,tank = fuel;
        vector<int> trip;
        road.push_back(A);
        help(A,status, B, fuel,road, found, trip);
        if (found) {
            for (int i = 0; i < trip.size(); i++){
                if (fuel < trip[i]) {//gemizo to tank me venzini
                    ++fills;
                    fuel = tank;
                }
                fuel -= trip[i];

            }
            cout << "POSSIBLE: " << fills << " fill(s),";
            for (int i = 0; i < road.size(); i++)
                if(road[i]!=-1)
                    cout<<" "<<road[i];
            cout<<endl;
        }
        else
            cout << "IMPOSSIBLE" << endl;

    }
};


int main() {
    int N, M, U, V, L, Q;
    cin >> N >> M;
    Graph graph(N);
    for (int i = 0; i < M; ++i) {
        cin >> U >> V >> L;
        graph.addEdge(U,V,L);
    }
    vector<int> q;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        int A,B,C;
        cin >> A;
        cin >> B;
        cin >> C;
        graph.test(A, B, C);
    }
}
