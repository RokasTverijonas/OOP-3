#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "zmogus.h"
#include "vector.h"

/**
 * @class Studentas
 * @brief Studento klasė su įvertinimais
 * 
 * Paveldi iš Zmogus klasės vardą ir pavardę. Saugo namų darbų, egzamino įvertinimus
 * bei skaičiuoja galutinį įvertinimą pagal vidurkį ir medianą
 */

class Studentas : public Zmogus{

private:
    Vector<int> nd_; ///< Namų darbų pažymių sąrašas
    int egzaminas_; ///< Egzamino pažymys
    double galutinisVid_; ///< Galutinis pažymys pagal vidurkį
    double galutinisMed_; ///< Galutinis pažymys pagal medianą

public:
    /**
     * @brief Default konstruktorius
     */
    Studentas() 
        : Zmogus(), egzaminas_(0), galutinisVid_(0.0), galutinisMed_(0.0) {}

    /**
     * @brief Konstruktorius su parametrais
     * @param v Studento vardas
     * @param p Studento pavardė
     */
    Studentas(const std::string& v, const std::string& p)
        : Zmogus(v, p), egzaminas_(0), galutinisVid_(0.0), galutinisMed_(0.0) {}

    /**
     * @brief Destruktorius
     */
    ~Studentas() override
    {
        vardas_.clear();
        pavarde_.clear();
        nd_.clear();
        egzaminas_ = 0;
        galutinisVid_ = 0.0;
        galutinisMed_ = 0.0;
    }


    /**
     * @brief Kopijos konstruktorius
     * @param a Kopijuojamas objektas
     */
    Studentas(const Studentas &a)
        : Zmogus(a),
          nd_(a.nd_),
          egzaminas_(a.egzaminas_),
          galutinisVid_(a.galutinisVid_),
          galutinisMed_(a.galutinisMed_) {}


    /**
     * @brief Kopijos priskyrimo operatorius
     * @param a Priskiriamas objektas
     * @return Nuoroda į objektą
     */
    Studentas& operator=(const Studentas &a)
    {
        if(this != &a)
        {
            Zmogus::operator=(a);
            nd_ = a.nd_;
            egzaminas_ = a.egzaminas_;
            galutinisVid_ = a.galutinisVid_;
            galutinisMed_ = a.galutinisMed_;
        }
        return *this;

    }

    /**
     * @brief Perkėlimo konstruktorius
     * @param a Perkeliamas objektas
     */
    Studentas(Studentas&& a)
        : Zmogus(std::move(a)),
          nd_(std::move(a.nd_)),
          egzaminas_(std::move(a.egzaminas_)),
          galutinisVid_(std::move(a.galutinisVid_)),
          galutinisMed_(std::move(a.galutinisMed_)) 
          {
            a.egzaminas_ = 0;
            a.galutinisVid_ = 0.0;
            a.galutinisMed_ = 0.0;
          }

    /**
     * @brief Perkėlimo priskyrimo operatorius
     * @param a Perkeliamas objektas
     * @return Nuoroda į objektą
     */
    Studentas& operator=(Studentas&& a)
    {
        if(this != &a)
        {
            Zmogus::operator=(std::move(a));
            nd_ = std::move(a.nd_);
            egzaminas_ = std::move(a.egzaminas_);
            galutinisVid_ = std::move(a.galutinisVid_);
            galutinisMed_ = std::move(a.galutinisMed_);

            a.egzaminas_ = 0;
            a.galutinisVid_ = 0.0;
            a.galutinisMed_ = 0.0;

        }

        return *this;
    }

    /**
     * @brief Išvesties operatorius
     * @param out Išvesties srautas
     * @param a Studentas objektas
     * @return Išvesties srautas
     */
    friend std::ostream& operator<<(std::ostream& out, const Studentas& a)
    {
        out << a.vardas_ << " " << a.pavarde_ << " ";
        for(int i : a.nd_)
        {
            out << i << " ";
        }
        out << a.egzaminas_;
        return out;
    }

    /**
     * @brief Įvesties operatorius
     * @param in Įvesties srautas
     * @param a Studentas objektas
     * @return Įvesties srautas
     */
    friend std::istream& operator>>(std::istream& in, Studentas& a)
    {
        std::string eilute;
        std::getline(in, eilute);
        std::stringstream ss(eilute);
        ss >> a.vardas_ >> a.pavarde_;

        int skaicius;
        Vector<int> visi;

        while(ss >> skaicius)
        {
            visi.push_back(skaicius);
        }
        a.egzaminas_  = visi.back();
        visi.pop_back();
        a.nd_ = visi;

        return in;
    }
    
    /**
     * @brief Grąžina namų darbų pažymius
     */
    const Vector<int>& getNd() const { return nd_; }

    /**
     * @brief Grąžina egzamino pažymį
     */
    int getEgzaminas() const { return egzaminas_; }

    /**
     * @brief Grąžina galutinį pažymį pagal vidurkį
     */
    double getGalutinisVid() const { return galutinisVid_; }

    /**
     * @brief Grąžina galutinį pažymį pagal medianą
     */
    double getGalutinisMed() const { return galutinisMed_; }

    /**
     * @brief Nustato namų darbų pažymius
     * @param n Pažymių sąrašas
     */
    void setNd(const Vector<int>& n) { nd_ = n; }

    /**
     * @brief Nustato egzamino pažymį
     * @param e Egzamino pažymys
     */
    void setEgzaminas(int e) { egzaminas_ = e; }

    /**
     * @brief Nustato galutinį pažymį pagal vidurkį
     * @param galVid galutinis pažymys pagal vidurkį
     */
    void setGalutinisVid(double galVid) { galutinisVid_ = galVid; }

    /**
     * @brief Nustato galutinį pažymį pagal medianą
     * @param galMed galutinis pažymys pagal medianą
     */
    void setGalutinisMed(double galMed) { galutinisMed_ = galMed; }

    /**
     * @brief Apskaičiuoja namų darbų vidurkį
     * @return Vidurkis kaip double
     */
    double vidurkis() const override;

    /**
     * @brief Apskaičiuoja namų darbų medianą
     * @return Mediana kaip double
     */
    double mediana() const;

    /**
     * @brief Apskaičiuoja galutinį pažymį pagal vidurkį
     * @return Galutinis pažymys kaip double
     */
    double galutinisVid() const;

    /**
     * @brief Apskaičiuoja galutinį pažymį pagal medianą
     * @return Galutinis pažymys kaip double
     */
    double galutinisMed() const;


};

#endif
