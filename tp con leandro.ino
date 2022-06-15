#include "RTClib.h"
RTC_DS1307 rtc;

#define BTN_MENU 2
#define BTN_SALIR 4
#define BTN_INCREMENTAR 5
#define BTN_DECREMENTAR 3
////////////////////////////////////////////////
#define PIN_LUCES 11
#define PIN_VENTILADOR 12
#define PIN_BOMBA_AGUA 13
///////////////////////////////////////////////////
/* LED CONSTANTES*/
#define MINIMO 0
#define MAXIMO 100
int aguaMin = 23;
int aguaMax = aguaMin + 3;
int luz ;
int escVen = 3;
int tiempo = 0;
int periodo = 4000;
int ambienteMin = 24;
int ambienteMax = ambienteMin + 4;
bool actuadores = true;
int dia[10];
int mes[10];
int anio[10];
int hora[10];
int minuto[10];
int segundo[10];
string evento [10];
int luz_max = luz_min + 3;
int luz_min = 20;
int tempAmbiente ;
int tempAgua;
///////////////////////
int pulsadores[4] = {BTN_MENU, BTN_SALIR, BTN_INCREMENTAR, BTN_DECREMENTAR};
int leds[3] = {PIN_LUCES, PIN_VENTILADOR, PIN_BOMBA_AGUA};
///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
int pin_pulsadores[4] = {BTN_MENU, BTN_SALIR, BTN_INCREMENTAR, BTN_DECREMENTAR};
int btnAnterior[4] = {true, true, true, true};
//////////////////////////////////////////////////////////////
bool btnPress(int btn)
{
    bool estado_actual = digitalRead(pulsadores[btn]);
    bool estado = estado_actual != btnAnterior[btn] && estado_actual == HIGH;
    btnAnterior[btn] = estado_actual;
    return estado;
}
void logEvento(String actual,){
evenT(actual,evento);
hora(day(),dia);
hora(month(),mes);
hora(year(),anio);
hora(hour(),hora);
hora(minute(),minuto);
hora(second(),segundo);
}
void printEventos(){
  for(int i = 0; i < 10; i++){
    Serial.print(evento[i]);
    Serial.print(" ");
    Serial.print(dia[i]);
    Serial.print(" ");
    Serial.print(mes[i]);
    Serial.print(" ");
    Serial.print(anio[i]);
    Serial.print(" ");
    Serial.print(hora[i]);
    Serial.print(" ");
    Serial.print(minuto[i]);
    Serial.print(" ");
    Serial.print(segundo[i]);
    Serial.print("\n");
  }
}
void hora(int dato, int evento[]){
  for (int idx = 8;idx >= 0; idx--){
    String evento_actual = evento[idx];
    evento[idx+1] = evento_actual;
  }
  evento[0] = dato;
}
void evenT(String event, int evento){
  for (int idx = 8;idx >= 0; idx--){
    String evento_actual = evento[idx];
    evento[idx+1] = evento_actual;
  }
  evento[0] = event;
}
/////////////////////////////////////////////////////////////
enum estados  {
    HOME,
    MENU,
    LUCES,
    VENTILADOR,
    BOMBA_AGUA,
    LOG_EVENTOS,
    NULO};
int est = HOME;
int estAnterior = NULO;
///////////////////////////////////////////////
enum PULL  {
    btnMenu,
    btnSalir,
    btnIncrementar,
    btnDecrementar};
bool print = false;
////////////////////////////////////////////////////////////////
void delacracionPines()
{
    for (int fila = 0; fila < 4; fila++)
    {
        int pinPulsador = pulsadores[fila];
        pinMode(pinPulsador, INPUT);
    }
    for (int fila = 0; fila < 3; fila++)
    {
        int pinLed = leds[fila];
        pinMode(pinLed, OUTPUT);
    }
}
///////////////////////////////////////////
void setup()
{
    Serial.begin(9600);
    delacracionPines();
}
void lucesPrint(){
    if(print){
    Serial.println("ESTADO_OPCION_3-->");
          Serial.print("MAX:");
          Serial.println(luz_max);
          Serial.print("MIN:");
          Serial.println(luz_min);
          print = false;
}
}
void luces()
{   
    if (btnPress(btnMenu)) menu = LOG_EVENTOS;
    if (btnPress(btnSalir)) menu = HOME;
    if (btnPress(btnDecrementar)){
        luz_min--;
        print = true;
      }
    if (btnPress(btnIncrementar)){
        luz_min++;
        print = true;
      }
    }
