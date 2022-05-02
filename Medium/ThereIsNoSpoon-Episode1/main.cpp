#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>
using namespace std;
int width,height;

class node{
    public:
    int name;
    int x=0,y=0;
    int links=0;
    int neighbours=0;
    int dlinks=0,ulinks=0,rlinks=0,llinks=0;
    int down=-1,up=-1,left=-1,right=-1;
    node(int wx, int wy, int wlinks){x=wx;y=wy;links=wlinks;name=wx+height*wy;}
    void show(){cerr<<"name="<<name<<" up="<<up<<" down="<<down<<" left="<<left<<" right="<<right<<endl;}
    string coords(){ostringstream ss;ss<<x<<" "<<y;return ss.str();}
    string coords(char naN,vector<node> nodes){
        int nN;
        switch(naN){
            case 'd':nN=down;break;
            case 'u':nN=up;break;
            case 'l':nN=left;break;
            case 'r':nN=right;break;
        }
        
        
        if(nN==-1) return "-1 -1";
        else
        {vector<node>::iterator it;
        it=find_if(nodes.begin(),nodes.end(),[nN](node vertex){return vertex.name==nN;});
        return it->coords();}
    }
};

vector<node> nodes;
vector<node>::iterator it;
/**
 * Don't let the machines win. You are humanity's last hope...
 **/
int main()
{int upN[31];for (auto& value : upN) value=-1;
    cin >> width; cin.ignore();
    cin >> height; cin.ignore();
    for (int y = 0; y < height; y++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        cerr<<line<<endl;
        int prev=-1;
        for (int x=0;x<width;x++)
         if(line[x]!='.'){
             node temp (x,y,(int)line[x]);
             //cerr<<"wstawiam "<<x<<" "<<y<<endl;
             if(prev==-1){prev=temp.name;temp.left=-1;}
             else {
                 temp.left=prev;temp.neighbours++;
                 it=find_if(nodes.begin(),nodes.end(),[prev](node& elem){return elem.name==prev;});
                 it->right=temp.name;
                 it->neighbours++;
                 prev=temp.name;
             }
             if(upN[x]==-1){upN[x]=temp.name;temp.up=-1;}
             else{temp.up=upN[x];temp.neighbours++;
                 int sasiad=upN[x];
                 it=find_if(nodes.begin(),nodes.end(),[sasiad](node& elem){return elem.name==sasiad;});
                 it->down=temp.name;
                 it->neighbours++;
                 upN[x]=temp.name;
             }
             
             nodes.push_back(temp);
             for (auto vertex : nodes) {cerr<<"x="<<x<<" ";vertex.show();}
         }
    }

for (auto vertex : nodes)
    cout<<vertex.coords()<<" "<<vertex.coords('r',nodes)<<" "<<vertex.coords('d',nodes)<<endl;
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    //cout << "0 0 1 0 0 1" << endl; // Three coordinates: a node, its right neighbor, its bottom neighbor
}