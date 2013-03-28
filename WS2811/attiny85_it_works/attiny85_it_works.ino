// Where the WS2811 is attached (pin B4)
#define LED_BIT (1<<1)
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN PINB
#define NOP __asm__("nop\n\t")

class WS2811 {
public:
  static void init() {
    LED_PORT &= ~LED_BIT;
    LED_DDR |= LED_BIT;
  }
};
WS2811 ws2811;


// A single LED in the string
class LED {
  byte r_,g_,b_;
  static void sendByte(byte b) {
    byte mask = 0x80;
    while (mask!=0) {
      if ((b&mask)==0) {
        // Send a '0'
        LED_PIN = LED_BIT;  // Hi (start)
        NOP;                // Hi
        LED_PIN = LED_BIT;  // Lo (250ns)
        NOP;                // Lo
        NOP;                // Lo (500ns)
        NOP;                // Lo (data bit here!)
        NOP;                // Lo (750ns)
        NOP;                // Lo (875ns)
      }
      else {
        // Send a '1'
        LED_PIN = LED_BIT;  // Hi (start)
        NOP;                // Hi
        NOP;                // Hi (250ns)
        NOP;                // Hi
        NOP;                // Hi (500ns)
        NOP;                // Hi (data bit here!)
        NOP;                // Hi (750ns)
        LED_PIN = LED_BIT;  // Lo (875ns)
      }
      mask >>= 1;           // Lo (1000ns)
    }
  }
public:
  // Set my color
  LED& setColor(byte r, byte g, byte b) {
    r_ = r;
    g_ = g;
    b_ = b;
  }
  // Send me to the LED
  void send() const {
    cli();   // Interrupts have to be off while we do this as they cause timing glitches
    sendByte(g_);
    sendByte(b_);
    sendByte(r_);
    sei();
  }
};

LED led;

long onOff = 0;

void setup()
{
  ws2811.init();
}

void loop()
{
  if((millis() - onOff) < 500) {
  run(0,0,255);
  }
  if((millis() - onOff) > 500 && (millis() - onOff) < 1000) {
    run(0,0,0); }
if(millis() - onOff > 1000) {
      onOff = millis(); }
}

void run(int b, int g, int r) {
  led.setColor(b,g,r);
  led.send();
  led.setColor(b,g,r);
  led.send();
  led.setColor(b,g,r);
  led.send();
  led.setColor(b,g,r);
  led.send();
    led.setColor(b,g,r);
  led.send();
  led.setColor(b,g,r);
  led.send();
  led.setColor(b,g,r);
  led.send();
  led.setColor(b,g,r);
  led.send();
  led.setColor(b,g,r);
  led.send();
  delay(50);
}


