/****************************************************************/
/*                           Calculs	                        */
/*                                                              */
/****************************************************************/

#include "Calculst.h"
     
// fonctions intervenant dans le calcul des puits
double Calculs::quotientUn(int i, int j)
{
      return ((i+0.5)/j);
}

double Calculs::quotientDeux(int i, int j)
{
      return (1-(i+0.5)/j);
}

// Puit feuille                      
double Calculs::Puitf(int nn)
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
double Calculs::Puitp(int n)
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
double Calculs::Puite(int n)
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
double Calculs::Puitepi(int n)
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
double Calculs::Puitfleur(int n)
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
int Calculs::Ksi(int n)
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
double Calculs::dem(int n)
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
void Calculs::vdem()
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
void Calculs::initEnv()
{
       W[0] = 1;
       W[1] = 1;
       W[2] = 1;
       W[3] = 1;
       W[4] = 1;
       W[5] = 1;
       W[6] = 1;
       W[7] = 1;
       W[8] = 1;
       W[9] = 1;
       W[10] = 1;
       W[11] = 1;
       W[12] = 1;
       W[13] = 1;
       W[14] = 1;
       W[15] = 1;
       W[16] = 1;
       W[17] = 1;
       W[18] = 1;
       W[19] = 1;
       W[20] = 1;
       W[21] = 1;
       W[22] = 1;
       W[23] = 1;
       W[24] = 1;
       W[25] = 1;
       W[26] = 1;
       W[27] = 1;
       W[28] = 1;
       W[29] = 1;
       W[30] = 1;
       W[31] = 1;
       W[32] = 1;
       W[33] = 1;
} 

// création du vecteur donnant l'influence de l'environnement sur la biomasse
void Calculs::Env()
{
      for(i=1;i<34;i++)
      {
                       E[i] = K*(W[i]-Wmin)/(Wmax-Wmin);
                       //cout << "L'environnment au cycle " << i << " vaut " << W[i] << endl;
      }
}

// création du vecteur biomasse
void Calculs::Biomasse()
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
double Calculs::sommeFeuilles(int n)
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
double Calculs::masse(int n)
{
      som = 0;
      for(jj=1;jj<n+1;++jj)
      {
              som = som + Puitepi(jj-15)*Q[jj-1]*Rho/D[jj];
              //cout << "la contribution du cycle " << jj << " a la masse de l'epi est " << Puitepi(jj-15)*Q[jj-1]*Rho/D[jj] << endl;
      }
      return som;
}

// initialisation de l'épi temoin
void Calculs::init_temoin()
{
      Temoin.resize(34);
      for(ij=1;ij<34;ij++)
      {
              Temoin[ij] = masse(ij);
      }
}

// retourne les valeurs du témoin
double Calculs::temoin(int j)
{
      return Temoin[j];
}
       
////////////////////
//Calcul du gradient
////////////////////

// Dimensionnement et initialisation des matrices
void Calculs::initmat()
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
void Calculs::construction_dGdU()
{
       for(j=2;j<34;j++)
       {
              dGdU[j][j-1] = Rho*Puitepi(j-TappEpi)*K*Sp*(1-exp(-(sommeFeuilles(j-1))/Sp))/(D[j]*R*(Wmax-Wmin));
       }      
}                      

// Calcul de la matrice dérivée du poids par rapport à la biomasse
void Calculs::construction_dGdX()
{
       for(j=2;j<34;j++)
       {
              dGdX[j][j-1] = Rho*Puitepi(j-TappEpi)/(D[j]);
       }
}
       
// Calcul de la matrice dérivée de la biomasse par rapport à l'environnement
void Calculs::construction_dFdU()
{
       for (u=1;u<34;u++)
       {
                dFdU[u][u] = K*Sp*(1-exp(-sommeFeuilles(u)/Sp))/(R*(Wmax-Wmin));
       }
       //for(j=0;j<35;j++){
//       for(i=0;i<34;i++)
//       {
//                        cout << dFdU[j][i] << " " ;
//       }
//       cout << endl;}     
}
                
// Calcul du tenseur dérivée de la surface des feuilles à un cycle donné par rapport à la biomasse
void Calculs::construction_dSdX()
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
void Calculs::construction_dFdX()
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
void Calculs::transposition(mat &MM)
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
vec Calculs::produit(mat MM, vec V)
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

