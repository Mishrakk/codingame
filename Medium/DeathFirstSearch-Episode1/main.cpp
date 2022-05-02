#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>
#include <sstream>
using namespace std;

int IMAX=numeric_limits<int>::max();
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 struct vertex{
     int name;
     vector<int> adj;
     int dist;
     string color;
     int parent;
     bool visited;
     vertex(int s){name=s;}
     vertex(int s,int x){name=s; adj.push_back(x);}
 };
 

map<int, vertex *> graf;
vector<int> gateways; 
void dodajKrawedz(int N1, int N2)
{//cerr<<"N1 "<<N1<<" N2 "<<N2<<endl;
if(graf.find(N1)==graf.end())graf[N1]=new vertex(N1,N2);
else graf[N1]->adj.push_back(N2);

if(graf.find(N2)==graf.end()) graf[N2]=new vertex(N2,N1);
else graf[N2]->adj.push_back(N1);
}

void usunKrawedz(int N1,int N2)
{
int ile=graf[N1]->adj.size();    
 for(int i=0;i<ile;i++)
 if(graf[N1]->adj[i]==N2){graf[N1]->adj.erase(graf[N1]->adj.begin()+i);break;}

ile=graf[N2]->adj.size();    
 for(int i=0;i<ile;i++)
 if(graf[N2]->adj[i]==N1){graf[N2]->adj.erase(graf[N2]->adj.begin()+i);break;}
}

void bfs(int source){
    for(auto ver:graf)
    {
    ver.second->dist=IMAX;
    ver.second->parent=IMAX;
    ver.second->visited=false;
    }
    
    vector<vertex*> queue;
    graf[source]->dist=0;
    graf[source]->visited=true;
    
    queue.push_back(graf[source]);
    while(!queue.empty())
    {
        int sr=queue[0]->name;
        int d=queue[0]->dist;
        for(auto neigh: graf[sr]->adj)
        {
            if(!graf[neigh]->visited)
            {
            graf[neigh]->visited=true;
            graf[neigh]->dist=d+1;
            graf[neigh]->parent=sr;
            queue.push_back(graf[neigh]);
            }
        }
        queue.erase(queue.begin());
    }
    
}

void sciezka(int source, int target,vector<pair<int,int>>& sciezka)
{
    int obecny=target;
    int i=0;
    while(1)
    {
    //cerr<<graf[obecny]->name<<" "<<graf[obecny]->parent<<endl;
    //cerr<<"wkladam:"<<graf[obecny]->name<<" "<<graf[obecny]->adj.size()<<endl;
    sciezka.push_back(make_pair(graf[obecny]->name,graf[obecny]->adj.size()));
    if(graf[obecny]->parent==IMAX) {break;}
    else {obecny=graf[obecny]->parent;}
    }
    /*do
    {
    sciezka.push_back(make_pair(graf[obecny]->name,graf[obecny]->adj.size()));
    obecny=graf[obecny]->parent;
    }while(graf[obecny]->parent=!IMAX);
    sciezka.push_back(make_pair(graf[source]->name,graf[source]->adj.size()));
    */
}

int main()
{
    int N; // the total number of nodes in the level, including the gateways
    int L; // the number of links
    int E; // the number of exit gateways
    cin >> N >> L >> E; cin.ignore();
    for (int i = 0; i < L; i++) {
        int N1; // N1 and N2 defines a link between these nodes
        int N2;
        cin >> N1 >> N2; cin.ignore();
        dodajKrawedz(N1,N2);
    }
    //wyglad
    //cerr<<"N="<<N<<endl;
    /*for (int i=0;i<N;i++)
    {cerr<<"ver="<<i<<" sasiedzi:";
    for (int j=0;j<graf[i]->adj.size();j++) cerr<<" "<<graf[i]->adj[j];
    cerr<<endl;
    }*/
    
    
    for (int i = 0; i < E; i++) {
        int EI; // the index of a gateway node
        cin >> EI; cin.ignore();
        gateways.push_back(EI);
        //cerr<<"gate:"<<EI<<endl;
    }
//cerr<<"vertext="<<graf[2]->name<<"odl="<<graf[2]->dist<<endl;

    // game loop
    while (1) {
        int SI; // The index of the node on which the Skynet agent is positioned this turn
        cin >> SI; cin.ignore();
        bfs(SI);
        cerr<<"vertext="<<graf[gateways[0]]->name<<"odl="<<graf[gateways[0]]->dist<<endl;
        
        int sas=IMAX;//sasiedzi
        string przerwij="";
        int distA=IMAX;
        int u1,u2;
        for (auto gates:gateways)
        {
        vector<pair<int,int>> sc;
        sciezka(SI,gates,sc);
        int pozycja=0;
        cerr<<"sciezka:"<<sc.size()<<endl;
        for(auto scI:sc)cerr<<" "<<scI.first;
        cerr<<endl;
        for(auto scI:sc)
        {
            //if (distA>graf[scI.first]->dist)
            if (sc.size()<distA && sc.size()>1)
            {
            if(1==1 || scI.second<sas)
            {
            sas=scI.second;
            ostringstream pr;
            u1=scI.first;
                if(scI.first!=SI){
                u2=graf[scI.first]->parent;    
                }
                else{//cerr<<"poz="<<pozycja<<endl;
                pozycja==0?u2=sc[pozycja+1].first:u2=sc[pozycja-1].first;
                }
            
            pr<<u1<<" "<<u2;
            przerwij=pr.str();
            }
            //cerr<<""
            //distA=graf[scI.first]->dist;
            distA=sc.size();
            }
        pozycja++;
        }
        }
        cerr<<distA<<" "<<przerwij;
        usunKrawedz(u1,u2);
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        cout<<przerwij<<endl;
        //cout << "0 1" << endl; // Example: 0 1 are the indices of the nodes you wish to sever the link between
    }
}