#include <chrono>
#include <iostream>
#include "PID.h"

using namespace std;
using namespace std::chrono;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  this->previousCTE = 0.0;
}

void PID::UpdateError(double cte) {


}

double PID::TotalError() {

}

double PID::steeringAngle(double cte) {

  double diff_cte = 0;
  //long long int diff_time = 0;
  if(previousTimestamp == 0) {

      previousTimestamp = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
      ).count();
      previousCTE = cte;
      diff_cte = 0.0;
  } else {

    auto now = duration_cast< milliseconds >(
      system_clock::now().time_since_epoch()
    ).count();

    //diff_time = now - previousTimestamp;
    diff_cte = cte - previousCTE; //1000 * (cte - previousCTE) / diff_time;
    this->sumCTE = this-> sumCTE + cte; // * diff_time / 1000;

    //previousTimestamp = now;

  }

  auto p_part = -Kp*cte;
  auto d_part = -Kd*diff_cte;
  auto i_part = -Ki*sumCTE;
  std::cout << "P_PART: " << p_part << endl;
  std::cout << "D_PART: " << d_part << endl;
  std::cout << "I_PART: " << i_part << endl;
  //std::cout << "\tt_diff: " << diff_time << endl;
  std::cout << "\tSum CTE: " << sumCTE << endl;
  auto steering = p_part + d_part + i_part;
  if(steering < -1.0) {
    return -1.0;
  }
  if(steering > 1.0) {
    return 1.0;
  }
  return steering;
}

