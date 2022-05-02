using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Player
{
        public static int  N;
        public static int  L;
        public static int E ;
        public static int [] exite;
        public static int [,] links;
         static void Main(string[] args)
    {
        string[] inputs;
        inputs = Console.ReadLine().Split(' ');
         N = int.Parse(inputs[0]); // the total number of nodes in the level, including the gateways
         L = int.Parse(inputs[1]); // the number of links
         E = int.Parse(inputs[2]); // the number of exit gateways
         exite= new int [N];
         links= new int [N,N];
        for (int i = 0; i < L; i++)
        {
            inputs = Console.ReadLine().Split(' ');
            int N1 = int.Parse(inputs[0]); // N1 and N2 defines a link between these nodes
            int N2 = int.Parse(inputs[1]);
            links[N1,N2]=1;
            links[N2,N1]=1;
            }
        for (int i = 0; i < E; i++)
        {
            int EI = int.Parse(Console.ReadLine()); // the index of a gateway node
            exite[EI]=1;
        }

        // game loop
        while (true)
        {
            int SI = int.Parse(Console.ReadLine()); // The index of the node on which the Skynet agent is positioned this turn
            bool con=firstcheack(SI);
            if(con==false){
                secondcheack();
            }
            // Write an action using Console.WriteLine()
            // To debug: Console.Error.WriteLine("Debug messages...");
           // Example: 0 1 are the indices of the nodes you wish to sever the link between
           // Console.WriteLine("0 1");
        }
    }
     
    public static bool firstcheack(int SI){
          int x = 0;
            int n1 = 0;
            int n2 = 0;
            
            for (int i = 0; i < N; i++) {
                if (exite[i]==1) {
                    if (links[i,SI]==1) { 
                        x = 1;
                        n1 = i;
                        n2 = SI;
                    }
                }
            }
            
           if (x==1) {
            Console.WriteLine(n1 + " " + n2);
           return true;
           }
           return false;
    }
    public static void secondcheack(){
        int n1=0;
        int n2=0;
        for (int i = 0; i < N; i++) {
                   if (exite[i]==1) 
                       for (int j = 0; j < N; j++)
                           if ((links[i,j])==1 ) { 
                               n1 = i;
                               n2 = j;
                           }
               }
           Console.WriteLine(n1 + " " + n2);
    }
}