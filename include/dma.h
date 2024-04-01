#include "base.h"
#include "common-defines.h"

#define RCC_AHBENR_OFFSET           (0x38)
#define RCC_AHBENR                  (*(volatile unsigned int*)(RCC_PERIPHERAL + RCC_AHBENR_OFFSET))

#define DMA_CCR1_OFFSET             (0x08 + 0x14 * (1 - 1))
#define DMA_CCR1                    (*(volatile unsigned int*)(DMA1_PERIPHERAL + DMA_CCR1_OFFSET))

#define DMA_CNDTR1_OFFSET           (0x0C + 0x14 * (1 - 1))
#define DMA_CNDTR1                  (*(volatile unsigned int*)(DMA1_PERIPHERAL + DMA_CNDTR1_OFFSET))

#define DMA_CPAR1_OFFSET            (0x10 + 0x14 * (1 - 1))
#define DMA_CPAR1                   (*(volatile unsigned int*)(DMA1_PERIPHERAL + DMA_CPAR1_OFFSET))

#define DMA_CMAR1_OFFSET            (0x14 + 0x14 * (1 - 1))
#define DMA_CMAR1                   (*(volatile unsigned int*)(DMA1_PERIPHERAL + DMA_CMAR1_OFFSET))

#define DMA_IFCR_OFFSET             (0x04)
#define DMA_IFCR                    (*(volatile unsigned int*)(DMA1_PERIPHERAL + DMA_IFCR_OFFSET))

#define DMA_ISR_OFFSET              (0x00)
#define DMA_ISR                     (*(volatile unsigned int*)(DMA1_PERIPHERAL + DMA_ISR_OFFSET))

#define DMAMUX_C1CR_OFFSET          (0x000 + 0x04 * 0)
#define DMAMUX_C1CR                 (*(volatile unsigned int*)(DMAMUX_PERIPHERAL + DMAMUX_C1CR_OFFSET))



/*Prototypes*/
void dma_init(void);
void dma_config(uint32_t srcAddr, uint32_t dstAddr, uint16_t dataSize);
