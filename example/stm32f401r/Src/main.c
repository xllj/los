/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "los.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim11;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM11_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int fd, const void *buf, size_t count)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)buf, count, 0xFFFF);
  return count;
}
size_t Tick;
//重写回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    Tick++;
}
void bubbleSort(int *arr,uint32_t len) {
    int  i,j,temp ;
    for (  i = 0; i < len - 1; i++) {
        for (  j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j+1]) {        // 相邻元素两两对比
                temp = arr[j+1];        // 元素交换
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
int test[224] = {
	0x6C, 0x6F, 0x73, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0A, 0x02, 0x32, 0x38, 0x28, 0x3C, 0x55, 0x3A, 
	0x41, 0x3E, 0x21, 0x05, 0x3F, 0x20, 0x05, 0x21, 0x01, 0x08, 0x3D, 0x08, 0x00, 0x3E, 0x30, 0x08, 
	0x3D, 0x08, 0x00, 0x3E, 0x30, 0x04, 0x3F, 0x30, 0x04, 0x3D, 0x11, 0x10, 0x27, 0x3A, 0x0D, 0x08, 
	0x2D, 0x08, 0x18, 0x0F, 0x10, 0x41, 0x20, 0x01, 0x0D, 0x20, 0x18, 0x36, 0x00, 0x3F, 0x30, 0x04, 
	0x3D, 0x09, 0x01, 0x3A, 0x00, 0x08, 0x3E, 0x30, 0x04, 0x35, 0x25, 0x05, 0x00, 0x00, 0x01, 0x03, 
	0x3D, 0x08, 0x00, 0x3E, 0x20, 0x02, 0x3F, 0x20, 0x02, 0x21, 0x10, 0x3F, 0x31, 0x0B, 0x3D, 0x0A, 
	0x01, 0x3A, 0x01, 0x11, 0x3A, 0x0C, 0x08, 0x2D, 0x08, 0xAE, 0x3D, 0x08, 0x00, 0x3E, 0x20, 0x01, 
	0x3F, 0x20, 0x01, 0x21, 0x10, 0x3F, 0x31, 0x0B, 0x3D, 0x0A, 0x01, 0x3A, 0x01, 0x11, 0x3F, 0x22, 
	0x02, 0x21, 0x12, 0x3A, 0x01, 0x11, 0x3A, 0x0C, 0x08, 0x2D, 0x08, 0x7E, 0x3F, 0x30, 0x07, 0x3F, 
	0x21, 0x01, 0x21, 0x11, 0x3A, 0x00, 0x08, 0x44, 0x00, 0x21, 0x10, 0x3F, 0x31, 0x07, 0x3F, 0x22, 
	0x01, 0x21, 0x12, 0x3D, 0x0B, 0x01, 0x3A, 0x00, 0x1A, 0x3A, 0x00, 0x11, 0x44, 0x09, 0x21, 0x11, 
	0x3A, 0x0B, 0x08, 0x2D, 0x08, 0x46, 0x3F, 0x30, 0x07, 0x3F, 0x21, 0x01, 0x21, 0x11, 0x3D, 0x0A
};
unsigned char los[1175] = {
	0x6C, 0x6F, 0x73, 0x00, 0x00, 0x00, 0x00, 0x81, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEF, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x6C, 0x00, 0x00, 0x00, 0x6F, 0x00, 0x00, 0x00, 
	0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
	0x32, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 
	0x55, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 
	0x21, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
	0x05, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 
	0x3D, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 
	0x30, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x3F, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 
	0x11, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 
	0x0D, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 
	0x18, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 
	0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
	0x18, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 
	0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 
	0x3E, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 
	0x25, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
	0x3F, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 
	0x10, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 
	0x3D, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 
	0x08, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xAE, 0x00, 0x00, 0x00, 
	0x3D, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 
	0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 
	0x31, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 
	0x3F, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 
	0x12, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 
	0x3A, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 
	0x08, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 
	0x07, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x21, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x08, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 
	0x10, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 
	0x3F, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 
	0x12, 0x00, 0x00, 0x00, 0x3D, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 
	0x21, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x3A, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 
	0x08, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x46, 0x00, 0x00, 0x00, 
	0x3F, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 
	0x21, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 
	0x3D, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x04, 0x3D, 0x08, 0x00, 0x3E, 0x30, 0x04, 
	0x0F, 0xE0, 0x41, 0x20, 0x01, 0x0D, 0x20, 0x18, 0x15, 0x00, 0x05, 0x00, 0x00, 0x01, 0x0C, 0x3D, 
	0x08, 0x00, 0x3E, 0x30, 0x0C, 0x3F, 0x30, 0x0C, 0x3F, 0x31, 0x14, 0x3D, 0x0A, 0x01, 0x3A, 0x01, 
	0x11, 0x3A, 0x0C, 0x08, 0x2D, 0x08, 0xBE, 0x3D, 0x08, 0x00, 0x3E, 0x30, 0x08, 0x3F, 0x30, 0x08, 
	0x3F, 0x31, 0x14, 0x3D, 0x0A, 0x01, 0x3A, 0x01, 0x11, 0x3F, 0x32, 0x0C, 0x3A, 0x01, 0x11, 0x3A, 
	0x0C, 0x08, 0x2D, 0x08, 0x92, 0x3F, 0x30, 0x10, 0x3F, 0x31, 0x08, 0x3D, 0x0A, 0x02, 0x3A, 0x12, 
	0x11, 0x3A, 0x00, 0x08, 0x44, 0x80, 0x3F, 0x31, 0x10, 0x3F, 0x32, 0x08, 0x3D, 0x0B, 0x01, 0x3A, 
	0x00, 0x1A, 0x3D, 0x0B, 0x02, 0x3A, 0x12, 0x1A, 0x3A, 0x00, 0x11, 0x44, 0x89, 0x3A, 0x0B, 0x08, 
	0x2D, 0x08, 0x56, 0x3F, 0x30, 0x10, 0x3F, 0x31, 0x08, 0x3D, 0x0A, 0x01, 0x3A, 0x00, 0x11, 0x3D, 
	0x0A, 0x02, 0x3A, 0x12, 0x11, 0x3A, 0x00, 0x08, 0x44, 0x80, 0x3E, 0x30, 0x04, 0x3F, 0x30, 0x10, 
	0x3F, 0x31, 0x08, 0x3D, 0x0A, 0x02, 0x3A, 0x12, 0x11, 0x3A, 0x00, 0x08, 0x44, 0x80, 0x3F, 0x31, 
	0x10, 0x3F, 0x32, 0x08, 0x3D, 0x0B, 0x01, 0x3A, 0x00, 0x1A, 0x3D, 0x0B, 0x02, 0x3A, 0x12, 0x1A, 
	0x3A, 0x00, 0x11, 0x45, 0x81, 0x3F, 0x30, 0x04, 0x3F, 0x31, 0x10, 0x3F, 0x32, 0x08, 0x3D, 0x0B, 
	0x02, 0x3A, 0x12, 0x1A, 0x3A, 0x00, 0x11, 0x45, 0x81, 0x3F, 0x30, 0x08, 0x3D, 0x09, 0x01, 0x3A, 
	0x00, 0x08, 0x3E, 0x30, 0x08, 0x35, 0xAA, 0x3F, 0x30, 0x0C, 0x3D, 0x09, 0x01, 0x3A, 0x00, 0x08, 
	0x3E, 0x30, 0x0C, 0x35, 0xD0, 0x0A, 0x14
};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
size_t i,ret;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */
   HAL_TIM_Base_Start_IT(&htim11);
   //10us
   printf("los demo\r\n");
   Tick=0;
   bubbleSort(test,224);
   i=Tick;
   printf("time %d(1ms)\r\n",i);
   Tick=0;
   ret=los_app_first(los);
   i=Tick;
   printf("los time[%x] %d(1ms)\r\n",ret,i);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 83;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 999;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/