// création des états adjoints Z
void Calculs::construction_adjoints()
{
       transposition(dGdU);
       transposition(dGdX);
       transposition(dFdU);
       transposition(dFdX);
       Z.resize(35);
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
       for(i=33;i>-1;i--)
       {
               for(j=0;j<dFdX[0].size();j++)
               {
                        AA = produit(dFdX,Z[i+1]);
                        Z[i][j] = AA[j]-dGdX[j][i];
               }
       }
       //for(j=0;j<35;j++){
//       for(i=0;i<34;i++)
//       {
//                        cout << Z[j][i] << " " ;
//       }
//       cout << endl;}              
}

// Construction du gradient du poids de l'épi
void Calculs::construction_gradient()
{
       G.resize(34);
       for(i=0;i<34;i++)
       {
               G[i] = 0;
       }
       for(i=0;i<34;i++)
       {
               for(k=1;k<34;k++)
               {
                       AA = produit(dFdU,Z[k]);
                       G[i] = G[i]+dGdU[i][k]-AA[i];
               }
               //cout << i << " " << G[i] << endl;
       }
}

void Calculs::compile_gradient(int nnn)
{
       if(nnn==0)
       {
               initEnv();
       }
       Env();
       Biomasse();
       if(nnn==0)
       {
               init_temoin();
       }
       initmat();
       construction_dGdU();
       construction_dGdX();
       construction_dFdU();
       construction_dSdX();
       construction_dFdX();
       construction_adjoints();
       construction_gradient();       
}

//////////////
//Optimisation
//////////////

// Méthode du gradient
void Calculs::algo_grad(int mmm)
{
       cond = 1;
       CC.resize(34);
       for(i=0;i<34;i++)
       {
               CC[i] = W[i];
       }
       som = 0;
       for(i=1;i<34;i++)
       {
               som = som+W[i];
       }
       //cout << "La somme des W vaut " << som << endl;
       for(i=1;i<34;i++)
       {
               CC[i] = CC[i]+rho*G[i];
               //cout << "La composante " << i << " du gradient non perturbe vaut " << G[i] << endl;
       }
       if(som>Wmaximal)
       {
               cond = 0;
               WW.resize(34);
               for(k=1;k<34;k++)
               {
                       G[k] = G[k]-exp(100*(som-Wmaximal));//*epsilon(mmm)[k];
                       //cout << "La composante " << k << " du gradient perturbe vaut " << G[k] << endl;
               }
               for(i=0;i<34;i++)
               {
                       WW[i] = W[i];
               }
               for(i=1;i<34;i++)
               {
                       WW[i] = WW[i]+rho*G[i];
                       if(WW[i]<0)
                       {
                               cond = 1;
                       }
               }
       }
       //cout << "Le gradient choisi est " << cond << " (0=perturbe, 1=non perturbe)" << endl;
       if(cond==1)
       {
               for(i=1;i<34;i++)
               {
                       W[i] = CC[i];
               }
       }
       else
       {
               for(i=1;i<34;i++)
               {
                       W[i] = WW[i];
               }
       }
               
}

// Fonction de pénalisation
vec Calculs::epsilon(int lll)
{
       pena.resize(34);
       for(j=0;j<34;j++)
       {
               pena[j] = 1;
       }
       for(j=1;j<34;j++)
       {
               pena[j] = pena[j];///(exp(-10*lll));
       }
       return pena;
}
                 



     
void affiche(double* t, int n)
       {
            int i;         
            for(i=0;i<n;++i)
            {
                  cout << t[i] << endl;
            }

       }


int main(){
    Calculs aaa;
    aaa.vdem();
    int iter;
    int iiii;
    ofstream myfile ("masse_epi.dat");
    for(iter=0;iter<47;iter++)
    {
            aaa.compile_gradient(iter);
            cout << iter << endl;
            //cout << "Au bout de l'iteration " << iter << ", la masse de l'epi vaut " << aaa.masse(33) << endl;
            if(iter==46)
            {
                    if (myfile.is_open())
                    {
                            myfile << "#Evolution de la masse de l'epi optimise par rapport a un epi temoin \n";
                            for (iiii=1;iiii<34;++iiii)
                            {
                                    //Calculs bbb;
                                    myfile << iiii << "      " << aaa.masse(iiii) << "      " << aaa.temoin(iiii) << endl;
                            }
                            myfile.close();
                    }
                    else {cout << "Unable to open file";}
            }        
            aaa.algo_grad(iter);
            //system("pause");
    }
    int i;
    



    //cout << "la somme des Q vaut " << aaa.Biomasse() << endl;
    //cout << "la masse de l'epi vaut " << aaa.masse(33) << endl;
    system("pause");
    return 0;
}
