#include <Servo.h> //Servos' head file
Servo myservo1; //named the servos
Servo myservo2;
Servo myservo3; 
Servo myservo4; 
Servo myservo5;  
Servo myservo6;  
String comdata = "";
//numdata is an array of num
int numdata[30] = {0}, mark = 0; 

//to find the max number and min number in an array
void findArrMaxMin(int a[], int size, int *min, int *max)  
{  
    if(size == 0) {  
        return;  
    }  
    if(size == 1) {  
        *min = *max = a[0];  
        return;  
    }  
  
    *min = a[0] > a[1] ? a[1] : a[0];  
    *max = a[0] <= a[1] ? a[1] : a[0];        
  
    int i, j;  
    for(i = 2, j = 3; i < size, j < size; i += 2, j += 2) {  
        int tempmax = a[i] >= a[j] ? a[i] : a[j];  
        int tempmin = a[i] < a[j] ? a[i] : a[j];  
  
        if(tempmax > *max)  
            *max = tempmax;  
        if(tempmin < *min)  
            *min = tempmin;  
    }  
  
    //如果数组元素是奇数个，那么最后一个元素在分组的过程中没有包含其中，  
    //这里单独比较  
    if(size % 2 != 0) {  
        if(a[size -1] > *max)  
            *max = a[size - 1];  
        else if(a[size -1] < *min)  
            *min = a[size -1];  
    }  
}  

//core control algorithm 
void reachpos(int numdata[])
{
  int a,b,c,d,e,f,spd;//current data of Posread
  int stateA,stateB,stateC,stateD,stateE,stateF;//servo direction state
  int arrmin,arrmax;
  
//Speed
  spd = numdata[6]; 
  
//Serial print and assignment
//  Serial.print("Speed is ");
//  Serial.println(numdata[6]);
//  Serial.print("\n");

//read the  pos of arm
  a = myservo1.read();b = myservo2.read();c = myservo3.read();d = myservo4.read();e = myservo5.read();f = myservo6.read();
//   Serial.print("Servo1's init position is ");
//   Serial.print(a);
//   Serial.print(" degree\n");
//   Serial.print("Servo2's init position is ");
//   Serial.print(b);
//   Serial.print(" degree\n");
//   Serial.print("Servo3's init position is ");
//   Serial.print(c);
//   Serial.print(" degree\n");
//   Serial.print("Servo4's init position is ");
//   Serial.print(d);
//   Serial.print(" degree\n");
//   Serial.print("Servo5's init position is ");
//   Serial.print(e);
//   Serial.print(" degree\n");
//   Serial.print("Servo6's init position is ");
//   Serial.print(f);
//   Serial.print(" degree\n");

//state function
  if(a >= numdata[0])stateA = 1;else stateA = -1;
  if(b >= numdata[1])stateB = 1;else stateB = -1;
  if(c >= numdata[2])stateC = 1;else stateC = -1;
  if(d >= numdata[3])stateD = 1;else stateD = -1;
  if(e >= numdata[4])stateE = 1;else stateE = -1;
  if(f >= numdata[5])stateF = 1;else stateF = -1; 
//Serial.print("stateA is ");Serial.println(stateA);           
//Serial.print("stateB is ");Serial.println(stateB);        
//Serial.print("stateC is ");Serial.println(stateC);        
//Serial.print("stateD is ");Serial.println(stateD);        
//Serial.print("stateE is ");Serial.println(stateE);       
//Serial.print("stateF is ");Serial.println(stateF);  

//differ from the source to object
      int differ1 = abs(a - numdata[0]);
      int differ2 = abs(b - numdata[1]);
      int differ3 = abs(c - numdata[2]);
      int differ4 = abs(d - numdata[3]);
      int differ5 = abs(e - numdata[4]);
      int differ6 = abs(f - numdata[5]); 
//Serial.print("differ1 is ");Serial.println(differ1);   
//Serial.print("differ2 is ");Serial.println(differ2);       
//Serial.print("differ3 is ");Serial.println(differ3);         
//Serial.print("differ4 is ");Serial.println(differ4);        
//Serial.print("differ5 is ");Serial.println(differ5);  
//Serial.print("differ6 is ");Serial.println(differ6);  

//get the array's max data
      int differ[6] = {differ1,differ2,differ3,differ4,differ5,differ6};
//Serial.print("differ1 is ");Serial.println(differ[0]);   
//Serial.print("differ2 is ");Serial.println(differ[1]);       
//Serial.print("differ3 is ");Serial.println(differ[2]);         
//Serial.print("differ4 is ");Serial.println(differ[3]);        
//Serial.print("differ5 is ");Serial.println(differ[4]);  
//Serial.print("differ6 is ");Serial.println(differ[5]);  
      findArrMaxMin(differ, 6, &arrmin, &arrmax);
     
//write data to servo
      for(int i = 0 ;i <= arrmax;i += spd)
        {
          if(differ1 >= i)myservo1.write(a - stateA * i);
          if(differ2 >= i)myservo2.write(b - stateB * i);
          if(differ3 >= i)myservo3.write(c - stateC * i);
          if(differ4 >= i)myservo4.write(d - stateD * i);
          if(differ5 >= i)myservo5.write(e - stateE * i);
          if(differ6 >= i)myservo6.write(f - stateF * i);
          delay(20); //the core point to speed of servos
        }
        
//read the finally data of the pos of arm and print them       
//   a=myservo1.read();b=myservo2.read();c=myservo3.read();d=myservo4.read();e=myservo5.read();f=myservo6.read(); 
//   Serial.print("Servo1's final position is ");
//   Serial.print(a);
//   Serial.print(" degree\n");
//   Serial.print("Servo2's final position is ");
//   Serial.print(b);
//   Serial.print(" degree\n");
//   Serial.print("Servo3's final position is ");
//   Serial.print(c);
//   Serial.print(" degree\n");
//   Serial.print("Servo4's final position is ");
//   Serial.print(d);
//   Serial.print(" degree\n");
//   Serial.print("Servo5's final position is ");
//   Serial.print(e);
//   Serial.print(" degree\n");
//   Serial.print("Servo6's final position is ");
//   Serial.print(f);
//   Serial.print(" degree\n");
}

