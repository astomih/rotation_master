/* Copyright 2022 iwatake2222

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef CONVERTER_H
#define CONVERTER_H

/*** Include ***/
#include <cstdint>
#include <cstdio>
#include <vector>

#include "container.h"

namespace Converter
{
    void UpdateInput(InputContainer& input_container, OutputContainer& output_container);
    void Convert(InputContainer& input_container, OutputContainer& output_container);
    void ResetValue(InputContainer& input_container, OutputContainer& output_container);
};

#endif