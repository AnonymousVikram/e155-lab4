#ifndef STM32L4_TIM67_H
#define STM32L4_TIM67_H

#include <stdint.h>

#define __IO volatile

#define TIM1_BASE (0x40012C00UL)
#define TIM2_BASE (0x40000000UL)
#define TIM6_BASE (0x40001000UL)
#define TIM7_BASE (0x40001400UL)
#define TIM15_BASE (0x40014000UL)
#define TIM16_BASE (0x40014400UL)

typedef struct {
  __IO uint32_t CR1;  // 0x00
  __IO uint32_t CR2;  // 0x04
  uint32_t RES1;      // 0x08
  __IO uint32_t DIER; // 0x0C
  __IO uint32_t SR;   // 0x10
  __IO uint32_t EGR;  // 0x14
  uint32_t RES2;      // 0x18
  uint32_t RES3;      // 0x1C
  uint32_t RES4;      // 0x20
  __IO uint32_t CNT;  // 0x24
  __IO uint32_t PSC;  // 0x28
  __IO uint32_t ARR;  // 0x2C
} TIM6_t;             // VALID FOR TIM67

#define TIM6 ((TIM6_t *)TIM6_BASE)

void initTIM6();

void waitMillis(uint16_t millis);

#endif