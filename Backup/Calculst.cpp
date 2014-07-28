/****************************************************************/
/*                           Objectif	                        */
/*                                                              */
/****************************************************************/

#include "Objectift.h"
     
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

// Puit pétiole
double Objectif::Puitp(int n)
{
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

// Puit épi
double Objectif::Puitepi(int n)
{
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

// Puit fleur mâle
double Objectif::Puitfleur(int n)
{
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

// fonction Ksi : fonction traduisant l'arrêt de la croissance des organes après le 22 ème
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
      some = 0; somf = 0; somp = 0;
      for (jj=1;jj<n+1;jj++)
      {
          some = some + Ksi(jj)*Puite(n-jj);
          somp = somp + Ksi(jj)*Puitp(n-jj);
          somf = somf + Ksi(jj)*Puitf(n-jj);
      }
      return (some + somf + somp + Puitepi(n-TappEpi) + Puitfleur(n-TappFleur));
}

// création du vecteur de demande totale
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
void Objectif::initEnv()
{
       for(i=1;i<34;i++)
       {
                        W[i] = 1;
       }
} 

// création du vecteur donnant l'influence de l'environnement sur la biomasse
void Objectif::Env()
{
      for(i=1;i<34;i++)
      {
                       E[i] = K*(W[i]-Wmin)/(Wmax-Wmin);
      }
}

// création du vecteur biomasse
void Objectif::Biomasse()
{
      Q[0] = reserve;
      //spe = 0;
      for(kk=1;kk<34;++kk)
      {
                     sommef = sommeFeuilles(kk);
                     Q[kk] = (E[kk]/R)*Sp*(1 - exp(-sommef/Sp));
                     //spe = spe + Q[kk];
                     //cout << "la quantite de biomasse Q creee au cycle " << kk << " vaut " << Q[kk] << endl;
      }
}

// création de la somme des surfaces des feuilles intervenant dans le calcul de la biomasse                        
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

// calcul de la masse de l'épi
double Objectif::masse(int n)
{
      som = 0;
      for(jj=1;jj<n+1;++jj)
      {
              som = Puitepi(jj-15)*Q[jj-1]*Rho/D[jj];
              //cout << "la contribution du cycle " << jj << " a la masse de l'epi est " << Puitepi(jj-15)*Q[jj-1]*Rho/D[jj] << endl;
      }
      return som;
}

//calcul de la masse de l'épi en fin de croissance
double Objectif::masseepi()
{
	vdem();
	Env();
	Biomasse();
	som=0;
	Rho=1;
	for(jj=1;jj<34;++jj)
                {
                        som = som + Puitepi(jj-15)*Q[jj-1]*Rho/D[jj];
                }
         return som;
}


////////////////////
//Calcul du gradient
////////////////////

// Dimensionnement et initialisation des matrices
void Objectif::initmat()
{
       dGdU.resize(34);
       dGdX.resize(34);
       dFdU.resize(34);
       dFdX.resize(34);
       dSdX.resize(34);
       Id.resize(34);
       mat_int.resize(34);   // mat_int : matrice servant d'intermédiaire pour la transposition
       for(u=0;u<mat_int.size();u++)
       {
               mat_int[u].resize(34);
       }
       for(u=0;u<Id.size();u++)
       {
               Id[u].resize(34);
       }
       for(i=0;i<dGdU.size();i++)
       {
               dGdU[i].resize(34);
       }
       for(i=0;i<dGdX.size();i++)
       {
               dGdX[i].resize(34);
       }
       for(i=0;i<dFdU.size();i++)
       {
               dFdU[i].resize(34);
       }
       for(i=0;i<dFdX.size();i++)
       {
               dFdX[i].resize(34);
       }
       for(i=0;i<dSdX.size();i++)
       {
               dSdX[i].resize(12);
       }
       for(i=0;i<dSdX.size();i++)
       {
               for(j=0;j<dSdX[i].size();j++)
               {
                       dSdX[i][j].resize(34);
               }
       }
       for(i=0;i<dFdU.size();i++)
       {
               for(j=0;j<dFdU[i].size();j++)
               {
                        dGdU[i][j] = 0;
                        dGdX[i][j] = 0;
                        dFdU[i][j] = 0;
                        dFdX[i][j] = 0;
                        mat_int[i][j] = 0;
               }
       }
       for(i=0;i<dFdU.size();i++)
       {
               Id[i][i] = 1;
       }
       for(i=0;i<dSdX.size();i++)
       {
               for(j=0;j<dSdX[i].size();j++)
               {
                       for(k=0;k<dSdX[i][j].size();k++)
                       {
                                dSdX[i][j][k] = 0;
                       }
               }
       }
}

// Calcul de la matrice dérivée du poids par rapport à l'environnement
void Objectif::construction_dGdU()
{
       for(j=1;j<34;j++)
       {
              dGdU[j][j] = Rho*Puitepi(j-TappEpi)*K*Sp*(1-exp(-(sommeFeuilles(j))/Sp))/(D[j]*R*(Wmax-Wmin));
       }      
}                      

// Calcul de la matrice dérivée du poids par rapport à la biomasse
void Objectif::construction_dGdX()
{
       for(j=2;j<34;j++)
       {
              dGdX[j][j-1] = Rho*Puitepi(j-TappEpi)/(D[j]);
       }
}
       
// Calcul de la matrice dérivée de la biomasse par rapport à l'environnement
void Objectif::construction_dFdU()
{
       for (u=1;u<34;u++)
       {
                dFdU[u][u] = K*Sp*(1-exp(-sommeFeuilles(u)/Sp))/(R*(Wmax-Wmin));
       }
}
                
// Calcul du tenseur dérivée de la surface des feuilles à un cycle donné par rapport à la biomasse
void Objectif::construction_dSdX()
{
       for(u=1;u<34;u++)                       // cycles
       {
               for(v=0;v<12;v++)               // âge des feuilles
               {
                         for(w=1;w<34;w++)     // variable de dérivation (Q(j))
                         {         
                                   if(w<u)
                                   {
                                            dSdX[u][v][w] = Ksi(u-v)*Puitf(w+1-(u-v))/(e*D[w+1]);
                                   }         
                         }
               }
       }
}

// Calcul du vecteur dérivée de la biomasse par rapport à la biomasse
void Objectif::construction_dFdX()
{
       for(u=1;u<34;u++)
       {
               for(w=1;w<34;w++)
               {
                        sommef = 0;
                        for(v=0;v<12;v++)
                        {
                                 sommef = sommef + dSdX[u][v][w];
                        }
                        dFdX[u][w] = E[u]*sommef*exp(-sommeFeuilles(u)/Sp)/R;
                        //cout << dFdX[u][w] << endl;
               }
       }
}

// fonction transposant une matrice
void Objectif::transposition(mat &MM)
{
       for(u=0;u<33;u++)
       {
               for(v=u+1;v<34;v++)
               {
                        mat_int[v][u] = MM[u][v]; 
                        mat_int[u][v] = MM[v][u];
                        MM[u][v] = mat_int[u][v]; 
                        MM[v][u] = mat_int[v][u];       
               }
       }
}

// fonction retournant le produit d'une matrice et d'un vecteur
vec Objectif::produit(mat MM, vec V)
{
       VV.resize(MM.size());
       for(kk=0;kk<MM.size();kk++)
       {
               som = 0;
               for(ll=0;ll<V.size();ll++)
               {
                       som = som+MM[kk][ll]*V[ll];
               }
               VV[kk] = som;
       }
       return VV;
}

// création des états adjoints
void Objectif::construction_adjoints()
{
       transposition(dGdU);
       transposition(dGdX);
       transposition(dFdU);
       transposition(dFdX);
       Z.resize(34);
       for(i=0;i<Z.size();i++)                               // initialisation de Z
       {                                                     //
               Z[i].resize(34);                              //
       }                                                     //
       for(i=0;i<Z.size();i++)                               //
       {                                                     //
               for(j=0;j<Z[i].size();j++)                    //
               {                                             //
                       Z[i][j] = 0;                          //
               }                                             //
       }                                                     //
       for(i=0;i<Id.size();i++)
       {
               for(j=0;j<Id[i].size();j++)
               {
                        dFdX[i][j] = dFdX[i][j] + Id[i][j];
               }
       } 
       for(i=32;i>-1;i--)
       {
               for(j=0;j<dFdX[0].size();j++)
               {
                        AA = produit(dFdX,Z[i+1]);
                        Z[j][i] = AA[j]-dGdX[j][i+1];
               }
       }              
}

// Construction du gradient du poids de l'épi
void construction_gradient()
{
       jj





     
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
//        Objectif aaa;
//        myfile << i << "  " << aaa.dem(i)<< endl;
//    }
//    myfile.close();
//  }
//  else {cout << "Unable to open file";}
    /*Objectif aaa;
    aaa.vdem();
    aaa.initEnv();
    aaa.Env();
    aaa.Biomasse();
    aaa.initmat();
    aaa.construction_dGdU();
    aaa.construction_dGdX();
    aaa.construction_dSdX();
    aaa.construction_dFdX();
    aaa.construction_adjoints();
    //cout << "la somme des Q vaut " << aaa.Biomasse() << endl;
    //cout << "la masse de l'epi vaut " << aaa.masse(33) << endl;
    system("pause");
    return 0;*/
}
