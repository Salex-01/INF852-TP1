#ifndef __SMSSDTPROBLEM_CPP
#define __SMSSDTPROBLEM_CPP


#include "SMSSDTSolution.h"


#include <cmath>
#include <conio.h>
#include "Tools.h"
using namespace std;

/**
 * SMSSDTSolution()
 * Constructeur de la classe
 * Assigne les valeurs aléatoires initiales à la solution
**/

SMSSDTSolution::SMSSDTSolution(int N, bool test,SMSSDTProblem* probleme) {
	LeProb = probleme;
	// scheduling vector
	Solution.resize(N);
	TT.resize(N);
	CT.resize(N);
	ST.resize(N);
	// initialisation of possible values
	vector < int > possibles(N);
	for (int i = 0; i < N; i++)
		possibles[i] = i;
	// random initialization
	int rInd;              // random index
	for (int i = 0; i < N; i++)
	{
		rInd = (int)(((double)rand() / ((double)RAND_MAX + 1.0)) * (N - i));//rng.uniform (N - i);
		Solution[i] = possibles[rInd];
		possibles[rInd] = possibles[N - i - 1];
	}
}

SMSSDTSolution::SMSSDTSolution(int N, char methode)
{
	// scheduling vector
	Solution.resize(N);
	TT.resize(N);
	CT.resize(N);
	ST.resize(N);
	// initialisation of possible values
	vector < int > possibles(N);
	for (int i = 0; i < N; i++)
		possibles[i] = i;
	// random initialization
	int rInd;              // random index
	for (int i = 0; i < N; i++)
	{
		rInd = (int)(((double)rand() / ((double)RAND_MAX + 1.0)) * (N - i));//rng.uniform (N - i);
		Solution[i] = possibles[rInd];
		possibles[rInd] = possibles[N - i - 1];
	}
	//descenteVoisinage(N);
}




/**
 * Save
 * Fonction permettant d'écrire la solution dans un flux
 * @param Stream : Flux dans lequel on doit écrire
**/
ostream& SMSSDTSolution::Save(ostream& Stream) {
	
	for (int i = 0; i < (int)Solution.size(); i++) {
		Stream << Solution[i] << " ";

	}
	
	return Stream;
}


SMSSDTSolution::~SMSSDTSolution() {
	Solution.clear();
}

void SMSSDTSolution::descenteVoisinage(int N)
{
	vector<int> neighborhood;
	neighborhood.resize(N);
	for (int i = 1; i < N; i++) {
		neighborhood = Solution;
		std::swap(neighborhood[0], neighborhood[i]);
		voisinage.push_back(neighborhood);
	}
}

void SMSSDTSolution::algoDescente()
{
	clock_t	Start, End;
	descenteVoisinage(LeProb->getN());
	double	dTheBestFitness = 100000;	//Fitness de la meilleure solution
	SMSSDTSolution	Smeilleur = *this;	//Sauvegarde de la meilleure solution
	Start = clock();	//Démarrer l'horloge
	for (int i = 0; i < voisinage.size(); i++)
	{
		//SMSSDTSolution* tmpSol = this;
		Solution = voisinage.at(i);
		//int test = pSolution->voisinage.size();
		vector<int> wala = Solution;

		//pSolution = new SMSSDTSolution(LeProb->getN(), true);	//Une solution aléatoire

		Tools::Evaluer(LeProb, *this);	//Évaluer la solution
		double abc = getObj();
		double abcd = getObj();
		if (getObj() < dTheBestFitness) // Si améliore meilleure solution, la garder
		{
			Smeilleur = *this;
			dTheBestFitness = Smeilleur.getObj();
			i = 0;
			descenteVoisinage(LeProb->getN());
		}
	}
	End = clock(); // Arrêter le clock
	double Elapsed = (double(End - Start)) / CLOCKS_PER_SEC;	//Calculer le temps écoulé
	Tools::WriteReportLog(Elapsed, Smeilleur, LeProb->getNomFichier());	//Logguer le temps et la meilleure solution
}





#endif  //__SMSSDTPROBLEM_CPP