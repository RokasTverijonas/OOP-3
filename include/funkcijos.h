#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include "studentas.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <list>
#include <deque>
#include <chrono>
#include <iomanip>
#include "vector.h"

/**
 * @brief Spausdina studentų sąrašą
 * @param A Studentų vektorius
 */
void spausdinimas(Vector<Studentas>& A);

/**
 * @brief Spausina studentų sąrašą ekrane arba faile
 * @param A Studentų vektorius
 */
void failoSpausdinimas(Vector<Studentas>& A);

/**
 * @brief Generuoja studentų failą
 * @param studKiekis Studentų kiekis
 */
void failoGeneravimas(int studKiekis);

/**
 * @brief Atlieka tyrimą - matuoja failų generavimo laiką
 */
void tyrimasPirmas();

/**
 * @brief Atlieka tyrimą - matuoja nuskaitymo ir padalinimo laiką
 * @param A Studentų vektorius
 * @param vargsai Prastai besimokančių studentų vektorius
 * @param kietekai Gerai besimokančių studentų vektorius
 */
void tyrimasAntras(Vector<Studentas>& A, Vector<Studentas>& vargsai, Vector<Studentas>& kietekai);


/**
 * @brief Nuskaito duomenis iš failo
 * @tparam konteineris Konteineris (vector, list, deque)
 * @param A Studentų konteineris
 * @param failas Failo pavadinimas
 */
template<typename konteineris> 
void skaitymas(konteineris& A, std::string failas)
{
    std::ifstream input(failas);

    if(!input.is_open())
    {
        throw std::runtime_error("Pasirinkto failo nepavyko atidaryti!");
    }
    std::string eilute;

    getline(input, eilute);

    while(getline(input, eilute))
    {
        std::stringstream ss(eilute);
        Studentas s;
        std::string vardas, pavarde;
        ss >> vardas >> pavarde;
        s.setVardas(vardas);
        s.setPavarde(pavarde);

        Vector<int> pazymiai;
        int x;
        while(ss >> x)
        {
            pazymiai.push_back(x);
        }

        s.setEgzaminas(pazymiai.back());
        pazymiai.pop_back();


        s.setNd(pazymiai);
        s.setGalutinisVid(s.galutinisVid());
        s.setGalutinisMed(s.galutinisMed());

        A.push_back(s);
    }
    input.close();
}

/**
 * @brief Surašo vargšus ir kietekus į atskirus failus
 * @tparam konteineris Konteineris (vector, list, deque)
 * @param failas Orginalaus failo pavadinimas
 * @param vargsai Vargšų studentų konteineris
 * @param kietekai Kietekų studentų konteineris
 */
template<typename konteineris>
void atskiriFailai(std::string failas, konteineris& vargsai, konteineris& kietekai)
{
    std::ofstream vargsuf("vargsai_" + failas);
    std::ofstream kietekuf("kietekai_" + failas);

    vargsuf << std::left << std::setw(10) << "Vardas" << std::setw(10) << "Pavarde"
    << std::setw(20) << "Galutinis(Vid.)" << std::setw(20) << "Galutinis(Med.)" << "\n";

    kietekuf << std::left << std::setw(15) << "Vardas" << std::setw(20) << "Pavarde"
    << std::setw(20) << "Galutinis(Vid.)" << std::setw(20) << "Galutinis(Med.)" << "\n";

    for(auto& s : vargsai)
    {
        vargsuf << std::setw(15) << s.getVardas() << std::setw(20) << s.getPavarde();

        vargsuf << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisMed() << "\n";
        
    }

    if(!kietekai.empty())
    {
        for(auto& s : kietekai)
        {
            kietekuf << std::setw(15) << s.getVardas() << std::setw(20) << s.getPavarde();

            kietekuf << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisMed() << "\n";
        
        }        
    }
}

