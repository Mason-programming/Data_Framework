#include <pybind11/pybind11.h>
#include "processCommand.h"

namespace py = pybind11;

PYBIND11_MODULE(processbridge, m) {
    py::class_<ProcessCommand>(m, "ProcessCommand")
        .def(py::init<std::string, std::string, std::string>())
        .def("launch", &ProcessCommand::launch)
        .def("getProcessInfo", &ProcessCommand::getProcessInfo);
}
