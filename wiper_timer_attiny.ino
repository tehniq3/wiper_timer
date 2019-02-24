/* 
 *  program scris de Liviu Hinoveanu cu f. putin ajutor din partea lui Nicu FLORICA (niq_ro)
 *  
*/
// A7 este plusul contact- primul de sus spre sofer
#define buton 3 // A1-partea de fir spre mufa --- pin 1 parte sus spre pasager
#define aux 4 // A4 sprituitoare
#define out 2 // A1-partea de fir ramasa spre UCH 
int stareaux = 0;
int starebuton = 0; //flag to see if the button has been pressed, used internal on the subroutine only
int duratamare = 100; // valoare timp apaaare lunga, in ms
int duratapasare = duratamare; // initializare timp apasare
int aparare = 0;// sets default push value for the button going low
int eliberare = 0;// sets the default value for when the button goes back high
int timpmemorat = 5000;
byte Impuls = 0;
byte Impulsaux = 0; 
unsigned long timp = 0;
unsigned long debounce = 50;

boolean buttonflag = false; // default value for the button flag


void setup() {
   pinMode(out, OUTPUT);
   pinMode(buton,INPUT);
   pinMode(aux,INPUT);
   digitalWrite(out,LOW);
}

void loop() {
    duratapasare = aflareduratapasare();
    stareaux = digitalRead(aux);
   
    if ((duratapasare>=2000) && (duratapasare<=15000)) 
    {timpmemorat = duratapasare ; }
    
    if(starebuton == LOW)
    {digitalWrite(out,LOW);Impuls = 0;}
   
    if(starebuton == HIGH &&  Impuls == 0)
    {digitalWrite(out,HIGH); delay(200);digitalWrite(out,LOW); Impuls = 1;}
   
    if (starebuton == HIGH &&  Impuls == 1 &&  millis() - timp > timpmemorat)
    {digitalWrite(out,HIGH); delay(200);digitalWrite(out,LOW);Impuls = 0;timp = millis();}  
    
    if(stareaux == HIGH &&  millis() - timp > debounce)
    {Impulsaux = 1;timp = millis();}
     
    if(stareaux == LOW && Impulsaux == 1 && millis() - timp > 5000) 
    {digitalWrite(out,HIGH); delay(200);digitalWrite(out,LOW);Impulsaux = 0;timp = millis();}   
    }// sfarsit program

int aflareduratapasare () {
  starebuton = digitalRead(buton);
  if(starebuton == LOW && buttonflag == false && millis() - timp > debounce){     
          aparare = millis(); 
          timp = millis();
          buttonflag = true;
          };
   if (starebuton == HIGH && buttonflag == true && millis() -timp > debounce) {
          eliberare = millis ();
          timp = millis();
          buttonflag = false ;  
          duratapasare = eliberare - aparare;    
    };             
     return duratapasare;
   }
