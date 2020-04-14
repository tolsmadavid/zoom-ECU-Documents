/**
  ******************************************************************************
  * @file    BSP/Src/audio_play.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the audio feature in the
  *          STM32G474E EVAL driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>

/** @addtogroup STM32G4xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/*Since SysTick is set to 1ms (unless to set it quicker) */
/* to run up to 48khz, a buffer around 1000 (or more) is requested*/
/* to run up to 96khz, a buffer around 2000 (or more) is requested*/
#define AUDIO_DEFAULT_VOLUME    60

/* Audio file size and start address are defined here since the audio file is
   stored in Flash memory as a constant table of 16-bit data */
#define AUDIO_BUFFER_SIZE             4096
#define AUDIO_FILE_SIZE               (180*1024)
#define AUDIO_START_OFFSET_ADDRESS    0            /* Offset relative to audio file header size */

/* Private typedef -----------------------------------------------------------*/
typedef enum {
  AUDIO_STATE_IDLE = 0,
  AUDIO_STATE_INIT,
  AUDIO_STATE_PLAYING,
}AUDIO_PLAYBACK_StateTypeDef;

typedef enum {
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;

typedef struct {
  uint8_t buff[AUDIO_BUFFER_SIZE];
  uint32_t fptr;
  BUFFER_StateTypeDef state;
  uint32_t AudioFileSize;
  uint32_t *SrcAddress;
}AUDIO_BufferTypeDef;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static AUDIO_BufferTypeDef  buffer_ctl;
static AUDIO_PLAYBACK_StateTypeDef  audio_state;
__IO uint32_t uwVolume = 20;
uint8_t ReadVol = 0;
__IO uint32_t uwPauseEnabledStatus = 0;
uint32_t updown = 1;

uint32_t AudioFreq[8] = {96000, 48000, 44100, 32000, 22050, 16000, 11025, 8000};

BSP_AUDIO_Init_t AudioPlayInit;
static uint32_t JoyState = JOY_NONE;
uint32_t OutputDevice = 0;

/* Private function prototypes -----------------------------------------------*/
static void Audio_SetHint(uint32_t Index);
static uint32_t GetData(void *pdata, uint32_t offset, uint8_t *pbuf, uint32_t NbrOfData);
AUDIO_ErrorTypeDef AUDIO_Start(uint32_t *psrc_address, uint32_t file_size);
AUDIO_ErrorTypeDef AUDIO_Stop(void);
static void AudioDeviceUpdate(void);
static void AudioChResUpdate(void);

/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Audio Play demo
  * @param  None
  * @retval None
  */
int32_t AudioPlay_demo (void)
{
  uint32_t *AudioFreq_ptr;
  uint32_t y_size;

  uint32_t AudioSize;

  BSP_LCD_GetYSize(0, &y_size);

  AudioFreq_ptr = &AudioFreq[0]; /*96K*/

  uint8_t FreqStr[256] = {0};
  Point Points2[] = {{100, 140}, {160, 180}, {100, 220}};

  uwPauseEnabledStatus = 1; /* 0 when audio is running, 1 when Pause is on */
  uwVolume = 40;

  Audio_SetHint(0);
  GUI_SetFont(&Font20);

  BSP_JOY_Init(JOY1, JOY_MODE_GPIO, JOY_ALL);

  AudioPlayInit.Device = AUDIO_OUT_DEVICE_HEADPHONE;
  AudioPlayInit.ChannelsNbr = 2;                      /* 16bit value offset=22 of wave file */
  AudioPlayInit.SampleRate = AUDIO_FREQUENCY_8K;      /* 32bit value offset=24 of wave file */
  AudioPlayInit.BitsPerSample = AUDIO_RESOLUTION_16B; /* 16bit value offset=34 of wave file */
  AudioPlayInit.Volume = uwVolume;

  if(BSP_AUDIO_OUT_Init(0, &AudioPlayInit) == 0)
  {
    GUI_SetBackColor(GUI_COLOR_WHITE);
    GUI_SetTextColor(GUI_COLOR_GREEN);
    GUI_DisplayStringAt(0, y_size - 95, (uint8_t *)"  AUDIO CODEC   OK  ", CENTER_MODE);
  }
  else
  {
    GUI_SetBackColor(GUI_COLOR_WHITE);
    GUI_SetTextColor(GUI_COLOR_RED);
    GUI_DisplayStringAt(0, y_size - 95, (uint8_t *)"  AUDIO CODEC  FAIL ", CENTER_MODE);
    GUI_DisplayStringAt(0, y_size - 80, (uint8_t *)" Try to reset board ", CENTER_MODE);
  }

  /*
  Start playing the file from a circular buffer, once the DMA is enabled, it is
  always in running state. Application has to fill the buffer with the audio data
  using Transfer complete and/or half transfer complete interrupts callbacks
  (BSP_AUDIO_OUT_TransferComplete_CallBack() or BSP_AUDIO_OUT_HalfTransfer_CallBack()...
  */
  AudioSize = (uint32_t )(*((uint32_t *)(AUDIO_SRC_FILE_ADDRESS+40)));

  /* check if audio is present */
  if ((uint32_t )(*((uint32_t *)(AUDIO_SRC_FILE_ADDRESS))) != 0x46464952)
  {
   GUI_SetBackColor(GUI_COLOR_WHITE);
   GUI_SetTextColor(GUI_COLOR_RED);
   GUI_DisplayStringAt(0, LINE(8), (uint8_t *)" ERROR  file not found", CENTER_MODE);
   return -1;
  }
   
  AUDIO_Start((uint32_t *)AUDIO_SRC_FILE_ADDRESS, (uint32_t)AudioSize);
  /* Display the state on the screen */
  GUI_SetBackColor(GUI_COLOR_WHITE);
  GUI_SetTextColor(GUI_COLOR_BLUE);
  GUI_DisplayStringAt(0, LINE(8), (uint8_t *)"       PLAYING...     ", CENTER_MODE);

  sprintf((char*)FreqStr, "       VOL:    %3d     ", uwVolume);
  GUI_DisplayStringAt(0,  LINE(9), (uint8_t *)FreqStr, CENTER_MODE);

  sprintf((char*)FreqStr, "      FREQ: %6d     ", *AudioFreq_ptr);
  GUI_DisplayStringAt(0, LINE(10), (uint8_t *)FreqStr, CENTER_MODE);

  GUI_SetFont(&Font16);
  GUI_DisplayStringAt(0, y_size - 40, (uint8_t *)"Hear nothing ? Have you copied the audio file with STM-LINK UTILITY ?", CENTER_MODE);

  GUI_SetFont(&Font20);

  /* Audio is playing */
  GUI_FillPolygon(Points2, 3, GUI_COLOR_WHITE);
  BSP_LCD_FillRect(0, 100, 140, 25 , 80, LCD_COLOR_RGB565_BLACK);
  BSP_LCD_FillRect(0, 140, 140, 25 , 80, LCD_COLOR_RGB565_BLACK);

  /* IMPORTANT:
  AUDIO_Process() is called by the SysTick Handler, as it should be called
  within a periodic process */

  /* Infinite loop */
  while (1)
  {
   /* IMPORTANT: AUDIO_Process() should be called within a periodic process */
    AUDIO_Process();
    AudioDeviceUpdate();

    /* Get the Joystick State */
    switch (BSP_JOY_GetState(JOY1))
    {
    case JOY_UP:
      /* Increase volume by 5% */
      if (uwVolume < 95)
        uwVolume += 5;
      else
        uwVolume = 100;
      sprintf((char*)FreqStr, "       VOL:    %3d     ", uwVolume);
      BSP_AUDIO_OUT_SetVolume(0, uwVolume);
      GUI_DisplayStringAt(0, LINE(9), (uint8_t *)FreqStr, CENTER_MODE);
      break;
    case JOY_DOWN:
      /* Decrease volume by 5% */
      if (uwVolume > 5)
        uwVolume -= 5;
      else
        uwVolume = 0;
      sprintf((char*)FreqStr, "       VOL:    %3d     ", uwVolume);
      BSP_AUDIO_OUT_SetVolume(0, uwVolume);
      GUI_DisplayStringAt(0, LINE(9), (uint8_t *)FreqStr, CENTER_MODE);
      break;
    case JOY_LEFT:
      /*Decrease Frequency */
      if (*AudioFreq_ptr != 8000)
      {
        AudioFreq_ptr++;
        sprintf((char*)FreqStr, "      FREQ: %6d     ", *AudioFreq_ptr);
        BSP_AUDIO_OUT_Pause(0);
        BSP_AUDIO_OUT_SetSampleRate(0, *AudioFreq_ptr);
        BSP_AUDIO_OUT_Resume(0);
        BSP_AUDIO_OUT_SetVolume(0, uwVolume);
      }
      GUI_DisplayStringAt(0, LINE(10), (uint8_t *)FreqStr, CENTER_MODE);
      break;
    case JOY_RIGHT:
      /* Increase Frequency */
      if (*AudioFreq_ptr != 96000)
      {
        AudioFreq_ptr--;
        sprintf((char*)FreqStr, "      FREQ: %6d     ", *AudioFreq_ptr);
        BSP_AUDIO_OUT_Pause(0);
        BSP_AUDIO_OUT_SetSampleRate(0, *AudioFreq_ptr);
        BSP_AUDIO_OUT_Resume(0);
        BSP_AUDIO_OUT_SetVolume(0, uwVolume);
      }

      GUI_DisplayStringAt(0, LINE(10), (uint8_t *)FreqStr, CENTER_MODE);
      break;
    case JOY_SEL:
      /* Set Pause / Resume */
      if (uwPauseEnabledStatus == 1)
      { /* Pause is enabled, call Resume */
        BSP_AUDIO_OUT_Resume(0);
        uwPauseEnabledStatus = 0;
        GUI_DisplayStringAt(0, LINE(8), (uint8_t *)"       PLAYING...     ", CENTER_MODE);
        GUI_FillPolygon(Points2, 3, GUI_COLOR_WHITE);
        BSP_LCD_FillRect(0, 100, 140, 25 , 80, LCD_COLOR_RGB565_BLACK);
        BSP_LCD_FillRect(0, 140, 140, 25 , 80, LCD_COLOR_RGB565_BLACK);
      }
      else
      { /* Pause the playback */
        BSP_AUDIO_OUT_Pause(0);
        uwPauseEnabledStatus = 1;
        GUI_DisplayStringAt(0, LINE(8), (uint8_t *)"       PAUSE  ...     ", CENTER_MODE);
        BSP_LCD_FillRect(0, 100, 140, 80 , 80, LCD_COLOR_RGB565_WHITE);
        GUI_FillPolygon(Points2, 3, GUI_COLOR_GREEN);
      }
      HAL_Delay(200);
      break;

    default:
      break;
    }
  }
}

int32_t AudioPlay_demo2 (void)
{
  uint32_t *AudioFreq_ptr;
  uint32_t y_size;

  BSP_LCD_GetYSize(0, &y_size);
  AudioFreq_ptr = &AudioFreq[0]; /*96K*/

  uint8_t FreqStr[256] = {0};

  uwVolume = 40;

  Audio_SetHint(1);
  GUI_SetFont(&Font20);


  BSP_JOY_Init(JOY1, JOY_MODE_GPIO, JOY_ALL);

  AudioPlayInit.Device = AUDIO_OUT_DEVICE_HEADPHONE;
  AudioPlayInit.ChannelsNbr = 2;
  AudioPlayInit.SampleRate = AUDIO_FREQUENCY_96K;
  AudioPlayInit.BitsPerSample = AUDIO_RESOLUTION_16B;
  AudioPlayInit.Volume = uwVolume;

  if(BSP_AUDIO_OUT_Init(0, &AudioPlayInit) == 0)
  {
    GUI_SetBackColor(GUI_COLOR_WHITE);
    GUI_SetTextColor(GUI_COLOR_GREEN);
    GUI_DisplayStringAt(0, y_size - 95, (uint8_t *)"  AUDIO CODEC   OK  ", CENTER_MODE);
  }
  else
  {
    GUI_SetBackColor(GUI_COLOR_WHITE);
    GUI_SetTextColor(GUI_COLOR_RED);
    GUI_DisplayStringAt(0, y_size - 95, (uint8_t *)"  AUDIO CODEC  FAIL ", CENTER_MODE);
    GUI_DisplayStringAt(0, y_size - 80, (uint8_t *)" Try to reset board ", CENTER_MODE);
  }

  /*
  Start playing the file from a circular buffer, once the DMA is enabled, it is
  always in running state. Application has to fill the buffer with the audio data
  using Transfer complete and/or half transfer complete interrupts callbacks
  (BSP_AUDIO_OUT_TransferComplete_CallBack() or BSP_AUDIO_OUT_HalfTransfer_CallBack()...
  */
  AUDIO_Start((uint32_t *)AUDIO_SRC_FILE_ADDRESS, (uint32_t)AUDIO_FILE_SIZE);

  /* Display the state on the screen */
  GUI_SetBackColor(GUI_COLOR_WHITE);
  GUI_SetTextColor(GUI_COLOR_BLUE);
  GUI_DisplayStringAt(0, LINE(8), (uint8_t *)"       PLAYING...     ", CENTER_MODE);

  sprintf((char*)FreqStr, "       VOL:    %3d     ", uwVolume);
  GUI_DisplayStringAt(0,  LINE(9), (uint8_t *)FreqStr, CENTER_MODE);

  sprintf((char*)FreqStr, "      FREQ: %6d     ", *AudioFreq_ptr);
  GUI_DisplayStringAt(0, LINE(10), (uint8_t *)FreqStr, CENTER_MODE);

  GUI_SetFont(&Font16);
  GUI_DisplayStringAt(0, y_size - 40, (uint8_t *)"Hear nothing ? Have you copied the audio file with STM-LINK UTILITY ?", CENTER_MODE);

  GUI_SetFont(&Font20);
  GUI_DisplayStringAt(0, LINE(11), (uint8_t *)"AUDIO OUT STEREO MODE   ", CENTER_MODE);
  GUI_DisplayStringAt(0, LINE(12), (uint8_t *)"AUDIO_RESOLUTION_16b   ", CENTER_MODE);

  /* IMPORTANT:
  AUDIO_Process() is called by the SysTick Handler, as it should be called
  within a periodic process */

  /* Infinite loop */
  while (1)
  {
   /* IMPORTANT: AUDIO_Process() should be called within a periodic process */
    AUDIO_Process();
    AudioChResUpdate();
  }
}

/**
  * @brief  Display Audio demo hint
  * @param  None
  * @retval None
  */
static void Audio_SetHint(uint32_t Index)
{
  uint32_t x_size, y_size;
  uint8_t texte[30];

  BSP_LCD_GetXSize(0, &x_size);
  BSP_LCD_GetYSize(0, &y_size);

  /* Clear the LCD */
  BSP_LCD_Clear(0, LCD_COLOR_RGB565_WHITE);

  /* Set Audio Demo description */
  BSP_LCD_FillRect(0, 0, 0, x_size, 120, LCD_COLOR_RGB565_BLUE);
  GUI_SetTextColor(GUI_COLOR_WHITE);
  GUI_SetBackColor(GUI_COLOR_BLUE);
  GUI_SetFont(&Font20);
  if(Index == 0)
  {
  GUI_DisplayStringAt(0, 0, (uint8_t *)"SET MUTE / SET VOLUME / SET SAMPLE RATE", CENTER_MODE);
  GUI_SetFont(&Font12);
  GUI_DisplayStringAt(0, 30, (uint8_t *)"Press User button for next menu          ", CENTER_MODE);
  GUI_DisplayStringAt(0, 45, (uint8_t *)"    ", CENTER_MODE);
  sprintf((char *)texte, "copy audio file at @ 0x%x", AUDIO_SRC_FILE_ADDRESS);
  GUI_DisplayStringAt( 30, 154, (uint8_t *)texte, LEFT_MODE);
  GUI_DisplayStringAt(0, 60, (uint8_t *)"Use touch screen +/- to change Frequency ", CENTER_MODE);
  GUI_DisplayStringAt(0, 75, (uint8_t *)"Touch upper part of the screen to Pause/Resume    ", CENTER_MODE);
  GUI_DisplayStringAt(0, 90, (uint8_t *)"Use Joy keys to set output device    ", CENTER_MODE);
  }
  else
  {
  GUI_DisplayStringAt(0, 0, (uint8_t *)"SET CHANNEL NUMBER/ SET BIT PER SAMPLE", CENTER_MODE);
  GUI_SetFont(&Font12);
  GUI_DisplayStringAt(0, 30, (uint8_t *)"Press User button for next menu          ", CENTER_MODE);
  GUI_DisplayStringAt(0, 45, (uint8_t *)"Use Joy keys UP/DOWN to set Channels Number    ", CENTER_MODE);
  GUI_DisplayStringAt(0, 60, (uint8_t *)"Use Joy keys LEFT/RIGHT to set resolution    ", CENTER_MODE);
  }

  GUI_DrawRect(10, 120, x_size - 20, y_size - 130, GUI_COLOR_RED);
  GUI_DrawRect(11, 121, x_size - 22, y_size - 132, GUI_COLOR_RED);
}


/**
  * @brief  Starts Audio streaming.
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_Start(uint32_t *psrc_address, uint32_t file_size)
{
  uint32_t bytesread;

  buffer_ctl.state = BUFFER_OFFSET_NONE;
  buffer_ctl.AudioFileSize = file_size;
  buffer_ctl.SrcAddress = psrc_address;

  /* actual wave file starts at offset=44*/
  bytesread = GetData( (void *)psrc_address,
                       0,
                       &buffer_ctl.buff[0],
                       AUDIO_BUFFER_SIZE);
  if(bytesread > 0)
  {
    BSP_AUDIO_OUT_Play(0, (uint8_t *)&buffer_ctl.buff[0], AUDIO_BUFFER_SIZE);
    audio_state = AUDIO_STATE_PLAYING;
    buffer_ctl.fptr = bytesread;
    return AUDIO_ERROR_NONE;
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Manages Audio process.
  * @param  None
  * @retval Audio error
  */
uint8_t AUDIO_Process(void)
{
  uint32_t bytesread;
  AUDIO_ErrorTypeDef error_state = AUDIO_ERROR_NONE;

  switch(audio_state)
  {
  case AUDIO_STATE_PLAYING:

    if(buffer_ctl.fptr >= buffer_ctl.AudioFileSize)
    {
      /* Play audio sample again ... */
      buffer_ctl.fptr = 0;
      error_state = AUDIO_ERROR_EOF;
    }

    /* 1st half buffer played; so fill it and continue playing from bottom*/
    if(buffer_ctl.state == BUFFER_OFFSET_HALF)
    {
      bytesread = GetData((void *)buffer_ctl.SrcAddress,
                          buffer_ctl.fptr,
                          &buffer_ctl.buff[0],
                          AUDIO_BUFFER_SIZE /2);

      if( bytesread >0)
      {
        buffer_ctl.state = BUFFER_OFFSET_NONE;
        buffer_ctl.fptr += bytesread;
      }
    }

    /* 2nd half buffer played; so fill it and continue playing from top */
    if(buffer_ctl.state == BUFFER_OFFSET_FULL)
    {
      bytesread = GetData((void *)buffer_ctl.SrcAddress,
                          buffer_ctl.fptr,
                          &buffer_ctl.buff[AUDIO_BUFFER_SIZE /2],
                          AUDIO_BUFFER_SIZE /2);
      if( bytesread > 0)
      {
        buffer_ctl.state = BUFFER_OFFSET_NONE;
        buffer_ctl.fptr += bytesread;
      }
    }
    break;

  default:
    error_state = AUDIO_ERROR_NOTREADY;
    break;
  }
  return (uint8_t) error_state;
}

/**
  * @brief  Gets Data from storage unit.
  * @param  None
  * @retval None
  */
static uint32_t GetData(void *pdata, uint32_t offset, uint8_t *pbuf, uint32_t NbrOfData)
{
  uint8_t *lptr = pdata;
  uint32_t ReadDataNbr;

  ReadDataNbr = 0;
  while(((offset + ReadDataNbr) < buffer_ctl.AudioFileSize) && (ReadDataNbr < NbrOfData))
  {
    pbuf[ReadDataNbr]= lptr [offset + ReadDataNbr];
    ReadDataNbr++;
  }
  return ReadDataNbr;
}

/*------------------------------------------------------------------------------
       Callbacks implementation:
           the callbacks API are defined __weak in the stm32769i_discovery_audio.c file
           and their implementation should be done the user code if they are needed.
           Below some examples of callback implementations.
  ----------------------------------------------------------------------------*/
/**
  * @brief  Manages the full Transfer complete event.
  * @param  Instance
  * @retval None
  */
void BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance)
{
  if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* allows AUDIO_Process() to refill 2nd part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_FULL;
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  * @param  Instance
  * @retval None
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance)
{
  if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* allows AUDIO_Process() to refill 1st part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_HALF;
  }
}

