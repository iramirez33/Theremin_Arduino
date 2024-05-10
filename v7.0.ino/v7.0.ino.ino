#define MIN_DISTANCIA 50
#define FRECUENCIA_ADDED 500
#include <SPI.h>
#include <SD.h>   
File myFile; 

/* https://www.luisllamas.es/reproducir-sonidos-arduino-buzzer-pasivo-altavoz/ */

int echoSensor1 = 11; // Pin para echo
int triggerSensor1 = 12; // Pin para trigger
int speaker1 = 13; // Pin para el buzzer unsigned long tiempoRespuesta; unsigned long distancia; float freqRad; int tono;

int echoSensor2 = 8; // Pin para echo
int triggerSensor2 = 7; // Pin para trigger
int speaker2 = 9;

int interruptor = 2;

/*Tarjeta sd*/

int cs = 6;
int sck = 5;
int mosi = 4;
int miso = 3;


int tonoSensor1;
int tonoSensor2;
unsigned long distanciaSensor1;
unsigned long distanciaSensor2;
unsigned long tiempoRespuestaSensor1;
unsigned long tiempoRespuestaSensor2;
float freqRadSensor1;
float freqRadSensor2;

File fileS1;
File fileS2;

bool recording = false;

void setup() { 
  pinMode(speaker1, OUTPUT);
  pinMode(triggerSensor1, OUTPUT);
  pinMode(echoSensor1, INPUT);

  pinMode(speaker2, OUTPUT);
  pinMode(triggerSensor2, OUTPUT);
  pinMode(echoSensor2, INPUT);

  pinMode(interruptor, INPUT);


  // Begin Serial communication at a baudrate of 9600: 
  Serial.begin(9600); 

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(cs)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  fileS1 = SD.open("S1.txt", FILE_WRITE);
  fileS2 = SD.open("S2.txt", FILE_WRITE);


}

void loop() { 

  // SENSOR1
  digitalWrite(triggerSensor1, HIGH); // Enviamos pulso de 10 microsegundos delayMicroseconds(10);
  digitalWrite(triggerSensor1, LOW);

  tiempoRespuestaSensor1 = pulseIn(echoSensor1, HIGH); // Y esperamos pulso de vuelta 
  distanciaSensor1 = tiempoRespuestaSensor1/58; // Calculo de distancia en cm

  if (distanciaSensor1 < MIN_DISTANCIA) { 
    freqRadSensor1 = sin(distanciaSensor1*(3.14/180)); // Pasamos frecuencia a radianes 
    tonoSensor1 = (int(freqRadSensor1*1000)); // calculamos el tono
    // tone(speaker, tonoSensor1); 
    tone(speaker1, tonoSensor1+FRECUENCIA_ADDED); 

  } else {
    noTone(speaker1);  
  }

  // SENSOR2
  digitalWrite(triggerSensor2, HIGH); // Enviamos pulso de 10 microsegundos delayMicroseconds(10);
  digitalWrite(triggerSensor2, LOW);
  
  tiempoRespuestaSensor2 = pulseIn(echoSensor2, HIGH); // Y esperamos pulso de vuelta 
  distanciaSensor2 = tiempoRespuestaSensor2/58; // Calculo de distancia en cm

  if (distanciaSensor2 < MIN_DISTANCIA) { 
    freqRadSensor2 = sin(distanciaSensor2*(3.14/180)); // Pasamos frecuencia a radianes 
    tonoSensor2 = (int(freqRadSensor2*1000)); // calculamos el tono
    // tone(speaker, tonoSensor2); 
    tone(speaker2, tonoSensor2+FRECUENCIA_ADDED); 

  } else {
    noTone(speaker2);  
  }

  

  // Print the distance on the Serial Monitor (Ctrl+Shift+M): 
  Serial.print("DistanceSensor1 = "); 
  Serial.print(distanciaSensor1); 
  Serial.println(" cm");

  Serial.print("DistanceSensor2 = "); 
  Serial.print(distanciaSensor2); 
  Serial.println(" cm");

  Serial.print("TonoSensor1 = "); 
  Serial.print(tonoSensor1); 
  Serial.println(" Hz");

  Serial.print("TonoSensor2 = "); 
  Serial.print(tonoSensor2); 
  Serial.println(" Hz");

}
