 // Código C para Arduino, PROGRAMA UNIVERSAL DE LAVADORA
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
#include "RTClib.h"
RTC_DS1307 RTC;

unsigned long cycleStart;  // Se utiliza para hacer el seguimiento de cuánto tiempo ha estado lavando.
// notas melodía:
int melody[] = {
NOTE_C3, NOTE_C3, NOTE_C3, NOTE_GS2, NOTE_DS3, NOTE_C3, NOTE_GS2, NOTE_DS3, NOTE_C3, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_GS4, NOTE_DS4, NOTE_C4, NOTE_GS2, NOTE_DS3, NOTE_C3 };
//notas duración: 4 = cuarta note, 8 = octava note, etc.:
int noteDurations[] = {
4,4,4,4,8,4,4,8,4,4,4,4,4,8,4,4,8,4};

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);

int push1=0; //almacena el estado del botón
int push2=0;
int push3=0;
int push4=0;
int push5=0;
int estado1=0; //0=led apagado, 1=led encendido
int estado2=0;
int estado3=0;
int estado4=0;
int estado5=0;
int pushAnt1=0; //almacena el estado anterior del boton
int pushAnt2=0;
int pushAnt3=0;
int pushAnt4=0;
int pushAnt5=0;
int x;

//Designando pines
//#define OFF HIGH //no encuentro explicación porque me funcionan al contrario (·@####@@#@#@#¬€€¬€aaaaaarrrrrrgggggggg)
//#define ON LOW
#define MotorVelocidad4 4 //pin centrifugado Media
#define MotorVelocidad1 1 //pin lavado Rapido
#define MotorVelocidad2 2 //pin centrifugado Media
#define MotorVelocidad3 3 //pin centrifugado Rapido
// BOTONES
#define PushMenu  5 // pin boto Menu
#define PushLavado 6 //pin boton de Lavado
#define PushexprimeR  8 //pin boton de Centrifugado Rapido
#define PushInicioComp  13 // pin boton y puerta abierta (Inicia el Ciclo Completo)
#define PushCicloR 10 // Pin Boto Ciclo Rapido
// FUNCIONES
#define PinBuzzer  7 //BUZZER MUSICA FINAL
#define VaciadoPin 9 //pin bomba desague
#define AguaIn1 11 //pin electrovalcula prelavado o suavizante
//#define Hidronivel 12 // pin hidronivel
#define sensoragua A1 // Pin Hidronivel
#define variadonivel A0 // pin parametro de nivel de agua
//** Programa **//

void setup() {

  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  //RTC.adjust(DateTime(__DATE__, __TIME__));
  RTC.adjust(DateTime(2019, 12, 1, 0, 0, 0));
  lcd.begin(20,4);  // 20x4 LCD Panel
  lcd.setBacklightPin(3,POSITIVE);
 
 //declarando posición de las entradas de los pines
 /////////////////BOTONES////////////////////////////  
  pinMode(PushMenu,INPUT);
  pinMode(PushLavado,INPUT);
  pinMode(PushexprimeR,INPUT);
  pinMode(PushInicioComp,INPUT);
  pinMode(PushCicloR, INPUT);
  
  //pinMode(Hidronivel, INPUT);
  /////////////////////SALIDAS/////////////////////
  pinMode(AguaIn1, OUTPUT);
  pinMode(VaciadoPin, OUTPUT);
  pinMode(MotorVelocidad1, OUTPUT);
  pinMode(MotorVelocidad2, OUTPUT);
  pinMode(MotorVelocidad3, OUTPUT);
  pinMode(MotorVelocidad4, OUTPUT);
  
  /////////////PINES DE CONFIGURACION Y NIVELES DE AGUA /////////
  pinMode(sensoragua, INPUT);  
  pinMode(variadonivel, INPUT);  
   
 //INICIALIZO LOS PINES/////////////
  digitalWrite(AguaIn1, HIGH);
  digitalWrite(VaciadoPin, HIGH);
  digitalWrite(MotorVelocidad4, LOW);
  digitalWrite(MotorVelocidad1, LOW);
  digitalWrite(MotorVelocidad2, LOW);
  digitalWrite(MotorVelocidad3, LOW);  

lcd.backlight();
lcd.setCursor(3,0); 
lcd.print(F("FAMILIA RIVERA")); // Aqui podes poner lo que se Antoje yo use mi apellido por me parecio bien xd
lcd.setCursor(0,1);
lcd.print(F("     BIENVENIDO   "));
lcd.setCursor(0,2);
lcd.print(F("   PRESIONE MENU"));

}

