/*   ----------------
 *   |IR|IR|IR|IR|IR|
 *   A11 A2 A3 A4 A10
 *   ----------------
*/

//Declaración de variables
int IR_izqizq, IR_izq, IR_cntr, IR_dch, IR_dchdch = 0;

void setup(){  
  Serial.begin(9600);
}  
   
void loop(){  
  IR_izqizq=analogRead(A11); 
  IR_izq= analogRead(A2);
  IR_cntr= analogRead(A3);
  IR_dch= analogRead(A4);
  IR_dchdch= analogRead(A10);

  //Negro > 400
  //Blanco< 100
  
  Serial.print(IR_izqizq); 
  Serial.print(" "); 
  Serial.print(IR_izq);
  Serial.print(" "); 
  Serial.print(IR_cntr); 
  Serial.print(" "); 
  Serial.print(IR_dch);    
  Serial.print(" "); 
  Serial.println(IR_dchdch); 
 
  delay(1000);
}

