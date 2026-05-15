#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <list>
#include <deque>
#include "funkcijos.h"
#include "studentas.h"
#include "zmogus.h"
#include "vector.h"


const Vector<std::string> vardai = {"Rokas", "Dziugas", "Kajus", "Dovydas", "Matas", "Simonas", "Mantas", "Kasparas", "Tomas", "Kristupas"};
const Vector<std::string> pavardes = {"Brazdeikis" , "Kazlauskas", "Macijauskas", "Sabonis", "Valanciunas", "Tubelis", "Sirvydis", "Ulanovas", "Giedraitis", "Kalnietis"};


int main(){
    
    Vector<Studentas> A;
    Vector<Studentas> vargsai;
    Vector<Studentas> kietekai;
    srand(time(NULL));
    bool run = true;
    int auto_kiekis = -1;
    int kiekis = 0;

    while(run)
    {
        std::cout << "Pasirinkimų meniu: " << std::endl;
        std::cout << "1 - Ivesti ranka; " << std::endl;
        std::cout << "2 - Generuoti tik pazymius; " << std::endl;
        std::cout << "3 - Generuoti studentu vardus, pavardes ir pazymius; " << std::endl;
        std::cout << "4 - Skaityti informacija is failo; " << std::endl;
        std::cout << "5 - Generuoti studentų failą; " << std::endl;
        std::cout << "6 - Rusiuoti studentus i vargsus ir kietekus; " << std::endl;
        std::cout << "7 - atlikti pirmą arba antrą tyrimą;" << std::endl;
        std::cout << "8 - Atlikti tyrima su skirtingais konteineriais;"<< std::endl;
        //std::cout << "9 - Atlikti testą su naujais metodais;" << std::endl;
        std::cout << "9 - Spausdinti;" << std::endl;
        std::cout << "10 - Baigti darbą; " << std::endl;
        std::cout << " Pasirinkite ";
        int pasirinkimas;
        try{
            std::cin >> pasirinkimas;
            if(std::cin.fail())
            {
                throw std::invalid_argument("Įvestis nėra sveikasis skaičius. ");
            }
            if(pasirinkimas < 1 || pasirinkimas > 11) 
            {
                throw std::out_of_range("Pasirinkimas už leistino intervalo (1-10) ribų");
            }
        } catch(std::exception& e) {
            std::cout << "Klaida: " << e.what() << std::endl;

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        

        switch(pasirinkimas)
        {
            case 1: //ranka
            case 2: //auto nd ir egz
            {
                while(true)
                {
                    
                    Studentas s;
                    std::cout << "Iveskite " << A.size() + 1 << " studento varda ('pabaiga' - baigia ivedinejima): " << std::endl;
                    std::string vardas1, pavarde1;
                    std::cin >> vardas1;
                    s.setVardas(vardas1);
                    if(s.getVardas() == "pabaiga")
                    {
                        break;
                    }

                    std::cout << "Iveskite studento pavarde: " << std::endl;
                    std::cin >> pavarde1;
                    s.setPavarde(pavarde1);
                    int egz;
                    Vector<int> temp_nd;

                    if(pasirinkimas == 1)
                    {
                        while(true)
                        {
                            int nd;
                            std::cout << "Iveskite " << A.size() + 1 << " studento " << s.getNd().size() + 1 <<  " namu darbo ivertinima ( 0 - baigti): " << std::endl;
                            std::cin >> nd;
                            if(nd == 0)
                            {
                                break;
                            }

                            if(nd < 0 || nd > 10)
                            {
                                std::cin.clear();
                                std::cin.ignore(10000, '\n');
                                std::cout << "Ivedete neteisingai, bandykite dar karta!" << std::endl;
                                continue;
                            }

                            temp_nd.push_back(nd);
                            s.setNd(temp_nd);

                        }
                    }
                    else if(pasirinkimas == 2)
                    {
                        if(auto_kiekis == -1)
                        {
                            std::cout << "Iveskite norima pazymiu kieki: " << std::endl;
                            std::cin >> auto_kiekis;
                        }
                        for(int i = 0; i < auto_kiekis; i++)
                        {
                            temp_nd.push_back(rand() % 10 + 1);
                        }
                        s.setNd(temp_nd);
                    }

                    if(pasirinkimas == 1)
                    {
                        while(true)
                        {
                        std::cout << "Iveskite " << A.size() + 1 << " studento egzamino rezultata: " << std::endl;
                        std::cin >> egz;
                        if(egz > 0 && egz <= 10)
                        {
                            break;
                        }
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Ivedete neteisingai, bandykite dar karta!" << std::endl;
                        }
                    }
                    else if(pasirinkimas == 2)
                    {
                        egz = rand() % 10 + 1;
                    }
                    s.setEgzaminas(egz);

                    s.setGalutinisVid(s.galutinisVid());
                    s.setGalutinisMed(s.galutinisMed());

                    A.push_back(s);

                }
                break;
            }
            case 3:
            {
                int m;
                int n;
                std::cout << "Kiek studentu sugeneruoti? " << std::endl;
                while(true)
                {
                    std::cin >> m;
                    if(m >= 0)
                    {
                        break;
                    }
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ivedete neteisingai, bandykite dar karta! " << std::endl;
                }
                std::cout << "Kiek pazymiu sugeneruoti? " << std::endl;
                std::cin >> n;
                for(int i = 0; i < m; i++)
                {
                    Studentas s;
                    Vector<int> temp_nd;
                    s.setVardas(vardai[rand() % vardai.size()]);
                    s.setPavarde(pavardes[rand() % pavardes.size()]);
                    s.setEgzaminas(rand() % 10 + 1);
                    if(m > 0)
                    {
                        for(int i = 0; i < n; i++)
                        {
                            temp_nd.push_back(rand() % 10 + 1);
                        }
                    }
                    s.setNd(temp_nd);

                    s.setGalutinisVid(s.galutinisVid());
                    s.setGalutinisMed(s.galutinisMed());
                    
                    A.push_back(s);
                }

                break;
            }
            case 4:
            {
                bool tinka = true;
                while(tinka)
                {
                    std::string failas;
                    std::cout << "Pasirinkite faila: " <<std::endl;
                    std::cout << "kursiokai.txt , studentai10000.txt, studentai100000.txt, studentai1000000.txt" << std::endl;
                    std::cin >> failas;
                    try{
                        skaitymas(A, failas);
                        tinka = false;
                    } catch(std::exception& e) {
                        std::cout << "Klaida: " << e.what() << std::endl;
                        std::cout<< "Bandykite dar karta!" << std::endl;
                    }

                }
                int kriterijus;
                while(true)
                {
                    std::cout << "Pagal ka rikiuoti? " << std::endl;
                    std::cout << " 1 - varda " << std::endl;
                    std::cout << " 2 - pavarde " << std::endl;
                    std::cout << " 3 - Galutni (vidurkis) " << std::endl;
                    std::cout << " 4 - Galutini (mediana) " << std:: endl;
                    std::cin >> kriterijus;
                    if(kriterijus == 1 || kriterijus == 2 || kriterijus == 3 || kriterijus == 4)
                    {
                        break;
                    }
                    std::cout << "Ivedete neteisingai, bandykite dar karta! " << std::endl;
                }
                rikiavimas(A,kriterijus);
                failoSpausdinimas(A);
                //skaitymoTestai(A, "studentai1000000.txt");
                run = false;
                break;
            }
            case 5:
            {
            
                while(true)
                {
                    std::cout << "Įveskite kiek studentų norite turėti faile: " << std::endl;
                    std::cin >> kiekis;
                    if(kiekis > 0)
                    {
                        break;
                    }
                }
                failoGeneravimas(kiekis);
                break;
            }
            case 6:
            {
                int kriterijus;
                while(true)
                {
                    std::cout << "Pagal ka rikiuoti? " << std::endl;
                    std::cout << " 1 - varda " << std::endl;
                    std::cout << " 2 - pavarde " << std::endl;
                    std::cout << " 3 - Galutni (vidurkis) " << std::endl;
                    std::cout << " 4 - Galutini (mediana) " << std:: endl;
                    std::cin >> kriterijus;
                    if(kriterijus == 1 || kriterijus == 2 || kriterijus == 3 || kriterijus == 4)
                    {
                        break;
                    }
                    std::cout << "Ivedete neteisingai, bandykite dar karta! " << std::endl;
                }
                skaitymas(A, "studentai" + std::to_string(kiekis) + ".txt");
                StudentuPadalinimas(A, vargsai, kietekai);
                rikiavimas(vargsai, kriterijus);
                rikiavimas(kietekai, kriterijus);
                atskiriFailai("studentai" + std::to_string(kiekis) + ".txt",vargsai, kietekai);
                break;
            }

            case 7:
            {
                int tyrimas;
                while(true)
                {
                    std::cout << "Kurį tyrimą norite atlikti (1 arba 2): " <<std::endl;
                    std::cin >> tyrimas;
                    if(tyrimas == 1 || tyrimas == 2)
                    {
                        break;
                    }
                }

                if(tyrimas == 1)
                {
                    tyrimasPirmas();
                }
                else
                {
                    tyrimasAntras(A, vargsai, kietekai);
                }


                break;

            }
            case 8:
            {
                int strategija;
                while(true)
                {
                    std::cout << "Pasirinkite strategija (1, 2 arba 3): " << std::endl;
                    std::cin >> strategija;
                    if(strategija == 1 || strategija == 2 || strategija == 3)
                    {
                        break;
                    }
                    std::cin.clear();
                    std::cin.ignore(100000, '\n');
                }
                


                char kontPasirinkimas;
                while(true)
                {
                    std::cout <<"Pasirinkite konteinerio tipa: " << std::endl;
                    std::cout << "v - vector, l - list, d - deque" << std::endl;
                    std::cin >> kontPasirinkimas;
                    kontPasirinkimas = tolower(kontPasirinkimas);
                    if(kontPasirinkimas == 'v' || kontPasirinkimas == 'l' || kontPasirinkimas == 'd')
                    {
                        break;
                    }
                    std::cout << "Ivedete neteisingai, bandykite dar karta! " << std::endl;
                }
                int kriterijus;
                while(true)
                {
                    std::cout << "Pagal ka rikiuoti? " << std::endl;
                    std::cout << " 1 - varda " << std::endl;
                    std::cout << " 2 - pavarde " << std::endl;
                    std::cout << " 3 - Galutni (vidurkis) " << std::endl;
                    std::cout << " 4 - Galutini (mediana) " << std:: endl;
                    std::cin >> kriterijus;
                    if(kriterijus == 1 || kriterijus == 2 || kriterijus == 3 || kriterijus == 4)
                    {
                        break;
                    }
                    std::cout << "Ivedete neteisingai, bandykite dar karta! " << std::endl;
                }
                if(kontPasirinkimas == 'v')
                {
                    KonteineriuTyrimas(A, vargsai, kietekai, kriterijus, strategija);
                }
                else if(kontPasirinkimas == 'l')
                {
                    std::list<Studentas> A_list;
                    std::list<Studentas> vargsai_list;
                    std::list<Studentas> kietekai_list;
                    KonteineriuTyrimas(A_list, vargsai_list, kietekai_list, kriterijus, strategija);
                }
                else
                {
                    std::deque<Studentas> A_deque;
                    std::deque<Studentas> vargsai_deque;
                    std::deque<Studentas> kietekai_deque;
                    KonteineriuTyrimas(A_deque, vargsai_deque, kietekai_deque, kriterijus, strategija);
                }

                break;
            }
            
            case 9:
            {
                spausdinimas(A);
                break;
            }
            case 10:
            {
                run = false;
                break;
            }
            default:
            {
                std::cout << "Ivedete neteisingai, bandykite dar karta! " << std::endl;
                break;
            }
        }

    }
    return 0;
}
