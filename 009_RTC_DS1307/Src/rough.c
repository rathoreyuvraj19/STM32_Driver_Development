/* main_spi_rx_it.c
 *
 * Example: Receive 10 bytes over SPI1 as MASTER using interrupt-driven API.
 *
 * Assumptions:
 * - Your driver header stm32f407xx_spi.h provides:
 *     SPIx_Init, SPIx_Peri_Control, SPIx_IRQConfig, SPIx_IRQControl,
 *     SPIx_ReceiveDataIT, SPIx_IRQHandling, SPI_ApplicationEventCallback override point,
 *     SPI1, SPIx_Handle_t type, and relevant macros (SPI_TXRX_SUCCESS, SPI_EVENT_RX_CMPLT, ...)
 * - Your vector table routes SPI1 IRQ to SPI1_IRQHandler which calls SPIx_IRQHandling(&SPI1Handle).
 * - Simple GPIO functions GPIO_Init/WritePin exist (replace with your board code).
 */

#include "stm32f407xx_spi.h"
#include "stm32f407xx_gpio.h"   /* your GPIO helper; replace with real header */
#include <stdint.h>

/* ---------- Application resources ---------- */

/* receive buffer for 10 bytes */
static uint8_t spi1_rx_buf[10];

/* completion flag set in application callback (IRQ context) */
static volatile uint8_t spi1_rx_done = 0U;

/* SPI1 handle instance (global, used by IRQ wrapper) */
SPIx_Handle_t SPI1Handle = {
    .pSPIx = SPI1,
    .pTXBuffer = NULL,
    .TXLen = 0,
    .TXCount = 0,
    .TxState = SPI_STATE_READY,
    .pRXBuffer = NULL,
    .RXLen = 0,
    .RXCount = 0,
    .RxState = SPI_STATE_READY
};

/* ------------ Chip-select (CS) helpers ------------ */
/* Replace these with real GPIO port/pin and driver calls for your board */
#define CS_PORT   GPIOA
#define CS_PIN    4U

static void cs_config(void)
{
    GPIO_InitTypeDef gpio_cfg;
    gpio_cfg.pin   = CS_PIN;
    gpio_cfg.mode  = GPIO_MODE_OUTPUT;
    gpio_cfg.speed = GPIO_SPEED_HIGH;
    gpio_cfg.pull  = GPIO_NOPULL;
    GPIO_Init(CS_PORT, &gpio_cfg);
    /* default high (inactive) */
    GPIO_WritePin(CS_PORT, CS_PIN, 1);
}

static inline void cs_assert(void)   { GPIO_WritePin(CS_PORT, CS_PIN, 0); } /* active low */
static inline void cs_deassert(void) { GPIO_WritePin(CS_PORT, CS_PIN, 1); }

/* ------------ Application callback (overrides weak symbol) ------------
   This runs in IRQ context. Keep it short: set flag and deassert CS.  */
void SPI_ApplicationEventCallback(SPIx_Handle_t *pHandle, uint8_t AppEv)
{
    (void)pHandle;
    if (AppEv == SPI_EVENT_RX_CMPLT) {
        /* Reception finished successfully */
        cs_deassert();         /* release slave select */
        spi1_rx_done = 1U;     /* signal main loop */
    } else if (AppEv == SPI_EVENT_OVR_ERR) {
        /* Overrun error: deassert CS and signal error */
        cs_deassert();
        spi1_rx_done = 2U;
    }
}

/* ------------ SPI1 IRQ wrapper (vector must call this) ------------
   Ensure your vector table names this function or adapt accordingly. */
extern void SPI1_IRQHandler(void);
void SPI1_IRQHandler(void)
{
    SPIx_IRQHandling(&SPI1Handle);
}

/* ------------ Hardware init helpers (GPIO + SPI config) ------------- */
static void spi1_hw_init(void)
{
    /* 1) Configure CS GPIO */
    cs_config();
    cs_deassert();

    /* 2) Configure SPI1 peripheral parameters (fill your config struct) */
    SPI_Config_t cfg;
    cfg.SPI_DEVICE_MODE = SPI_DEVICE_MODE_MASTER;
    cfg.SPI_BUS_MODE    = SPI_BUS_MODE_FULL_DUPLEX; /* use TXE for dummy writes */
    cfg.SPI_CLOCK_SPEED = SPI_CLOCK_DIV16;          /* adjust as required */
    cfg.SPI_CPOL        = SPI_CPOL_LOW;
    cfg.SPI_CPHA        = SPI_CPHA_1EDGE;
    cfg.SPI_FRAME_SIZE  = SPI_FRAME_8BIT;
    cfg.SPI_SSM_SETTING = SPI_SSM_ENABLE;          /* software NSS */
    cfg.SPI_BIT_ORDER   = SPI_BIT_MSB_FIRST;
    cfg.SPI_SSOE        = SPI_SSOE_DISABLE;
    cfg.SPI_CRC_EN      = 0U;

    SPI1Handle.SPI_CONFIG = cfg;

    /* Initialize SPI1 (this should configure GPIO AF for SCK/MISO/MOSI inside) */
    SPIx_Init(&SPI1Handle);

    /* Enable SPI peripheral (SPE bit) */
    SPIx_Peri_Control(SPI1, ENABLE);
}

/* -------------------------- main ------------------------------------ */
int main(void)
{
    uint8_t rc;

    /* Basic hardware initialization (clocking, etc.) should already be done */

    /* Initialize SPI and CS GPIO */
    spi1_hw_init();

    /* Configure NVIC priority for SPI1 beforehand (safe order) */
    SPIx_IRQConfig(IRQ_NUM_SPI1, 3U); /* priority 3 (example) */

    /* Assert CS (select slave) before starting the master receive */
    cs_assert();

    /* Start a 10-byte interrupt-driven receive
       - This populates the handle and enables RXNEIE (and TXEIE in master mode).
       - It does NOT enable NVIC in this example; we enable NVIC next. */
    rc = SPIx_ReceiveDataIT(&SPI1Handle, spi1_rx_buf, sizeof(spi1_rx_buf));
    if (rc != SPI_TXRX_SUCCESS) {
        /* failed to start transfer (busy or invalid params) */
        cs_deassert();
        while (1) { /* error handling: hang or blink LED */ }
    }

    /* Enable NVIC line for SPI1 now that peripheral interrupts are set */
    SPIx_IRQControl(IRQ_NUM_SPI1, ENABLE);

    /* Wait for completion flag set by application callback (simple busy-wait) */
    while (spi1_rx_done == 0U) {
        /* Optionally sleep / do other work */
    }

    /* Check result */
    if (spi1_rx_done == 1U) {
        /* Successful reception: spi1_rx_buf[0..9] contain the 10 bytes */
        /* Process received data here */
    } else {
        /* spi1_rx_done == 2U => OVR or other error */
    }

    /* Cleanup: disable SPI peripheral interrupts and NVIC line */
    SPIx_PeripheralInterruptControl(SPI1, SPI_IT_TYPE_RXNEIE, DISABLE);
    SPIx_PeripheralInterruptControl(SPI1, SPI_IT_TYPE_TXEIE, DISABLE);
    SPIx_IRQControl(IRQ_NUM_SPI1, DISABLE);

    while (1) {
        /* main loop */
    }

    /* never reached */
    return 0;
}
