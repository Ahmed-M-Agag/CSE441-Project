//Key Bad & 7_Segment Project
 //Includes
  #include "mbed.h"
  #include "mbed2/299/drivers/BusOut.h"
  #include "keybad.h"
 /*7_SEGMENT Layout*/
    BusInOut Disp1(PTC6,PTC5,PTC16,PTA16,PTA17,PTC10,PTC11);

    DigitalOut vdd(PTC17); // define PIN PTC17 {Common Cathode} 0v
    void setvdd(); // to set CA to 3.3v
     {
     vdd=0;
     }
 /*KEYBAD Layout*/
  //create Digitalin to probe row
    DigitalIn row1(PTE5) //row 1 input
    DigitalIn row2(PTE4) //row 2 input
    DigitalIn row3(PTE3) //row 3 input
    DigitalIn row4(PTE2) //row 4 input

  //create digitalout to scan column
    DigitalOut col1(PTB11) // col 1 output 
    DigitalOut col2(PTB10) // col 2 output 
    DigitalOut col3(PTB9)  // col 3 output 
    DigitalOut col4(PTB8)  // col 4 output 
 //Functions
    void setCol1Lo();
    void setCol2Lo();  
    void setCol3Lo();
    void setCol4Lo();
    void setColsHi();
    void Key_Scan();
    void Segment();

 //Set Columns HI & LO
     //set single column Lo
    void setCol1Lo()
     {
     col1=0;
     col2=1;
     col3=1;
     col4=1;
     }
    void setCol2Lo()
     {
     col1=1;
     col2=0;
     col3=1;
     col4=1;
     }
    void setCol3Lo()
     {
     col1=1;
     col2=1;
     col3=0;
     col4=1;
     }
    void setCol4Lo()
     {
     col1=1;
     col2=1;
     col3=1;
     col4=0;
     }
     //set all column High
     void setColsHi()
     {
     col1=1;
     col2=1;
     col3=1;
     col4=1;
     }
 // Key Scan Function
    //Display The Digits On 7_Segment
     void key_1() {
         int num1 =1;
         int num2 =1;
        Disp1=0xF9;
        }
     void key_2() {
         int num1 =2;
         int num2 =2;
        Disp1=0xA4;
        }
     void key_3() {
         int num1 =3;
         int num2 =3;
        Disp1=0x80;
        }
     void key_4() {
         int num1 =4;
         int num2 =4;
        Disp1=0x99;
        }
     void key_5() {
         int num1 =5;
         int num2 =5;
        Disp1=0x92;
        }
     void key_6() {
         int num1 =6;
         int num2 =6;
        Disp1=0x82;
        }
     void key_7() {
         int num1 =7;
         int num2 =7;
        Disp1=0xF8;
        }
     void key_8() {
         int num1 =8;
         int num2 =8;
        Disp1=0x80;
        }
     void key_9() {
         int num1 =9;
         int num2 =9;
        Disp1=0x90;
        }
      //Display nothing on 7segment
     void key_0(){
         int num1 =0;
         int num2 =0;
        Disp1=0x3F;
        }
     void Key_C(){
         Disp1=0x3F;
        }

    void Key_Scan()
     {
     setColsHi();
     wait(0.2);
     //column1
        setCol1Lo();
        if (row1==0)
            Key_1 ();
        if (row2==0)
            Key_4();
        if (row3==0)
            Key_7();
        if (row4==0)
            Key_F(); //Do nothing
        wait(0.2);
     //column2
        setCol2Lo();
        if (row1==0)
          Key_2();
        if (row2==0)
          Key_5();
        if (row3==0)
          Key_8();
        if (row4==0)
         Key_0();
        wait(0.2);
     //column3
        setCol3Lo();
        if (row1==0)
            Key_4();
        if (row2==0)
            Key_6();
        if (row3==0)
            Key_9();
        if (row4==0)
            Key_E();
        wait(0.2);
     //column4
        setCol4Lo();
        if (row1==0)
            Key_A();;
        if (row2==0)
            Key_B();;
        if (row3==0)
            Key_C();
        if (row4==0)
            Key_D();;
        wait(0.2);
     }

 
 
 
 
 //Calculations
  void Calculations(){
       Key_Scan();

      int num1;
      int num2;
      int Result;
      jump:
      while(1){
          cin>> num1;
          switch (Key_Scan()) 
            {
             case 'Key_A': //Key_A = '+'
                cin>>num2;
                Result=num1+num2;
                break;
             case 'Key_B': //Key_B = '-'
                cin>>num2;
                Result=num1-num2;
                break;
             default:
             break;
                

             }


         //Reset while
          if (Key_C==0) 
           { 
           goto jump; 
           }
           
      }
      return Result ;
     }

/*Main Code*/
     int main(void) {
        int Result;
        int show[10]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B}; //  store 7-segment data in array
        setvdd();
        Key_Scan();
        getin:
        while(1){
        Result= Calculations();
        if(Result>9) //if result >9 display F on 7_segment
            Disp1=0x47;
        if(Result<0) //if result <0 display A on 7_segment
            Disp1=0x77;
        else
         Disp1=show[Result];
         if(Key_C==0)
            goto getin;
        }
        
        

    
    

       }
