/*ProgramaTeste: V7.0
  *29/07/2020
  *Programa para testar o robo junto a um magnetometro
  */
  #include <Coordinates.h> //Biblioteca que converte valores de retangular para polar
  #include "MPU9250.h" //Biblioteca do sensor Magnetometro / Giroscopio / Acelerometro
  #include <EEPROM.h> // Biblioteca da EEPROM do arduino, usada para armazanar os valores da parametrização
  
  Coordinates Angulo = Coordinates();
  
  MPU9250 IMU(Wire,0x68);
  int status;


  //#define N 3

//*********Ultrassonico********
//Sensor Frontal
  #define trigF 4
  #define echoF 5
  
//Sensor Lateral Direito
  #define trigDir 6
  #define echoDir 7
  
//Sensor Lateral Esquerdo
  #define trigEsq 2
  #define echoEsq 3

//***********Ponte H*********
  //Motor Direito
  #define IN1 53
  #define IN2 51

  //Motor Esquerdo
  #define IN3 49
  #define IN4 47

  //Controle de velocidade
  #define En1 8
  #define En2 9


//X / max / min 7400.42 / 3647.85  Y / max / min 4311.10 / 2111.91 ENIAC - MESA DO PC
//X / max / min 7714.59 / 3804.93  Y / max / min 4328.55 / 575.98
//X / max / min 8325.48 / 4154.01  Y / max / min 4241.28 / 209.45
//mesa de casa X / max / min 8203.30 / 3822.39  Y / max / min 4311.10 / 52.36
  

//Variáveis para o sensor magnetometro  
  float Xmin = 1000000;
  float Ymin = 1000000;
  float Ymax = -1000000;
  float Xmax = -1000000;

  float Xmed, Ymed;

  int Defasagem = 0;
  float ang;
  float ang2;
  char dir;
    
  #define NMag 200
  unsigned long ValoresMag[NMag],
               SomatoriaMag = 0;
  
   #define Total 3 //Total de médias móveis utilizadas
   #define N 3
   unsigned long Valores[Total][N],
                 Somatoria = 0;

  byte Entradas [] = {echoF, echoDir, echoEsq};
  byte Saidas [] = {IN1, IN2, IN3, IN4, En1, En2, trigF, trigDir, trigEsq};

//************************************************************////SETUP\\\\***********************************************
void setup() 
{
   pinMode(50, INPUT_PULLUP);
  // serial to display data
  Serial.begin(9600);
  Serial1.begin(9600); // Módulo bluetooth
  
  pinMode(13, OUTPUT);
  
  while(!Serial){digitalWrite(13,!digitalRead(13));}
  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) 
  {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1){digitalWrite(13,!digitalRead(13)); delay(100);}
  }

  for(byte i = 0; i < sizeof(Saidas); i++) pinMode(Saidas[i], OUTPUT);
  for(byte i = 0; i < sizeof(Entradas); i++) pinMode(Entradas[i], INPUT);

  analogWrite(En1, 70);//Direito
  analogWrite(En2, 80);//Esquerdo


  if(digitalRead(50) == LOW)
  {
    digitalWrite(13,HIGH); delay(500); digitalWrite(13,LOW);
    Calibra();  
    delay(2000);
  }
  else
  {
    Atualiza_Parametro_EEPROM();  
  }
  analogWrite(En1, 210);//Direito
  analogWrite(En2, 250);//Esquerdo
  
 
    Encher_Filtros(); //Faz algumas leituras com os ultrassonicos para encher os endereços do filtro 
    Encher_Filtros(); //Faz algumas leituras com os ultrassonicos para encher os endereços do filtro 
    Para();
}

//************************************************************////LOOP\\\\***********************************************
void loop() 
{
 
  
  Logica();
  //Medir();
  Serial1.print(dir);Serial1.print(" ");
            Serial1.println(Medir());
  if(digitalRead(50) == LOW)
  {
    if(ang2 >= 157)
    {
      Defasagem += (ang2 - 157) * -1;
    }
    if(ang2 < 157)
    {
      Defasagem += 157 - ang2;
    }
    delay(500);
  }
} 
