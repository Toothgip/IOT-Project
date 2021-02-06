#include <ChainableLED.h>
#define NUM_LEDS  1
ChainableLED leds(26, 25, NUM_LEDS);// A0


TaskHandle_t blink = NULL;
TaskHandle_t powerOn = NULL;
int STACK_SIZE = 5000;

struct taskParms {
    int r;   
    int g;
    int b;
};

struct taskParms color;
int duration = 0;
  //Rouge Fixe => En cours de démarrage 
  //Vert fixe tout est OK      
  //Blanc clignotte -> Lumiere probleme       
                  
  //Vert clignotte erreur => Erreur HTTP      
  //Bleu clignotte => Erreur humidité         
  //Rouge clignotte => Probleme de wifi       
  //Jaune clignottant => Envoi de food        
     
  
//Power on the RGB with a color
void powerOnRGB(int r,int  g,int b){
  for (byte i=0; i<NUM_LEDS; i++){
    leds.setColorRGB(i, r, g, b);
  }
}

//Task for put a fade light
void powerOnTask(void *pvParameters) {
  for( ;; ){
    powerOnRGB(color.r, color.g,color.b);    
  }
  
}

//Task for put a blink light
void blinkRGBTask(void *pvParameters) {
  for( ;; ) {
    powerOnRGB(color.r, color.g,color.b);
    delay(500);
    powerOnRGB(0, 0,0);
    delay(500);
  }
}

void stopBlinkTask(void *pvParameters) {
  delay(duration);
  blink= deleteTask(blink);
  powerOn= deleteTask(powerOn);
  color.r = 0;
  color.g = 255;
  color.b = 0;
  xTaskCreate(powerOnTask, "PowerOn", STACK_SIZE, NULL, tskIDLE_PRIORITY, &powerOn);
  vTaskDelete(NULL);
  
}

void switchTemporaryBlinkRGB(int r, int g , int b, int d) {
  color.r = r;
  color.g = g;
  color.b = b;
  
  if(!blinking) {
    blinking = true;
    powerOn= deleteTask(powerOn);
  }
  else {
    blink= deleteTask(blink);
  }
  duration = d;
  xTaskCreate(blinkRGBTask, "Temporary Blink", STACK_SIZE, NULL, tskIDLE_PRIORITY, &blink);
  xTaskCreate(stopBlinkTask, "Stop blink", STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
}


void switchOnRGB(int r,int g,int b) {

  if(blinking) {
    blink= deleteTask(blink);
    blinking = false;
  }
  else {
    powerOn= deleteTask(powerOn);
  }
  color.r = r;
  color.g = g;
  color.b = b;
  xTaskCreate(powerOnTask, "PowerOn", STACK_SIZE, NULL, tskIDLE_PRIORITY, &powerOn);
}


TaskHandle_t deleteTask(TaskHandle_t taskHandle){
  if(taskHandle != NULL){
      vTaskDelete( taskHandle );
      taskHandle = NULL;
  }
  return taskHandle;
}
