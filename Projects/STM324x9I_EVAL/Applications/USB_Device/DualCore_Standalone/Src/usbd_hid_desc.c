/**
  ******************************************************************************
  * @file    USB_Device/DualCore_Standalone/Src/usbd_hid_desc.c
  * @author  MCD Application Team
  * @brief   This file provides the USBD HID descriptors and string formating method.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------ */
#include "usbd_core.h"
#include "usbd_hid_desc.h"
#include "usbd_conf.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
#define USBD_HID_VID                      0x0483
#define USBD_HID_PID                      0x5710
#define USBD_HID_LANGID_STRING            0x409
#define USBD_HID_MANUFACTURER_STRING      "STMicroelectronics"
#define USBD_HID_PRODUCT_HS_STRING        "HID Joystick in HS Mode"
#define USBD_HID_PRODUCT_FS_STRING        "HID Joystick in FS Mode"
#define USBD_HID_CONFIGURATION_HS_STRING  "HID Config"
#define USBD_HID_INTERFACE_HS_STRING      "HID Interface"
#define USBD_HID_CONFIGURATION_FS_STRING  "HID Config"
#define USBD_HID_INTERFACE_FS_STRING      "HID Interface"

/* Private macro ------------------------------------------------------------- */
/* Private function prototypes ----------------------------------------------- */
uint8_t *USBD_HID_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t * length);
uint8_t *USBD_HID_LangIDStrDescriptor(USBD_SpeedTypeDef speed,
                                      uint16_t * length);
uint8_t *USBD_HID_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed,
                                            uint16_t * length);
uint8_t *USBD_HID_ProductStrDescriptor(USBD_SpeedTypeDef speed,
                                       uint16_t * length);
uint8_t *USBD_HID_SerialStrDescriptor(USBD_SpeedTypeDef speed,
                                      uint16_t * length);
uint8_t *USBD_HID_ConfigStrDescriptor(USBD_SpeedTypeDef speed,
                                      uint16_t * length);
uint8_t *USBD_HID_InterfaceStrDescriptor(USBD_SpeedTypeDef speed,
                                         uint16_t * length);

/* Private variables --------------------------------------------------------- */
USBD_DescriptorsTypeDef HID_Desc = {
  USBD_HID_DeviceDescriptor,
  USBD_HID_LangIDStrDescriptor,
  USBD_HID_ManufacturerStrDescriptor,
  USBD_HID_ProductStrDescriptor,
  USBD_HID_SerialStrDescriptor,
  USBD_HID_ConfigStrDescriptor,
  USBD_HID_InterfaceStrDescriptor,
};

/* USB Standard Device Descriptor */
#if defined ( __ICCARM__ )      /* !< IAR Compiler */
#pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t USBD_HID_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END = {
  0x12,                         /* bLength */
  USB_DESC_TYPE_DEVICE,         /* bDescriptorType */
  0x00,                         /* bcdUSB */
  0x02,
  0x00,                         /* bDeviceClass */
  0x00,                         /* bDeviceSubClass */
  0x00,                         /* bDeviceProtocol */
  USB_MAX_EP0_SIZE,             /* bMaxPacketSize */
  LOBYTE(USBD_HID_VID),         /* idVendor */
  HIBYTE(USBD_HID_VID),         /* idVendor */
  LOBYTE(USBD_HID_PID),         /* idVendor */
  HIBYTE(USBD_HID_PID),         /* idVendor */
  0x00,                         /* bcdDevice rel. 2.00 */
  0x02,
  USBD_IDX_MFC_STR,             /* Index of manufacturer string */
  USBD_IDX_PRODUCT_STR,         /* Index of product string */
  USBD_IDX_SERIAL_STR,          /* Index of serial number string */
  USBD_MAX_NUM_CONFIGURATION    /* bNumConfigurations */
};                              /* USB_DeviceDescriptor */

/* USB Standard Device Descriptor */
#if defined ( __ICCARM__ )      /* !< IAR Compiler */
#pragma data_alignment=4
#endif
__ALIGN_BEGIN uint8_t USBD_HID_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
  USB_LEN_LANGID_STR_DESC,
  USB_DESC_TYPE_STRING,
  LOBYTE(USBD_HID_LANGID_STRING),
  HIBYTE(USBD_HID_LANGID_STRING),
};

uint8_t USBD_HID_StringSerial[USB_SIZ_STRING_SERIAL] = {
  USB_SIZ_STRING_SERIAL,
  USB_DESC_TYPE_STRING,
};

#if defined ( __ICCARM__ )      /* !< IAR Compiler */
#pragma data_alignment=4
#endif

