int Paso [ 8 ][ 4 ] =
   {  {1, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 1},
      {1, 0, 0, 1}
   };
//MOTOR 1
#define IN1  12
#define IN2  11
#define IN3  10
#define IN4  9
//MOTOR 2
#define IN21  22
#define IN22  24
#define IN23  26
#define IN24  28
//MOTROR 3 
#define IN31  34
#define IN32  36
#define IN33  38
#define IN34  40
// botones 
int bot=3; //giro horario subida
int bot1=6;  //anti horario bajada
int bota=4;  //ajuste 
int botb=7;  // visualizacion
//VALORES BOT
int val;
int val1;
int val_a; //para ajuste
int val_b; //para visualizacion
//VALORES MOTOR
int Steps = 0; //POSICIONAMIENTO 
int Step = 0; //POSICIONAMIENTO atras
int steps_left=64; //numero de pasos para dar una vuelta arriba
int steps_lefta=64; //numero de pasos para dar una vuelta hacia abajo
//JOSTICK 
int jx=A1;
int jy=A2;
//VALORES JOSSTICK
int valx;
int valy;
//Fin de carrera  // se debe combrobar el funcionamiento de estps ìnes dasignados
int fin1=46;
int fin2=48;
int fin3=50;
//Valores de fin fn de carrera
int val_f1;
int val_f2;
int val_f3;
// limite de carrera superior e inferior
int valorsuperior=128; 
int valorinferior=-128; 
//Estableimiento de contadores para determinar la posicion
int cont; // realiza la cuenta en el eje Z, es decir todos lo motores funcionan a la par.
int dic1;
int dic2;
int dic3;
int dic4;
// Cordenadas
float x;
float y;
// calculos en micras
float d1;
float d2;
float d3;
float d4;
float mic=11.72; //micras por paso 
//Cuenta de posicionamentos de cada motor
int con1;
int con2;
int con3;
// inicialiazacion de Pantalla de LCD
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,16,2);
String frase1; // texto que muestra en la patalla
String frase2;
String frase3; // texto que muestra en la patalla
String frase4="micras";
//VALORES para el autoajuste, se crea estados independientres para cada motor
//MOTOR 1
int estado;
int e_bajada =1;
int e_subida =2;
int e_parada =0;
int valor_ajuste=valorinferior;
//MOTOR 2
int estado2;
int e_bajada2 =1;
int e_subida2 =2; 
int e_parada2 =0;
int valor_ajuste2=valorinferior;
//MOTOR 3
int estado3;
int e_bajada3 =1;
int e_subida3 =2;
int e_parada3 =0;
int valor_ajuste3=valorinferior;
//estado.
int ajustado1=0;
int ajustado2=0;
int ajustado3=0;
//maquina de estados salidas
int sal1;
int sal2;
int sal3;
//para maquina de estado del jostick
int valxa;
int valya;
int jos_quieto;
//funcion para estado de pantalla
int contp;

void setup() {
  
     Serial.begin(9600);
     pinMode(IN1, OUTPUT);  //MOTOR 1
     pinMode(IN2, OUTPUT);
     pinMode(IN3, OUTPUT);
     pinMode(IN4, OUTPUT);
     pinMode(IN21, OUTPUT);  //MOTOR 2
     pinMode(IN22, OUTPUT);
     pinMode(IN23, OUTPUT);
     pinMode(IN24, OUTPUT);
     pinMode(IN31, OUTPUT);  //MOTOR 3
     pinMode(IN32, OUTPUT);
     pinMode(IN33, OUTPUT);
     pinMode(IN34, OUTPUT);          
     pinMode(bot, INPUT);    //BOTONES
     pinMode(bot1, INPUT);
     pinMode(x, INPUT);      //JOSTICK 
     pinMode(y, INPUT);
     lcd.init();   //inicializamos la pamntalla 
     lcd.backlight(); // brillo para que se vea
     ajuste();
}

