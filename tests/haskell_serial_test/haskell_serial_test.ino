static int test_running;
static uint8_t expected_char;

static const uint8_t lowest_expected_char  = 0x61;  //was 0x00
static const uint8_t highest_expected_char = 0xff;

// the setup routine runs once when you press reset:
void setup()
{
  // initialize the digital pin as an output.
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}


void ConsumeAllSerial()
{
  while ( Serial.available() )
    Serial.read();
}


// the loop routine runs over and over again forever:
void loop()
{
  if ( Serial.available() )
  {
    int i = Serial.read();
    switch (i)
    {
      case 'a':
        Serial.write(i);
        Serial.end();
        Serial.begin(1200);
        ConsumeAllSerial();
        test_running = 1;
        expected_char = lowest_expected_char;
        break;
      case 'b':
        Serial.write(i);
        Serial.end();
        Serial.begin(2400);
        ConsumeAllSerial();
        test_running = 1;
        expected_char = lowest_expected_char;
        break;
      case 'c':
        Serial.write(i);
        Serial.end();
        Serial.begin(4800);
        ConsumeAllSerial();
        test_running = 1;
        expected_char = lowest_expected_char;
        break;
      case 'd':
        Serial.write(i);
        Serial.end();
        Serial.begin(9600);
        ConsumeAllSerial();
        test_running = 1;
        expected_char = lowest_expected_char;
        break;
      case 'e':
        Serial.write(i);
        Serial.end();
        Serial.begin(19200);
        ConsumeAllSerial();
        test_running = 1;
        expected_char = lowest_expected_char;
        break;
      case 'f':
        Serial.write(i);
        Serial.end();
        Serial.begin(57600);
        ConsumeAllSerial();
        test_running = 1;
        expected_char = lowest_expected_char;
        break;
      case 'g':
        Serial.write(i);
        Serial.end();
        Serial.begin(115200);
        ConsumeAllSerial();
        test_running = 1;
        expected_char = lowest_expected_char;
        break;
      case 'h':
        Serial.write(i);
        Serial.end();
        Serial.begin(9600);
        ConsumeAllSerial();
        test_running = 2;
        break;
    }
  }

  if ( test_running == 1 )
  {
    while ( Serial.available() )
    {
      uint8_t i = Serial.read() & 0xff;
      if ( i == expected_char)
      {
        Serial.write(expected_char);
        if ( expected_char == highest_expected_char )
        {
          // test successfull
          Serial.println("ok");
          Serial.flush();
          Serial.end();
          test_running = 0;
        }
        else
          expected_char++;
      }
      else
      {
        Serial.print("expected char('");
        Serial.print(expected_char, HEX);
        Serial.print("') got ('");
        Serial.print(i, HEX);
        Serial.println("') test failed");
      }
    }
  }
  else if ( test_running == 2 )
  {
    while ( Serial.available() )
    {
      uint8_t i = Serial.read() & 0xff;
      switch ( i )
      {
        case 'a':
          Serial.write('a');
          Serial.write('A');
          break;
        case 'b':
          Serial.write('b');
          delay(50);
          Serial.write('B');
          break;
        case 'c':
          Serial.write('c');
          delay(150);
          Serial.write('C');
          break;
        case 'd':
          Serial.write('d');
          delay(200);
          Serial.write('D');
          break;
        case 'e':
          // 50 ms delay
          delay(500);
          Serial.write('E');
          break;
        default:
          test_running = 0;
          break;
      }
    }
  }
}

