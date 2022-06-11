#define PIN_PULSADOR_MENU 3
#define PIN_PULSADOR_SALIR 2
#define PIN_PULSADOR_INCREMENTAR 5
#define PIN_PULSADOR_DECREMENTAR 4

#define PIN_LED_R 11
#define PIN_LED_G 10
#define PIN_LED_B 9
/* LED CONSTANTES*/
#define MAX_INTENSIDAD 255
#define MIN_INTENTSIDAD 0
#define LED_INCREMENTO_DECREMENTO 20
int pulsadores[4] = {
    {PIN_PULSADOR_MENU, PIN_PULSADOR_SALIR, PIN_PULSADOR_INCREMENTAR, PIN_PULSADOR_DECREMENTAR}};
int leds[3] = {
    {PIN_LED_R, PIN_LED_G, PIN_LED_B}};
    int periodo1 = 4000;
    int periodo2 = 8000;
enum std_menu = {
    HOME,
    LED_R,
    LED_G,
    LED_B};
int menu = HOME;
enum logs = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int index = 0;
void setup()
{
    
}



void actuadores(){
    //mostrar bomba de abua, ventilador, intencidad luz del 0% al 100%
}
void sensores(){
    //mostrar sensores, tempratura ambiente, temp agua en c, sensor luz ldr en lux 
}
void home (int periodo,int periodo_2)
{ int inActua = 0;
  int inSen = 0;
    if(millis() > inActua + periodo){
        inActua = millis();
        actuadores();
    }
    else if(millis() > inSen + periodo_2){
        inSen = millis();
        sensores();
    }

}


switch (menu)
{
case HOME:
{   logEvento("HOME");//falta crear la funcion de historial
    home(periodo1,periodo2);
    break;
}
case MENU :{
    logEvento("MENU");
    printMenu();
    break;
}
case LED_R:
{   logEvento("LED_RED");
    led_r();//mostrar lo mismo pero indicando lugar y opcion para modificar parametros
    break;
}
case LED_G:
{  logevento("LED_GREEN");
    led_g();
    break;
}
case LED_B:
{ logEvento("LED_BLUE");
    led_b();
    break;
}
case LOG_EVENTOS:{
    //MOSTRAR EVENTOS
    break;
}
}

void loop{

}
