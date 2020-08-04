//***************************************//Calibração sensor Mag\\*************************************
void Calibra()
{
        float X, Y;
        
        Direita('F');
        for(int i = 0; i < 20000; i++) //Parametrizaçã o do sensor
        {
                IMU.readSensor();
                X = (IMU.getMagX_uT()*100);
                Y = (IMU.getMagY_uT()*100);
            //800
                  // 1400 < 800
                  if(Xmax < X)
                {
                      Xmax = X; // 1400
                }
                if(Ymax < Y)
                {
                      Ymax = Y;
                }
              
                if(Xmin > X)
                {
                      Xmin = X; 
                }
                if(Ymin > Y)
                {
                     Ymin = Y;
                }
                
                delay(1);
        }
  
        Para();
        Serial1.print("X / max / min ");  Serial1.print(Xmax); Serial1.print(" / "); Serial1.print(Xmin);
        Serial1.print("  Y / max / min "); Serial1.print(Ymax); Serial1.print(" / "); Serial1.println(Ymin);

        long Xmin2, Ymin2, Xmax2, Ymax2;
        Xmin2 = Xmin; Ymin2 = Ymin; Xmax2 = Xmax; Ymax2 = Ymax;

       if(Xmin2 < 0) { Xmin2 *= -1; EEPROM.write(0, 1);}
       else{EEPROM.write(0, 0);}
       EEPROM.write(1,Xmin2 >> 8);
       EEPROM.write(2, Xmin2 & 0XFF);

       if(Ymin2 < 0) { Ymin2 *= -1; EEPROM.write(3, 1);}
       else{EEPROM.write(3, 0);}
       EEPROM.write(4,Ymin2 >> 8);
       EEPROM.write(5, Ymin2 & 0XFF);

       if(Ymax2 < 0) { Ymax2 *= -1; EEPROM.write(6, 1);}
       else{EEPROM.write(6, 0);}
       EEPROM.write(7,Ymax2 >> 8);
       EEPROM.write(8, Ymax2 & 0XFF);
    
       if(Xmax2 < 0) { Xmax2 *= -1; EEPROM.write(9, 1);}
       else{EEPROM.write(9, 0);}
       EEPROM.write(10,Xmax2 >> 8);
       EEPROM.write(11, Xmax2 & 0XFF);
}

void Atualiza_Parametro_EEPROM() //Atualiza os varores do parametro com  o que está guardado na EEPROM.
{
   Xmin = (EEPROM.read(1)<<8) + EEPROM.read(2);
   if(EEPROM.read(0) == 1) Xmin *= -1;

   Ymin = (EEPROM.read(4)<<8) + EEPROM.read(5);
   if(EEPROM.read(3) == 1) Ymin *= -1;

   Ymax = (EEPROM.read(7)<<8) + EEPROM.read(8);
   if(EEPROM.read(6) == 1) Ymax *= -1;

   Xmax = (EEPROM.read(10)<<8) + EEPROM.read(11);
   if(EEPROM.read(9) == 1) Xmax *= -1;

   Serial1.print("X / max / min ");  Serial1.print(Xmax); Serial1.print(" / "); Serial1.print(Xmin);
   Serial1.print("  Y / max / min "); Serial1.print(Ymax); Serial1.print(" / "); Serial1.println(Ymin);   

}

//***************************************//Medição sensor Mag\\*************************************

long Medir() //Faz um mapeamento dos valorez máximos e minimos para manter a proporção entre os eixos X e Y
{
  //for(int i = N; i > 0; i--)
//   {
      IMU.readSensor();
    
      Xmed = map((IMU.getMagX_uT()*100), Xmin, Xmax, -1000, 1000);
      Ymed = map((IMU.getMagY_uT()*100), Ymin, Ymax, -1000, 1000);
      //Serial.print("X = "); Serial.print(Xmed); Serial.print(" Y = "); Serial.println(Ymed);
      Calcular();
   //}
   long Dist_Filtrada = Filtro_Mag(ang);
// Serial1.print(dir);Serial1.print(" ");
//  Serial1.println(Dist_Filtrada);
  return (Dist_Filtrada);
}

