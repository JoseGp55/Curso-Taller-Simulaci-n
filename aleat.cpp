//Proyecto de simulacion por computadora mallado
//José Guadalupe Ibarra Armenta
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#define epce 8.85419e-12
#define qe 1.6021e-19
#define MAXPART 500
#define na 6.02217e23
#define kb 1.38062e-23
#define pi 3.141592653589793
#define esc 1e-9
#define MAXCLASES 500

void leer_entrada(void);
void imprimir_entrada(void);
void selecciona_ion(void);
void mover_ion(void);
void metropolis(void);
void condiciones_periodicas(void);
int signo(float a);
float distancia(float a,float b); 
float variacion_de_energia(void);
void gdr(void);
void salida3d(void);
void calculos_iniciales(void);
float aleat(void);
int posiciones_iniciales(void);
float distancia(int a, int b);

struct io{
float x,y,z;
int carga;
}ion[MAXPART];

/****Info del sistema****/
int pasos;//Numero de pasos
int actu;//Actiualizacion
float w, l;//w=ancho, l=largo de la caja
float temp; //temperatura en K
float epsi;//
int clases;
float dx,dy,dz;

int p;
int ni,n, np, nn;
float denspp, denspn;
float dl, dw;
int rechazo=0, aceptacion=0;

int gdrpx[MAXCLASES]={0},gdrpy[MAXCLASES]={0},gdrpz[MAXCLASES]={0};
int gdrnx[MAXCLASES]={0},gdrny[MAXCLASES]={0},gdrnz[MAXCLASES]={0};

