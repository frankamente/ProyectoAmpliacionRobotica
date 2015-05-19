void mover_adelante()
{
  //Preparamos la salida para que el motor gire hacia delante
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
}

void mover_atras()
{
  //Preparamos la salida para que el motor gire hacia detras
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);  
}
void parar(double correr)
{correr=0;
  pa_alante=0;
  pa_atras=0;
  Serial.println("PARAR");
  /*if(estado==1&&distI==vueltasqueremosI&&distD==vueltasqueremosD){
    estado=2;
  }*/
    
  //PARADA
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);  
  analogWrite(ENB,correr);
  analogWrite(ENA,correr);
}

void adelante(double correrI,double correrD)
{pa_alante=1;
pa_atras=0;
Serial.println("DELANTE");
  mover_adelante();
  velocidad(correrD,correrI);
}

void atras(double correrI,double correrD)
{
  pa_alante=0;
  pa_atras=1;
  Serial.println("ATRAS");
  mover_atras();  
  velocidad(correrD,correrI);
}

void girar_izquierda()
{
  //Preparamos la salida para que el motor gire hacia delante
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
}

void girar_derecha()
{
  //Preparamos la salida para que el motor gire hacia detras
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW); 
}

void velocidad(int velD,int velI)
{
  analogWrite(ENB,velD);
  analogWrite(ENA,velI);
}


void leer_sensores()
{
   // lee y muestra valor de ultrasonidos
    //Serial.println("Sensores entra");
    unsigned int uS1 = sonar1.ping(); // Send ping, get ping time in microseconds (uS).
    //Serial.print("Ping1: ");
    if(uS1 / US_ROUNDTRIP_CM==0)
    {
      dis1=200;
    }
    else
    {
      dis1=uS1 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis1); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
    
    unsigned int uS2 = sonar2.ping(); // Send ping, get ping time in microseconds (uS).
   // Serial.print("Ping2: ");
    if(uS2 / US_ROUNDTRIP_CM==0)
    {
      dis2=200;
    }
    else
    {
      dis2=uS2 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis2); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
  
    unsigned int uS3 = sonar3.ping(); // Send ping, get ping time in microseconds (uS).
    //Serial.print("Ping3: ");
    if(uS3 / US_ROUNDTRIP_CM==0)
    {
      dis3=200;
    }
    else
    {
      dis3=uS3 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis3); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
    
    unsigned int uS4 = sonar4.ping(); // Send ping, get ping time in microseconds (uS).
    //Serial.print("Ping4: ");
    if(uS4 / US_ROUNDTRIP_CM==0)
    {
      dis4=200;
    }
    else
    {
      dis4=uS4 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis4); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
    
    unsigned int uS5 = sonar5.ping(); // Send ping, get ping time in microseconds (uS).
    //Serial.print("Ping5: ");
    if(uS5 / US_ROUNDTRIP_CM==0)
    {
      dis5=200;
    }
    else
    {
      dis5=uS5 / US_ROUNDTRIP_CM;
    }
    //Serial.print(dis5); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println("cm");
    
    if(dis1<10 || dis2<20 || dis3<20 || dis4<20 || dis5<10 )
    {
      colision=1;
    }
    else
    {
      colision=0;
    }
    //Serial.print("colision "); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    //Serial.println(colision);
}


void  inter0 ()   {  // Se ejecuta cuando se detecta un cambio de estado del Pin 2
  int EncoderI;
  EncoderI=digitalRead(OUT1); 
  if(pa_alante==1 && pa_atras==0){
    distI++;}
  else if (pa_alante==0 && pa_atras==1){
    distI--;}
  etat2 =! etat2;  // Cambia el estado. De HIGH a LOW y de LOW a HIGH
  

}


void  inter1 ()   {  // Se ejecuta cuando se detecta un cambio de estado del Pin 3
  
 int EncoderD;
  EncoderD=digitalRead(OUT2);
  if(pa_alante==1 && pa_atras==0){
    distD++;}
  else if (pa_alante==0 && pa_atras==1){
    distD--;}
    
  etat3 =! etat3;  // Cambia el estado. De HIGH a LOW y de LOW a HIGH
  
  
}
void control(int vueltasqueremosI, int vueltasqueremosD)
{
  double Kp=7995500;
  double Td=0.2;
  dif_tiempo=tiempo-tiempo_a;
  /* CALCULOS PARA IZQUERDA*/
  errorposicionI=vueltasqueremosI-distI;
  errorvelocidadI=errorposicionI/dif_tiempo;
  intI =int(Kp*(errorposicionI+ Td*errorvelocidadI));
  Serial.print("Intensidad Izquierda: ");
  Serial.println(intI);
  /* CALCULOS PARA DERECHA*/
  errorposicionD=vueltasqueremosD-distD;
  errorvelocidadD=errorposicionD/dif_tiempo;
  intD =int(Kp*(errorposicionD+ Td*errorvelocidadD));
  Serial.print("Intensidad Derecha: ");
  Serial.println(intD);
  if (intI>30&&intD>30){
    adelante(intI,intD);
    Serial.print("PRIMERO ");
  }
  else if(intI<-15&&intD<-15)
  {Serial.print("SEGUNDO ");
    atras(-intI,-intD);
  }
  else if(intI>30&&intD<30&&intD>-15)
  {adelante(intI,0);
  Serial.print("TERCERO ");
  }
  else if(intI<30&&intI>-15&&intD<-15)
  {atras(0,-intD);
  Serial.print("CUARTO ");
  }
  else if(intI<-15&&intD<30&&intD>-15)
  {atras(-intI,0);
  Serial.print("QUINTO ");
  }
  else if(intI<30&&intI>-15&&intD>30)
  {atras(0,-intD);
  Serial.print("SEXTO ");
  }
  else if(intI>30&&intD<-15)
  { atras(0,-intD);
  delay(50);
    adelante(intI,0);
    delay(50);
    
    
    Serial.print("SEPTIMO ");
  }
  else if(intI<-15&&intD>30)
  {
    atras(-intI,0);
    delay(50);
  adelante(0,intD);
  delay(50);
  Serial.print("OCTAVO ");
  }
  
  else if(intI>-15&&intI<30&&intD>-15&&intD<30)
  {
    parar(0);
    Serial.print("NOVENO ");
  }
  
  delay(10);
  tiempo_a=tiempo; 
}