//coordinate analysis
void calc(int pos[],int n,int rate)
{
  int statedegree,delaypause = 1000;//direction and the space of time
  
  //convert to the real coordinate
  float realx = pos[0] / 26.66;
  float realy = pos[1] / 26.66;
 
 //calculate the distance from arm to the object
  float dis = sqrt(pow( abs(realx - 12.6),2 ) + pow( abs(realy - 26),2 ) ) + 2;
  
 //direction analysis
  if( realx - 12.6 > 0)statedegree = -1;else statedegree = 1 ;
 
 //calculate the rotate drgree 
  float temp = abs(atan( (realx - 12.6)/(realy - 26) )) ;
   temp = 180 * temp /3.14159265;
  int degree =93 + statedegree * round(temp);
  
//  Serial.print("distance is ");
//  Serial.println(dis);
//  Serial.print("statedegree is ");
//  Serial.println(statedegree);
//  Serial.print("temp is ");
//  Serial.println(temp);
//  Serial.print("degree is ");
//  Serial.println(degree);

//compare the realdistance and reference distance 
    if(0 <= dis && dis < 10.5)  //num1
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,120,5,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,120,5,45,degree,75,rate*n}; 
      reachpos(tempdata2); 
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);     
    }
    else if (10.5 <= dis && dis < 11.5)  //num2
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,115,10,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,115,10,45,degree,75,rate*n}; 
      reachpos(tempdata2); 
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);      
    }
    else if (11.5 <= dis && dis < 12)  //num3
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,108,15,45,degree,150,n};      
      reachpos(tempdata1); 
      delay(delaypause);
      int tempdata2[]={degree,108,15,45,degree,75,rate*n}; 
      reachpos(tempdata2); 
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);     
    }
    else if (12 <= dis && dis < 12.5)   //num4
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,105,18,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,105,18,45,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (12.5 <= dis && dis < 13)   //num5
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,100,21,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,100,21,45,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (13 <= dis && dis < 14)   //num6
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,95,26,45,degree,150,n};      
      reachpos(tempdata1); 
      delay(delaypause);
      int tempdata2[]={degree,95,26,45,degree,75,rate*n}; 
      reachpos(tempdata2);
       delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);      
    }
    else if (14 <= dis && dis < 14.5)   //num7
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,90,31,45,degree,150,n};      
      reachpos(tempdata1); 
      delay(delaypause);
      int tempdata2[]={degree,90,31,45,degree,75,rate*n}; 
      reachpos(tempdata2);
       delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);      
    }
    else if (14.5 <= dis && dis < 15.5)   //num8
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,85,36,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,85,36,45,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (15.5 <= dis && dis < 16.5)   //num9
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,80,42,45,degree,150,n};      
      reachpos(tempdata1); 
       delay(delaypause);
      int tempdata2[]={degree,80,42,45,degree,75,rate*n}; 
      reachpos(tempdata2);
       delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);      
    }
    else if (16.5 <= dis && dis < 17)   //num10
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,78,44,45,degree,150,n};      
      reachpos(tempdata1); 
      delay(delaypause);
      int tempdata2[]={degree,78,44,45,degree,75,rate*n}; 
      reachpos(tempdata2);
       delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);      
    }
    else if (17 <= dis && dis < 17.5)   //num11
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,74,49,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,74,49,45,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (17.5 <= dis && dis < 18)   //num12
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,73,52,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,73,52,45,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (18 <= dis && dis < 18.5)   //num13
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,71,55,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,71,55,45,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (18.5 <= dis && dis < 19)   //num14
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,68,58,45,degree,150,n};      
      reachpos(tempdata1); 
      delay(delaypause);
      int tempdata2[]={degree,68,58,45,degree,75,rate*n}; 
      reachpos(tempdata2);
       delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);      
    }
    else if (19 <= dis && dis < 20)   //num15
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,65,62,45,degree,150,n};      
      reachpos(tempdata1); 
      delay(delaypause);
      int tempdata2[]={degree,65,62,45,degree,75,rate*n}; 
      reachpos(tempdata2);
       delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);      
    }
    else if (20 <= dis && dis < 20.5)    //num16
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,62,66,45,degree,150,n};      
      reachpos(tempdata1); 
      delay(delaypause);
      int tempdata2[]={degree,62,66,45,degree,75,rate*n}; 
      reachpos(tempdata2);
       delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);      
    }
    else if (20.5 <= dis && dis < 21.5)    //num17
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,60,70,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,60,70,45,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (21.5 <= dis && dis < 22)   //num18
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,56,75,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,56,75,45,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (22 <= dis && dis < 23)   //num19
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,53,80,45,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,53,80,45,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (23 <= dis && dis < 24)   //num20
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,50,85,43,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,50,85,43,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (24 <= dis && dis < 24.5)   //num21
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,48,90,43,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,48,90,43,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (24.5 <= dis && dis < 25.5)   //num22
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,45,95,43,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,45,95,43,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (25.5 <= dis && dis < 26.5)   //num23
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,40,103,43,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,40,103,43,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (26 <= dis && dis < 27)  //num24
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,35,110,43,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,35,110,43,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (27 <= dis && dis < 28)   //num25
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause); 
      int tempdata1[]={degree,30,118,43,degree,150,n};      
      reachpos(tempdata1); 
      delay(delaypause);
      int tempdata2[]={degree,30,118,43,degree,75,rate*n}; 
      reachpos(tempdata2);
       delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,2*n}; 
      reachpos(tempdata3);      
    }
    else if (28 <= dis && dis < 29)   //num26
    {
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause);  
      int tempdata1[]={degree,25,128,43,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,25,128,43,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }
    else if (29 <= dis && dis <= 40)   //num27
    { 
      int tempdata0[]={degree,120,60,45,90,150,rate*n}; 
      reachpos(tempdata0);
      delay(delaypause);  
      int tempdata1[]={degree,20,135,43,degree,150,n};      
      reachpos(tempdata1);
      delay(delaypause);
      int tempdata2[]={degree,20,135,43,degree,75,rate*n}; 
      reachpos(tempdata2);
      delay(delaypause);
      int tempdata3[]={degree,120,60,45,90,75,rate*n}; 
      reachpos(tempdata3);       
    }  
}

