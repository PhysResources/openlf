/*
* Copyright (c) 2015 Heidelberg Collaboratory for Image Processing
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of
* this software and associated documentation files (the "Software"), to deal in
* the Software without restriction, including without limitation the rights to use,
* copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
* Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Author Sven Wanner, Maximilian Diebold, Hendrick Siedelmann 
*
*/

#include <vigra/convolution.hxx>
#include <vigra/multi_convolution.hxx>
#include "operators.hpp"

#define OPENLF_OP_CONSTRUCT_PARAMS \

OPENLF_OP_START(OP_Scharr, 1, 2, 3, 3)
        
    Kernel1D<float> D;
    D.initExplicitly(-1,1) = -1.0/2.0, 0.0, 1.0/2.0;
    D.setBorderTreatment(BORDER_TREATMENT_REFLECT);
    Kernel1D<float> S;
    S.initExplicitly(-1,1) = 3.0/16.0, 10.0/16.0, 3.0/16.0;
    S.setBorderTreatment(BORDER_TREATMENT_REFLECT);
                
    convolveMultiArrayOneDimension(*in[0], *out[0], 1, D);
    convolveMultiArrayOneDimension(*out[0], *out[0], 0, S);
    
    convolveMultiArrayOneDimension(*in[0], *out[1], 0, D);
    convolveMultiArrayOneDimension(*out[1], *out[1], 0, S);
    
OPENLF_OP_END(OP_Scharr, 1, 2, 3, 3)
