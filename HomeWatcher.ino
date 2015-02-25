const int GAS_MAX_VAL = 500;
const int MOVE_MAX_VAL = 500;
const unsigned long SECURITY_DELAY_TIME = 3 * 60 * 1000;

const unsigned long BLINK_DELAY_TIME = 1000;
const unsigned long CHECK_DELAY_TIME = 100;

const int pinBtnReset = 2;
const int pinBtnSecurity = 4;
const int pinBtnAlarm = 3;

const int pinLedAlarm = 9;
const int pinLedGas = 8;

const int pinAnalogGas = 0;
const int pinAnalogMoveSensor = 1;

enum DEV_STATE {
	REGULAR = 0, SECURITY, WARNING, ALARM
};

int mCurentState = REGULAR;

bool mBtnReset = false;
bool mBtnSecurity = false;
bool mBtnAlarm = false;

int mSenGas = 0;
int mSenMove = 0;

void setup() {

	Serial.begin(9600);
	pinMode(pinLedAlarm, OUTPUT);
	pinMode(pinLedGas, OUTPUT);

	pinMode(pinBtnReset, INPUT);
	pinMode(pinBtnSecurity, INPUT);
	pinMode(pinBtnAlarm, OUTPUT);
}

void readData() {
	mBtnReset = digitalRead(pinBtnReset) != 0;
	mBtnSecurity = digitalRead(pinBtnSecurity) != 0;
	mBtnAlarm = digitalRead(pinBtnAlarm) != 0;

	mSenGas = analogRead(pinAnalogGas);

        Serial.print("mBtnReset = ");
	Serial.println(mBtnReset);

        Serial.print("mBtnSecurity = ");
	Serial.println(mBtnSecurity);

        Serial.print("mBtnAlarm = ");
	Serial.println(mBtnAlarm);

        Serial.print("Gas = ");
	Serial.println(mSenGas);
}

void ResetLeds() {
	digitalWrite(pinLedAlarm, LOW);
	digitalWrite(pinLedGas, LOW);
}

bool ResetDelay(unsigned long mSec) {

	for (int i = 0; i < mSec / CHECK_DELAY_TIME; i++) {
		if (digitalRead(pinBtnReset) != 0) {
			Serial.println("Reset bu user");
			return true;
		}
		delay(CHECK_DELAY_TIME);
	}
	return false;
}

bool BlinkLed(int led, int nTimes) {
	for (int i = 0; i < nTimes; i++) {
		Serial.print("BlinkLed ");
		Serial.println(i);
		digitalWrite(led, HIGH);
		if (ResetDelay(BLINK_DELAY_TIME)) {
			return false;
		}
		digitalWrite(led, LOW);
		if (ResetDelay(BLINK_DELAY_TIME)) {
			return false;
		}
	}
	return true;
}

void loop() {
        Serial.println("*******************************");
	readData();
	Serial.println(mCurentState);
  
	if (mBtnAlarm) {
		mCurentState = ALARM;
		Serial.println("ALARM");
	}

	if (mBtnSecurity) {
		mCurentState = SECURITY;

		if (BlinkLed(pinLedAlarm, 5) != false) {
			Serial.print("SECURITY delay: ");
			Serial.println(SECURITY_DELAY_TIME, DEC);
			ResetDelay(SECURITY_DELAY_TIME);
          	digitalWrite(pinLedAlarm, HIGH);
		} else {
			Serial.print("SECURITY reset by user");
		}
	}

	if (mBtnReset) {
		mCurentState = REGULAR;
		ResetLeds();
		Serial.println("REGULAR");

	}

	if (mSenGas > GAS_MAX_VAL) {
		mCurentState = ALARM;
		digitalWrite(pinLedGas, HIGH);
		Serial.println("ALARM");
	}

	switch (mCurentState) {
	case REGULAR:

		break;
	case WARNING:
		break;
	case SECURITY:
		mSenMove = analogRead(pinAnalogMoveSensor);
		if (mSenMove < MOVE_MAX_VAL) {
			Serial.println("mSenMove < MOVE_MAX_VAL");
          
          if (BlinkLed(pinLedAlarm, 10) == true) {
			mCurentState = ALARM;
		} 
			
		}
		break;
	case ALARM:
		digitalWrite(pinLedAlarm, HIGH);
		break;
	default:
		Serial.println("Unknown state");
		break;
	}
}
