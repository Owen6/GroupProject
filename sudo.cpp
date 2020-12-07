Loop{
  if(button on){
    if(water level ok & temp < threshold){
      idle state
    }
    blue LED on
    ajust angle of vent based on change of input
    check temp and humidity;
    diplay temp and humidity to LCD Screen
    if temp > threshold {
      start fan;
      record time;
      running state;
    }else {
      stop fan;
      record time;
    }
    if( water too low){
        error state
    }
    check to adjust the vent from input
  }else{
    turn motor off
    disabled state
    yellow led
  }
}