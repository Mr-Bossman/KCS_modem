
#define DIAL_TONE 91
#define ANS_MK_2225 15
#define ORG_MK_1270 29


static inline void write_DAC(uint8_t val) {
    PORTB = val & 0x3F;
}

void do_cycle(uint8_t time) {
  #define N 2
  static const uint8_t sin_lut[] = {63,63,63,63,63,62,62,61,61,60,60,59,58,57,56,55,54,53,52,51,50,48,47,46,44,43,41,40,38,37,35,34,32,31,29,28,26,25,23,22,20,19,17,16,15,13,12,11,10,9,8,7,6,5,4,3,3,2,2,1,1,0,0,0};
  for(uint8_t i = 0; i <= 63; i++){
    write_DAC(sin_lut[i]);
    _delay_loop_1(time);
    __builtin_avr_nops(N);
  }
  for(int8_t i = 63; i >= 0; i--){
    write_DAC(sin_lut[i]);
    _delay_loop_1(time);
    __builtin_avr_nops(N);
  }
}


void setup() {
  DDRB = 0x3F;
  pinMode(3, INPUT);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  cli();
  while(1) {
      if(PINC & (1 << 4)) {
        while(!(PIND & (1 << 3)) && (PINC & (1 << 4)))
          do_cycle(DIAL_TONE);
        if(!(PINC & (1 << 4)))
          continue;
        for(uint8_t i = 0; i < 5; i++)
          for(uint8_t j = 0; j < 255; j++)
            do_cycle(DIAL_TONE);
        while(PINC & (1 << 4))
          do_cycle(ANS_MK_2225);
      } else if (!(PINC & (1 << 5))) {
        do_cycle(ORG_MK_1270);
      }
  }
}

void loop() {

}
