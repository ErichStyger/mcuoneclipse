/*
 * Copyright (c) 2021-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "car.hh"
#include <stdlib.h> // for exit()

class Car {
  private: int price;
  public:
      Car(void) { // constructor
        price = 1000;
      }
      ~Car(void) { // destructor
        price = -1;
      }
      void SetPrice(int price) { // setter method
        this->price = price;
      }
};

// global variables
static Car c; // global object, shall be initialized by startup (constructor)
static int i; // initialized by startup (zero-out)
static int j = 0x1234; // initialized by startup (copy-down)

void CAR_Test(void) {
  Car newCar; // local object: constructor called?

  c.SetPrice(i+1000);
  newCar.SetPrice(j);
  // destructors of newCar called?
}

extern "C" {
    extern void __libc_fini_array(void);
}

void CAR_Exit(void) {
  __libc_fini_array();
  exit(-1); // force application exit, global destructors called?
}