void loop() {
  lectura();
//subida de todos los elementos`por botones
    if (val==1 && val1==0) {
        con1++;
        con2++;
        con3++; 
        sal1=1;
        sal2=1;
        sal3=1;
      while(steps_left>0)
        { 
        lmotor1();
        lmotor2();
        lmotor3();
        paso();
        }
        contador();  //introducir el contador dentro o fuera es indeiferente cuenta bien
        frase1="Movimiento eje Z";
        frase2=cont*mic;
        frase3="";
      steps_left = 64;
      }
   if (val==0 && val1==1) {
        con1--;
        con2--;
        con3--;
        sal1=0;
        sal2=0;
        sal3=0;  
            while(steps_lefta>0)
        { 
        lmotor1a();
        lmotor2a();
        lmotor3a();
        paso();
        }
        contador(); //`
        frase1="Movimiento eje Z";
        frase2=cont*mic;
        frase3="";
      steps_lefta = 64;
      }
//segun para posicionamiento del jostick
if ( valx==0 && 340<=valy<=360) {  //APUNTA ARRIBA 12 011
        con1++;
        con2--;
        con3--;
        sal1=1;
        sal2=0;
        sal3=0; 
     while(steps_left>0){     //motor  baja 
        lmotor1() ;
        lmotor2a();
        lmotor3a() ;
        paso();
        }
      dic1=dic1+1; //Realiza la ceunta y la muesttra en pantalla 
       frase1="Plano Z: Direc: ";
       frase2=d1;
       frase3=" 1";
      steps_left = 64;
}
if  ( valx==0 && valy==0) { //13,5    //001
        con1++;
        con2++;
        con3--; 
        sal1=1;
        sal2=1;
        sal3=0; 
     while(steps_left>0){     //motor  baja 
        lmotor1() ;
        lmotor2();
        lmotor3a() ;
        paso();
        }
      dic2=dic2+1;
       frase1="Plano Z: Direc: ";
       frase2=d2;
         frase3=" 2";
      steps_left = 64;
}
if  ( 340<=valx<=360 && valy==0) { //15  X01
        con2++;
        con3--;
        sal1=1;
        sal2=1;
        sal3=0; 
      while(steps_left>0){     //motor  baja 
        lmotor2();
        lmotor3a() ;
        paso();
        }
      dic3=dic3+1;
       frase1="Plano Z: Direc: ";
       frase2=d3;
       frase3=" 3";
      steps_left = 64;
}
if  ( valx>=650 && valy==0) { //16.5  //101
        con1--;
        con2++;
        con3--;
        sal1=0;
        sal2=1;
        sal3=0;      
     while(steps_left>0){     //motor  baja 
        lmotor1a() ;
        lmotor2();
        lmotor3a() ;
        paso();
        }
      dic4=dic4+1;
       frase1="Plano Z: Direc: ";
       frase2=d4;
       frase3=" 4";
      steps_left = 64;;
}
if  ( valx>=650 && 340<=valy<=360) { //18  100
        con1--;
        con2++;
        con3++; 
        sal1=0;
        sal2=1;
        sal3=1;    
      while(steps_left>0){     //motor  baja 
        lmotor1a() ;
        lmotor2();
        lmotor3() ;
        paso();
        }
       frase1="Plano Z: Direc: ";
       frase2=d1;
       dic1=dic1-1;
       frase3=" 5";
      steps_left = 64;     
}
if ( valx>=670 && valy>=670) { //19.5  110
        con1--;
        con2--;
        con3++;
        sal1=0;
        sal2=0;
        sal3=1;
     while(steps_left>0){     //motor  baja 
        lmotor1a() ;
        lmotor2a();
        lmotor3() ;
        paso();
        }
       frase1="Plano Z: Direc: ";
       frase2=d2;
       frase3=" 6";
      steps_left = 64;
}
if  (340<=valx<=360 && valy>=663 ) { //21  X10
        con2--;
        con3++;
        sal1=1;
        sal2=0;
        sal3=1;
     while(steps_left>0){     //motor  baja 
        lmotor2a();
        lmotor3() ;
        paso();
        }
      dic3=dic3-1;
       frase1="Plano Z: Direc: ";
       frase2=d3;
       frase3=" 7";       
      steps_left = 64; 
}
if  ( valx==0 && valy>=650) { //22,5  010
        con1++;
        con2--;
        con3++; 
        sal1=1;
        sal2=0;
        sal3=1; 
     while(steps_left>0){     //motor  baja 
        lmotor1() ;
        lmotor2a();
        lmotor3() ;
        paso();
        }
      dic4=dic4-1;
       frase1="Plano Z: Direc: ";
       frase2=d4;
       frase3=" 8";
      steps_left = 64;
}
if (val_a==1) {
    ajuste();
}
if (val_b==1){
  frase1=" POSICIONAMINETO";
  frase2="_________________";
  frase3="";
  frase4="";
  pantalla();
  delay(500);
  contp=1;
  while (contp==1) {
  frase1="Posicion eje Z";
  frase2=cont*mic;
  frase3="";
  frase4="micras";
  pantalla2();
  lectura();
  if (val_b==1){
    contp=2;
  }
  else {
    contp=1;
  }
  }
  frase1="MOVIMIENTO PLANO Z";
  frase2="VALORES EN MICRAS";
  pantalla2();
  delay(1000);
  while (contp==2) {  
  frase1="Cord X:";
  frase2="Cord Y:";
  frase3=x;
  frase4=y;
  pantalla2();
  //delay(500);
  lectura();
    if (val==1){
    contp=0;
  }
  else {
    contp=2;
  }
  }
  contp=0;
  
}
else  //motores apagado 
{
 motor1() ;
 motor2();
 motor3();
 Steps=0;  
 } 
 pantalla();
 jost(); //actualizo el valor del jsotick
 Serial.println(jos_quieto);
}


