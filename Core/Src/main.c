/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sign.h"
/** ################################## tlf ################################## */
#ifdef TLF
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <limits.h>
#include <stdint.h>
#include "vlist.h"
#include "vutils.h"
#include "logme.h"
#include "DHT.h"
#define PORT_TYPE GPIO_TypeDef*
#define PINS_INVALID_PORT NULL
#define PIN_TYPE uint16_t
#define PINS_INVALID_PIN UINT16_MAX
#include "pins.h"
#include "LCD1602.h"
#include "keypad.h"
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#include "keypad.h"
#include "pins.h"
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#include "LCD1602.h"
#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/** ################################## tlf ################################## */
#ifdef TLF
typedef enum GPIO_OutputLevel{
    GPIO_OutputLevel_LOW = GPIO_PIN_RESET,
    GPIO_OutputLevel_HIGH = GPIO_PIN_SET,
    GPIO_OutputLevel_NOT_OUTPUT
} GPIO_OutputLevel;
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#endif
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/** ################################## tlf ################################## */
#ifdef TLF
//#define LOG_USING_SERIAL_DATA
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/** ################################## tlf ################################## */
#ifdef TLF
#define WELCOME "hello, world! From THSensorSystem :)"
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#endif
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
/** ################################## tlf ################################## */
#ifdef TLF
const uint16_t RS_Pin = PA2;
const uint16_t RW_Pin = PA3;
const uint16_t EN_Pin = PA4;
const uint16_t D0_Pin = PA5;
const uint16_t D1_Pin = PA6;
const uint16_t D2_Pin = PA7;
const uint16_t D3_Pin = PC4;
const uint16_t D4_Pin = PC5;
const uint16_t D5_Pin = PB0;
const uint16_t D6_Pin = PB1;
const uint16_t D7_Pin = PC2;

