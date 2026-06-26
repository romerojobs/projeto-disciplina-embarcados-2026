#include "TaskVitoria.h"

void TaskVitoria(void *pvParameters)
{
  int leitura;

  while(1){
    leitura = gpio_get_level(SENSOR_VITORIA_PIN);
    
    if(leitura == 0){
      gpio_set_level(LED_VITORIA_PIN,1);
    }else{
      gpio_set_level(LED_VITORIA_PIN,0);
    }
    vTaskDelay(pdMS_TO_TICKS(PERIODO_LEITURA_VITORIA));
  }
}