__ALIGN_BEGIN uint8_t USBD_HID_StrDesc[USBD_MAX_STR_DESC_SIZ] __ALIGN_END;
/* Private functions --------------------------------------------------------- */
static void IntToUnicode(uint32_t value, uint8_t * pbuf, uint8_t len);
static void Get_SerialNum(void);

/**
  * @brief  Returns the device descriptor. 
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_DeviceDescriptor(USBD_SpeedTypeDef speed, uint16_t * length)
{
  *length = sizeof(USBD_HID_DeviceDesc);
  return (uint8_t *) USBD_HID_DeviceDesc;
}

/**
  * @brief  Returns the LangID string descriptor.        
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_LangIDStrDescriptor(USBD_SpeedTypeDef speed,
                                      uint16_t * length)
{
  *length = sizeof(USBD_HID_LangIDDesc);
  return (uint8_t *) USBD_HID_LangIDDesc;
}

/**
  * @brief  Returns the product string descriptor. 
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_ProductStrDescriptor(USBD_SpeedTypeDef speed,
                                       uint16_t * length)
{
  if (speed == 0)
  {
    USBD_GetString((uint8_t *) USBD_HID_PRODUCT_HS_STRING, USBD_HID_StrDesc,
                   length);
  }
  else
  {
    USBD_GetString((uint8_t *) USBD_HID_PRODUCT_FS_STRING, USBD_HID_StrDesc,
                   length);
  }
  return USBD_HID_StrDesc;
}

/**
  * @brief  Returns the manufacturer string descriptor. 
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_ManufacturerStrDescriptor(USBD_SpeedTypeDef speed,
                                            uint16_t * length)
{
  USBD_GetString((uint8_t *) USBD_HID_MANUFACTURER_STRING, USBD_HID_StrDesc,
                 length);
  return USBD_HID_StrDesc;
}

/**
  * @brief  Returns the serial number string descriptor.        
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_SerialStrDescriptor(USBD_SpeedTypeDef speed,
                                      uint16_t * length)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(speed);
  
  *length = USB_SIZ_STRING_SERIAL;

  /* Update the serial number string descriptor with the data from the unique
   * ID */
  Get_SerialNum();

  return (uint8_t *) USBD_HID_StringSerial;
}

/**
  * @brief  Returns the configuration string descriptor.    
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_ConfigStrDescriptor(USBD_SpeedTypeDef speed,
                                      uint16_t * length)
{
  if (speed == USBD_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *) USBD_HID_CONFIGURATION_HS_STRING,
                   USBD_HID_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *) USBD_HID_CONFIGURATION_FS_STRING,
                   USBD_HID_StrDesc, length);
  }
  return USBD_HID_StrDesc;
}

/**
  * @brief  Returns the interface string descriptor.        
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
uint8_t *USBD_HID_InterfaceStrDescriptor(USBD_SpeedTypeDef speed,
                                         uint16_t * length)
{
  if (speed == 0)
  {
    USBD_GetString((uint8_t *) USBD_HID_INTERFACE_HS_STRING, USBD_HID_StrDesc,
                   length);
  }
  else
  {
    USBD_GetString((uint8_t *) USBD_HID_INTERFACE_FS_STRING, USBD_HID_StrDesc,
                   length);
  }
  return USBD_HID_StrDesc;
}

/**
  * @brief  Create the serial number string descriptor 
  * @param  None 
  * @retval None
  */
static void Get_SerialNum(void)
{
  uint32_t deviceserial0, deviceserial1, deviceserial2;

  deviceserial0 = *(uint32_t *) DEVICE_ID1;
  deviceserial1 = *(uint32_t *) DEVICE_ID2;
  deviceserial2 = *(uint32_t *) DEVICE_ID3;

  deviceserial0 += deviceserial2;

  if (deviceserial0 != 0)
  {
    IntToUnicode(deviceserial0, &USBD_HID_StringSerial[2], 8);
    IntToUnicode(deviceserial1, &USBD_HID_StringSerial[18], 4);
  }
}

/**
  * @brief  Convert Hex 32Bits value into char 
  * @param  value: value to convert
  * @param  pbuf: pointer to the buffer 
  * @param  len: buffer length
  * @retval None
  */
static void IntToUnicode(uint32_t value, uint8_t * pbuf, uint8_t len)
{
  uint8_t idx = 0;

  for (idx = 0; idx < len; idx++)
  {
    if (((value >> 28)) < 0xA)
    {
      pbuf[2 * idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2 * idx] = (value >> 28) + 'A' - 10;
    }

    value = value << 4;

    pbuf[2 * idx + 1] = 0;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
