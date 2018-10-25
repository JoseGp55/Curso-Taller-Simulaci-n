#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define MAXPART 500
#define kb 1.3806e-23
#define qe 1.60219e-19
#define esc 1e-9
#define epce 8.85419e-12
#define pi 3.141592653589793

double alea(void);
void calculos_iniciales(void);
int posiciones_iniciales(void);
void selecciona_ion(void);
void mueve_ion(void);
void salida3d(void);
void condiciones_periodicas(void);
int signo(float a);
void metropolis(void);
float variacion_energia(void);
float distancia(int a, int b);


struct io{
	float x, y, z;
	int carga;
}ion [MAXPART];

int pasos = 10000000;
int actu = 5000;
float dx = 5, dy= 5, dz = 5;
int np=300, nn=100;//aqui modificamos para agregar la carga que estamos agregando de mas en el centro de la celda, tambien moficamos la proporcion entre positivos y negativos si queremos meter sales 2:1, 3:1, 2:3 etc
int p;
int ni, n, temp=300, aceptacion=0, rechazo=0, rechazo_traslape=0, rechazo_metropolis=0;

main(){
	srand((unsigned)time(NULL));
	system ("mkdir temp");
	calculos_iniciales();
	posiciones_iniciales();
	for(p=1; p<=pasos; p++){
			rechazo=0;
			selecciona_ion();
			mueve_ion();
			condiciones_periodicas();
			metropolis();
			printf("\rPaso: %i Aceptacion=%f rechazo metropolis: %f rechazo traslape: %f", p, aceptacion*1.0/p, rechazo_metropolis*1.0/p, rechazo_traslape*1.0/p);
			if(p%actu==0)salida3d();
	}
	return(0);
}
double alea(void){
	return((double)rand()/RAND_MAX);
}

void metropolis(void){
	double argexp;
		argexp=(-1)*variacion_energia()/(kb*temp);
	if(rechazo==0){
		if (exp(argexp)>alea()){
			aceptacion++;
			//printf"
		}else{
			ion[ni]=ion[0];
			rechazo_metropolis++;
		}
	}else{//el programa solo entra aca si hubo traslape de esferas
		ion[ni]=ion[0];
		rechazo_traslape++;
	}
}

float variacion_energia(void){
	int i;
	float ecoul_i=0, ecoul_f=0, den, cte=qe*qe/(4*pi*epce*78.5);//aqui introduje la permitividad dielectrica relativa del agua a 300 K para suavizar las interacciones
	for (i=1; i<=n;i++){
		if((i!=ni)&&(distancia(ni,i)>=1)){
			ecoul_i+=cte*ion[0].carga*ion[i].carga/(distancia(0,1)*esc);
			ecoul_f+=cte*ion[ni].carga*ion[i].carga/(distancia(ni,1)*esc);
			}else if((i!=ni)&&(distancia(ni,i)<1)){//en esta parte se revisa si los iones se traslapan y de ser asi se rechaza el movimiento se corta el calculo y la variable rechazo cambia de valor para que no se efectue el algoritmo de Metropolis
			rechazo=1;
			return (den);
		}
	//condicion 1
	//	ecoul_i+=cte*ion[0].carga*5/(sqrt(pow((ion[0].x-10),2)+pow((ion[0].y-10),2)+pow((ion[0].z-10),2))*esc);//en estas dos lineas se pone una carga positiva de 1 carga electrica fundamental en el centro de la celda (10,10,10) la interaccion tiene simetria esferica
	//	ecoul_f+=cte*ion[ni].carga*5/(sqrt(pow((ion[ni].x-10),2)+pow((ion[ni].y-10),2)+pow((ion[ni].z-10),2))*esc);
	//condicion 2
		ecoul_i+=cte*ion[0].carga*1/(sqrt(pow((ion[0].x-10),2)+pow((ion[0].y-10),2))*esc);//en estas dos lineas se pone una carga positiva de 1 carga electrica fundamental en el centro de la celda (10,10,10) la interaccion tiene simetria cilindrica
		ecoul_f+=cte*ion[ni].carga*1/(sqrt(pow((ion[ni].x-10),2)+pow((ion[ni].y-10),2))*esc);
	//condicion 3	
		ecoul_i+=cte*ion[0].carga*1/(sqrt(pow((ion[0].z-10),2))*esc);//en estas dos lineas se pone una carga positiva de 1 carga electrica fundamental en el centro de la celda (x=10) la interaccion tiene simetria plana
		ecoul_f+=cte*ion[ni].carga*1/(sqrt(pow((ion[ni].z-10),2))*esc);		
		
	}
	den=ecoul_f-ecoul_i;
	//printf("Den=%1.6e\n",den);
	return(den);
}

float distancia(int a, int b){
	float dist, xx, yy, zz;
	xx=ion[b].x;
	yy=ion[b].y;
	zz=ion[b].z;
	if (fabs(ion[a].x-xx)>10)xx+=20*signo(ion[a].x-xx);
	if (fabs(ion[a].y-yy)>10)yy+=20*signo(ion[a].y-yy);
	if (fabs(ion[a].z-zz)>10)zz+=20*signo(ion[a].z-zz);
	dist=sqrt(pow((ion[a].x-xx),2)+pow((ion[a].y-yy),2)+pow((ion[a].z-zz),2));
	return(dist);
}

void condiciones_periodicas(void){
	if((ion[ni].x<0) || (ion[ni].x>=20)){
		ion[ni].x+=20*signo(-ion[ni].x);
	}
	if((ion[ni].y<0) || (ion[ni].y>=20)){
		ion[ni].y+=20*signo(-ion[ni].y);
	}
	if((ion[ni].z<0) || (ion[ni].z>=20)){
		ion[ni].z+=20*signo(-ion[ni].z);
	}
}


int signo(float a){
	if(a>0) return(1);
	else if (a<0) return(-1);
	else return (0);
}


void calculos_iniciales(void){
	n = np+nn;
}

int posiciones_iniciales(void){
	int i, j, k, m=1;
	for (i=1; i<=10;i++){
		for(j=1; j<=10; j++){
			for (k=1; k<=10; k++){
				ion[m].x=i;
				ion[m].y=j;
				ion[m].z=k;
				if(m<=np) ion[m].carga=1;
				else ion[m].carga=-3;
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

void salida3d(void){
		int m;
		FILE *dat;
		char nombre[30];
		sprintf(nombre, "temp/salida3d%i.dat", p/actu);
			dat=fopen(nombre, "w");
			fprintf(dat, "Execute[{");
			for (m=1; m<=n;m++){
				if(ion[m].carga==1)fprintf(dat,"\"S%i:(x-%f)^2+(y-%f)^2+(z-%f)^2=0.25\",\"SetColor[S%i,Blue]\"", m, ion[m].x, ion[m].y, ion[m].z, m);
				else fprintf(dat,"\"S%i:(x-%f)^2+(y-%f)^2+(z-%f)^2=0.25\",\"SetColor[S%i,Red]\"", m, ion[m].x, ion[m].y, ion[m].z, m);
				if(m<n)fprintf(dat, ",");
			}
		fprintf(dat, "}]");
		fclose(dat);
}

void selecciona_ion(void){
	do{
		ni=int(alea()*n)+1;
	}while(ni>n);
}

void mueve_ion(void){
	ion[0]=ion[ni];
	ion[ni].x+=(alea()-0.5)*dx;
	ion[ni].y+=(alea()-0.5)*dy;
	ion[ni].z+=(alea()-0.5)*dz;
}