const uint16_t keyboard_C4_Pin__ = PD2;
const uint16_t keyboard_C3_Pin__ = PC12;
const uint16_t keyboard_C2_Pin__ = PC11;
const uint16_t keyboard_C1_Pin__ = PC10;
const uint16_t keyboard_R1_Pin__ = PC6;
const uint16_t keyboard_R2_Pin__ = PC7;
const uint16_t keyboard_R3_Pin__ = PC8;
const uint16_t keyboard_R4_Pin__ = PC9;
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
int WorC = 0;             //0 means work,1 cry
int deverse = 1;			//deverce lcd
#endif
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */
/** ################################## tlf ################################## */
#ifdef TLF
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#endif
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/** ################################## tlf ################################## */
#ifdef TLF
void logme_vprintf(const char* restrict format, va_list vlist){
    char buf[2048] = {0};
    vsnprintf(buf, sizeof(buf), format, vlist);
    uint32_t primask = __get_PRIMASK();
    __enable_irq();
    while (HAL_UART_Transmit(
#ifdef LOG_USING_SERIAL_DATA
            &huart1
#else
            &huart3
#endif
            , (uint8_t *)buf, strlen(buf), 0xFFFFFFFF)!=HAL_OK);
//    __set_PRIMASK(primask);
}
long long logme_get_time(){
    return HAL_GetTick();
}
int logme_prepare(){
    return 1;
}
PortType pins_get_port(DigitalPinType digitalPin){
    if (digitalPin == PINS_INVALID_DIGITAL_PIN) return PINS_INVALID_PORT;
    switch (digitalPin & 15U) {
        case 0U: return GPIOA;
        case 1U: return GPIOB;
        case 2U: return GPIOC;
        case 3U: return GPIOD;
        case 4U: return GPIOE;
        case 5U: return GPIOF;
        case 6U: return GPIOG;
        default: return PINS_INVALID_PORT;
    }
}
PinType pins_get_pin(DigitalPinType digitalPin){
    if (digitalPin == PINS_INVALID_DIGITAL_PIN) return PINS_INVALID_PIN;
    switch (digitalPin >> 4U) {
        case 0U: return GPIO_PIN_0;
        case 1U: return GPIO_PIN_1;
        case 2U: return GPIO_PIN_2;
        case 3U: return GPIO_PIN_3;
        case 4U: return GPIO_PIN_4;
        case 5U: return GPIO_PIN_5;
        case 6U: return GPIO_PIN_6;
        case 7U: return GPIO_PIN_7;
        case 8U: return GPIO_PIN_8;
        case 9U: return GPIO_PIN_9;
        case 10U: return GPIO_PIN_10;
        case 11U: return GPIO_PIN_11;
        case 12U: return GPIO_PIN_12;
        case 13U: return GPIO_PIN_13;
        case 14U: return GPIO_PIN_14;
        case 15U: return GPIO_PIN_15;
        default: return PINS_INVALID_PIN;
    }
}
DigitalPinType pins_get_digital_pin(PortType port, PinType pin){
    DigitalPinType res = 0;
    switch (pin) {
        case GPIO_PIN_0: res += 0U<<4U; break;
        case GPIO_PIN_1: res += 1U<<4U; break;
        case GPIO_PIN_2: res += 2U<<4U; break;
        case GPIO_PIN_3: res += 3U<<4U; break;
        case GPIO_PIN_4: res += 4U<<4U; break;
        case GPIO_PIN_5: res += 5U<<4U; break;
        case GPIO_PIN_6: res += 6U<<4U; break;
        case GPIO_PIN_7: res += 7U<<4U; break;
        case GPIO_PIN_8: res += 8U<<4U; break;
        case GPIO_PIN_9: res += 9U<<4U; break;
        case GPIO_PIN_10: res += 10U<<4U; break;
        case GPIO_PIN_11: res += 11U<<4U; break;
        case GPIO_PIN_12: res += 12U<<4U; break;
        case GPIO_PIN_13: res += 13U<<4U; break;
        case GPIO_PIN_14: res += 14U<<4U; break;
        case GPIO_PIN_15: res += 15U<<4U; break;
        default: return PINS_INVALID_DIGITAL_PIN;
    }
    if (port == GPIOA){
        res += 0U;
    } else if (port == GPIOB){
        res += 1U;
    } else if (port == GPIOC){
        res += 2U;
    } else if (port == GPIOD){
        res += 3U;
    } else if (port == GPIOE){
        res += 4U;
    } else if (port == GPIOF){
        res += 5U;
    } else if (port == GPIOG){
        res += 6U;
    } else{
        return PINS_INVALID_DIGITAL_PIN;
    }
    return res;
}
void GPIO_Configure(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_OutputLevel output_level, uint32_t GPIO_Mode, uint32_t GPIO_Pull, uint32_t GPIO_Speed)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    switch (GPIO_Pin) {
        case GPIO_PIN_0:
        case GPIO_PIN_1:
        case GPIO_PIN_2:
        case GPIO_PIN_3:
        case GPIO_PIN_4:
        case GPIO_PIN_5:
        case GPIO_PIN_6:
        case GPIO_PIN_7:
        case GPIO_PIN_8:
        case GPIO_PIN_9:
        case GPIO_PIN_10:
        case GPIO_PIN_11:
        case GPIO_PIN_12:
        case GPIO_PIN_13:
        case GPIO_PIN_14:
        case GPIO_PIN_15:
            break;
        default:
            return;
    }

    /* GPIO Ports Clock Enable */
    if (GPIOx == GPIOA){
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (GPIOx == GPIOB){
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (GPIOx == GPIOC){
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if (GPIOx == GPIOD){
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if (GPIOx == GPIOE){
        __HAL_RCC_GPIOE_CLK_ENABLE();
    } else if (GPIOx == GPIOF){
        __HAL_RCC_GPIOF_CLK_ENABLE();
    } else if (GPIOx == GPIOG){
        __HAL_RCC_GPIOG_CLK_ENABLE();
    } else{
        return;
    }

    switch (output_level) {
        case GPIO_OutputLevel_LOW:
            HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
            break;
        case GPIO_OutputLevel_HIGH:
            HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
            break;
        default:
            break;
    }

    /* Configure GPIO pin */
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_Mode;
    GPIO_InitStruct.Pull = GPIO_Pull;
    /* For most families there are dedicated registers so it is
     * not so important, register can be set at any time.But for
     * families like F1, speed only applies to output. */
    if (GPIO_Mode == GPIO_MODE_OUTPUT_PP || GPIO_Mode == GPIO_MODE_OUTPUT_OD) {
        GPIO_InitStruct.Speed = GPIO_Speed;
    }
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void DHT_pinMode_in(uint16_t pin, DHT_PIN_MODE mode, int default_output_low){
    switch (mode) {
        case DHT_PIN_MODE_INPUT:
            GPIO_Configure(pins_get_port(pin), pins_get_pin(pin), GPIO_OutputLevel_NOT_OUTPUT, GPIO_MODE_INPUT, GPIO_NOPULL,
#ifdef GPIO_SPEED_VERY_HIGH
                    GPIO_SPEED_VERY_HIGH
#else
                           GPIO_SPEED_HIGH
#endif
            );
            break;
        case DHT_PIN_MODE_INPUT_PULLUP:
            GPIO_Configure(pins_get_port(pin), pins_get_pin(pin), GPIO_OutputLevel_NOT_OUTPUT, GPIO_MODE_INPUT, GPIO_PULLUP,
#ifdef GPIO_SPEED_VERY_HIGH
                    GPIO_SPEED_VERY_HIGH
#else
                           GPIO_SPEED_HIGH
#endif
            );
            break;
        case DHT_PIN_MODE_OUTPUT:
            GPIO_Configure(pins_get_port(pin), pins_get_pin(pin), default_output_low ? GPIO_OutputLevel_LOW : GPIO_OutputLevel_HIGH, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,
#ifdef GPIO_SPEED_VERY_HIGH
                    GPIO_SPEED_VERY_HIGH
#else
                           GPIO_SPEED_HIGH
#endif
            );
            break;
        default:
            break;
    }
}
void DHT_pinMode_Output_Low(uint16_t pin, DHT_PIN_MODE mode){
    DHT_pinMode_in(pin, mode, 1);
}
void DHT_pinMode_Output_High(uint16_t pin, DHT_PIN_MODE mode){
    DHT_pinMode_in(pin, mode, 0);
}
void DHT_pinMode(uint16_t pin, DHT_PIN_MODE mode){
    DHT_pinMode_Output_Low(pin, mode);
}
void DHT_delay(unsigned long ms){
    while (ms > 0UL) {
        uint32_t temp_ms = ms > UINT32_MAX ? UINT32_MAX : ms;
        HAL_Delay(temp_ms);
        ms -= temp_ms;
    }
}
uint32_t getUs(void) {
    uint32_t usTicks = HAL_RCC_GetSysClockFreq() / (uint32_t)1000000;
    register uint32_t ms, cycle_cnt;
    do {
        ms = HAL_GetTick();
        cycle_cnt = SysTick->VAL;
    } while (ms != HAL_GetTick());
    return (ms * (uint32_t)1000) + (usTicks * (uint32_t)1000 - cycle_cnt) / usTicks;
}
void delayUs(uint32_t us) {
    uint32_t start = getUs();
    while (getUs() - start < us);
}
void delayUs_tim(uint16_t us){
    HAL_TIM_Base_Start(&htim2);
    __HAL_TIM_SetCounter(&htim2, us);
    while(__HAL_TIM_GetCounter(&htim2)>1);
    HAL_TIM_Base_Stop(&htim2);
}
void delayUs_tim_long_long(unsigned long long us){
    while (us > 0ULL){
        uint16_t temp_us = us > UINT16_MAX ? UINT16_MAX : us;
        delayUs_tim(temp_us);
        us -= temp_us;
    }
}
void DHT_delayMicroseconds(unsigned long us) {
    delayUs_tim_long_long(us);
}
void DHT_digitalWrite(uint16_t pin, DHT_PIN_VALUE value){
    switch (value) {
        case DHT_PIN_VALUE_LOW:
            HAL_GPIO_WritePin(pins_get_port(pin), pins_get_pin(pin), GPIO_PIN_RESET);
            break;
        case DHT_PIN_VALUE_HIGH:
            HAL_GPIO_WritePin(pins_get_port(pin), pins_get_pin(pin), GPIO_PIN_SET);
            break;
        default:
            break;
    }
}
DHT_PIN_VALUE DHT_digitalRead(uint16_t pin){
    switch (HAL_GPIO_ReadPin(pins_get_port(pin), pins_get_pin(pin))) {
        default:
        case GPIO_PIN_RESET:
            return DHT_PIN_VALUE_LOW;
        case GPIO_PIN_SET:
            return DHT_PIN_VALUE_HIGH;
    }
}
long long DHT_microsecondsToClockCycles(long long us){
    return ( (us) * ((long long)SystemCoreClock / 1000000LL) );
}
void DHT_disable_interrupt(){
    __disable_irq();
}
void DHT_enable_interrupt(){
    __enable_irq();
}
void printTHtoLCD(float t, float h){
    lcd_clear();
    lcd_print(0, 0, "tem: %.2f", t);
    lcd_print(1, 0, "hum: %.0f%%", h);
}
void LCD_pinMode(uint16_t pin, LCD_PIN_MODE mode){
    switch (mode) {
        case LCD_PIN_MODE_INPUT_PULLUP:
            DHT_pinMode(pin, DHT_PIN_MODE_INPUT_PULLUP); break;
        case LCD_PIN_MODE_INPUT:
            DHT_pinMode(pin, DHT_PIN_MODE_INPUT); break;
        case LCD_PIN_MODE_OUTPUT:
            DHT_pinMode(pin, DHT_PIN_MODE_OUTPUT); break;
        default:;
    }
}
void LCD_digitalWrite(uint16_t pin, LCD_PIN_VALUE value){
    switch (value) {
        case LCD_PIN_VALUE_HIGH:
            DHT_digitalWrite(pin, DHT_PIN_VALUE_HIGH);
            break;
        case LCD_PIN_VALUE_LOW:
            DHT_digitalWrite(pin, DHT_PIN_VALUE_LOW);
            break;
        default:;
    }
}
LCD_PIN_VALUE LCD_digitalRead(uint16_t pin){
    switch (DHT_digitalRead(pin)) {
        default:
        case DHT_PIN_VALUE_HIGH:
            return LCD_PIN_VALUE_HIGH;
        case DHT_PIN_VALUE_LOW:
            return LCD_PIN_VALUE_LOW;
    }
}
void KEY_BOARD_digitalWrite(uint16_t pin, KEY_BOARD_PIN_VALUE value){
    switch (value) {
        case KEY_BOARD_PIN_VALUE_HIGH:
            DHT_digitalWrite(pin, DHT_PIN_VALUE_HIGH);
            break;
        case KEY_BOARD_PIN_VALUE_LOW:
            DHT_digitalWrite(pin, DHT_PIN_VALUE_LOW);
            break;
        default:;
    }
}
KEY_BOARD_PIN_VALUE KEY_BOARD_digitalRead(uint16_t pin){
    switch (DHT_digitalRead(pin)) {
        default:
        case DHT_PIN_VALUE_HIGH:
            return KEY_BOARD_PIN_VALUE_HIGH;
        case DHT_PIN_VALUE_LOW:
            return KEY_BOARD_PIN_VALUE_LOW;
    }
}
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
void send_voice_analog_value_to_serial_data(int is_caused_by_digital_in, unsigned int analog_v){
    unsigned char is_d = is_caused_by_digital_in?1U:0U;
    unsigned char av_high = analog_v>>8;
    unsigned char av_low = analog_v;
    HAL_UART_Transmit(&huart1, "\xF0", 1, 0xFFFFFFFF);
    HAL_UART_Transmit(&huart1, &is_d, 1, 0xFFFFFFFF);
    HAL_UART_Transmit(&huart1, &av_high, 1, 0xFFFFFFFF);
    HAL_UART_Transmit(&huart1, &av_low, 1, 0xFFFFFFFF);
}
unsigned int get_voice_av(){
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 50) == HAL_OK){
        return HAL_ADC_GetValue(&hadc1);
    }else{
        return UINT_MAX;
    }
}
void auto_send_voice_analog_value (int is_caused_by_digital_in) {
    unsigned int voice_av = get_voice_av();
    if (voice_av != UINT_MAX){
        LogMe.it("%sread voice_av = %u", is_caused_by_digital_in?"Caused by Digital input: ":"", voice_av);
        send_voice_analog_value_to_serial_data(is_caused_by_digital_in, voice_av);
    } else{
        LogMe.et("%sread voice_av Fail", is_caused_by_digital_in?"Caused by Digital input: ":"");
    }
}
/*
 * Init lcd
 * Make voice_module work
 */
void initmodule(){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    lcd_init();
    lcd_clear();
}
void stop(){
    uint16_t key = read_keypad();
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
    WorC = 0;
}
void cry(){
    lcd_clear();
    lcd_put_cur(0, 0);
    lcd_send_string(" BABY ");
    lcd_send_string("IS ");
    lcd_send_string("CRYING");
}
void work(){
    if (WorC == 0 && deverse == 1) {
        lcd_clear();
        lcd_put_cur(0, 0);
        lcd_send_string(" DEV ");
        lcd_send_string("IS ");
        lcd_send_string("WORKING");
        lcd_put_cur(1, 0);
        lcd_send_string("FROM T&J PRODUCE");
        deverse = 0;
    }
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == VOICE_Digital_in_Pin)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
        if (deverse==0) {
            cry();
            deverse=1;
            auto_send_voice_analog_value(1);
            stop();
        }
    }
}
#endif
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
/** ################################## tlf ################################## */
#ifdef TLF
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#endif
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
/** ################################## tlf ################################## */
#ifdef TLF
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#endif
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
/** ################################## tlf ################################## */
#ifdef TLF
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#endif
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
/** ################################## tlf ################################## */
#ifdef TLF
    logme_init();
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
    DHT_digitalWrite(pins_get_digital_pin(GPIOB, GPIO_PIN_9), DHT_PIN_VALUE_HIGH);
    DHT_digitalWrite(pins_get_digital_pin(GPIOA, GPIO_PIN_12), DHT_PIN_VALUE_HIGH);
    DHT_digitalWrite(pins_get_digital_pin(GPIOA, GPIO_PIN_11), DHT_PIN_VALUE_HIGH);
    DHT_digitalWrite(pins_get_digital_pin(GPIOB, GPIO_PIN_12), DHT_PIN_VALUE_LOW);
    HAL_Delay(1100); // wait for DHT to be stable
    dht_init(pins_get_digital_pin(GPIOA, GPIO_PIN_1));
    lcd_init();
    lcd_clear();
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
    initmodule();
