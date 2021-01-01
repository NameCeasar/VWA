#pragma once

char* toString(int number) {
  bool neg = number < 0;
  if(neg) number *= -1;
  int len = 1;
  int pow = 1;
  for(; number >= (pow * 10); pow *= 10) len++; 
  char out[len + (neg?2:1)];
  out[len+(neg?1:0)] = 0;
  if(neg) out[0] = 0x2D;
  for(int i = 0; i < len; i++) {
    out[neg?(i+1):i] = (char) ((number / pow) % 10) + 0x30;
    pow /= 10;
  } char* ptr = out;
  return ptr;
}