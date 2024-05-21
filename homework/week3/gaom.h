#ifndef GAOM_H
#define GAOM_H

#include "../problem/OneMax.cpp"

class Gaom: OneMax {
public:
    void RunALG(int, int, int);

private:
    // Input from Command-line Argument
    int _Bit;
    int _Run;
    int _Iter;

    int _Nfes;
    int _Mnfes;

    std::vector<int> _Best;

    void Init();
    void Evaluation();
    void Reset();

    void Selection();
    void Crossover();
    void Mutation();

};

void Gaom::RunALG (int Bit, int Run, int Iter){
    this->_Bit = Bit;
    this->_Run = Run;
    this->_Iter = Iter;
    this->_Nfes = this->_Mnfes = 0;

    while (this->_Run--){
        cout << "-------------------Run" << Run - this->_Run << "---------------------" << endl;
        Init();
        Evaluation();
        Reset();
    }
    cout << "Average NFEs : " << this->_Mnfes/Run << endl;
}

void Gaom::Evaluation(){
    for (int iter=0; iter<this->_Iter && (OneMaxProblem(this->_Best, this->_Bit)!=this->_Bit); iter++){
        Selection();
        Crossover();
        Mutation();
    }
}

void Gaom::Init(){
    this->_Best.resize(this->_Bit);
    for (int i=0; i<this->_Bit; i++){
        this->_Best[i] = rand()%2;
    }
}

void Gaom::Reset(){
    this->_Mnfes += this->_Nfes;
    this->_Nfes = 0;
    this->_Best.clear();
}


void Gaom::Selection(){
    
}
void Gaom::Crossover(){

}
void Gaom::Mutation(){

}

#endif