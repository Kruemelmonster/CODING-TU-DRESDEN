#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//#include <detection.c>
#define Messwertanzahl 32000
//benötigte angaben
#define true 1
#define false 0
int s=50;                      //schwelle für NGD


int ndg_histogramm(short *feld_ptr, unsigned int anzahl_atw, float *hist_ori, float *hist_diff){

	int p = 0;	//Abstand zwischen Nulldurchgängen
	int distance = 0,a=0; //a um p in feld zu speichern
	int feld[Messwertanzahl];
	int i = 0, ndg = 0, b=0, z=0, f=0, j=0;
	int mittel,grenze1,grenze2;
	unsigned int min =32000, max=0;
	char fall = false, above = false, across=false;

	for(p=0;p<4;p++){ 		//Nullsetzen alles Histogramme
		*(hist_ori+p)=0;
		*(hist_diff+p)=0;
	}

	for(i;i<anzahl_atw;i++) {    //genauso wie bei *Dichte*
		if(*(feld_ptr+i) >= s)
			across=true;
		if(*(feld_ptr+i) <= -s)
			above=true;
		if(across & !above)
			fall =true;
		if(!across  && above)
			fall =false;
		if(across  && above ){
      //printf(" p is %d | ",p);
      if(b){
			feld[a]=p;   //Speichert Abstand zwischen den NDG an der Stelle a in Array
			distance +=p;
         a++;
         }
         b=1;
			if (fall)
				across = false ;
			else
				above = false;
			}
		//wenn ein ndg stattfand muss p angeglichen werden
		//P wird über "echten" NDG angeglichen

		if((*feld_ptr+i)>=0 && *(feld_ptr+i+1) <0 || (*(feld_ptr+i)<= 0 && *(feld_ptr+i+1) >0)){
			p = i-distance;
         i++;              }
	}
}
for(f=0; f<a;f++) printf("p[%d)=%d | ",f,feld[f]);
//Restlichen Felder 0 setzen
while(a<= anzahl_atw){ //Setze restliche Felder 0
	feld[a]=0;
	a++;
}

//Bestimmung von Max und Min für Zuordnung
for(z=0; z<anzahl_atw;z++){
	if(feld[z]>max)
		max=feld[z];

	if((feld[z]<min) && feld[z] !=0)
		min=feld[z];
      }


	//Bestimmung der 4 Gruppen,
	mittel=(max+min)/2;
	grenze1=(mittel+min)/2;
	grenze2=(min+grenze1)/2;
   printf(" The limits are %d %d %d %d %d\n",min, mittel,grenze1,grenze2,max);
	//Nulldurchgänge den Gruppen zuorden

	for(j=0; j < anzahl_atw; j++) {
   printf("<FIRST!!!");
		if(min<=feld[j] && feld[j] < grenze1 ){
			(*hist_ori)++ ;
         }
		if(grenze1<=feld[j] && feld[j] < mittel )
			(*(hist_ori+1))++;
		if(mittel<=feld[j] && feld[j] < grenze2 )
			(*(hist_ori+2))++;
		if(grenze2<=feld[j] && feld[j] < max )
			(*(hist_ori+3))++;



		//Genauso wie oben
		 fall = false, above = false, across=false;
       a=0; i=0;

		for(i;i < anzahl_atw-1;i++) {	   // +1 -1 !?!:
			if(*(feld_ptr+i)-*(feld_ptr+i+1) >=  s)
				across = true;
			if(*(feld_ptr+i)-*(feld_ptr+i+1) <=  -s)
				above = true;
			if(across  && !above )
				fall = true;
			if(!across && above )
				fall = false;
			if(across && above ){
				feld[a]=p;
				distance +=p;

				if(fall )
					across = false;
				else
					above = false;
				a++;
			}

			//P anpassen über keinen "gezählten" NDG

			if((*(feld_ptr+i)-*(feld_ptr+i+1) >= 0 && *(feld_ptr+i+1)-*(feld_ptr+i+2) < 0) || (*(feld_ptr+i)-*(feld_ptr+i+1) <= 0 && *(feld_ptr+i+1)-*(feld_ptr+i+2) > 0)){
                           p = i-laenge;
			}
		}
		//Restlichen Felder 0 setzen
		while(a<= anzahl_atw){
			feld[a]=0;
			a++;
		}
		//Bestimmung von Max und Min für Zuordnung
		for(a=0; a<=anzahl_atw;a++){
			if(feld[a]>max)
				max=feld[a];

			if((feld[a]<min) && feld[a] !=0)
				min=feld[a];
		}

		//Bestimmung der 4 Gruppen,
		mittel=(max+min)/12;
		grenze1=(mittel+min)/3;
		grenze2=(mittel+max)/3;


		//Nulldurchgänge den Gruppen zuorden

		for(a=0; a <= anzahl_atw; a++) {
			if(min<=feld[a] && feld[a] < grenze1 )
				(*hist_diff)++ ;
			if(grenze1<=feld[a] && feld[a] < mittel )
				(*(hist_diff+1))++;
			if(mittel<=feld[a] && feld[a] < grenze2 )
				(*(hist_diff+2))++;
			if(grenze2<=feld[a] && feld[a] < max )
				(*(hist_diff+3))++;
		}
		return 0;
	}
   }