/***INICIO***/
main(){
srand((unsigned) time(NULL));
leer_entrada();
imprimir_entrada();
calculos_iniciales();
posiciones_iniciales();
	for(p=1;p<=pasos;p++){//Ciclo principal
		rechazo=0;
		selecciona_ion();
		mover_ion();
		condiciones_periodicas();
		metropolis();
		gdr();
		printf("\r %i aceptacion: %f",p, (1.0*aceptacion)/p);
	}//Fin de ciclo principal
return 0;
}
//******FIN****///
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
void leer_entrada(void){
FILE *dat;
	dat=fopen("Entrada.txt","r");
	if(dat){
        fscanf(dat,"Numero de pasos: %i\n",&pasos);
		fscanf(dat,"Actualizacion: %i\n",&actu);
 		fscanf(dat,"Iones negativos: %i\n",&nn);
		fscanf(dat,"Iones positivos: %i\n",&np);
		fscanf(dat,"(w,l): %f, %f\n",&w,&l); 
		fscanf(dat,"Temperatura: %f\n",&temp);
		fscanf(dat,"Permitividad dielectrica relativa: %f\n",&epsi);
		fscanf(dat,"Numero de clases: %i\n",&clases);
		fscanf(dat,"(dx,dy,dz)= %f, %f, %f\n",&dx,&dy,&dz);
	}
	fclose(dat);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimir_entrada(void){
 	printf("Datos del sistema\n");	
        printf("Numero de pasos: %i\n",pasos);
	printf("Actualizacion: %i\n",actu);
 	printf("Iones negativos: %i\n",nn);
	printf("Iones positivos: %i\n",np);
	printf("(w,l): %f, %f\n",w,l); 
	printf("Temperatura: %f\n",temp);
	printf("Permitividad dielectrica relativa: %f\n",epsi);
	printf("Numero de clases: %i\n",clases);
	printf("(dx,dy,dz)= %f, %f, %f\n\n",dx,dy,dz);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float aleat(void){//genera numeros aleatorios entre 0 y 1
	float aleatt;
	aleatt=(float)rand()/RAND_MAX;//32767 dependiente de la libreria
	return(aleatt); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int signo (float a){
	if(a>0) return(1);
	else if (a<0) return(-1);
	else return(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void calculos_iniciales(void){
	n=np+nn;
	denspp=np*1.0/clases;
	denspn=nn*1.0/clases;
	printf("\n denspp: %f denspn: %f\n", denspp, denspn);
	dl=l/clases;
	dw=w/clases;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int posiciones_iniciales(void){
	int i,j,k,m=1;
	for(i=1; i<=w; i++){
		for(j=1; j<=w; j++){
			for(k=1; k<=l; k++){
				ion[m].x=i;
				ion[m].y=j;
				ion[m].z=k;
				if(m%2==0)ion[m].carga=1;
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
	char nombre[50];
	sprintf(nombre,"Salida3d_%i.dat",p/actu);
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
		ni=int(aleat()*n)+1;
	}while(ni>n);
	//printf("\n ni: %i\n", ni);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mover_ion(void){
ion[0]=ion[ni];
ion[ni].x+=(aleat()-0.5)*dx;
ion[ni].y+=(aleat()-0.5)*dy;
ion[ni].z+=(aleat()-0.5)*dz;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void condiciones_periodicas(void){
	if((ion[ni].x<0)||(ion[ni].x>=w)){
		ion[ni].x+=w*signo(-ion[ni].x);
	}
	if((ion[ni].y<0)||(ion[ni].y>=w)){
		ion[ni].y+=w*signo(-ion[ni].y);
	}
	if((ion[ni].z<0)||(ion[ni].z>=l)){
		ion[ni].z+=l*signo(-ion[ni].z);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void metropolis(void){
	double argexp;
	argexp=(-variacion_de_energia()/kb*temp);
	if(rechazo==0){
		if(exp(argexp)>aleat()){//movimiento aceptado
			aceptacion++;
			//printf("ACEPTADO \n \n");
			//getch();
		}else{//movimiento rechazado
			ion[ni]=ion[0];
			//printf("RECHAZO METROPOLIS \n \n ");
		}
	}else{//rechazo por traslape
		ion[ni]=ion[0];
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float variacion_de_energia(void){
	int i;
	float ecoul_i=0, ecoul_f=0, den, cte=qe*qe/(4*pi*epce*epsi);
	for(i=1;i<=n;i++){
		if((i!=ni)&&(distancia(ni,i)>=1)){
			ecoul_i+=cte*ion[0].carga*ion[i].carga/(distancia(0,i)*esc);
			ecoul_f+=cte*ion[ni].carga*ion[i].carga/(distancia(ni,i)*esc);
		}else if((i!=ni)&&(distancia(ni,i)<1)){
			rechazo=1;
			den=ecoul_f-ecoul_i;
//printf("\n TRASLAPE distancia (%i, %i): %f \n \n", ni, i, distancia(i,ni));
			return (den);
		}
	}
	//den=ecoul_f-ecoul_i;
	den=0;
//printf("\n de: %e \n", den);	
	return(den);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float distancia(int a, int b){
	float dist;
	dist=sqrt(pow((ion[a].x-ion[b].x),2)+pow((ion[a].y-ion[b].y),2)+pow((ion[a].z-ion[b].z),2));
	return(dist);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gdr(void){
	int i;
	for(i=1; i<=n; i++){
		if(ion[i].carga==1){
			gdrpx[int(ion[i].x/dw)+1]++;
			gdrpy[int(ion[i].y/dw)+1]++;
			gdrpz[int(ion[i].z/dl)+1]++;
		}else{
			gdrnx[int(ion[i].x/dw)+1]++;
			gdrny[int(ion[i].y/dw)+1]++;
			gdrnz[int(ion[i].z/dl)+1]++;
		}
	}
	if(p%actu==0){
		FILE *dat;
		char nombre[50];
		sprintf(nombre,"gdr_%i.dat",p/actu);
		dat=fopen(nombre, "w");
		for(i=1; i<=clases; i++){
			fprintf(dat,"%f	%f	%f	%f	%f	%f	%f	%f\n", (i-0.5)*dw, gdrpx[i]/(denspp*p), gdrnx[i]/(denspn*p), gdrpy[i]/(denspp*p), gdrny[i]/(denspn*p), (i-0.5)*dl, gdrpz[i]/(denspp*p), gdrnz[i]/(denspn*p));
		}
	fclose(dat);
	salida3d();
	}	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

