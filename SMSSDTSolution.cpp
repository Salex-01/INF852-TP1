#ifndef __SMSSDTPROBLEM_CPP
#define __SMSSDTPROBLEM_CPP


#include "SMSSDTSolution.h"


#include <cmath>
#include <conio.h>
using namespace std;

/**
 * SMSSDTSolution()
 * Constructeur de la classe
 * Assigne les valeurs aléatoires initiales à la solution
**/

SMSSDTSolution::SMSSDTSolution(int N, bool test) {
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





#endif  //__SMSSDTPROBLEM_CPP