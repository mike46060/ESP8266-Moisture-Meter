  /*
  
  A sketch to control the 10-Bit, 8-channel ADC MCP3008 on the Rheingold Heavy
  I2C and SPI Education Shield.  The code supposes the use of the Education Shield,
  but if you're using a breakout board, connect the CS pin to Digital 4, and the
  SPI pins in their usual locations.
 
  Website:   http://www.rheingoldheavy.com/mcp3008-tutorial-02-sampling-dc-voltage/
  Datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/21295d.pdf
 
 */
 
 
#include <SPI.h>                          // Include the SPI library
 
SPISettings MCP3008(2000000, MSBFIRST, SPI_MODE0);
 
const int  CS_MCP3008       = 10;         // ADC Chip Select Pin on Arduino
const byte adc_single_ch0   = (0x08);     // ADC Channel 0
const byte adc_single_ch1   = (0x09);     // ADC Channel 1
const byte adc_single_ch2   = (0x0A);     // ADC Channel 2
const byte adc_single_ch3   = (0x0B);     // ADC Channel 3
const byte adc_single_ch4   = (0x0C);     // ADC Channel 4
const byte adc_single_ch5   = (0x0D);     // ADC Channel 5
const byte adc_single_ch6   = (0x0E);     // ADC Channel 6
const byte adc_single_ch7   = (0x0F);     // ADC Channel 7

int adc_reading[8];
 
void setup()
{
  SPI.begin     ();
  Serial.begin  (9600);
  pinMode       (CS_MCP3008, OUTPUT);
  digitalWrite  (CS_MCP3008, LOW);        // Cycle the ADC CS pin to reset chip as per datasheet
  digitalWrite  (CS_MCP3008, HIGH);
}
  
void loop()
{
  // Set vRef Voltage
  double vRef = 3.30;     // Use 3.30 if using on board 3v3
                          // Use 4.91 if powering by usb
                          // Use 5.00 if powering by external 5V on Pin27
                          // Use 5.00 if powering by external 6-20V on Pin30
  
  // Clear Array                            
  for(int i = 0; i<8;++i)     
    adc_reading[i] = (int)0;
    
  // If using a single channel uncomment the following line and comment the Array below
  //adc_reading= adc_single_channel_read (adc_single_ch7);
  
  // Populate Array - if using multiple channels / Un/comment as needed
  adc_reading[0]= adc_single_channel_read (adc_single_ch0);
  adc_reading[1]= adc_single_channel_read (adc_single_ch1);
  adc_reading[2]= adc_single_channel_read (adc_single_ch2);
  adc_reading[3]= adc_single_channel_read (adc_single_ch3);
  adc_reading[4]= adc_single_channel_read (adc_single_ch4);
  adc_reading[5]= adc_single_channel_read (adc_single_ch5);
  adc_reading[6]= adc_single_channel_read (adc_single_ch6);
  adc_reading[7]= adc_single_channel_read (adc_single_ch7);
     
  // Print Array Values - Un/comment as needed
  //ch0
  Serial.print("ADC Ch ");
  Serial.print(adc_single_ch0 & 0x00);
  Serial.print(" Voltage: ");
  Serial.println((adc_reading[0] * vRef) / 1024, 2); // The ", 2)" specifies decimals to display
  delay(50);
  //ch1
  Serial.print("ADC Ch ");
  Serial.print(adc_single_ch1 & 0x01);
  Serial.print(" Voltage: ");
  Serial.println((adc_reading[1] * vRef) / 1024, 2); // The ", 2)" specifies decimals to display
  delay(50);
  //ch2
  Serial.print("ADC Ch ");
  Serial.print(adc_single_ch2 & 0x02);
  Serial.print(" Voltage: ");
  Serial.println((adc_reading[2] * vRef) / 1024, 2); // The ", 2)" specifies decimals to display
  delay(50);
  //ch3
  Serial.print("ADC Ch ");
  Serial.print(adc_single_ch3 & 0x03);
  Serial.print(" Voltage: ");
  Serial.println((adc_reading[3] * vRef) / 1024, 2); // The ", 2)" specifies decimals to display
  delay(50);
  //ch4
  Serial.print("ADC Ch ");
  Serial.print(adc_single_ch4 & 0x04);
  Serial.print(" Voltage: ");
  Serial.println((adc_reading[4] * vRef) / 1024, 2); // The ", 2)" specifies decimals to display
  delay(50);
  //ch5
  Serial.print("ADC Ch ");
  Serial.print(adc_single_ch5 & 0x05);
  Serial.print(" Voltage: ");
  Serial.println((adc_reading[5] * vRef) / 1024, 2); // The ", 2)" specifies decimals to display
  delay(50);
  //ch6
  Serial.print("ADC Ch ");
  Serial.print(adc_single_ch6 & 0x06);
  Serial.print(" Voltage: ");
  Serial.println((adc_reading[6] * vRef) / 1024, 2); // The ", 2)" specifies decimals to display
  delay(50);
  //ch7
  Serial.print("ADC Ch ");
  Serial.print(adc_single_ch7 & 0x07);
  Serial.print(" Voltage: ");
  Serial.println((adc_reading[7] * vRef) / 1024, 2); // The ", 2)" specifies decimals to display
  delay(50);
}
 
int adc_single_channel_read(byte readAddress)
{
  byte dataMSB =    0;
  byte dataLSB =    0;
  byte JUNK    = 0x00;
  
  SPI.beginTransaction (MCP3008);                             // Callout which SPI device we want to use
  digitalWrite         (CS_MCP3008, LOW);                     // 
  SPI.transfer         (0x01);                                // Start Bit
  dataMSB =            SPI.transfer(readAddress << 4) & 0x03; // Send readAddress and receive MSB data, masked to two bits
  dataLSB =            SPI.transfer(JUNK);                    // Push junk data and get LSB byte return
  digitalWrite         (CS_MCP3008, HIGH);                    //
  SPI.endTransaction   ();
 
  return               dataMSB << 8 | dataLSB;
}
