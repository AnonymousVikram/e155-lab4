///*********************************************************************
//*                    SEGGER Microcontroller GmbH                     *
//*                        The Embedded Experts                        *
//**********************************************************************

//-------------------------- END-OF-HEADER -----------------------------

// File    : main.c
// Purpose : Generic application start

//*/

#include "../lib/STM32L432KC_FLASH.h"
#include "../lib/STM32L432KC_RCC.h"
#include "../lib/STM32L432KC_TIM16.h"
#include "../lib/STM32L432KC_TIM67.h"

///*********************************************************************
//*
//*       main()
//*
//*  Function description
//*   Application entry point.
//*/

// const int notes[][2] = {
//     {659, 125}, {623, 125}, {659, 125},  {623, 125}, {659, 125}, {494, 125},
//     {587, 125}, {523, 125}, {440, 250},  {0, 125},   {262, 125}, {330, 125},
//     {440, 125}, {494, 250}, {0, 125},    {330, 125}, {416, 125}, {494, 125},
//     {523, 250}, {0, 125},   {330, 125},  {659, 125}, {623, 125}, {659, 125},
//     {623, 125}, {659, 125}, {494, 125},  {587, 125}, {523, 125}, {440, 250},
//     {0, 125},   {262, 125}, {330, 125},  {440, 125}, {494, 250}, {0, 125},
//     {330, 125}, {523, 125}, {494, 125},  {440, 250}, {0, 125},   {494, 125},
//     {523, 125}, {587, 125}, {659, 375},  {392, 125}, {699, 125}, {659, 125},
//     {587, 375}, {349, 125}, {659, 125},  {587, 125}, {523, 375}, {330, 125},
//     {587, 125}, {523, 125}, {494, 250},  {0, 125},   {330, 125}, {659, 125},
//     {0, 250},   {659, 125}, {1319, 125}, {0, 250},   {623, 125}, {659, 125},
//     {0, 250},   {623, 125}, {659, 125},  {623, 125}, {659, 125}, {623, 125},
//     {659, 125}, {494, 125}, {587, 125},  {523, 125}, {440, 250}, {0, 125},
//     {262, 125}, {330, 125}, {440, 125},  {494, 250}, {0, 125},   {330, 125},
//     {416, 125}, {494, 125}, {523, 250},  {0, 125},   {330, 125}, {659, 125},
//     {623, 125}, {659, 125}, {623, 125},  {659, 125}, {494, 125}, {587, 125},
//     {523, 125}, {440, 250}, {0, 125},    {262, 125}, {330, 125}, {440, 125},
//     {494, 250}, {0, 125},   {330, 125},  {523, 125}, {494, 125}, {440, 500},
//     {0, 0}};

