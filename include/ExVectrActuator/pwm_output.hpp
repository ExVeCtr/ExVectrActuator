#ifndef EXVECTRACTUATOR_PWMOUTPUT_H_
#define EXVECTRACTUATOR_PWMOUTPUT_H_

#include "ExVectrHAL/output.hpp"
#include "ExVectrHAL/pin_pwm.hpp"

namespace VCTR
{

    namespace ACTR
    {

        /**
         * @brief   Different types of pwm outptu protocols. Standard to use for most servos, ESCs often support faster like Multishot.
         * @note    Currently digital protocols like Dshot are not supported due to the high complexity to implement ( AKA I dont have the time :/ )
         *          Setting to a value which the PWM output cannot handle will probably output a warning on runtime.
         */
        enum class PWM_Output_Protocol {
            //1000-2000us, works with all standard servos, ESCs and most outputs can handle this but is slow with 500Hz output rate.
            STANDARD,
            //125-250us, much faster than standard with 4000Hz output rate but probably wont work with standard servos.
            ONESHOT125,
            //42-84us, very fast 11904Hz output rate, wont work with some external PWM output expansion boards.
            ONESHOT42,
            //5-25us, extremely fast 40KHz output rate. Does not amke sense for expansion boards because we cannot update the board pwm at this frequency.
            MULTISHOT
        };

        /**
         * @brief   This class used PWM outputs to generate timed pulses for output to control servos, escs etc.
         * @note    PWM use for servos is not the same for direct DC motor control. DC motor pwm uses the duty cycle (ratio of time on to time off) to control 
         *          the amount of power to a motor. PWM servos use the length of time the signal is on to tranfer the data. E.g. standard uses 1000us on as 0 or
         *          minimum and 2000us on as 1 or maximum, everything between is a different analog value e.g. 1500 is 0.5.
         */
        class PWM_Output {
        private:

            //PWM pin to use.
            HAL::PinPWM& pwmPin_;

            //Used to map the value to the dutycycle needed to achieve correct pulses.
            float offset_ = 0;
            //Used to map the value to the dutycycle needed to achieve correct pulses.
            float factor_ = 0;

            //Current output value.
            float currentValue_ = 0;

        public:

            /**
             * @brief Standard ctor.
             * @note Make sure to check if the used PWM output is even capable of the given PWM protocol e.g software PWM usually cant be used.
             * @param pwmPin Pwm pin to use to output servo pwm signals
             * @param pwmProtocol Protocol to use. Defaults to Standard.
             */
            PWM_Output(HAL::PinPWM& pwmPin, PWM_Output_Protocol pwmProtocol = PWM_Output_Protocol::STANDARD);

            /**
             * @brief Sets the value to output, from 0 to 1.
             * @param val Range 0 to 1.
             */
            void setValue(float val);

            /**
             * @brief Returns the current set output value.
             * @note Remember that most actuators take time to move. A servo wont instantly move from -90 to +90 degrees.
             * @return current value from 0 to 1.
             */
            float getValue();

        };

    } // namespace ACTR for ExVectrActuator

} // namespace VCTR The EXVECTR Library

#endif