void menu() {
push1 = digitalRead(PushMenu); //lee si el botón está pulsado

if((push1==LOW)&&(pushAnt1==HIGH)){ //si el boton es pulsado y antes no lo estaba
estado1++;
delay(20); //pausa de 40 ms
}
pushAnt1=push1; //actualiza el nuevo estado del boton
}

void lavado() {
push2 = digitalRead(PushLavado); //lee si el botón está pulsado

if((push2==LOW)&&(pushAnt2==HIGH)){ //si el boton es pulsado y antes no lo estaba
estado2++;
delay(20); //pausa de 40 ms
}
pushAnt2=push2; //actualiza el nuevo estado del boton
}

void centrifugadof() {
push3 = digitalRead(PushexprimeR); //lee si el botón está pulsado

if((push3==LOW)&&(pushAnt3==HIGH)){ //si el boton es pulsado y antes no lo estaba
estado3++;
delay(20); //pausa de 40 ms
}
pushAnt3=push3; //actualiza el nuevo estado del boton
}

void ciclocompleto() {
push4 = digitalRead(PushInicioComp); //lee si el botón está pulsado

if((push4==LOW)&&(pushAnt4==HIGH)){ //si el boton es pulsado y antes no lo estaba
estado4++;
delay(20); //pausa de 40 ms
}
pushAnt4=push4; //actualiza el nuevo estado del boton
}

void ciclorapidin() {
push5 = digitalRead(PushCicloR); //lee si el botón está pulsado

if((push5==LOW)&&(pushAnt5==HIGH)){ //si el boton es pulsado y antes no lo estaba
estado5++;
delay(20); //pausa de 40 ms
}
pushAnt5=push5; //actualiza el nuevo estado del boton
}


void loop()
{
menu();

switch (estado1) {
case 1:
lcd.clear();
lcd.setCursor(1,0);
lcd.print(F("1.CICLO RAPIDO"));
lcd.setCursor(1,1);
  lcd.print(F("2.LAVADO")); 
  lcd.setCursor(1, 2);
  lcd.print(F("3.EXPRIMIR RAPIDO"));
  lcd.setCursor(1,3);
  lcd.print(F("4.CICLO COMPLETO"));

case 2:
estado1=0;
break;
default: 
//
break;
}
lavado();

switch (estado2) {
case 1:

RTC.adjust(DateTime(2019, 12, 1, 0, 0, 0));
 
  cycleStart = millis();
  //VaciandoLavadora(15000, 0);//un poco de vaciado antes de comenzar 15 sec
  //delay(100);
  llenarAgua(1300000, 1);//JABÓN: valvula prelavado/suavizante 1, valvula jabon 2
  delay(100);
  MotorLavado(900000, 3);//LAVADO parametro1= tiempo de lavado, parametro2= pantalla "Lavando"//900000 
  delay(100);
  lcd.clear();
  lcd.setCursor(0,3);
  lcd.print(F("Lavado finalizado"));
  delay(5000);
  musica();
  musica();
  lcd.clear();
  lcd.noBacklight();
  
case 2:
estado2=0;
break;
default: 
//
break;
}
centrifugadof();

switch (estado3) {
case 1:

RTC.adjust(DateTime(2019, 12, 1, 0, 0, 0));

  cycleStart = millis();
  VaciandoLavadora(800000, 2);
  delay(1000);
  CentrifugadoSuave(70000);//SUAVE parametro1 = tiempo 1,5 minutos = 90000 ms
  CentrifugadoFuerte(200000);//FUERTE parametro1 = tiempo
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,3);
  lcd.print(F("Exprimir finalizado"));
  delay(5000);
  musica();
  musica();
  lcd.clear();
  lcd.noBacklight();
    
case 2:
estado3=0;
break;
default: 
//
break;
}
ciclocompleto();

