/* Generación aleatoria de sprites de planetas */



#include <stdio.h>
#include <stdlib.h>
#include "w3d/estructuras.h"
#include <math.h>

/* Generación aleatoria de sprites de planetas */
/*

Esta función genera un sistema de coordenadas aleatorio.
El punto de posición se encuentra en la superficie de una esfera de radio 6000
y centro 0,0,0. Se calcula aleatoriamente.

El sistema de coordendas sólo tiene una regla fija, el vector z apunta al origen
y el x se calcula aleatoriamente. y se calcula a partir de z^x


*/



int genera_sistema_coordenadas(lista_sprites_spc *sprite) {
	FILE *fich;
  	float x,y,z;
	float radio=6000.0f;
	float normal[3];
	float eje_y[3];
	float eje_x[3];

	double aux;
	int contador=0;


	
	/*
		x=sqrt(pow(radio,2)-pow(y,2)-pow(z,2));
		
		x=sqrt(radio²-y²-z²);

		y²+z²<radio²;

		
	*/	
		
	
		/* Punto aleatorio de una esfera de radio 6000 */

		z=(float)(rand() % 6000);
		y=sqrt(rand() % (int)(pow(radio,2)-pow(z,2)));
		x=sqrt(pow(radio,2)-pow(y,2)-pow(z,2));
		if (rand()%2==0)
			z=z*-1;
		if (rand()%2==0)
			x=x*-1;
		if (rand()%2==0)
			y=y*-1;

			

		/* Vector unitario que une ese punto con el origen de coordenadas */

		normal[0]=x/radio;
		normal[1]=y/radio;
		normal[2]=z/radio;	
		
		/* En definitiva es el eje z de ese sistema de coordendas */
		
		/*
			i	j	k	
			az	bz	cz
			ax	bx	cx

			ay=bz*cx-cz*bx
			by=cz*ax-az*cx
			cy=az*bx-bz*ax

			az*ax+bz*bx+cz*cx=0

			cx=-(az*ax+bz*bx)/cz

			Por lo tanto, elegimos ax y bx entre 0 y 1
		*/

		eje_x[0]=(rand()%1001)/1000.0f;
		eje_x[1]=(rand()%1001)/1000.0f;
		eje_x[2]=-(normal[0]*eje_x[0]+normal[1]*eje_x[1])/normal[2];

		/* Y ahora hacemos el eje x unitario */

		aux=(sqrt(pow(eje_x[0],2)+pow(eje_x[1],2)+pow(eje_x[2],2)));
		eje_x[0]=eje_x[0]/aux;
		eje_x[1]=eje_x[1]/aux;
		eje_x[2]=eje_x[2]/aux;

		/* A por el eje Y que es z^x */
		eje_y[0]=normal[1]*eje_x[2]-normal[2]*eje_x[1];
		eje_y[1]=normal[2]*eje_x[0]-normal[0]*eje_x[2];
		eje_y[2]=normal[0]*eje_x[1]-normal[1]*eje_x[0];

		/* Voilá, ya tenemos nuestro punto y sistema de coordenadas para este sprite */

	
		
		printf ("Punto de la esfera\t %f\t%f\t%f \t\tradio %f\n",x,y,z,pow(x,2)+pow(y,2)+pow(z,2));
		printf ("Eje z:\t%f\t%f\t%f\tmodulo\t%f\n",normal[0],normal[1],normal[2],
			sqrt(pow(normal[0],2)+pow(normal[1],2)+pow(normal[2],2)));
		printf ("Eje x:\t%f\t%f\t%f\tmodulo\t%f\n",eje_x[0],eje_x[1],eje_x[2],
			(sqrt(pow(eje_x[0],2)+pow(eje_x[1],2)+pow(eje_x[2],2))));
		printf ("Eje y:\t%f\t%f\t%f\tmodulo\t%f\n",eje_y[0],eje_y[1],eje_y[2],
                        (sqrt(pow(eje_y[0],2)+pow(eje_y[1],2)+pow(eje_y[2],2))));
		printf ("Comprobación producto escalar z*x %f\n",normal[0]*eje_x[0]+normal[1]*eje_x[1]+normal[2]*eje_x[2]);
		printf ("Comprobación producto escalar z*y %f\n",normal[0]*eje_y[0]+normal[1]*eje_y[1]+normal[2]*eje_y[2]);
		printf ("Comprobación producto escalar y*x %f\n",eje_y[0]*eje_x[0]+eje_y[1]*eje_x[1]+eje_y[2]*eje_x[2]);


		sprite->matriz[3][0]=x;
		sprite->matriz[3][1]=y;
		sprite->matriz[3][2]=z;

		sprite->matriz[2][0]=normal[0];
		sprite->matriz[2][1]=normal[1];
		sprite->matriz[2][2]=normal[2];

		sprite->matriz[0][0]=eje_x[0];
		sprite->matriz[0][1]=eje_x[1];
		sprite->matriz[0][2]=eje_x[2];

		sprite->matriz[1][0]=eje_y[0];
		sprite->matriz[1][1]=eje_y[1];
		sprite->matriz[1][2]=eje_y[2];

		sprite->tam_x=(rand() % 475)+25;
		sprite->tam_y=500;
		





	
}


main (int argc,char **argv) {
	FILE *fich;
	lista_sprites_spc	lista_aux;
  int x,y,z;
	int i;
	char *text[]={"planeta.tga","quasar2.tga","quasar.tga","planeta2.tga","nebulosa.tga"};

	fich=fopen("espacio1.txt","wt");
  for (i=0;i<atoi(argv[1]);i++) {
	  genera_sistema_coordenadas(&lista_aux);
  	fprintf(fich,"<TIPO>SPRITE\n");
		fprintf(fich,"<TEXTURA>texturas/%s\n",text[(rand()%5)]);
		fprintf(fich,"<POSICION>%f,%f,%f\n",lista_aux.matriz[3][0],lista_aux.matriz[3][1],lista_aux.matriz[3][2]);
		fprintf(fich,"<EJE_X>%f,%f,%f\n",lista_aux.matriz[0][0],lista_aux.matriz[0][1],lista_aux.matriz[0][2]);
		fprintf(fich,"<EJE_Y>%f,%f,%f\n",lista_aux.matriz[1][0],lista_aux.matriz[1][1],lista_aux.matriz[1][2]);
		fprintf(fich,"<EJE_Z>%f,%f,%f\n",lista_aux.matriz[2][0],lista_aux.matriz[2][1],lista_aux.matriz[2][2]);
		fprintf(fich,"<TAMA_X>%f\n",lista_aux.tam_x);
		fprintf(fich,"<TAMA_Y>%f\n",lista_aux.tam_y);
	}
}
