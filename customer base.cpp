#include "utility.h"

using namespace std;



map<string,string> mymap;

extern int LoadFile(fstream* file);

int main(void)
{

    
    // declaration of map

    // map<index field datatype,the record type> mapname
    
    // setup iterator
    map<string,string>::iterator iter;

    // Open file:
    fstream file;
    LoadFile(&file);

    // output map
    cout<<"Map output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        //(*pointer to iterator value).first is the key
        //pointer to iteraror value->second is the record
        cout<<(*iter).first << " is the key in the record " <<endl<< iter->second << endl;
    }

    /*
    // add an element to the map
    RECORD r4("Dd","Doug Dee");
    // map[key value]
    mymap["Dd"] = r4;
    cout<<"Second output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        cout<<(*iter).first << " is the key in the record " <<endl<< iter->second << endl;
    }

    //adding a third element

    RECORD r5("Cc","Zach Black");
     mymap["Cc"] = r5;

    cout << "third output: "<<endl;
    for (iter = mymap.begin(); iter != mymap.end(); ++iter)
    {
        cout<<(*iter).first << " is the key in the record " <<endl<< iter->second << endl;
    }
    */


    file.close();

    Pause();
    return 0;
}

/*
 LoadFile()
 Erick Veil
 10-22-11

*/
int LoadFile(fstream* file)
{
     //RECORD temp;
    int size=0;
     string temp_in,key;
     file->open(IOFILE,fstream::in);
     if (file->fail())
     {
         cout<<"\nFile read\\write failed: LoadFile()\n";
         exit(777);
     }
     while(!file->eof())
     {
         // one getline statement for each member of the structure
         getline(*file,temp_in);
         key = temp_in.substr(0,temp_in.find('\t'));
         mymap[key] = temp_in; 
         ++size;
     }
     return size;
}
