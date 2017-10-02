dbgu_print_ascii(const char *a) {}

#define SET_USER_LED_1 1<<8
#define SET_USER_LED_ 1<<29
#define RIGHT_BTN 1<<4
#define LEFT_BTN 1<<5

// Peripherial Enable Registers for controller B and C
volatile unsigned int* PIOB_PER = (volatile unsigned int)0xFFFFF400;
volatile unsigned int* PIOC_PER = (volatile unsigned int)0xFFFFF600;

// Power Management Controller Peripherial Clock Enable Register
volatile unsigned int PMC_PCER = volatile unsigned int(0x0010); 

// Pull Up Enable Register
volatile unsigned int PIO_PUER = volatile unsigned int(0x0F0FFF0F);

// Output Enable Registers for controllers B and C
volatile unsigned int* PIOB_OER = (volatile unsigned int)0xFFFFF410;
volatile unsigned int* PIOC_OER = (volatile unsigned int)0xFFFFF610;

// Output Disable Registers for controllers B and C
volatile unsigned int* PIOB_ODR = (volatile unsigned int)0xFFFFF414;
volatile unsigned int* PIOC_ODR = (volatile unsigned int)0xFFFFF614;

// Set Output Data Registers for controllers B and C
volatile unsigned int* PIOB_SODR = (volatile unsigned int)0xFFFFF430;
volatile unsigned int* PIOC_SODR = (volatile unsigned int)0xFFFFF630;

// Clear Output Data Registers for controllers B and C
volatile unsigned int* PIOB_CODR = (volatile unsigned int)0xFFFFF434;
volatile unsigned int* PIOC_CODR = (volatile unsigned int)0xFFFFF634;

void configureRegisters();

int main() {
  
  configureRegisters();
  
  

  
  while(1);
  return 0;
}

void configureRegisters() {
  /**** DIODS SETUP ****/
  // Peripherial enable register must be configured to set IO port in IO mode and enable further configuration
  *PIOB_PER = SET_USER_LED_1;
  // By defult, IO mode is set to input but we want diods to be used as an output(blinking)
  *PIOB_OER = SET_USER_LED_1;

// Peripherial enable register must be configured to set IO port in IO mode and enable further configuration
  *PIOC_PER = SET_USER_LED_2;
  // By defult, IO mode is set to input but we want diods to be used as an output(blinking)
  *PIOC_OER = SET_USER_LED_2;


  /**** BUTTONS SETUP ****/
  // By setting output disable register we immediately say that we want default input mode(because buttons are used as an input peripherial)
  // Since PER is already enabled we don't have to do this again and we can perform further configuration
  *PIOC_ODR = LEFT_BTN;
  *PIOC_ODR = RIGHT_BTN;
}