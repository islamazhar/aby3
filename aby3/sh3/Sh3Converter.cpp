#include "Sh3Converter.h"
#include <libOTe/Tools/Tools.h>
#include "Sh3BinaryEvaluator.h"

using namespace oc;

namespace aby3
{


    template<typename  ValueType>
    void Sh3Converter<ValueType>::toPackedBin(const sbMatrix<ValueType> & in, sPackedBin & dest)
    {
        dest.reset(in.rows(), in.bitCount());

        for (u64 i = 0; i < 2; ++i)
        {
            auto& s = in.mShares[i];
            auto& d = dest.mShares[i];

            MatrixView<u8> inView(
                (u8*)(s.data()),
                (u8*)(s.data() + s.size()),
                sizeof(ValueType) * s.cols());
            
            MatrixView<u8> memView(
                (u8*)(d.data()),
                (u8*)(d.data() + d.size()),
                sizeof(ValueType) * d.cols());

            transpose(inView, memView);
        }
    }
    template<typename  ValueType>
    void Sh3Converter<ValueType>::toBinaryMatrix(const sPackedBin & in, sbMatrix<ValueType> & dest)
    {
        dest.resize(in.shareCount(), in.bitCount());

        for (u64 i = 0; i < 2; ++i)
        {
            auto& s = in.mShares[i];
            auto& d = dest.mShares[i];

            MatrixView<u8> inView(
                (u8*)(s.data()),
                (u8*)(s.data() + s.size()),
                sizeof(ValueType) * s.cols());

            MatrixView<u8> memView(
                (u8*)(d.data()),
                (u8*)(d.data() + d.size()),
                sizeof(ValueType) * d.cols());

            transpose(inView, memView);
        }
    }
    template<typename  ValueType>
    Sh3Task Sh3Converter<ValueType>::toPackedBin(Sh3Task dep, Sh3ShareGen& gen, const siMatrix<ValueType>& in, sPackedBin& dest)
    {
        return dep.then([&](CommPkg & comm, Sh3Task self) {
            struct State {
                Sh3BinaryEvaluator mEval;
                //oc::BetaCircuit mCircuit;
            };

            auto state = std::make_unique<State>();
            state->mEval.setCir(mLib.convert_arith_to_bin(in.cols(), 64), in.rows(), gen);

            throw RTE_LOC;
            //state->mEval.setInput
            //for(u64 i =0; i < in.)

        });
    }

}