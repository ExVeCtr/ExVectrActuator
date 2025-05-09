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
            pwmProtocol_ = pwmProtocol;
        }

        void PWM_Output::init() {

            pwmPin_.init();

            switch (pwmProtocol_)
            {
            case PWM_Output_Protocol::STANDARD:

                pwmPin_.setPinFrequency(400); // 500Hz allows for 0us to 2000us pulses.

                if (pwmPin_.getPinFrequency() != 400)
                    Core::printW("PWM_Output: PWM_Output() failed to set pwm pin to 500Hz. Returned Hz: %f.\n", pwmPin_.getPinFrequency());

                offset_ = 1;
                factor_ = 1;
                interval_ = 2.5;

                break;

            case PWM_Output_Protocol::ONESHOT125:

                pwmPin_.setPinFrequency(2000); // 4000Hz allows for 0us to 250us pulses.

                if (pwmPin_.getPinFrequency() != 2000)
                    Core::printW("PWM_Output: PWM_Output() failed to set pwm pin to 4000Hz. Returned Hz: %f.\n", pwmPin_.getPinFrequency());

                offset_ = 125;
                factor_ = 125;
                interval_ = 500;

                break;

            case PWM_Output_Protocol::ONESHOT42:

                pwmPin_.setPinFrequency(11904); // 11904Hz allows for 0us to 84.005us pulses.

                if (pwmPin_.getPinFrequency() != 11904)
                    Core::printW("PWM_Output: PWM_Output() failed to set pwm pin to 11904Hz. Returned Hz: %f.\n", pwmPin_.getPinFrequency());

                offset_ = 42;
                factor_ = 84;
                interval_ = 100;

                break;

            case PWM_Output_Protocol::MULTISHOT:

                pwmPin_.setPinFrequency(25000); // 40000Hz allows for 0us to 25us pulses.

                if (pwmPin_.getPinFrequency() != 25000)
                    Core::printW("PWM_Output: PWM_Output() failed to set pwm pin to 40000Hz. Returned Hz: %f.\n", pwmPin_.getPinFrequency());

                offset_ = 5;
                factor_ = 25;
                interval_ = 100;

                break;

            default:
                Core::printW("PWM_Output: PWM_Output() received an unsupported pwm protocol. Protocol given: %d.\n", size_t(pwmProtocol_));
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

            if (outputEnabled_)
                pwmPin_.setPinValue((currentValue_ * factor_ + offset_)/interval_);
        }

        float PWM_Output::getValue()
        {
            return currentValue_;
        }

        void PWM_Output::enableOutput(bool enable)
        {
            
            if (outputEnabled_ && !enable)
            {
                pwmPin_.setPinValue(0.0f); //Should pretty much disable it.
            }
            else if (!outputEnabled_ && enable)
            {
                setValue(currentValue_);
            }

        }

    }

}