void ventiladorPrint(){
    if(print){
    Serial.println("ESTADO_OPCION_1-->");
          Serial.print("MAX:");
          Serial.println(ambienteMax);
          Serial.print("MIN:");
          Serial.println(ambienteMin);
          print = false;
}
}
void ventilador()
{
    if (btnPress(btnMenu)) menu = BOMBA_AGUA;
    if (btnPress(btnSalir)) menu = HOME;
    if (btnPress(btnDecrementar)){
        print = true;
        ambienteMin--;
    }
    if (btnPress(btnIncrementar)){
        print = true;
        ambienteMin++;
    }
}
void bombaAguaPrint(){
    if(print){
    Serial.println("ESTADO_OPCION_2-->");
          Serial.print("MAX:");
          Serial.println(aguaMax);
          Serial.print("MIN:");
          Serial.println(aguaMin);
          print = false;
}
}
void bombaAgua()
{
    if (btnPress(btnMenu)) menu = LUCES;
    if (btnPress(btnSalir)) menu = HOME;
    if (btnPress(btnDecrementar)){
        print = true;
        aguaMin--;
    }
    if (btnPress(btnIncrementar)){
        print = true;
        aguaMin++;
    }
}

void limpiarPantalla()
{
    for (int index = 0; index < 10; index++)
    {
        Serial.println("");
    }
}
////////////////////////////////////
void printActuadores()
{
    // mostrar bomba de abua, ventilador, intencidad luz del 0% al 100%
}
void printMenu(){
    Serial.println("Pantalla Menu:");
    Serial.println("-->Opción 1 - ajustar temperatura ambiente");
    Serial.println("-->Opción 2 - ajustar temperatura del agua");
    Serial.println("-->Opción 3 - ajustar nivel de luz");
    Serial.println("-->Opción 4 - mostrar logs de Eventos");
}
void printSensores()
{
    // mostrar sensores, tempratura ambiente, temp agua en c, sensor luz ldr en lux
}
/////////////////////////////////////////
void home()
{
   if (btnPress(btnMenu)) menu = MENU;
    if (millis() > tiempo + periodo)
    {   tiempo = millis();
        actuadores = !actuadores;
        limpiarPantalla();
    }
    if (actuadores)
    {//aca meter millis acordate gorito
        printActuadores();
    } else { 
        printSensores();
        }
}
/////////////////////////////////////////////
void lectura (int parametro, int valorMax, int valorMin, int sistema,int accion1,int accion2)
{
    if (parametro > valorMax)digitalWrite(sistema, accion1);
    else if (tempAmbiente < valorMin)digitalWrite(sistema, accion2);
}
/////////////////////////////////////////////
void menuOp (int estado)
{
    switch (estado)
    {
    case HOME:
    { // falta crear la funcion de historial
        home();
        break;
    }
    case MENU:{
        if(print){
        limpiarPantalla();
        printMenu();
        print = false;
        }
        if (btnPress(btnMenu)) menu = VENTILADOR;
        if (btnPress(btnSalir)) menu = HOME;
    }
        break;
    
    case LUCES:
    {   if(print){
        limpiarPantalla();
        lucesPrint();
        print = false;
        }
       // logEvento("luces");
        luces();
        break;
    }
    case VENTILADOR:
    {
        if(print){
        limpiarPantalla();
        ventiladorPrint();
        print = false;
        }
       // logevento("VENTILADOR");
        ventilador();
        break;
    }
    case BOMBA_AGUA:
    {   if(print){
        limpiarPantalla();
        bombaAguaPrint();
        print = false;
        }
       // logEvento("BOMBA AGUA");
        bombaAgua();
        break;
    }
    case LOG_EVENTOS:
    {   if(print){
        printEventos();
        print = false;
        }
        printEventos();
        break;
    }
    }
    if (est != estAnterior) {
    print = true;
  }
  estAnterior = est;
    }


//////////////////////////////////////////////
void loop ()
{
lectura(luz, MAX_INTENSIDAD, MIN_INTENTSIDAD, PIN_LUCES, HIGH, LOW);
lectura(tempAmbiente, ambienteMax, ambienteMin, PIN_VENTILADOR, LOW, HIGH);
lectura(tempAgua, aguaMax, aguaMin, PIN_BOMBA_AGUA, LOW, HIGH);
menuOp(est);
}
