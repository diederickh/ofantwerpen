/*
 *  untitled.h
 *  emptyExample
 *
 *  Created by Dries De Roeck on 14/07/11.
 *  Copyright 2011 Cloudboy. All rights reserved.
 *
 */
string word;
int counter;

word = "the score is ";
word.append(ofToString(counter));
unsigned char* c_word = (unsigned char*)word.c_str();
mySerial.writeByte(0x01);
int len = word.size();

mySerial.writeByte(len);
for (int i = 0; i<len; i++) {
	mySerial.writeByte(c_word[i]);
}

mySerial.writeByte(0x02);
counter++;
}