//FUNCIONES ESTRUCTURALES
//FUNCIONAMIENTO DE LOS MOTORES
   void motor1()            //Avanza un paso
   {      
      digitalWrite( IN1, Paso[Steps][ 0] );
      digitalWrite( IN2, Paso[Steps][ 1] );
      digitalWrite( IN3, Paso[Steps][ 2] );
      digitalWrite( IN4, Paso[Steps][ 3] );
   }
   void motor2()            //Avanza un paso
   {  digitalWrite( IN21, Paso[Steps][ 0] );
      digitalWrite( IN22, Paso[Steps][ 1] );
      digitalWrite( IN23, Paso[Steps][ 2] );
      digitalWrite( IN24, Paso[Steps][ 3] );
   }
      void motor3()            //Avanza un paso
   {  digitalWrite( IN31, Paso[Steps][ 0] );
      digitalWrite( IN32, Paso[Steps][ 1] );
      digitalWrite( IN33, Paso[Steps][ 2] );
      digitalWrite( IN34, Paso[Steps][ 3] );
   }
   void motor1a()            //retrocede un paso
   {  digitalWrite( IN1, Paso[Step][ 0] );
      digitalWrite( IN2, Paso[Step][ 1] );
      digitalWrite( IN3, Paso[Step][ 2] );
      digitalWrite( IN4, Paso[Step][ 3] );
   }
   void motor2a()            //Avanza un paso
   {  digitalWrite( IN21, Paso[Step][ 0] );
      digitalWrite( IN22, Paso[Step][ 1] );
      digitalWrite( IN23, Paso[Step][ 2] );
      digitalWrite( IN24, Paso[Step][ 3] );
   }
      void motor3a()            //Avanza un paso
   {  digitalWrite( IN31, Paso[Step][ 0] );
      digitalWrite( IN32, Paso[Step][ 1] );
      digitalWrite( IN33, Paso[Step][ 2] );
      digitalWrite( IN34, Paso[Step][ 3] );
   }
  //Funcion que genera el recorrido de la matriz
   void paso()            //Avanza un paso
   {    Steps++; 
        Step--;   
        Steps = ( Steps + 8 ) % 8 ;
        Step = ( Step + 8 ) % 8 ;
        steps_left-- ;  // Un paso menos sin eso el moviemientos es clave
        steps_lefta-- ;  // Un paso menos sin eso el moviemientos es clave
        delay (1) ;
   }
