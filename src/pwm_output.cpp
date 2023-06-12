#include "ExVectrCore/print.hpp"

#include "ExVectrHAL/analog_output.hpp"
#include "ExVectrHAL/pin_pwm.hpp"

#include "ExVectrActuator/pwm_output.hpp"

namespace VCTR
{

    namespace ACTR
    {

        PWM_Output::PWM_Output(HAL::PinPWM &pwmPin, PWM_Output_Protocol pwmProtocol) : pwmPin_(pwmPin)
        {

            switch (pwmProtocol)
            {
            case PWM_Output_Protocol::STANDARD:

                pwmPin_.setPinFrequency(500); // 500Hz allows for 0us to 2000us pulses.

                if (pwmPin.getPinFrequency() != 500)
                    Core::printW("PWM_Output: PWM_Output() failed to set pwm pin to 500Hz. Returned Hz: %f.\n", pwmPin.getPinFrequency());

                offset_ = 0.5;
                factor_ = 0.5;

                break;

            case PWM_Output_Protocol::ONESHOT125:

                pwmPin_.setPinFrequency(4000); // 4000Hz allows for 0us to 250us pulses.

                if (pwmPin.getPinFrequency() != 4000)
                    Core::printW("PWM_Output: PWM_Output() failed to set pwm pin to 4000Hz. Returned Hz: %f.\n", pwmPin.getPinFrequency());

                offset_ = 0.5;
                factor_ = 0.5;

                break;

            case PWM_Output_Protocol::ONESHOT42:

                pwmPin_.setPinFrequency(11904); // 11904Hz allows for 0us to 84.005us pulses.

                if (pwmPin.getPinFrequency() != 11904)
                    Core::printW("PWM_Output: PWM_Output() failed to set pwm pin to 11904Hz. Returned Hz: %f.\n", pwmPin.getPinFrequency());

                offset_ = 0.5;
                factor_ = 0.5;

                break;

            case PWM_Output_Protocol::MULTISHOT:

                pwmPin_.setPinFrequency(40000); // 40000Hz allows for 0us to 25us pulses.

                if (pwmPin.getPinFrequency() != 40000)
                    Core::printW("PWM_Output: PWM_Output() failed to set pwm pin to 40000Hz. Returned Hz: %f.\n", pwmPin.getPinFrequency());

                offset_ = 0.2;
                factor_ = 0.8;

                break;

            default:
                Core::printW("PWM_Output: PWM_Output() received an unsupported pwm protocol. Protocol given: %d.\n", size_t(pwmProtocol));
                break;
            }
        }

        void PWM_Output::setValue(float val)
        {

            currentValue_ = val;
            if (currentValue_ > 1.0)
                currentValue_ = 1.0;
            else if (currentValue_ < 0.0)
                currentValue_ = 0.0;

            pwmPin_.setPinValue(currentValue_ * factor_ + offset_);
        }

        float PWM_Output::getValue()
        {
            return currentValue_;
        }

    }

}
