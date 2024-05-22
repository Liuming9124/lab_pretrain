#ifndef SAOM_H
#define SAOM_H

#include "../problem/OneMax.cpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
using std::setw;

class Saom : OneMax
{
public:
    void RunALG(int, int, int, double, double);

private:
    // Input from Command-line Argument
    int _Bit;
    int _Run;
    int _Iter;
    double _Temp;
    double _Rate;

    int nfes;
    int mnfes;

    int _Iter_len = 0;
    std::vector<bool> _Sol;

    void Init();
    void Evaluation();
    void Reset(double);
};

void Saom::RunALG(int Bit, int Run, int Iter, double Temp, double Rate){
    this->_Bit = Bit;
    this->_Run = Run;
    this->_Iter = Iter;
    this->_Temp = Temp;
    this->_Rate = Rate;
    this->nfes = this->mnfes = 0;

    while (this->_Run--){
        cout << "-------------------Run" << Run - this->_Run << "---------------------" << endl;
        Init();
        Evaluation();
        Reset(Temp);
    }
    cout << "Average NFEs : " << this->mnfes/Run << endl;
}

void Saom::Evaluation(){
    vector<bool> best = this->_Sol;
    vector<bool> candidate = this->_Sol;
    bool best_flag = false;
    for (int i=0; i<this->_Iter && best_flag ==false; i++){
        this->nfes++;
        Transaction(&candidate, this->_Bit);
        if ( OneMaxCompare(candidate, best, this->_Bit) ){
            best = candidate;
            if (OneMaxProblem(candidate, this->_Bit) == this->_Bit){
                best_flag = true;
            }
        }
        else{
            double p = (rand() % 10000) / 100;
            if (p < this->_Temp){
                best = candidate;
            }
        }
        this->_Temp *= this->_Rate;
        Print(i, best, this->_Iter_len, this->_Bit, this->_Run, "onemax", "sa");
    }
}

void Saom::Reset(const double Temp){
    this->mnfes += this->nfes;
    cout << this->nfes << endl;
    this->nfes = 0;
    this->_Iter_len = 0;
    this->_Temp = Temp;
}

void Saom::Init(){
    this->_Sol.resize(this->_Bit);
    for (int i=0; i<this->_Bit; i++){
        this->_Sol[i] = rand()%2;
    }
    int count = this->_Iter;
    do {
        this->_Iter_len++;
    } while (count/=10);
}

#endif