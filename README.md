# 🧠 STM32 Driver Development

This repository contains **bare-metal driver development projects** for the **STM32F407 Discovery Board**, written entirely from scratch without using HAL or STM32Cube libraries.  
Each project focuses on a specific hardware feature or peripheral of the STM32 microcontroller, helping to build a deep understanding of low-level embedded system design.

---

## 📂 Repository Structure

| Folder | Description |
|---------|--------------|
| **000_Hello_World** | Basic GPIO configuration — toggle an LED using software delay. |
| **001_STM_CLOCK_ENABLE** | Demonstrates clock enabling for GPIO peripherals and verifies clock using MCO pin on a logic analyzer. |
| **002_User_button_interrupt** | Implements an **external interrupt (EXTI)** on the user button (PA0) to toggle LEDs using an ISR. |
| **Resource** | Reference materials, schematics, and supporting documentation. |

---

## ⚙️ Hardware Used

- **Microcontroller:** STM32F407VG (ARM Cortex-M4)  
- **Board:** STM32F4 Discovery Kit  
- **Core Clock:** 16 MHz (HSE)  
- **Tools Required:**
  - STM32CubeIDE or any ARM-GCC-based IDE  
  - ST-Link debugger/programmer  
  - Logic analyzer (optional, for clock verification)

---

## 💻 Development Approach

All drivers are written **bare-metal**, meaning:
- Direct register access (no HAL or StdPeriph libraries)
- Complete control of clock gating, GPIO modes, and interrupt configuration
- Written in **C** with startup assembly for vector table mapping

---

## 🧩 Concepts Covered So Far

- GPIO initialization and configuration  
- RCC (Reset and Clock Control) fundamentals  
- External interrupt (EXTI) setup using SYSCFG  
- NVIC configuration and interrupt masking  
- Debouncing techniques in ISRs  
- Understanding the STM32 bus architecture (AHB/APB)  

---

## 🚀 Upcoming Modules

Planned future modules include:
- SPI Master/Slave driver implementation  
- I2C driver (polling + interrupt-based)  
- UART communication  
- Timer-based LED blinking (SysTick & TIM2)  
- ADC/DAC configuration and data acquisition  
- DMA-controlled data transfers  

---

## 🧠 Learning Objective

This repository is a **step-by-step journey** toward mastering STM32 microcontrollers through:
- Building reusable driver-level code  
- Understanding how ARM Cortex-M4 interfaces with peripherals  
- Learning to read and apply the STM32 Reference Manual and Datasheet  

---

## 🧑‍💻 Author

**Yuvraj Singh Rathore**  
🎓 IIT Bombay Postgraduate | Scientist, DRDO  
📍 Bangalore, India  
💬 Interested in Embedded Systems, VLSI, and Radar Communication Systems  

---

## 📜 License

This project is released under the **MIT License** — free to use, modify, and distribute with attribution.

---

### ⭐ If you find this repository helpful, don’t forget to star it on GitHub!
