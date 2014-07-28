/****************************************************************/
/*                  Objectif de l'algo g�n�tique                */
/*                                                              */
/****************************************************************/

#include <stdio.h> 
#include <math.h> 
#include <string.h> 
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include "Objectif.h"

using namespace std;

       
       
              

               
       // fonctions intervenant dans le calcul des puits
       double Objectif::quotientUn(int i, int j)
       {
              return ((i+0.5)/j);
       }
       
       double Objectif::quotientDeux(int i, int j)
       {
              return (1-(i+0.5)/j);
       }
       
       // Puit feuille                      
       double Objectif::Puitf(int nn)
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
       double Objectif::Puitp(int n)
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
       double Objectif::Puite(int n)
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
       double Objectif::Puitepi(int n)
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
       double Objectif::Puitfleur(int n)
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
       int Objectif::Ksi(int n)
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
       double Objectif::dem(int n)
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
       void Objectif::vdem()
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
      /* void initEnv()
       {
               for(i=1;i<34;i++)
               {
                                W[i] = 1;
               }
       }*/

       //r�cup�ration du g�nome et allocation en vecteur d'environnement
       void Objectif::recupgenome(double* X)
       {
	       for(int i=1;i<34;i++)
	       { 
		       W[i]=X[i];
               }
       }
       
       // cr�ation du vecteur donnant l'influence de l'environnement sur la biomasse
       void Objectif::Env()
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
       double Objectif::Biomasse()
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
       double Objectif::sommeFeuilles(int n)
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
       double Objectif::masse(int n)
       {
              vdem();
	      Env();
	      Biomasse();
	      som = 0;
              Rho = 1;
              for(jj=1;jj<n+1;++jj)
              {
                      som = som + Puitepi(jj-15)*Q[jj-1]*Rho/D[jj];
                      //cout << "la contribution du cycle " << jj << " a la masse de l'epi est " << Puitepi(jj-15)*Q[jj-1]*Rho/D[jj] << endl;
              }
              return som;
       }
                               


	//calcul de la masse de l'�pi en fin de croissance
	double Objectif::masseepi()
	{
		vdem();
		Env();
		Biomasse();
		som = 0;
		Rho = 1;
		for(jj=1;jj<34;++jj)
		{
			som = som + Puitepi(jj-15)*Q[jj-1]*Rho/D[jj];
		}
		return som;
	}
              
                            
                            
       
              


/*int main(){
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
    Objectif obj;
//    obj.vdem();
//    obj.initEnv();
//    obj.Env();
//    cout << "la somme des Q vaut " << aaa.Biomasse() << endl;
//    cout << "la masse de l'epi vaut " << aaa.masse(33) << endl;
    //aaa.vdem();
//    aaa.initEnv();
//    aaa.Env();
//    aaa.Biomasse();
//    cout << "La masse de l'epi au cycle 33 est de " << aaa.masse(33) << endl;
//    system("pause");
    return 0;
}*/