//Motores apagados
   void motor1off()            //apagado
   {      
      digitalWrite( IN1, 0 );
      digitalWrite( IN2, 0 );
      digitalWrite( IN3, 0 );
      digitalWrite( IN4, 0 );
   }
   void motor2off()          
   {      
      digitalWrite( IN21, 0 );
      digitalWrite( IN22, 0 );
      digitalWrite( IN23, 0 );
      digitalWrite( IN24, 0 );
   }
   void motor3off()          
   {      
      digitalWrite( IN31, 0 );
      digitalWrite( IN32, 0 );
      digitalWrite( IN33, 0 );
      digitalWrite( IN34, 0 );
   }

//Funcion de control limites superior y inferior de pasos
   void lmotor1() {           
     if (con1==valorsuperior ) {
       mensaje();  
   }
    else {             
        motor1();
   }
   }
   void lmotor2() {           
     if (con2==valorsuperior) {
       mensaje();  
   }
    else {             
        motor2();
   } 
   }
      void lmotor3()    {        
     if (con3==valorsuperior) {
       mensaje();  
   }
    else {             
        motor3();
   } 
   }
   void lmotor1a()            
   { 
    if (con1==valorsuperior ) {
       mensaje();  
   }
    else {             
        motor1a();
   }
   }
   void lmotor2a()            
   {  
      if (con2==valorsuperior) {
       mensaje();  
   }
    else {             
        motor2a();
   } 
   }
      void lmotor3a()            
   {
    if (con3==valorsuperior) {
       mensaje();  
   }
    else {           
        motor3a();
   } 
   }
  void  retroceso() {
   //Para que pueda salir del bucle genero posiblidad de movimiento y retroceder en el movimiento
  if (con1==valorsuperior) {
     con1=valorsuperior-1;
  }
  else if (con1==valorinferior) {
     con1=valorinferior+1;
  }
    if (con2==valorsuperior) {
     con2=valorsuperior-1;
  }
  else if (con2==valorinferior) {
     con2=valorinferior+1;
  }
    if (con3==valorsuperior) {
     con3=valorsuperior-1;
  }
  else if (con3==valorinferior) {
     con3=valorinferior+1;
}
  }
