#include <Keyboard.h>

class Switch{
  private:
  int port;
  int state;
  bool def = false;
  
  public:

  char* on;
  int on_length;
  char* off;
  int off_length;
  //on = new char[2]{"1", "2"};
  long type;
  long lastRunMils = 0;
  //0=SingleFire, 1=HoldKey, 2=Toggle, 3=RepeatNoDelay, 4+=RepeatWithDelay

  Switch(int port){
    this->port = port;
    pinMode(port, INPUT_PULLUP);
    state = digitalRead(port);
  }

  void defFunction(char* on, int on_length, char* off, int off_length, long type){
    this->on = on;
    this->on_length = on_length;
    this->off = off;
    this->off_length = off_length;
    this->type = type;
    def = true;
  }

  void update(long mils){
    if(!def){
      return;
    }
    
    switch(type){
      case 0:
        if(updateState()){
          if(state == LOW){
            runKeys(on, on_length);
          }
        }
        break;
      case 1:
        if(updateState()){
          if(state == LOW){
            Keyboard.press(on[0]);
          } else if(state ==  HIGH){
            Keyboard.release(on[0]);
          }
        }
        break;
      case 2:
         if(updateState()){
           if(state == LOW){
             runKeys(on, off_length);
           } else if(state == HIGH){
             runKeys(off, off_length);
           }
        }
        break;
      case 3:
        updateState();
        if(state == LOW){
          runKeys(on, on_length);
        } else if(state == HIGH){
          runKeys(off, off_length);
        }
        break;
      default:
        if(updateState()){
          lastRunMils = mils - type;
        }

        if(mils - type >= 0){
          if(state == LOW){
            runKeys(on, on_length);
          } else if(state == HIGH){
            runKeys(off, off_length);
          }
        }
        break;
    }
  }

  bool updateState(){
    if(digitalRead(port) != state){
      state = digitalRead(port);
      return true;
    } else {
      return false;
    }
  }

  void runKeys(char* keyset, int size){
    for(int i = 0; i < size; i++){
      Keyboard.press(keyset[i]);
    }
    delay(30);
    for(int i = 0; i < size; i++){
      Keyboard.release(keyset[i]);
    }
  }

  
};


Switch switches[] = {Switch(2), Switch(3), Switch(4), Switch(5), Switch(6), Switch(7), Switch(8), Switch(9)};
//Switches left to right: 5, 4, 3, 2
//Buttons left to right: 6, 7, 8, 9

//0=SingleFire, 1=HoldKey, 2=Toggle, 3=RepeatNoDelay, 4+=RepeatWithDelay
void setup() {
  Keyboard.begin();
  switches[3].defFunction(new char[1]{KEY_F24}, 1, new char[1]{KEY_F24}, 1, 1);
//  switches[3].defFunction(new char[1]{'q'}, 1, new char[1]{'q'}, 1, 1);
  switches[2].defFunction(new char[4]{KEY_LEFT_GUI, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'a'}, 4, new char[4]{KEY_LEFT_GUI, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'a'}, 4, 2);
  switches[1].defFunction(new char[1]{KEY_F15}, 1, new char[1]{KEY_F23}, 1, 2);
  switches[0].defFunction(new char[1]{KEY_F16}, 1, new char[1]{KEY_F16}, 1, 2);

  switches[4].defFunction(new char[1]{KEY_F20}, 1, new char[0]{}, 0, 0);
  switches[5].defFunction(new char[1]{KEY_F19}, 1, new char[0]{}, 0, 0);
  switches[6].defFunction(new char[1]{KEY_F18}, 1, new char[0]{}, 0, 0);
  switches[7].defFunction(new char[1]{KEY_F17}, 1, new char[0]{}, 0, 0);
  
}

bool said = false;
long lastTime = 0;
long dTime = 0;
void loop() {
  dTime = millis() - lastTime;
//  Serial.println(dTime);
  lastTime = millis();
  
  for(int i = 0; i < sizeof(switches)/sizeof(*switches); i++){
    switches[i].update(dTime);
  }
//
//  if(Serial.available() > 0){   
//    String recieved = Serial.readString();
//    Serial.println("Reccieved: " + recieved);
//  }
  
  delay(20);
}