switch (estado4) {
case 1:

RTC.adjust(DateTime(2019, 12, 1, 0, 0, 0));

  cycleStart = millis();
  //VaciandoLavadora(15000, 0);//un poco de vaciado antes de comenzar 15 sec
  //delay(100);
  //llenarAgua(330000, 1);//CUBETA PRELAVADO: valvula prelavado/suavizante 1, valvula jabon 2
  //(empezar) delay(100);
  //MotorLavado(600000, 4);//PRELAVADO 10 MINUTOS(600000) parametro1= tiempo de lavado, parametro2= pantalla "Lavando/Prelavado",
  //delay(100);
  //VaciandoLavadora(400000, 2);
  //delay(100);
  llenarAgua(1300000, 1); //JABÓN: valvula prelavado/suavizante 1, valvula jabon 2
  delay(100);
  MotorLavado(1400000, 3);//LAVADO parametro1= tiempo de lavado, parametro2= pantalla "Lavando" //1200000
  delay(100);
  VaciandoLavadora(800000, 2);//VACIA PARA COGER SUAVIZANTE
  delay(100);
  Centrifugalavado(60000);//SUAVE parametro1 = tiempo 1,5 minutos = 90000 ms
  delay(100);
  llenarAgua(1300000, 1);//SUAVIZANTE: valvula prelavado/suavizante 1, valvula jabon 2
  delay(5000);
  MotorLavado(640000, 5);//SUAVIZANTE parametro1= tiempo, parametro2= pantalla "Suavizante"//480000
  delay(100);
  VaciandoLavadora(800000, 2);
  delay(1000);
  Centrifugalavado(60000);//SUAVE parametro1 = tiempo 1,5 minutos = 90000 ms
  delay(100);
  llenarAgua(1300000, 1);//SUAVIZANTE: valvula prelavado/suavizante 1, valvula jabon 2
  delay(500);
  MotorLavado(420000, 5);//SUAVIZANTE parametro1= tiempo, parametro2= pantalla "Suavizante"//480000
  delay(9000);
  VaciandoLavadora(800000, 2);//VACIA PARA COGER SUAVIZANTE
  delay(3000);
  CentrifugadoSuave(60000);//SUAVE parametro1 = tiempo 1,5 minutos = 90000 ms
  CentrifugadoFuerte(200000);//FUERTE parametro1 = tiempo
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,3);
  lcd.print(F("Lavado finalizado"));
  delay(5000);
  musica();
  musica();
  delay(2000);
  lcd.clear();
  lcd.noBacklight();
  
case 2:
estado4=0;
break;
default: 
//
break;
}

ciclorapidin();

