/****************************************************************/
/*                           Calculs	                        */
/*                                                              */
/****************************************************************/

#include <stdio.h> 
#include <math.h> 
#include <string.h> 
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
typedef vector<double> vec;
typedef vector < vector<double> > mat;
typedef vector < vector < vector<double> >  > mat3d;

class Calculs
{
       
       // Déclaration des variables de calculs
       
       /////////////////////
       //VARIABLES COURANTES
       /////////////////////
       
       int i, j, k, l, n, m, u, v, w, kk, jj, ll, mm, nn;
       
       // intermédiaires de calculs
       double aa;
       double bb;
       double cc;
       double dd;
       double sortie;
       double som, somf, somp, some, sommef, somm, somee, spe;
       mat mat_int;
       mat MM;
       vec V, VV, AA, BB, CC;
       
       
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
       
       // variables intervenant dans le calcul du gradient
       vec G; // gradient du poids de l'épi par rapport à l'environnement
       mat Z; // matrice des états adjoints du système
       mat dGdU; // matrice dérivée du poids par rapport à l'environnement
       mat dGdX; // matrice dérivée du poids par rapport à la biomasse
       mat dFdU; // matrice dérivée de la biomasse par rapport à l'environnement
       mat dFdX; // matrice dérivée de la biomasse par rapport à la biomasse
       mat3d dSdX; // tenseur de dimension 3 dérivé de la surface des feuilles par rapport à la biomasse
       mat Id; // matrice identité (34*34)
       
       ///////////////////////////
       //Déclaration des fonctions
       ///////////////////////////
       
       public :
              
       Calculs()
       {
               D = new double[34];
               W = new double[34];
               U = new double[34];
               C = new double[34];
               Q = new double[34];
               E = new double[34];
               S = new double[396]; // 12*33
               
               // Paramètres de la feuille
               Tf = 12;
               alphaf = 2;
               betaf = 3;
               Pf = 1;
               
               // Paramètres du pétiole
               Tp = 12;
               alphap = 2;
               betap = 3;
               Pp = 0.8;
               
               // Paramètres de l'entrenoeud
               Te = 12;
               alphae = 5;
               betae = 5;
               Pe = 12;
               
               // Paramètres de l'épi
               Tepi = 19;
               alphaepi = 10;
               betaepi = 5;
               Pepi = 500;
               TappEpi = 15;
               
               // Paramètres de la fleur
               Tfleur = 2;
               alphafleur = 1;
               betafleur = 1;
               Pfleur = 8;
               TappFleur = 22;
               
               // Paramètres de l'environnement 
               K = 1;
               Wmin = 0.5;
               Wmax = 1;
               
               // Paramètres de la plante
               Sp = 125600;
               e = 0.028;
               reserve = 1;
               R = 17;
               Rho = 1;
               
       }
       
       ~Calculs()
       {
               delete D;
               delete W;
               delete U;
               delete C;
               delete Q;
               delete E;
               delete S;
               delete G;
               dFdX.clear();
               dGdX.clear();
               dFdU.clear();
               dGdU.clear();
               dSdX.clear();
               mat_int.clear();
               MM.clear();
               V.clear();
               VV.clear();
               AA.clear();
               BB.clear();
               CC.clear();
               Id.clear();
               G.clear();
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
       void initEnv();
              
       // création du vecteur donnant l'influence de l'environnement sur la biomasse
       void Env();
              
       // création du vecteur biomasse
       void Biomasse();
            
       // création de la somme des surfaces des feuilles intervenant dans le calcul de la biomasse                        
       double sommeFeuilles(int n);
              
       // calcul de la masse de l'épi
       double masse(int n);
              
       ////////////////////
       //Calcul du gradient
       ////////////////////
       
       // Dimensionnement et initialisation des matrices
       void initmat();
       
       // Calcul de la matrice dérivée du poids par rapport à l'environnement
       void construction_dGdU();
       
       // Calcul de la matrice dérivée du poids par rapport à la biomasse
       void construction_dGdX();
       
       // Calcul de la matrice dérivée de la biomasse par rapport à l'environnement
       void construction_dFdU();
       
       // Calcul de la matrice dérivée de la biomasse par rapport à la biomasse
       void construction_dFdX();
       
       // Calcul du tenseur dérivée de la surface des feuilles à un cycle donné par rapport à la biomasse
       void construction_dSdX();
       
       // fonction transposant une matrice
       void transposition(mat &mm);
       
       // fonction retournant le produit d'une matrice et d'un vecteur
       vec produit(mat MM, vec V);
       
       // création des états adjoints
       void construction_adjoints();
       
       // Construction du gradient du poids de l'épi
       void construction_gradient();
       
       
};
