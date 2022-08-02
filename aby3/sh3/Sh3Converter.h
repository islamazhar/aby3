#pragma once

#include "Sh3Types.h"
#include "Sh3Runtime.h"
#include "aby3/Circuit/CircuitLibrary.h"
#include "Sh3ShareGen.h"
namespace aby3
{

    template<typename  ValueType>
    class Sh3Converter
    {
    public:
        CircuitLibrary mLib;

        void toPackedBin(const sbMatrix<ValueType>& in, sPackedBin& dest);

        void toBinaryMatrix(const sPackedBin& in, sbMatrix<ValueType>& dest);

        Sh3Task toPackedBin(Sh3Task dep, Sh3ShareGen& gen, const si64Matrix& in, sPackedBin& dest);
        Sh3Task toBinaryMatrix(Sh3Task dep, const si64Matrix& in, sbMatrix<ValueType>& dest);

        Sh3Task toSi64Matrix(Sh3Task dep, const sbMatrix<ValueType>& in, si64Matrix& dest);
        Sh3Task toSi64Matrix(Sh3Task dep, const sPackedBin& in, si64Matrix& dest);
    };
}