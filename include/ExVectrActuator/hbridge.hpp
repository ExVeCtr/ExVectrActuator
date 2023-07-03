#ifndef EXVECTRACTUATOR_HBRIDGE_H_
#define EXVECTRACTUATOR_HBRIDGE_H_

#include "ExVectrHAL/analog_output.hpp"
#include "ExVectrHAL/pin_pwm.hpp"
#include "ExVectrHAL/pin_gpio.hpp"

namespace VCTR
{

    namespace ACTR
    {

        /**
         * @brief This implements an analog output interface for an H-Bridge connected over two PWM pins.
         * @note  Max output will set pin A to 100% and pin B to 0%. Min output will set pin A to 0% and pin B to 100%.
         */
        class HBridge2Wire : public HAL::AnalogOutput
        {
        private:
            HAL::PinPWM &pinA_;
            HAL::PinPWM &pinB_;

        public:
            /**
             * @brief Standard ctor.
             * @param pinA First PWM pin to use.
             * @param pinB Second PWM pin to use.
             */
            HBridge2Wire(HAL::PinPWM &pinA, HAL::PinPWM &pinB);

            /**
             * @brief Gets the type of bus this is.
             * @return IO_TYPE_t enum.
             */
            HAL::IO_TYPE_t getOutputType() const override;

            /**
             * @brief Changes given parameter.
             * @param param What parameter to change.
             * @param value What to change parameter to.
             * @return True if successfull and parameter is supported.
             */
            bool setOutputParam(HAL::IO_PARAM_t param, int32_t value) override;

            /**
             * @returns number of values that can be written at the moment. -1 means no limit to data size.
             */
            int32_t writable() override;

            /**
             * @brief Writes the values from values pointer.
             * @param values Pointer to data.
             * @param size Number of value to output.
             *
             * @return number of values actually written.
             */
            size_t writeValue(const float *values, size_t size) override;

            /**
             * @brief writes a single value.
             * @param value Value to be written to output.
             * @returns true if successfull, false otherwise
             */
            bool writeValue(float value) override;
        };

        /**
         * @brief This implements an analog output interface for an H-Bridge connected over two control pins and one pwm pin.
         * @note  Max output will set pin A to 100% and pin B to 0%. Min output will set pin A to 0% and pin B to 100%.
         */
        class HBridge3Wire : public HAL::AnalogOutput
        {
        private:
            HAL::PinGPIO &pinA_;
            HAL::PinGPIO &pinB_;
            HAL::PinPWM &pwm_;

            float limit_;

        public:
            /**
             * @brief Standard ctor.
             * @param pinA First PWM pin to use.
             * @param pinB Second PWM pin to use.
             * @param pinPWM PWM pin to use.
             * @param limit Maximum output value. Only limits output, does not scale it.
             */
            HBridge3Wire(HAL::PinGPIO &pinA, HAL::PinGPIO &pinB, HAL::PinPWM &pinPWM, float limit = 1.0f);

            /**
             * @brief Gets the type of bus this is.
             * @return IO_TYPE_t enum.
             */
            HAL::IO_TYPE_t getOutputType() const override;

            /**
             * @brief Changes given parameter.
             * @param param What parameter to change.
             * @param value What to change parameter to.
             * @return True if successfull and parameter is supported.
             */
            bool setOutputParam(HAL::IO_PARAM_t param, int32_t value) override;

            /**
             * @returns number of values that can be written at the moment. -1 means no limit to data size.
             */
            int32_t writable() override;

            /**
             * @brief Writes the values from values pointer.
             * @param values Pointer to data.
             * @param size Number of value to output.
             *
             * @return number of values actually written.
             */
            size_t writeValue(const float *values, size_t size) override;

            /**
             * @brief writes a single value.
             * @param value Value to be written to output.
             * @returns true if successfull, false otherwise
             */
            bool writeValue(float value) override;

        private:

            void writeHBridge(float value);

        };

    } // namespace ACTR for ExVectrActuator

} // namespace VCTR The EXVECTR Library

#endif