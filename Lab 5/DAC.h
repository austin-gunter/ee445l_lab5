#include <stdint.h>

// This will enable PortD 0-3 to work for the connected DAC
void DACinit(void);
void DAC_Out(uint16_t data);
