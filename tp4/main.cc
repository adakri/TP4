#include "TimeScheme.h"
#include "OdeSystem.h"
#include <string>
#include <iostream>
using namespace std;
using namespace Eigen;

int main()
{
	// Définition du temps initial, du temps final et du pas de temps
	double t0(0.), tfinal(5.), dt(0.01);//adjust
	// Définition du nombre d'itérations à partir du temps final et du pas de temps
	int nb_iterations = int(ceil(tfinal/dt));
	// Recalcul de dt
	dt = tfinal / nb_iterations;
	// Nom du fichier solution
	string results = "solution.txt";


	int userChoiceSys; // Choix de l’utilisateur

	// Définition du vecteur initial (vecteur de Eigen)
	// Ici dans R^2
	VectorXd sol0,exactSol;

	cout << "------------------------------------" << endl;
	cout << "Choississez le système : " << endl;
	cout << "1) X’ = X"<< endl;
	cout << "2) x’ = -y et y’ = x" << endl;
	cout << "3) x’ = x^2 t" << endl;
	cout << "4) Lotka_Volterra"<<endl;
	cout << "5) Pendule simple avec/sans frottement"<<endl;

	cin >> userChoiceSys;

	// Définition d'un pointeur de OdeSystem
	OdeSystem* sys(0); ///ou FirstExampleOdeSystem

	switch(userChoiceSys)
	{
	case 1:
		sys = new FirstExampleOdeSystem();
		sol0.resize(4);
		sol0(0) = 2.; sol0(1) = 3.1; sol0(2) = -5.1; sol0(3) = 0.1;
		exactSol = sol0*exp(tfinal);
		results = "first_ex ";
		break;
	case 2:
		sys = new SecondExampleOdeSystem();
		sol0.resize(2); exactSol.resize(2); sol0(0) = 1; sol0(1) = -1;
		exactSol(0) = sol0(0)*cos(tfinal)-sol0(1)*sin(tfinal);
		exactSol(1) = sol0(1)*cos(tfinal)+sol0(0)*sin(tfinal);
		results = "second_ex ";
		break;
	case 3:
		sys = new ThirdExampleOdeSystem();
		sol0.resize(1); exactSol.resize(1); sol0(0) = -2;
		exactSol(0) = 2*sol0(0)/(2-tfinal*tfinal*sol0(0));
		results = "third_ex ";
		break;
	case 4:
		//choix des param
		//cout<<"donner a"<<endl;
		double a,b,c,d;
		a=2./3.;b=4./3;c=1.;d=1.;
		sys = new LotkaVolterraOdeSystem(a,b,c,d);
		sol0.resize(2); exactSol.resize(2);
		sol0[0]=0.9;sol0[1]=0.9;
		results = "lkVolt_ex ";
		break;
	case 5:
		//choix des param
		//cout<<"donner a"<<endl;
		double m,l,k;
		m=0.1;l=1,k=3.;		
		sys = new PendulumOdeSystem(m,l,k);
		sol0.resize(2); exactSol.resize(2);
		sol0[0]=M_PI/5.;sol0[1]=0.;
		results = "pendulum ";
		break;
	default:
		cout << "Ce choix n’est pas possible ! Veuillez recommencer !" << endl;
		exit(0);
	}


	cout << "------------------------------------" << endl;
	cout << "Choississez le schèma: " << endl;
	cout << "1) Euler explicite"<< endl;
	cout << "2) Ruge-Kutta 3" << endl;
	

	cin >> userChoiceSys;

	// Définition d'un pointeur de OdeSystem
	TimeScheme* time_scheme(0); ///ou FirstExampleOdeSystem

	switch(userChoiceSys)
	{
		case 1:
			time_scheme = new TimeScheme();
			results += " Euler_exp.txt";
			break;
		case 2:
			time_scheme = new RungeKuttaScheme3();
			results += "RungeKuttaScheme3.txt";
			break;	
		default:
			cout << "Ce choix n’est pas possible ! Veuillez recommencer !" << endl;
			exit(0);
	}


	//TimeScheme time_scheme=scheme; // Objet de TimeScheme
	time_scheme->Initialize(t0, dt, sol0, results, sys); // Initialisation
	time_scheme->SaveSolution(); // Sauvegarde condition initiale
	for (int n = 0; n < nb_iterations; n++)
	{ // Boucle en temps
		time_scheme->Advance();
		time_scheme->SaveSolution();
	}
	if ((userChoiceSys == 1) || (userChoiceSys == 2) || (userChoiceSys == 3) ||(userChoiceSys == 4) ||(userChoiceSys == 5) )
	{
		VectorXd approxSol = time_scheme->GetIterateSolution(); // Temps final
		double error = ((approxSol-exactSol).array().abs()).sum();
		cout << "Erreur = " << error<< " pour dt = " << dt << endl;
		time_scheme->Initialize(t0, dt/2., sol0, results, sys);
		for (int n = 0; n < nb_iterations*2; n++)
			time_scheme->Advance();
		approxSol = time_scheme->GetIterateSolution(); // Temps final
		double error2 = ((approxSol-exactSol).array().abs()).sum();
		cout << "Erreur = " << error2<< " pour dt = " << dt/2. << endl;
		cout << "Ordre de la méthode = " << log2(error/error2) << endl;
	}
	delete time_scheme;
	delete sys;
	return 0;
	}
	// cout << "------------------------------------" << endl;
	// cout << "Euler Explicite" << endl;
	// cout << "------------------------------------" << endl;
	// cout << "Système : X' = X avec X0 = " << endl;
	// cout << sol0 << endl;
	// cout << "------------------------------------" << endl;
	//
	// // Initialisation
	// time_scheme.Initialize(t0, dt, sol0, results, sys);
	// // On sauvegarde la solution
	// time_scheme.SaveSolution();
	//
	// // Boucle en temps
	// for (int n = 0; n < nb_iterations; n++)
	// {
	// 	time_scheme.Advance();
	// 	time_scheme.SaveSolution();
	// }

	/*
	// On récupère la solution approchée au temps final
	VectorXd approxSol = time_scheme.GetIterateSolution();
	// Définition de la solution exacte au temps final
	VectorXd exactSol = sol0*exp(tfinal);
	double error = ((approxSol-exactSol).array().abs()).sum();
	cout << "Erreur = " << error << " pour dt = " << dt << endl;
	cout << "------------------------------------" << endl;


	time_scheme.Initialize(t0, dt/2., sol0, results, sys);
	for (int n = 0; n < nb_iterations*2; n++)
	{
		time_scheme.Advance();
	}

	// On récupère la solution approchée au temps final
	approxSol = time_scheme.GetIterateSolution();
	double error2 = ((approxSol-exactSol).array().abs()).sum();
	cout << "Erreur = " << error2<< " pour dt = " << dt/2. << endl;
	cout << "------------------------------------" << endl;

	cout << "Ordre de la méthode = " << log2(error/error2) << endl;
	cout << "------------------------------------" << endl;
	//*/
