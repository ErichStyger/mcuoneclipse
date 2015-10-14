// Copyright (c) 2014, 2015, Freescale Semiconductor, Inc.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Freescale Semiconductor, Inc. nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL FREESCALE SEMICONDUCTOR, INC. BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This file contains magnetic calibration functions. It is STRONGLY RECOMMENDED
// that the casual developer NOT TOUCH THIS FILE.  The mathematics behind this file
// is extremely complex, and it will be very easy (almost inevitable) that you screw it
// up.
//
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#include "build.h"
#include "types.h"
#include "SensorTasks.h"
#include "magnetic.h"
#include "matrix.h"

// function resets the magnetometer buffer and magnetic calibration
void fInitMagCalibration(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer)
{
	int8 j, k;	// loop counters

	// initialize the calibration hard and soft iron estimate to null
	f3x3matrixAeqI(pthisMagCal->finvW);
	pthisMagCal->fV[CHX] = pthisMagCal->fV[CHY] = pthisMagCal->fV[CHZ] = 0.0F;
	pthisMagCal->fB = DEFAULTB;
	pthisMagCal->fFitErrorpc = 1000.0F;
	pthisMagCal->iValidMagCal = 0;
	pthisMagCal->iCalInProgress = 0;
	pthisMagCal->iMagCalHasRun = 0;

	// set magnetic buffer index to invalid value -1 to denote invalid
	pthisMagBuffer->iMagBufferCount = 0;
	for (j = 0; j < MAGBUFFSIZEX; j++)
	{
		for (k = 0; k < MAGBUFFSIZEY; k++)
		{
			pthisMagBuffer->index[j][k] = -1;
		}
	}

	// initialize the array of (MAGBUFFSIZEX - 1) elements of 100 * tangents used for buffer indexing
	// entries cover the range 100 * tan(-PI/2 + PI/MAGBUFFSIZEX), 100 * tan(-PI/2 + 2*PI/MAGBUFFSIZEX) to
	// 100 * tan(-PI/2 + (MAGBUFFSIZEX - 1) * PI/MAGBUFFSIZEX).
	// for MAGBUFFSIZEX=12, the entries range in value from -373 to +373
	for (j = 0; j < (MAGBUFFSIZEX - 1); j++)
	{
		pthisMagBuffer->tanarray[j] = (int16) (100.0F * tanf(PI * (-0.5F + (float) (j + 1) / MAGBUFFSIZEX)));
	}

	return;
}

