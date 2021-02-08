#ifndef __SMRDSSOLUTION_CPP
#define __SMRDSSOLUTION_CPP

#include "SMRDSProblem.h"
#include <cmath>
#include <conio.h>
using namespace std;

/**
* Constructeur
*/
SMRDSProblem::SMRDSProblem(char* Fichier) {
	Import(Fichier);
}

/**
* Destructeur
*/
SMRDSProblem::~SMRDSProblem() {
	d.clear();
	depart.clear();
	p.clear();
	for (int i = 0; i < N; i++)
		s[i].clear();
	s.clear();
}

/**
 * Import(char* FileName)
 * Importation des donn�es allant servir � alimenter le probl�me
 * @param FileName : Nom du fichier dans lequel sont les donn�es relatives au probl�me
 * Cr�ation (22 novembre 2007) Aymen SIoud
**/
void SMRDSProblem::Import(char* FileName) {
	std::vector < int >  vChaine;
	ifstream fich(FileName, ios::in);
	if (!fich) {// Validation de l'ouverture du fichier.
		cerr << "Erreur lors de l'ouverture du fichier " << endl;
	}
	else
	{
		while (!fich.eof())
		{
			int  Tampon;
			fich >> Tampon;
			vChaine.push_back(Tampon);
		}
		strcpy_s(Nomfichier, FileName);
		fich.clear();
		fich.close();
		// Affectation des donnees
		// Number of job
		N = vChaine[0];
		int i;
		// Processing times
		for (i = 3; i < 3 + N; i++) {
			p.push_back(vChaine[i]);			
		}
		// Due-date times
		for (i = 3 + N; i < 3 + (2 * N); i++) {
			d.push_back(vChaine[i]);
		}
		// Depart
		for (i = 3 + (2 * N); i < 3 + (3 * N); i++) 
		{
			depart.push_back(vChaine[i]);
		}

		// Setup times
		s.resize(N);
		for (i = 0; i < (short)s.size(); i++)
			s[i].resize(N);
		i = 3 + (3 * N);
		for (unsigned short j = 0; j < N; j++) {
			for (unsigned short k = 0; k < N; k++) {
				s[j][k] = vChaine[i];
				i++;
			}
		}
	}
	vChaine.clear();

}

/**
* printing...
**/
void SMRDSProblem::printOn(ostream& os)
{
	int i, j;
	os << "Nom du fichier  : " << Nomfichier << endl << endl;
	os << " N = " << N << endl;
	os << "*** Processing times" << endl;
	for (j = 0; j < N; j++)
	{
		os << p[j] << " ";
	}
	os << endl << endl;
	os << "*** due-dates" << endl;
	for (j = 0; j < N; j++)
	{
		os << d[j] << " ";
	}
	os << endl << endl;

	os << "*** depart" << endl;
	for (j = 0; j < N; j++)
	{
		os << depart[j] << " ";
	}
	os << endl << endl;
	os << "*** Setup times" << endl;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			os << s[i][j] << " ";
		}
		os << endl;
	}
	os << endl << endl;
}


#endif  //__SMRDSPROBLEM_CPP