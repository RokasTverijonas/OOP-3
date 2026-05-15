#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <chrono>
#include "studentas.h"
#include "funkcijos.h"
#include "vector.h"


/*
void skaitymoTestai(std::vector<studentas>& A, std::string failas)
{
    int kartai = 5;
    double bendras = 0.0;
    
    while(true)
    {
        std::cout << "Kuri faila nuskaityti testavimui?" << std::endl;
        std::cin >> failas;
        if(failas == "kursiokai.txt" || failas == "studentai10000.txt" || failas == "studentai100000.txt" || failas == "studentai1000000.txt")
        {
            break;
        }
        std::cout << "Bandykite ivest dar karta! " << std::endl;
    }

    for(int i = 0; i < kartai; i++)
    {
        A.clear();
        auto start = std::chrono::steady_clock::now();

        skaitymas(A, failas);

        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> diff = end - start;
        bendras += diff.count();
    }

    std::cout << "failo " << failas << " nuskaitymo vidurkis: " << bendras / kartai << "s." << std::endl;
}
    */

double Studentas::vidurkis() const 
{
    if(nd_.empty())
    {
        return 0.0;
    }

    double suma = 0;

    for(int x : nd_)
    {
        suma += x;
    }
    return suma / nd_.size();
}

double Studentas::mediana() const 
{
    if(nd_.empty())
    {
        return 0.0;
    }
    Vector<int> temp = nd_;
    std::sort(temp.begin(), temp.end());

    int n = temp.size(); 

    if(n % 2 == 0)
    {
        return (temp[n / 2] + temp[(n - 1) / 2]) / 2.0;
    }
    else
    {
        return temp[n/2];
    }

}

double Studentas::galutinisVid() const
{
    return 0.4 * vidurkis() + 0.6 * egzaminas_;//2.4 + 3.6
}
double Studentas::galutinisMed() const
{
    return 0.4 * mediana() + 0.6 * egzaminas_;
}

void spausdinimas(Vector<Studentas>& A)
{
    char budas;
    while(true)
    {
        std::cout << "Skaiciuoti pagal vidurki (v) ar mediana (m)? " << std::endl;
        std::cin >> budas;
        budas = tolower(budas);
        if(budas == 'v' || budas == 'm')
        {
            break;
        }
        std::cout << "Ivedete neteisingai, iveskite (v) arba (m)" << std::endl;
    }
    std::cout << std::left << std::setw(10) << "Vardas" << std::setw(10) << "Pavarde";
    
    if(budas == 'm')
    {
        std::cout << std::setw(20) << "Galutinis (Med.)" << std::endl;
    }
    else
    {
        std::cout << std::setw(20) << "Galutinis (Vid.)" << std::endl;
    }
    
    std::cout << "------------------------------------------" << std::endl;

    for(auto& s : A)
    {
        std::cout <<std::setw(10) <<  s.getVardas() << std::setw(15)<< s.getPavarde();
        if(budas == 'm')
        {
            std::cout << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisMed() << std::endl;
        }
        else
        {
            std::cout << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisVid() << std::endl;
        }
    } 
}

void failoSpausdinimas(Vector<Studentas>& A)
{
    char isvedimas;
    while(true)
    {
        std::cout << "Isvesti ekrane ar faile? (e) - ekrane, (f) - faile " << std::endl;
        std::cin >> isvedimas;
        if(isvedimas == 'e' || isvedimas == 'f')
        {
            break;
        }
        std::cout << "Ivedete neteisingai, bandykite dar karta! " << std::endl;
    }
    if(isvedimas == 'e')
    {
        std::cout << std::left << std::setw(20) << "Vardas" << std::setw(25) << "Pavarde"
    << std::setw(20) << "Galutinis (Vid.)" << std::setw(20) << "Galutinis (Med.)" << std::endl;

    std::cout << "--------------------------------------------------------------" << std::endl;

    
    for(auto& s : A)
    {
        std::cout << std::setw(20) << s.getVardas() << std::setw(25) << s.getPavarde();

        std::cout << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisMed() << std::endl;
        
    }
    }
    else
    {
        std:: ofstream failas("rezultatai.txt");
        failas << std::left << std::setw(20) << "Vardas" << std::setw(25) << "Pavarde"
    << std::setw(20) << "Galutinis (Vid.)" << std::setw(20) << "Galutinis (Med.)" << std::endl;

    failas << "--------------------------------------------------------------" << std::endl;

    
    for(auto& s : A)
    {
        failas << std::setw(20) << s.getVardas() << std::setw(25) << s.getPavarde();

        failas << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisVid() << std::setw(20) << std::fixed << std::setprecision(2) << s.getGalutinisMed() << std::endl;
        
    }
    std::cout << "Rezultatai isvesti faile pavadinimu 'rezultatai.txt'" << std::endl;
    }

}

