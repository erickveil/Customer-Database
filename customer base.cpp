#include "utility.h"
#include <map>
using namespace std;


int main(void)
{
    // declaration of map

    // map<index field datatype,the record type> mapname
    map<char,string> mymap;
    // setup iterator
    map<char,string>::iterator iter;

     

    // add strings to map
    string s1 = "This";
    string s2 = "is";
    string s3 = "an";
    string s4 = "example";
    string s5 = "string";

    // add strings to the map

    // mapname[index value] = record
    mymap[s1[0]] = s1;
    mymap[s2[0]] = s2;
    mymap[s3[0]] = s3;
    mymap[s4[0]] = s4;
    mymap[s5[0]] = s5;

    // output map
    cout<<"Map output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        //(*pointer to iterator value).first is the key
        //pointer to iteraror value->second is the record
        cout<<(*iter).first << " is the first characterin the word " << iter->second << endl;
    }

    // add an element to the map
    string s6 = "test";
    mymap[s6[0]] = s6;
    cout<<"Second output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        cout<<(*iter).first << " is the first characterin the word " << iter->second << endl;
    }

    //adding a third element

    string s7 = "sample";
    mymap[s7[0]] = s7;

    cout << "third output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        cout<<(*iter).first << " is the first characterin the word " << iter->second << endl;
    }




    Pause();
    return 0;
}
