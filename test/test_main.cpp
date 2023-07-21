#ifdef ARDUINO  
#include <Arduino.h>   // needed for service delay
#endif

#include <unity.h>

#include "LinearCalib.h"



void setUp(void) 
{
  // set stuff up here
}

void tearDown(void) 
{
  // clean stuff up here
}



void test_static_map(void) 
{
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, LinearCalib::map(0.0, 0.0, 256.0, 0.0, 1.0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, LinearCalib::map(128.0, 0.0, 256.0, 0.0, 1.0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, LinearCalib::map(256.0, 0.0, 256.0, 0.0, 1.0));  
  TEST_ASSERT_FLOAT_WITHIN(0.01, 128.0, LinearCalib::map(0.5, 1.0, 0.0, 0.0, 256.0));
}



void test_unconfigured_class(void) 
{
  LinearCalib myCalib;
  float m, n;

  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, myCalib.calc(0.0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, myCalib.calc(0.5));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, myCalib.calc(1.0));  
  TEST_ASSERT_FLOAT_WITHIN(0.01, 128.0, myCalib.calc(128.0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, -128.0, myCalib.calc(-128.0));

  myCalib.getParams(&m, &n);
  TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, m);  
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, n);  
}



void test_set_params(void) 
{
  LinearCalib myCalib(-10.0, -2.0);
  float m, n;

  myCalib.getParams(&m, &n);
  TEST_ASSERT_FLOAT_WITHIN(0.01, -10.0, m);  
  TEST_ASSERT_FLOAT_WITHIN(0.01, -2.0, n);

  myCalib.setParams(2.0, 1.0);
  myCalib.getParams(&m, &n);
  TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, m);  
  TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, n);

  TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, myCalib.calc(0.0));  

}



void test_calc_params(void) 
{
  LinearCalib myCalib;
  float m, n;

  TEST_ASSERT_EQUAL_INT(0, myCalib.setParams(0.0, 1.0, 0.0, 256.0));
  myCalib.getParams(&m, &n);
  TEST_ASSERT_FLOAT_WITHIN(0.01, 256.0, m);  
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, n);

  myCalib.setParams(0.0, 1.0, -1.0, 0.0);
  myCalib.getParams(&m, &n);
  TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, m);  
  TEST_ASSERT_FLOAT_WITHIN(0.01, -1.0, n);

  myCalib.setParams(0.5, 1.3, 0.0, 1.0);
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, myCalib.calc(0.5));  
  TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, myCalib.calc(0.9));  
  TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, myCalib.calc(1.3));       
}



void test_shit(void) 
{
  LinearCalib myCalib;
  
  TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, LinearCalib::map(2.0, 0.0, 0.0, 0.0, 0.0));

  TEST_ASSERT_EQUAL_INT(-1, myCalib.setParams(1.0, 1.0, 1.0, 1.0));
  TEST_ASSERT_FLOAT_WITHIN(0.01, 4711.0, myCalib.calc(4711.0));
}



void setup()
{
#ifdef ARDUINO
  delay(2000); // service delay
#endif

  UNITY_BEGIN();

  RUN_TEST(test_static_map);
  RUN_TEST(test_unconfigured_class);
  RUN_TEST(test_set_params);
  RUN_TEST(test_calc_params);
  RUN_TEST(test_shit);

  UNITY_END(); // stop unit testing
}



void loop()
{
}



#ifndef ARDUINO
// only needed if unit test is running in an native environment
int main(int argc, char *argv[])
{
  setup();
  loop();
  return 0;
}
#endif