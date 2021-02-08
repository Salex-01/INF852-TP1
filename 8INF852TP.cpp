

#include <iostream>
#include "Tools.h"
using namespace std;


int main(int argc, char* argv[]) 
{	
	clock_t	Start, End;	//Déclaration de variable afin de calculer le temps écoulé
	double Elapsed = 0;	//Variable servant à calculer le temps écoulé (Différence entre End et Start
	double	dTheBestFitness = 100000;	//Fitness de la meilleure solution
	SMRDSProblem* LeProb;	//Déclaration d'un problème	
	LeProb = new SMRDSProblem(argv[2]);	//Lecture du deuxi;eme paramètre à partir de la console
	//LeProb->printOn(cout);	// Imprimer le Problème
	SMRDSSolution* pSolution = NULL;	//Solution intermédiaire

	int methode = atoi(argv[3]);
	char* meth;
	switch (methode)
	{
	case 1:
		meth = "recuit simulé";
		break;
	case 2:
		meth = "descente";
		break;
	case 3:
		meth = "recherche taboue";
		break;
	default:
		break;
	}

	// argv[1] exécutions de la génération aléatoire
	for (int j = 0; j < atoi(argv[1]); j++)
	{
		Start = clock();	//Démarrer l'horloge	
		SMRDSSolution	Smeilleur(LeProb->getN());	//Sauvegarde de la meilleure solution
		for (int i = 0; i < 1000000; i++)
		{
			pSolution = new SMRDSSolution(LeProb->getN(), true);	//Une solution aléatoire
			switch (methode)
			{
			case 1:
				pSolution->recuitSimule(LeProb);
				break;
			case 2:
				pSolution->descente();
				break;
			case 3:
				pSolution->taboue(LeProb);
				break;
			default:
				break;
			}
			Tools::Evaluer(LeProb, *pSolution);	//Évaluer la solution
			if (pSolution->getObj() < dTheBestFitness) // Si améliore meilleure solution, la garder
			{
				Smeilleur = *pSolution;
				dTheBestFitness = Smeilleur.getObj();
			}
			delete pSolution;
		}
		End = clock(); // Arrêter le clock
		Elapsed = (double(End - Start)) / CLOCKS_PER_SEC;	//Calculer le temps écoulé
		Tools::WriteReportLog(Elapsed, Smeilleur, meth, LeProb->getNomFichier());	//Logguer le temps et la meilleure solution
		dTheBestFitness = 100000;

	}
	

	return 0;

}


