#include "stm32f429xx.h"

// 定义常用宏
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 
#define	MODIFY_REG_BITS(REG, CLEARMASK, VALUE)	MODIFY_REG(REG, CLEARMASK, ((VALUE)<<POSITION_VAL(CLEARMASK)) & (CLEARMASK))

// GPIO mode
#define	GPIO_MODE_INPUT		0UL
#define	GPIO_MODE_OUTPUT	1UL
#define	GPIO_MODE_AF		2UL
#define	GPIO_MODE_ANALOG	3UL

//  GPIO output type
#define	GPIO_OTYPE_PUSH_PULL	0UL
#define	GPIO_OTYPE_OPEN_DRAIN	1UL

// GPIO output speed
#define	GPIO_OSPEED_2M		0UL
#define	GPIO_OSPEED_25M		1UL
#define	GPIO_OSPEED_50M		2UL
#define	GPIO_OSPEED_100M	3UL

// GPIO pull up/down or floating
#define	GPIO_PUPDR_FLOATING	0UL
#define	GPIO_PUPDR_PULL_UP	1UL
#define	GPIO_PUPDR_PULL_DOWN	2UL
#define	GPIO_PUPDR_RESERVED	3UL

// GPIO AF group
#define	GPIO_AF0		0x0UL
#define	GPIO_AF1		0x1UL
#define	GPIO_AF2		0x2UL
#define	GPIO_AF3		0x3UL
#define	GPIO_AF4		0x4UL
#define	GPIO_AF5		0x5UL
#define	GPIO_AF6		0x6UL
#define	GPIO_AF7		0x7UL
#define	GPIO_AF8		0x8UL
#define	GPIO_AF9		0x9UL
#define	GPIO_AF10		0xAUL
#define	GPIO_AF11		0xBUL
#define	GPIO_AF12		0xCUL
#define	GPIO_AF13		0xDUL
#define	GPIO_AF14		0xEUL
#define	GPIO_AF15		0xFUL

#define GPIO_AF_RTC_50Hz	GPIO_AF0
#define GPIO_AF_MCO		GPIO_AF0
#define GPIO_AF_TAMPER		GPIO_AF0
#define GPIO_AF_SWJ		GPIO_AF0
#define GPIO_AF_TRACE		GPIO_AF0
#define GPIO_AF_TIM1		GPIO_AF1
#define GPIO_AF_TIM2		GPIO_AF1
#define GPIO_AF_TIM3		GPIO_AF2
#define GPIO_AF_TIM4		GPIO_AF2
#define GPIO_AF_TIM5		GPIO_AF2
#define GPIO_AF_TIM8 		GPIO_AF3
#define GPIO_AF_TIM9 		GPIO_AF3
#define GPIO_AF_TIM10		GPIO_AF3
#define GPIO_AF_TIM11		GPIO_AF3
#define GPIO_AF_I2C1		GPIO_AF4
#define GPIO_AF_I2C2		GPIO_AF4
#define GPIO_AF_I2C3		GPIO_AF4
#define GPIO_AF_SPI1		GPIO_AF5
#define GPIO_AF_SPI2		GPIO_AF5
#define GPIO_AF_SPI3		GPIO_AF6
#define GPIO_AF_USART1 		GPIO_AF7
#define GPIO_AF_USART2 		GPIO_AF7
#define GPIO_AF_USART3 		GPIO_AF7
#define GPIO_AF_UART4 		GPIO_AF8
#define GPIO_AF_UART5 		GPIO_AF8
#define GPIO_AF_USART6		GPIO_AF8
#define GPIO_AF_CAN1 		GPIO_AF9
#define GPIO_AF_CAN2 		GPIO_AF9
#define GPIO_AF_TIM12		GPIO_AF9
#define GPIO_AF_TIM13		GPIO_AF9
#define GPIO_AF_TIM14		GPIO_AF9
#define GPIO_AF_OTG_FS		GPIO_AF10
#define GPIO_AF_OTG_HS		GPIO_AF10
#define GPIO_AF_ETH		GPIO_AF11
#define GPIO_AF_FMC		GPIO_AF12
#define GPIO_AF_OTG_HS_FS	GPIO_AF12
#define GPIO_AF_SDIO		GPIO_AF12
#define GPIO_AF_DCMI		GPIO_AF13
#define GPIO_AF_LTDC		GPIO_AF14
#define GPIO_AF_EVENTOUT	GPIO_AF15