// function updates the magnetic measurement buffer with most recent magnetic data (typically 200Hz)
// the uncalibrated measurements iBs are stored in the buffer but the calibrated measurements iBc are used for indexing.
void iUpdateMagnetometerBuffer(struct MagneticBuffer *pthisMagBuffer, struct MagSensor *pthisMag, int32 loopcounter)
{
	// local variables
	int32 idelta;					// absolute vector distance
	int32 i;						// counter
	int16 itanj, itank;				// indexing accelerometer ratios
	int8 j, k, l, m;				// counters
	int8 itooclose;					// flag denoting measurement is too close to existing ones

	// calculate the magnetometer buffer bins from the tangent ratios
	if (pthisMag->iBcAvg[CHZ] == 0) return;
	itanj = (100 * (int32)pthisMag->iBcAvg[CHX]) / ((int32)pthisMag->iBcAvg[CHZ]);
	itank = (100 * (int32)pthisMag->iBcAvg[CHY]) / ((int32)pthisMag->iBcAvg[CHZ]);
	// map tangent ratios to bins j and k using equal angle bins: C guarantees left to right execution of the test
	// and add an offset of MAGBUFFSIZEX bins to k to mimic atan2 on this ratio
	// j will vary from 0 to MAGBUFFSIZEX - 1 and k from 0 to 2 * MAGBUFFSIZEX - 1
	j = k = 0;
	while ((j < (MAGBUFFSIZEX - 1) && (itanj >= pthisMagBuffer->tanarray[j]))) j++;
	while ((k < (MAGBUFFSIZEX - 1) && (itank >= pthisMagBuffer->tanarray[k]))) k++;
	if (pthisMag->iBcAvg[CHX] < 0) k += MAGBUFFSIZEX;

	// case 1: buffer is full and this bin has a measurement: over-write without increasing number of measurements
	// this is the most common option at run time
	if ((pthisMagBuffer->iMagBufferCount == MAXMEASUREMENTS) && (pthisMagBuffer->index[j][k] != -1))
	{
		// store the fast (unaveraged at typically 200Hz) integer magnetometer reading into the buffer bin j, k
		for (i = CHX; i <= CHZ; i++)
		{
			pthisMagBuffer->iBs[i][j][k] = pthisMag->iBs[i];
		}
		pthisMagBuffer->index[j][k] = loopcounter;
		return;
	} // end case 1

	// case 2: the buffer is full and this bin does not have a measurement: store and retire the oldest
	// this is the second most common option at run time
	if ((pthisMagBuffer->iMagBufferCount == MAXMEASUREMENTS) && (pthisMagBuffer->index[j][k] == -1))
	{		
		// store the fast (unaveraged at typically 200Hz) integer magnetometer reading into the buffer bin j, k
		for (i = CHX; i <= CHZ; i++)
		{
			pthisMagBuffer->iBs[i][j][k] = pthisMag->iBs[i];
		}
		pthisMagBuffer->index[j][k] = loopcounter;

		// set l and m to the oldest active entry and disable it
		i = loopcounter;
		l = m = 0; // to avoid compiler complaint
		for (j = 0; j < MAGBUFFSIZEX; j++)
		{
			for (k = 0; k < MAGBUFFSIZEY; k++)
			{
				// check if the time stamp is older than the oldest found so far (normally fails this test)
				if (pthisMagBuffer->index[j][k] < i)
				{
					// check if this bin is active (normally passes this test)
					if (pthisMagBuffer->index[j][k] != -1)
					{
						// set l and m to the indices of the oldest entry found so far
						l = j;
						m = k;
						// set i to the time stamp of the oldest entry found so far
						i = pthisMagBuffer->index[l][m];
					} // end of test for active
				} // end of test for older
			} // end of loop over k
		} // end of loop over j

		// deactivate the oldest measurement (no need to zero the measurement data)
		pthisMagBuffer->index[l][m] = -1;
		return;
	} // end case 2

	// case 3: buffer is not full and this bin is empty: store and increment number of measurements
	if ((pthisMagBuffer->iMagBufferCount < MAXMEASUREMENTS) && (pthisMagBuffer->index[j][k] == -1))
	{
		// store the fast (unaveraged at typically 200Hz) integer magnetometer reading into the buffer bin j, k
		for (i = CHX; i <= CHZ; i++)
		{
			pthisMagBuffer->iBs[i][j][k] = pthisMag->iBs[i];
		}
		pthisMagBuffer->index[j][k] = loopcounter;
		(pthisMagBuffer->iMagBufferCount)++;
		return;
	} // end case 3

	// case 4: buffer is not full and this bin has a measurement: over-write if close or try to slot in
	// elsewhere if not close to the other measurements so as to create a mesh at power up
	if ((pthisMagBuffer->iMagBufferCount < MAXMEASUREMENTS) && (pthisMagBuffer->index[j][k] != -1))
	{
		// calculate the vector difference between current measurement and the buffer entry
		idelta = 0;
		for (i = CHX; i <= CHZ; i++)
		{
			idelta += abs((int32)pthisMag->iBs[i] - (int32)pthisMagBuffer->iBs[i][j][k]);
		}
		// check to see if the current reading is close to this existing magnetic buffer entry
		if (idelta < MESHDELTACOUNTS)
		{
			// simply over-write the measurement and return
			for (i = CHX; i <= CHZ; i++)
			{
				pthisMagBuffer->iBs[i][j][k] = pthisMag->iBs[i];
			}
			pthisMagBuffer->index[j][k] = loopcounter;
		}
		else
		{
			// reset the flag denoting that the current measurement is close to any measurement in the buffer
			itooclose = 0;
			// to avoid compiler warning
			l = m = 0;
			// loop over the buffer j from 0 potentially up to MAGBUFFSIZEX - 1 
			j = 0;
			while (!itooclose && (j < MAGBUFFSIZEX))
			{
				// loop over the buffer k from 0 potentially up to MAGBUFFSIZEY - 1 
				k = 0;
				while (!itooclose && (k < MAGBUFFSIZEY))
				{
					// check whether this buffer entry already has a measurement or not
					if (pthisMagBuffer->index[j][k] != -1)
					{
						// calculate the vector difference between current measurement and the buffer entry
						idelta = 0;
						for (i = CHX; i <= CHZ; i++)
						{
							idelta += abs((int32)pthisMag->iBs[i] - (int32)pthisMagBuffer->iBs[i][j][k]);
						}
						// check to see if the current reading is close to this existing magnetic buffer entry
						if (idelta < MESHDELTACOUNTS)
						{
							// set the flag to abort the search
							itooclose = 1;
						}
					}
					else
					{
						// store the location of this empty bin for future use
						l = j;
						m = k;
					} // end of test for valid measurement in this bin
					k++;
				} // end of k loop
				j++;
			} // end of j loop

			// if none too close, store the measurement in the last empty bin found and return
			// l and m are guaranteed to be set if no entries too close are detected
			if (!itooclose)
			{
				for (i = CHX; i <= CHZ; i++)
				{
					pthisMagBuffer->iBs[i][l][m] = pthisMag->iBs[i];
				}
				pthisMagBuffer->index[l][m] = loopcounter;
				(pthisMagBuffer->iMagBufferCount)++;
			}
		} // end of test for closeness to current buffer entry
		return;
	} // end case 4

	// this line should be unreachable
	return;
}

