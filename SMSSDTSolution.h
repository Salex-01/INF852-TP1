#pragma once
#ifndef __SMSSDTSOLUTION_H
#define __SMSSDTSOLUTION_H
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "SMSSDTProblem.h"

using namespace std;

class SMSSDTSolution
{
protected:
	double FctObj;

public:
	SMSSDTProblem* LeProb;
	vector<int > Solution;
	vector<int > CT;
	vector<int > TT;
	vector<int > ST;
	vector <vector<int>> voisinage;
	
	/**
	 * SMSSDTSolution()
	 * Constructeur de la classe
	**/
	SMSSDTSolution(int N) {
		Solution.resize(N);
		TT.resize(N);
		CT.resize(N);
		ST.resize(N);
		FctObj = -1;

	};

	/**
	 * SMSSDTSolution(int N)
	 * Constructeur de la classe
	 * Assigne les valeurs al�atoires initiales � la solution
	**/
	SMSSDTSolution(int N, bool test, SMSSDTProblem* probleme);
	SMSSDTSolution(int N, char methode);
	
	/* Destructeur*/
	~SMSSDTSolution();

	void descenteVoisinage(int N);
	void algoDescente();
	/**
	 * Save
	 * Fonction permettant d'�crire la solution dans un flux
	 * @param Stream : Flux dans lequel on doit �crire
	**/
	ostream& Save(ostream& Stream);

	
	/**  definition des accesseurs **/

	/* Retourne la valeur de l'objectif */
	double getObj() {
		return FctObj;
	}

	
	void setObj(double obj) {
		FctObj = obj;
	}
};




#endif
