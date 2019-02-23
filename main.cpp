#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "abc.h"

//#define DEBUG

#ifdef DEBUG
    int complexity = 0;
#endif // DEBUG







int main()
{
    std::fstream input ("input.txt",std::ios::in);
    abcSorting hell (input,100);

    hell.doSort();

    hell.outResult();
    input.close();

    #ifdef DEBUG
        std::cout<<complexity <<" "<< hell.findLongest();
    #endif // DEBUG

    return 0;
}
