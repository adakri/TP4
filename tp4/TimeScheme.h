#ifndef _TIME_SCHEME_H

#include "OdeSystem.h"

class TimeScheme
{
  private:
  protected:
    // Pas de temps
    double _dt;
    // Temps en cours
    double _t;
    // Vecteur initial et vecteur solution
    Eigen::VectorXd _sol0, _sol;
    // Pointeur vers le système d'EDO
    OdeSystem* _sys;

  public:
    // Constructeur par défaut
    TimeScheme();
    // Destructeur par défaut - Si la classe ne contient pas de destructeur par défaut
    // alors le compilateur en génère un implicitement.
    virtual ~TimeScheme();
    // Initialisation de vos différentes variables
    virtual void Initialize(double t0, double dt, Eigen::VectorXd & sol0, std::string name_file, OdeSystem* sys);
    // Enregistre la solution un fichier
    virtual void SaveSolution();
    // Une étape du schéma en temps
    virtual void Advance();
    // Permet de récupérer _sol
    virtual const Eigen::VectorXd & GetIterateSolution() const;
};

//Ruge-Kutta 3
class RungeKuttaScheme3 : public TimeScheme
{
  public:
    //constructor
    RungeKuttaScheme3();
    void Advance();

};

//Adam-Bashforth
class AdBashforthScheme3 : public TimeScheme
{
  public:
    //constructor
    AdBashforthScheme3();
    void Advance();

};






#define _TIME_SCHEME_H
#endif
