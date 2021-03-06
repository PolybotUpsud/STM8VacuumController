#define _SFR_(mem_addr) (*(volatile uint8_t *)(0x5000 + (mem_addr)))

#define PA_ODR _SFR_(0x00)
#define PA_IDR _SFR_(0x01)
#define PA_DDR _SFR_(0x02)
#define PA_CR1 _SFR_(0x03)
#define PA_CR2 _SFR_(0x04)

#define PB_ODR _SFR_(0x05)
#define PB_IDR _SFR_(0x06)
#define PB_DDR _SFR_(0x07)
#define PB_CR1 _SFR_(0x08)
#define PB_CR2 _SFR_(0x09)

#define PC_ODR _SFR_(0x0A)
#define PC_IDR _SFR_(0x0B)
#define PC_DDR _SFR_(0x0C)
#define PC_CR1 _SFR_(0x0D)
#define PC_CR2 _SFR_(0x0E)

#define PD_ODR _SFR_(0x0F)
#define PD_IDR _SFR_(0x10)
#define PD_DDR _SFR_(0x11)
#define PD_CR1 _SFR_(0x12)
#define PD_CR2 _SFR_(0x13)

#define PE_ODR _SFR_(0x14)
#define PE_IDR _SFR_(0x15)
#define PE_DDR _SFR_(0x16)
#define PE_CR1 _SFR_(0x17)
#define PE_CR2 _SFR_(0x18)

#define PF_ODR _SFR_(0x19)
#define PF_IDR _SFR_(0x1A)
#define PF_DDR _SFR_(0x1B)
#define PF_CR1 _SFR_(0x1C)
#define PF_CR2 _SFR_(0x1D)

#define UART_SR _SFR_(0x230)
#define UART_TXE 7
#define UART_TC 6
#define UART_RXNE 5
#define UART_DR _SFR_(0x231)
#define UART_BRR1 _SFR_(0x232)
#define UART_BRR2 _SFR_(0x233)
#define UART_CR1 _SFR_(0x234)
#define UART_CR2 _SFR_(0x235)
#define UART_TEN 3
#define UART_REN 2
