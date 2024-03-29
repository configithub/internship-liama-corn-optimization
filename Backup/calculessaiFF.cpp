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

using namespace std;

class Calculs{
       
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
       
       ///////////////////////////
       //D�claration des fonctions
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
               S = new double[396];
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
       }
               
       // fonctions intervenant dans le calcul des puits
       double quotientUn(int i, int j)
       {
              return ((i+0.5)/j);
       }
       
       double quotientDeux(int i, int j)
       {
              return (1-(i+0.5)/j);
       }
       
       // Puit feuille                      
       double Puitf(int nn)
       {
              Tf = 12;
              alphaf = 2;
              betaf = 3;
              Pf = 1;
              if ((nn<0)|(nn>(Tf - 1)))
              {
                  return 0;
              }
              else
              {
                  aa = pow(quotientUn(nn,Tf),alphaf-1);
                  bb = pow(quotientDeux(nn,Tf),betaf-1);
                  som = 0;
                  for (i=0;i<Tf;++i)
                  {
                      cc = pow(quotientUn(i,Tf),alphaf-1);
                      dd = pow(quotientDeux(i,Tf),betaf-1);
                      som = som + cc*dd;
                  }
                  sortie = (Pf*aa*bb)/som;
              } 
              return sortie;
       }
       
       // Puit p�tiole
       double Puitp(int n)
       {
              Tp = 12;
              alphap = 2;
              betap = 3;
              Pp = 0.8;
              if ((n<0)|(n>(Tp - 1)))
              {
                  return 0;
              }
              else
              {
                  aa = pow(quotientUn(n,Tp),alphap-1);
                  bb = pow(quotientDeux(n,Tp),betap-1);
                  som = 0;
                  for (i=0;i<Tp;++i)
                  {
                      cc = pow(quotientUn(i,Tp),alphap-1);
                      dd = pow(quotientDeux(i,Tp),betap-1);
                      som = som + cc*dd;
                  }
                  sortie = (Pp*aa*bb)/som;
              } 
              return sortie;
       }
       
       // Puit entrenoeud
       double Puite(int n)
       {
              Te = 12;
              alphae = 5;
              betae = 5;
              Pe = 12;
              if ((n<0)|(n>(Te - 1)))
              {
                  return 0;
              }
              else
              {
                  aa = pow(quotientUn(n,Te),alphae-1);
                  bb = pow(quotientDeux(n,Te),betae-1);
                  som = 0;
                  for (i=0;i<Te;++i)
                  {
                      cc = pow(quotientUn(i,Te),alphae-1);
                      dd = pow(quotientDeux(i,Te),betae-1);
                      som = som + cc*dd;
                  }
                  sortie = (Pe*aa*bb)/som;
              } 
              return sortie;
       }
       
       // Puit �pi
       double Puitepi(int n)
       {
              Tepi = 19;
              alphaepi = 10;
              betaepi = 5;
              Pepi = 500;
              if ((n<0)|(n>(Tepi - 1)))
              {
                  return 0;
              }
              else
              {
                  aa = pow(quotientUn(n,Tepi),alphaepi-1);
                  bb = pow(quotientDeux(n,Tepi),betaepi-1);
                  some = 0;
                  for (i=0;i<Tepi;++i)
                  {
                      cc = pow(quotientUn(i,Tepi),alphaepi-1);
                      dd = pow(quotientDeux(i,Tepi),betaepi-1);
                      some = some + cc*dd;
                  }
                  sortie = (Pepi*aa*bb)/some;
              } 
              return sortie;
       }
       
       // Puit fleur m�le
       double Puitfleur(int n)
       {
              Tfleur = 2;
              alphafleur = 1;
              betafleur = 1;
              Pfleur = 8;
              if ((n<0)|(n>(Tfleur - 1)))
              {
                  return 0;
              }
              else
              {
                  aa = pow(quotientUn(n,Tfleur),alphafleur-1);
                  bb = pow(quotientDeux(n,Tfleur),betafleur-1);
                  som = 0;
                  for (i=0;i<Tfleur;++i)
                  {
                      cc = pow(quotientUn(i,Tfleur),alphafleur-1);
                      dd = pow(quotientDeux(i,Tfleur),betafleur-1);
                      som = som + cc*dd;
                  }
                  sortie = (Pfleur*aa*bb)/som;
              } 
              return sortie;
       }
       
       // fonction Ksi : fonction traduisant l'arr�t de la croissance des organes apr�s le 22 �me
       // cycle
       int Ksi(int n)
       {
           if ((n<1)|(n>22))
           {
               return 0;
           }
           else
           {
               return 1;
           }
       }
       
       // calcul de la demande totale au cycle n
       double dem(int n)
       {
              TappEpi = 15;
              TappFleur = 22;
              some = 0; somf = 0; somp = 0;
              for (jj=1;jj<n+1;jj++)
              {
                  some = some + Ksi(jj)*Puite(n-jj);
                  somp = somp + Ksi(jj)*Puitp(n-jj);
                  somf = somf + Ksi(jj)*Puitf(n-jj);
              }
              return (some + somf + somp + Puitepi(n-TappEpi) + Puitfleur(n-TappFleur));
       }
       
       // cr�ation du vecteur de demande totale
       void vdem()
       {
              //cout << dem(0)<<endl;
              for(k=0;k<34;k++)
              {
                               D[k] = dem(k);
                               //cout << deman[k] << "  " << k << endl;
                              // system("pause");
              }
       }
       
       // initialisation du vecteur environnement
       void initEnv()
       {
               for(i=1;i<34;i++)
               {
                                W[i] = 1;
               }
       } 
       
       // cr�ation du vecteur donnant l'influence de l'environnement sur la biomasse
       void Env()
       {
              K = 1;
              Wmin = 0.5;
              Wmax = 1;
              for(i=1;i<34;i++)
              {
                               E[i] = K*(W[i]-Wmin)/(Wmax-Wmin);
              }
       }
       
       // cr�ation du vecteur biomasse
       double Biomasse()
       {
              reserve = 1;
              R = 17;
              Q[0] = reserve;
              Sp = 125600;
              e = 0.028;
              spe = 0;
              for(kk=1;kk<34;++kk)
              {
                             sommef = sommeFeuilles(kk);
                             Q[kk] = (E[kk]/R)*Sp*(1 - exp(-sommef/Sp));
                             spe = spe + Q[kk];
                             //cout << "la quantite de biomasse Q creee au cycle " << kk << " vaut " << Q[kk] << endl;
              }
              return spe;
       }
     
       // cr�ation de la somme des surfaces des feuilles intervenant dans le calcul de la biomasse                        
       double sommeFeuilles(int n)
       {
              for(l=0;l<12;++l)
              {
                   somm = 0;
                   for(m=1;m<n+1;++m)
                   {
                        somm = somm + Puitf(m-(n-l))*Q[m-1]/(e*D[m]);
                   }
              S[12*(n-1)+l] = Ksi(n-l)*somm;
              }
              somee = 0;
              for(i=0;i<12;++i)
              {
                               somee = somee + S[12*(n-1)+i];
              }
              //cout << "la somme des surfaces des feuilles au cycle " << n << " vaut " << somee << endl;
              return somee;
       }
       
       // calcul de la masse de l'�pi
       double masse(int n)
       {
              som = 0;
              Rho = 1;
              for(jj=1;jj<n+1;++jj)
              {
                      som = som + Puitepi(jj-15)*Q[jj-1]*Rho/D[jj];
                      //cout << "la contribution du cycle " << jj << " a la masse de l'epi est " << Puitepi(jj-15)*Q[jj-1]*Rho/D[jj] << endl;
              }
              return som;
       }
                               


       
              
                            
                            
       
              
};

void affiche(double* t, int n)
       {
            int i;         
            for(i=0;i<n;++i)
            {
                  cout << t[i] << endl;
            }

       }

int main(){
//    int i;
//    ofstream myfile ("demande.dat");
//  if (myfile.is_open())
//  {
//    myfile << "#Evolution de la demande de la plante \n";
//    for (i=1;i<34;++i)
//    {
//        Calculs aaa;
//        myfile << i << "  " << aaa.dem(i)<< endl;
//    }
//    myfile.close();
//  }
//  else {cout << "Unable to open file";}
    Calculs aaa;
    aaa.vdem();
    aaa.initEnv();
    aaa.Env();
    cout << "la somme des Q vaut " << aaa.Biomasse() << endl;
    cout << "la masse de l'epi vaut " << aaa.masse(33) << endl;
    //aaa.vdem();
//    aaa.initEnv();
//    aaa.Env();
//    aaa.Biomasse();
//    cout << "La masse de l'epi au cycle 33 est de " << aaa.masse(33) << endl;
    system("pause");
    return 0;
}