// function maps the uncalibrated magnetometer data fBsAvg (uT) onto calibrated averaged data fBcAvg (uT), iBcAvg (counts)
void fInvertMagCal(struct MagSensor *pthisMag, struct MagCalibration *pthisMagCal)
{
	// local variables
	float ftmp[3];					// temporary array
	int8 i; 						// loop counter

	// check for a valid calibration to reduce clock ticks particularly at power on when the 
	// magnetic buffer is being filled as rapidly as possible
	if (pthisMagCal->iValidMagCal)
	{
		// remove the computed hard iron offsets (uT): ftmp[]=fBs[]-V[]
		for (i = CHX; i <= CHZ; i++)
		{
			ftmp[i] = pthisMag->fBsAvg[i] - pthisMagCal->fV[i];
		}
		// remove the computed soft iron offsets (uT and counts): fBc=inv(W)*(fBs[]-V[])
		for (i = CHX; i <= CHZ; i++)
		{
			pthisMag->fBcAvg[i] = pthisMagCal->finvW[i][CHX] * ftmp[CHX] + pthisMagCal->finvW[i][CHY] * ftmp[CHY] + pthisMagCal->finvW[i][CHZ] * ftmp[CHZ];
			pthisMag->iBcAvg[i] = (int16) (pthisMag->fBcAvg[i] * pthisMag->fCountsPeruT);
		}
	}
	else
	{
		// simply set the calibrated reading to the uncalibrated reading
		for (i = CHX; i <= CHZ; i++)
		{
			pthisMag->fBcAvg[i] = pthisMag->fBsAvg[i];
			pthisMag->iBcAvg[i] = pthisMag->iBsAvg[i];
		}
	}

	return;
}

// function runs the magnetic calibration
void fRunMagCalibration(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer, struct MagSensor* pthisMag)
{
	int8 i, j;			// loop counters
	int8 isolver;		// magnetic solver used

	// 4 element calibration case
	if (pthisMagBuffer->iMagBufferCount < MINMEASUREMENTS7CAL)
	{
		// age the existing fit error to avoid one good calibration locking out future updates
		if (pthisMagCal->iValidMagCal)
		{
			pthisMagCal->fFitErrorpc *= (1.0F + (float) INTERVAL4CAL * (float) OVERSAMPLE_RATIO / ((float) SENSORFS * FITERRORAGINGSECS));	
		}
		// call the 4 element matrix inversion calibration
		isolver = 4;
		fUpdateCalibration4INV(pthisMagCal, pthisMagBuffer, pthisMag);
	}
	// 7 element calibration case
	else if (pthisMagBuffer->iMagBufferCount < MINMEASUREMENTS10CAL)
	{
		// age the existing fit error to avoid one good calibration locking out future updates
		if (pthisMagCal->iValidMagCal)
		{
			pthisMagCal->fFitErrorpc *= (1.0F + (float) INTERVAL7CAL * (float) OVERSAMPLE_RATIO / ((float) SENSORFS * FITERRORAGINGSECS));	
		}
		// call the 7 element eigenpair calibration
		isolver = 7;
		fUpdateCalibration7EIG(pthisMagCal, pthisMagBuffer, pthisMag);
	}
	// 10 element calibration case
	else
	{
		// age the existing fit error to avoid one good calibration locking out future updates
		if (pthisMagCal->iValidMagCal)
		{
			pthisMagCal->fFitErrorpc *= (1.0F + (float) INTERVAL10CAL * (float) OVERSAMPLE_RATIO / ((float) SENSORFS * FITERRORAGINGSECS));	
		}
		// call the 10 element eigenpair calibration
		isolver = 10;
		fUpdateCalibration10EIG(pthisMagCal, pthisMagBuffer, pthisMag);
	}

	// the trial geomagnetic field must be in range (earth is 22uT to 67uT)
	if ((pthisMagCal->ftrB >= MINBFITUT) && (pthisMagCal->ftrB <= MAXBFITUT))		
	{
		// always accept the calibration if i) no previous calibration exists ii) the calibration fit is reduced or
		// an improved solver was used giving a good trial calibration (4% or under)
		if ((pthisMagCal->iValidMagCal == 0) ||
				(pthisMagCal->ftrFitErrorpc <= pthisMagCal->fFitErrorpc) ||
				((isolver > pthisMagCal->iValidMagCal) && (pthisMagCal->ftrFitErrorpc <= 4.0F)))
		{
			// accept the new calibration solution
			pthisMagCal->iValidMagCal = isolver;
			pthisMagCal->fFitErrorpc = pthisMagCal->ftrFitErrorpc;
			pthisMagCal->fB = pthisMagCal->ftrB;
			for (i = CHX; i <= CHZ; i++)
			{
				pthisMagCal->fV[i] = pthisMagCal->ftrV[i];
				for (j = CHX; j <= CHZ; j++)
				{
					pthisMagCal->finvW[i][j] = pthisMagCal->ftrinvW[i][j];
				}
			}
		} // end of test to accept the new calibration 
	} // end of test for geomagnetic field strength in range

	// reset the calibration in progress flag to allow writing to the magnetic buffer
	pthisMagCal->iCalInProgress = 0;

	return;
}