#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
  while (1)
  {
/** ################################## tlf ################################## */
#ifdef TLF
//      vlist list = make_vlist(5);
//      char *rabbit = zero_malloc(5);
//      if (rabbit == NULL) continue;
//      LogMe.b("%s", WELCOME);
      LogMe.bt("%s", WELCOME);
      float temperature, humidity;
      int res = dht_readTemperatureAndHumidity(pins_get_digital_pin(GPIOA, GPIO_PIN_1), dht_sensor_type_DHT11, dht_temperature_scale_Celcius, &temperature, &humidity);
      if (res){
          LogMe.bt("Temperature = %f (C), Humidity = %f", temperature, humidity);
          unsigned char tem_i = temperature;
          unsigned char tem_f = ((long)(temperature*100))-(((long)temperature)*100);
          unsigned char hum = humidity;
          HAL_UART_Transmit(&huart1, "\xFF", 1, 0xFFFFFFFF);
          HAL_UART_Transmit(&huart1, &tem_i, 1, 0xFFFFFFFF);
          HAL_UART_Transmit(&huart1, &tem_f, 1, 0xFFFFFFFF);
          HAL_UART_Transmit(&huart1, &hum, 1, 0xFFFFFFFF);
          printTHtoLCD(temperature, humidity);
      } else{
          LogMe.bt("Temperature = Fail (C), Humidity = Fail");
      }
      HAL_UART_Transmit(&huart1, WELCOME"\n", strlen(WELCOME"\n"), 0xFFFFFFFF);
//      HAL_Delay(2100);
      delayUs_tim_long_long(2100000ULL);
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
    work();
    auto_send_voice_analog_value(0);
#endif
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
/** ################################## tlf ################################## */
#ifdef TLF
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#endif
  }
