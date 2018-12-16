#include<bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<b;i++)

string to_string(int a)
{
      string ret;
      while(a)
      {
            int d = a%10;
            char ch = '0'+d;
            ret = ch + ret;
            a/=10;
      }
      return ret;
}

void init_airplanes()
{
      fstream fout("airplanes.txt");
      string companies[] = {"Kingfisher","Indian Airlines","SpiceJet","Jet Airways","Etihad Airways"};
      string cities[] = {"Delhi","Kolkata","Guwahati","Indore","Mumbai","Chennai","Hyderabad"};
      int limit = 10;
      int id = 9;
      FOR(i,0,limit)
      {
            id++;
            int r = rand()%5;
            string put = companies[r];
            put += "\nAirbus 777";
            put += "\nARL0" + to_string(id);
            put += "\n" + to_string(6+i) + ":30";
            put += "\n" + to_string(7+i) + ":15";
            r = rand()%7;
            put += "\n" + cities[r];
            put += "\n0";
            put += "\n0";
            put += "\n";
            fout<<put<<endl;
            cout<<put<<endl;
      }
      fout.close();
}

int main()
{
      init_airplanes();
      return 0;
}