// 4 element calibration using 4x4 matrix inverse
void fUpdateCalibration4INV(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer, struct MagSensor *pthisMag)
{
	// local variables
	float fBs2;								// fBs[CHX]^2+fBs[CHY]^2+fBs[CHZ]^2
	float fSumBs4;							// sum of fBs2
	float fscaling;							// set to FUTPERCOUNT * FMATRIXSCALING
	float fE;								// error function = r^T.r
	int16 iOffset[3];						// offset to remove large DC hard iron bias in matrix
	int16 iCount;							// number of measurements counted
	int8 ierror;							// matrix inversion error flag
	int8 i, j, k, l;						// loop counters

	// working arrays for 4x4 matrix inversion
	float *pfRows[4];
	int8 iColInd[4];
	int8 iRowInd[4];
	int8 iPivot[4];

	// compute fscaling to reduce multiplications later
	fscaling = pthisMag->fuTPerCount / DEFAULTB;

	// the trial inverse soft iron matrix invW always equals the identity matrix for 4 element calibration
	f3x3matrixAeqI(pthisMagCal->ftrinvW);

	// zero fSumBs4=Y^T.Y, fvecB=X^T.Y (4x1) and on and above diagonal elements of fmatA=X^T*X (4x4)
	fSumBs4 = 0.0F;
	for (i = 0; i < 4; i++)
	{
		pthisMagCal->fvecB[i] = 0.0F;
		for (j = i; j < 4; j++)
		{
			pthisMagCal->fmatA[i][j] = 0.0F;
		}
	}

	// the offsets are guaranteed to be set from the first element but to avoid compiler error
	iOffset[CHX] = iOffset[CHY] = iOffset[CHZ] = 0;

	// use entries from magnetic buffer to compute matrices
	iCount = 0;
	for (j = 0; j < MAGBUFFSIZEX; j++)
	{
		for (k = 0; k < MAGBUFFSIZEY; k++)
		{
			if (pthisMagBuffer->index[j][k] != -1)
			{
				// use first valid magnetic buffer entry as estimate (in counts) for offset
				if (iCount == 0)
				{
					for (l = CHX; l <= CHZ; l++)
					{
						iOffset[l] = pthisMagBuffer->iBs[l][j][k];
					}
				}

				// store scaled and offset fBs[XYZ] in fvecA[0-2] and fBs[XYZ]^2 in fvecA[3-5]
				for (l = CHX; l <= CHZ; l++)
				{
					pthisMagCal->fvecA[l] = (float)((int32)pthisMagBuffer->iBs[l][j][k] - (int32)iOffset[l]) * fscaling;
					pthisMagCal->fvecA[l + 3] = pthisMagCal->fvecA[l] * pthisMagCal->fvecA[l];
				}

				// calculate fBs2 = fBs[CHX]^2 + fBs[CHY]^2 + fBs[CHZ]^2 (scaled uT^2) 
				fBs2 = pthisMagCal->fvecA[3] + pthisMagCal->fvecA[4] + pthisMagCal->fvecA[5];

				// accumulate fBs^4 over all measurements into fSumBs4=Y^T.Y
				fSumBs4 += fBs2 * fBs2;

				// now we have fBs2, accumulate fvecB[0-2] = X^T.Y =sum(fBs2.fBs[XYZ])
				for (l = CHX; l <= CHZ; l++)
				{
					pthisMagCal->fvecB[l] += pthisMagCal->fvecA[l] * fBs2;
				}

				//accumulate fvecB[3] = X^T.Y =sum(fBs2)
				pthisMagCal->fvecB[3] += fBs2;

				// accumulate on and above-diagonal terms of fmatA = X^T.X ignoring fmatA[3][3]
				pthisMagCal->fmatA[0][0] += pthisMagCal->fvecA[CHX + 3];
				pthisMagCal->fmatA[0][1] += pthisMagCal->fvecA[CHX] * pthisMagCal->fvecA[CHY];
				pthisMagCal->fmatA[0][2] += pthisMagCal->fvecA[CHX] * pthisMagCal->fvecA[CHZ];
				pthisMagCal->fmatA[0][3] += pthisMagCal->fvecA[CHX];
				pthisMagCal->fmatA[1][1] += pthisMagCal->fvecA[CHY + 3];
				pthisMagCal->fmatA[1][2] += pthisMagCal->fvecA[CHY] * pthisMagCal->fvecA[CHZ];
				pthisMagCal->fmatA[1][3] += pthisMagCal->fvecA[CHY];
				pthisMagCal->fmatA[2][2] += pthisMagCal->fvecA[CHZ + 3];
				pthisMagCal->fmatA[2][3] += pthisMagCal->fvecA[CHZ];

				// increment the counter for next iteration
				iCount++;
			}
		}
	}

	// set the last element of the measurement matrix to the number of buffer elements used
	pthisMagCal->fmatA[3][3] = (float) iCount;

	// store the number of measurements accumulated (defensive programming, should never be needed)
	pthisMagBuffer->iMagBufferCount = iCount;

	// use above diagonal elements of symmetric fmatA to set both fmatB and fmatA to X^T.X
	for (i = 0; i < 4; i++)
	{
		for (j = i; j < 4; j++)
		{
			pthisMagCal->fmatB[i][j] = pthisMagCal->fmatB[j][i] = pthisMagCal->fmatA[j][i] = pthisMagCal->fmatA[i][j];
		}
	}

	// calculate in situ inverse of fmatB = inv(X^T.X) (4x4) while fmatA still holds X^T.X
	for (i = 0; i < 4; i++)
	{
		pfRows[i] = pthisMagCal->fmatB[i];
	}
	fmatrixAeqInvA(pfRows, iColInd, iRowInd, iPivot, 4, &ierror);

	// calculate fvecA = solution beta (4x1) = inv(X^T.X).X^T.Y = fmatB * fvecB
	for (i = 0; i < 4; i++)
	{
		pthisMagCal->fvecA[i] = 0.0F;
		for (k = 0; k < 4; k++)
		{
			pthisMagCal->fvecA[i] += pthisMagCal->fmatB[i][k] * pthisMagCal->fvecB[k];
		} 
	} 

	// calculate P = r^T.r = Y^T.Y - 2 * beta^T.(X^T.Y) + beta^T.(X^T.X).beta
	// = fSumBs4 - 2 * fvecA^T.fvecB + fvecA^T.fmatA.fvecA
	// first set P = Y^T.Y - 2 * beta^T.(X^T.Y) = fSumBs4 - 2 * fvecA^T.fvecB
	fE = 0.0F;
	for (i = 0; i < 4; i++)
	{
		fE += pthisMagCal->fvecA[i] * pthisMagCal->fvecB[i];
	}
	fE = fSumBs4 - 2.0F * fE;

	// set fvecB = (X^T.X).beta = fmatA.fvecA	
	for (i = 0; i < 4; i++)
	{
		pthisMagCal->fvecB[i] = 0.0F;
		for (k = 0; k < 4; k++)
		{
			pthisMagCal->fvecB[i] += pthisMagCal->fmatA[i][k] * pthisMagCal->fvecA[k];
		} 
	} 

	// complete calculation of P by adding beta^T.(X^T.X).beta = fvecA^T * fvecB
	for (i = 0; i < 4; i++)
	{
		fE += pthisMagCal->fvecB[i] * pthisMagCal->fvecA[i];
	}

	// compute the hard iron vector (in uT but offset and scaled by FMATRIXSCALING)
	for (l = CHX; l <= CHZ; l++)
	{
		pthisMagCal->ftrV[l] = 0.5F * pthisMagCal->fvecA[l];
	}

	// compute the scaled geomagnetic field strength B (in uT but scaled by FMATRIXSCALING)
	pthisMagCal->ftrB = sqrtf(pthisMagCal->fvecA[3] + pthisMagCal->ftrV[CHX] * pthisMagCal->ftrV[CHX] +
			pthisMagCal->ftrV[CHY] * pthisMagCal->ftrV[CHY] + pthisMagCal->ftrV[CHZ] * pthisMagCal->ftrV[CHZ]);

	// calculate the trial fit error (percent) normalized to number of measurements and scaled geomagnetic field strength
	pthisMagCal->ftrFitErrorpc = sqrtf(fE / (float) pthisMagBuffer->iMagBufferCount) * 100.0F /
			(2.0F * pthisMagCal->ftrB * pthisMagCal->ftrB);

	// correct the hard iron estimate for FMATRIXSCALING and the offsets applied (result in uT)
	for (l = CHX; l <= CHZ; l++)
	{
		pthisMagCal->ftrV[l] = pthisMagCal->ftrV[l] * DEFAULTB + (float)iOffset[l] * pthisMag->fuTPerCount;
	}

	// correct the geomagnetic field strength B to correct scaling (result in uT)
	pthisMagCal->ftrB *= DEFAULTB;
	
	return;
}

