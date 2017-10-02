dbgu_print_ascii(const char *a) {}

#define SET_DS_1 1<<8
#define SET_DS_2 1<<29
#define SET_BP2 1<<4
#define SET_BP1 1<<5
#define SET_CLOCK  1<<4

#define DELAY_VALUE 100000
#define SWITCH_LED 100000


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

// Pin Data Status Register
volatile unsigned int *PIOC_PDSR = (volatile unsigned int *) 0xFFFFF63C;

void configureLEDs();
void configurreButtons();
void configureRegisters();
unsigned int checkIfLeftButtonPressed();
unsigned int checkIfRightButtonPressed();
void handleButtonPressed();
void delay(unsigned int);
void switchOnDS2();
void switchOffDS2();
void switchOnDS1();
void switchOffDS1();


int main() {
  
  configureRegisters();
  unsigned int counter = 0;

  while(1) {
    handleButtonPressed();

    if (counter < SWITCH_LED) {
      switchOnDS2();
    } else if (counter > SWITCH_LED) {
      switchOffDS2();
    }
    
    if (counter == 2 * SWITCH_LED) increment = 0;

    delay(DELAY_VALUE);
    counter++;
  }
  return 0;
}

void switchOnDS2() {
  PIOC_CODR = SET_DS_2;
}

void switchOffDS2() {
  PIOC_SODR = SET_DS_2;
}

void switchOnDS1() {
  PIOB_CODR = SET_DS_1;
}

void switchOffDS1() {
  PIOB_SODR = SET_DS_1;
}

void configureRegisters() {
  configureLEDs();
  configurreButtons();
  *PMC_PCER = SET_CLOCK;
}

void configureLEDs() {
  // Peripherial enable register must be configured to set IO port in IO mode and enable further configuration
  *PIOB_PER = SET_DS_1;
  // By defult, IO mode is set to input but we want diods to be used as an output(blinking)
  *PIOB_OER = SET_DS_1;

// Peripherial enable register must be configured to set IO port in IO mode and enable further configuration
  *PIOC_PER = SET_DS_2;
  // By defult, IO mode is set to input but we want diods to be used as an output(blinking)
  *PIOC_OER = SET_DS_2;
}

void configurreButtons() {
  // By setting output disable register we immediately say that we want default input mode(because buttons are used as an input peripherial)
  // Since PER is already enabled we don't have to do this again and we can perform further configuration
  *PIOC_ODR = SET_BP1;
  *PIOC_ODR = SET_BP;

  // TODO: Enable Pull-ups to ensure state 1 when button is released
  //*PIO_PUER
}

void handleButtonPressed() {
  if(checkIfRightButtonPressed())
    switchOnDS1(); 
  
  if (checkIfLeftButtonPressed())
    switchOffDS1();
}

unsigned int checkIfLeftButtonPressed() {
  (~(*PIOC_PDSR & SET_BP1)) ? return 1 : return 0;
}

unsigned int checkIfRightButtonPressed() {
  (~(*PIOC_PDSR & SET_BP)) ? return 1 : return 0;
}

void delay(unsigned int delay) {
  unsigned int counter = 0;
  while (counter < delay)
    counter++;
}