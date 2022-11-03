#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
# define INF 0x3f3f3f3
#include <climits>
using namespace std;
typedef pair<int, int> Pair;

struct Edge
{
    int weight;
    int src;
    int dest;

    Edge(int weight, int src, int dest)
    {
        this->weight = weight;
        this->src = src;
        this->dest = dest;
    }
};
class Union_Find
{
public:
    int size;
    vector<int> id;
    vector<int> sz;
    int numComponents;

    Union_Find(int k)
    {
        size = k;
        id.resize(k);
        for(int i = 0; i<size; i++)
        {
            id[i] = i;

        }
        sz.resize(k);
        numComponents = k;
    }

    int find(int u)
    {
        int root = u;
        while(root != id[root])
        {
            root = id[root];
        }

        while(u != root)
        {
            int next = id[u];
            id[u] = root;
            u = next;
        }

        return root;

    }

    void unify(int u, int v)
    {
        if(id[u] == id[v])
            return;
        int root1 = find(u);
        int root2 = find(v);
        int size1 = sz[u];
        int size2 = sz[v];

        if(size1 < size2 )
        {
            sz[root1] += sz[root2];
            id[root1] = root2;

        }
        else
        {
            sz[root2] += sz[root1];
            id[root2] = root1;

        }
        numComponents --;

    }



};

class Graph
{
public:
    int V;
    vector<vector<Pair>> adjList;
    vector<Edge> edgeList;

    Graph(int vertices)
    {
        V = vertices;
        adjList.resize(vertices + 1);

    }


    void addEdge(int source, int destination, int weight)
    {
        adjList[source].push_back(Pair(weight,destination));
        adjList[destination].push_back(Pair(weight,source));


    }



    void print_graph()
    {
        for(int vert = 0; vert < V; vert++)
        {
            cout << "Vertex " << vert << " has edge with \n";
            for(auto& dests : adjList[vert])
            {
                cout << dests.second << " with weight " << dests.first << endl;
            }
        }

    }


    void buildEdgeList()
    {
        for(int vert = 0; vert < V; vert++)
        {
            for(auto& dests : adjList[vert])
            {
                edgeList.push_back(Edge(dests.first, vert, dests.second));

            }


        }
    }
    void printEdgeList()
    {
        for(auto& edge : edgeList)
        {
            cout << "   Weight " << edge.weight << "   Source " << edge.src << "    Destination " << edge.dest << endl;


        }

    }


    void BFS(int src)
    {
        bool visited[V];
        for(int i =0; i < V; i++)
        {
            visited[i] = false;
        }
        visited[src] = true;
        queue<int> q;
        q.push(src);
        while(!q.empty())
        {
            int node = q.front();
            cout << "Visited " << node << endl;
            q.pop();
            for(auto& v : adjList[node])
            {
                if (visited[v.second] == false)
                {
                    q.push(v.second);
                    visited[v.second] = true;
                }
            }
        }

    }






    void DFS(int src)
    {
        bool visited[V];
        for(int i = 0; i < V ; i++)
        {
            visited[i] = false;
        }
        stack<int> s; //stos
        s.push(src);
        while( ! s.empty())
        {
            int node = s.top();
            s.pop();

            if(!visited[node])
            {
                cout << node << " ";
                visited[node] = true;
            }
            for(auto& v : adjList[node])
            {
                if(visited[v.second] == false)
                {
                    s.push(v.second);
                }
            }
        }






    }










    void sortEdgeList()
    {


        sort(edgeList.begin(), edgeList.end(), [](const Edge& lhs, const Edge& rhs)
        {
            return lhs.weight < rhs.weight;
        });

    }






    void prim()
    {
        vector<int> MST(V,-1);
        priority_queue< Pair, vector <Pair>, greater<Pair> > pq;
        int source = 0;
        int ans = 0;
        vector<int> key(V,INF);
        vector<bool> inMst(V,false);
        pq.push(make_pair(0,source));
        key[source] = 0;
        while(!pq.empty())
        {
            int node = pq.top().second;
            cout<<" NODE " << node << " " << " WEIGHT " << pq.top().first;
            pq.pop();
            if(inMst[node] == true)
            {
                continue;
            }
            inMst[node] = true;
            for(auto& v : adjList[node])
            {
                int vert = v.second;
                int weight = v.first;
                if(!inMst[vert] && weight < key[vert])
                {
                    key[vert] = weight;
                    ans += weight;
                    pq.push(make_pair(key[vert],vert));
                    MST[vert] = node;
                }

            }
        }
        for (int i = 1; i < V + 1; i++)
            cout << MST[i] << " - " << i <<" \n";
        cout << ans << endl;

    }




    void rozwiazanie_zadania(int k)
    {
        buildEdgeList();
        sortEdgeList();
        int edgeNum = edgeList.size();
        Union_Find uf(edgeNum);
        int ans = 0;
        priority_queue<int> pq;
        int super_city = 0;
        vector<Edge> Mst;
        for(auto& edge : edgeList)
        {
            int weight = edge.weight;
            int source = edge.src;
            int destination = edge.dest;
            pq.push(weight);
            if(uf.find(source) != uf.find(destination))
            {
                uf.unify(source,destination);
                ans += weight;
                Mst.push_back(edge);

            }
        }
        while(ans > k){
            int d = pq.top();
            pq.pop();
            ans = ans - d + 1;
            super_city++;
        }
        cout<< "Zachowane drogi : "<<endl;
        for(auto& e: Mst){
            cout << '(' << e.src << ',' << e.dest << ',' << e.weight << ')' << endl;
        }
        cout << "Liczba super drog : "<<super_city;

    }





    void dijkstra(int source)
    {
        vector<int> distances(V,INT_MAX);
        priority_queue< Pair, vector <Pair>, greater<Pair> > pq;
        pq.push(Pair(0, source));
        distances[source] = 0;
        while(!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();
            for(auto& e : adjList[u])
            {
                int weight = e.first;
                int v = e.second;
                if(distances[v] > distances[u] + weight)
                {
                    distances[v] = distances[u] + weight;
                    pq.push(Pair(distances[v],v));
                }


            }



        }
        for(int i = 0; i<V; i++)
        {
            cout << i << " - > " << distances[i] << endl;
        }



    }





    void bellman_ford(int source)
    {
        buildEdgeList();
        vector<int> distance(V,INT_MAX);
        distance[source] = 0;
        for(int i = 0; i < V - 1; i++)
        {
            for(int j = 0; j < edgeList.size(); j++)
            {
                Edge e = edgeList[j];
                int weight = e.weight;
                int source = e.src;
                int destination = e.dest;
                if(distance[source] != INT_MAX && distance[destination] > distance[source] + weight)
                {
                    distance[destination] = distance[source] + weight;
                }
            }

        }

        for(int i = 0; i < V; i++)
        {
            cout << i << " - > " << distance[i] << endl;
        }
    }
























};

int main()
{

    int V = 3;
    int k = 6;
    Graph g(V);

   g.addEdge(1,2,5);
   g.addEdge(2,3,4);
   g.addEdge(1,3,3);
   g.rozwiazanie_zadania(k);
    return 0;
}
