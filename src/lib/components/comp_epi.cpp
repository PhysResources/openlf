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

#include "comp_epi.hpp"

#include "clif/subset3d.hpp"
#include "clif/clif_vigra.hpp"


using namespace clif;
using namespace vigra;

namespace openlf { namespace components {
  
EpiCircuit::EpiCircuit()
{
  AddInput_("input");
  AddOutput_("output");
  
  _circuit.AddComponent(_source, "source");
  _circuit.AddComponent(_sink, "sink");
}
  
void EpiCircuit::set(DspCircuit *circuit)
{
  if (_epi_circuit)
    _circuit.RemoveComponent(_epi_circuit);
  
  _epi_circuit = circuit;
  _circuit.AddComponent(_epi_circuit, "epi_circuit");
}

void EpiCircuit::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
  LF *in = NULL;
  LF *out = NULL;
  
  inputs.GetValue(0, in);
  //FIXME Hendrik: create linked copy of input in->dataset
  //out = ...
  //maybe an internal clif::Dataset? What does DSPatch recommend?
  outputs.SetValue(0, out);
  
  assert(_epi_circuit);
  assert(in);
  assert(out);
  
  //TODO get settings using DSPatch routines...
  double disparity = 10;
  int subset_idx = 0; //we could also loop over all subsets or specify subset using string name
  
  Subset3d *subset = new Subset3d(in->dataset, subset_idx);
  
  for(int c=0;c<in->dataset->channels();c++)
    for(int i=0;i<subset->EPICount();i++) {
      readEPI(subset, c, _source_mav, i, disparity);
      
      //tick the circuit to fill _sink_mav using _source_mav and the circuit
      _circuit.Tick();
      
      //TODO accumulate _sink_mav into whatever we want (e.g. center-view disparity)
    }
  //TODO store whatever we accumulated into the clif file 
}

}} //namespace openlf::components
