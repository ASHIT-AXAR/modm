// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2011, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
// ----------------------------------------------------------------------------

#ifndef XPCC_STM32F2__GPIO_HPP
#define XPCC_STM32F2__GPIO_HPP

#include <xpcc/architecture/driver/gpio.hpp>
#include "../device.h"

/* 
 * GPIO Ports
 * ==========
 * 
 * Each port bit of the General Purpose IO (GPIO) Ports, can be
 * individually configured by software in several modes:
 * - Input floating
 * - Input (with pull-up or pull-down)
 * - Analog
 * - Output open-drain (with pull-up or pull-down)
 * - Output push-pull (with pull-up or pull-down)
 * - Alternate function push-pull (with pull-up or pull-down)
 * - Alternate function open-drain (with pull-up or pull-down)
 * 
 * GPIOx_MODER (32-bit)
 *   00: Input
 *   01: General purpose output mode
 *   10: Alternate function mode
 *   11: Analog mode
 * GPIOx_OTYPER (16-bit)
 *   0: Output push-pull
 *   1: Output open-drain
 * GPIOx_OSPEEDR (32-bit)
 *   00: 2 MHz
 *   01: 25 MHz
 *   10: 50 MHz
 *   11: 100 MHz
 * GPIOx_PUPDR (32-bit)
 *   00: No pull-up, pull-down
 *   01: Pull-up
 *   10: Pull-down
 *   11: Reserved
 * 
 * GPIOx_IDR = input state (read-only) (16-bit)
 * GPIOx_ODR = output state (16-bit)
 * 
 * GPIOx_BSRR = set and reset register (32-bit)
 * - BSRR(i) sets
 * - BSRR(i+16) resets
 */

namespace xpcc
{
	namespace stm32
	{
		/**
		 * \ingroup	stm32f2
		 */
		enum PullType
		{
			FLOATING = 0x0,
			PULLUP = 0x1,
			PULLDOWN = 0x2,
		};
		
		/**
		 * \ingroup	stm32f2
		 */
		enum OutputType
		{
			PUSH_PULL = 0x0,
			OPEN_DRAIN = 0x1,
		};
		
		/**
		 * \ingroup	stm32f2
		 */
		enum OutputSpeed
		{
			SPEED_2MHZ = 0x0,
			SPEED_25MHZ = 0x1,
			SPEED_50MHZ = 0x1,
			SPEED_100MHZ = 0x3,
		};
		
		/**
		 * \ingroup	stm32f2
		 */
		// 0..7 = AFRL[31:0]
		// 8..15 = AFRH[31:0]
		enum AlternateFunction
		{
			AF_RTC_50Hz = 0x00,	///< RTC_50Hz Alternate Function mapping
			AF_MCO = 0x00,		///< MCO (MCO1 and MCO2) Alternate Function mapping
			AF_TAMPER = 0x00,	///< TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping
			AF_SWJ = 0x00,		///< SWJ (SWD and JTAG) Alternate Function mapping
			AF_TRACE = 0x00,	///< TRACE Alternate Function mapping
			
			// AF 1 selection  
			AF_TIM1 = 0x01,		///< TIM1 Alternate Function mapping
			AF_TIM2 = 0x01,		///< TIM2 Alternate Function mapping
			
			// AF 2 selection  
			AF_TIM3 = 0x02,		///< TIM3 Alternate Function mapping
			AF_TIM4 = 0x02,		///< TIM4 Alternate Function mapping
			AF_TIM5 = 0x02,		///< TIM5 Alternate Function mapping
			
			// AF 3 selection  
			AF_TIM8 = 0x03,		///< TIM8 Alternate Function mapping
			AF_TIM9 = 0x03,		///< TIM9 Alternate Function mapping
			AF_TIM10 = 0x03,	///< TIM10 Alternate Function mapping
			AF_TIM11 = 0x03,	///< TIM11 Alternate Function mapping
			
			// AF 4 selection  
			AF_I2C1 = 0x04,		///< I2C1 Alternate Function mapping
			AF_I2C2 = 0x04,		///< I2C2 Alternate Function mapping
			AF_I2C3 = 0x04,		///< I2C3 Alternate Function mapping
			
			// AF 5 selection  
			AF_SPI1 = 0x05,		///< SPI1 Alternate Function mapping
			AF_SPI2 = 0x05,		///< SPI2/I2S2 Alternate Function mapping
			
			// AF 6 selection  
			AF_SPI3 = 0x06,		///< SPI3/I2S3 Alternate Function mapping
			
			// AF 7 selection  
			AF_USART1 = 0x07,	///< USART1 Alternate Function mapping
			AF_USART2 = 0x07,	///< USART2 Alternate Function mapping
			AF_USART3 = 0x07,	///< USART3 Alternate Function mapping
			
