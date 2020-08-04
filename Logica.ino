void Logica()
{
 
  if(LeituraF() < 4 )
  {
    Para();

     if(LeituraDir() > LeituraEsq())
     {
       Virar_D();
     }
     else if(LeituraDir() < LeituraEsq())
     {
       Virar_E();
     }
    
  }
  else
  {
    Frente();
  }
}

void Virar_D()
{
  Serial1.println("Virar para Direita");
  for (int i = 0; i < 200; i++) Medir();
  
  long AnguloD =  Medir();
  long AnguloObjetivo;
  int Temp;
  
   analogWrite(En1, 90);//Direito
   analogWrite(En2, 190);//Esquerdo
  if(dir == '+')
  { 
          if(AnguloD <= 90)
          {
                   AnguloObjetivo = AnguloD + 90; 
                   Serial1.print("Angulo: "); Serial1.println(dir); Serial1.print(AnguloD); Serial1.print("  Angulo final: "); Serial1.print("+"); Serial1.println(AnguloObjetivo);
                  // delay(500);             
                   Direita('F');
                   delay(1900);
                   Para();
                   delay(200);
                   for (int i = 0; i < 200; i++) Medir();
                 
                   while (Medir() < AnguloObjetivo && dir != '-')
                   {
                         if(AnguloObjetivo - Medir() > 15 )  Temp = 300;
                         else Temp = 100;
                         delay(100);
                         Direita('F');
                         delay(Temp);
                         Para();
                         for (int i = 0; i < 200; i++) Medir();
                         Serial1.print(dir);Serial1.print(" ");
                         Serial1.println(Medir());                  
                   }
                   
           }
           else if(AnguloD > 90)
           {
                   AnguloObjetivo = AnguloD - 90;
                   AnguloObjetivo = 180 - AnguloObjetivo;
                    Serial1.print("Angulo: "); Serial1.print(dir); Serial1.print(AnguloD); Serial1.print("  Angulo final: "); Serial1.print("-"); Serial1.println(AnguloObjetivo);
                    Direita('F');
                   delay(1900);
                   Para();
                   delay(200);
                   for (int i = 0; i < 200; i++) Medir();
                    
                    while (dir != '-' )
                    {
                          if(180 - AnguloObjetivo > 15 ) Temp = 300;
                          else if(180 - Medir() > 15)Temp = 300;
                          else Temp = 100;
                          delay(10);
                          Direita('F');
                          delay(Temp);
                          Para();
                          for (int i = 0; i < 200; i++) Medir();
                          Serial1.print(dir);Serial1.print(" ");
                          Serial1.println(Medir());  
                    }
              
                    Direita('F');
                    delay(200);
                    Para();
                  
                   while (Medir() > AnguloObjetivo )
                    {
                         if(Medir() - AnguloObjetivo > 15 ) Temp = 300;
                         else Temp = 100;
                         delay(100);
                         Direita('F');
                         delay(Temp);
                         Para();
                         for (int i = 0; i < 200; i++) Medir();
                         Serial1.print(dir);Serial1.print(" ");
                         Serial1.println(Medir());
                    }
                    Para();
                    delay(500);
          }
  }
  
  
  
 else if(dir == '-')
  {
         if(AnguloD >= 90)
          {
                   AnguloObjetivo = AnguloD - 90; 
                   Serial1.print("Angulo: "); Serial1.println(dir); Serial1.print(AnguloD); Serial1.print("  Angulo final: "); Serial1.print("-"); Serial1.println(AnguloObjetivo);
                   delay(500);             
                   Direita('F');
                   delay(1900);
                   Para();
                   delay(200);
                   for (int i = 0; i < 200; i++) Medir();
          

                    while (Medir() > AnguloObjetivo && dir != '+')
                   {
                         if(Medir() - AnguloObjetivo > 15 ) Temp = 300;
                         else Temp = 100;
                         delay(100);
                         Direita('F');
                         delay(Temp);
                         Para();
                         for (int i = 0; i < 200; i++) Medir();
                         Serial1.print(dir);Serial1.print(" ");
                         Serial1.println(Medir());                  
                   }
          }
          
          else if(AnguloD < 90)
           {
                   AnguloObjetivo = AnguloD + 90;
                   AnguloObjetivo = AnguloObjetivo - 180;
                    Serial1.print("Angulo: "); Serial1.println(dir); Serial1.print(AnguloD); Serial1.print("  Angulo final: "); Serial1.print("+"); Serial1.println(AnguloObjetivo);
                    Direita('F');
                   delay(1900);
                   Para();
                   delay(200);
                   for (int i = 0; i < 200; i++) Medir();
                   
                    while (dir != '+' )
                    {
                          if(AnguloObjetivo > 15 ) Temp = 300;
                          else if( Medir() > 15)Temp = 300;
                          else Temp = 100;
                          delay(10);
                          Direita('F');
                          delay(Temp);
                          Para();
                          for (int i = 0; i < 200; i++) Medir();
                          Serial1.print(dir);Serial1.print(" ");
                          Serial1.println(Medir());  
                    }
              
                    Direita('F');
                    delay(200);
                    Para();
                  
                   while (Medir() < AnguloObjetivo )
                    {
                         if(AnguloObjetivo - Medir() > 15 ) Temp = 300;
                         else Temp = 100;
                         delay(100);
                         Direita('F');
                         delay(Temp);
                         Para();
                         for (int i = 0; i < 200; i++) Medir();
                         Serial1.print(dir);Serial1.print(" ");
                         Serial1.println(Medir());
                    }
                    Para();
                    delay(500);
          }
  }

  analogWrite(En1, 210);//Direito
  analogWrite(En2, 250);//Esquerdo
}

