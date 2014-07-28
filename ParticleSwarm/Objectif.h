/****************************************************************/
/*                           Objectif	                        */
/*                                                              */
/****************************************************************/

#ifndef _OBJECTIF_H_
#define _OBJECTIF_H_

#include <stdio.h> 
#include <math.h> 
#include <string.h> 
#include <stdlib.h> 
#include <iostream>
#include <fstream>

using namespace std;

class Objectif
{
       
       // D�claration des variables de calculs
       
       /////////////////////
       //VARIABLES COURANTES
       /////////////////////
       
       int i, j, k, l, n, m, kk, jj, ll, mm, nn;
       
       // interm�diaires de calculs
       double aa;
       double bb;
       double cc;
       double dd;
       double sortie;
       double som, somf, somp, some, sommef, somm, somee, spe;
       
       // Temps d'expansion des diff�rents organes
       int Tf;
       int Tp;
       int Te;
       int Tepi;
       int Tfleur;
       
       // Temps d'apparition des diff�rents organes
       int TappEpi;
       int TappFleur;
       
       // Puits des diff�rents organes
       double Pf;
       double Pp; 
       double Pe;
       double Pepi;
       double Pfleur;
       
       // alpha des diff�rents organes
       float alphaf;
       float alphap; 
       float alphae;
       float alphaepi;
       float alphafleur;
       
       // b�ta des diff�rents organes
       float betaf;
       float betap; 
       float betae;
       float betaepi;
       float betafleur;
       
       // vecteur demande
       double* D ;
       
       // vecteur environnement
       double* W;
       double* E;
       double Wmin; // environnement min
       double Wmax; // environnement max
       double K; // constante de proportionnalit� de l'environnement
       
       // vecteur irrigation
       double* U;
       
       // vecteur consommation
       double* C;
       
       // vecteur biomasse
       double* Q;
       double reserve; // reserve de biomasse contenue dans la graine
       
       // feuilles
       double* S; // tableau donnant toutes les surfaces des feuilles actives � un cycle donn�
       double Sp; // param�tre intervenant dans la cr�ation de biomasse
       double e; // "masse volumique" de la feuille
       double R; // r�sistance de la feuille
      
       // �pi
       double Rho; // "masse volumique" de l'�pi
       
       // gradient du poids de l'epi
       double* G;
       
       // etat adjoint
       double* Z;
       
       ///////////////////////////
       //D�claration des fonctions
       ///////////////////////////
       
       public :
              
       Objectif()
       {
               D = new double[34];
               W = new double[34];
               U = new double[34];
               C = new double[34];
               Q = new double[34];
               E = new double[34];
               S = new double[396];
               Z = new double[34];
               G = new double[34];
       }
       
       ~Objectif()
       {
               delete[] D;
               delete[] W;
               delete[] U;
               delete[] C;
               delete[] Q;
               delete[] E;
               delete[] S;
	       delete[] Z;
	       delete[] G;
       }
               
       // fonctions intervenant dans le calcul des puits
       double quotientUn(int i, int j);      
       double quotientDeux(int i, int j);
       
       // Puit feuille                      
       double Puitf(int nn);
              
       // Puit p�tiole
       double Puitp(int n);
              
       // Puit entrenoeud
       double Puite(int n);
              
       // Puit �pi
       double Puitepi(int n);
              
       // Puit fleur m�le
       double Puitfleur(int n);
              
       // fonction Ksi : fonction traduisant l'arr�t de la croissance des organes apr�s le 22 �me
       // cycle
       int Ksi(int n);
              
       // calcul de la demande totale au cycle n
       double dem(int n);
              
       // cr�ation du vecteur de demande totale
       void vdem();
              
       // initialisation du vecteur environnement
       //void initEnv();

       // recup�ration du g�nome et allocation en vecteur W
       void recupgenome(double* X);
                     
       // cr�ation du vecteur donnant l'influence de l'environnement sur la biomasse
       void Env();
              
       // cr�ation du vecteur biomasse
       double Biomasse();
            
       // cr�ation de la somme des surfaces des feuilles intervenant dans le calcul de la biomasse                        
       double sommeFeuilles(int n);
              
       // calcul de la masse de l'�pi au cycle n
       double masse(int n);
       
       //calcul de la masse finale de l'�pi
       double masseepi();
              
  
       
       
       
       
};

#endif
