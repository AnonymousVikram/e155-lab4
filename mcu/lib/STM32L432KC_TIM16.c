#include "STM32L432KC_TIM16.h"
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"

void initTIM16() {

  // For clock:
  // Enable APB2ENR
  // Set the AHB Prescaler to 0
  // Set the APB2 Prescaler to 0

  // Enable TIM16
  RCC->AHB2ENR |= (1 << 0);
  RCC->APB2ENR |= (1 << 17);

  // Set the AHB Prescaler to 0
  RCC->CFGR &= ~(0b1111 << 4);

  // Set the APB2 Prescaler to 0
  RCC->CFGR &= ~(0b111 << 13);

  // At this point, the clock is running at 4 MHz

  /*
  For TIM16:
  1. Set the counter enable bit in the TIMx_CR1 register
  2. Set the auto-reload preload enable bit in the TIMx_CR1 register
  3. Set the update generation bit in the TIMx_EGR register
  4. Set the capture/compare mode bits in the TIMx_CCMRx register
  5. Set the output enable bit in the TIMx_CCER register
  6. Set the output polarity bit in the TIMx_CCER register
  7. Set the compare value in the TIMx_CCRx register
  8. Set the auto-reload value in the TIMx_ARR register
  9. Set the prescaler value in the TIMx_PSC register
  */

  // Set the auto-reload preload enable bit in the TIMx_CR1 register
  TIM16->CR1 |= (1 << 7);

  // Set the output enable bit in the TIMx_CCER register
  TIM16->CCER |= 1;

  // Set the output polarity bit in the TIMx_CCER register
  TIM16->CCER &= ~(1 << 1);

  // Set the compare value in the TIMx_CCRx register
  TIM16->CCR1 = 0;

  // Set the auto-reload value in the TIMx_ARR register
  TIM16->ARR = 1000;

  // Set the prescaler value in the TIMx_PSC register
  TIM16->PSC = 19;

  // Set the PWM mode 1 in the TIMx_CCMRx register
  TIM16->CCMR1 &= ~(0b111 << 4);
  TIM16->CCMR1 |= (0b110 << 4);

  // Set the ccmr1 cc1 as output
  TIM16->CCMR1 &= ~(0b11 << 0);
  TIM16->CCMR1 |= (0b00 << 0);

  // set the output compare 1 preload enable bit
  TIM16->CCMR1 |= (1 << 3);

  // Set the update generation bit in the TIMx_EGR register
  TIM16->EGR |= 1;

  TIM16->BDTR |= (1 << 15);
  // Set the counter enable bit in the TIMx_CR1 register
  TIM16->CR1 |= 1;

  // Set the Alternative function to AF14 for PA6
  GPIOA->MODER &= ~(0b11 << 12);
  GPIOA->MODER |= (0b10 << 12);
  GPIOA->AFRL &= ~(0b1111 << 24);
  GPIOA->AFRL |= (0b1110 << 24);
};

void setPWM(uint16_t dutyCycle, uint16_t frequency) {
  TIM16->ARR = 4000000 / frequency;
  TIM16->CCR1 = 4000000 / frequency * dutyCycle / 100;
  TIM16->EGR |= 1; // Update generation
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