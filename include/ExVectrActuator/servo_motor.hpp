#ifndef EXVECTRACTUATOR_SERVOMOTOR_H_
#define EXVECTRACTUATOR_SERVOMOTOR_H_

#include "ExVectrMath.hpp"

#include "ExVectrHAL/analog_output.hpp"

#include "ExVectrActuator/hbridge.hpp"

#include "ExVectrSensor/encoder.hpp"

namespace VCTR
{

    namespace ACTR
    {

        /**
         * @brief A servo motor is a motor with the ability to rotate to a specific angle and a specific speed.
         */
        class ServoMotor
        {
        public:
            /**
             * @brief Function to get the current state of the motor.
             * @returns The current state of the motor. First value is the angle, second is the speed.
             */
            virtual const Math::Vector<float, 2>& getServoState() const = 0;

            /**
             * @brief Function to set the current state of the motor.
             * @param state The state to set the motor to. First value is the angle, second is the speed.
             */
            virtual void setServoState(const Math::Vector<float, 2> &state) = 0;
        };

    } // namespace ACTR for ExVectrActuator

} // namespace VCTR The EXVECTR Library

#endif