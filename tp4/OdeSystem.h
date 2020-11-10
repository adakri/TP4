#ifndef _ODE_SYSTEM_H

#include "Dense"
#include <fstream>

class OdeSystem
{
  private:
    // Écriture du fichier
    // std::ofstream _file_out;

  protected:
    // Votre fonction f
    Eigen::VectorXd _f;
    std::ofstream _file_out;

  public:
    // Constructeur par défaut
    OdeSystem();
    // Destructeur par défaut
    virtual ~OdeSystem();
    // Initialiser le nom du fichier solution
    void InitializeFileName(const std::string file_name);
    // Sauvegarde la solution
    virtual void SaveSolution(const double t, const Eigen::VectorXd & sol);
    // Pour récupérer _f
    const Eigen::VectorXd &  GetF()  const;
    // Pour construire _f en fonction de votre système
    virtual void BuildF(const double t, const Eigen::VectorXd & sol)=0;
};


//-------------------------------------------------------------
// Classe fille publique d’OdeSystem
class FirstExampleOdeSystem : public OdeSystem
{
  public:
    void BuildF(const double t, const Eigen::VectorXd & sol); //f(X,t) = X
};

//classe 2eme exemple

class SecondExampleOdeSystem : public OdeSystem
{
  public:
    void BuildF(const double t, const Eigen::VectorXd & sol);


};

//Classe 3eme exemple

class ThirdExampleOdeSystem : public OdeSystem
{
  public:
    void BuildF(const double t, const Eigen::VectorXd & sol);

};

//LotkaVolterraOdeSystem

class LotkaVolterraOdeSystem : public OdeSystem
{
private:
  double _a,_b,_c,_d;
public:
  //constructeur nv
  LotkaVolterraOdeSystem(double a, double b, double c, double d);
  //dest nv
  //virtual ~LotkaVolterraOdeSystem();

  void BuildF(const double t, const Eigen::VectorXd & sol);

};


//pendulum system
class PendulumOdeSystem : public OdeSystem
{
  private:
    double _m,_k,_l;
  public:
  //constructors
    PendulumOdeSystem(double m, double l); // _k=0
    PendulumOdeSystem(double m, double l, double k);
  //method
    void BuildF(const double t, const Eigen::VectorXd & sol);
    void SaveSolution(const double t, const Eigen::VectorXd & sol);
};






#define _ODE_SYSTEM_H;
#endif