// 7 element calibration using direct eigen-decomposition
void fUpdateCalibration7EIG(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer, struct MagSensor *pthisMag)
{
	// local variables
	float det;								// matrix determinant
	float fscaling;							// set to FUTPERCOUNT * FMATRIXSCALING
	float ftmp;								// scratch variable
	int16 iOffset[3];						// offset to remove large DC hard iron bias
	int16 iCount;							// number of measurements counted
	int8 i, j, k, l, m, n;					// loop counters

	// compute fscaling to reduce multiplications later
	fscaling = pthisMag->fuTPerCount / DEFAULTB;

	// the offsets are guaranteed to be set from the first element but to avoid compiler error
	iOffset[CHX] = iOffset[CHY] = iOffset[CHZ] = 0;

	// zero the on and above diagonal elements of the 7x7 symmetric measurement matrix fmatA
	for (m = 0; m < 7; m++)
	{
		for (n = m; n < 7; n++)
		{
			pthisMagCal->fmatA[m][n] = 0.0F;
		}
	}

	// add megnetic buffer entries into product matrix fmatA
	iCount = 0;
	for (j = 0; j < MAGBUFFSIZEX; j++)
	{
		for (k = 0; k < MAGBUFFSIZEY; k++)
		{
			if (pthisMagBuffer->index[j][k] != -1)
			{
				// use first valid magnetic buffer entry as offset estimate (bit counts)
				if (iCount == 0)
				{
					for (l = CHX; l <= CHZ; l++)
					{
						iOffset[l] = pthisMagBuffer->iBs[l][j][k];
					}
				}

				// apply the offset and scaling and store in fvecA
				for (l = CHX; l <= CHZ; l++)
				{
					pthisMagCal->fvecA[l + 3] = (float)((int32)pthisMagBuffer->iBs[l][j][k] - (int32)iOffset[l]) * fscaling;
					pthisMagCal->fvecA[l] = pthisMagCal->fvecA[l + 3] * pthisMagCal->fvecA[l + 3];
				}

				// accumulate the on-and above-diagonal terms of pthisMagCal->fmatA=Sigma{fvecA^T * fvecA}
				// with the exception of fmatA[6][6] which will sum to the number of measurements
				// and remembering that fvecA[6] equals 1.0F
				// update the right hand column [6] of fmatA except for fmatA[6][6]
				for (m = 0; m < 6; m++)
				{
					pthisMagCal->fmatA[m][6] += pthisMagCal->fvecA[m];
				}
				// update the on and above diagonal terms except for right hand column 6
				for (m = 0; m < 6; m++)
				{
					for (n = m; n < 6; n++)
					{
						pthisMagCal->fmatA[m][n] += pthisMagCal->fvecA[m] * pthisMagCal->fvecA[n];
					}
				}

				// increment the measurement counter for the next iteration
				iCount++;
			}
		}
	}

	// finally set the last element fmatA[6][6] to the number of measurements
	pthisMagCal->fmatA[6][6] = (float) iCount;

	// store the number of measurements accumulated (defensive programming, should never be needed)
	pthisMagBuffer->iMagBufferCount = iCount;

	// copy the above diagonal elements of fmatA to below the diagonal
	for (m = 1; m < 7; m++)
	{
		for (n = 0; n < m; n++)
		{
			pthisMagCal->fmatA[m][n] = pthisMagCal->fmatA[n][m];
		}
	}

	// set tmpA7x1 to the unsorted eigenvalues and fmatB to the unsorted eigenvectors of fmatA
	eigencompute10(pthisMagCal->fmatA, pthisMagCal->fvecA, pthisMagCal->fmatB, 7);

	// find the smallest eigenvalue
	j = 0;
	for (i = 1; i < 7; i++)
	{
		if (pthisMagCal->fvecA[i] < pthisMagCal->fvecA[j])
		{
			j = i;
		}
	}

	// set ellipsoid matrix A to the solution vector with smallest eigenvalue, compute its determinant
	// and the hard iron offset (scaled and offset)
	f3x3matrixAeqScalar(pthisMagCal->fA, 0.0F);
	det = 1.0F;
	for (l = CHX; l <= CHZ; l++)
	{
		pthisMagCal->fA[l][l] = pthisMagCal->fmatB[l][j];
		det *= pthisMagCal->fA[l][l];
		pthisMagCal->ftrV[l] = -0.5F * pthisMagCal->fmatB[l + 3][j] / pthisMagCal->fA[l][l];
	}

	// negate A if it has negative determinant
	if (det < 0.0F)
	{
		f3x3matrixAeqMinusA(pthisMagCal->fA);
		pthisMagCal->fmatB[6][j] = -pthisMagCal->fmatB[6][j];
		det = -det;
	}

	// set ftmp to the square of the trial geomagnetic field strength B (counts times FMATRIXSCALING)
	ftmp = -pthisMagCal->fmatB[6][j];
	for (l = CHX; l <= CHZ; l++)
	{
		ftmp += pthisMagCal->fA[l][l] * pthisMagCal->ftrV[l] * pthisMagCal->ftrV[l];
	}

	// calculate the trial normalized fit error as a percentage
	pthisMagCal->ftrFitErrorpc = 50.0F * sqrtf(fabsf(pthisMagCal->fvecA[j]) / (float) pthisMagBuffer->iMagBufferCount) / fabsf(ftmp);

	// normalize the ellipsoid matrix A to unit determinant
	f3x3matrixAeqAxScalar(pthisMagCal->fA, powf(det, -(ONETHIRD)));

	// convert the geomagnetic field strength B into uT for normalized soft iron matrix A and normalize
	pthisMagCal->ftrB = sqrtf(fabsf(ftmp)) * DEFAULTB * powf(det, -(ONESIXTH));

	// compute trial invW from the square root of A also with normalized determinant and hard iron offset in uT
	f3x3matrixAeqI(pthisMagCal->ftrinvW);
	for (l = CHX; l <= CHZ; l++)
	{
		pthisMagCal->ftrinvW[l][l] = sqrtf(fabsf(pthisMagCal->fA[l][l]));
		pthisMagCal->ftrV[l] = pthisMagCal->ftrV[l] * DEFAULTB + (float)iOffset[l] * pthisMag->fuTPerCount;
	}

	return;
}