/**
  * @brief  Manages the DMA FIFO error event.
  * @param  Instance
  * @retval None
  */
void BSP_AUDIO_OUT_Error_CallBack(uint32_t Instance)
{
  /* Display message on the LCD screen */
  GUI_SetBackColor(GUI_COLOR_RED);
  GUI_DisplayStringAt(0, LINE(14), (uint8_t *)"       DMA  ERROR     ", CENTER_MODE);
  GUI_SetBackColor(GUI_COLOR_WHITE);

  /* Stop the program with an infinite loop */
  while (BSP_PB_GetState(BUTTON_USER) != RESET)
  {
    return;
  }

  /* could also generate a system reset to recover from the error */
  /* .... */
}

static void AudioChResUpdate(void)
{
  JoyState = BSP_JOY_GetState(JOY1);

  switch(JoyState)
  {
  case JOY_UP:
    BSP_AUDIO_OUT_Pause(0);
    BSP_AUDIO_OUT_SetChannelsNbr(0, 1);
    BSP_AUDIO_OUT_Resume(0);

    GUI_DisplayStringAt(0, LINE(11), (uint8_t *)"AUDIO OUT MONO MODE    ", CENTER_MODE);
    break;
  case JOY_DOWN:
    BSP_AUDIO_OUT_Pause(0);
    BSP_AUDIO_OUT_SetChannelsNbr(0, 2);
    BSP_AUDIO_OUT_Resume(0);
    GUI_DisplayStringAt(0, LINE(11), (uint8_t *)"AUDIO OUT STEREO MODE   ", CENTER_MODE);
    break;
  case JOY_LEFT:
    BSP_AUDIO_OUT_Pause(0);
    BSP_AUDIO_OUT_SetBitsPerSample(0, AUDIO_RESOLUTION_16B);
    BSP_AUDIO_OUT_Resume(0);
    GUI_DisplayStringAt(0, LINE(12), (uint8_t *)"AUDIO_RESOLUTION_16b   ", CENTER_MODE);
    break;
  case JOY_RIGHT:
    BSP_AUDIO_OUT_Pause(0);
    BSP_AUDIO_OUT_SetBitsPerSample(0, AUDIO_RESOLUTION_32B);
    BSP_AUDIO_OUT_Resume(0);
    GUI_DisplayStringAt(0, LINE(12), (uint8_t *)"AUDIO_RESOLUTION_32b   ", CENTER_MODE);
    break;
  default:
    break;
  }
}

