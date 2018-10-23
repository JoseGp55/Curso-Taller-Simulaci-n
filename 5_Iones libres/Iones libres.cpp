//Sistema de iones con movimiento aleatorio e ilimitado (particulas libres)
//José Guadalupe Ibarra Armenta
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXPART 500

double alea(void);

void calculos_iniciales(void);
int posiciones_iniciales(void);
void selecciona_ion(void);
void mueve_ion(void);
void salida3d(void);

struct io{
float x,y,z;
int carga;
}ion[MAXPART];

/****Info del sistema****/
int pasos=10000000;//Numero de pasos
int actu=50;//Actiualizacion
float dx=0.5,dy=0.5,dz=0.5;
int np=20, nn=20

int p;
int ni, n;

/***INICIO***/
main(){
srand((unsigned) time(NULL));
system ("mkdir temp");        
calculos_iniciales();
posiciones_iniciales();
	for(p=1;p<=pasos;p++){//Ciclo principal
		selecciona_ion();
		mueve_ion();
		printf("\rPaso: %i",p);
		if(p%actu==0)salida3d();
	}//Fin de ciclo principal
return 0;
}
//******FIN****///
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
double alea(void){//genera numeros aleatorios entre 0 y 1
return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void calculos_iniciales(void){
	n=np+nn;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int posiciones_iniciales(void){
	int i,j,k,m=1;
	for(i=1; i<=10; i++){
		for(j=1; j<=10; j++){
			for(k=1; k<=10; k++){
				ion[m].x=i;
				ion[m].y=j;
				ion[m].z=k;
				if(m<=np)ion[m].carga=1;
				else ion[m].carga=-1;
				m++;
				if(m>n){
					salida3d();
					return(0);
				}	
			}
		}
	}
salida3d();
return(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void salida3d(void){
	int m;
	FILE *dat;
	char nombre[30];
	sprintf(nombre,"temp/Salida3d%i.dat",p/actu);
	dat=fopen(nombre, "w");
	fprintf(dat,"Execute[{");
	for(m=1; m<=n; m++){
		if(ion[m].carga==1)fprintf(dat,"\"S%i:(x-%f)^2+(y-%f)^2+(z-%f)^2=0.25\",\"SetColor[S%i,Blue]\"", m, ion[m].x, ion[m].y, ion[m].z, m);
		else fprintf(dat,"\"S%i:(x-%f)^2+(y-%f)^2+(z-%f)^2=0.25\",\"SetColor[S%i,Red]\"", m, ion[m].x, ion[m].y, ion[m].z, m);
		if(m<n)fprintf(dat,",");
	}
	fprintf(dat,"}]");
	fclose(dat);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void selecciona_ion(void){
	do{
		ni=int(alea()*n)+1;
	}while(ni>n);
	//printf("\n ni: %i\n", ni);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mueve_ion(void){
ion[0]=ion[ni];
ion[ni].x+=(alea()-0.5)*dx;
ion[ni].y+=(alea()-0.5)*dy;
ion[ni].z+=(alea()-0.5)*dz;
}
/////////////////////////////////////////////////////The End/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

