#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <queue>
#include <stdlib.h>
#include <vector>
using namespace std;
struct pares
{
    int first;
    char* second;
};
typedef vector<pares> vpar;
struct node
{
	int Tllegada;
	char* nombre;
	int duracion;
	int x;
	int y;
	node()
	{
		nombre="";
	}
	node(char* a,int TLL,int Dura)
	{
		this->nombre=a;
		this->Tllegada=TLL;
		this->duracion=Dura;
	}
};
typedef vector<node> vnodo;

void sortLLegada(vnodo &v){
    for(double i=0;i<v.size();i++)
    {
        for(double j=i-1;j>=0;j--)
        {
            if(v[j].Tllegada<=v[j+1].Tllegada)
                break;
            swap(v[j],v[j+1]);
        }
    }
}
void sortDuracion(vnodo &v){
    for(double i=0;i<v.size();i++)
    {
        for(double j=i-1;j>=0;j--)
        {
            if(v[j].duracion<=v[j+1].duracion)
                break;
            swap(v[j],v[j+1]);
        }
    }
}

vpar Politica1(vnodo A){
	vpar res;
	sortLLegada(A);
	pares r;
    while(!A.empty()){
        for(int i=0;i<A[0].duracion;i++){
        	r.first=1;
        	r.second=A[0].nombre;
        	res.push_back(r);
        }
        A.erase(A.begin());
    }
    return res;
}

vpar Politica2(vnodo A){
	vpar res;
	sortDuracion(A);
	pares r;
    while(!A.empty()){
        for(int i=0;i<A[0].duracion;i++){
        	r.first=1;
        	r.second=A[0].nombre;
        	res.push_back(r);
        }
        A.erase(A.begin());
    }
    return res;
}

vpar Politica3(vnodo v)
{
	sortLLegada(v);
	vpar res;
	pares r;
	int temporizador=0,cont=0;
	vnodo aux;
	aux.push_back(v[cont]);
	cont++;
	while(!aux.empty())
	{
		temporizador++;
		aux[0].duracion--;
		///cout<<aux[0].nombre<<" "<<aux[0].duracion<<endl;
		r.first=1;
		r.second=aux[0].nombre;
		res.push_back(r);
		while(v[cont].Tllegada<=temporizador && cont<v.size())
		{
			aux.push_back(v[cont]);
			cont++;
			sortDuracion(aux);
		}
		if(aux[0].duracion==0)
		{
			aux.erase(aux.begin());
		}
	}
	return res;
}

vpar Politica5(vnodo pro,int quantum=2){
	sortLLegada(pro);
	vpar res;
	pares r;
	int temporizador=0,cont=0;
	queue<node> aux;
	aux.push(pro[cont]);
	cont++;
	node temp;
	while(!aux.empty()){
		temp=aux.front();
		aux.pop();
		for(int i=0;i<quantum;i++){
			if(temp.duracion>0){
				temporizador++;
				temp.duracion--;
				r.first=1;
				r.second=temp.nombre;
				//cout<<temp.nombre<<": "<<temp.duracion<<endl;
				res.push_back(r);
			}
			else
				break;
		}
		while(pro[cont].Tllegada<=temporizador && cont<pro.size()){

			aux.push(pro[cont]);
			cont++;
		}
		if(temp.duracion>0)
			aux.push(temp);

	}
	return res;
}

const char* tostr (int x)
{
    stringstream str;
    str << x;
    return str.str().c_str();
}

