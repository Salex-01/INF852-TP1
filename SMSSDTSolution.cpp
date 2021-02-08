#ifndef __SMSSDTPROBLEM_CPP
#define __SMSSDTPROBLEM_CPP


#include "SMSSDTSolution.h"
#include "SMSSDTProblem.h"
#include "Tools.h"


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

void recuitSimule(SMSSDTProblem *prob) {
	if (N > 1) {
		double temp = 1;
		Tools::Evaluer(prob, this);
		double solValue = this.getObj();
		while (temp > 0.001 && solValue > 0) {
			SMSSDTSolution tmpSol(N);
			tmpSol.Solution = std::copy(this.Solution.begin(), this.Solution.end(), tmpSol.Solution.begin());
			int index1 = std::abs(rand()) % N;
			int index2;
			do
			{
				index2 = std::abs(rand()) % N;
			} while (index2==index1);
			int tmp = tmpSol.Solution[index1];
			tmpSol.Solution[index1] = tmpSol.Solution[index2];
			tmpSol.Solution[index2] = tmp;
			Tools::Evaluer(prob, tmpSol);
			if (tmpSol.getObj() < solValue) {
				solValue = tmpSol.getObj();
				this.Solution = std::copy(tmpSol.Solution.begin(), tmpSol.Solution.end(), this.Solution.begin());
			}
			else {
				if ((((double)(std::abs(rand()))) / ((double)RAND_MAX)) <= exp((solValue - tmpSol.getObj()) / T)) {
					solValue = tmpSol.getObj();
					this.Solution = std::copy(tmpSol.Solution.begin(), tmpSol.Solution.end(), this.Solution.begin());
				}
			}
			temp *= 0.99;
		}
	}
}

int factiorielle(int n) {
	int res = 1;
	for (int i = 2; i <= n; i++) {
		res *= i;
	}
	return res;
}

vector<SMSSDTSolution> getNeighbors(SMSSDTSolution s) {
	vector<SMSSDTSolution> result;
	result.resize(factorielle(N) / (2 * factorielle(N - 2)));
	int i = 0;
	for (int j = 0; j < N - 1; j++) {
		for (int k = j + 1; k < N; k++) {
			result[i] = new SMSSDTSolution(N);
			std::copy(s.Solution.begin(), s.Solution.end(), result[i].Solution.begin());
			int tmp = result[i].Solution[j];
			result[i].Solution[j] = result[i].Solution[k];
			result[i].Solution[k] = tmp;
			i++;
		}
	}
	return result;
}

bool contains(vector<SMSSDTSolution> sols, SMSSDTSolution s) {
	for (SMSSDTSolution sol : sols) {
		if (std::equal(sol.Solution.begin(), sol.Solution.end(), s.Solution.begin())) {
			return true;
		}
	}
	return false;
}

void taboue(SMSSDTProblem *prob) {
	if (N > 1) {
		SMSSDTSolution tmpSol = this;
		std::queue<SMSSDTSolution> tabous;
		tabous.push(this);
		Tools::Evaluer(prob, this);
		double solValue = this.getObj();
		int i = 0;
		while (solValue > 0 && i <= N) {
			i++;
			vector<SMSSDTSolution> neighbors = getNeighbors(tmpSol);
			tmpSol = neighbors[0];
			for (int j = 1; j < neighbors.size; j++) {
				if (!contains(tabous, neighbors[j])) {
					Tools::Evaluer(prob, neighbors[j]);
					if (neighbors[j].getObj < tmpSol.getObj()) {
						tmpSol = neighbors[j];
					}
				}
			}
			if (tmpSol.getObj() < this.getObj()) {
				std::copy(tmpSol.Solution.begin(), tmpSol.Solution.end(), this.Solution.begin());
				this.setObj(tmpSol.getObj());
			}
			tabous.push(tmpSol);
			if (tabous.size > N / 10) {
				tabous.pop();
			}
		}
	}
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





#endif  //__SMSSDTPROBLEM_CPP