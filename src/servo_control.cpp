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

        Servo_Control::Servo_Control(HAL::PinPWM &pwmPin, float maxPosition, float minPosition, float maxVel, float maxAccel, PWM_Output_Protocol pwmProtocol):
            Task_Periodic("Servo Control", 20*Core::MILLISECONDS),
            pwm_(pwmPin, pwmProtocol)
        {
            
        }

        void Servo_Control::setPosition(float val)
        {
        }

        float Servo_Control::getAngleSet()
        {
        }

        float Servo_Control::getAngleReal()
        {
        }

    }
}
