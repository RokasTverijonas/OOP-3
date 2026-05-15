#include "vector.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>



int main()
{
    std::vector<unsigned int> sizes ={10000, 100000, 1000000, 10000000, 100000000 };

    std::cout << std::left
          << std::setw(15) << "Elementu sk."
          << std::setw(15) << "std::vector"
          << std::setw(15) << "Vector" << "\n";
    std::cout << "-------------------------------------------\n";

    for(unsigned int sz : sizes)
    {
        auto start1 = std::chrono::high_resolution_clock::now();
        std::vector<int> v1;
        for(int i = 0; i < sz; i++)
        {
            v1.push_back(i);
        }
        auto end1 = std::chrono::high_resolution_clock::now();

        auto start2 = std::chrono::high_resolution_clock::now();
        Vector<int> v2;
        for(int i = 0; i < sz; i++)
        {
            v2.push_back(i);
        }
        auto end2 = std::chrono::high_resolution_clock::now();

        std::cout << std::left << std::setw(15) << sz << std::setw(15) << std::chrono::duration<double>(end1 - start1).count()
        << std::setw(15) << std::chrono::duration<double>(end2 - start2).count() << "\n";
    }

    //perskirtymai
    unsigned int sz = 100000000;
    int reallocStd = 0;
    int reallocMy = 0;

    std::vector<int> v3;
    for(int i = 0; i < sz; i++)
    {
        if(v3.capacity() == v3.size())
        {
            reallocStd++;
        }
        v3.push_back(i);
    }

    Vector<int> v4;
    for(int i = 0; i < sz; i++)
    {
        if(v4.capacity() == v4.size())
        {
            reallocMy++;
        }
        v4.push_back(i);
    }


    std::cout << "\nstd::vector perskirstymai: " << reallocStd << "\n";
    std::cout << "Vector perskirstymai:      " << reallocMy << "\n";

    return 0;
}