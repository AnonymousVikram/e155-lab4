#include "STM32L432KC_TIM67.h"
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"

void initTIM6() {
  // Enable the clock for the timer
  RCC->APB1ENR1 |= 1 << 4;

  // Set the APB1 Prescaler to 0
  RCC->CFGR &= ~(0b111 << 8);

  // At this point, the clock should be going into TIM6

  TIM6->PSC = 39999; // scale the clock down to 1 kHz

  TIM6->CR1 |= 1 << 7; // Auto-reload preload enable
  TIM6->CR1 |= 11 << 2;
  TIM6->EGR |= 1; // Update generation
}

void waitMillis(uint16_t millis) {
  if (millis == 0)
    return;
  TIM6->ARR &= ~(0xFFFF);
  TIM6->ARR |= millis * 2;
  TIM6->EGR |= 1;
  TIM6->CR1 |= 1; // Enable the timer
  while (!(TIM6->SR & 1))
    ;
  TIM6->SR &= 0;
}

/*
Pulse Width Modulation mode allows you to generate a signal with a frequency
determined by the value of the TIMx_ARR register and a duty cycle determined by
the value of the TIMx_CCRx register. The PWM mode can be selected independently
on each channel (one PWM per OCx output) by writing ‘110’ (PWM mode 1) or ‘111’
(PWM mode 2) in the OCxM bits in the TIMx_CCMRx register. You must enable the
corresponding preload register by setting the OCxPE bit in the TIMx_CCMRx
register, and eventually the auto-reload preload register (in upcounting or
center-aligned modes) by setting the ARPE bit in the TIMx_CR1 register. As the
preload registers are transferred to the shadow registers only when an update
event occurs, before starting the counter, you have to initialize all the
registers by setting the UG bit in the TIMx_EGR register. OCx polarity is
software programmable using the CCxP bit in the TIMx_CCER register. It can be
programmed as active high or active low. OCx output is enabled by a combination
of the CCxE, CCxNE, MOE, OSSI and OSSR bits (TIMx_CCER and TIMx_BDTR registers).
Refer to the TIMx_CCER register description for more details.
In PWM mode (1 or 2), TIMx_CNT and TIMx_CCRx are always compared to determine
whether TIMx_CCRx ≤ TIMx_CNT or TIMx_CNT ≤ TIMx_CCRx (depending on the direction
of the counter).
The TIM15/TIM16 are capable of upcounting only. Refer to Upcounting mode on page
893. In the following example, we consider PWM mode 1. The reference PWM signal
OCxREF is high as long as TIMx_CNT < TIMx_CCRx else it becomes low. If the
compare value in TIMx_CCRx is greater than the auto-reload value (in TIMx_ARR)
then OCxREF is held at ‘1’. If the compare value is 0 then OCxRef is held at
‘0’. Figure 312 shows some edgealigned PWM waveforms in an example where
TIMx_ARR=8.
*/