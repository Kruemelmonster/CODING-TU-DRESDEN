
/* Detektion des Signals */
#include <stdio.h>
#include <stdlib.h>

#define FENSTER 320        /* Fensterlaenge=20 ms fuer Energieberechnung */
#define MIN_FENSTER_ANZ 10 /* Minimal 10 Fenster Signal */
#define ABSTAND 10        /* Abstand Effektivwertquadrat Signal-Pause */
#define Messwertanzahl 32000 //Anleitung
int signal_detekt(short **sample_anfang,unsigned int *sample_anzahl)
{
int counter = 0, max = 0, threshold = 0, time = 0, p=0, hoehstes = 0, anfang = 0;
	int  i;
	long int teil = 0;
	long int eVerlauf[Messwertanzahl/FENSTER];            //Energieverläufe werden hier gespeichert





	for(i= 0; i <= *sample_anzahl; i++) {
		teil += (*(*sample_anfang+i))*(*(*sample_anfang+i));        //berechnen des quadratischen effektivwertes
		if( i>1 && i % FENSTER == 0 ) {				    // Über die Fensterlänge iterieren 		
			if(counter>(Messwertanzahl/FENSTER)) {              // Falls 100 Überschritten wird "error1" 
				printf("error1");                                   
				return -1;}
			eVerlauf[counter] = teil;                           //Speicher Effektivwerte in Array
			counter++;
			teil=0;}
	}


	for(i=0;i<=Messwertanzahl/FENSTER;i++){
		if(max<eVerlauf[i])   
			max=eVerlauf[i];}  //Höchster Wert als Max gespeichert


	threshold=max/(Messwertanzahl/FENSTER);        // Schwelle festsetzen

	// Finden des geeingeten Abschnitts

	for(i=0;i<=Messwertanzahl/FENSTER;i++){
		if(eVerlauf[i]>= threshold){   // Effektivwerte die über der Schwelle liegen
			p=i;
			time = 0;
			while(eVerlauf[p]>=threshold && p< (Messwertanzahl/FENSTER)){
				p++;
				time++;}

			if(hoehstes < time){
				hoehstes=time;  //Neue Höchstzeit gefunden
				anfang = i;     //Anfang ist der Beginn des Nutzsignals 
			}

		}
	}
	//Wenn Mindestzeit nicht erreicht wurde muss 1 zurückgegeben werden

	if(hoehstes<MIN_FENSTER_ANZ)
		return 1;

	*sample_anfang += anfang*FENSTER;
	*sample_anzahl =hoehstes*FENSTER;
return (0);
}
