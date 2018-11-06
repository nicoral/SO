#include <iostream>
#include <vector>
#include <utility>

using namespace std;


struct process
{
	string nom;
	int Tmemoria;
	int tama;
	bool band;
};
struct particiones
{
	string nom;
	int tam;
	int tiempo;
	bool estado;
};
struct memoria
{
	int tamMax;
	vector<particiones> parti;
};
bool huecos(vector<particiones> &A)
{
	for(int i=0;i<A.size()-1;i++)
	{
		if(A[i].nom==" ")
		{
			return true;
		}
	}
	return false;
}
int compactar(vector<particiones> &A)
{
	int ncompactados=0;
	while(huecos(A))
	{
		for(int i=0;i<A.size();i++)
		{
			if(A[i].nom==" " && A[i].estado==false)
			{
				ncompactados++;
				A.erase(A.begin()+i);
			}
		}
	}
	return ncompactados;
}
int EspacioLibre(memoria &A)
{
	int es=0;
	for(int i=0;i<A.parti.size();i++)
	{
		es+=A.parti[i].tam;
	}
	return A.tamMax-es;
}
void borrarProcess(string a,vector<process> &B)
{
	for(int i=0;i<B.size();i++)
	{
		if(B[i].nom==a)
		{
			B.erase(B.begin()+i);
			break;
		}
	}
}
bool procesoTerminado(memoria &M)
{
	for(int i=0;i<M.parti.size();i++)
	{
		if(M.parti[i].tiempo==0)
			return true;
	}
	return false;
}
void imprimirM(memoria &M,int tem)
{
	for(int i=0;i<M.parti.size();i++)
	{
		cout<<M.parti[i].nom<<" "<<M.parti[i].tam<<" "<<M.parti[i].tiempo<<endl;
	}
	cout<<"Espacio Libre:"<<EspacioLibre(M)<<endl;
	cout<<"tiempo:"<<tem<<endl;
}


void primer_ajuste(vector<process> &A,memoria &M,int &i){
	for(int j=0;j<M.parti.size();j++)
	{
		if(M.parti[j].estado==false && M.parti[j].tam>=A[i].tama)
		{
			M.parti[j].nom=A[i].nom;
			M.parti[j].tiempo=A[i].Tmemoria;
			M.parti[j].estado=true;
			A[i].band=true;
			break;
		}
	}
}	


void Pcompactacion(vector<process> &A,int mem,int ajuste)
{
	memoria M;
	M.tamMax=mem;
	int tem=0;
	particiones auxP;
	//mientras que hayan procesos
	while(!A.empty())
	{
		//metiendo los procesos a la memoria
		for(int i=0;i<A.size();i++)
		{
			//si es el primer proceso
			if(M.parti.empty())
			{
				if(A[i].tama<EspacioLibre(M) && A[i].band==false)
				{
					A[i].band=true;
					auxP.nom=A[i].nom;
					auxP.tam=A[i].tama;
					auxP.tiempo=A[i].Tmemoria;
					auxP.estado=true;
					M.parti.push_back(auxP);
				}
			}
			//si ya hay procesos existentes en memoria
			else
			{	
									for(int j=0;j<M.parti.size();j++)
					{
						if(M.parti[j].estado==false && M.parti[j].tam>=A[i].tama)
						{
							M.parti[j].nom=A[i].nom;
							M.parti[j].tiempo=A[i].Tmemoria;
							M.parti[j].estado=true;
							A[i].band=true;
							break;
						}
					}/*
				if(ajuste==1){


				}else if(ajuste==2){

				}else if(ajuste==3){

				}else if(ajuste==4)
				*/
				/* Ajustes

				*/
				if(A[i].tama<EspacioLibre(M) && A[i].band==false)
				{
					A[i].band=true;
					auxP.nom=A[i].nom;
					auxP.tam=A[i].tama;
					auxP.tiempo=A[i].Tmemoria;
					auxP.estado=true;
					M.parti.push_back(auxP);
				}
				
			}
		}
		
		tem++;
		for(int i=0;i<M.parti.size();i++)
		{
			if(M.parti[i].tiempo==0)
			{
				for(int j=0;j<M.parti.size();j++)
				{
					if(M.parti[j].tiempo==0)
					{
						borrarProcess(M.parti[j].nom,A);
						M.parti[j].nom=" ";
						M.parti[j].estado=false;
					}	
				}		
				for(int j=i;j<M.parti.size();j++)
				{
					M.parti[j].tiempo-=1;
				}
				///ban=false;
				cout<<"1°: "<<endl;
				imprimirM(M,tem);
				break;
			}
			else
			{
				M.parti[i].tiempo-=1;
			}
			cout<<"2°: "<<endl;
			imprimirM(M,tem);
		}
	}
}

int main()
{
	vector<process> v;
	process aux;
	aux.nom="p1";
	aux.Tmemoria=5;
	aux.tama=40;
	aux.band=false;
	v.push_back(aux);
	aux.nom="p2";
	aux.Tmemoria=5;
	aux.tama=20;
	aux.band=false;
	v.push_back(aux);
	aux.nom="p3";
	aux.Tmemoria=7;
	aux.tama=50;
	aux.band=false;
	v.push_back(aux);
	Pcompactacion(v,100,1);
	return 0;
}
