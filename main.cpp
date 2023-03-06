#include<iostream>
#include<stdio.h>
#include<string>
#include <vector>
#include "Dothrak_English_Dictionary.h"
using namespace std;
int main(int argc, char *argv[])
{
    //File operations and necessary declarations
    ifstream input1(argv[1]);
    ofstream myFile(argv[2]);
    Dothrak_English_Dictionary dictionary;
    dictionary.root = make_node();
    string english_equiv;
    bool is_for_delete=false;
    string myText;
    vector<string> inputs;
    string subst=",";
    while (getline (input1, myText)) {
        inputs.push_back(myText);
    }
    //for loop to read the input for performing operations
    for(int i=0;i<inputs.size();i++){
        //insert operation
        if(inputs[i].substr(0,6)=="insert"){
            int index=inputs[i].find(subst);
            string dothrak=inputs[i].substr(7,index-7);
            english_equiv=inputs[i].substr(index+1,(inputs[i].length()-2)-index);
            //below, if statement checks if there already exists the word in dictionary, and then inserts accordingly(more detailed explanation in before function definiton)
            if(!dictionary.search_for_insert(dothrak,english_equiv,myFile)){
                dictionary.insert(dothrak,english_equiv,myFile);
            }

        }
        //search operation
        else if(inputs[i].substr(0,6)=="search"){
            string dothrak=inputs[i].substr(7,inputs[i].length()-8);
            is_for_delete= false;
            dictionary.search(dothrak,is_for_delete, myFile);

        }
        //delete operation
        else if(inputs[i].substr(0,6)=="delete"){
            string dothrak=inputs[i].substr(7,inputs[i].length()-8);
            is_for_delete= true;
            //search if the word exists before deletion
            if(dictionary.search(dothrak,is_for_delete,myFile)){
                dictionary.root = dictionary.delete_word(dictionary.root, dothrak, 0);
                myFile<< "\""<<dothrak<< "\""<<" deletion is successful"<<endl;
            }
            is_for_delete= false;

        }
        //list operation
        else if(inputs[i].substr(0,4)=="list"){
            char str[100];
            print_dictionary(dictionary.root,0,str,myFile);
        }

    }
   input1.close();
   myFile.close();
    return 0;
}