#pragma clang diagnostic pop
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7;
  htim2.Init.CounterMode = TIM_COUNTERMODE_DOWN;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LCD1602D7_Pin|LCD1602D3_Pin|LCD1602D4_Pin|KB_C1_Pin
                          |KB_C2_Pin|KB_C3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD1602RS_Pin|LCD1602RW_Pin|LCD1602E_Pin|LCD1602D0_Pin
                          |LCD1602D1_Pin|LCD1602D2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD1602D5_Pin|LCD1602D6_Pin|GND_Pin|VOICE___Pin
                          |VOICE_G_Pin|Debug_pin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, V_5V_Output_Pin|V_5V_OutputA12_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(KB_C4_GPIO_Port, KB_C4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DHT11_power_GPIO_Port, DHT11_power_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LCD1602D7_Pin LCD1602D3_Pin LCD1602D4_Pin KB_C1_Pin
                           KB_C2_Pin KB_C3_Pin */
  GPIO_InitStruct.Pin = LCD1602D7_Pin|LCD1602D3_Pin|LCD1602D4_Pin|KB_C1_Pin
                          |KB_C2_Pin|KB_C3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : DHT11_data_Pin */
  GPIO_InitStruct.Pin = DHT11_data_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DHT11_data_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD1602RS_Pin LCD1602RW_Pin LCD1602E_Pin LCD1602D0_Pin
                           LCD1602D1_Pin LCD1602D2_Pin V_5V_Output_Pin V_5V_OutputA12_Pin */
  GPIO_InitStruct.Pin = LCD1602RS_Pin|LCD1602RW_Pin|LCD1602E_Pin|LCD1602D0_Pin
                          |LCD1602D1_Pin|LCD1602D2_Pin|V_5V_Output_Pin|V_5V_OutputA12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD1602D5_Pin LCD1602D6_Pin GND_Pin VOICE___Pin
                           VOICE_G_Pin Debug_pin_Pin DHT11_power_Pin */
  GPIO_InitStruct.Pin = LCD1602D5_Pin|LCD1602D6_Pin|GND_Pin|VOICE___Pin
                          |VOICE_G_Pin|Debug_pin_Pin|DHT11_power_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : KB_R1_Pin KB_R2_Pin KB_R3_Pin KB_R4_Pin */
  GPIO_InitStruct.Pin = KB_R1_Pin|KB_R2_Pin|KB_R3_Pin|KB_R4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : KB_C4_Pin */
  GPIO_InitStruct.Pin = KB_C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KB_C4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : VOICE_Digital_in_Pin */
  GPIO_InitStruct.Pin = VOICE_Digital_in_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VOICE_Digital_in_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
/** ################################## tlf ################################## */
#ifdef TLF
#endif
/** ################################## wxm ################################## */
#ifdef WXM
#endif
/** ################################## ppy ################################## */
#ifdef PPY
#endif
/** ################################## sjj ################################## */
#ifdef SJJ
#endif
/** ################################## tyj ################################## */
#ifdef TYJ
#endif
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
