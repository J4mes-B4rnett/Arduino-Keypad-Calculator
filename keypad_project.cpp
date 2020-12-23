#include <Keypad.h>

const byte ROWS = 4;
const byte COLM = 4;

char keys[ROWS][COLM] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 11, 10};
byte colmPins[COLM] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colmPins, ROWS, COLM);

float inputs[2];
bool inputs_entered[2];
bool inputs_displayed[2];

char arithmetic_op;
bool arithmetic_op_entered = false;
bool arithmetic_op_displayed = false;

void setup() {
  Serial.begin(9600);
  
  ResetValues();
  Calculator();
}

void loop() {}

void ResetValues()
{
  for (int i = 0; i < 2; i++)
  {
    inputs_entered[i] = false;
    inputs_displayed[i] = false;

    inputs[i] = 0;
  }
  
  arithmetic_op = NULL;
  arithmetic_op_entered = false;
  arithmetic_op_displayed = false;
}

void Calculator()
{
  ResetValues();
  
  GetInputs();
  GetOperator();

  switch(arithmetic_op){
    case 'A':
      Serial.println(inputs[0] + inputs[1]);
      break;
    case 'B':
      Serial.println(inputs[0] - inputs[1]);
      break;
    case 'C':
      Serial.println(inputs[0] * inputs[1]);
      break;
    case 'D':
      Serial.println(inputs[0] / inputs[1]);
      break;
  }

  delay(100);
  Serial.flush();
  Calculator();
}

void GetInputs()
{
  while (!inputs_entered[0]){
    for (int i = 0; i < 2; i++)
    {
      if (!inputs_entered[i] && !inputs_displayed[i])
      {
        Serial.println("Input " + String(i) + ": ");
        inputs_displayed[i] = true;
    
        while (!inputs_entered[i])
        {
          char customKey = keypad.getKey();
          if (customKey != NO_KEY)
          {
            customKey = convertValues(customKey);
            inputs[i] = customKey;
            Serial.println(inputs[i]);
            inputs_entered[i] = true;
          }
        }
      }
    }
  }
}

void GetOperator()
{
  while (!arithmetic_op_entered){
    if (!arithmetic_op_entered && !arithmetic_op_displayed)
    {
      Serial.println("Arithmetic Operator: ");
      arithmetic_op_displayed = true;
    
      while (!arithmetic_op_entered)
      {
        char customKey = keypad.getKey();
        if (customKey != NO_KEY)
        {
          arithmetic_op = customKey;
          Serial.println(keypad.getKey());
          arithmetic_op_entered = true;
        }
      }
    }
  }
}

int convertValues(int x)
{
  return x - '0';
}
