#include "abc.h"

unsigned int abcSorting::findLongest (){
    unsigned int maximum = input[0].size();
    for (unsigned int i=0;i<inputSize;i++){
        if (input[i].size()>maximum){
            maximum = input[i].size();
        }
    }
    return maximum;
}

abcSorting::abcSorting (std::fstream &input,int amount=2000){
    std::string temp;
    std::vector<int> nul;
    while (amount-- > 0 && input >> temp){
        this->input.push_back (temp);
    }

    inputSize = this->input.size();
    for (unsigned int i=0;i<inputSize;i++){
        wordTrecker.push_back(-1);
    }

    rang = findLongest();
    for (unsigned int i = 0;i<rang;i++){
        nul.push_back(-1);
    }
    for (unsigned int i = 'a'; i<='z';i++){
            letterTrecker.push_back(nul);
    }
}

int abcSorting::toInt (int index, unsigned int rang)const{
    return (rang<=input[index].size()-1) ? ((int)input[index][rang]-(int)'a') : -1;
}

void abcSorting::fillConnections (int rang = 0){
    //k is an index of a number of a letter from a beginning of the word
    for (unsigned int i=0; i< inputSize;i++){
            #ifdef DEBUG
                complexity++;
            #endif // DEBUG
        if (letterTrecker[toInt(i,rang)][rang] == -1){
            wordTrecker[i] = -1;
            letterTrecker[toInt(i,rang)][rang] = i;
        }
        else{
            wordTrecker[i] = letterTrecker[toInt(i,rang)][rang];
            letterTrecker[toInt(i,rang)][rang] = i;
        }
    }
}

void abcSorting::addWord (int index){
    result.push_back(input[index]);
}

int abcSorting::fillForOne (int rang = 0){
    //completes one cell and fill rang+1
    //return 0 if no words
    //       1 if added
    //       2 if finished but didn't add

    int i=0;
    int cur;
    int temp;

    while (i<=(int)'z'-(int)'a' && letterTrecker[i][rang] == -1){
        #ifdef DEBUG
            complexity++;
        #endif // DEBUG
        i++;
    }

    if (i>(int)'z'-(int)'a'){
        return 0;
    }

    temp = i;
    i = letterTrecker[i][rang];
    letterTrecker[temp][rang] = -1;
    rang++;

    #ifdef DEBUG
        outInputAndWt();
        outLettertrecker();
    #endif // DEBUG

    if (wordTrecker[i] == -1){
        addWord(i);
        wordTrecker[i] = -2;
        return 1;
    }

    while (i != -1 && i != -2){
    #ifdef DEBUG
        outInputAndWt();
        outLettertrecker();
        complexity++;
    #endif // DEBUG

        if ((cur = toInt(i,rang)) == -1){
            addWord(i);
            temp = i;
            i = wordTrecker[i];
            wordTrecker[temp] = -2;
        }
        else{
            if (letterTrecker[cur][rang] == -1){
                letterTrecker[cur][rang] = i;
                temp = i;
                i = wordTrecker[i];
                wordTrecker[temp] = -1;
                }
            else{
                temp = wordTrecker[i];
                wordTrecker[i] = letterTrecker[cur][rang];
                letterTrecker[cur][rang] = i;
                i = temp;
            }
        }
    }
    return 2;
}

void abcSorting::doSortRec(int rang = 0){
    int temp = fillForOne(rang);
    if (temp == 0 && rang == 0){
        return;
    }
    else if (temp == 0){
        doSortRec(rang-1);
    }
    else if (temp == 1){
        doSortRec(rang);
    }
    else{
        doSortRec(rang+1);
    }
}
void abcSorting::doSort (){
    fillConnections();
    doSortRec();
}

void abcSorting::outInput ()const{
    for (unsigned int i=0;i<inputSize;i++){
        std::cout<<input[i]<<" ";
    }
    std::cout<<std::endl;
}

void abcSorting::outWordtrecker ()const{
    unsigned int wordTreckerSize = wordTrecker.size();
    for (unsigned int i=0;i<wordTreckerSize;i++){
        std::cout<<wordTrecker[i]<<" ";
    }
    std::cout<<std::endl;
}

void abcSorting::outInputAndWt()const{
    unsigned int wordTreckerSize = wordTrecker.size();
    for (unsigned int i=0;i<wordTreckerSize;i++){
        std::cout<<i<<":"<<input[i]<<":"<<wordTrecker[i]<<" ";
    }
}

void abcSorting::outLettertrecker()const{
    std::cout<<std::endl;
    unsigned int finish = 'z' - 'a';
    for (unsigned int j = 0; j<rang;j++){
    for (unsigned int i = 0; i<=finish;i++){
            std::cout<<letterTrecker[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void abcSorting::outResult()const{
    std::cout<<std::endl;
    unsigned int outSize = result.size();
    for(unsigned int i=0;i<outSize;i++){
        std::cout<<result[i]<<" ";
    }
    std::cout<<std::endl;
}
