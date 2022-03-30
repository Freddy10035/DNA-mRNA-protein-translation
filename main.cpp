#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;
string readFastaFile(string path);
void readCsvFile(string path);
string transcribe(string dnaString);
vector<string> translate(string mrnaString);
//global vector of vectors (2Dimensional vector) list
vector<vector<string> > mycodons;

string readFastaFile(string path)
{
    string dnaString;
    fstream newfile;
    newfile.open(path,ios::in);  // open a file to perform write operation using file object
    if(newfile.is_open()){   //checking whether the file is open
        string line;
        getline(newfile, line);
        while(getline(newfile, line)){ //read data from file object and put it into string.
            dnaString += line;
        }
        newfile.close(); //close the file object.
    }
    //cout << dnaString.substr(0,100)<< endl;
    return dnaString;
}

void readCsvFile(string path)
{
    ifstream inFile;
    string codon,Abv, AAcode, name;

    inFile.open(path);
    //read the first entry as column headers
    getline ( inFile, codon, ',' );
    getline ( inFile, Abv, ',' );
    getline ( inFile, AAcode, ',' );
    inFile >> name;
    while (!inFile.eof()) {//while we have not reached the end of file
        //read next entry
        getline ( inFile, codon, ',' );
        getline ( inFile, Abv, ',' );
        getline ( inFile, AAcode, ',' );
        inFile >> name;
        vector<string> temp;
        codon.erase(std::remove_if(codon.begin(), codon.end(), ::isspace), codon.end());//clear from white space characters

        temp.push_back(codon);
        AAcode.erase(std::remove_if(AAcode.begin(), AAcode.end(), ::isspace), AAcode.end());//clear from white space characters
        temp.push_back(AAcode); // add a vector entry consisting of codon and AAcode
        mycodons.push_back(temp);//add the vector to mycodons 2D vector
    }
 }
string findAA(string codon)
{   //search the AAcode for a specific codon
    for(int i = 0 ; i < mycodons.size(); i++){
        if(mycodons[i][0] == codon){
            return mycodons[i][1];
        }
    }
    return "";
}
//convert DNA string to mRNA string
string transcribe(string dna_string){

    // your code comes here

    string dnastring = "AGCT"; // DNA Bases
    string mrnastring = "AGCU"; // mRNA Bases

    string mrna_string = "";

    // Loop over the DNA string and replace with
    // repective RNA Base.
    // here I counted the strings DNA and mRNA bases as 0,1,2,3 which is AGCT respectively and replaced the DNA number values with the appropriate
    // mRNA base
    for (int i = 0; i < dna_string.length(); i++) {
               if (dnastring[i] == dnastring[0]) { // Adenine
            mrna_string += mrnastring[3];
        } else if (dnarstring[i] == dnastring[1]) { // Guanine
            mrna_string += mrnastring[2];
        } else if (dnastring[i] == dnastring[2]) { // Cytosine
            mrna_string += mrnastring[1];
        } else if (dnastring[i] == dnastring[3]) { // Uracil
            mrna_string += mrnastring[0];
        }
    }

    // Return mRNA string
    return mrna_string;
}

//search for codons in the mRNA string and convert them to equivalent AAcodes
//each protein starts with AUG codon and ends with UAG, UGA or UAA codons
//return the list of proteins as a vector
vector<string> translate(string mrna_string)
{
   // your code comes here
}

void print_protein_list(vector<string> list)
{
    for(string line : list)
    {
        cout << line << endl;
    }
    cout << list.size() << " proteins listed" << endl;
}

int main()
{
    string dnastring = readFastaFile("ecoli.fa");
    readCsvFile("codon_table.csv");
    string mrnastring = transcribe(dnastring);
    vector<string> protein_list = translate(mrnastring);
    print_protein_list(protein_list);

    return 0;
}
