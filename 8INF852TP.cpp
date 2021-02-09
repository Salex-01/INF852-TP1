

#include <iostream>
#include "Tools.h"
using namespace std;


int main(int argc, char* argv[])
{
	clock_t	Start, End;	//Déclaration de variable afin de calculer le temps écoulé
	//double Elapsed = 0;	//Variable servant à calculer le temps écoulé (Différence entre End et Start
	double	dTheBestFitness = 100000;	//Fitness de la meilleure solution
	char meth = argv[3][0];
	/*
	char wait;
	switch (meth)
	{
	case '1':
		//Descente
		cin >> wait;
		break;
	case '2':
		//Taboue
		cin >> wait;
		break;
	case '3':
		//Recuit
		cin >> wait;
		break;
	default:
		cout << "Mauvaise entre";
		cin >> wait;
		break;
	}*/
	SMSSDTProblem* LeProb;	//Déclaration d'un problème	
	//LeProb = new SMSSDTProblem(argv[2]);	//Lecture du deuxi;eme paramètre à partir de la console
	LeProb = new SMSSDTProblem(argv[2], argv[3][0]);	//Lecture du deuxi;eme paramètre à partir de la console
	//LeProb->printOn(cout);	// Imprimer le Problème
	SMSSDTSolution* pSolution = NULL;	//Solution intermédiaire

	/*cout << "Quelle methode voulez vous usiliser ? \n 1 -> Descente  \n 2 -> Recuit Simule  \n 3 -> Recherche Taboue \n";
	char result;
	cin >> result;*/




	// argv[1] exécutions de la génération aléatoire
	for (int j = 0; j < atoi(argv[1]); j++)
	{
		Start = clock();	//Démarrer l'horloge	
		pSolution = new SMSSDTSolution(LeProb->getN(), argv[3][0], LeProb);
		
		switch (meth)
		{
		case '1':
			pSolution->algoDescente();
			break;
		case '2':
			//Taboue

			break;
		case '3':
			//Recuit
			break;
		default:
			cout << "Mauvaise entre";
			break;
		}


		delete pSolution;
		dTheBestFitness = 100000;

	}


	return 0;

}