			// AF 8 selection  
			AF_UART4 = 0x08,	///< UART4 Alternate Function mapping
			AF_UART5 = 0x08,	///< UART5 Alternate Function mapping
			AF_USART6 = 0x08,	///< USART6 Alternate Function mapping
			
			// AF 9 selection 
			AF_CAN1 = 0x09,		///< CAN1 Alternate Function mapping
			AF_CAN2 = 0x09,		///< CAN2 Alternate Function mapping
			AF_TIM12 = 0x09,	///< TIM12 Alternate Function mapping
			AF_TIM13 = 0x09,	///< TIM13 Alternate Function mapping
			AF_TIM14 = 0x09,	///< TIM14 Alternate Function mapping
			
			// AF 10 selection  
			AF_OTG_FS = 0xA,	///< OTG_FS Alternate Function mapping
			AF_OTG_HS = 0xA,	///< OTG_HS Alternate Function mapping
			
			// AF 11 selection  
			AF_ETH = 0x0B,		///< ETHERNET Alternate Function mapping
			
			// AF 12 selection  
			AF_FSMC = 0xC,		///< FSMC Alternate Function mapping
			AF_OTG_HS_FS = 0xC,	///< OTG HS configured in FS, Alternate Function mapping
			AF_SDIO = 0xC,		///< SDIO Alternate Function mapping
			
			// AF 13 selection  
			AF_DCMI = 0x0D,		///< DCMI Alternate Function mapping
			
			// AF 15 selection  
			AF_EVENTOUT = 0x0F,	///< EVENTOUT Alternate Function mapping
			
			AF_0 = 0x00,		///< System
			AF_1 = 0x01,		///< TIM1/2
			AF_2 = 0x02,		///< TIM3..5
			AF_3 = 0x03,		///< TIM8...11
			AF_4 = 0x04,		///< I2C1..3
			AF_5 = 0x05,		///< SPI1/2
			AF_6 = 0x06,		///< SPI3
			AF_7 = 0x07,		///< USART1..3
			AF_8 = 0x08,		///< USART4..6
			AF_9 = 0x09,		///< CAN1/2, TIM12..14
			AF_10 = 0x0a,		///< OTG_FS, OTG_HS
			AF_11 = 0x0b,		///< ETH
			AF_12 = 0x0c,		///< FSMC, SDIO, OTG_HS (configured as FS)
			AF_13 = 0x0d,		///< DCMI
			AF_14 = 0x0e,		///< Reserved
			AF_15 = 0x0f,		///< EVENTOUT
		};
		
		/** \internal */
		template<unsigned int P, unsigned char N, bool = (N >= 8)>
		struct AlternateMode {
			ALWAYS_INLINE static void setMode(AlternateFunction m) {
				uint32_t tmp = reinterpret_cast<GPIO_TypeDef*>(P)->AFR[1];
				tmp &= ~(0xf << ((N - 8) * 4));
				tmp |= (m << ((N - 8) * 4));
				reinterpret_cast<GPIO_TypeDef*>(P)->AFR[1] = tmp;
			}
		};
		
		/** \internal */
		template<unsigned int P, unsigned char N>
		struct AlternateMode<P, N, false> {
			ALWAYS_INLINE static void setMode(AlternateFunction m) {
				uint32_t tmp = reinterpret_cast<GPIO_TypeDef*>(P)->AFR[0];
				tmp &= ~(0xf << (N * 4));
				tmp |= m << (N * 4);
				reinterpret_cast<GPIO_TypeDef*>(P)->AFR[0] = tmp;
			}
		};
	}
}

/**
 * \ingroup	stm32
 * \brief	Create a input/output pin type
 * 
 * \hideinitializer
 */
