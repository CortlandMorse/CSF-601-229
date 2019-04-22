#include <unistd.h>
#include <stdio.h>
#define STDIN 0//stdin for fd
#define STDOUT 1//stdout for fd

/* Format of output line:
aaaa  hh hh hh hh hh hh hh hh  cccccccc\n
*/

/* You may want to use this */
char hex2asc[17]="0123456789ABCDEF";

//function adds address to beginning of writebuffer in hex
void wbuf_add(unsigned char wbuf[], int cur) {
  for (int i = 3; i >= 0; i--) {
    wbuf[i] = hex2asc[cur%16];//take cur and calculate/write hex value
    cur /= 16;//prepare next hex calculation
  }

  wbuf[4] = ' '; wbuf[5] = ' ';//adds space between address & charhex
}

//function converts ascii integer values to hex
void wbuf_charhex(unsigned char rbuf[], unsigned char wbuf[], int len) {
  int wi = 6;//writebuffer index init
  for (int i = 0; i < 8; i++) {
    if (i >= len) {//when there are less than 8 values to write
      wbuf[wi] = ' ';
      wbuf[wi+1] = ' ';
    } else {//this section writes the values
      int val = (int)rbuf[i];//convert char to int
      wbuf[wi+1] = hex2asc[val%16];//hex pos2
      val /= 16;
      wbuf[wi] = hex2asc[val%16];//hex pos1
    }
    wbuf[wi+2] = ' ';//adds end space
    wbuf[wi+3] = ' ';
    wi += 3;//increments writebuffer index
  }
}

//writes ascii values at end of line
void wbuf_ascii(unsigned char rbuf[], unsigned char wbuf[], int len) {
  for (int i = 0; i < 8; i++) {
    if (i >= len) {//when less than 8 chars to convert
      wbuf[31+i] = ' ';
    } else {//converts char values
      int val = (int)rbuf[i];//gets ascii int value
      if (val < 32 || val > 126) {
        wbuf[31+i] = '.';//shows unprintable characters as dots
      } else {
        wbuf[31+i] = (unsigned char)val;//adds ascii character to wbuffer
      }
    }
  }
}

int main() {
  unsigned char rbuf[8];//initializing read buffer
  unsigned char wbuf[40];//initializing write buffer
  wbuf[39] = '\n';//adds newline to end of writebuffer, done once
  int rd = read(STDIN, rbuf, 8);//first read value
  int ad = 0;//address initializer
  while (rd > 0) {
    wbuf_add(wbuf, ad);//calls address writer
    ad += rd;
    wbuf_charhex(rbuf, wbuf, rd);//calls hexvalue writer
    wbuf_ascii(rbuf, wbuf, rd);// calls ascii writer
    if (rd < 8) {//activates when less than 8 values to write
      wbuf[31+rd] = '\n';
      write(STDOUT, wbuf, 32+rd);
    } else {//activates when there are 8 values to write
      write(STDOUT, wbuf, 40);
    }

    rd = read(STDIN, rbuf, 8);//reads next batch
  }

  if (rd < 0) {//activates when error in read
    return 1;
  }

  return 0;//end
}
