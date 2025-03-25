
/* M2X10A Example
 * Board: Arduino UNO
 */

// Pin definitions
#define M2X10A_STBY_PIN 2
#define M2X10A_INVA_PIN 3
#define M2X10A_INVB_PIN 4
#define M2X10A_DIRA_PIN 5
#define M2X10A_DIRB_PIN 6
#define M2X10A_PWMA_PIN 9
#define M2X10A_PWMB_PIN 10

/* M2X10A Driver intialisation function
 * Configures controller pins, and enables driver.
 */
void M2X10A_Init()
{
  //Configure pins
  pinMode(M2X10A_STBY_PIN, OUTPUT);
  pinMode(M2X10A_INVA_PIN, OUTPUT);
  pinMode(M2X10A_INVB_PIN, OUTPUT);
  pinMode(M2X10A_DIRA_PIN, OUTPUT);
  pinMode(M2X10A_DIRB_PIN, OUTPUT);
  pinMode(M2X10A_PWMA_PIN, OUTPUT);
  pinMode(M2X10A_PWMB_PIN, OUTPUT);

  /* Configure driver PWM mode
   * Set INV pins to 0 to enable active braking.
   */
  digitalWrite(M2X10A_INVA_PIN, 1);
  digitalWrite(M2X10A_INVB_PIN, 1);

  //Enable driver
  digitalWrite(M2X10A_STBY_PIN, 1);
}

/* M2X10A Driver pwm control function
 * pwmA and pwmB should be between -255 and 255.
 * Negative pwm turns the motor in reverse.
 */
void M2X10A_SetPWM(int pwmA, int pwmB)
{
  if (pwmA > 255) pwmA = 255;
  else if (pwmA < -255) pwmA = -255;

  if (pwmA < 0)
  {
    analogWrite(M2X10A_PWMA_PIN, -pwmA);
    digitalWrite(M2X10A_DIRA_PIN, 1);
  }
  else
  {
    analogWrite(M2X10A_PWMA_PIN, pwmA);
    digitalWrite(M2X10A_DIRA_PIN, 0);
  }

  if (pwmB > 255) pwmB = 255;
  else if (pwmB < -255) pwmB = -255;

  if (pwmB < 0)
  {
    analogWrite(M2X10A_PWMB_PIN, -pwmB);
    digitalWrite(M2X10A_DIRB_PIN, 1);
  }
  else
  {
    analogWrite(M2X10A_PWMB_PIN, pwmB);
    digitalWrite(M2X10A_DIRB_PIN, 0);
  }
}

void setup() {
  M2X10A_Init();
}

void loop() {
  /* Ramp up both motors from 0 to +255,
   * then back to 0, then to -255 and back to 0.
   */

  for (int i = 0; i < 255; i++)
  {
    M2X10A_SetPWM(i,i);
    delay(20);
  }

  for (int i = 255; i > 0; i--)
  {
    M2X10A_SetPWM(i,i);
    delay(20);
  }

  for (int i = 0; i > -255; i--)
  {
    M2X10A_SetPWM(i,i);
    delay(20);
  }

  for (int i = -255; i < 0; i++)
  {
    M2X10A_SetPWM(i,i);
    delay(20);
  }
}
