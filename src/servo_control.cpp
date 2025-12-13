#include "ExVectrCore/time_definitions.hpp"
#include "ExVectrCore/scheduler2.hpp"
#include "ExVectrCore/task_types.hpp"

#include "ExVectrHAL/digital_output.hpp"
#include "ExVectrHAL/pin_pwm.hpp"

#include "ExVectrActuator/pwm_output.hpp"
#include "ExVectrActuator/servo_control.hpp"

namespace VCTR
{

    namespace ACTR
    {

        Servo_Control::Servo_Control(float maxPosition, float minPosition, float maxVel, float maxAccel, HAL::PinPWM &pwmPin, PWM_Output_Protocol pwmProtocol):
            Task_Periodic("Servo Control", 20*Core::MILLISECONDS),
            pwm_(pwmPin, pwmProtocol)
        {
            maxPos_ = maxPosition;
            minPos_ = minPosition;
            maxVel_ = maxVel;
            accel_ = maxAccel;

            currentPosition_ = 0.0f; // Start at 0 degrees
            targetPosition_ = 0.0f; // Start at 0 degrees

            pwm_.enableOutput(true);

            Core::getSystemScheduler().addTask(*this); // Attach to the scheduler
        }

        void Servo_Control::setPosition(float val)
        {
            targetPosition_ = val;
            if (targetPosition_ > maxPos_) targetPosition_ = maxPos_;
            else if (targetPosition_ < minPos_) targetPosition_ = minPos_;
        }

        float Servo_Control::getAngleSet()
        {
            return targetPosition_;
        }

        float Servo_Control::getAngleReal()
        {
            return currentPosition_;
        }

        void Servo_Control::taskThread() 
        {
            // Simulate the servo movement using a simple physics model and set the PWM output accordingly
            float dTime = (Core::NOW() - lastUpdate_) / Core::SECONDS;
            lastUpdate_ = Core::NOW();
            float dHTS = 0.5 * dTime *dTime;

            // Calculate the current servo position based on the current velocity and acceleration
            currentPosition_ += currentVelocity_ * dTime + dHTS * accel_;
            currentVelocity_ += accel_ * dTime;

            //Calculate the required acceleration to reach the target position
            float deltaPos = targetPosition_ - currentPosition_;
            float requiredAccel = deltaPos / dTime - currentVelocity_ / dTime;
            if (requiredAccel > accel_) requiredAccel = accel_;
            else if (requiredAccel < -accel_) requiredAccel = -accel_;
            accel_ = requiredAccel;

            // update the servo output. An output value of 1 is max rotation, 0 is min rotation.
            auto output = (currentPosition_ - minPos_) / (maxPos_ - minPos_);
            pwm_.setValue(output); // Assuming the servo is controlled by a PWM signal between 0 and 1000


        }

    }
}
