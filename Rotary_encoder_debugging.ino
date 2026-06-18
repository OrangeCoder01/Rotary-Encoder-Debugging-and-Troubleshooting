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

int press_state_identifier()
{
  bool current_SW_state = digitalRead(rot_enc_SW_pin);
  int result = 0;

  if(current_SW_state != previous_SW_state && current_SW_state == HIGH)
  {
    result = 1;
  }

  previous_SW_state = current_SW_state;

  return result;
}

void rotary_encoder_debugger_func()
{
  static int previous_direction = 0;
  int current_direction = direction_identifier();
  bool is_pressed = press_state_identifier();
  //Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");


//
  if(previous_direction != current_direction)
  {
    Serial.print("|| Changing direction ||");
  }
  else 
  {
    Serial.print("|| On the same direction ||");
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

void setup()
{
  pinMode(rot_enc_SW_pin ,INPUT_PULLUP);
  pinMode(rot_enc_CLK_pin ,INPUT_PULLUP);
  pinMode(rot_enc_DT_pin ,INPUT_PULLUP);

  Serial.begin(115200); //ARDUINO 9600
  previous_CLK_state = digitalRead(rot_enc_CLK_pin);
  previous_SW_state = digitalRead(rot_enc_SW_pin);
}

void loop()
{
  rotary_encoder_debugger_func();
}

