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

#include "vigra/convolution.hxx"
#include "vigra/multi_math.hxx"
#include <vigra/mathutil.hxx>
#include "operators.hpp"

#include <cmath>

using namespace vigra::multi_math;

#define OPENLF_OP_CONSTRUCT_PARAMS \

OPENLF_OP_START(OP_Tensor2Orientation, 3, 1, 3, 3)
  
    *out[0] = (*in[1]) * (*in[1]) ;
        
        
    //*out[0] = vigra::tan(vigra::atan2(2*vigra::round(*in[1]*10^10)/10^10, vigra::round(*in[2]*10^10)/10^10 - vigra::round(*in[0]*10^10)/10^10 + 10^(-25)));
    //*out[1] = std::sqrt( \
              (std::round(*in[2]*10^10)/10^10 - std::round(*in[0]*10^10)/10^10) \
             *(std::round(*in[2]*10^10)/10^10 - std::round(*in[0]*10^10)/10^10) \
             + 4*std::round(*in[1]*10^10)/10^10*std::round(*in[1]*10^10)/10^10) \
             / ( std::round(*in[0]*10^10)/10^10 + std::round(*in[2]*10^10)/10^10 + 10^(-25));


OPENLF_OP_END(OP_Tensor2Orientation, 3, 1, 3, 3)
