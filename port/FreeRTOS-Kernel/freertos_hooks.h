#ifndef FREERTOS_HOOKS_H
#define FREERTOS_HOOKS_H

void vApplicationIdleHook(void);
void vApplicationMallocFailedHook(void);
void vApplicationStackOverflowHook(TaskHandle_t task, char* taskName);
void vApplicationGetIdleTaskMemory(StaticTask_t**, StackType_t**, uint32_t*);
void vApplicationGetTimerTaskMemory(StaticTask_t**, StackType_t**, uint32_t*);
void vApplicationGetPassiveIdleTaskMemory(StaticTask_t**, StackType_t**, uint32_t*, BaseType_t);

#endif
