

/* Berechnung der NDG - Dichte eines Signalabschnittes */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
#define true 1
#define false 0

int s = 60;
int ndg_dichte(short *feld_ptr, unsigned int anzahl_atw, float *dichte_ori, float *dichte_diff){
   int i = 0;
	int ndg = 0;      //Initialisierung von Zähler(i) und Nulldurchgänge
	short fall = false, below = false, above =false; //Initialisierung von "Merkmale" für NDG
  *dichte_ori = (float)0.0;

  *dichte_diff = (float)0.0;



	for(i;i<anzahl_atw;i++) {             //Alle Abtastwerte(atw) abarbeiten
		if(*(feld_ptr+i) >= s)
			above=true;
		if(*(feld_ptr+i) <= -s)
			below=true;
		if(above & !below) 
			fall =true;                // Fall Hilfsvariable um je nachdem above oder below false zu setzen
		if(!above  && below)
			fall =false;
		if(above  && below ){       //Sind above und below gesetzt fand ein NDG statt
			ndg++;

			if (fall)
				above = false ;  // Falls  "gesetzt" ist, wird
			else
				below = false;}
	}
	printf("ndg=%i",ndg);
	*dichte_ori =anzahl_atw/ndg; /*dichte_ori=Anzahl der Nulldurchgänge im vorgegebenen
				       Abtastwertefeld im Verhältnis zur Anzahl der Abtastwerte im gesamten Analysefenster.*/


	i = 0; ndg = 0;
	above = false; fall = false; below = false; //Alle Werte resetten
	// Selber Code wie oben nur für differenziertes Signal

	for(i;i < anzahl_atw-1;i++) {// evtl. +1 !?!
		if(*(feld_ptr+i)-*(feld_ptr+i+1) >= s){
			above = true;}
		if(*(feld_ptr+i)-*(feld_ptr+i+1) <= -s){
			below = true;}
		if(above  && !below )
			fall = true;
		if(!above && below )
			fall = false;
		if(above && below ){
			ndg++;
			if(fall )
				above = false;
			else
				below = false;}

	}
	*dichte_diff = anzahl_atw/ndg;

return (0);
}
