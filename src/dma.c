#include "dma.h"
#include "usart.h"

#define DMA1_EN                 (1U << 0)
#define DMA_CCR1_DIR            (1U << 4)
#define DMA_CCR1_CIRC           (1U << 5)
#define DMA_CCR1_PSIZE          ((1 << 8) | (1 << 9))
#define DMA_CCR1_MSIZE          ((1 << 10) | (1 << 11))
#define DMA_CCR1_PL             ((1 << 12) | (1 << 13)) 
#define DMA_CCR1_EN             (1U << 0)
#define DMA_CCR1_HTIE           (1U << 2)
#define DMA_CCR1_TCIE           (1U << 1)
#define DMA_CCR1_TEIE           (1U << 3)
#define DMA_CCR1_PINC           (1U <<  6)
#define DMA_CCR1_MINC           (1U <<  7)

#define DMA_ISR_HTIF1           (1U << 2)
#define DMA_ISR_TCIF1           (1U << 1)

#define DMA_IFCR_CTCIF1         (1U << 1)
#define DMA_IFCR_CHTIF1		(1U << 2)

#define DMAMUX_C1CR_DMAREQ_ID   (0x35 << 0)
void dma_init(void){

	RCC_AHBENR |= DMA1_EN; // Enable clock

	DMA_CCR1 |= DMA_CCR1_DIR; // Read from memory
	
	DMA_CCR1 |= DMA_CCR1_CIRC; // Circular mode
	
	DMA_CCR1 |= DMA_CCR1_MINC; // Enable memory increment
	
	DMA_CCR1 &= ~DMA_CCR1_PINC; // Disable peripheral increment
	
	DMA_CCR1 &= ~DMA_CCR1_PSIZE; // Peripheral size 8 bits
	
	DMA_CCR1 &= ~DMA_CCR1_MSIZE; // Memory size 8 bits
	
	DMA_CCR1 &= ~DMA_CCR1_PL; // Priority level
	
	DMA_CCR1 |= DMA_CCR1_TCIE | 
		    DMA_CCR1_HTIE |
		    DMA_CCR1_TEIE; // Complete, half and error transfer interrupts enbaled
	
}

void dma_config(uint32_t srcAddr, uint32_t dstAddr, uint16_t dataSize){

	DMA_CNDTR1  = dataSize;
	
	DMA_CMAR1 = srcAddr;
	
	DMA_CPAR1 = dstAddr;
	
	DMAMUX_C1CR |= DMAMUX_C1CR_DMAREQ_ID; //Link USART2_TX -----> channel 1 DMA
	
	DMA_CCR1 |= DMA_CCR1_EN; // Enable channel
}

void DMA1_Channel1_IRQHandler(void){
	if (DMA_ISR & DMA_ISR_HTIF1){
		DMA_IFCR |= DMA_IFCR_CHTIF1; // Half transfer flag clear for channel 1
	}
	
	if (DMA_ISR & DMA_ISR_TCIF1){
		DMA_IFCR |= DMA_IFCR_CTCIF1; // Transfer complete flag clear for channel 1
	}

}
