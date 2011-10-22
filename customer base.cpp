#include "utility.h"
#include <map>
using namespace std;

class RECORD
{
private:
    string key,name;
public:
    RECORD()
    {}

    RECORD(string k, string n)
    {
        key=k;
        name=n;
    }
    void SetKey(string k)
    {
        key=k;
    }
    void SetName(string n)
    {
        name=n;
    }
    string GetKey(void)
    {
        return key;
    }
    string GetName(void)
    {
        return name;
    }
    string GetRecord(void)
    {
        string record;
        record = key+"\t"+name;
        cout<<record;
        return record;
    }
};

ostream& operator<<(ostream& os, RECORD& obj) 
{ 
  obj.GetRecord();
  return os;
}


int main(void)
{
    // declaration of map

    // map<index field datatype,the record type> mapname
    map<string,RECORD> mymap;
    // setup iterator
    map<string,RECORD>::iterator iter;

     

    // add strings to map
    RECORD r1("Aa","Bob Smith");
    RECORD r2("Bb","John Ki");
    RECORD r3("Cc","Cat Stevens");


    // add strings to the map

    // mapname[index value] = record
    mymap["Aa"] = r1;
    mymap["Bb"] = r2;
    mymap["Cc"] = r3;
    

    // output map
    cout<<"Map output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        //(*pointer to iterator value).first is the key
        //pointer to iteraror value->second is the record
        cout<<(*iter).first << " is the key in the record " << iter->second << endl;
    }

    // add an element to the map
    RECORD r4("Dd","Doug Dee");
    // map[key value]
    mymap["Dd"] = r4;
    cout<<"Second output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        cout<<(*iter).first << " is the first characterin the word " << iter->second << endl;
    }

    //adding a third element

    RECORD r5("Cc","Zach Black");
     mymap["Cc"] = r5;

    cout << "third output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        cout<<(*iter).first << " is the first characterin the word " << iter->second << endl;
    }




    Pause();
    return 0;
}
