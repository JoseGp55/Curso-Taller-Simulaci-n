//Programa para generar numeros aleatorios del 1 al 10 de manera uniforme
//José Guadalupe Ibarra Armenta
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double alea(void);

//INICIO DEL PROGRAMA PRINCIPAL***************************************************************************************************************************
main(){
srand((unsigned)time(NULL));/*sembrando la semilla*/

int p, i;
int pasos=1000000000;
int numero;
int contador[10]={0};//inicializar siempre :P
float razon[10];
float suma=0;

for(p=1; p<=pasos; p++){/*INICIO(Principal)*/
	do{
		numero=int(alea()*10)+1;
	}while(numero>10);
	//printf("\n numero: %i \n",numero);
 	contador[numero]++;
	for(i=1; i<=10; i++){
		razon[i]=contador[i]/(p*1.0);
		suma+=razon[i];
	}		
	if(p%1==0)printf("\r P:%i 1:%1.6f 2:%1.6f  3:%1.6f 4:%1.6f 5:%1.6f 6:%1.6f 7:%1.6f 8:%1.6f 9:%1.6f 10:%1.6f S:%1.6f", p, razon[1], razon[2], razon[3], razon[4], razon[5], razon[6], razon[7], razon[8], razon[9], razon[10], suma);
	suma=0;
}/*FINAL(Principal)*/
return(0);
}
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alea(void){//genera numeros aleatorios entre 0 y 1
return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
/////////////////////////////////////////////////////////////////////////////THE END///////////////////////////////////////////////////////////////////////





