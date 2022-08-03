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

        Sh3Task toPackedBin(Sh3Task dep, Sh3ShareGen& gen, const siMatrix<ValueType>& in, sPackedBin& dest);
        Sh3Task toBinaryMatrix(Sh3Task dep, const siMatrix<ValueType>& in, sbMatrix<ValueType>& dest);

        Sh3Task toSiMatrix(Sh3Task dep, const sbMatrix<ValueType>& in, siMatrix<ValueType>& dest); // not implemented
        Sh3Task toSiMatrix(Sh3Task dep, const sPackedBin& in, siMatrix<ValueType>& dest); // not implemented
    };
}