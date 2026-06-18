const int rot_enc_SW_pin = 25; // ARDUINO D5
const int rot_enc_CLK_pin = 26; // ARDUINO D4
const int rot_enc_DT_pin = 27; // ARDUINO D3

bool previous_CLK_state;
bool previous_SW_state;


int direction_identifier()
{
  int result = 0;
  bool current_CLK_state = digitalRead(rot_enc_CLK_pin);
  bool current_DT_state = digitalRead(rot_enc_DT_pin);

  if(current_CLK_state != previous_CLK_state && current_CLK_state == HIGH)
  {
    if(current_DT_state == LOW)
    {
      result = 1;//Serial.println("ClockWise Rotation");
    }
    else
    {
      result = -1;//Serial.println("AntiClockWise Rotation");
    }
  }

  previous_CLK_state = current_CLK_state;
  return result;

}

bool press_state_identifier()
{
  bool current_SW_state = digitalRead(rot_enc_SW_pin);
  int result = LOW;

  if(current_SW_state != previous_SW_state && current_SW_state == HIGH)
  {
    result = HIGH;
  }

  previous_SW_state = current_SW_state;

  return result;
}

void rotary_encoder_debugger_func()
{
  static int previous_direction = 0;
  int current_direction = direction_identifier();
  bool is_pressed = press_state_identifier();

//
  if(previous_direction != current_direction)
  {
    if(current_direction != 0)
    {
      Serial.print("|| Changing direction ||");
    }
  }
  else 
  {
    if(current_direction != 0)
    {
      Serial.print("|| On the same direction ||");
    }
  }

//
  if(current_direction == 1)
  {
    Serial.print("|| ClockWise Rotation ||");
  }
  else if(current_direction == -1)
  {
    Serial.print("|| Anti-ClockWise Rotation ||");
  }
  else
  {
    Serial.print("|| Stale (no-rotation) ||");
  }  
//
  if(is_pressed == HIGH)
  {
     Serial.println("|| Pressed! ||");
  }
  else
  {
    Serial.println("Not Pressed");
  }


//
  previous_direction = current_direction;
} 


void displaying_rotary_encoder_debugger_func()
{
  static unsigned long int last_time = 0;
  unsigned long int current_time = micros();

  if(current_time - last_time >= 50000) // 50000 microseconds = 50 millisecond
  {
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    rotary_encoder_debugger_func();
    last_time = current_time;
    Serial.println("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
  }
}


void setup()
{
  pinMode(rot_enc_SW_pin ,INPUT_PULLDOWN);
  pinMode(rot_enc_CLK_pin ,INPUT_PULLDOWN);
  pinMode(rot_enc_DT_pin ,INPUT_PULLDOWN);

  Serial.begin(115200); //ARDUINO 9600
  previous_CLK_state = digitalRead(rot_enc_CLK_pin);
  previous_SW_state = digitalRead(rot_enc_SW_pin);
}

void loop()
{
  displaying_rotary_encoder_debugger_func();
}

