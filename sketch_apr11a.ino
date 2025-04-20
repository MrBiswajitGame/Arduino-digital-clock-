#define Led_pin 13
#define buzar A4
          //a,b,c,d,e,f,g
int pin[] = {2,3,4,5,6,7,8};
int dig[] = {9,10,11,12};
int button[] = {A0, A1, A2, A3};
               //0,  1,  2,  3

unsigned long PV = 0, pri = 0;
unsigned long pv[6] = {0,0,0,0,0,0};
int in = 1500;
int HH = 2, MM = 14, hh = 0,Day = 19, Manth = 4;
int alarm_hh = 7, alarm_mm = 5;
int x[4];
float xm;
int state = 0;
int rx = 1, mx = 1, nx = 1;
bool xc = true;
int Number[10][7] = {
   //a,b,c,d,e,f,g
    {1,1,1,1,1,1,0}, //0
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
    {1,0,1,1,0,1,1}, //5
    {1,0,1,1,1,1,1}, //6
    {1,1,1,0,0,0,0}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,1,0,1,1}  //9
};  
 
void setup(){
    for(int i = 0; i < 7; i++)
          pinMode(pin[i], OUTPUT);
           for(int i =0; i < 4; i++)
         pinMode(dig[i], OUTPUT);
    for(int i = 0; i < 4; i++)
            pinMode(button[i], INPUT_PULLUP);
    pinMode(Led_pin, OUTPUT);
    pinMode(A5, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    alarm();
    time();
    Display_Out();
    button_in();
    separator();
}

void time(){
     long ml = millis();
    if(ml - PV >= 59980){
        PV = ml;
      MM++;        
        if(MM == 60){
            MM = 0;
            HH++;
            if(HH == 13){
              HH = 1;
              hh++;
              if(hh == 2){
                hh = 0;
                date();
            }}}}}

void date(){
    Day++;
    if(Day == 30){
        Day = 1;
        Manth++;
        if(Manth > 12)
        Manth = 1;    
        }}

void Display_Out(){
    if(millis() - pri >= 10000 && state >= 0){
        pri = millis();
        nx++; 
        if(nx == 2){
        nx = 0;
        }}
    if(state >= 1 && state < 3) nx = 1;
    if(state >= 3) nx = 0;
      if(nx == 1){
            x[0] = MM % 10;
            x[1] = MM / 10;
            x[2] = HH % 10;
            x[3] = HH / 10;
            }
      if(nx == 0){
            x[0] = Manth % 10;
            x[1] = Manth / 10;
            x[2] = Day % 10;
            x[3] = Day / 10;    
            }
      if(mx == 0){
            x[0] = alarm_mm % 10;
            x[1] = alarm_mm / 10;
            x[2] = alarm_hh % 10;
            x[3] = alarm_hh / 10;
            }  
 for(int i = 0; i < 4; i++){
        digitalWrite(dig[i], 0);
        for(int j = 0; j < 7; j++){
           digitalWrite(pin[j], Number[x[i]][j]);
            }      
            delay(3);
            digitalWrite(dig[i], 1);
 }}

void button_in(){
 if(digitalRead(button[2]) == 0 && millis() - pv[0] >= 200){
       if(mx == 1) state++;
       if(state == 5) state = 0;
       if(mx == 0){ state++; 
       if(state == 3) state = 0; }
       pv[0] = millis();
       }
    if(digitalRead(button[3]) == 0 && millis() - pv[1] >= 200){
       pv[1] = millis();
       mx = !mx;
       }
    if(digitalRead(button[0]) ==0 && millis() - pv[2] >= in){
        if(state == 1 && mx == 1)MM++;
        if(MM > 60) MM = 60;
        else if(state == 2 && mx == 1) HH++;
        if(HH > 12) HH = 12;
        else if( state == 3 && mx == 1) Day++;
        if(Day > 30) Day = 30;
        else if(state == 4 && mx == 1) Manth++;
        if(Manth > 12) Manth = 12;
        
        else if(state == 1) alarm_mm++;
        if(alarm_mm > 60) alarm_mm = 60;
        else if(state == 2) alarm_hh++;
        if(alarm_hh > 12) alarm_hh = 12;
        pv[2] = millis();
        }
    if(digitalRead(button[1]) == 0 && millis() - pv[3] >= in){
        if(state == 1 && mx == 1) MM--;      
        if(MM < 1) MM = 1;
        else if(state == 2 && mx == 1) HH--;
        if(HH < 1) HH = 1;
        else if(state == 3 && mx == 1) Day--;
        if(Day < 1) Day = 1;
        else if(state == 4 && mx == 1) Manth--;
        if(Manth < 1) Manth = 1;
        
        else if(state == 1) alarm_mm--;
        if(alarm_mm < 1) alarm_mm = 1; 
        else if(state == 2) alarm_hh--;
        if(alarm_hh < 1) alarm_hh = 1;
        pv[3] = millis();
        }} 
 
void alarm(){
    if(HH == alarm_hh && MM == alarm_mm)
    tone(buzar, 1500);
    else noTone(buzar);
    }

void separator(){
 if(millis() - pv[4] >= 1000 && state == 0){
   digitalWrite(Led_pin, xc);
   pv[4] = millis();
   xc = !xc;
}}