switch (estado5) {
case 1:

RTC.adjust(DateTime(2019, 12, 1, 0, 0, 0));

  cycleStart = millis();
  //VaciandoLavadora(15000, 0);//un poco de vaciado antes de comenzar 15 sec
  //delay(100);
  //llenarAgua(330000, 1);//CUBETA PRELAVADO: valvula prelavado/suavizante 1, valvula jabon 2
  //(empezar) delay(100);
  //MotorLavado(600000, 4);//PRELAVADO 10 MINUTOS(600000) parametro1= tiempo de lavado, parametro2= pantalla "Lavando/Prelavado",
  //delay(100);
  //VaciandoLavadora(400000, 2);
  //delay(100);
  llenarAgua(1300000, 1); //JABÓN: valvula prelavado/suavizante 1, valvula jabon 2
  delay(100);
  MotorLavado(850000, 3);//LAVADO parametro1= tiempo de lavado, parametro2= pantalla "Lavando" //1200000
  delay(100);
  VaciandoLavadora(800000, 2);//VACIA PARA COGER SUAVIZANTE
  delay(100);
  Centrifugalavado(60000);//SUAVE parametro1 = tiempo 1,5 minutos = 90000 ms
  delay(100);
  llenarAgua(1300000, 1);//SUAVIZANTE: valvula prelavado/suavizante 1, valvula jabon 2
  delay(5000);
  MotorLavado(420000, 5);//SUAVIZANTE parametro1= tiempo, parametro2= pantalla "Suavizante"//480000
  delay(100);
  VaciandoLavadora(800000, 2);
  delay(100);
  Centrifugalavado(60000);//SUAVE parametro1 = tiempo 1,5 minutos = 90000 ms
  delay(100);
  llenarAgua(1300000, 1);//SUAVIZANTE: valvula prelavado/suavizante 1, valvula jabon 2
  delay(5000);
  MotorLavado(270000, 5);//SUAVIZANTE parametro1= tiempo, parametro2= pantalla "Suavizante"//480000
  delay(7000);
  VaciandoLavadora(800000, 2);  
  delay(2000);
  CentrifugadoSuave(60000);//SUAVE parametro1 = tiempo 1,5 minutos = 90000 ms
  CentrifugadoFuerte(170000);//FUERTE parametro1 = tiempo
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,3);
  lcd.print(F("Lavado finalizado"));
  delay(5000);
  musica();
  musica();
  delay(2000);
  lcd.clear();
  lcd.noBacklight();
  
case 2:
estado5=0;
break;
default: 
//
break;
}

}

//==================================================================================================
//====================================FUNCIONES DEPURADAS===========================================
//==================================================================================================
double Hidronivel(int RawADC) {

  double kpascal;
  int sensorVal = 0;
  int sensorPin = A1;
//  int kpascal = 0;
//float Nmedia;
//float N = 0;
//int nivel1, decimas;

sensorVal = analogRead(sensorPin);
kpascal=map(sensorVal, 378, 745,  0, 10);
delay(100);
return kpascal;
}

double nivelControl(int RawADC) {

  double parametro;
  int variadorVal = 0;
  int variadorPin = A0;

variadorVal = analogRead(variadorPin);
parametro=map(variadorVal, 602, 980,  0, 10);
delay(100);

return parametro;
}

