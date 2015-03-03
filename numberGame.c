#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void divideByTwo(char*str){
   int i = 0;
   while(i < 349){
      str[i]=str[i+1];
      i++;
   }
}

void binaryAdder(char*dest,char*str,char*str2,int i, unsigned int carry){
   if(i==350)
      return;
   dest[i] = carry ^ str[i] ^ str2[i];
   unsigned int newCarry = (str[i] & str2[i]) | (carry&(str[i]^str2[i]));
   binaryAdder(dest,str,str2,++i,newCarry); 
}

void flipBinaryBits(char * binStr){
   int i = 0;
   while(i < 350){
      if(binStr[i]==0)
         binStr[i]=1;
      else if(binStr[i]==1)
         binStr[i]=0;
       i++;
   }
}

void addBinaryOne(char * str){
   int i = 0;
   while (str[i] == 1) {
      str[i]= 0;
      i++;
   }
   str[i] = 1;
}
int returnsZeroIfZeroOneIfOneTwoOtherwise(char * str){
   long max = 350;
   int i = 1; 
   while(i < max) {
      if(str[i]!=0)
         return 2;
      i++;
   }
   return str[0];
}

void binarySubtraction(char * res, char * firstNum, char * secondNum){
   if(returnsZeroIfZeroOneIfOneTwoOtherwise(secondNum)==0){
      memcpy(res,firstNum,350);
      return;
   }
   flipBinaryBits(secondNum);
   addBinaryOne(secondNum);
   binaryAdder(res,firstNum,secondNum,0,0);
   int i = 349;
   while(firstNum[i]==0)
      {i--;}
   res[i+1]=0;
}

int compareTo(char* str, char* str2){
   int i = 349;
   while(str[i]==str2[i]){
      i--;
   }
   if (i < 0){
      return 0;
   } else if (str[i] == 1){
      return 1;
   }
   else {
      return -1;
   }

}   
int notZeroDecStr(char * str){
   long max = strlen(str);
   int i = 0; 
   while(i < max) {
      if(str[i]!='0')
         return 1;
      i++;
   }
   return 0;
}

void addFive(char * str,int pos) {
   switch(str[pos]){
      case '4':
         str[pos]='9';
         break;
      case '3':
         str[pos]='8';
         break;
      case '2':
         str[pos]='7';
         break;
      case '1':
         str[pos]='6';
         break;
      case '0':
         str[pos]='5';
         break;
   }
}

void divideStrByTwo(char * str) {
   long max = strlen(str)-1;
   int i = max;
   while(i >= 0){
      switch(str[i]) {
      case '8':
         str[i] = '4';
         break;
      case '6':
         str[i] = '3';
         break;
      case '4':
         str[i] = '2';
         break;
      case '2':
         str[i] = '1';
         break;
      case '0':
         break;
      case '9':
         addFive(str,i+1);
         str[i] = '4';
         break;
      case '7':
         addFive(str,i+1);
         str[i] = '3';
         break;
      case '5':
         addFive(str,i+1);
         str[i] = '2';
         break;
      case '3':
         addFive(str,i+1);
         str[i] = '1';
         break;
      case '1':
         if(i!=max) {
         addFive(str,i+1);
         str[i] = '0';
      }
         break;
      }
      i--;
   }
}
 


char * atob(char * str){
   char * binaryNumRep = calloc(1,350);
   int i = strlen(str)-1;
   int j = 0;
   while (notZeroDecStr(str)){
      unsigned int bit = 0;
      switch(str[i]){
      case '9':
         str[i] = '8';
         bit = 1;
         break;
      case '7':
         str[i] = '6';
         bit = 1;
         break;
      case '5':
         str[i] = '4';
         bit = 1;
         break;
      case '3':
         str[i] = '2';
         bit = 1;
         break;
      case '1':
         str[i] = '0';
         bit = 1;
         break;
      }
      binaryNumRep[j] |= bit;
      divideStrByTwo(str);
      j++;
   }
   return binaryNumRep;
}

void minusOne(char * D){
   int i;
   for(i = 0; D[i]==0;i++){
      D[i]=1;
   }
   D[i]=0;
}

void multiplyByTwo(char* D){
   int i = 349;
   while( i > 0){
      D[i] = D[i-1];
      i--;
   }
   D[0]=0;
}

int magic (char * A, int B, int C, char * D){
   //if A falls in D's range
   if(compareTo(A,D)!= 1){
      //return the bit
      return B;
   } else {
      char * res = calloc(1,350);
      char * Dnew = calloc(1,350);
      memcpy(Dnew,D,350);
      //subtract current Jacobsthal's number from A, save as res
      binarySubtraction(res,A,D);
      free(A);
      free(D);
      //calculate next number in the Jacobsthal sequence
      multiplyByTwo(Dnew);
      //every other time, add one to double current J's number
      //otherwise subtract one
      //C % 2 is used to track this
      if(C%2==0) {
         addBinaryOne(Dnew);
      } else {
         minusOne(Dnew);
      }
      //flip bit
      B = (B == 0? 1 : 0);
      //call with new subtraction result, flipped bit, incremented count
      //and new Jacobsthal number
      return magic(res, B,++C,Dnew);
   }
}

