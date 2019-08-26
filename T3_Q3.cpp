/**
 ============================================================================
 * @file analogue-example.cpp (180.ARM_Peripherals/Snippets)
 * @brief Example showing use of a single-ended ADC channel
 *
 *  Created on: 10/6/2016
 *      Author: podonoghue
 ============================================================================
 */
#include "hardware.h"

using namespace USBDM;

/*
 * Demonstrates single-ended conversion on a channel
 */

// Connection mapping - change as required
// Note - many actions on the channel affect the entire ADC

// Shared ADC to use
using Adc        = Adc0;

// ADC channel to use
using AdcChannel = Adc::Channel<15>;

using heater = GpioC<0>;

// Resolution to use for ADC
constexpr AdcResolution adcResolution = AdcResolution_10bit_se;

int main(void) {
   // Enable and configure ADC
   Adc::configure(AdcResolution_12bit_se);

   // Calibrate before first use
   Adc::calibrate();

   // May change current resolution as needed e.g.
   Adc::setResolution(adcResolution);

   // Connect ADC channel to pin
   //button later
   AdcChannel::setInput();
   heater::setOutput();

   float minTemp = 15.0;
   float maxTemp = 35.0;

   //int setTemp = 20;
   //int offset = 2;

   float heatOnTemp = 18.0;
   float heatOffTemp = 22.0;
   float currentTemperature;

   for(;;) {
      // Do next conversion
      uint32_t value = AdcChannel::readAnalogue();
      currentTemperature = 1.0*minTemp + (maxTemp - minTemp)/Adc::getSinglendeddMaximum(adcResolution) * value;

      if (currentTemperature <= heatOnTemp)
      {
    	  heater::on();
      }

      if (currentTemperature >= heatOffTemp)
      {
    	  heater::off();
      }

      console.write("currentTemp = ").write(currentTemperature).writeln(" degrees");

      waitMS(5000);
   }
}