//put the object to a place
void putobject1()
{
  int putback1[] = {0,120,60,45,90,75,1};
  int putback2[] = {0,75,50,45,90,75,1};
  int putback3[] = {0,75,50,45,90,150,1};
  int putback4[] = {0,120,60,45,90,150,1};
  delay(500);
  reachpos(putback1);
  delay(300);
  reachpos(putback2);
  delay(300);
  reachpos(putback3);
  delay(300);
  reachpos(putback4);
}

void putobject2()
{
  int putback1[] = {25,120,60,45,115,75,1};
  int putback2[] = {25,72,55,45,115,75,1};
  int putback3[] = {25,72,55,45,115,150,1};
  int putback4[] = {25,120,60,45,115,150,1};
  delay(500);
  reachpos(putback1);
  delay(300);
  reachpos(putback2);
  delay(300);
  reachpos(putback3);
  delay(300);
  reachpos(putback4);
}

void putobject3()
{
  int putback1[] = {0,120,60,45,90,75,1};
  int putback2[] = {0,113,12,45,90,75,1};
  int putback3[] = {0,113,12,45,90,150,1};
  int putback4[] = {0,120,60,45,90,150,1};
  delay(500);
  reachpos(putback1);
  delay(300);
  reachpos(putback2);
  delay(300);
  reachpos(putback3);
  delay(300);
  reachpos(putback4);
}