// 10 element calibration using direct eigen-decomposition
void fUpdateCalibration10EIG(struct MagCalibration *pthisMagCal, struct MagneticBuffer *pthisMagBuffer, struct MagSensor *pthisMag)
{
	// local variables
	float det;								// matrix determinant
	float fscaling;							// set to FUTPERCOUNT * FMATRIXSCALING
	float ftmp;								// scratch variable
	int16 iOffset[3];						// offset to remove large DC hard iron bias in matrix
	int16 iCount;							// number of measurements counted
	int8 i, j, k, l, m, n;					// loop counters

	// compute fscaling to reduce multiplications later
	fscaling = pthisMag->fuTPerCount / DEFAULTB;

	// the offsets are guaranteed to be set from the first element but to avoid compiler error
	iOffset[CHX] = iOffset[CHY] = iOffset[CHZ] = 0;

	// zero the on and above diagonal elements of the 10x10 symmetric measurement matrix fmatA
	for (m = 0; m < 10; m++)
	{
		for (n = m; n < 10; n++)
		{
			pthisMagCal->fmatA[m][n] = 0.0F;
		}
	}

	// add magnetic buffer entries into the 10x10 product matrix fmatA
	iCount = 0;
	for (j = 0; j < MAGBUFFSIZEX; j++)
	{
		for (k = 0; k < MAGBUFFSIZEY; k++)
		{
			if (pthisMagBuffer->index[j][k] != -1)
			{
				// use first valid magnetic buffer entry as estimate for offset to help solution (bit counts)
				if (iCount == 0)
				{
					for (l = CHX; l <= CHZ; l++)
					{
						iOffset[l] = pthisMagBuffer->iBs[l][j][k];
					}
				}

				// apply the fixed offset and scaling and enter into fvecA[6-8]
				for (l = CHX; l <= CHZ; l++)
				{
					pthisMagCal->fvecA[l + 6] = (float)((int32)pthisMagBuffer->iBs[l][j][k] - (int32)iOffset[l]) * fscaling;
				}

				// compute measurement vector elements fvecA[0-5] from fvecA[6-8]
				pthisMagCal->fvecA[0] = pthisMagCal->fvecA[6] * pthisMagCal->fvecA[6];
				pthisMagCal->fvecA[1] = 2.0F * pthisMagCal->fvecA[6] * pthisMagCal->fvecA[7];
				pthisMagCal->fvecA[2] = 2.0F * pthisMagCal->fvecA[6] * pthisMagCal->fvecA[8];
				pthisMagCal->fvecA[3] = pthisMagCal->fvecA[7] * pthisMagCal->fvecA[7];
				pthisMagCal->fvecA[4] = 2.0F * pthisMagCal->fvecA[7] * pthisMagCal->fvecA[8];
				pthisMagCal->fvecA[5] = pthisMagCal->fvecA[8] * pthisMagCal->fvecA[8];

				// accumulate the on-and above-diagonal terms of fmatA=Sigma{fvecA^T * fvecA}
				// with the exception of fmatA[9][9] which equals the number of measurements
				// update the right hand column [9] of fmatA[0-8][9] ignoring fmatA[9][9]
				for (m = 0; m < 9; m++)
				{
					pthisMagCal->fmatA[m][9] += pthisMagCal->fvecA[m];
				}
				// update the on and above diagonal terms of fmatA ignoring right hand column 9
				for (m = 0; m < 9; m++)
				{
					for (n = m; n < 9; n++)
					{
						pthisMagCal->fmatA[m][n] += pthisMagCal->fvecA[m] * pthisMagCal->fvecA[n];
					}
				}

				// increment the measurement counter for the next iteration
				iCount++;
			}
		}
	}

	// set the last element fmatA[9][9] to the number of measurements
	pthisMagCal->fmatA[9][9] = (float) iCount;

	// store the number of measurements accumulated (defensive programming, should never be needed)
	pthisMagBuffer->iMagBufferCount = iCount;

	// copy the above diagonal elements of symmetric product matrix fmatA to below the diagonal
	for (m = 1; m < 10; m++)
	{
		for (n = 0; n < m; n++)
		{
			pthisMagCal->fmatA[m][n] = pthisMagCal->fmatA[n][m];
		}
	}

	// set pthisMagCal->fvecA to the unsorted eigenvalues and fmatB to the unsorted normalized eigenvectors of fmatA
	eigencompute10(pthisMagCal->fmatA, pthisMagCal->fvecA, pthisMagCal->fmatB, 10);

	// set ellipsoid matrix A from elements of the solution vector column j with smallest eigenvalue
	j = 0;
	for (i = 1; i < 10; i++)
	{
		if (pthisMagCal->fvecA[i] < pthisMagCal->fvecA[j])
		{
			j = i;
		}
	}
	pthisMagCal->fA[0][0] = pthisMagCal->fmatB[0][j];
	pthisMagCal->fA[0][1] = pthisMagCal->fA[1][0] = pthisMagCal->fmatB[1][j];
	pthisMagCal->fA[0][2] = pthisMagCal->fA[2][0] = pthisMagCal->fmatB[2][j];
	pthisMagCal->fA[1][1] = pthisMagCal->fmatB[3][j];
	pthisMagCal->fA[1][2] = pthisMagCal->fA[2][1] = pthisMagCal->fmatB[4][j];
	pthisMagCal->fA[2][2] = pthisMagCal->fmatB[5][j];

	// negate entire solution if A has negative determinant
	det = f3x3matrixDetA(pthisMagCal->fA);
	if (det < 0.0F)
	{
		f3x3matrixAeqMinusA(pthisMagCal->fA);
		pthisMagCal->fmatB[6][j] = -pthisMagCal->fmatB[6][j];
		pthisMagCal->fmatB[7][j] = -pthisMagCal->fmatB[7][j];
		pthisMagCal->fmatB[8][j] = -pthisMagCal->fmatB[8][j];
		pthisMagCal->fmatB[9][j] = -pthisMagCal->fmatB[9][j];
		det = -det;
	}

	// compute the inverse of the ellipsoid matrix
	f3x3matrixAeqInvSymB(pthisMagCal->finvA, pthisMagCal->fA);

	// compute the trial hard iron vector in offset bit counts times FMATRIXSCALING
	for (l = CHX; l <= CHZ; l++)
	{
		pthisMagCal->ftrV[l] = 0.0F;
		for (m = CHX; m <= CHZ; m++)
		{
			pthisMagCal->ftrV[l] += pthisMagCal->finvA[l][m] * pthisMagCal->fmatB[m + 6][j];
		}
		pthisMagCal->ftrV[l] *= -0.5F;
	}

	// compute the trial geomagnetic field strength B in bit counts times FMATRIXSCALING
	pthisMagCal->ftrB = sqrtf(fabsf(pthisMagCal->fA[0][0] * pthisMagCal->ftrV[CHX] * pthisMagCal->ftrV[CHX] +
			2.0F * pthisMagCal->fA[0][1] * pthisMagCal->ftrV[CHX] * pthisMagCal->ftrV[CHY] +
			2.0F * pthisMagCal->fA[0][2] * pthisMagCal->ftrV[CHX] * pthisMagCal->ftrV[CHZ] +
			pthisMagCal->fA[1][1] * pthisMagCal->ftrV[CHY] * pthisMagCal->ftrV[CHY] +
			2.0F * pthisMagCal->fA[1][2] * pthisMagCal->ftrV[CHY] * pthisMagCal->ftrV[CHZ] +
			pthisMagCal->fA[2][2] * pthisMagCal->ftrV[CHZ] * pthisMagCal->ftrV[CHZ] - pthisMagCal->fmatB[9][j]));

	// calculate the trial normalized fit error as a percentage
	pthisMagCal->ftrFitErrorpc = 50.0F * sqrtf(fabsf(pthisMagCal->fvecA[j]) / (float) pthisMagBuffer->iMagBufferCount) /
			(pthisMagCal->ftrB * pthisMagCal->ftrB);

	// correct for the measurement matrix offset and scaling and get the computed hard iron offset in uT
	for (l = CHX; l <= CHZ; l++)
	{
		pthisMagCal->ftrV[l] = pthisMagCal->ftrV[l] * DEFAULTB + (float)iOffset[l] * pthisMag->fuTPerCount;
	}

	// convert the trial geomagnetic field strength B into uT for un-normalized soft iron matrix A
	pthisMagCal->ftrB *= DEFAULTB;

	// normalize the ellipsoid matrix A to unit determinant and correct B by root of this multiplicative factor
	f3x3matrixAeqAxScalar(pthisMagCal->fA, powf(det, -(ONETHIRD)));
	pthisMagCal->ftrB *= powf(det, -(ONESIXTH));

	// compute trial invW from the square root of fA (both with normalized determinant)	
	// set fvecA to the unsorted eigenvalues and fmatB to the unsorted eigenvectors of fmatA
	// where fmatA holds the 3x3 matrix fA in its top left elements
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			pthisMagCal->fmatA[i][j] = pthisMagCal->fA[i][j];
		}
	}
	eigencompute10(pthisMagCal->fmatA, pthisMagCal->fvecA, pthisMagCal->fmatB, 3);

	// set pthisMagCal->fmatB to be eigenvectors . diag(sqrt(sqrt(eigenvalues))) = fmatB . diag(sqrt(sqrt(fvecA))
	for (j = 0; j < 3; j++) // loop over columns j
	{
		ftmp = sqrtf(sqrtf(fabsf(pthisMagCal->fvecA[j])));
		for (i = 0; i < 3; i++) // loop over rows i
		{
			pthisMagCal->fmatB[i][j] *= ftmp;
		}
	}

	// set ftrinvW to eigenvectors * diag(sqrt(eigenvalues)) * eigenvectors^T
	// = fmatB * fmatB^T = sqrt(fA) (guaranteed symmetric)
	// loop over rows
	for (i = 0; i < 3; i++)
	{
		// loop over on and above diagonal columns
		for (j = i; j < 3; j++)
		{
			pthisMagCal->ftrinvW[i][j] = 0.0F;
			// accumulate the matrix product
			for (k = 0; k < 3; k++)
			{
				pthisMagCal->ftrinvW[i][j] += pthisMagCal->fmatB[i][k] * pthisMagCal->fmatB[j][k];
			}
			// copy to below diagonal element
			pthisMagCal->ftrinvW[j][i] = pthisMagCal->ftrinvW[i][j];
		}
	}

	return;
}
