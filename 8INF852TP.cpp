

#include <iostream>
#include "Tools.h"
using namespace std;


int main(int argc, char* argv[]) 
{	
	clock_t	Start, End;	//Déclaration de variable afin de calculer le temps écoulé
	double Elapsed = 0;	//Variable servant à calculer le temps écoulé (Différence entre End et Start
	double	dTheBestFitness = 100000;	//Fitness de la meilleure solution
	/*char meth = argv[3][0];

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
		pSolution = new SMSSDTSolution(LeProb->getN(), argv[3][0]);
		SMSSDTSolution	Smeilleur = *pSolution;	//Sauvegarde de la meilleure solution
		pSolution->descenteVoisinage(LeProb->getN());
		for (int i = 0; i < pSolution->voisinage.size(); i++)
		{
			pSolution->Solution = pSolution->voisinage.at(i);
			//int test = pSolution->voisinage.size();
			vector<int> wala = pSolution->Solution;
			//pSolution = new SMSSDTSolution(LeProb->getN(), true);	//Une solution aléatoire
			vector<int> wala2 = Smeilleur.Solution;
			Tools::Evaluer(LeProb, *pSolution);	//Évaluer la solution
			double abc = pSolution->getObj();
			double abcd = Smeilleur.getObj();
			if (pSolution->getObj() < dTheBestFitness) // Si améliore meilleure solution, la garder
			{
				Smeilleur = *pSolution;
				dTheBestFitness = Smeilleur.getObj();
				i = 0;
				pSolution->descenteVoisinage(LeProb->getN());
			}
			//else 
			//delete pSolution;
		}
		delete pSolution;
		End = clock(); // Arrêter le clock
		Elapsed = (double(End - Start)) / CLOCKS_PER_SEC;	//Calculer le temps écoulé
		Tools::WriteReportLog(Elapsed, Smeilleur, LeProb->getNomFichier());	//Logguer le temps et la meilleure solution
		dTheBestFitness = 100000;

	}
	

	return 0;

}


