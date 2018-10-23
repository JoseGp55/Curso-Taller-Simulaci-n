//Calculo del area de un circulo de radio unitario
//José Guadalupe Ibarra Armenta
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double alea(void);
FILE *dat;
//INICIO DEL PROGRAMA PRINCIPAL***************************************************************************************************************************

main(){
srand((unsigned)time(NULL));/*sembrando la semilla*/
system ("mkdir temp");
dat=fopen("temp/pi.dat","w");
fclose(dat);
int p;
int pasos=1000000000;
double cont_area=0;
double xi, yi, area;
double suma_prom;
suma_prom=0;
for(p=1; p<=pasos; p++){/*INICIO(Principal)*/
	xi=alea()*2-1;
	yi=alea()*2-1;
	if(pow(xi,2)+pow(yi,2)<1){
        	cont_area++;
        }
	area=cont_area*4.0/p;
	suma_prom+=area;
	if(p%1==0)printf("\r%i %1.8f %1.8f", p, area, suma_prom/p);
	if(p%1000==0){
		dat=fopen("temp/pi.dat","a");
		fprintf(dat,"\n%i	%1.8f	%1.8f", p, area, suma_prom/p);
		fclose(dat);
	}
}/*FINAL(Principal)*/

return(0);
}
//FINAL DEL PROGRAMA PRINCIPAL*****************************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alea(void){//genera numeros aleatorios entre 0 y 1
return((double)rand()/RAND_MAX); //32767 dependiente de la libreria
}
/////////////////////////////////////////////////////////////////////////////THE END///////////////////////////////////////////////////////////////////////




