#include <FreeRTOS.h>
#include <task.h>

void vApplicationIdleHook(void) {
}

void vApplicationMallocFailedHook(void) {
}

void vApplicationStackOverflowHook(TaskHandle_t task, char* taskName) {
}

void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer,
                                   StackType_t** ppxIdleTaskStackBuffer,
                                   uint32_t* pulIdleTaskStackSize) {
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t** ppxTimerTaskTCBBuffer,
                                    StackType_t** ppxTimerTaskStackBuffer,
                                    uint32_t* pulTimerTaskStackSize) {
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

void vApplicationGetPassiveIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer,
                                          StackType_t** ppxIdleTaskStackBuffer,
                                          uint32_t* pulIdleTaskStackSize,
                                          BaseType_t xSize) {
    static StaticTask_t xPassiveIdleTaskTCB;
    static StackType_t uxPassiveIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    (void)xSize;

    *ppxIdleTaskTCBBuffer = &xPassiveIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxPassiveIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