void llenarAgua(unsigned long tiempo, int nivelagua) { //DOBLE SISTEMA DE SEGURIDAD, POR TIEMPO Y POR HIDRONIVEL
  lcd.begin(20,4);
  lcd.clear();
  muestraPantalla(1);
 unsigned long tiempollenado = millis();
 
 int val = analogRead(A1);
 int val22 = analogRead(A0);
 //VARIABLE DE SENSOR & PARAMETRO;
 double kpascal = Hidronivel(val);
 double parametro = nivelControl(val22);
 
 delay(4000); 
 digitalWrite(AguaIn1, LOW);     
            
 while (((millis() - tiempollenado) < tiempo) && (kpascal < parametro  ))  {
 //el Llenado inicialmente esta inicializado por tiempo mientras no se cumple el tiempo esta activado el motor de llenado hasta que el sensor mpx10p sense o sea mayor al del parametro
            if(kpascal > parametro){digitalWrite(AguaIn1, HIGH);}
            kpascal = Hidronivel(val);
            parametro = nivelControl(val22);
            muestraPantalla(1);
            Serial.print(kpascal);
            Serial.println(parametro);
            delay(100);
            }
                       
      digitalWrite(AguaIn1, HIGH);
      delay(1000);
} 
void VaciandoLavadora(unsigned long tiempo, int pantalla) {//argumento1=tiempo, argumento2=1(iniciando) 2(vaciando)
  lcd.begin(20,4);  // La pantalla aparece cuando el motor entra en acción
  lcd.clear();
  muestraPantalla(pantalla);
  unsigned long vaciadoTiempo = millis();                      
  int val1 = analogRead(A1);
 //int nivel;
  double kpascal = Hidronivel(val1); 
  delay(100);
  
  while (((millis() - vaciadoTiempo) < tiempo) && (0 < kpascal )) {  
    if(0 < kpascal){digitalWrite(VaciadoPin, LOW);}else{digitalWrite(VaciadoPin, HIGH);}
    kpascal = Hidronivel(val1);
    muestraPantalla(pantalla);
    delay(100);
  }
  digitalWrite(VaciadoPin, HIGH);
  delay(8000);
}
void MotorLavado(unsigned long tiempo, int pantalla) { //argumento1=tiempo, argumento2=indicación pantalla,
  lcd.begin(20,4);  // La pantalla aparece cuando el motor entra en acción
  lcd.clear();
  muestraPantalla(pantalla);
  unsigned long tmpmotorgiro = millis();
   
      while ((millis() - tmpmotorgiro) < tiempo) { //mientras lavado, gira en motor en ambos sentidos 
        muestraPantalla(pantalla);
              //GIRA A DERECHA
              digitalWrite(MotorVelocidad1, HIGH);
              digitalWrite(MotorVelocidad2, HIGH); //Pin de Activacion de Relay "OJO con Corto Circuito"
              delay(5000);            
              digitalWrite(MotorVelocidad1, LOW);
              digitalWrite(MotorVelocidad2, LOW);
              delay(3500);   
              // GIRA A IZQUIERDA
              digitalWrite(MotorVelocidad1, HIGH);
              digitalWrite(MotorVelocidad4, HIGH); //Pin de Activacion de Relay "OJO con Corto Circuito" 
              delay(5000);            
              digitalWrite(MotorVelocidad1, LOW);
              digitalWrite(MotorVelocidad4, LOW);
              delay(3500);   
                                        
    }    
}
void CentrifugadoSuave(unsigned long tiempo) {
  lcd.begin(20,4);  // La pantalla aparece cuando el motor entra en acción
  lcd.clear();
  muestraPantalla(6);
  unsigned long tmpmotorgiro = millis(); 
    
    while ((millis() - tmpmotorgiro) < tiempo) { //mientras lavado, gira en motor en ambos sentidos
               digitalWrite(MotorVelocidad1, HIGH);
               digitalWrite(MotorVelocidad3, HIGH); //solo el 3 500 rpm
               digitalWrite(VaciadoPin, LOW);
               delay(100);
               muestraPantalla(6);
    }
  digitalWrite(VaciadoPin, LOW);
  digitalWrite(MotorVelocidad1, HIGH);
  digitalWrite(MotorVelocidad2, HIGH);
  digitalWrite(MotorVelocidad3, LOW);
  muestraPantalla(6);
  delay(20000);//20000

  digitalWrite(VaciadoPin, LOW);
  digitalWrite(MotorVelocidad1, LOW);
  digitalWrite(MotorVelocidad2, LOW);
  digitalWrite(MotorVelocidad3, LOW);
  muestraPantalla(6); 
  delay(8000);
}

void CentrifugadoFuerte(unsigned long tiempo) {
  lcd.begin(20,4);  // La pantalla aparece cuando el motor entra en acción
  lcd.clear();
  muestraPantalla(7);
  unsigned long tmpmotorgiro = millis(); 
  
    while ((millis() - tmpmotorgiro) < tiempo) { //mientras lavado, gira en motor en ambos sentidos
              digitalWrite(MotorVelocidad1, HIGH);
              digitalWrite(MotorVelocidad2, HIGH);
              digitalWrite(VaciadoPin, LOW);
          delay(100);
          muestraPantalla(7);
  }
  digitalWrite(VaciadoPin, LOW);
  digitalWrite(MotorVelocidad1, HIGH);
  digitalWrite(MotorVelocidad2, HIGH);
  digitalWrite(MotorVelocidad3, HIGH);
  muestraPantalla(7);
  delay(30000);//270000

  muestraPantalla(7);
  delay(8000);
  
  digitalWrite(VaciadoPin, HIGH);
  digitalWrite(MotorVelocidad1, LOW);
  digitalWrite(MotorVelocidad2, LOW);
  digitalWrite(MotorVelocidad3, LOW);
  muestraPantalla(7);
  delay(2000);
}

