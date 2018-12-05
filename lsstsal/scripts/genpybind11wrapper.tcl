#include <string>
#include <typeinfo>
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "SAL_m2ms.h"

// use std::array or py::array_t<type> name

namespace py = pybind11;

PYBIND11_PLUGIN(SALPY_m2ms) {
    py::module m("SALPY_m2ms");

// INSERT_SAL_PYTHON_DATATYPES
// INSERT CMDALIAS SUPPORT  for issueCommand and acceptCommand  
// INSERT EVENTALIAS SUPPORT 
// INSERT_SAL_PYTHON_GETPUT

    py::class_< m2ms_logeventC >(m, "m2ms_logeventC" )
        .def(py::init<>())
        .def_readwrite( "message", &m2ms_logeventC::message )    
        ;

    return m.ptr();
}


