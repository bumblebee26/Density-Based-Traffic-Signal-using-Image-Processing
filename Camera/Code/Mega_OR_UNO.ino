// Pins configurations:
// SDA/SIOD ---> pin A4 (for Arduino UNO) | pin 20/SDA (for Arduino MEGA)
// SCL/SIOC ---> pin A5 (for Arduino UNO) | pin 21/SCL (for Arduino MEGA)
// MCLK/XCLK --> pin 11 (for Arduino UNO) | pin 10 (for Arduino MEGA)
// PCLK -------> pin 2
// VS/VSYNC ---> pin 3
// HS/HREF ----> pin 8
// D0 ---------> pin A0
// D1 ---------> pin A1
// D2 ---------> pin A2
// D3 ---------> pin A3
// D4 ---------> pin 4
// D5 ---------> pin 5
// D6 ---------> pin 6
// D7 ---------> pin 7

#include <Wire.h>

#define CAMERA_ADDRESS 0x21

// Definitions of functions for manipulating the Arduino boards pins according to each Arduino board registers, so the code will work for both Arduino UNO and Arduino MEGA:
// The only change is the connections of the SDA/SIOD, SCL/SIOC and MCLK/XCLK pins to each board (see the pins configurations above).
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // If you are using Arduino MEGA the IDE will automatically define the "__AVR_ATmega1280__" or "__AVR_ATmega2560__" constants.
#define TIMER2_PWM_A_PIN_MODE_OUTPUT() ({ DDRB |= 0b00010000; })
#define PIN2_DIGITAL_READ() ({ (PINE & 0b00010000) == 0 ? LOW : HIGH; })
#define PIN3_DIGITAL_READ() ({ (PINE & 0b00100000) == 0 ? LOW : HIGH; })
#define PIN4_DIGITAL_READ() ({ (PING & 0b00100000) == 0 ? LOW : HIGH; })
#define PIN5_DIGITAL_READ() ({ (PINE & 0b00001000) == 0 ? LOW : HIGH; })
#define PIN6_DIGITAL_READ() ({ (PINH & 0b00001000) == 0 ? LOW : HIGH; })
#define PIN7_DIGITAL_READ() ({ (PINH & 0b00010000) == 0 ? LOW : HIGH; })
#define PIN8_DIGITAL_READ() ({ (PINH & 0b00100000) == 0 ? LOW : HIGH; })
#define PINA0_DIGITAL_READ() ({ (PINF & 0b00000001) == 0 ? LOW : HIGH; })
#define PINA1_DIGITAL_READ() ({ (PINF & 0b00000010) == 0 ? LOW : HIGH; })
#define PINA2_DIGITAL_READ() ({ (PINF & 0b00000100) == 0 ? LOW : HIGH; })
#define PINA3_DIGITAL_READ() ({ (PINF & 0b00001000) == 0 ? LOW : HIGH; })
#elif defined(__AVR_ATmega328P__) // If you are using Arduino UNO the IDE will automatically define the "__AVR_ATmega328P__" constant.
#define TIMER2_PWM_A_PIN_MODE_OUTPUT() ({ DDRB |= 0b00001000; })
#define PIN2_DIGITAL_READ() ({ (PIND & 0b00000100) == 0 ? LOW : HIGH; })
#define PIN3_DIGITAL_READ() ({ (PIND & 0b00001000) == 0 ? LOW : HIGH; })
#define PIN4_DIGITAL_READ() ({ (PIND & 0b00010000) == 0 ? LOW : HIGH; })
#define PIN5_DIGITAL_READ() ({ (PIND & 0b00100000) == 0 ? LOW : HIGH; })
#define PIN6_DIGITAL_READ() ({ (PIND & 0b01000000) == 0 ? LOW : HIGH; })
#define PIN7_DIGITAL_READ() ({ (PIND & 0b10000000) == 0 ? LOW : HIGH; })
#define PIN8_DIGITAL_READ() ({ (PINB & 0b00000001) == 0 ? LOW : HIGH; })
#define PINA0_DIGITAL_READ() ({ (PINC & 0b00000001) == 0 ? LOW : HIGH; })
#define PINA1_DIGITAL_READ() ({ (PINC & 0b00000010) == 0 ? LOW : HIGH; })
#define PINA2_DIGITAL_READ() ({ (PINC & 0b00000100) == 0 ? LOW : HIGH; })
#define PINA3_DIGITAL_READ() ({ (PINC & 0b00001000) == 0 ? LOW : HIGH; })
#endif