void pantalla_Inicio(int x,int y,char* nombre)
{
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
    setcolor(WHITE);
    outtextxy(275+x,y-10,nombre);
    const char* cha;
    setlinestyle(SOLID_LINE,4,3);
    line(100+x,350+y,100+x,20+y);
    line(100+x,350+y,520+x,350+y);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
    for(int i=0;i<=40;i+=5){
        cha=tostr(i);
    	outtextxy(100+x,360+y,cha);
    	x+=50;
    }


}
vpar Tfinalizacion(vnodo  vn,vpar vp)
{
    vpar Res;
    pares a;
    char* nom;
    for(int i=0;i<vn.size();i++)
    {
        a.first=0;
        a.second=vn[i].nombre;
        Res.push_back(a);

    }
    for(int i=0;i<vn.size();i++)
    {
        nom=vn[i].nombre;
        for(int j=0;j<vp.size();j++)
        {
            if(vp[j].second==nom)
            {
                Res[i].first=j+1;
            }

        }

    }
    return Res;
}
vpar Tespera(vnodo  vn,vpar vp)
{
    vpar Res,TF;
    TF=Tfinalizacion(vn,vp);
    pares a;
    char* nom;
    for(int i=0;i<vn.size();i++)
    {
        a.first=0;
        a.second=vn[i].nombre;
        Res.push_back(a);

    }
    for(int i=0;i<Res.size();i++)
    {
        nom=Res[i].second;
        for(int j=0;j<vp.size();j++)
        {
            if(vp[j].second!=nom && vn[i].Tllegada<=j && TF[i].first>=j+1)
            {
                Res[i].first++;
            }

        }
    }
    return Res;
}
vpar Tretorno(vnodo vn,vpar vp)
{
    vpar TF=Tfinalizacion(vn,vp);
    vpar Res;
    pares a;
    char* nom;
    for(int i=0;i<vn.size();i++)
    {
        a.first=0;
        a.second=vn[i].nombre;
        Res.push_back(a);

    }
    for(int i=0;i<vn.size();i++)
    {
        nom=Res[i].second;
        for(int j=0;j<vp.size();j++)
        {
            if(vp[j].second==nom)
            {
                Res[i].first=TF[i].first - j;
                break;
            }

        }
    }
    for(int i=0;i<Res.size();i++)
    {
        cout<<Res[i].first<<" "<<Res[i].second<<endl;
    }
    return Res;
}
int Promedio(vpar A)
{
    int Res=0;
    for(int i=0;i<A.size();i++)
    {
        Res+=A[i].first;
    }
    return Res/A.size();
}
void mostrar_politica(int x,int y,vnodo v,vpar vv,char* name)
{
    pantalla_Inicio(x,y,name);

    int Ax,Ay,c=0,actual=x+100;
    setlinestyle(SOLID_LINE,1,1);
    for(int i=0;i<v.size();i++)
    {
        outtextxy(70+x,310+y-(i*70),v[i].nombre);
        v[i].y=310+y-(i*70);
    }
    char* nom;
    for(int i=0;i<vv.size();i++)
    {
        nom=vv[i].second;
        while(v[c].nombre!=vv[i].second)
        {
            c++;
        }
        Ay=v[c].y+10;
        c=0;
        setlinestyle(SOLID_LINE,1,1);
        line(actual,Ay,actual+10,Ay);
        actual+=10;
        if(nom!=vv[i+1].second)
        {
            setlinestyle(1,1,1);
            line(actual,350+y,actual,20+y);
        }

    }
    ///outtextxy(550+x,120+y,"T. Finalizacion = ");outtextxy(670+x,120+y,tostr(vv.size()));
    vpar TF,TR,TE;
    TF=Tfinalizacion(v,vv);
    TE=Tespera(v,vv);
    TR=Tretorno(v,vv);
    for(int i=0;i<7;i++){
        setlinestyle(SOLID_LINE,1,1);
        line(550+x,90+y+(i*36),900+x,90+y+(i*36));
    }

    for(int i=0;i<5;i++){
        setlinestyle(SOLID_LINE,1,1);
        line(550+x+(i*87.5),90+y,550+x+(i*87.5),305+y);

    }

    for(int i=0;i<v.size();i++)
    {
        outtextxy(580+x,280+y-(i*36),v[i].nombre);
        outtextxy(680+x,280+y-(i*36),tostr(TF[i].first));
        outtextxy(760+x,280+y-(i*36),tostr(TE[i].first));
        outtextxy(860+x,280+y-(i*36),tostr(TR[i].first));
        v[i].y=310+y-(i*70);
    }


    outtextxy(655+x,100+y,"T. Fina");
    outtextxy(735+x,100+y,"T. Espera");
    outtextxy(820+x,100+y,"T. Retorno");

    outtextxy(550+x,330+y,"T.P. Finalizacion =");
    outtextxy(700+x,330+y,tostr(Promedio(TF)));
    outtextxy(550+x,350+y,"T.P. Espera =");
    outtextxy(700+x,350+y,tostr(Promedio(TE)));
    outtextxy(550+x,370+y,"T.P. Retorno =");
    outtextxy(700+x,370+y,tostr(Promedio(TR)));

}

int main()
{
    initwindow(1900,1000,"SO",0,0);
    ///setbkcolor(7);
    vpar poli1,poli2,poli3,poli5;
    node a("P1",0,20);
	node b("P2",2,12);
	node c("P3",3,5);
	node d("P4",3,2);
	node e("P5",4,3);
	vnodo v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);
	v.push_back(e);
	poli1=Politica1(v);
	poli2=Politica2(v);
	poli3=Politica3(v);
	poli5=Politica5(v,3);

    mostrar_politica(0,30,v,poli1,"FIFO");
    mostrar_politica(900,30,v,poli2,"SJF");
    mostrar_politica(0,550,v,poli3,"STF");
    mostrar_politica(900,550,v,poli5,"ROUND ROBIN");
    Tretorno(v,poli5);
    getch();
    return 0;
}