int func(char * firstNum,char*secondNum,char*thirdNum){
   int aVsB = compareTo(firstNum,secondNum);
   int bVsC = compareTo(secondNum,thirdNum);
   int aVsC = compareTo(firstNum,thirdNum);
 /*  printf("avb, %d bvc, %d avc, %d \n",aVsB,bVsC,aVsC);
   printf("following three nums:\n");
   for(int i = 0; i < 10; i ++)
      {printf("%d",firstNum[i]);}
   printf("\n");
      for(int i = 0; i < 10; i ++)
      {printf("%d",secondNum[i]);}
   printf("\n");
   for(int i = 0; i < 10; i ++)
      {printf("%d",thirdNum[i]);}*/
   char * firstSub = calloc(1,350);
   char * secondSub = calloc(1,350);
   char * D = calloc(1,350);
   char * E = calloc(1,350);
   int firstResult;
   int secondResult;
      if(aVsB == 1 && aVsC == 1) {
         if(bVsC == 1){
            char * temp = calloc(1,350);
            memcpy(temp,secondNum,350);
         binarySubtraction(firstSub, firstNum, secondNum);
         binarySubtraction(secondSub, temp, thirdNum);
         }
         else{
            char * temp = calloc(1,350);
            memcpy(temp,thirdNum,350);
            binarySubtraction(firstSub, firstNum, thirdNum);
            binarySubtraction(secondSub, temp, secondNum);
         }
         firstResult = magic(firstSub,1,0,D);
         secondResult = magic(secondSub,1,0,E);
      } else if(bVsC == 1){
         if(aVsC == 1){
            char * temp = calloc(1,350);
            memcpy(temp,firstNum,350);
         binarySubtraction(firstSub, secondNum, firstNum);
         binarySubtraction(secondSub, temp, thirdNum);
         }
         else{
            char * temp = calloc(1,350);
            memcpy(temp,thirdNum,350);
            binarySubtraction(firstSub, secondNum, thirdNum);
            binarySubtraction(secondSub, temp, firstNum);
         }
         firstResult = magic(firstSub,1,0,D);
         secondResult = magic(secondSub,1,0,E);
      } else {
         if(aVsB == 1){
            char * temp = calloc(1,350);
            memcpy(temp,firstNum,350);
            binarySubtraction(firstSub, thirdNum, firstNum);
            binarySubtraction(secondSub, temp, secondNum);
         }
         else{
            char * temp = calloc(1,350);
            memcpy(temp,secondNum,350);
            binarySubtraction(firstSub, thirdNum, secondNum);
            binarySubtraction(secondSub, temp, firstNum);
         }
         firstResult = magic(firstSub,1,0,D);
         secondResult = magic(secondSub,1,0,E);
      }
      //printf("nums: %d %d \n",firstResult,secondResult);
      return firstResult+secondResult;
      //return 0;
      /*if(firstResult && secondResult){
         //printf("Second\n");
         return 1;
      }
      else {
         return 0;
         //printf("First\n");
      }*/
}

int main(int argc, char * argv[])
{
   int max;
   scanf("%d",&max);
   int i = 0;
   while(i < max){
   char * firstInputNum = calloc(1,101);
   char * secondInputNum = calloc(1,101);
   char * thirdInputNum = calloc(1,101);
   scanf("%s %s %s",firstInputNum,secondInputNum,thirdInputNum);
   char * firstNum = atob(firstInputNum);
   char * secondNum = atob(secondInputNum);
   char * thirdNum = atob(thirdInputNum);
   //compute first move
   char * firstCopyOne = calloc(1,350);
   memcpy(firstCopyOne,firstNum,350);
   char * secondCopyOne = calloc(1,350);
   memcpy(secondCopyOne,firstNum,350);
   char * thirdCopyOne = calloc(1,350);
   memcpy(thirdCopyOne,firstNum,350);
   char * firstCopyTwo = calloc(1,350);
   memcpy(firstCopyTwo,secondNum,350);
   char * secondCopyTwo = calloc(1,350);
   memcpy(secondCopyTwo,secondNum,350);
   char * thirdCopyTwo = calloc(1,350);
   memcpy(thirdCopyTwo,secondNum,350);
   char * firstCopyThree = calloc(1,350);
   memcpy(firstCopyThree,thirdNum,350);
   char * secondCopyThree = calloc(1,350);
   memcpy(secondCopyThree,thirdNum,350);
   char * thirdCopyThree = calloc(1,350);
   memcpy(thirdCopyThree,thirdNum,350);

   binaryAdder(firstCopyOne,firstCopyTwo,firstCopyThree,0,0);
   binaryAdder(secondCopyTwo,secondCopyOne,secondCopyThree,0,0);
   binaryAdder(thirdCopyThree,thirdCopyOne,thirdCopyTwo,0,0);
   divideByTwo(firstCopyOne);
   divideByTwo(secondCopyTwo);
   divideByTwo(thirdCopyThree);

   int aVsB = compareTo(firstNum,secondNum);
   int bVsC = compareTo(secondNum,thirdNum);
   int aVsC = compareTo(firstNum,thirdNum);
   if(aVsB == 0 && bVsC == 0 && aVsC == 0){
      printf("Second\n");
   } else if(aVsB == 0 || bVsC == 0 || aVsC == 0) {
      printf("First\n"); 
   } else {
      int threshold = 5;
      if(compareTo(firstCopyOne,secondCopyOne)==0) {
         threshold-=2;
      }
      if(compareTo(secondCopyTwo,thirdCopyTwo)==0) {
         threshold-=2;
      }
      if(compareTo(thirdCopyThree,firstCopyThree)==0) {
         threshold-=2;
      }
      int one = func(firstCopyOne,firstCopyTwo,firstCopyThree);
      int two = func(secondCopyOne,secondCopyTwo,secondCopyThree);
      int three = func(thirdCopyOne,thirdCopyTwo,thirdCopyThree);
      //printf("%d %d %d\n", one,two,three);
      int sum = one + two + three;
      /*printf("one %d\n",one);
      printf("two %d\n",two);
      printf("three %d\n",three);
      printf("Sum %d\n",sum);*/
      if(sum >= threshold){
         printf("Second\n");
      } else {
         printf("First\n"); 
      }
   }
   i++;  
   }
   return 0;
}