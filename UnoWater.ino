#define OPEN 1
#define CLOSE 0

int waterTime = 6000;//amount of time that the valve is open for each RING in ms, the time between two RINGs is 5000ms so it's recommended to keep this value above 5000ms
long closeTime = 0; //the time on which the valve closes, this value will be changed when someone calls.

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int valve = 2;

void setup() {
  // initialize serial:
  pinMode(valve,OUTPUT);
  //digitalWrite(valve,HIGH);
  //delay(400);   //unlock this if you want to do a valve test at startup
  digitalWrite(valve,LOW);
  Serial.begin(9600);
  Serial.write("at");
  //  Serial.write("communication has started\r\n");
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  if(closeTime>millis()){  //if the close time is in the future, the valve should de open, otherwise is should be closed
    digitalWrite(valve,OPEN);
  }
  else{
    digitalWrite(valve,CLOSE);
  }
  
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.println(inputString); 
    action(inputString);  //this is were everything happens
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    
    char inChar = (char)Serial.read(); 
    //Serial.print(inChar);
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n' || inChar == '\r' ) {
      stringComplete = true;
    } 
  }
}

void action(String input){
   //Serial.print("nieuw bericht");
   //Serial.print(input);  
   
     if(input=="RING\r"){   //if someone calls
       
       //Serial.print("jaaa! een ring");
       if(closeTime<=millis()){ //if the current time passed the close time
         closeTime=millis()+waterTime; //the valve will close waterTime from now
       }
       else{  //now the close time lies in the future
         closeTime+=waterTime; //the watertime wil be added to the close time
       }
     //Serial.print("het is een ring!!!!!!\n");Serial.print(millis());
   }
  
  return;
}