void putobject4()
{
  int putback1[] = {40,120,60,45,130,75,1};
  int putback2[] = {40,105,20,45,130,75,1};
  int putback3[] = {40,105,20,45,130,150,1};
  int putback4[] = {40,120,60,45,130,150,1};
  delay(500);
  reachpos(putback1);
  delay(300);
  reachpos(putback2);
  delay(300);
  reachpos(putback3);
  delay(300);
  reachpos(putback4);
}

void putobject5()
{
  int putback1[] = {45,120,60,45,135,75,1};
  int putback2[] = {45,55,80,45,135,75,1};
  int putback3[] = {45,55,80,45,135,150,1};
  int putback4[] = {45,120,60,45,135,150,1};
  delay(500);
  reachpos(putback1);
  delay(300);
  reachpos(putback2);
  delay(300);
  reachpos(putback3);
  delay(300);
  reachpos(putback4);
}
//after operation back to the init position
void backfunction()
{
  int back[] = {0,180,0,35,90,150,1};
  delay(300);
  reachpos(back);
}

//init function
void setup()
{
//set the Servos' pins
  myservo1.attach(11);  
  myservo2.attach(10);  
  myservo3.attach(9);  
  myservo4.attach(8);  
  myservo5.attach(7);  
  myservo6.attach(6);  
//set the Baud rate
  Serial.begin(9600);
  Serial.print("I am ready!\n");
//set the initialize the arm's position
  myservo1.write(0);myservo2.write(180);myservo3.write(0);myservo4.write(35);myservo5.write(90);myservo6.write(150);
}