/**
 * @brief Rikiuoja studentus pagal pasirinktą kriterijų
 * @tparam konteineris Konteineris (vector, list, deque)
 * @param A Studentų konteineris
 * @param kriterijus Rikiavimo kriterijus (1 - vardas; 2 - pavardė; 3 - galutinis pagal vidurkį; 4 - galutinis pagal medianą)
 */
template<typename konteineris>
void rikiavimas(konteineris& A, int kriterijus)
{
    
    auto byVardas = [](const Studentas& a, const Studentas& b)
    {
        return a.getVardas() < b.getVardas();
    };
    auto byPavarde = [](const Studentas& a, const Studentas& b)
    {
        return a.getPavarde() < b.getPavarde();
    };
    auto byGalVid = [](const Studentas& a, const Studentas& b)
    {
        return a.getGalutinisVid() < b.getGalutinisVid();
    };
    auto byGalMed = [](const Studentas& a, const Studentas& b)
    {
        return a.getGalutinisMed() < b.getGalutinisMed();
    };

    //Listo rikiavimas
    if constexpr (std::is_same_v<konteineris, std::list<Studentas>>)
    {
        switch(kriterijus)
        {
            case 1: A.sort(byVardas); break;
            case 2: A.sort(byPavarde); break;
            case 3: A.sort(byGalVid); break;
            case 4: A.sort(byGalMed); break;
        }
    }
    //Vector arba deque rikiavimas
    else
    {
        switch(kriterijus)
        {
            case 1: std::sort(A.begin(), A.end(), byVardas); break;
            case 2: std::sort(A.begin(), A.end(), byPavarde); break;
            case 3: std::sort(A.begin(), A.end(), byGalVid); break;
            case 4: std::sort(A.begin(), A.end(), byGalMed); break;
        }   
    }
    

}

/**
 * @brief 1 strategija - dalina studentus į du atskirus konteinerius
 * @tparam konteineris Konteineris (vector, list, deque)
 * @param A Studentų konteineris
 * @param vargsai Prastai besimokančių studentų konteineris
 * @param kietekai Gerai besimokančių studentų konteineris
 */
template<typename konteineris>
void StudentuPadalinimas( konteineris& A, konteineris& vargsai, konteineris& kietekai)
{
    for(const auto& s : A)
    {
        if(s.getGalutinisVid() < 5.0)
        {
            vargsai.push_back(s);
        }
        else
        {
            kietekai.push_back(s);
        }
    }
    A.clear();

}
/**
 * @brief 2 strategija - rikiuoja ir išima vargšus iš galo
 * @tparam konteineris Konteineris (vector, list, deque)
 * @param A Studentų konteineris
 * @param vargsai Prastai besimokančių studentų konteineris
 */
template<typename konteineris>
void StudentuPadalinimas2(konteineris& A, konteineris& vargsai)
{
    
    if constexpr (std::is_same_v<konteineris, std::list<Studentas>>)
    {
        A.sort([](const Studentas& a, const Studentas& b){
            return a.getGalutinisVid() > b.getGalutinisVid();
        });
    }
    else 
    {
        std::sort(A.begin(), A.end(), [](const Studentas& a, const Studentas& b){
            return a.getGalutinisVid() > b.getGalutinisVid();
        });
    }
    while(A.back().galutinisVid() < 5)
    {
        vargsai.push_back(A.back());
        A.pop_back();
    }
    /*
    auto it = A.end();

    while(it != A.begin())
    {
        --it;
        if(it->getGalutinisVid() < 5)
        {
            vargsai.push_back(*it);
            it = A.erase(it);
        }
        else{
            break;
        }
    }*/


    
    /*remove_if iskelia konteinerio elementus i jo gala, ties kuriais lambda grazina true
    // it yra iteratorius kuri po remove_if rodo i pirma "netikusi" elementa, kuri reikia pasalinti
    auto it = remove_if(A.begin(), A.end(), [&vargsai](studentas& a)
    {
        if(a.galutinisVid < 5.0)
        {
            vargsai.push_back(a);
            return true;
        }
        return false;
    });
    //istrinam pagrindinio konteinerio galo elementus, kurie po remove_if buvo ten sudėti
    A.erase(it, A.end());
    */

}

