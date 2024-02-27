#define MIN_DISTANCIA 30

/* https://www.luisllamas.es/reproducir-sonidos-arduino-buzzer-pasivo-altavoz/ */

int echo = 9;     // Pin para echo                          
int trigger = 10; // Pin para trigger                               
int speaker = 11; // Pin para el buzzer
unsigned long tiempoRespuesta;
unsigned long distancia;
float freqRad;
int tono;

void setup() {
  pinMode(speaker, OUTPUT);                  
  pinMode(trigger, OUTPUT);                     
  pinMode(echo, INPUT);

                      
  //Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);
 } 

void loop() {
  digitalWrite(trigger, HIGH);            // Enviamos pulso de 10 microsegundos
  delayMicroseconds(10);                        
  digitalWrite(trigger, LOW);                   
  tiempoRespuesta = pulseIn(echo, HIGH);  // Y esperamos pulso de vuelta
  distancia = tiempoRespuesta/58;         // Calculo de distancia en cm


  if (distancia < MIN_DISTANCIA) {
    freqRad = sin(distancia*(3.14/180)); // Pasamos frecuencia a radianes
    tono = 2000+(int(freqRad*1000));     // calculamos el tono        
    tone(speaker, tono, 500);
  } 

  
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance = ");
  Serial.print(distancia);
  Serial.println(" cm");

}
