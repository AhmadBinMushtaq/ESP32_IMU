#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================


void initializeIMU();

struct IMU_Values GetIMUvalues();

void sendData(struct IMU_Values);

#endif