static void AudioDeviceUpdate(void)
{
  JoyState = BSP_JOY_GetState(JOY1);

  switch(JoyState)
  {
  case JOY_UP:
    BSP_AUDIO_OUT_Pause(0);
    BSP_AUDIO_OUT_SetDevice(0, AUDIO_OUT_DEVICE_HEADPHONE);
    BSP_AUDIO_OUT_Resume(0);

    GUI_DisplayStringAt(0, LINE(11), (uint8_t *)"AUDIO_OUT_DEVICE_HEADPHONE   ", CENTER_MODE);
    break;
  case JOY_DOWN:
    BSP_AUDIO_OUT_Pause(0);
    BSP_AUDIO_OUT_SetDevice(0, AUDIO_OUT_DEVICE_HEADPHONE);
    BSP_AUDIO_OUT_Resume(0);
    GUI_DisplayStringAt(0, LINE(11), (uint8_t *)"AUDIO_OUT_DEVICE_SPEAKER   ", CENTER_MODE);
    break;
  case JOY_LEFT:
    BSP_AUDIO_OUT_Pause(0);
    BSP_AUDIO_OUT_SetDevice(0, AUDIO_OUT_DEVICE_HEADPHONE);
    BSP_AUDIO_OUT_Resume(0);
    GUI_DisplayStringAt(0, LINE(11), (uint8_t *)"AUDIO_OUT_DEVICE_SPK_HP   ", CENTER_MODE);
    break;
  case JOY_RIGHT:
    BSP_AUDIO_OUT_Pause(0);
    BSP_AUDIO_OUT_SetDevice(0, AUDIO_OUT_DEVICE_HEADPHONE);
    BSP_AUDIO_OUT_Resume(0);
    GUI_DisplayStringAt(0, LINE(11), (uint8_t *)"AUDIO_OUT_DEVICE_AUTO      ", CENTER_MODE);
    break;
  default:
    break;
  }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
