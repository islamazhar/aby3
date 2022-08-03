#pragma once
#include "Sh3Types.h"
#include "Sh3ShareGen.h"
#include "Sh3Runtime.h"
#include "Sh3FixedPoint.h"
#include "aby3/OT/SharedOT.h"

namespace aby3
{
    template<typename ValueType>
    struct TruncationPair
    {
        // the share that should be added before the value being trucnated is revealed.
        //i64Matrix mR;
        eMatrix<ValueType>mR;

        // the share that thsould be subtracted after the value has been truncated.
       // si64Matrix mRTrunc;
        siMatrix<ValueType> mRTrunc;
    };

    template<typename ValueType>
    class Sh3Evaluator
    {
    public:

		void init(u64 partyIdx, block prevSeed, block nextSeed, u64 buffSize = 256);
		void init(u64 partyIdx, CommPkg& comm, block seed, u64 buffSize = 256);

		bool DEBUG_disable_randomization = false;

        //void mul(
        //    CommPkg& comm,
        //    const si64Matrix & A,
        //    const si64Matrix & B,
        //    si64Matrix& C);

        //CompletionHandle asyncMul(
        //    CommPkg& comm,
        //    const si64Matrix& A,
        //    const si64Matrix& B,
        //    si64Matrix& C);

		Sh3Task asyncMul(
			Sh3Task dependency,
			const si<ValueType>& A,
			const si<ValueType>& B,
			si<ValueType>& C);

        Sh3Task asyncMul(
            Sh3Task dependency,
            const siMatrix<ValueType>& A,
            const siMatrix<ValueType>& B,
            siMatrix<ValueType>& C);


		Sh3Task asyncMul(
			Sh3Task dependency,
			const siMatrix<ValueType>& A,
			const siMatrix<ValueType>& B,
			siMatrix<ValueType>& C,
			u64 shift);


		Sh3Task asyncMul(
			Sh3Task dependency,
			const si<ValueType>& A,
			const si<ValueType>& B,
			si<ValueType>& C,
			u64 shift);

        template<Decimal D>
		Sh3Task asyncMul(
			Sh3Task dependency,
			const sf<ValueType, D>& A,
			const sf<ValueType, D>& B,
			sf<ValueType, D>& C)
		{
			return asyncMul(dependency, A.ValueTypeCast(), B.ValueTypeCast(), C.ValueTypeCast(), D);
		}

		template<Decimal D>
		Sh3Task asyncMul(
			Sh3Task dependency,
			const sfMatrix<ValueType, D>& A,
			const sfMatrix<ValueType, D>& B,
			sfMatrix<ValueType, D>& C,
			u64 shift)
		{
			return asyncMul(dependency,A.ValueTypeCast(), B.ValueTypeCast(), C.ValueTypeCast(), D + shift);
		}

		template<Decimal D>
		Sh3Task asyncMul(
			Sh3Task dependency,
			const sfMatrix<ValueType, D>& A,
			const sfMatrix<ValueType, D>& B,
			sfMatrix<ValueType, D>& C)
		{
			return asyncMul(dependency,A.ValueTypeCast(), B.ValueTypeCast(), C.ValueTypeCast(), D);
		}

		Sh3Task asyncMul(
			Sh3Task dep,
			const siMatrix<ValueType>& A,
			const sbMatrix<ValueType>& B,
			siMatrix<ValueType>& C);

		Sh3Task asyncMul(
			Sh3Task dep,
			const ValueType& a,
			const sbMatrix<ValueType>& B,
			siMatrix<ValueType>& C);

        TruncationPair<ValueType> getTruncationTuple(u64 xSize, u64 ySize, u64 d);

        u64 mPartyIdx = -1, mTruncationIdx = 0;
        Sh3ShareGen mShareGen;
		SharedOT mOtPrev, mOtNext;
    };




}