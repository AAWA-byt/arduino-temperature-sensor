// define pins for seven segment displays
int D1 = 8;
int D2 = 2;
int D3 = 3;
int D4 = 4;

// define pins for shift register
int dataPin = 5;
int storePin = 6;
int shiftPin = 7;

// define pin for temp360
int temp36 = A0;

// define ints for temperature
int einer;
int zehner;

// define array with decimals for seven segment displays
int temp[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 156, 198};

// define ints for system time
int time;
int time2;

void setup() {
// put your setup code here, to run once:
pinMode(dataPin, OUTPUT);
pinMode(shiftPin, OUTPUT);
pinMode(storePin, OUTPUT);
pinMode(D1, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(D3, OUTPUT);
pinMode(D4, OUTPUT);

}

void loop() {
// put your main code here, to run repeatedly:

// get system time
time = millis();

// get temp
int reading = analogRead(temp36);

// convert into voltage
int voltage = reading * (5000 / 1024.0);

// convert into temperature Celsius
int temperature = (voltage - 500) / 10;

// print temp
Serial.print(temperature);
Serial.print(" °");
Serial.println("C");


// Split temperature in two single numbers
zehner = temperature / 10;
einer = temperature % 10;

// do-while 
do {

    // seven segment display functions
    seven_segment_zehner();
    seven_segment_einer();
    seven_segment_temp_sign();
    seven_segment_celcius_sign();

    // get system time
    time2 = millis();

// after one seccond and do-while loop
} while (time2 - time < 1000 );
}


// function for first display and first temperature number
void seven_segment_zehner() {
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    digitalWrite(storePin, LOW);
    shiftOut(dataPin, shiftPin, LSBFIRST, temp[zehner]);
    digitalWrite(storePin, HIGH);
    delay(5);
}

// function for seccond display and seccond temperature number
void seven_segment_einer() {
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    digitalWrite(storePin, LOW);
    shiftOut(dataPin, shiftPin, LSBFIRST, temp[einer]);
    digitalWrite(storePin, HIGH);
    delay(5);
}

// function for third display and temperature sign
void seven_segment_temp_sign() {
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
    digitalWrite(storePin, LOW);
    shiftOut(dataPin, shiftPin, LSBFIRST, 156);
    digitalWrite(storePin, HIGH);
    delay(5);
}

// function for fourth display and celcius sign
void seven_segment_celcius_sign() {
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
    digitalWrite(storePin, LOW);
    shiftOut(dataPin, shiftPin, LSBFIRST, 198);
    digitalWrite(storePin, HIGH);
    delay(5);
}