void Virar_E()
{
    for (int i = 0; i < 200; i++) Medir();
  
  long AnguloD =  Medir();
  long AnguloObjetivo;
  int Temp;
  
   analogWrite(En1, 90);//Direito
   analogWrite(En2, 190);//Esquerdo
  if(dir == '+')
  {
          if(AnguloD >= 90)
          {
                   AnguloObjetivo = AnguloD - 90; 
                   Serial1.print("Angulo: "); Serial1.println(dir); Serial1.print(AnguloD); Serial1.print("  Angulo final: "); Serial1.print("+"); Serial1.println(AnguloObjetivo);
                   delay(500);             
                   Esquerda('F');
                   delay(1900);
                   Para();
                   delay(200);
                   for (int i = 0; i < 200; i++) Medir();
                 
                   while (Medir() > AnguloObjetivo && dir != '-')
                   {
                         if(Medir() - AnguloObjetivo > 15 ) Temp = 300;
                         else Temp = 100;
                         delay(100);
                         Esquerda('F');
                         delay(Temp);
                         Para();
                         for (int i = 0; i < 200; i++) Medir();
                         Serial1.print(dir);Serial1.print(" ");
                         Serial1.println(Medir());                  
                   }
                   Serial1.println("a");
           }
           else if(AnguloD < 90)
           {
                   AnguloObjetivo = 90 - AnguloD ;
                  // AnguloObjetivo = 180 - AnguloObjetivo;
                   Serial1.print("Angulo: "); Serial1.println(dir); Serial1.print(AnguloD); Serial1.print("  Angulo final: "); Serial1.print("-"); Serial1.println(AnguloObjetivo);
                   Esquerda('F');
                   delay(1900);
                   Para();
                   delay(200);
                   for (int i = 0; i < 200; i++) Medir();
                    while (dir != '-' )
                    {
                          if(AnguloObjetivo > 15 ) Temp = 300;
                          else if( Medir() > 15)Temp = 300;
                          else Temp = 100;
                          delay(10);
                          Esquerda('F');
                          delay(Temp);
                          Para();
                          for (int i = 0; i < 200; i++) Medir();
                          Serial1.print(dir);Serial1.print(" ");
                          Serial1.println(Medir());  
                    }
              
                    Esquerda('F');
                    delay(200);
                    Para();
                  
                   while (Medir() < AnguloObjetivo )
                    {
                         if(AnguloObjetivo - Medir() > 15 ) Temp = 300;
                         else Temp = 100;
                         delay(100);
                         Esquerda('F');
                         delay(Temp);
                         Para();
                         for (int i = 0; i < 200; i++) Medir();
                         Serial1.print(dir);Serial1.print(" ");
                         Serial1.println(Medir());
                    }
                    Para();
                    delay(500);
          }
  }
  
  
  
 else if(dir == '-')
  {
         if(AnguloD <= 90)
          {
                   AnguloObjetivo =   90 + AnguloD; 
                   Serial1.print("Angulo: "); Serial1.println(dir); Serial1.print(AnguloD); Serial1.print("  Angulo final: "); Serial1.print("-"); Serial1.println(AnguloObjetivo);
                   delay(500);             
                   Esquerda('F');
                   delay(1900);
                   Para();
                   delay(200);
                   for (int i = 0; i < 200; i++) Medir();
          

                    while (Medir() < AnguloObjetivo && dir != '+')
                   {
                         if(AnguloObjetivo - Medir() > 15 )  Temp = 300;
                         else Temp = 100; 
                         delay(100);
                         Esquerda('F');
                         delay(Temp);
                         Para();
                         for (int i = 0; i < 200; i++) Medir();
                         Serial1.print(dir);Serial1.print(" ");
                         Serial1.println(Medir());                  
                   }
          }
          
          else if(AnguloD > 90)
           {
                   AnguloObjetivo = AnguloD - 90;
                   AnguloObjetivo = 180 - AnguloObjetivo ;
                   Serial1.print("Angulo: "); Serial1.println(dir); Serial1.print(AnguloD); Serial1.print("  Angulo final: "); Serial1.print("+"); Serial1.println(AnguloObjetivo);
                   Esquerda('F');
                   delay(1900);
                   Para();
                   delay(200);
                   for (int i = 0; i < 200; i++) Medir();
                    while (dir != '+' )
                    {
                          if(180 - AnguloObjetivo > 15 ) Temp = 300;
                          else if(180 - Medir() > 15)Temp = 300;
                          else Temp = 100;
                          delay(10);
                          Esquerda('F');
                          delay(Temp);
                          Para();
                          for (int i = 0; i < 200; i++) Medir();
                          Serial1.print(dir);Serial1.print(" ");
                          Serial1.println(Medir());  
                    }
              
                    Esquerda('F');
                    delay(200);
                    Para();
                  
                   while (Medir() > AnguloObjetivo )
                    {
                         if(Medir() - AnguloObjetivo > 15 ) Temp = 300;
                         else Temp = 100;
                         delay(100);
                         Esquerda('F');
                         delay(Temp);
                         Para();
                         for (int i = 0; i < 200; i++) Medir();
                         Serial1.print(dir);Serial1.print(" ");
                         Serial1.println(Medir());
                    }
                    Para();
                    delay(500);
          }
  }

  analogWrite(En1, 210);//Direito
  analogWrite(En2, 250);//Esquerdo
}
