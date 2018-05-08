
#include <Servo.h> 
Servo myservo;      
int luz = 0; // variables control de luz
int parar =90;
int subir = 180;
int bajar =0;
byte val ;
boolean dia = true; // controla que solo suba o baje con el primer valor aceptado en cada estado
boolean agua = false;
boolean disponible = true;
boolean abajo = false;
boolean arriba = true;
char valor=0;
char res[2];
int i = 0;
String buff = "";
int NEWLINE = 10;
int isAuto = 1;
int lluvia;
const int sensorPin =9;

const int pinecho1 = 3;   //superior
const int pintrigger1 = 4;

const int pinecho2 = 5;   //inferior
const int pintrigger2 = 6;


void setup(){

   Serial.begin(9600); 
   myservo.attach(10);// conexión servomotor
   pinMode(sensorPin, INPUT);
//   cronometro_temperatura=millis();
  pinMode(pinecho1, INPUT);
  pinMode(pintrigger1, OUTPUT);
  
  pinMode(pinecho2, INPUT);
  pinMode(pintrigger2, OUTPUT);
}

void loop(){
 
  if(Serial.available()>0)  //Condición para ver si a llegado datos al buffer del puerto serie
    serialEvent(Serial.read());//Cargamos el valor de grados en val
    
  lluvia = digitalRead(sensorPin);
//Serial.println(luz); //1 si NO detecta agua y 0 si SI que detecta agua
  
 if(isAuto){
  luz=(1023-analogRead(A0))/4;  //medidor de intensidad de la luz
   
  
  if((luz>90) && (dia) && (disponible))   {   //si es de noche     BAJAR
  
  dia= false;
  disponible = false;
  down();
    
  
 }
 if((luz<90) && (!dia) && (!disponible))  {     //si es de dia    SUBIR
  dia=true;
  disponible = true;
myservo.write(subir);
    delay(2700);
   myservo.write(parar); 
  }
  
if((lluvia == 0) && (!agua) && (disponible)) {
    agua = true;
    disponible = false;
    down();
  }

if((lluvia == 1) && (agua) && (!disponible)){
    agua = false;
    disponible = true;
   myservo.write(subir);
    delay(2700);
   myservo.write(parar); 
  }
     
  }

}
  
void down(){
  int tiempo2=0;
  int distancia2 = 0;
 do{    myservo.write(bajar);
        digitalWrite(pintrigger2, LOW);
        delayMicroseconds(2);
        digitalWrite(pintrigger2, HIGH);
 
        delayMicroseconds(10);
        digitalWrite(pintrigger2, LOW);
 
  
        tiempo2 = pulseIn(pinecho2, HIGH);
 
        distancia2 = tiempo2 / 58;
      }while (distancia2>8);
    
  myservo.write(parar);
  }
  

void up(){
  int tiempo1=0;
  int distancia1 = 0;
 do{    myservo.write(subir);
        digitalWrite(pintrigger1, LOW);
        delayMicroseconds(2);
        digitalWrite(pintrigger1, HIGH);
 
        delayMicroseconds(10);
        digitalWrite(pintrigger1, LOW);
 
  
        tiempo1 = pulseIn(pinecho1, HIGH);
 
        distancia1 = tiempo1 / 58;
        Serial.println(distancia1);
      }while (distancia1<8);
    
  myservo.write(parar);
  }


void serialEvent(int serial)
{
  if(serial != NEWLINE){
 buff += char(serial);
 } else {
 char c = buff.charAt(0);
 char e = buff.charAt(1);
// buff = buff.substring(1);
// buff = buff.substring(0, buff.length()-1);
 if (c == 'M')
  isAuto = 0;
 else if (c == 'A')
  isAuto = 1;
 else if (c == 'B')
 {
  if(!isAuto){
    //ToDo
    if((!abajo)&&(arriba)){
      down();
      abajo = true;
      arriba = false;
    }
    
    }
 }
 else if (c == 'S'){
    if(!isAuto){
    //ToDo
    if((abajo)&&(!arriba)){
    myservo.write(subir);
    delay(2700);
   myservo.write(parar); 
   abajo = false;
   arriba = true;
       }
    }
 }

 buff = "";
 Serial.flush();
  }
      
}