//Funciones para la pantalla LCD
//Mensjae de contabilizacion de posicion
void pantalla(){
  calculo();
  lcd.display(); 
  delay(200); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(frase1); 
  lcd.setCursor (0,1);  // ESTA MANERA SE PUEDE CONSEGUIR OCUPAR TODOS LOS ELEMENTOS DE LA PANTALLA
  lcd.print(frase2);
  lcd.setCursor (14,0);
  lcd.print(frase3);
  lcd.setCursor (10,1);
  lcd.print(frase4);
}
// mensaje ajsute 
void pantalla1(){
  frase3="         ";
  frase4="         ";
  lcd.display(); 
  delay(200);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(frase1); 
  lcd.setCursor (0,1);
  lcd.print(frase2);
}
void pantalla2(){
  calculo();
  lcd.display(); 
  delay(200); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(frase1); 
  lcd.setCursor (0,1);  // ESTA MANERA SE PUEDE CONSEGUIR OCUPAR TODOS LOS ELEMENTOS DE LA PANTALLA
  lcd.print(frase2);
  lcd.setCursor (10,0);
  lcd.print(frase3);
  lcd.setCursor (10,1);
  lcd.print(frase4);
}
// Funcion mensaje limite de paso 
void mensaje(){
  frase3="";
  frase4="";
  lcd.display(); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("A alcanzado el"); 
  lcd.setCursor (0,1);
  lcd.print("maximo, invierta");
  delay(1000);
  lcd.display();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("el movimiento o"); 
  lcd.setCursor (0,1);
  lcd.print("pulse btn ajuste");
  delay(1000);
  retroceso();
}
//fUNCION DE AJUSTE
void ajuste() {
ajustado1=0; //se debe poner en cero para mantener el bucle sino no entra despues de un accionamineto  
frase1="AJUSTANDO MOTOR1";
frase2="PROGRESO:  30%";
pantalla1();
  while (ajustado1==0){
    delay(20);
    val_f1=digitalRead(fin1);
    if ((val_f1==1 || estado==e_subida) && valor_ajuste!=0 ){  //por cada motor su propia funcion 
      estado=e_subida; 
      valor_ajuste++;
          while(steps_left>0)
              { 
              motor1();
              paso();
              }
              delay(10);
            steps_left = 64;
    }
    if (valor_ajuste==0) {
      estado=e_parada;
      ajustado1=1;
      valor_ajuste=valorinferior;
    }
    if((val_f1==0 && valor_ajuste!=0) && estado!=e_subida) {
       estado=e_bajada;
            while(steps_lefta>0)
              { 
              motor1a();
              paso();
              } 
              delay(10);
            steps_lefta = 64;
    }
} 
motor1off(); //apago el motor1
frase1="AJUSTANDO MOTOR2";
frase2="PROGRESO:  60%  ";
pantalla1();
ajustado2=0;
    while (ajustado2==0){
      delay(20);
  val_f2=digitalRead(fin2);
//val_f3=digitalRead(fin3);
    if ((val_f2==1 || estado2==e_subida2) && valor_ajuste2!=0 ){  //por cada motor su propia funcion 
      estado2=e_subida2; 
      valor_ajuste2++;
          while(steps_left>0)
              { 
              motor2();
              paso();
              }
             delay(10);
            steps_left = 64;
    }
    if (valor_ajuste2==0) {
      estado2=e_parada2;
      ajustado2=1;
      valor_ajuste2=valorinferior;
    }
    if((val_f2==0 && valor_ajuste2!=0) && estado2!=e_subida2) {
       estado2=e_bajada2;
            while(steps_lefta>0)
              { 
              motor2a();
              paso();
              }
             delay(10);
            steps_lefta = 64;
    }
}
motor2off();// apago motor 2
frase1="AJUSTANDO MOTOR3";
frase2="PROGRESO:  70%  ";
pantalla1();
ajustado3=0;
    while (ajustado3==0){
      delay(20);
    val_f3=digitalRead(fin3);
    if ((val_f3==1 || estado3==e_subida3) && valor_ajuste3!=0 ){  //por cada motor su propia funcion 
      estado3=e_subida3; 
      valor_ajuste3++;
          while(steps_left>0)
              { 
              motor3();
              paso();
              }
               delay(10);
            steps_left = 64;
    }
    if (valor_ajuste3==0) {
      estado3=e_parada3;
      ajustado3=1;
      valor_ajuste3=valorinferior;
    }
    if((val_f3==0 && valor_ajuste3!=0) && estado3!=e_subida2) {
       estado3=e_bajada3;
            while(steps_lefta>0)
              { 
              motor3a();
              paso();
              }
               delay(10);
            steps_lefta = 64;
    }
}
motor3off(); //apago los motores
frase1="-- AJUSTADO --";
frase2="PROGRESO: 100% ";
pantalla1();
//estado_espera();
//Actualizacion de valores en posicion incial a 0
cont=0;
dic1=0;
dic2=0;
dic3=0;
dic4=0;
con1=0;
con2=0;
con3=0;
 }
//Funcion de cuenta en eje Z
//Contadores
void contador(){ // cuenta en el eje Z
  if (steps_left==0){
    cont=cont+1;
  }
  else if (steps_lefta==0){
    cont=cont-1;
  }
  else  {
  cont=cont;  
  }
}
// calculo de posicion

void calculo() {
  x=((dic2*0.866) + dic3 + (dic4*0.866))*mic;
  y=((dic2*0.5) + dic1 - (dic4*0.5))*mic; 
  d1=y;
  d2=y/0.5;
  d3=x;
  d4=x/0.866;
}
void estado_espera()
{
  while(val==0 && val1==0 && jos_quieto==1)
  {
    lectura();
    frase1="SISTEMA AJUSTADO";
    frase2="INICIE MOVIMIENTO";
    pantalla1();
    delay(100);
    lcd.noDisplay(); 
}
}
void lectura(){
    val=digitalRead(bot);
    val1=digitalRead(bot1);
    valx = analogRead(jx);               //es necesaria una pequeña pausa entre lecturas analógicas
    valy = analogRead(jy);
    val_a=digitalRead(bota);
    val_b=digitalRead(botb);  
    
}
//Esta fucnion es para saber si muevo el jostick
void jost(){
  lectura(); //leo los valores 
  if (valx==valxa && valy==valya){
    jos_quieto=1;
  }
  else {
    jos_quieto=0;
  }
  valxa=valx;
  valya=valy;
}