// 设置为输出时，默认为Pull（GPIO_PUPDR_PULL_UP和GPIO_PUPDR_PULL_DOWN分别对应于1和0）
#define	GPIO_setup(group, pin, mode, output_type, output_speed, pull, AF)		\
	do{										\
		GPIO##group->MODER	= (GPIO##group->MODER&~(3UL<<(2*pin)))|		\
					  (mode<<(2*pin));				\
		GPIO##group->OTYPER	= (GPIO##group->OTYPER&~(1UL<<pin))|		\
					  (output_type<<pin);				\
		GPIO##group->OSPEEDR	= (GPIO##group->OSPEEDR&~(3UL<<(2*pin)))|	\
					  (output_speed<<(2*pin));			\
		GPIO##group->PUPDR	= (GPIO##group->PUPDR&~(3UL<<(2*pin)))|		\
					  (pull<<(2*pin));				\
		GPIO##group->ODR	= (GPIO##group->ODR&~(1UL<<pin))|		\
					  ((pull==GPIO_PUPDR_PULL_UP?1:0)<<(pin));	\
		GPIO##group->AFR[(pin>=8)?1:0]	= (GPIO##group->AFR[(pin>=8)?1:0]	\
						  &~(0xFUL<<(4*(pin%8)))) |		\
						  (AF<<(4*(pin%8)));			\
	}while(0)

// GPIO设置
// 	功能引脚
#define	GPIO_SET_AF(group, pin, AF)		GPIO_setup(group, pin, GPIO_MODE_AF, GPIO_OTYPE_PUSH_PULL, GPIO_OSPEED_100M, GPIO_PUPDR_FLOATING, AF)
// 	LED
#define	GPIO_SET_LED(group, pin)		GPIO_setup(group, pin, GPIO_MODE_OUTPUT, GPIO_OTYPE_PUSH_PULL, GPIO_OSPEED_50M, GPIO_PUPDR_PULL_DOWN, 0)
//	GPIO输入，默认拉低
#define	GPIO_SET_INPUT_LOW(group, pin)		GPIO_setup(group, pin, GPIO_MODE_INPUT, GPIO_OTYPE_PUSH_PULL, GPIO_OSPEED_50M, GPIO_PUPDR_PULL_DOWN, 0)
//	GPIO输入，默认拉高
#define	GPIO_SET_INPUT_HIGH(group, pin)		GPIO_setup(group, pin, GPIO_MODE_INPUT, GPIO_OTYPE_PUSH_PULL, GPIO_OSPEED_50M, GPIO_PUPDR_PULL_UP, 0)
//	GPIO输出，默认输出低
#define	GPIO_SET_OUTPUT_LOW(group, pin)		GPIO_setup(group, pin, GPIO_MODE_OUTPUT, GPIO_OTYPE_PUSH_PULL, GPIO_OSPEED_50M, GPIO_PUPDR_PULL_DOWN, 0)
//	GPIO输出，默认输出高
#define	GPIO_SET_OUTPUT_HIGH(group, pin)	GPIO_setup(group, pin, GPIO_MODE_OUTPUT, GPIO_OTYPE_PUSH_PULL, GPIO_OSPEED_50M, GPIO_PUPDR_PULL_UP, 0)

	
// GPIO引脚输出引脚拉高或拉低
#define	GPIO_OUTPUT(group, pin, value)	GPIO##group->ODR = (GPIO##group->ODR&~(1UL<<pin))|((value==0?0:1)<<pin)
// GPIO引脚输出读取
#define	GPIO_INPUT(group, pin)	(((GPIO##group->IDR)&(1UL<<pin))?1:0)
