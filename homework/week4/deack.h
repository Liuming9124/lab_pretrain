#ifndef DEACK_H
#define DEACK_H


#include "../problem/Ackley.cpp"
#include <queue>
#include <vector>


class Deack: Ackley {
public:
    void RunALG( int, int, int, int, int, int, float);

private:
    int _Pop;
    int _Run;
    int _Iter;
    int _Bounder;
    int _Cr;
    float _F;
    int _Place;

    typedef struct Particle{
        vector<float> _position;
        float _fitness;
    } _Particle;

    _Particle _Gbest, _Offspring;
    vector<_Particle> _Swarm;

    void Init();
    void Evaluation();
    void Reset();
    
    void Mutation();
    void Crossover();
    void Selection();

    float Frand();
    void CheckBorder(_Particle);
};

void Deack::RunALG(int Pop, int Run, int Iter, int Dim, int Bounder, int Cr, float F){

    _Pop = Pop;
    _Run = Run;
    _Iter = Iter;
    _Bounder = Bounder;
    _Cr = Cr;
    _F = F;
    setArgs(20, 0.2, 2*M_PI, Dim);

    while (_Run--){
        cout << "-------------------Run" << Run - _Run << "---------------------" << endl;
        Init();
        Evaluation();
        Reset();
    }
}

void Deack::Init(){
    _Swarm.resize(_Pop);
    _Offspring._position.resize(getDim());
    int dim = getDim();
    for (int i=0; i<_Pop; i++){
        _Swarm[i]._position.resize(dim);
        for (int j=0; j<dim; j++){
            _Swarm[i]._position[j] = (rand() % _Bounder*2 - _Bounder);
        }
        _Swarm[i]._fitness = AckleyProblem(_Swarm[i]._position);
        (i==0) ? _Gbest = _Swarm[i] : _Gbest = (_Gbest._fitness < _Swarm[i]._fitness) ? _Gbest : _Swarm[i];
    }
}

void Deack::Evaluation(){
    for (int iter=0; iter<_Iter; iter++){
        float temp = _Gbest._fitness;
        Mutation();
        Crossover();
        Selection();

        if (temp != _Gbest._fitness){
            cout << "Iter: " << iter << " Best fitness: " << _Gbest._fitness << endl;
        }
    }
    cout << "Best fitness: " << _Gbest._fitness << endl;
}


void Deack::Reset(){
    _Swarm.clear();
    _Offspring._position.clear();
    _Offspring._fitness = 0;
    _Gbest._position.clear();
    _Gbest._fitness = 0;
}

float Deack::Frand(){
    int r = rand()%1001;
    return r / 1000.0;
}

void Deack::CheckBorder(_Particle check){
    for (int i = 0; i<getDim(); i++){
        if (!(check._position[i]<=_Bounder&& check._position[i]>=_Bounder)){
            check._position[i] = (rand() % _Bounder*2 - _Bounder);
        }
    }
}

void Deack::Mutation(){
    // init rand r1,r2 with different value
    int p, r1, r2;
    do {
        p  = rand() % _Pop;
        r1 = rand() % _Pop;
        r2 = rand() % _Pop;
    } while(r1 == r2 || r1 == p || r2 == p);
    _Place = p;
    for (int i=0; i<getDim(); i++){
        _Offspring._position[i] = _Swarm[p]._position[i]
            + _F * ( _Gbest._position[i] - _Swarm[p]._position[i]) 
            + _F * ( _Swarm[r1]._position[i] - _Swarm[r2]._position[i]);
    }
    CheckBorder(_Offspring);
}

void Deack::Crossover(){
    int Jrand = rand() % getDim();
    for (int i=0; i<getDim(); i++){
        if ( !(rand()%100) < _Cr || i == Jrand){
            _Offspring._position[i] = _Swarm[_Place]._position[i];
        }
    }
}

void Deack::Selection(){
    _Offspring._fitness = AckleyProblem(_Offspring._position);
    if (_Offspring._fitness < _Swarm[_Place]._fitness){
        _Swarm[_Place] = _Offspring;
        if (_Swarm[_Place]._fitness < _Gbest._fitness){
            _Gbest = _Offspring;
        }
    }
}

#endif