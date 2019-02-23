#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class abcSorting {

private:
    std::vector <std::string> input;
    unsigned int inputSize;
    unsigned int rang;
    std::vector <int> wordTrecker;
    std::vector <std::vector<int> > letterTrecker;
    std::vector <std::string> result;
public:
    unsigned int findLongest ();

    abcSorting (std::fstream &input,int amount);

    int toInt (int index, unsigned int rang)const;

    void fillConnections (int rang);

    void addWord (int index);

    int fillForOne (int rang );

    void doSortRec(int rang);

    void doSort ();


    void outInput ()const;


    void outWordtrecker ()const;


    void outInputAndWt()const;

    void outLettertrecker()const;

    void outResult()const;

};