void failoGeneravimas(int studKiekis) {
    
    int pazymiuKiekis = 10;
    std::string failas = "studentai" + std::to_string(studKiekis) + ".txt";
    std::ofstream out(failas);

    out << std::left << std::setw(20) << "Vardas" << std::setw(25) << "Pavarde";

    for(int i = 1; i <= pazymiuKiekis; i++)
    {
        out << std::setw(8) << "ND" + std::to_string(i);
    }
    out << std::setw(8) << "Galutinis" << "\n";


    for(int i = 1; i <= studKiekis; i++)
    {
        out << std::left << std::setw(20) << "VardasNR" + std::to_string(i) << std::setw(25) << "PavardeNR" + std::to_string(i);

        for(int j = 0; j < pazymiuKiekis; j++)
        {
            out << std::setw(8) <<  (rand() % 10 + 1);
        }
        out << std::setw(8) << (rand() % 10 + 1) << "\n";
    }
    
    out.close();

}



void tyrimasPirmas()
{
    Vector<int> studKiekis = {1000, 10000, 100000, 1000000, 10000000};

    std::cout << std::left << std::setw(22) << "Studentų skaičius" << std::setw(10) << "Laikas" << std::endl;

    for(auto x : studKiekis)
    {
        auto start = std::chrono::high_resolution_clock::now();

        failoGeneravimas(x);

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff = end - start;

        std::cout << std::left << std::setw(20) << std::to_string(x) + " studentų" << std::setw(10) << diff.count() << "s" << std::endl;

    }
}

void tyrimasAntras(Vector<Studentas>& A, Vector<Studentas>& vargsai, Vector<Studentas>& kietekai)
{
    Vector<int> studKiekis = {1000, 10000, 100000, 1000000, 10000000};

    std::cout << std::left << std::setw(12) << "Studentai" << std::setw(15) << "Skaitymas"
    << std::setw(15) << "Padalinimas" << std::setw(15) << "Atskiri f." 
    << std::setw(15) << "Bendras laikas" << std::endl;


    for(auto x : studKiekis)
    {
        vargsai.clear();
        kietekai.clear();
        A.clear();
        
        Vector<Studentas> stud;
        stud.reserve(x);
        //nuskaitymas
        auto start1 = std::chrono::high_resolution_clock::now();
        skaitymas(stud, "studentai" + std::to_string(x) + ".txt");
        auto end1 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff1 = end1 - start1;

        //rikiavimas
        auto start2 = std::chrono::high_resolution_clock::now();
        StudentuPadalinimas(stud, vargsai, kietekai);
        auto end2 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff2 = end2 - start2;

        //i atskirus failus
        auto start3 = std::chrono::high_resolution_clock::now();
        atskiriFailai("studentai" + std::to_string(x) + ".txt", vargsai, kietekai);
        auto end3 = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> diff3 = end3 - start3;

        //bendras
        double visas = diff1.count() + diff2.count() + diff3.count();

        std::cout << std::left << std::setw(12) << x << std::setw(15) << diff1.count()
        << std::setw(15) << diff2.count() << std::setw(15) << diff3.count() 
        << std::setw(15) << visas << std::endl;


    }
}