void initializePWMTimer() {
  cli();
  TIMER2_PWM_A_PIN_MODE_OUTPUT(); // Set the A PWM pin of TIMER2 to output
  ASSR &= ~(_BV(EXCLK) | _BV(AS2));
  TCCR2A = (1 << COM2A0) | (1 << WGM21) | (1 << WGM20);
  TCCR2B = (1 << WGM22) | (1 << CS20);
  OCR2A = 0;
  sei();
}

byte readCameraRegister(byte registerId) {
  Wire.beginTransmission(CAMERA_ADDRESS);
  Wire.write(registerId);
  Wire.endTransmission();
  Wire.requestFrom(CAMERA_ADDRESS, 1);
  while (Wire.available() <= 0);
  byte registerValue = Wire.read();
  delay(1);
  return registerValue;
}

void writeCameraRegister(byte registerId, byte registerValue) {
  Wire.beginTransmission(CAMERA_ADDRESS);
  Wire.write(registerId);
  Wire.write(registerValue);
  Wire.endTransmission();
  delay(1);
}

void captureFrame(unsigned int frameWidth, unsigned int frameHeight) {
  Serial.print("*RDY*"); // send to the frame capture software a "start of frame" message for beginning capturing

  delay(1000);

  cli(); // disable all interrupts during frame capture (because it needs to be as fast as possible)
  while (PIN3_DIGITAL_READ() == LOW); // wait until VS/VSYNC pin is high
  while (PIN3_DIGITAL_READ() == HIGH); // wait until VS/VSYNC pin is low
  unsigned int tempWidth = 0;
  while (frameHeight--) {
    tempWidth = frameWidth;
    while (tempWidth--) {
      while (PIN2_DIGITAL_READ() == LOW); // wait until PCLK pin is high
      while (PIN2_DIGITAL_READ() == HIGH); // wait until PCLK pin is low
      byte byteToWrite = 0b00000000;
      byteToWrite |= ((PIN7_DIGITAL_READ() == HIGH) << 7);
      byteToWrite |= ((PIN6_DIGITAL_READ() == HIGH) << 6);
      byteToWrite |= ((PIN5_DIGITAL_READ() == HIGH) << 5);
      byteToWrite |= ((PIN4_DIGITAL_READ() == HIGH) << 4);
      byteToWrite |= ((PINA3_DIGITAL_READ() == HIGH) << 3);
      byteToWrite |= ((PINA2_DIGITAL_READ() == HIGH) << 2);
      byteToWrite |= ((PINA1_DIGITAL_READ() == HIGH) << 1);
      byteToWrite |= ((PINA0_DIGITAL_READ() == HIGH));
      UDR0 = byteToWrite; // send data via serial connection with UART register (we need to use the serial register directly for fast transfer)
      while (PIN2_DIGITAL_READ() == LOW); // wait until PCLK pin is high
      while (PIN2_DIGITAL_READ() == HIGH); // wait until PCLK pin is low
      // ignore each second byte (for a grayscale image we only need each first byte, which represents luminescence)
    }
  }
  sei(); // enable all interrupts
  
  delay(1000);
}


void setup() {
  initializePWMTimer();
  Wire.begin();
  Serial.begin(1000000); // the frame capture software communicates with the Arduino at a baud rate of 1MHz
}

void loop() {
  captureFrame(320, 240); // capture a frame at QVGA resolution (320 x 240)
}
