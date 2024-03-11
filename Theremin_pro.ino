#define MIN_DISTANCIA 30
#define FRECUENCIA_ADDED 500

/* https://www.luisllamas.es/reproducir-sonidos-arduino-buzzer-pasivo-altavoz/ */

int echoSensor1 = 9; // Pin para echo
int triggerSensor1 = 10; // Pin para trigger
int speaker = 11; // Pin para el buzzer unsigned long tiempoRespuesta; unsigned long distancia; float freqRad; int tono;


int echoSensor2 = 5; // Pin para echo
int triggerSensor2 = 4; // Pin para trigger
int tonoSensor1;
int tonoSensor2;
int distanciaSensor1;
int distanciaSensor2;
int tiempoRespuestaSensor1;
int tiempoRespuestaSensor2;
float freqRadSensor1;
float freqRadSensor2;


void setup() { 
  pinMode(speaker, OUTPUT);
  pinMode(triggerSensor1, OUTPUT);
  pinMode(echoSensor1, INPUT);
  pinMode(triggerSensor2, OUTPUT);
  pinMode(echoSensor2, INPUT);

  // Begin Serial communication at a baudrate of 9600: 
  Serial.begin(9600); 
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
  }

  tone(speaker, tonoSensor1+tonoSensor2+FRECUENCIA_ADDED); 

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
