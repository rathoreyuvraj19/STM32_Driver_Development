# STM32F407 Bare-Metal Driver Development

[![Version](https://img.shields.io/badge/version-1.0-blue.svg)](https://github.com/yourusername/stm32f407-drivers)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-STM32F407-orange.svg)](https://www.st.com/en/microcontrollers-microprocessors/stm32f407.html)

> Bare-metal driver development for STM32F407 Discovery Board without HAL or STM32Cube libraries.

This repository contains a collection of bare-metal driver projects for the **STM32F407VG** microcontroller, written entirely from scratch using direct register manipulation. Each project demonstrates specific hardware features and peripheral configurations, building a comprehensive understanding of low-level embedded system design.

---

## Table of Contents

- [Hardware Specifications](#hardware-specifications)
- [Repository Structure](#repository-structure)
- [Development Approach](#development-approach)
- [Projects Overview](#projects-overview)
- [Concepts Covered](#concepts-covered)
- [Getting Started](#getting-started)
- [Building and Flashing](#building-and-flashing)
- [API Documentation](#api-documentation)
- [Upcoming Modules](#upcoming-modules)
- [Learning Resources](#learning-resources)
- [Author](#author)
- [License](#license)

---

## Hardware Specifications

### Microcontroller

- **MCU**: STM32F407VG
- **Architecture**: ARM Cortex-M4 with FPU and DSP
- **Core Clock**: Up to 168 MHz
- **Flash Memory**: 1 MB
- **SRAM**: 192 KB (112 KB + 16 KB + 64 KB CCM)
- **Board**: STM32F4 Discovery Kit

### Clock Configuration

- **External Crystal**: 16 MHz HSE
  ```
  f_HSE = 16 MHz
  f_SYSCLK = (f_HSE / M) × N / P  (PLL configuration)
  ```

### Required Tools

- STM32CubeIDE or ARM-GCC toolchain
- ST-Link debugger (integrated on-board)
- Logic analyzer (optional, for signal verification)
- Serial terminal application (for debug output)

---

## Repository Structure

```
STM32F407-Drivers/
│
├── Projects/
│   ├── 000_Hello_World/
│   │   ├── Src/
│   │   │   ├── main.c
│   │   │   ├── syscalls.c
│   │   │   └── sysmem.c
│   │   └── README.md
│   │
│   ├── 001_STM_CLOCK_ENABLE/
│   │   ├── Src/
│   │   │   ├── main.c
│   │   │   ├── syscalls.c
│   │   │   └── sysmem.c
│   │   └── README.md
│   │
│   ├── 002_User_button_interrupt/
│   │   ├── Src/
│   │   │   ├── main.c
│   │   │   ├── syscalls.c
│   │   │   └── sysmem.c
│   │   └── README.md
│   │
│   └── 003_Testing_stm32f407xx_drivers/
│       ├── Drivers/
│       │   ├── inc/
│       │   │   ├── stm32f407xx.h           # MCU register definitions
│       │   │   └── stm32f407xx_gpio.h      # GPIO driver API
│       │   └── src/
│       │       └── stm32f407xx_gpio.c      # GPIO driver implementation
│       ├── Src/
│       │   ├── main.c
│       │   ├── syscalls.c
│       │   └── sysmem.c
│       └── README.md
│
├── Resources/                              # Datasheets and schematics
├── Docs/                                   # Doxygen-generated documentation
│   └── refman.pdf                          # Reference manual
└── README.md
```

---

## Development Approach

### Bare-Metal Philosophy

All drivers are implemented **bare-metal**, meaning:

**What We Use:**

- Direct access to peripheral registers via memory-mapped addresses
  ```c
  Register_Address = Base_Address + Offset
  ```
- Manual RCC clock gating and control
- Direct GPIO register configuration
- Custom interrupt vector handling
- NVIC priority configuration

**What We Don't Use:**

- HAL (Hardware Abstraction Layer)
- LL (Low-Level) drivers
- StdPeriph libraries
- Any ST-provided middleware or abstraction

### Implementation Details

**Memory-Mapped I/O:**

```c
#define PERIPHERAL_BASEADDR    0x40000000UL
#define AHB1_PERIPHERAL_BASE   (PERIPHERAL_BASEADDR + 0x00020000UL)
#define GPIOD_BASEADDR         (AHB1_PERIPHERAL_BASE + 0x0C00UL)
```

**Register Access:**

```c
typedef struct {
    volatile uint32_t MODER;      // Mode register
    volatile uint32_t OTYPER;     // Output type register
    volatile uint32_t OSPEEDR;    // Output speed register
    volatile uint32_t PUPDR;      // Pull-up/pull-down register
    volatile uint32_t IDR;        // Input data register
    volatile uint32_t ODR;        // Output data register
    volatile uint32_t BSRR;       // Bit set/reset register
    volatile uint32_t LCKR;       // Configuration lock register
    volatile uint32_t AFRL;       // Alternate function low register
    volatile uint32_t AFRH;       // Alternate function high register
} GPIOx_RegDef_t;
```

### Technology Stack

- **Language**: C (driver logic)
- **Assembly**: Startup code and vector table
- **Build System**: ARM-GCC toolchain
- **Debugger**: GDB with OpenOCD/ST-Link
- **Documentation**: Doxygen

---

## Projects Overview

### Project 000: Hello World

**Purpose**: Basic GPIO initialization and LED control

**Features**:

- GPIO port clock enabling via RCC
- GPIO pin mode configuration (output)
- Simple LED toggle using software delay loop
- Introduction to memory-mapped peripheral access

**Hardware Used**:

- On-board LEDs (PD12, PD13, PD14, PD15)

**Key Learning**:

- Basic GPIO output configuration
- Software delay implementation
- Peripheral clock management

---

### Project 001: STM Clock Enable

**Purpose**: Clock system configuration and external clock output

**Features**:

- HSE (High-Speed External) clock enabling
- MCO1 (Microcontroller Clock Output) pin configuration
- Clock routing to PA8 for external measurement
- GPIO alternate function configuration (AF0)

**Hardware Used**:

- PA8 (MCO1 output pin)
- Logic analyzer for clock verification

**Key Concepts**:

```c
f_MCO1 = f_HSE / Prescaler
```

**Key Learning**:

- RCC clock control register (RCC_CR)
- Clock configuration register (RCC_CFGR)
- MCO prescaler settings
- GPIO alternate function mapping

---

### Project 002: User Button Interrupt

**Purpose**: External interrupt configuration and handling

**Features**:

- EXTI (External Interrupt) line configuration
- SYSCFG port mapping
- NVIC interrupt priority and enabling
- ISR (Interrupt Service Routine) implementation
- Button debouncing techniques

**Hardware Used**:

- User button (PA0)
- On-board LEDs (PD12-PD15)

**Key Concepts**:

```c
EXTI_Line = Pin_Number
```

**Interrupt Flow**:

```
GPIO Pin → EXTI Controller → NVIC → CPU → ISR
```

**Key Learning**:

- EXTI configuration (IMR, RTSR, FTSR)
- SYSCFG external interrupt mapping
- NVIC interrupt enabling (ISER registers)
- Interrupt pending flag clearing
- Debouncing in ISR context

---

### Project 003: Testing STM32F407xx Drivers

**Purpose**: Modular driver development and testing framework

**Features**:

- Complete GPIO driver API implementation
- Structured driver architecture
- Configurable pin initialization
- Port-level and pin-level operations

**Driver Architecture**:

```c
// Configuration Structure
typedef struct {
    uint8_t GPIO_PIN_NUMBER;      // Pin 0-15
    uint8_t GPIO_MODE;            // Input/Output/Alt/Analog
    uint8_t GPIO_OP_TYPE;         // Push-pull/Open-drain
    uint8_t GPIO_PU_PD;           // Pull-up/Pull-down/None
    uint8_t GPIO_SPEED;           // Low/Medium/High/Very High
    uint8_t GPIO_ALT_FUNC;        // AF0-AF15
} GPIOx_Config_t;

// Handle Structure
typedef struct {
    GPIOx_RegDef_t *pGPIOx;       // Base address pointer
    GPIOx_Config_t GPIO_CONFIG;   // Configuration settings
} GPIOx_Handle_t;
```

**API Functions**:

```c
// Initialization and De-initialization
void gpio_pin_init(GPIOx_Handle_t *handle);
void gpio_port_deinit(GPIOx_RegDef_t *pGPIOx);

// Read/Write Operations
uint8_t gpio_read_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin);
uint16_t gpio_read_port(GPIOx_RegDef_t *pGPIOx);
void gpio_write_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin, uint8_t state);
void gpio_write_port(GPIOx_RegDef_t *pGPIOx, uint16_t value);
void gpio_toggle_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin);

// Interrupt Management
void gpio_irq_config(uint8_t pin, uint8_t trigger);
void gpio_irq_control(uint8_t irq_no, uint8_t en);
void gpio_irq_clear(uint8_t pin);
```

**Key Learning**:

- Modular driver design patterns
- API abstraction and encapsulation
- Configuration vs. operation separation
- Error handling strategies

---

## Concepts Covered

### Memory Architecture

- **Flash Memory**: Main program storage (0x0800 0000)
- **SRAM1**: 112 KB at 0x2000 0000
- **SRAM2**: 16 KB at 0x2001 C000
- **SRAM3**: 64 KB CCM at 0x2002 0000
- **System Memory**: ROM bootloader at 0x1FFF 0000

### Bus Architecture

```
           AHB (168 MHz)
                │
    ┌───────────┼───────────┐
    │           │           │
  AHB1        AHB2        AHB3
    │           │           │
  GPIO        USB         FMC
  DMA       Camera
  RCC
    │
    ├──── APB1 (42 MHz)
    │     └── TIM2-7, SPI2/3, I2C1-3, UART
    │
    └──── APB2 (84 MHz)
          └── TIM1/8, SPI1, USART1/6, ADC
```

### Clock System

```
HSE (16 MHz) ──┐
               ├──> PLL ──> SYSCLK (up to 168 MHz)
HSI (16 MHz) ──┘            │
                            ├──> AHB (HCLK)
                            │    └──> APB1 (PCLK1)
                            │    └──> APB2 (PCLK2)
                            └──> MCO1/MCO2
```

### GPIO Configuration

- **Modes**: Input, Output, Alternate Function, Analog
- **Output Types**: Push-Pull, Open-Drain
- **Speeds**: Low (2 MHz), Medium (25 MHz), High (50 MHz), Very High (100 MHz)
- **Pull resistors**: None, Pull-up, Pull-down
- **Alternate Functions**: AF0 through AF15

### Interrupt System

- **EXTI Lines**: 0-22 (16 GPIO + 7 internal)
- **Priority Levels**: 16 levels (0 = highest priority)
- **NVIC**: Nested Vectored Interrupt Controller
- **Vector Table**: Defined in startup assembly

---

## Getting Started

### Prerequisites

1. **Hardware**:

   - STM32F4 Discovery board
   - USB cable for ST-Link
   - (Optional) Logic analyzer

2. **Software**:
   - STM32CubeIDE (recommended) or
   - ARM GCC toolchain + Make + OpenOCD
   - Git

### Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/STM32F407-Drivers.git
cd STM32F407-Drivers

# Open in STM32CubeIDE
# File → Open Projects from File System → Select project folder
```

### Project Setup

1. **Import Project**:

   - Open STM32CubeIDE
   - File → Import → General → Existing Projects
   - Select desired project from `Projects/` directory

2. **Build Configuration**:

   - Debug configuration for development
   - Release configuration for optimized code

3. **Debugger Setup**:
   - Select ST-Link (ST-LINK GDB server)
   - Configure SWD interface
   - Set breakpoints as needed

---

## Building and Flashing

### Using STM32CubeIDE

```bash
# Build project
Project → Build All (Ctrl+B)

# Flash and debug
Run → Debug (F11)

# Or flash without debugging
Run → Run (Ctrl+F11)
```

### Using Command Line (ARM-GCC)

```bash
# Navigate to project directory
cd Projects/000_Hello_World

# Build
make clean
make all

# Flash using OpenOCD
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
        -c "program build/output.elf verify reset exit"

# Or using st-flash
st-flash write build/output.bin 0x8000000
```

---

## API Documentation

### GPIO Driver API

#### Initialization Functions

```c
/**
 * @brief  Initialize a GPIO pin with specified configuration
 * @param  handle: Pointer to GPIO handle structure
 * @retval None
 */
void gpio_pin_init(GPIOx_Handle_t *handle);

/**
 * @brief  Reset entire GPIO port to default state
 * @param  pGPIOx: GPIO port base address (GPIOA-GPIOI)
 * @retval None
 * @note   Uses RCC AHB1RSTR register
 */
void gpio_port_deinit(GPIOx_RegDef_t *pGPIOx);
```

#### Read/Write Functions

```c
/**
 * @brief  Read logic level of a GPIO pin
 * @param  pGPIOx: GPIO port base address
 * @param  pin: Pin number (0-15)
 * @retval Pin state (0 or 1)
 */
uint8_t gpio_read_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin);

/**
 * @brief  Write logic level to a GPIO pin
 * @param  pGPIOx: GPIO port base address
 * @param  pin: Pin number (0-15)
 * @param  state: 0 (LOW) or 1 (HIGH)
 * @retval None
 */
void gpio_write_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin, uint8_t state);

/**
 * @brief  Toggle GPIO pin output state
 * @param  pGPIOx: GPIO port base address
 * @param  pin: Pin number (0-15)
 * @retval None
 */
void gpio_toggle_pin(GPIOx_RegDef_t *pGPIOx, uint8_t pin);
```

#### Interrupt Functions

```c
/**
 * @brief  Configure EXTI line trigger type
 * @param  pin: Pin number (0-15)
 * @param  trigger: Rising/Falling/Both edge
 * @retval None
 */
void gpio_irq_config(uint8_t pin, uint8_t trigger);

/**
 * @brief  Enable or disable NVIC interrupt
 * @param  irq_no: IRQ number
 * @param  en: ENABLE or DISABLE
 * @retval None
 */
void gpio_irq_control(uint8_t irq_no, uint8_t en);

/**
 * @brief  Clear EXTI pending interrupt flag
 * @param  pin: Pin number (0-15)
 * @retval None
 */
void gpio_irq_clear(uint8_t pin);
```

### Usage Example

```c
#include "stm32f407xx.h"
#include "stm32f407xx_gpio.h"

int main(void) {
    GPIOx_Handle_t gpio_led;

    // Configure LED pin (PD12)
    gpio_led.pGPIOx = GPIOD;
    gpio_led.GPIO_CONFIG.GPIO_PIN_NUMBER = 12;
    gpio_led.GPIO_CONFIG.GPIO_MODE = GPIO_MODE_OUTPUT;
    gpio_led.GPIO_CONFIG.GPIO_OP_TYPE = GPIO_OP_TYPE_PP;
    gpio_led.GPIO_CONFIG.GPIO_SPEED = GPIO_SPEED_LOW;
    gpio_led.GPIO_CONFIG.GPIO_PU_PD = GPIO_PU_PD_NONE;

    // Initialize pin
    gpio_pin_init(&gpio_led);

    // Toggle LED
    while(1) {
        gpio_toggle_pin(GPIOD, 12);
        for(volatile int i = 0; i < 500000; i++);
    }
}
```

---

## Upcoming Modules

### Planned Peripherals

1. **SPI Driver**

   - Master/Slave modes
   - DMA support
   - Full-duplex communication

2. **I2C Driver**

   - Multi-master support
   - 7-bit and 10-bit addressing
   - Polling and interrupt modes

3. **UART/USART Driver**

   - Asynchronous communication
   - Hardware flow control
   - DMA transfer

4. **Timer Driver**

   - PWM generation
   - Input capture
   - Output compare
   - Encoder interface

5. **ADC Driver**

   - Single and continuous conversion
   - DMA circular mode
   - Multi-channel scanning

6. **DMA Driver**

   - Memory-to-memory
   - Peripheral-to-memory
   - Stream configuration

7. **Advanced Clock Configuration**
   - PLL configuration
   ```
   f_SYSCLK = (f_HSE / M) × N / P
   ```
   - System clock switching
   - Peripheral clock scaling

---

## Learning Resources

### Reference Documents

- **RM0090**: STM32F407 Reference Manual
- **PM0214**: STM32F4 Programming Manual
- **DS8626**: STM32F407VG Datasheet
- **UM1472**: STM32F4 Discovery Kit User Manual

### Documentation

Full API documentation is generated using Doxygen and available in:

```
Docs/html/index.html       # HTML documentation
Docs/refman.pdf            # PDF reference manual
```

### Key Sections in Reference Manual

- Section 6: Clock Control (RCC)
- Section 7: General-purpose I/Os (GPIO)
- Section 10: Interrupts and Events (EXTI)
- Section 12: Nested Vectored Interrupt Controller (NVIC)

---

## Learning Objectives

This repository is designed to help developers:

1. **Understand Hardware**

   - ARM Cortex-M4 architecture
   - Memory-mapped peripherals
   - Bus architecture and timing

2. **Master Register-Level Programming**

   - Direct register manipulation
   - Bit-field operations
   - Hardware abstraction design

3. **Build Reusable Drivers**

   - Modular code structure
   - API design principles
   - Documentation practices

4. **Navigate Reference Manuals**

   - Register descriptions
   - Peripheral operation
   - Timing diagrams

5. **Debug Embedded Systems**
   - SWD debugging
   - Logic analyzer usage
   - Peripheral register inspection

---

## Contributing

Contributions are welcome! Please follow these guidelines:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Follow existing code style and documentation standards
4. Add Doxygen comments for all public APIs
5. Test thoroughly on hardware
6. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
7. Push to the branch (`git push origin feature/AmazingFeature`)
8. Open a Pull Request

---

## Author

**Yuvraj Singh Rathore**

- Postgraduate, IIT Bombay
- Scientist, DRDO
- Location: Bangalore, India
- Interests: Embedded Systems, VLSI, Radar Communication Systems

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2025 Yuvraj Singh Rathore

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## Acknowledgments

- STMicroelectronics for comprehensive documentation
- ARM for Cortex-M4 architecture documentation
- Open-source embedded systems community

---

## Support

If you find this repository useful, please consider:

- Starring the repository on GitHub
- Sharing with fellow embedded enthusiasts
- Contributing improvements and bug fixes
- Reporting issues or suggesting enhancements

---

**Note**: This is an educational project focused on understanding low-level hardware programming. For production applications, consider using tested libraries like STM32 HAL or third-party RTOS solutions.
