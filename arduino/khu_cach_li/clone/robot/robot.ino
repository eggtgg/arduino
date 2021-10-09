#include <PS2X_lib.h>  

PS2X ps2x; // create PS2 Controller Class

#define isd_lay_com     A0
#define isd_do_nhiet    A1
#define toi_trai         3
#define lui_trai         5
#define toi_phai         6
#define lui_phai         9

int   error = 0; 
byte  type = 0;
byte  vibrate = 0;

void setup()
{
 Serial.begin(9600);
 pinMode(toi_trai,          OUTPUT);
 pinMode(lui_trai,          OUTPUT);
 pinMode(toi_phai,          OUTPUT);
 pinMode(lui_phai,          OUTPUT);
 pinMode(isd_lay_com,       OUTPUT);
 pinMode(isd_do_nhiet,      OUTPUT);
 analogWrite(toi_trai, 0);
 analogWrite(lui_trai, 0);
 analogWrite(toi_phai, 0);
 analogWrite(lui_phai, 0);
 digitalWrite(isd_lay_com,  LOW);
 digitalWrite(isd_do_nhiet, LOW);
 
 error = ps2x.config_gamepad(13,11,10,12, true, true);  
 
 if(error == 0)
 {
    Serial.println("Found Controller, configured successful");
 }
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips"); 
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  type = ps2x.readType(); 
  switch(type) 
  {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }
}

void loop()
{    
 if(error == 1) //skip loop if no controller found
  return; 
 if(type == 2)
 { 
   ps2x.read_gamepad();          //read controller 
 }
 else 
 { 
    ps2x.read_gamepad(false, vibrate);          
    //**** 2 NÚT START, SELECT ****
    if(ps2x.Button(PSB_START))                   
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
    //BẤM NÚT R2 (PHẢI DƯỚI) KẾT HỢP NÚT TRÁI PHẢI ĐỂ XOAY)         
    if(ps2x.Button(PSB_R2))
    {
      if(ps2x.Button(PSB_PAD_RIGHT))
      {
        Serial.println("PHẢI CHÍNH TÂM");
        analogWrite(toi_trai, 170);
        analogWrite(lui_trai, 0);
        analogWrite(toi_phai, 0);
        analogWrite(lui_phai, 255);
      }
      else if(ps2x.Button(PSB_PAD_LEFT))
      {
        Serial.println("TRÁI CHÍNH TÂM");
        analogWrite(toi_trai, 0);
        analogWrite(lui_trai, 170);
        analogWrite(toi_phai, 255);
        analogWrite(lui_phai, 0);
      }    
      else
      {
        analogWrite(toi_trai, 0);
        analogWrite(lui_trai, 0);
        analogWrite(toi_phai, 0);
        analogWrite(lui_phai, 0);
        digitalWrite(isd_lay_com,  LOW);
        digitalWrite(isd_do_nhiet, LOW);
      }
    }
    else
    {
      if(ps2x.Button(PSB_PAD_RIGHT))
      {
        Serial.println("PHẢI");
        analogWrite(toi_trai, 170);
        analogWrite(lui_trai, 0);
        analogWrite(toi_phai, 0);
        analogWrite(lui_phai, 0);
      }
      else if(ps2x.Button(PSB_PAD_LEFT))
      {
        Serial.println("TRÁI");
        analogWrite(toi_trai, 0);
        analogWrite(lui_trai, 0);
        analogWrite(toi_phai, 255);
        analogWrite(lui_phai, 0);
      }
      else
      {
        analogWrite(toi_trai, 0);
        analogWrite(lui_trai, 0);
        analogWrite(toi_phai, 0);
        analogWrite(lui_phai, 0);
        digitalWrite(isd_lay_com,  LOW);
        digitalWrite(isd_do_nhiet, LOW);
      }
    }
         
    //**** 4 NÚT UP, RIGHT, LEFT, RIGHT, DOWN ****   
    if((ps2x.Button(PSB_PAD_UP))&&(ps2x.Button(PSB_PAD_RIGHT))) 
    {        
      Serial.println("TỚI-PHẢI");
      analogWrite(toi_trai, 170);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 170);
      analogWrite(lui_phai, 0);
    }
    else if((ps2x.Button(PSB_PAD_UP))&&(ps2x.Button(PSB_PAD_LEFT))) 
    {        
      Serial.println("TỚI-TRÁI");
      analogWrite(toi_trai, 75);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 255);
      analogWrite(lui_phai, 0);
    }
    else if((ps2x.Button(PSB_PAD_DOWN))&&(ps2x.Button(PSB_PAD_RIGHT))) 
    {        
      Serial.println("LUI-PHẢI");
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 170);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 120);
    }
    else if((ps2x.Button(PSB_PAD_DOWN))&&(ps2x.Button(PSB_PAD_LEFT))) 
    {        
      Serial.println("LUI-TRÁI");
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 110);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 255);
    }
      
    else if(ps2x.Button(PSB_PAD_UP)) 
    {        
      Serial.println("TỚI");
      analogWrite(toi_trai, 125);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 255);
      analogWrite(lui_phai, 0);
    }
    
    else if(ps2x.Button(PSB_PAD_DOWN))
    {
      Serial.println("LUI");
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 135);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 255);
    }
    //**** 4 NÚT TRÒN, VUÔNG, X, TAM GIÁC ****
    else if(ps2x.ButtonPressed(PSB_RED))             
       Serial.println("NUT TRON");
         
    else if(ps2x.ButtonReleased(PSB_PINK)) 
    {          
       Serial.println("NUT VUONG");     
       digitalWrite(isd_lay_com,  HIGH);
       delay(1000);
       digitalWrite(isd_lay_com,  LOW);
    }
    else if(ps2x.NewButtonState(PSB_BLUE))           
       Serial.println("NUT X");    
    
    else if(ps2x.Button(PSB_GREEN))
    {
      Serial.println("NUT TAM GIAC");  
      digitalWrite(isd_do_nhiet, HIGH);
      delay(1000);
      digitalWrite(isd_do_nhiet, LOW);
    }
    else     
    {
      /*
      analogWrite(toi_trai, 0);
      analogWrite(lui_trai, 0);
      analogWrite(toi_phai, 0);
      analogWrite(lui_phai, 0);
      digitalWrite(isd_lay_com,  LOW);
      digitalWrite(isd_do_nhiet, LOW);
      */
    }
  }
  delay(50);   
}
