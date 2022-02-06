

#include <SafeString.h>

void setup() {
  Serial.begin(9600);

  createSafeString(appCmd, 50);  // large enought for the largest cmd
  createSafeString(token1, 20);
  createSafeString(token2, 20);
  createSafeString(token3, 20);
  appCmd = "['255','4','16']";
  size_t nextIdx = 1; //step over leading {
  nextIdx = appCmd.stoken(token1, nextIdx, "',");
  nextIdx++; //step over delimiter
  nextIdx = appCmd.stoken(token2, nextIdx, "',");
  nextIdx++; //step over delimiter
  nextIdx = appCmd.stoken(token3, nextIdx, "',");
  nextIdx++; //step over delimiter
  // can trim tokens if needed e.g. token1.trim()
  Serial.println(token1);
  Serial.println(token2); 
  Serial.println(token3);
}

void loop() {
}
