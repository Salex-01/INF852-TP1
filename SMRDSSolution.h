#pragma once
#ifndef __SMRDSSOLUTION_H
#define __SMRDSSOLUTION_H
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

class SMRDSSolution
{
protected:
	double FctObj;

public:

	vector<int > Solution;
	vector<int > CT;
	vector<int > TT;
	vector<int > ST;

	
	/**
	 * SMRDSSolution()
	 * Constructeur de la classe
	**/
	SMRDSSolution(int N) {
		Solution.resize(N);
		TT.resize(N);
		CT.resize(N);
		ST.resize(N);
		FctObj = -1;

	};

	/**
	 * SMRDSSolution(int N)
	 * Constructeur de la classe
	 * Assigne les valeurs aléatoires initiales à la solution
	**/
	SMRDSSolution(int N, bool test);

	
	/* Destructeur*/
	~SMRDSSolution();

	void recuitSimule(SMRDSProblem* prob);

	void taboue(SMRDSProblem* prob);

	/**
	 * Save
	 * Fonction permettant d'écrire la solution dans un flux
	 * @param Stream : Flux dans lequel on doit écrire
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
