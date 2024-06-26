#ifndef SAOM_H
#define SAOM_H

#include "../problem/OneMax.cpp"
#include "../problem/AlgPrint.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;
using std::setw;

AlgPrint Show;

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

    int _nfes;
    int _mnfes;

    std::vector<bool> _Sol;

    void Init();
    void Evaluation();
    void Reset(double);
};

void Saom::RunALG(int Bit, int Run, int Iter, double Temp, double Rate){
    _Bit = Bit;
    _Run = Run;
    _Iter = Iter;
    _Temp = Temp;
    _Rate = Rate;
    _nfes = _mnfes = 0;

    
    Show = AlgPrint(_Run, "onemax", "sa");
    Show.NewShowDataInt(_Iter);
    for (int i = 0; i < _Run; i++){
        Show.clearResult("../result/onemax/sa/onemaxsa_" + to_string(i) + ".txt");
    }

    while (_Run--){
        cout << "-------------------Run" << Run - _Run << "---------------------" << endl;
        Init();
        Evaluation();
        Reset(Temp);
    }
    Show.PrintToFile("../result/onemax/sa/onemaxsaAvg.txt");
    cout << "Average _nfes : " << _mnfes/Run << endl;
}

void Saom::Evaluation(){
    vector<bool> best = _Sol;
    vector<bool> candidate = _Sol;
    bool best_flag = false;
    for (int i=0; i<_Iter; i++){
        if (best_flag ==false){
            _nfes++;
            Transaction(&candidate, _Bit);
            if ( OneMaxCompare(candidate, best, _Bit) ){
                best = candidate;
                if (OneMaxProblem(candidate, _Bit) == _Bit){
                    best_flag = true;
                }
            }
            else{
                double p = (rand() % 10000) / 100;
                if (p < _Temp){
                    best = candidate;
                }
            }
            _Temp *= _Rate;
            Print( best, _Bit, _Run, "onemax", "sa");
            Show.SetDataInt(OneMaxProblem(best, _Bit), i);
        }
        else{
            for (int j=i; j<_Iter; j++){
                Show.SetDataInt(OneMaxProblem(best, _Bit), j);
            }
            break;
        }
    }
}

void Saom::Reset(const double Temp){
    _mnfes += _nfes;
    _nfes = 0;
    _Temp = Temp;
}

void Saom::Init(){
    _Sol.resize(_Bit);
    for (int i=0; i<_Bit; i++){
        _Sol[i] = rand()%2;
    }
}

#endif