/**
 * @brief 3 strategija - naudoja partition padalinimui
 * @tparam konteineris Konteineris (vector, list, deque)
 * @param A Studentų konteineris
 * @param vargsai Prastai besimokančių studentų konteineris
 */
template<typename konteineris>
void StudentuPadalinimas3(konteineris& A, konteineris& vargsai)
{
    //grazina iteratoriu it, kuris rodo i antro bloko pirma elementa, kuris pagal partition ir musu salyga buvo false
    //konteineris lieka isdeliotas taip: pirmi elementai tie, kurie tenkina salyga, tada po ju eina visi like
    auto it = std::partition(A.begin(), A.end(), [](const Studentas& a) { return a.getGalutinisVid() >= 5.0; });

    //sudeda elementus nuo konteinerio A iteratoriaus iki konteinerio pabaigos i vargsai konteineri
    vargsai.insert(vargsai.begin(), it, A.end());
    //istrina A konteinerio elementus nuo iteratoriaus iki konteinerio pabaigos
    A.erase(it, A.end());

}

/**
 * @brief Atlieka skirtingų konteinerių greičio tyrimą su skirtingomis strategijomis
 * @tparam konteineris Konteineris (vector, list, deque)
 * @param A Studentų konteineris
 * @param vargsai Prastai besimokančių studentų konteineris
 * @param kietekai Gerai besimokančių studentų konteineris
 * @param kriterijus Rikiavimo kriterijus (1 - vardas; 2 - pavardė; 3 - galutinis pagal vidurkį; 4 - galutinis pagal medianą)
 * @param strategija Padalinimo strategija (1, 2 arba 3)
 */
template<typename konteineris>
void KonteineriuTyrimas(konteineris& A, konteineris& vargsai, konteineris& kietekai, int kriterijus, int strategija)
{
    Vector<int> studKiekis = {1000, 10000, 100000, 1000000, 10000000};

    std::cout << std::left << std::setw(12) << "Studentai" << std::setw(15) << "Skaitymas"
    << std::setw(15) << "Rikiavimas" << std::setw(15) << "skirstymas" 
    << std::setw(15) << "Bendras laikas" << std::endl;


    for(auto x : studKiekis)
    {
        A.clear();
        vargsai.clear();
        kietekai.clear();
        
        //nuskaitymas
        auto start1 = std::chrono::high_resolution_clock::now();
        skaitymas(A, "studentai" + std::to_string(x) + ".txt");
        auto end1 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff1 = end1 - start1;

        //rikiavimas
        auto start2 = std::chrono::high_resolution_clock::now();
        rikiavimas(A, kriterijus);
        auto end2 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff2 = end2 - start2;

        //padalinimas
        auto start3 = std::chrono::high_resolution_clock::now();
        if(strategija == 1)
        {
            StudentuPadalinimas(A, vargsai, kietekai);
        }
        else if(strategija == 2)
        {
            StudentuPadalinimas2(A, vargsai);
            //kietekai = A;
            //A.clear();
        }
        else if(strategija == 3)
        {
            StudentuPadalinimas3(A, vargsai);
            //kietekai = A;
            //A.clear();
        }
        auto end3 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff3 = end3 - start3;

        //bendras
        double visas = diff1.count() + diff2.count() + diff3.count();

        std::cout << std::left << std::setw(12) << x << std::setw(15) << diff1.count()
        << std::setw(15) << diff2.count() << std::setw(15) << diff3.count() 
        << std::setw(15) << visas << std::endl;

        ///atskiriFailai("studentai" + std::to_string(x) + ".txt", vargsai, kietekai);

        


    }
    A.clear();
    vargsai.clear();
    kietekai.clear();
}

#endif