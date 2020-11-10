#ifndef _ODE_SYSTEM_CPP

#include "OdeSystem.h"
#include <iostream>

using namespace Eigen;
using namespace std;

// Constructeur par défaut
OdeSystem::OdeSystem()
{}

// Destructeur par défaut
OdeSystem::~OdeSystem()
{}

// Initialisation du nom du fichier
void OdeSystem::InitializeFileName(const std::string file_name)
{
  _file_out.open(file_name);
}

// Renvoie le vecteur _f
const VectorXd & OdeSystem::GetF() const
{
  return _f;
}


// // Construit le vecteur f(t, sol)
// void OdeSystem::BuildF(const double t, const VectorXd & sol)
// {
//   _f = sol;
// } devenue virtuelle pure

///-------------premier exemple-----------------------
void FirstExampleOdeSystem::BuildF(const double t, const VectorXd & sol)
{
  _f=sol; ///
}



//---------------second exemple-----------------------------
void SecondExampleOdeSystem::BuildF(const double t, const VectorXd & sol)
{

  _f.resize(sol.size());
  _f[0]=-sol[1];
  _f[1]=sol[0];

   ///f([x,y],t)=[-y,x]
}



//---------------Third example-----------------------------
void ThirdExampleOdeSystem::BuildF(const double t, const VectorXd & sol)
{
  _f.resize(sol.size());
  _f[0]=t*pow(sol[0],2);
   ///f(x,t)=t*x*x
}


//----------------LotkaVolterraOdeSystem------------------

LotkaVolterraOdeSystem::LotkaVolterraOdeSystem(double a, double b, double c, double d):OdeSystem()
{
  _a=a;
  _b=b;
  _c=c;_d=d;
}

void LotkaVolterraOdeSystem::BuildF(const double t, const VectorXd & sol)
{
  _f.resize(sol.size());
  _f[0]=sol[0]*(_a-_b*sol[1]);
  _f[1]=sol[1]*(_c*sol[1]-_d);
   
}

//Pendulum constructor
PendulumOdeSystem::PendulumOdeSystem(double m, double l): OdeSystem()
{
  _m=m;
  _l=l;
  _k=0.;
  
}

PendulumOdeSystem::PendulumOdeSystem(double m, double k, double l): OdeSystem()
{
  _m=m;
  _l=l;
  _k=k;
  
}

void PendulumOdeSystem::BuildF(const double t, const Eigen::VectorXd & sol)
{
  _f.resize(sol.size());
  _f[0]=sol[1];
  _f[1]=-(9.81/_l) *sin(sol[0]) - (_k/(_m*pow(_l,2))) * sol[1];
}

//save solution sprecial
void PendulumOdeSystem::SaveSolution(const double t, const Eigen::VectorXd & sol)
{
  
  _file_out << t <<" " << sin(sol[0]) << " " <<-cos(sol[0]) <<endl;
};



// Enregistre la solution
// Pour le moment : sol_1, sol_2 ...
void OdeSystem::SaveSolution(const double t, const VectorXd & sol)
{
  _file_out << t;
  for (int i = 0 ; i < sol.rows() ; ++i)
  {
    _file_out << " " << sol(i);
  }
  _file_out << std::endl;
}


#define _ODE_SYSTEM_CPP
#endif