#define	GPIO__IO(name, port, pin) \
	struct name { \
		ALWAYS_INLINE static void setOutput(bool status) { \
			set(status); \
			setOutput(); } \
		ALWAYS_INLINE static void \
		setOutput(::xpcc::stm32::OutputType out = ::xpcc::stm32::PUSH_PULL, \
				::xpcc::stm32::OutputSpeed speed = ::xpcc::stm32::SPEED_50MHZ, \
				::xpcc::stm32::PullType pull = ::xpcc::stm32::FLOATING) { \
			GPIO ## port->MODER = (GPIO ## port->MODER & ~(0x3 << (pin * 2))) | (0x1 << (pin * 2)); \
			GPIO ## port->OTYPER = (GPIO ## port->OTYPER & ~(1 << pin)) | (out << pin); \
			GPIO ## port->OSPEEDR = (GPIO ## port->OSPEEDR & ~(0x3 << (pin * 2))) | (speed << (pin * 2)); \
			GPIO ## port->PUPDR = (GPIO ## port->PUPDR & ~(0x3 << (pin * 2))) | (pull << (pin * 2)); \
		} \
		ALWAYS_INLINE static void \
		setAlternateFunction( \
				::xpcc::stm32::AlternateFunction alt, \
				::xpcc::stm32::OutputType out, \
				::xpcc::stm32::OutputSpeed speed = ::xpcc::stm32::SPEED_50MHZ, \
				::xpcc::stm32::PullType pull = ::xpcc::stm32::FLOATING) { \
			GPIO ## port->MODER = (GPIO ## port->MODER & ~(0x3 << (pin * 2))) | (0x2 << (pin * 2)); \
			::xpcc::stm32::AlternateMode<GPIO ## port ## _BASE, pin>::setMode(alt); \
			GPIO ## port->OTYPER = (GPIO ## port->OTYPER & ~(1 << pin)) | (out << pin); \
			GPIO ## port->OSPEEDR = (GPIO ## port->OSPEEDR & ~(0x3 << (pin * 2))) | (speed << (pin * 2)); \
			GPIO ## port->PUPDR = (GPIO ## port->PUPDR & ~(0x3 << (pin * 2))) | (pull << (pin * 2)); \
		} \
		ALWAYS_INLINE static void \
		setAlternateFunction( \
				::xpcc::stm32::AlternateFunction alt, \
				::xpcc::stm32::PullType pull) { \
			GPIO ## port->MODER = (GPIO ## port->MODER & ~(0x3 << (pin * 2))) | (0x2 << (pin * 2)); \
			::xpcc::stm32::AlternateMode<GPIO ## port ## _BASE, pin>::setMode(alt); \
			GPIO ## port->OTYPER = (GPIO ## port->OTYPER & ~(1 << pin)) | \
				(::xpcc::stm32::PUSH_PULL << pin); \
			GPIO ## port->OSPEEDR = (GPIO ## port->OSPEEDR & ~(0x3 << (pin * 2))) | \
				(::xpcc::stm32::SPEED_2MHZ << (pin * 2)); \
			GPIO ## port->PUPDR = (GPIO ## port->PUPDR & ~(0x3 << (pin * 2))) | (pull << (pin * 2)); \
		} \
		ALWAYS_INLINE static void \
		setInput(::xpcc::stm32::PullType type = ::xpcc::stm32::FLOATING) { \
			GPIO ## port->MODER &= ~(0x3 << (pin * 2)); \
			GPIO ## port->PUPDR = \
				(GPIO ## port->PUPDR & ~(0x3 << (pin * 2))) | \
				(type << (pin * 2)); \
		} \
		ALWAYS_INLINE static void \
		setAnalogInput() { \
			GPIO ## port->MODER |= 0x3 << (pin * 2); \
		} \
		ALWAYS_INLINE static void set() { GPIO ## port->BSRRL = (1 << pin); } \
		ALWAYS_INLINE static void reset() { GPIO ## port->BSRRH = (1 << pin); } \
		ALWAYS_INLINE static void toggle() { if (GPIO ## port->ODR & (1 << pin)) { reset(); } else { set(); } } \
		ALWAYS_INLINE static void set(bool status) { if (status) { set(); } else { reset(); } } \
		\
		ALWAYS_INLINE static bool read() { \
			return GPIO ## port->IDR & (1 << pin); \
		} \
	}

/**
 * \brief	Create a output pin type
 * 
 * Examples:
 * \code
 * GPIO__OUTPUT(Led, C, 12);
 * 
 * Led::setOutput();
 * Led::setOutput(xpcc::stm32::PUSH_PULL);
 * Led::setOutput(xpcc::stm32::PUSH_PULL, xpcc::stm32::SPEED_10MHZ);
 * Led::setOutput(xpcc::stm32::OPEN_DRAIN);
 * 
 * Led::setAlternateFunction(); 
 * Led::setAlternateFunction(xpcc::stm32::PUSH_PULL); 
 * Led::setAlternateFunction(xpcc::stm32::PUSH_PULL, xpcc::stm32::SPEED_50MHZ); 
 * Led::setAlternateFunction(xpcc::stm32::OPEN_DRAIN);
 * 
 * Led::set();
 * Led::reset();
 * 
 * Led::toggle();
 * \endcode
 * 
 * \hideinitializer
 * \ingroup	stm32
 */
#define	GPIO__OUTPUT(name, port, pin) \
	struct name { \
		ALWAYS_INLINE static void setOutput(bool status) { \
			set(status); \
			setOutput(); } \
		ALWAYS_INLINE static void \
		setOutput(::xpcc::stm32::OutputType out = ::xpcc::stm32::PUSH_PULL, \
				::xpcc::stm32::OutputSpeed speed = ::xpcc::stm32::SPEED_50MHZ, \
				::xpcc::stm32::PullType pull = ::xpcc::stm32::FLOATING) { \
			GPIO ## port->MODER = (GPIO ## port->MODER & ~(0x3 << (pin * 2))) | (0x1 << (pin * 2)); \
			GPIO ## port->OTYPER = (GPIO ## port->OTYPER & ~(1 << pin)) | (out << pin); \
			GPIO ## port->OSPEEDR = (GPIO ## port->OSPEEDR & ~(0x3 << (pin * 2))) | (speed << (pin * 2)); \
			GPIO ## port->PUPDR = (GPIO ## port->PUPDR & ~(0x3 << (pin * 2))) | (pull << (pin * 2)); \
		} \
		ALWAYS_INLINE static void \
		setAlternateFunction( \
				::xpcc::stm32::AlternateFunction alt, \
				::xpcc::stm32::OutputType out, \
				::xpcc::stm32::OutputSpeed speed = ::xpcc::stm32::SPEED_50MHZ, \
				::xpcc::stm32::PullType pull = ::xpcc::stm32::FLOATING) { \
			GPIO ## port->MODER = (GPIO ## port->MODER & ~(0x3 << (pin * 2))) | (0x2 << (pin * 2)); \
			::xpcc::stm32::AlternateMode<GPIO ## port ## _BASE, pin>::setMode(alt); \
			GPIO ## port->OTYPER = (GPIO ## port->OTYPER & ~(1 << pin)) | (out << pin); \
			GPIO ## port->OSPEEDR = (GPIO ## port->OSPEEDR & ~(0x3 << (pin * 2))) | (speed << (pin * 2)); \
			GPIO ## port->PUPDR = (GPIO ## port->PUPDR & ~(0x3 << (pin * 2))) | (pull << (pin * 2)); \
		} \
		ALWAYS_INLINE static void set() { GPIO ## port->BSRRL = (1 << pin); } \
		ALWAYS_INLINE static void reset() { GPIO ## port->BSRRH = (1 << pin); } \
		ALWAYS_INLINE static void toggle() { if (GPIO ## port->ODR & (1 << pin)) { reset(); } else { set(); } } \
		ALWAYS_INLINE static void set(bool status) { if (status) { set(); } else { reset(); } } \
	}

/**
 * \brief	Create a input type
 * 
 * Examples:
 * \code
 * GPIO__INPUT(Button, A, 0);
 * 
 * Button::setInput();
 * Button::setInput(xpcc::stm32::PULLUP);
 * Button::setInput(xpcc::stm32::PULLDOWN);
 * Button::setAnalogInput();
 * Button::setAlternateFunction();
 * Button::setAlternateFunction(xpcc::stm32::PULLDOWN);
 * 
 * if (Button::read()) {
 *     ...
 * }
 * \endcode
 * 
 * \hideinitializer
 * \ingroup	stm32
 */
#define GPIO__INPUT(name, port, pin) \
	struct name { \
		ALWAYS_INLINE static void \
		setInput(::xpcc::stm32::PullType type = ::xpcc::stm32::FLOATING) { \
			GPIO ## port->MODER &= ~(0x3 << (pin * 2)); \
			GPIO ## port->PUPDR = \
				(GPIO ## port->PUPDR & ~(0x3 << (pin * 2))) | \
				(type << (pin * 2)); \
		} \
		ALWAYS_INLINE static void \
		setAnalogInput() { \
			GPIO ## port->MODER |= 0x3 << (pin * 2); \
		} \
		ALWAYS_INLINE static void \
		setAlternateFunction( \
				::xpcc::stm32::AlternateFunction alt, \
				::xpcc::stm32::PullType pull = ::xpcc::stm32::FLOATING) { \
			GPIO ## port->MODER = (GPIO ## port->MODER & ~(0x3 << (pin * 2))) | (0x2 << (pin * 2)); \
			::xpcc::stm32::AlternateMode<GPIO ## port ## _BASE, pin>::setMode(alt); \
			GPIO ## port->OTYPER = (GPIO ## port->OTYPER & ~(1 << pin)) | \
				(::xpcc::stm32::PUSH_PULL << pin); \
			GPIO ## port->OSPEEDR = (GPIO ## port->OSPEEDR & ~(0x3 << (pin * 2))) | \
				(::xpcc::stm32::SPEED_2MHZ << (pin * 2)); \
			GPIO ## port->PUPDR = (GPIO ## port->PUPDR & ~(0x3 << (pin * 2))) | (pull << (pin * 2)); \
		} \
		ALWAYS_INLINE static bool read() { \
			return GPIO ## port->IDR & (1 << pin); \
		} \
	}

#endif // XPCC_STM32F2__GPIO_HPP
