double sensor_values[11];
double val_1,val_2,val_3,val_4,val_5,val_6,val_7,val_8,val_9;

void setup()
{
  Serial.begin(9600); //Start serial
  
  // Generate 3 random numbers between -100 and +100
  
  
}

void loop(){
  val_1 = random(20,40); 
  val_2 = random(20,29);
  val_3 = random(1,5);
  val_4 = random(30,40);
  val_5 = random(25,29);
  val_6 = random(5,10);
  val_7 = random(0,2);
  val_8 = random(0,2);
  val_9 = random(0,2);


//  if(val_1 >= 40){
//    val_1 = 0;
//  }
//  else{
//    val_1++;
//  }
//  
//  if(val_2 >= 40){
//    val_2 = 0;
//  }
//  else{
//    val_2++;
//  }

  
  // Assign the values to array
  sensor_values[0] = val_1;
  sensor_values[1] = val_2;
  sensor_values[2] = val_3;
  sensor_values[3] = val_4;
  sensor_values[4] = val_5;
  sensor_values[5] = val_6;
  sensor_values[6] = val_7;
  sensor_values[7] = val_8;
  sensor_values[8] = val_9;
  
  //call the write sensor values function to write the values to serial port
  writeSensorValues(sensor_values);
  delay(500);
}

//Method that will write the values to the serial port
void writeSensorValues(double values [])
{
  
  for(int i = 0 ; i < 10 ; i++){
    Serial.print(values[i]);
    Serial.print(","); // Seperate each value with ',' to identify them seperately
  }
  Serial.println("");
}
