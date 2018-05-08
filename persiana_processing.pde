import controlP5.*;  //importamos la librería controlP5
import processing.serial.*;  //importamos la librería para la comunicación serie
Serial port;  //Asignación de la variable port de comunicación serie
ControlP5 cp5; //Asignación de la variable cp5 de librería ControlP5
int Grados = 0; //Variable para el valor de los grados
int V = 0; //Variable para identificar cuando cambiamos los grados
int rectX=350;
int rectY=80;
int rectSize = 100;
int mouseClicked;
int inactiveColor;
int activeColor;
int abajo =0;
int arriba = 180;
int para=90;
float n;
int dia= 1;
int noche =0;
int manual= 2;
int auto =3;
int activado =0;


int res[]; //array de respuesta (luz, lluvia, ...)

void setup() {
size (300, 300); //Tamaño del programa en pixeles
smooth();
background(150,190,180); //Color del fondo del programa
String arduinoPort = "COM3"; //Asignamos el numero de puerto de nuestro Arduino
port = new Serial(this, arduinoPort, 9600); //Establecemos el puerto y su velocidad
cp5 = new ControlP5(this); //Establecemos variable de la librería controlP5

textSize(26);
text("PERSIANA DOMÓTICA", 12, 30); 
fill(0, 102, 153);

cp5.addButton("Bajar")
.setValue(abajo)
.setPosition(30,150)
.setSize(rectSize,rectSize);


cp5.addButton("Subir")
.setValue(arriba)
.setPosition(170,150)
.setSize(rectSize,rectSize);

cp5.addButton("ManualMode")
.setValue(manual)
.setPosition(30,50)
.setSize(rectSize,70);

cp5.addButton("AutomaticMode")
.setValue(auto)
.setPosition(170,50)
.setSize(rectSize,70);

//fill(0); //Establecemos color negro
//textSize(20); //Tamaño de texto 30
//text("Pulsa para funcionar", 300, 50); 

//fill(0); //Establecemos color negro
//textSize(30); //Tamaño de texto 30
//text("Servomotor", 50, 100); //texto (color negro, tamaño 30) y posición
}

void draw()
{

}

public void controlEvent(ControlEvent theEvent) {
  println(theEvent.getController().getName());
  n = 0;
}


public void Bajar (int theValue){
  
  println("boton bajar pulsado");
  
  port.write("B\n");
  
}

public void Subir (int theValue){
 
  println("boton subir pulsado");
  port.write("S\n");

}

public void ManualMode (int TheValue){
  println("Modo manual activado");
  port.write("M\n");
 
}

public void AutomaticMode (int TheValue){
   
  println("Modo manual desactivado");
  port.write("A\n");

}