const int notes[][2] = {
    {0, 240},   {330, 180}, {0, 60},    {330, 180}, {0, 60},    {330, 180},
    {0, 60},    {330, 180}, {0, 60},    {330, 180}, {0, 60},    {294, 180},
    {0, 60},    {330, 180}, {0, 60},    {0, 240},   {330, 180}, {0, 60},
    {330, 180}, {0, 60},    {330, 180}, {0, 60},    {330, 180}, {0, 60},
    {330, 180}, {0, 60},    {294, 180}, {0, 60},    {330, 180}, {0, 60},
    {0, 240},   {330, 180}, {0, 60},    {330, 180}, {0, 60},    {330, 180},
    {0, 60},    {330, 180}, {0, 60},    {330, 180}, {0, 60},    {294, 180},
    {0, 60},    {294, 180}, {0, 60},    {0, 240},   {294, 180}, {0, 60},
    {294, 180}, {0, 60},    {262, 180}, {0, 60},    {262, 300}, {0, 60},
    {392, 300}, {0, 60},    {330, 180}, {0, 60},

    {0, 240},   {330, 180}, {0, 60},    {330, 180}, {0, 60},    {330, 180},
    {0, 60},    {330, 180}, {0, 60},    {330, 180}, {0, 60},    {294, 180},
    {0, 60},    {330, 180}, {0, 60},    {0, 240},   {330, 180}, {0, 60},
    {330, 180}, {0, 60},    {330, 180}, {0, 60},    {330, 300}, {0, 60},
    {330, 80},  {0, 40},    {294, 180}, {0, 60},    {330, 180}, {0, 60},
    {0, 240},   {330, 180}, {0, 60},    {330, 180}, {0, 60},    {330, 180},
    {0, 60},    {330, 180}, {0, 60},    {330, 180}, {0, 60},    {294, 180},
    {0, 60},    {294, 180}, {0, 60},    {0, 240},   {294, 180}, {0, 60},
    {294, 180}, {0, 60},    {262, 180}, {0, 60},    {262, 300}, {0, 60},
    {392, 300}, {0, 60},    {330, 180}, {0, 60},

    {0, 480},   {392, 400}, {0, 80},    {392, 180}, {0, 60},    {330, 80},
    {0, 40},    {294, 180}, {0, 40},    {262, 300}, {0, 60},    {392, 400},
    {0, 80},    {392, 400}, {0, 80},    {392, 180}, {0, 60},    {330, 80},
    {0, 40},    {294, 180}, {0, 40},    {262, 300}, {0, 60},    {392, 400},
    {0, 80},    {392, 400}, {0, 80},    {392, 180}, {0, 60},    {330, 80},
    {0, 40},    {294, 180}, {0, 40},    {262, 300}, {0, 60},    {523, 200},
    {0, 40},    {523, 200}, {0, 40},    {523, 200}, {0, 40},    {523, 200},
    {0, 40},    {523, 200}, {0, 40},    {523, 200}, {0, 40},    {587, 200},
    {0, 40},    {659, 200}, {0, 40},

    {0, 480},   {523, 400}, {0, 80},    {330, 80},  {0, 40},    {392, 180},
    {0, 60},    {523, 180}, {0, 60},    {392, 300}, {0, 60},

    {0, 720},   {330, 180}, {0, 60},    {330, 80},  {0, 40},    {392, 180},
    {0, 60},    {659, 300}, {0, 60},    {523, 180}, {0, 60},

    {0, 720},   {523, 180}, {0, 60},    {659, 180}, {0, 60},    {698, 180},
    {0, 60},    {659, 180}, {0, 60},    {523, 180}, {0, 60},

    {0, 720},   {523, 180}, {0, 60},    {659, 180}, {0, 60},    {587, 180},
    {0, 60},    {587, 180}, {0, 60},    {523, 180}, {0, 60},

    {0, 480},   {523, 400}, {0, 80},    {330, 180}, {0, 60},    {392, 80},
    {0, 40},    {523, 300}, {0, 60},    {392, 180}, {0, 60},

    {0, 960},   {330, 180}, {0, 60},    {392, 180}, {0, 60},    {659, 640},
    {0, 80},    {523, 400}, {0, 80},

    {523, 180}, {0, 60},    {659, 180}, {0, 60},    {698, 180}, {0, 60},
    {659, 180}, {0, 60},    {523, 180}, {0, 60},

    {0, 720},   {523, 180}, {0, 60},    {659, 180}, {0, 60},    {587, 180},
    {0, 60},    {587, 180}, {0, 60},    {523, 180}, {0, 60}};

int main(void) {
  configureFlash();
  configureClock();
  initTIM16();
  initTIM6();
  for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); ++i) {
    if (notes[i][1] == 0)
      break;
    setPWM(80, notes[i][0]);
    waitMillis(notes[i][1]);
  }
  setPWM(0, 1);
  while (1)
    ;
}

///*************************** End of file ****************************/

/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : LED blink demo

*/

// #include <stm32l432xx.h>
// #include <stdint.h>

// int main(void) {

//// Initialization code
// RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

// GPIOB->MODER |= GPIO_MODER_MODE3_0;
// GPIOB->MODER &= ~GPIO_MODER_MODE3_1;

// while(1) {
//  for(volatile int i = 0; i < 20000; i++);
//  GPIOB->ODR ^= (1 << 3);
//  }
// }
/*************************** End of file ****************************/