void Centrifugalavado(unsigned long tiempo) {
  lcd.begin(20,4);  // La pantalla aparece cuando el motor entra en acción
  lcd.clear();
  muestraPantalla(6);
  unsigned long tmpmotorgiro = millis(); 
    while ((millis() - tmpmotorgiro) < tiempo) { //mientras lavado, gira en motor en ambos sentidos
               digitalWrite(MotorVelocidad1, HIGH);
               digitalWrite(MotorVelocidad3, HIGH); //solo el 3 500 rpm
               digitalWrite(VaciadoPin, LOW);
               delay(100);
               muestraPantalla(6);
    }
  muestraPantalla(6);
  delay(5000);
  digitalWrite(VaciadoPin, LOW);  
  digitalWrite(MotorVelocidad1, HIGH);
  digitalWrite(MotorVelocidad2, HIGH);
  digitalWrite(MotorVelocidad3, LOW);
  delay(30000);//150000

  muestraPantalla(6);
  delay(8000);
  
  digitalWrite(VaciadoPin, HIGH);
  digitalWrite(MotorVelocidad1, LOW);
  digitalWrite(MotorVelocidad2, LOW);
  digitalWrite(MotorVelocidad3, LOW);
  muestraPantalla(6);
  delay(5000);
}
void musica(){
    for (int thisNote = 0; thisNote < 18; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(7, melody[thisNote],noteDuration); //conecta el pin 7
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(7); //desconecta el pin 7
  }
}
//==================================================================================================
void muestraPantalla(byte currentMode) {  // Necesita trabajarla

  int hora=0; // Variable donde se guardara la hora
  int minutos=0; // Variable donde se guardaran los minutos
  int segundos=0; // Variable donde se guardaran los segundos


  DateTime now = RTC.now();
  hora=(now.hour(),DEC);
  minutos=(now.minute(),DEC);
  segundos=(now.second(),DEC);
  
  lcd.setCursor(0,0);
  lcd.print("Tiempo: ");
  
    lcd.setCursor(8,0);
    lcd.print(now.hour(), DEC);
    lcd.print(":");
    
    lcd.setCursor(11,0);  
    lcd.print(now.minute(), DEC);
    lcd.print(":");
    
    lcd.setCursor(14,0);
    lcd.print(now.second(), DEC);

//Nivel de Agua
    int val=analogRead(A1);//Lee el valor del pin analogo 2 y lo mantiene como val              
    double kpascal = Hidronivel(val);//Realiza la conversión del valor analogico a nivel digital 

    int val50 = analogRead(A0);
    double parametro = nivelControl(val50);
    
    lcd.setCursor(0,2);
    lcd.print(F("Nivel Agua: "));  
    lcd.println(kpascal);

    
    lcd.setCursor(0,1);
    lcd.print(F("Parametro: "));  
    lcd.println(parametro);

    delay (100);
  
  lcd.setCursor(0,3);
  
  switch (currentMode) {
  case 0:
    lcd.print(F("Iniciando"));
    break;
    case 1:
    lcd.print(F("Llenando"));
    break;
  case 2:
    lcd.print(F("Vaciando"));
    break;
  case 3:
    lcd.print(F("Lavando ropa"));
    break;
  case 4:
    lcd.print(F("10 minutos Prelavado"));
    break;
  case 5:
    lcd.print(F("Suavizante"));
    break;
  case 6:
    lcd.print(F("Centrifugado suave"));
    break;
  case 7:
    lcd.print(F("Centrifugado fuerte"));
    break;
  }  
}
