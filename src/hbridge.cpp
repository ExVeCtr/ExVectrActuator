#include "ExVectrCore/print.hpp"

#include "ExVectrHAL/analog_output.hpp"
#include "ExVectrHAL/pin_pwm.hpp"
#include "ExVectrHAL/pin_gpio.hpp"

#include "ExVectrActuator/hbridge.hpp"

namespace VCTR
{

    namespace ACTR
    {

        // Implementation of HBridge2Wire class
        HBridge2Wire::HBridge2Wire(HAL::PinPWM &pinA, HAL::PinPWM &pinB) : pinA_(pinA), pinB_(pinB)
        {}

        HAL::IO_TYPE_t HBridge2Wire::getOutputType() const
        {
            return HAL::IO_TYPE_t::ANALOG_HBRIDGE;
        }

        bool HBridge2Wire::setOutputParam(HAL::IO_PARAM_t param, int32_t value)
        {
            switch (param)
            {
            case HAL::IO_PARAM_t::SPEED:
                pinA_.setPinFrequency(value);
                pinB_.setPinFrequency(value);
                return true;
            default:
                Core::printW("HBridge2Wire::setOutputParam: Parameter not supported. Param given: %d, val %d\n", param, value);
                return false;
            }
        }

        int32_t HBridge2Wire::writable()
        {
            return 1;
        }

        size_t HBridge2Wire::writeValue(const float *values, size_t size)
        {
            if (size < 1)
            {
                return 0;
            }

            if (values[0] > 0)
            {
                pinA_.setPinValue(values[0]);
                pinB_.setPinValue(0);
            }
            else
            {
                pinA_.setPinValue(0);
                pinB_.setPinValue(-values[0]);
            }

            return 1;
        }

        bool HBridge2Wire::writeValue(float value)
        {
            if (value > 0)
            {
                pinA_.setPinValue(value);
                pinB_.setPinValue(0);
            }
            else
            {
                pinA_.setPinValue(0);
                pinB_.setPinValue(-value);
            }

            return true;
        }


        // Implementation of HBridge3Wire class
        HBridge3Wire::HBridge3Wire(HAL::PinGPIO &pinA, HAL::PinGPIO &pinB, HAL::PinPWM &pinPWM, float limit) : pinA_(pinA), pinB_(pinB), pwm_(pinPWM), limit_(limit)
        {}

        HAL::IO_TYPE_t HBridge3Wire::getOutputType() const
        {
            return HAL::IO_TYPE_t::ANALOG_HBRIDGE;
        }

        bool HBridge3Wire::setOutputParam(HAL::IO_PARAM_t param, int32_t value)
        {
            switch (param)
            {
            case HAL::IO_PARAM_t::SPEED:
                pwm_.setPinFrequency(value);
                return true;
            default:
                Core::printW("HBridge3Wire::setOutputParam: Parameter not supported. Param given: %d, val %d\n", param, value);
                return false;
            }
        }

        int32_t HBridge3Wire::writable()
        {
            return 1;
        }

        size_t HBridge3Wire::writeValue(const float *values, size_t size)
        {
            if (size < 1)
            {
                return 0;
            }

            writeHBridge(values[0]);

            return 1;
        }

        bool HBridge3Wire::writeValue(float value)
        {
            
            writeHBridge(value);

            return true;
        }

        void HBridge3Wire::writeHBridge(float value)
        {

            if (value > limit_)
            {
                value = limit_;
            }
            else if (value < -limit_)
            {
                value = -limit_;
            }

            if (value > 0)
            {
                pinA_.setPinValue(1);
                pinB_.setPinValue(0);
                pwm_.setPinValue(value);
            }
            else
            {
                pinA_.setPinValue(0);
                pinB_.setPinValue(1);
                pwm_.setPinValue(-value);
            }

            
        }

    } // namespace ACTR for ExVectrActuator

} // namespace VCTR The EXVECTR Library