//main function 
void loop()
{
    //j是分拆之后数字数组的位置记数
    int j = 0;
    //不断循环检测串口缓存，一个个读入字符串，
    while (Serial.available() > 0)
    {      
    //读入之后将字符串，串接到comdata上面。
      comdata += char(Serial.read());
        //延时一会，让串口缓存准备好下一个数字，不延时会导致数据丢失，
      delay(2);
      //标记串口读过数据，如果没有数据的话，直接不执行这个while了。
      mark = 1;   
    }
   
    if(mark == 1)  //如果接收到数据则执行comdata分析操作，否则什么都不做。
    {
     //显示刚才输入的字符串（可选语句）
//      Serial.print("\n");
//      Serial.print("Init data is ");
//      Serial.println(comdata);
     //显示刚才输入的字符串长度（可选语句）
//     Serial.println(comdata.length());

  //以串口读取字符串长度循环，
        for(int i = 0,I = comdata.length(); i < I ; i++)
        {
        //逐个分析comdata[i]字符串的文字，如果碰到文字是分隔符（这里选择逗号分割）则将结果数组位置下移一位
        //即比如11,22,33,55开始的11记到numdata[0];碰到逗号就j等于1了，
        //再转换就转换到numdata[1];再碰到逗号就记到numdata[2];以此类推，直到字符串结束
          if(comdata[i] == ',')
            {
              j++;
            }
          else
          {
             //如果没有逗号的话，就将读到的数字*10加上以前读入的数字，
             //并且(comdata[i] - '0')就是将字符'0'的ASCII码转换成数字0（下面不再叙述此问题，直接视作数字0）。
             //比如输入数字是12345，有5次没有碰到逗号的机会，就会执行5次此语句。
             //因为左边的数字先获取到，并且numdata[0]等于0，
             //所以第一次循环是numdata[0] = 0*10+1 = 1
             //第二次numdata[0]等于1，循环是numdata[0] = 1*10+2 = 12
             //第三次是numdata[0]等于12，循环是numdata[0] = 12*10+3 = 123
             //第四次是numdata[0]等于123，循环是numdata[0] = 123*10+4 = 1234
             //如此类推，字符串将被变成数字0。
            numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
          }
        }
      //comdata的字符串已经全部转换到numdata了，清空comdata以便下一次使用，
      //如果不请空的话，本次结果极有可能干扰下一次。
        comdata = String("");

//source data print        
//      Serial.print("X point data is ");
//      Serial.println(numdata[0]);
//      Serial.print("Y point data is ");
//      Serial.println(numdata[1]);
//        Serial.print("I am on the way!\n");
      
//core operation 
      if ( numdata[24] == 1)//to make compatible between two software
      {
        int sped = numdata[20],rate = numdata[21],sum = numdata[22],choice = numdata[23];
        int xypoint1[] = { numdata[0] , numdata[1] };
        int xypoint2[] = { numdata[4] , numdata[5] }; 
        int xypoint3[] = { numdata[8] , numdata[9] };
        int xypoint4[] = { numdata[12] , numdata[13] };
        int xypoint5[] = { numdata[16] , numdata[17] };
        int check1,check2,check3,check4,check5,stand = 5;
//find the differ between Horizontal and vertical
        check1 = abs(numdata[2] - numdata[3]);
        check2 = abs(numdata[6] - numdata[7]);
        check3 = abs(numdata[10] - numdata[11]);
        check4 = abs(numdata[14] - numdata[15]);
        check5 = abs(numdata[18] - numdata[19]);       
//        Serial.print("check1 is \n");
//        Serial.println(check1);
//        Serial.print("check2 is \n");
//        Serial.println(check2);
//        Serial.print("check3 is \n");
//        Serial.println(check3);
//        Serial.print("check4 is \n");
//        Serial.println(check4);
//        Serial.print("check5 is \n");
//        Serial.println(check5);          
        int check[] = {check1,check2,check3,check4,check5};
        int arrxpoint[] = {numdata[0],numdata[4],numdata[8],numdata[12],numdata[16]};
        int arrypoint[] = {numdata[1],numdata[5],numdata[9],numdata[13],numdata[17]};
        int arrcirnumx[5] = {0};int arrrectnumx[5] = {0};
        int arrcirnumy[5] = {0};int arrrectnumy[5] = {0};
        int circlenum = 0 ;int rectnum = 0;
        int k = 0; int v =0;
        for (int i = 0; i < sum; i++)
        {
          if(check[i] <= stand)
          {
            arrcirnumx[k] = arrxpoint[i];
            arrcirnumy[k] = arrypoint[i];
            circlenum ++;
            k++;
          }
          else
          {
            arrrectnumx[v] = arrxpoint[i];            
            arrrectnumy[v] = arrypoint[i];            
            rectnum ++;
            v++;
          }
        }            
        int arrcirnum1[] = {arrcirnumx[0],arrcirnumy[0]};int arrcirnum2[] = {arrcirnumx[1],arrcirnumy[1]};
        int arrcirnum3[] = {arrcirnumx[2],arrcirnumy[2]};int arrcirnum4[] = {arrcirnumx[3],arrcirnumy[3]};
        int arrcirnum5[] = {arrcirnumx[4],arrcirnumy[4]}; 
        int arrrectnum1[] = {arrrectnumx[0],arrrectnumy[0]};int arrrectnum2[] = {arrrectnumx[1],arrrectnumy[1]};
        int arrrectnum3[] = {arrrectnumx[2],arrrectnumy[2]};int arrrectnum4[] = {arrrectnumx[3],arrrectnumy[3]};
        int arrrectnum5[] = {arrrectnumx[4],arrrectnumy[4]};
//        Serial.print(arrcirnumx[0]);Serial.print(" ");Serial.println(arrcirnumy[0]);
//        Serial.print(arrcirnumx[1]);Serial.print(" ");Serial.println(arrcirnumy[1]);
//        Serial.print(arrcirnumx[2]);Serial.print(" ");Serial.println(arrcirnumy[2]);
//        Serial.print(arrcirnumx[3]);Serial.print(" ");Serial.println(arrcirnumy[3]);
//        Serial.print(arrcirnumx[4]);Serial.print(" ");Serial.println(arrcirnumy[4]);
//        
//        Serial.print(arrrectnumx[0]);Serial.print(" ");Serial.println(arrrectnumy[0]);
//        Serial.print(arrrectnumx[1]);Serial.print(" ");Serial.println(arrrectnumy[1]);
//        Serial.print(arrrectnumx[2]);Serial.print(" ");Serial.println(arrrectnumy[2]);
//        Serial.print(arrrectnumx[3]);Serial.print(" ");Serial.println(arrrectnumy[3]);
//        Serial.print(arrrectnumx[4]);Serial.print(" ");Serial.println(arrrectnumy[4]);

//main function       
        if(sum == 0)Serial.print("Sorry,nothing have found!\n");
        else
        { 
            Serial.print("Circle's number is ");
            Serial.println(circlenum);
            Serial.print("Rectangle's number is ");
            Serial.println(rectnum);
//          Serial.print("choice is ");
//          Serial.println(choice);
          if(choice == 1)
          {
              if(sum == 1)
              {
                calc(xypoint1,sped,rate);
                putobject1();
                delay(300);
                backfunction();
              }
              else if(sum == 2)
              {
                calc(xypoint1,sped,rate); 
                putobject1();
                delay(300);
                calc(xypoint2,sped,rate);
                putobject2();
                delay(300);
                backfunction();
              }
              else if(sum == 3)
              {
                calc(xypoint1,sped,rate); 
                putobject1();
                delay(300);
                calc(xypoint2,sped,rate);
                putobject2();
                delay(300); 
                calc(xypoint3,sped,rate);
                putobject3(); 
                delay(300); 
                backfunction();
              }
              else if(sum == 4)
              {
                calc(xypoint1,sped,rate); 
                putobject1();
                delay(300);
                calc(xypoint2,sped,rate);
                putobject2();
                delay(300); 
                calc(xypoint3,sped,rate);
                putobject3(); 
                delay(300);
                calc(xypoint4,sped,rate);
                putobject4(); 
                delay(300); 
                backfunction();
              }
              else if(sum == 5)
              {
                calc(xypoint1,sped,rate); 
                putobject1();
                delay(300);
                calc(xypoint2,sped,rate);
                putobject2();
                delay(300); 
                calc(xypoint3,sped,rate);
                putobject3(); 
                delay(300); 
                calc(xypoint4,sped,rate);
                putobject4(); 
                delay(300);
                calc(xypoint5,sped,rate);
                putobject5(); 
                delay(300);
                backfunction();
              }
              else Serial.print("Sorry,out of my charge!\n");
          }
          
          else if(choice == 2)
          {
            if (sum <= 5)
                {
                    if(circlenum == 1)
                    {               
                          calc(arrcirnum1,sped,rate);
                          putobject1();
                          delay(300);
                          backfunction();
                     }                               
                    else if(circlenum == 2)
                    {               
                          calc(arrcirnum1,sped,rate); 
                          putobject1();
                          delay(300);                 
                          calc(arrcirnum2,sped,rate);
                          putobject2();
                          delay(300); 
                          backfunction();                 
                     }                                           
                    else if(circlenum == 3)
                    {                
                        calc(arrcirnum1,sped,rate); 
                        putobject1();
                        delay(300);               
                        calc(arrcirnum2,sped,rate);
                        putobject2();
                        delay(300); 
                        calc(arrcirnum3,sped,rate);
                        putobject3(); 
                        delay(300);
                        backfunction();                              
                    }             
                    else if(circlenum == 4)
                    {
                        calc(arrcirnum1,sped,rate); 
                        putobject1();
                        delay(300);
                        calc(arrcirnum2,sped,rate);
                        putobject2();
                        delay(300); 
                        calc(arrcirnum3,sped,rate);
                        putobject3(); 
                        delay(300);
                        calc(arrcirnum4,sped,rate);
                        putobject4(); 
                        delay(300);
                        backfunction();               
                    }
                    else if(circlenum == 5)
                    {
                        calc(arrcirnum1,sped,rate); 
                        putobject1();
                        delay(300);
                        calc(arrcirnum2,sped,rate);
                        putobject2();
                        delay(300);
                        calc(arrcirnum3,sped,rate);
                        putobject3(); 
                        delay(300);
                        calc(arrcirnum4,sped,rate);
                        putobject4(); 
                        delay(300);
                        calc(arrcirnum5,sped,rate);
                        putobject5(); 
                        delay(300);                  
                        backfunction();          
                    }
                }
              else Serial.print("Sorry,out of my charge!\n");
          }
          
          else if(choice == 3)
          {
            if(sum <= 5)
            {
              if(rectnum == 1)
              {
                    calc(arrrectnum1,sped,rate);
                    putobject1();
                    delay(300);
                    backfunction();
              }
              else if(rectnum == 2)
              {
                    calc(arrrectnum1,sped,rate); 
                    putobject1();
                    delay(300);
                    calc(arrrectnum2,sped,rate);
                    putobject2();
                    delay(300);                  
                    backfunction();
              }
              else if(rectnum == 3)
              {
                  calc(arrrectnum1,sped,rate); 
                  putobject1();
                  delay(300);
                  calc(arrrectnum2,sped,rate);
                  putobject2();
                  delay(300); 
                  calc(arrrectnum3,sped,rate);
                  putobject3(); 
                  delay(300);
                  backfunction();
              }
              else if(rectnum == 4)
              {
                  calc(arrrectnum1,sped,rate); 
                  putobject1();
                  delay(300);
                  calc(arrrectnum2,sped,rate);
                  putobject2();
                  delay(300); 
                  calc(arrrectnum3,sped,rate);
                  putobject3(); 
                  delay(300);
                  calc(arrrectnum4,sped,rate);
                  putobject4(); 
                  delay(300);
                  backfunction();        
              }
              else if(rectnum == 5)
              {
                  calc(arrrectnum1,sped,rate); 
                  putobject1();
                  delay(300);
                  calc(arrrectnum2,sped,rate);
                  putobject2();
                  delay(300);
                  calc(arrrectnum3,sped,rate);
                  putobject3(); 
                  delay(300);
                  calc(arrrectnum4,sped,rate);
                  putobject4(); 
                  delay(300);
                  calc(arrrectnum5,sped,rate);
                  putobject5(); 
                  delay(300);                  
                  backfunction();           
              }    
            }         
              else Serial.print("Sorry,out of my charge!\n");
          }
          
          else if(choice == 4)
          {
            if(sum <= 5)
            {
            if(circlenum == 1)
              {               
                    calc(arrcirnum1,sped,rate);
                    putobject1();
                    delay(300);
                    if(rectnum == 0)backfunction();
               }                               
              else if(circlenum == 2)
              {               
                    calc(arrcirnum1,sped,rate); 
                    putobject1();
                    delay(300);                 
                    calc(arrcirnum2,sped,rate);
                    putobject2();
                    delay(300); 
                    if(rectnum == 0)backfunction();                 
               }                                           
              else if(circlenum == 3)
              {                
                  calc(arrcirnum1,sped,rate); 
                  putobject1();
                  delay(300);               
                  calc(arrcirnum2,sped,rate);
                  putobject2();
                  delay(300); 
                  calc(arrcirnum3,sped,rate);
                  putobject5(); 
                  delay(300);
                  if(rectnum == 0)backfunction();                              
              }             
              else if(circlenum == 4)
              {
                  calc(arrcirnum1,sped,rate); 
                  putobject1();
                  delay(300);
                  calc(arrcirnum2,sped,rate);
                  putobject2();
                  delay(300); 
                  calc(arrcirnum3,sped,rate);
                  putobject5(); 
                  delay(300);
                  calc(arrcirnum4,sped,rate);
                  putobject1(); 
                  delay(300);
                  if(rectnum == 0)backfunction();               
              }
              else if(circlenum == 5)
              {
                  calc(arrcirnum1,sped,rate); 
                  putobject1();
                  delay(300);
                  calc(arrcirnum2,sped,rate);
                  putobject2();
                  delay(300);
                  calc(arrcirnum3,sped,rate);
                  putobject5(); 
                  delay(300);
                  calc(arrcirnum4,sped,rate);
                  putobject1(); 
                  delay(300);
                  calc(arrcirnum5,sped,rate);
                  putobject2(); 
                  delay(300);                  
                  if(rectnum == 0)backfunction();          
              }
              else Serial.print("Circle have scanned!\n");
              
              if(rectnum == 1)
              {
                    calc(arrrectnum1,sped,rate);
                    putobject3();
                    delay(300);
                    backfunction();
              }
              else if(rectnum == 2)
              {
                    calc(arrrectnum1,sped,rate); 
                    putobject3();
                    delay(300);
                    calc(arrrectnum2,sped,rate);
                    putobject4();
                    delay(300);                  
                    backfunction();
              }
              else if(rectnum == 3)
              {
                  calc(arrrectnum1,sped,rate); 
                  putobject3();
                  delay(300);
                  calc(arrrectnum2,sped,rate);
                  putobject4();
                  delay(300); 
                  calc(arrrectnum3,sped,rate);
                  putobject3(); 
                  delay(300);
                  backfunction();
              }
              else if(rectnum == 4)
              {
                  calc(arrrectnum1,sped,rate); 
                  putobject3();
                  delay(300);
                  calc(arrrectnum2,sped,rate);
                  putobject4();
                  delay(300); 
                  calc(arrrectnum3,sped,rate);
                  putobject3(); 
                  delay(300);
                  calc(arrrectnum4,sped,rate);
                  putobject4(); 
                  delay(300);
                  backfunction();        
              }
              else if(rectnum == 5)
              {
                  calc(arrrectnum1,sped,rate); 
                  putobject3();
                  delay(300);
                  calc(arrrectnum2,sped,rate);
                  putobject4();
                  delay(300);
                  calc(arrrectnum3,sped,rate);
                  putobject3(); 
                  delay(300);
                  calc(arrrectnum4,sped,rate);
                  putobject4(); 
                  delay(300);
                  calc(arrrectnum5,sped,rate);
                  putobject3(); 
                  delay(300);                  
                  backfunction();           
              } 
              else Serial.print("Rectangle have scanned!\n");
            } 
            else Serial.print("Sorry,it's out of my charge!\n");
          }        
          else Serial.print("Sorry,system error!\n");
        }
      }
      
      else if(numdata[6] != 1)
      {
        Serial.print("I'm online!\n");
      }
      
      else reachpos(numdata);
      
//循环输出numdata的内容
        for(int i = 0; i < 30; i++)
          {
            numdata[i] = 0;
          }
  
//输出之后必须将读到数据的mark置0，不置0下次循环就不能使用了。
         mark = 0;
         
// operation over       
       Serial.print("OK!\n");
    }
}
