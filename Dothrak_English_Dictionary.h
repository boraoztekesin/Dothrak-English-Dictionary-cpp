#include<iostream>
#include<stdio.h>
#include<string>
#include <map>
#include<algorithm>
#include <functional>
#include <fstream>
#include <vector>
using namespace std;

struct TrieNode
{
    string english_equivelant;
    bool is_end_of_word;
    TrieNode *alphabet[26];
};

class Dothrak_English_Dictionary
{
public:

    TrieNode *root;
    void insert(string,string,ofstream&);
    bool search(string,bool,ofstream&);
    TrieNode* delete_word(TrieNode*, string, int);
    bool search_for_insert(string,string,ofstream& );

};
TrieNode* make_node()
{
    TrieNode *node = new TrieNode;
    for (int i = 0; i < 26; i++){
        node->alphabet[i] = NULL;
    }
    node->is_end_of_word = false;
    return node;
}
//this function inserts into dictionary
void Dothrak_English_Dictionary::insert(string doth_word, string english_equiv,ofstream& myFile)
{
    TrieNode *node = root;
    int x;
    for (int i = 0; i < doth_word.length(); i++)
    {
        x = doth_word[i] - 'a';
        if (node->alphabet[x] == NULL)
            node->alphabet[x] = make_node();
        node = node->alphabet[x];
    }
    node->is_end_of_word = true;
    node->english_equivelant=english_equiv;
    myFile<<"\""<<doth_word<<"\""<<" was added"<<endl;
}

bool is_emptyy(TrieNode* root)
{
    for (int i = 0; i < 26; i++)
        if (root->alphabet[i])
            return false;
    return true;
}
bool Dothrak_English_Dictionary::search(string doth_word,bool is_for_delete,ofstream& myFile)
{
    TrieNode *node = root;
    int length = doth_word.length();
    for (int i = 0; i < length; i++)
    {
        int x = doth_word[i] - 'a';
        if(i==0 && (!node->alphabet[x])){
            myFile<<"\""<<"no record"<<"\""<<endl;
            return false;
        }
        if (!node->alphabet[x]){
            myFile<<"\""<<"incorrect Dothraki word"<<"\""<<endl;
            return false;
        }
        node = node->alphabet[x];
    }
    if (node != NULL && node->is_end_of_word){
        if(!is_for_delete){
            myFile << "\""<<"The English equivalent is "<<node->english_equivelant<< "\""<<endl;
        }
    }else if(node != NULL ){
        myFile<<"\""<<"not enough Dothraki word"<<"\""<<endl;
    }
    return (node != NULL && node->is_end_of_word);
}

// This function checks if there already exists the same dothraki word before inserting. If there is ,it either updates or does not change if their english equivalent is same.

bool Dothrak_English_Dictionary::search_for_insert(string doth_word,string engEquiv,ofstream& myFile)
{
    TrieNode *node = root;
    int length = doth_word.length();
    for (int i = 0; i < length; i++)
    {
        int x = doth_word[i] - 'a';
        if (!node->alphabet[x]){
            return false;
        }
        node = node->alphabet[x];
    }
    if (node->is_end_of_word &&node != NULL && node->english_equivelant!=engEquiv ){
        node->english_equivelant=engEquiv;
        myFile<<"\""<<doth_word<<"\""<<" was updated"<<endl;
    }else if(node->is_end_of_word &&node != NULL && node->english_equivelant==engEquiv){
        myFile<<"\""<<doth_word<<"\""<<" already exist"<<endl;
    }
    return ( node->is_end_of_word && node != NULL);
}
//Deletes a wanted word from dictionary
TrieNode* Dothrak_English_Dictionary::delete_word(TrieNode* root, string doth_word, int d )
{
    if (root == NULL)
        return NULL;

    if (d == doth_word.size())
    {
        if (root->is_end_of_word)
            root->is_end_of_word = false;
        if (is_emptyy(root))
        {
            delete (root);
            root = NULL;
        }
        return root;
    }
    int x = doth_word[d] - 'a';
    root->alphabet[x] = delete_word(root->alphabet[x], doth_word, d + 1);
    if (is_emptyy(root) && !root->is_end_of_word)
    {
        delete (root);
        root = NULL;
    }
    return root;
}
//prints the dictionary values into output file
void print_dictionary(struct TrieNode* root, int lvl, char strr[],ofstream& myFile)
{
    if (root->is_end_of_word)
    {
        strr[lvl] = '\0';
        myFile<<"-"<<strr<<"("<<root->english_equivelant<<")"<<endl;
    }
    for (int j = 0; j < 26; j++)
    {
        if (root->alphabet[j])
        {
            strr[lvl] = j + 'a';
            print_dictionary(root->alphabet[j], lvl + 1,strr,myFile );
        }
    }
}