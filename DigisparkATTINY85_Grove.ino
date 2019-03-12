// Setup Variables
const int grovePin = 2;
const int redLED = 4;
const int greenLED = 1;
const int blueLED = 0;

unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;//sampe 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

// int redValue = 0; // value to write to the red LED
// int greenValue = 0; // value to write to the green LED
// int blueValue = 0; // value to write to the blue LED

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

void setup() {
  // put your setup code here, to run once:
  
  // Initialize D2 as Analog In
  pinMode(grovePin, INPUT); //Anolog Pin for Grove Sensor

  // Pins for the RGB LED
  // Initialize Pin 4 (PWM) for RED
  pinMode(redLED, OUTPUT);   

  // Initialize Pin 1 (PWM) for Green
  pinMode(greenLED, OUTPUT);   

  // Initialize Pin 0 (PWM) for Blue
  pinMode(blueLED, OUTPUT);   

  // Blink 
  setColor(255, 255, 255);  // white
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 0);  // Off
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  duration = pulseIn(grovePin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
    
 if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
    {
        ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
        concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
  

        // Change LED colour based on Concentration Values
        // High Dust Concentration Over 20K
        if (concentration >= 10000)
        {
            // Set Colour to RED
            setColor(255, 0, 0);
        }


        else if (concentration >= 3000 && concentration < 10000)
        {
            // Set Colour to ORANGE
            setColor(255, 127, 0);
        }

        else if (concentration >= 1000 && concentration < 3000)
        {
            // Set Colour to YELLOW
            setColor(255, 255, 0);
        }


        else if (concentration >= 500 && concentration < 1000)
        {
            // Set Colour to GREEN
            setColor(0, 255, 0);
        }

        else
        {
            // Set Colour to Blue
            setColor(0, 0, 255);
        }
    }  
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redLED, red);
  analogWrite(greenLED, green);
  analogWrite(blueLED, blue);  
}