//***************************************//Calculo sensor Mag\\*************************************
void Calcular() //Calcula o angulo com base nos valores dos eixos X e Y, fazendo uma conversão de retangular para polar
{
   Angulo.fromCartesian(Ymed,Xmed);
   ang =  Angulo.getAngle(); //entr 0 e 6,28 -  628
   ang *= 100;
   ang2 = ang+Defasagem;
   ang += Defasagem;
   if(ang > 628) ang -= 628; 
   if(ang < 0) ang += 628; 
   if(ang <= 314) {ang = map(ang, 0, 314, 0, 180); dir = '+'; }//Mapeamento do valor resultando do calculo, para o angulo de 0 a 360
   if(ang > 314){ang = map(ang, 315, 628, 180, 0); dir = '-';} //Mapeamento do valor resultando do calculo, para o angulo de 0 a 360
  

   //Filtro_Mag(ang);
  /*Serial1.print(dir);Serial1.print(" ");
  Serial1.println(Filtro_Mag(ang));*/
}
//***************************************//Filtro sensor Mag\\*************************************
long Filtro_Mag(long pulso)
{

  int i;
  SomatoriaMag = 0; 
  
  for (i = NMag; i > 0; i--) ValoresMag[i] = ValoresMag[i-1];
  
  ValoresMag[0] = pulso;  

  for (i = 0; i < NMag; i++) SomatoriaMag = SomatoriaMag + ValoresMag[i];

  return (SomatoriaMag/NMag);
  
}
//***************************************//Leituras Utrassonicos\\*************************************
float LeituraF(){
 float temp; 
  for(int i = 0; i < N; i++)
   {
  
    digitalWrite(trigF, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigF, LOW);
      temp = Distancia_Fltrada(pulseIn(echoF, HIGH) , 0);
   }
   temp /= 58;
  //float temp = pulseIn(echoF, HIGH) /58;
  return temp;
 // delay(50);
}

float LeituraDir(){
 float temp;
  for(int i = 0; i < N; i++)
   {
    digitalWrite(trigDir, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigDir, LOW);
     temp = Distancia_Fltrada(pulseIn(echoDir, HIGH) , 1);
   }
  temp /= 58;
 // float temp = pulseIn(echoDir, HIGH) /58;
  return temp;
  //delay(50);
}

float LeituraEsq(){
  float temp;
  for(int i = 0; i < N; i++)
   {
    digitalWrite(trigEsq, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigEsq, LOW);
      temp = Distancia_Fltrada(pulseIn(echoEsq, HIGH) , 2);
   }
  temp /= 58;
  //float temp = pulseIn(echoEsq, HIGH) /58;
  return temp;
  //delay(50);
}

//***************************************//Filtro Utrassonicos\\*************************************
long Distancia_Fltrada(long pulso, byte T)
{

  int i;
  Somatoria = 0; 
  
  for (i = N-1; i > 0; i--) Valores[T][i] = Valores[T][i-1];
  Valores[T][0] = pulso;  

  for (i = 0; i < N; i++) Somatoria += Valores[T][i];  //Serial.print(i); Serial.print(" ");   Serial.print(Valores[0][i]); Serial.print(" "); Serial.print(Valores[1][i]); Serial.print(" "); Serial.println(Valores[2][i]);}

  return (Somatoria/N);
  
}

void Encher_Filtros()
{
  for(byte i = 0; i < N; i++)
  {
    LeituraEsq();
    LeituraDir();
    LeituraF();
  }
  for (int i = 0; i < 200; i++) Medir();
}

//***************************************//Comandos Ponte H \\*************************************
void Frente()
{
  //Liga Lado Direito
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Liga Lado Esquerdo 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Tras()
{
    //Liga Lado Direito
  digitalWrite(IN2, HIGH);
  digitalWrite(IN1, LOW);
  //Liga Lado Esquerdo 
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
}

void Esquerda(char Tipo)
{
    switch (Tipo)
  {
  case 'F':
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    //Liga Lado Esquerdo 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
   break;

   case 'A':
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    //Liga Lado Esquerdo 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
   break;
  
  }
}

void Direita(char Tipo)
{

  switch (Tipo)
  {
  case 'F':
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    //Liga Lado Esquerdo 
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
   break;

   case 'A':
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    //Liga Lado Esquerdo 
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
   break;
  
  }
}
void Para()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
