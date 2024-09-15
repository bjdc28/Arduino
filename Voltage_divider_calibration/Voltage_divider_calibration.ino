double a;
void setup() {
  Serial.begin(9600);

}

void loop() {
  //station 1 - battery
//  a = ((analogRead(A0)/1023.0)*90.86); //0.08873046875 millivolt accuracy
  //station 1 - solar
//  a = ((analogRead(A0)/1023.0)*91.68); //0.08953125 millivolt accuracy
  //station 2 - battery
  a = ((analogRead(A0)/1023.0)*90.86); //0.08873046875 millivolt accuracy
  //station 2 - solar
//  a = ((analogRead(A0)/1023.0)*90.86); //0.08873046875 millivolt accuracy
  Serial.println(a);
  delay(250);
}
