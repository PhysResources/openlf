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

#include "clif/clif_vigra.hpp"
#include "clif/subset3d.hpp"

#include "comp_lfwrite.hpp"
#include "openlf.hpp"

using namespace clif;
using namespace vigra;

namespace openlf { namespace components {
  
COMP_LFWrite::COMP_LFWrite()
{
  AddInput_("input");
  AddParameter_("filename", DspParameter(DspParameter::ParamType::String));
  AddParameter_("dataset", DspParameter(DspParameter::ParamType::String));
}

void COMP_LFWrite::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  const std::string *filename;
  const std::string *dataset_name = NULL;
  
  inputs.GetValue(0, in);
  
  filename = GetParameter(0)->GetString();
  if (GetParameter(1))
    dataset_name = GetParameter(1)->GetString();
  
  assert(in);
  assert(filename->size());
  
  ClifFile f;
  f.create(*filename);
  
  Dataset *save_set;
  
  //FIXME error handling
  if (dataset_name)
    save_set = f.createDataset(*dataset_name);
  else
    save_set = f.createDataset("default");
  
  //TODO link
  save_set->append(in->data);
  save_set->writeAttributes();
  
  delete save_set;
}

bool COMP_LFWrite::ParameterUpdating_ (int i, DspParameter const &p)
{
  //we only have two parameters
  if (i >= 2)
    return false;
  
  if (p.Type() != DspParameter::ParamType::String)
    return false;
  
  SetParameter_(i, p);
  return true;
}

}} //namespace openlf::components
