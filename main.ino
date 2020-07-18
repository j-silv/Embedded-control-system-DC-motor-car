//Pin for reading optical sensor impulsions
#define fourchePin 2   

//Gate pin for a MOSFET driver
#define InputGrille 3  
#define TWO_PI 6.283185307179586476925286766559

#include <PID_v1.h>

//PID controller variables and gain values
double Setpoint, Input, Output,Kp = 1,Ki = 1000,Kd = 10;

//Setup controller
PID myPID(&Input, &Output, &Setpoint,Kp,Ki,Kd, DIRECT);

volatile int count,countold,trou=20;   

//tempsRotDebut: time at the beginning of a revolution
//tempsRotFin: time at the end of the revolution
//tempsRotTotal: difference between these two times
unsigned long temps = 0, tempsRotDebut=0, tempsRotFin=0, tempsRotTotal=0;  

//125 cm for the disk radius
float rayonDisc=0.0125,vitesse=0.0;  

void setup()
{
  //PID controller definitions
  Input = vitesse;
  Setpoint = 3;

  //Turn on PID
  myPID.SetMode(AUTOMATIC);

  //Initialize counter at 0
  count = 0;
  countold = 0; 
  
  pinMode(fourchePin, INPUT);

  //Interrupt to catch optical sensor impulsion
  attachInterrupt(digitalPinToInterrupt(fourchePin), impulseTrigger, FALLING);   

  Serial.begin(2000000); 
  Serial.println("VITESSE DE VOITURE");

}


void loop()
{
  //this code only occurs if an impulsion is detected
  if (countold != count)   
  {
    if(count>=trou){
      //Calculation: time it takes for one full revolution
      tempsRotFin=temps;
      tempsRotTotal=tempsRotFin-tempsRotDebut;
      tempsRotDebut=tempsRotFin;

      //Speed calculation (km/hr)
      vitesse=3600*TWO_PI*rayonDisc/(tempsRotTotal);

      //Reset the counter at 0 (new revolution)
      count=0;

      //Display speed
      Serial.print("   VITESSE (km/h): ");
      Serial.println(vitesse,5);         
    }
    
    countold = count;
    
    //Control system    
    Input = vitesse;
    myPID.Compute();
    analogWrite(InputGrille,Output);
  }
}

void impulseTrigger()
{
  temps = millis();
  count++;   
}
