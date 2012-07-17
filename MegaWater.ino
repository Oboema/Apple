#define OPEN 1
#define CLOSE 0

int waterTime = 6000;//ammount of time that the valve is open for each RING in ms, the time between two RINGs is 5000ms  
long closeTime = 0; //the time on which the valve closes, this value will be changed when someone calls.

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int valve = 2;

void setup() {
  // initialize serial:
  pinMode(valve,OUTPUT);
  
  digitalWrite(valve,LOW);
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial3.write("at");
  Serial.write("communication has started\r\n");
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  if(closeTime>millis()){
    digitalWrite(valve,OPEN);
  }
  else{
    digitalWrite(valve,CLOSE);
  }
  
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.println(inputString); 
    action(inputString);
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
void serialEvent3() {
  while (Serial3.available()) {
    // get the new byte:
    char inChar = (char)Serial3.read(); 
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
   Serial.print("nieuw bericht");
   Serial.print(input);
      
   
   
   
   
     if(input=="RING\r"){
       if(closeTime<=millis()){ //if the current time passed the close time
         closeTime=millis()+waterTime;
       }
       else{  //now the close time lies in the future
         closeTime+=waterTime;
       }
     Serial.print("het is een ring!!!!!!\n");Serial.print(millis());
   }
  
  return;
}
