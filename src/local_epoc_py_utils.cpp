//
// Copyright 2004 Helsinki Institute for Information Technology (HIIT)
// and the authors.	 All rights reserved.
//
// Authors: Tero Hasu <tero.hasu@hut.fi>
//

// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation files
// (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge,
// publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "local_epoc_py_utils.h"

TInt ConstructType(const PyTypeObject* aTypeTemplate,
		   char* aClassName)
{
  PyTypeObject* typeObj = PyObject_New(PyTypeObject, &PyType_Type);
  if (!typeObj)
    // error set already, but telling caller also
    return KErrNoMemory;

  *typeObj = *aTypeTemplate; // fill in from a template
  typeObj->ob_type = &PyType_Type; // fill in the missing bit
  
  // PyDict_SetItemString returns 0 on success, and -1 on failure,
  // which is similar to enough to the Symbian error scheme that
  // we don't need to know which is being used
  TInt error = SPyAddGlobalString(aClassName, 
				  reinterpret_cast<PyObject*>(typeObj));
  if (error < 0)
    {
      PyObject_Del(typeObj);
      SPyErr_SetFromSymbianOSErr(error);
      return error;
    }

  return KErrNone;
}