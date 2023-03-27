/** User debugging parameters**/
boolean _debug = true;

float u1;  // First  user debug variable
float u2;  // Second user debug variable
float u3;  // Third  user debug variable

 float error;       // Temperature error relative to setpoint 
 float E;
 float I=0;
 float outDAC;

void control(){
  
  /*
   * This is the control function used to change the voltage 
   * applied to the peltier. 
   * 
   * Calculations of the control function are based on the current setpoint and  
   * most recently measured temperature.
   */
    
 error = temperature - setpoint ;
 E = -1*error/band ; 
 I += 1/t_integral * E * dt/1000 ;


  // COOLING
  //if (error >= band/2) {
  //  set_dac(-4095);
  //} 
  //else if (error < -1*band/2) {
  //  set_dac(0);
  //}

  // HEATING (On-Off Control - 4.2)
  //if (error >= band/2) {
  //  set_dac(-4095);
  //} 
  //else if (error < -1*band/2) {
  //  set_dac(4095);
  //}
  //}

  //outDAC = 2*E*4095;
  // Proportional Control - 4.3
  //if (error > band/2) {
  //  set_dac(-4095);
  //} 
  //else if (error < -1*band/2) {
  //  set_dac(4095);
  //}
  //else {
  //  set_dac(outDAC);
  //}

  // Proportional-Integral Control - 4.4
  if (error > band/2) {
    I = 0 ;
    set_dac(-4095);
  } 
  else if (error < -1*band/2) {
    I = 0 ;
    set_dac(4095);
  }
  else {
    I += 1/t_integral * E * dt/1000 ;
    outDAC = (2*E+I)*4095;
    set_dac(outDAC);
  }











  
}
