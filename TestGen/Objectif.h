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
       
       // Déclaration des variables de calculs
       
       /////////////////////
       //VARIABLES COURANTES
       /////////////////////
       
       int i, j, k, l, n, m, kk, jj, ll, mm, nn;
       
       // intermédiaires de calculs
       double aa;
       double bb;
       double cc;
       double dd;
       double sortie;
       double som, somf, somp, some, sommef, somm, somee, spe;
       
       // Temps d'expansion des différents organes
       int Tf;
       int Tp;
       int Te;
       int Tepi;
       int Tfleur;
       
       // Temps d'apparition des différents organes
       int TappEpi;
       int TappFleur;
       
       // Puits des différents organes
       double Pf;
       double Pp; 
       double Pe;
       double Pepi;
       double Pfleur;
       
       // alpha des différents organes
       float alphaf;
       float alphap; 
       float alphae;
       float alphaepi;
       float alphafleur;
       
       // bêta des différents organes
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
       double K; // constante de proportionnalité de l'environnement
       
       // vecteur irrigation
       double* U;
       
       // vecteur consommation
       double* C;
       
       // vecteur biomasse
       double* Q;
       double reserve; // reserve de biomasse contenue dans la graine
       
       // feuilles
       double* S; // tableau donnant toutes les surfaces des feuilles actives à un cycle donné
       double Sp; // paramètre intervenant dans la création de biomasse
       double e; // "masse volumique" de la feuille
       double R; // résistance de la feuille
      
       // épi
       double Rho; // "masse volumique" de l'épi
       
       // gradient du poids de l'epi
       double* G;
       
       // etat adjoint
       double* Z;
       
       ///////////////////////////
       //Déclaration des fonctions
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
              
       // Puit pétiole
       double Puitp(int n);
              
       // Puit entrenoeud
       double Puite(int n);
              
       // Puit épi
       double Puitepi(int n);
              
       // Puit fleur mâle
       double Puitfleur(int n);
              
       // fonction Ksi : fonction traduisant l'arrêt de la croissance des organes après le 22 ème
       // cycle
       int Ksi(int n);
              
       // calcul de la demande totale au cycle n
       double dem(int n);
              
       // création du vecteur de demande totale
       void vdem();
              
       // initialisation du vecteur environnement
       //void initEnv();

       // recupération du génome et allocation en vecteur W
       void recupgenome(double* X);
                     
       // création du vecteur donnant l'influence de l'environnement sur la biomasse
       void Env();
              
       // création du vecteur biomasse
       double Biomasse();
            
       // création de la somme des surfaces des feuilles intervenant dans le calcul de la biomasse                        
       double sommeFeuilles(int n);
              
       // calcul de la masse de l'épi au cycle n
       double masse(int n);
       
       //calcul de la masse finale de l'épi
       double masseepi();
              
  
       
       
       
       
};

#endif
