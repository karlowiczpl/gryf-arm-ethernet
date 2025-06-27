#include <stdio.h>

#include <pico/stdlib.h>

#include <FreeRTOS.h>
#include <task.h>

#include <gTcp.h>

static StaticTask_t idleTask_TCB;
static StackType_t idleTask_RAM[configMINIMAL_STACK_SIZE];

/*        Blink task memory initialise        */
#define BLINK_TASK_STACK_SIZE 256
StackType_t                   blink_RAM[BLINK_TASK_STACK_SIZE];
StaticTask_t                  blink_TCB;

/*        Ethernet task memory initialise        */
#define ETHERNET_TASK_STACK_SIZE 4096
StackType_t                   ethernet_RAM[ETHERNET_TASK_STACK_SIZE];
StaticTask_t                  ethernet_TCB;

static void blink_task(void* pvParameters)
{
  gpio_init(25);
  gpio_set_dir(25, GPIO_OUT);

  while(1)
  {
    gpio_put(25, 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
    gpio_put(25, 0);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

static void ethernet_task(void* pvParameters)
{
  setup_tcp();

  while(1)
  {
    // char* out = read_tcp();
    // if(out != NULL)       printf("%s", out);
    //
    http_server_run();
  }
}

int main()
{
  stdio_init_all();

  xTaskCreateStatic(
    blink_task,
    "BL",
    BLINK_TASK_STACK_SIZE,
    (void*) 0,
    tskIDLE_PRIORITY,
    blink_RAM,
    &blink_TCB
  );

  xTaskCreateStatic(
    ethernet_task,
    "ETH",
    ETHERNET_TASK_STACK_SIZE,
    (void*) 0,
    tskIDLE_PRIORITY,
    ethernet_RAM,
    &ethernet_TCB
  );

  vTaskStartScheduler();

  while(1);
  
  return 0;
}
