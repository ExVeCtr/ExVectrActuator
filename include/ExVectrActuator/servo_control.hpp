#ifndef EXVECTRACTUATOR_SERVOCONTROL_H_
#define EXVECTRACTUATOR_SERVOCONTROL_H_

#include "ExVectrCore/scheduler2.hpp"
#include "ExVectrCore/task_types.hpp"

#include "ExVectrHAL/pin_pwm.hpp"

#include "ExVectrActuator/pwm_output.hpp"

namespace VCTR
{

    namespace ACTR
    {

        /**
         * @brief   This adds a layer of acceleration and velocity control for servos. Generally use for servos.
         * @note    By limiting the acceleration and velocity of a servo, we reduce its stress when moving large masses,
         *          and assuming the accel and velocities are held by the servo, we get a better estimate of its actual
         *          position.
         */
        class Servo_Control : Core::Task_Periodic
        {
        private:
            // PWM pin to use.
            PWM_Output pwm_;

            float currentPosition_;
            float minPos_, maxPos, maxVel, accel;

        public:
            /**
             * @brief Standard ctor.
             * @note Make sure to check if the used PWM output is even capable of the given PWM protocol e.g software PWM usually cant be used.
             * @param pwmPin Pwm pin to use to output servo pwm signals
             * @param maxPosition The maximum position the servo can reach physically. Usually an angle.
             * @param minPosition The minumum position the servo can reach physically. Usually an angle.
             * @param maxVel The maximum velocity to move the servo at.
             * @param maxAccel The Maximum acceleration to move the servo at.
             * @param pwmProtocol Protocol to use. Defaults to Standard.
             */
            Servo_Control(HAL::PinPWM &pwmPin, float maxPosition, float minPosition, float maxVel, float maxAccel, PWM_Output_Protocol pwmProtocol = PWM_Output_Protocol::STANDARD);

            /**
             * @brief Sets the servo position setpoint ot reach using the given max accel and velocity.
             * @param val Position setpoint.
             */
            void setPosition(float val);

            /**
             * @returns the servo setpoint, not the actual current pwm output value.
             */
            float getAngleSet();

            /**
             * @returns the actual current output value.
             */
            float getAngleReal();
        };

    } // namespace ACTR for ExVectrActuator

} // namespace VCTR The EXVECTR Library

#endif