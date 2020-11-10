#ifndef _TIME_SCHEME_CPP

#include "TimeScheme.h"
#include <iostream>

using namespace Eigen;
using namespace std;

// Constructeur par défaut (ne pas oublier de mettre votre pointeur à 0 !!)
TimeScheme::TimeScheme() : _sys(0)
{}

// Destructeur
TimeScheme::~TimeScheme()
{}

// Initialisation de vos différentes variables
void TimeScheme::Initialize(double t0, double dt, VectorXd & sol0, string results, OdeSystem* sys)
{
  _dt = dt;
  _t = t0 ;
  _sol0 = sol0;
  _sol = sol0;
  _sys = sys;
  if (results.size() > 0)
  {
    _sys->InitializeFileName(results);
  }
}








// Schéma en temps par défaut : ici Euler Explicite
// Avancer d'un pas de temps
void TimeScheme::Advance()
{
  _sys->BuildF(_t, _sol);
  _sol += _dt*_sys->GetF();
  _t += _dt;
}

//-------------------RungeKutta-----------------------

//constructor
RungeKuttaScheme3::RungeKuttaScheme3()
{

}

void RungeKuttaScheme3::Advance()
{
  VectorXd k1,k2,k3;
  _sys->BuildF(_t, _sol);
  k1=_sys->GetF();
  _sys->BuildF(_t+0.5*_dt, _sol+0.5*_dt*k1);
  k2=_sys->GetF();
  _sys->BuildF(_t+_dt, _sol - _dt*k1+2*_dt*k2);
  k3=_sys->GetF();
  
  _sol += _dt*(1./6.)*(k1+4*k2+k3) ;              
  _t += _dt;
}
//------------------AdBashforthScheme3---------------------------------

//constructor
AdBashforthScheme3::AdBashforthScheme3()
{

}

void AdBashforthScheme3::Advance()
{
  VectorXd k1,k2,k3,k4;
  _sys->BuildF(_t, _sol); //à continuer
  k1=_sys->GetF();
  _sys->BuildF(_t+0.5*_dt, _sol+0.5*_dt*k1);
  k2=_sys->GetF();
  _sys->BuildF(_t+_dt, _sol - _dt*k1+2*_dt*k2);
  k3=_sys->GetF();
  
  _sol += _dt*(1./6.)*(k1+4*k2+k3) ;              
  _t += _dt;
}



// Enregistre la solution : fait appel à OdeSystem car la solution
// que l'on souhaite sauvegarder peut être différente de _sol SaveSolution
// le système
void TimeScheme::SaveSolution()
{
  _sys->SaveSolution(_t, _sol);
}

// Renvoie _sol (pratique pour calculer l'ordre de votre méthode)
const VectorXd & TimeScheme::GetIterateSolution() const
{
  return _sol;
}




#define _TIME_SCHEME_CPP
#endif
