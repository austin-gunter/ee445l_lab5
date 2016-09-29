
// This initializes PortD to have ADC functionality
void DACinit(void){
  uint32_t delay;
  SYSCTL_RCGCSSI_R |= 0x02; // activate SSI1
  SYSCTL_RCGCGPIO_R |= 0x08; // activate Port D
  delay = SYSCTL_RCGCGPIO_R; // delay
  GPIO_PORTD_AFSEL_R |= 0x0F; // PD0-3 get alt func for DAC use
  GPIO_PORTD_DEN_R |= 0x0F; // enable PD0-3
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0xFFFF0000) | 0x00002222; // Specifies PD0-3 to have SSI1 func
  GPIO_PORTD_AMSEL_R = 0;
  SSI1_CR1_R = 0x00000000; // disable the SSI temporarily
  SSI1_CPSR_R |= 0x00000002; // 8MHz clock
  SSI1_CR0_R &= ~0x0000FFF0; // SCR = 0, SPH = 0, SPO = 0 Freeform
  SSI1_CR0_R |= 0x0F; // DSS = 16-bit data
  // SSI1_DR_R = data   check if this is necessary
  SSI1_CR1_R |= 0x02;
}
