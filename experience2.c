#include <stdio.h>
#include <sys/time.h>
#define MAX_TAILLE_DATA_KO  4096 // = 4 Mo
int tab[MAX_TAILLE_DATA_KO * 1024]; // tableau des données accédées
int i,j,x; // un compteur de boucle simple
int taille_data, nbdonnee;// qui correspond à la taille totale des données accédées en Ko
 // = (taille_data * 1024) / sizeof(int)
int nbRep = 10 ; // nombre de repetition
struct timeval t1, t2; // variables utilisées pour mesurer le temps d’exécution
float temps_acces_moyen; //en microsecondes



void main() {
	FILE *f = fopen("benchmark", "w");
	fprintf(f, "#Le temps d’accès(en milliseconde) : la taille totale des données(en KO) ");
	printf("tab : %d\n", sizeof(tab));
	for (taille_data=sizeof(int); taille_data < MAX_TAILLE_DATA_KO * 1024; taille_data++){
		nbdonnee= (taille_data * 1024) / sizeof(int);
		for (i=0; i < nbdonnee ; i+=16) { // boucle simple qui pré-charge les données dans le cache L1
			x=x+tab[i];
		} // end for i
		gettimeofday(&t1,NULL);
		// récupérer ici la valeur de l’horloge juste avant la boucle
		//repeter nbRep fois
		int pas = 25;
		for (j=0; j < nbRep; j++){
			for (i=0; i < nbdonnee ; i+=16) { // boucle qui accède aux données pré-chargées dans le cache
				x=x+tab[i];
			} // end for i
		} // end for j
		gettimeofday(&t2,NULL); // récupérer la valeur de l’horloge à la fin de la boucle
		temps_acces_moyen= (float) ((t2.tv_usec + (t2.tv_sec*1000000)) - (t1.tv_usec + (t1.tv_sec*1000000))) / (nbdonnee*nbRep);
		//printf("Le temps d’accès moyen est de \%f microsecondes lorsque la taille totale des données accédées est de \%d KO", temps_acces_moyen, taille_data);
		if (f == NULL)
		{
    	printf("Error opening file!\n");
    	
		}

		fprintf(f, " %f : %d\n", temps_acces_moyen, taille_data*sizeof(int));
	
		} // endfor taille_data

		fclose(f);

	} // end main