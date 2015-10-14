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
#ifndef ORIENTATION_H
#define ORIENTATION_H
              
#include "SensorTasks.h"

// function prototypes
void f3DOFTiltNED(float fR[][3], float fGs[]);
void f3DOFTiltAndroid(float fR[][3], float fGs[]);
void f3DOFTiltWin8(float fR[][3], float fGs[]);
void f3DOFMagnetometerMatrixNED(float fR[][3], float fBc[]);
void f3DOFMagnetometerMatrixAndroid(float fR[][3], float fBc[]);
void f3DOFMagnetometerMatrixWin8(float fR[][3], float fBc[]);
void feCompassNED(float fR[][3], float *pfDelta, float fBc[], float fGs[]);
void feCompassAndroid(float fR[][3], float *pfDelta, float fBc[], float fGs[]);
void feCompassWin8(float fR[][3], float *pfDelta, float fBc[], float fGs[]);

void fLeastSquareseCompassNED(struct fquaternion *pfq, float fB, float fDelta, float fsinDelta, float fcosDelta,
		float *pfDelta6DOF, float fBc[], float fGs[], float *pfQvB, float *pfQvG);
void fLeastSquareseCompassAndroid(struct fquaternion *pfq, float fB, float fDelta, float fsinDelta, float fcosDelta,
		float *pfDelta6DOF, float fBc[], float fGs[], float *pfQvB, float *pfQvG);
void fLeastSquareseCompassWin8(struct fquaternion *pfq, float fB, float fDelta, float fsinDelta, float fcosDelta,
		float *pfDelta6DOF, float fBc[], float fGs[], float *pfQvB, float *pfQvG);

void fNEDAnglesDegFromRotationMatrix(float R[][3], float *pfPhiDeg, float *pfTheDeg, float *pfPsiDeg, float *pfRhoDeg, float *pfChiDeg);
void fAndroidAnglesDegFromRotationMatrix(float R[][3], float *pfPhiDeg, float *pfTheDeg, float *pfPsiDeg, float *pfRhoDeg, float *pfChiDeg);
void fWin8AnglesDegFromRotationMatrix(float R[][3], float *pfPhiDeg, float *pfTheDeg, float *pfPsiDeg, float *pfRhoDeg, float *pfChiDeg);
void fQuaternionFromRotationMatrix(float R[][3], struct fquaternion *pq);
void fRotationMatrixFromQuaternion(float R[][3], const struct fquaternion *pq);
void qAeqBxC(struct fquaternion *pqA, const struct fquaternion *pqB, const struct fquaternion *pqC);
void qAeqAxB(struct fquaternion *pqA, const struct fquaternion *pqB);
struct fquaternion qconjgAxB(const struct fquaternion *pqA, const struct fquaternion *pqB);
void fqAeqNormqA(struct fquaternion *pqA);
void fqAeq1(struct fquaternion *pqA);
void fQuaternionFromRotationVectorDeg(struct fquaternion *pq, const float rvecdeg[], float fscaling);
void fRotationVectorDegFromQuaternion(struct fquaternion *pq, float rvecdeg[]);
void fLPFOrientationQuaternion(struct fquaternion *pq, struct fquaternion *pLPq, float flpf, float fdeltat, float fOmega[]);
void fveqconjgquq(struct fquaternion *pfq, float fu[], float fv[]);

#endif   // #ifndef ORIENTATION_H
