
//Declaración de pines
int led_blanco = 22;
int led_azul = 23;
int led_verde = 24;
int led_naranja = 25;
int led_rojo = 26;

int potenciometro = A0;
int pulsadores = A1;

//Declaración de variables
int valor_sw = 0;
int valor_pot = 0;

//Inicialización de pines
void setup() {
  Serial.begin(9600);
  pinMode(led_blanco,OUTPUT);
  pinMode(led_azul,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_naranja,OUTPUT);
  pinMode(led_rojo,OUTPUT);

  //Encender leds
  digitalWrite(led_blanco, HIGH);
  digitalWrite(led_azul, HIGH);
  digitalWrite(led_verde, HIGH);
  digitalWrite(led_naranja, HIGH);
  digitalWrite(led_rojo, HIGH);
}

//Ejecutivo cíclico
void loop() {
  valor_sw = analogRead(pulsadores);
  valor_pot = analogRead(potenciometro);
/* Significado de las lecturas:
 * Blanco:848
 * Azul:335
 * Verde:503
 * Naranja:674
 * Rojo:167
 */
  if(valor_sw>800){
    Serial.print("Pulsador blanco ");
  }else{
      if(valor_sw>600){
        Serial.print("Pulsador naranja ");
      }else{
          if(valor_sw>500){
           Serial.print("Pulsador verde ");
           }else{
              if(valor_sw>300){
                Serial.print("Pulsador azul ");
              }else{
                if(valor_sw>150){
                  Serial.print("Pulsador rojo ");
                  }else Serial.print("No pulsado");
              }
           }
      }
  }
   
  Serial.print(" Potenciometro: ");
  Serial.println(valor_pot);
  delay(100);        // delay in between reads for stability
}
