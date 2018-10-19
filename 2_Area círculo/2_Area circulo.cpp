//Calculo del area de un circulo de radio unitario
//José Guadalupe Ibarra Armenta
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float signo(float num);
double alea(void);

//INICIO DEL PROGRAMA PRINCIPAL***************************************************************************************************************************

main(){
srand((unsigned)time(NULL));/*sembrando la semilla*/

int p;
int pasos=1000000000;
int cont_area=0;
float xi, yi, area;

for(p=1; p<=pasos; p++){/*INICIO(Principal)*/
	xi=alea()*2-1;
	yi=alea()*2-1;
	if(pow(xi,2)+pow(yi,2)<=1){
        	cont_area++;
        }
	area=(float)cont_area*4/p;
	if(p%1==0)printf("\r%i %1.8f", p, area);
}/*FINAL(Principal)*/
return(0);
}
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alea(void){//genera numeros aleatorios entre 0 y 1
return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
/////////////////////////////////////////////////////////////////////////////THE END///////////////////////////////////////////////////////////////////////





