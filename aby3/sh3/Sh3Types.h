#pragma once
#include <aby3/Common/Defines.h>
//#include <cryptoTools/Common/Matrix.h>
#include <Eigen/Dense>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Common/Matrix.h>

namespace aby3
{


    struct CommPkg {
        oc::Channel mPrev, mNext;
    };

    template<typename T>
    using eMatrix = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
    using i64Matrix = eMatrix<i64>;
    using i32Matrix = eMatrix<i32>;

    namespace details
    {

        bool areEqualImpl(
                const std::array<oc::MatrixView<u8>, 2>& a,
                const std::array<oc::MatrixView<u8>, 2>& b,
                u64 bitCount);


        template<typename T>
        bool areEqual(
                const std::array<oc::MatrixView<T>, 2>& a,
                const std::array<oc::MatrixView<T>, 2>& b,
                u64 bitCount)
        {
            std::array<oc::MatrixView<u8>, 2> aa;
            std::array<oc::MatrixView<u8>, 2> bb;

            static_assert(std::is_pod<T>::value, "");
            aa[0] = oc::MatrixView<u8>((u8*)a[0].data(), a[0].rows(), a[0].cols() * sizeof(T));
            aa[1] = oc::MatrixView<u8>((u8*)a[1].data(), a[1].rows(), a[1].cols() * sizeof(T));
            bb[0] = oc::MatrixView<u8>((u8*)b[0].data(), b[0].rows(), b[0].cols() * sizeof(T));
            bb[1] = oc::MatrixView<u8>((u8*)b[1].data(), b[1].rows(), b[1].cols() * sizeof(T));

            return areEqualImpl(aa, bb, bitCount);
        }
        template<typename T>
        bool areEqual(
                const std::array<oc::Matrix<T>, 2>& a,
                const std::array<oc::Matrix<T>, 2>& b,
                u64 bitCount)
        {

            std::array<oc::MatrixView<T>, 2> aa{ a[0], a[1] };
            std::array<oc::MatrixView<T>, 2> bb{ b[0], b[1] };

            return areEqual(aa, bb, bitCount);
        }

        void trimImpl(oc::MatrixView<u8> a, u64 bits);
        template<typename T>
        void trim(oc::MatrixView<T> a, i64 bits)
        {
            static_assert(std::is_pod<T>::value, "");
            oc::MatrixView<u8> aa((u8*)a.data(), a.rows(), a.cols() * sizeof(T));
            trimImpl(aa, bits);
        }
    }
    template<typename  T>
    struct si;

    // a reference to a si 64 bit integer (stored in a matrix).
    template<typename ShareType>
    struct Ref
    {
        friend ShareType;
        using ref_value_type = typename ShareType::value_type;

        std::array<ref_value_type*, 2> mData;


        Ref(ref_value_type& a0, ref_value_type& a1)
        {
            mData[0] = &a0;
            mData[1] = &a1;
        }

        const ShareType& operator=(const ShareType& copy);
        ref_value_type& operator[](u64 i) { return *mData[i]; }
        const ref_value_type& operator[](u64 i) const { return *mData[i]; }

    };


    // a shared 32 or 64 bit integer.
    template<typename ValueType>
    struct si
    {
        using value_type = ValueType;
        std::array<value_type, 2> mData;

        si() = default;
        si(const si&) = default;
        si(si&&) = default;
        si(const std::array<value_type, 2>& d) :mData(d) {}
        si(const Ref<si>& s) {
            mData[0] = *s.mData[0];
            mData[1] = *s.mData[1];
        }

        si& operator=(const si& copy);
        si operator+(const si& rhs) const;
        si operator-(const si& rhs) const;

        value_type& operator[](u64 i) { return mData[i]; }
        const value_type& operator[](u64 i) const { return mData[i]; }
    };


    // a shared 32 or 64 bit binary value
    template<typename ValueType>
    struct sb
    {
        using value_type = ValueType;
        std::array<value_type , 2> mData;

        sb() = default;
        sb(const sb&) = default;
        sb(sb&&) = default;
        sb(const std::array<value_type, 2>& d) :mData(d) {}

        ValueType& operator[](u64 i) { return mData[i]; }
        const ValueType& operator[](u64 i) const { return mData[i]; }


        sb& operator=(const sb& copy) = default;
        sb operator^(const sb& x) { return { { mData[0] ^ x.mData[0], mData[1] ^ x.mData[1] } }; }

    };

    template<typename ValueType>
    struct siMatrix
    {
        std::array<eMatrix<ValueType>, 2> mShares;

        struct ConstRow { const siMatrix& mMtx; const u64 mIdx; };

        struct Row { siMatrix& mMtx; const u64 mIdx; const Row& operator=(const Row& row); const ConstRow& operator=(const ConstRow& row); };

        struct ConstCol { const siMatrix& mMtx; const u64 mIdx; };
        struct Col { siMatrix& mMtx; const u64 mIdx; const Col& operator=(const Col& col); const ConstCol& operator=(const ConstCol& row); };

        siMatrix() = default;
        siMatrix(u64 xSize, u64 ySize)
        {
            resize(xSize, ySize);
        }

        void resize(u64 xSize, u64 ySize)
        {
            mShares[0].resize(xSize, ySize);
            mShares[1].resize(xSize, ySize);
        }


        u64 rows() const { return mShares[0].rows(); }
        u64 cols() const { return mShares[0].cols(); }
        u64 size() const { return mShares[0].size(); }

        Ref<si<ValueType>> operator()(u64 x, u64 y) const;
        Ref<si<ValueType>> operator()(u64 xy) const;
        siMatrix operator+(const siMatrix& B) const;
        siMatrix operator-(const siMatrix& B) const;

        siMatrix transpose() const;
        void transposeInPlace();


        Row row(u64 i);
        Col col(u64 i);
        ConstRow row(u64 i) const;
        ConstCol col(u64 i) const;

        bool operator !=(const siMatrix& b) const
        {
            return !(*this == b);
        }

        bool operator ==(const siMatrix& b) const
        {
            return (rows() == b.rows() &&
                    cols() == b.cols() &&
                    mShares == b.mShares);
        }

        eMatrix<ValueType>& operator[](u64 i) { return mShares[i]; }
        const eMatrix<ValueType>& operator[](u64 i) const { return mShares[i]; }
    };


    template<typename ValueType>
    struct sbMatrix
    {
        std::array<oc::Matrix<ValueType>, 2> mShares;
        u64 mBitCount = 0;
        //struct ConstRow { const si64Matrix& mMtx; const u64 mIdx; };
        //struct Row { si64Matrix& mMtx; const u64 mIdx; const Row& operator=(const Row& row); const ConstRow& operator=(const ConstRow& row); };

        //struct ConstCol { const si64Matrix& mMtx; const u64 mIdx; };
        //struct Col { si64Matrix& mMtx; const u64 mIdx; const Col& operator=(const Col& col); const ConstCol& operator=(const ConstCol& row); };

        sbMatrix() = default;
        sbMatrix(u64 xSize, u64 ySize)
        {
            resize(xSize, ySize);
        }

        void resize(u64 xSize, u64 bitCount)
        {
            mBitCount = bitCount;
            auto ySize = (bitCount + 63) / 64;
            mShares[0].resize(xSize, ySize, oc::AllocType::Uninitialized);
            mShares[1].resize(xSize, ySize, oc::AllocType::Uninitialized);
        }


        u64 rows() const { return mShares[0].rows(); }
        u64 i64Size() const { return mShares[0].size(); }
        u64 i64Cols() const { return mShares[0].cols(); }
        u64 bitCount() const { return mBitCount; }

        bool operator !=(const sbMatrix& b) const
        {
            return !(*this == b);
        }

        bool operator ==(const sbMatrix& b) const
        {
            return (rows() == b.rows() &&
                    bitCount() == b.bitCount() &&
                    details::areEqual(mShares, b.mShares, bitCount()));
        }

        void trim()
        {
            for (auto i = 0ull; i < mShares.size(); ++i)
            {
                details::trim(mShares[i], bitCount());
            }
        }
    };


    // Represents a packed set of binary secrets. Data is stored in a tranposed format.
    // The 'ith bit of all the shares are packed together into the i'th row. This allows
    // efficient SIMD operations. E.g. applying bit[0] = bit[1] ^ bit[2] to all the shares
    // can be performed to 64 shares using one instruction.
    template<typename T>
    struct sPackedBinBase
    {
        static_assert(std::is_pod<T>::value, "must be pod");
        u64 mShareCount;

        std::array<oc::MatrixView<T>, 2> mShares;
        std::unique_ptr<u8[]> mBacking;

        sPackedBinBase() = default;
        sPackedBinBase(u64 shareCount, u64 bitCount, u64 wordMultiple = 1)
        {
            reset(shareCount, bitCount, wordMultiple);
        }

        //void resize(u64 shareCount, u64 bitCount, u64 wordMultiple = 1)
        //{
        //    mShareCount = shareCount;
        //    auto bitsPerWord = 8 * sizeof(T);
        //    auto wordCount = (shareCount + bitsPerWord - 1) / bitsPerWord;
        //    wordCount = oc::roundUpTo(wordCount, wordMultiple);

        //    auto oldBacking = mBacking;
        //    auto old = mShares;

        //    mShares[0].resize(bitCount, wordCount, oc::AllocType::Uninitialized);
        //    mShares[1].resize(bitCount, wordCount, oc::AllocType::Uninitialized);
        //}

        // resize without copy
        void reset(u64 shareCount, u64 bitCount, u64 wordMultiple = 1)
        {

            auto bitsPerWord = 8 * sizeof(T);
            auto wordCount = (shareCount + bitsPerWord - 1) / bitsPerWord;
            wordCount = oc::roundUpTo(wordCount, wordMultiple);


            if (shareCount != mShareCount || wordCount != mShares[0].stride())
            {
                mShareCount = shareCount;

                auto sizeT = bitCount * wordCount;
                std::size_t sizeBytes = (sizeT + 1) * sizeof(T);
                auto totalT = 2 * sizeT + 1; // plus one to make sure we have enought space for aligned storage.

                mBacking.reset(new u8[totalT * sizeof(T)]);

                void* ptr = reinterpret_cast<void*>(mBacking.get());
                auto alignment = alignof(T);

                if (!std::align(alignment, sizeT * sizeof(T), ptr, sizeBytes))
                    throw RTE_LOC;

                T* aligned0 = static_cast<T*>(ptr);
                T* aligned1 = aligned0 + sizeT;

                mShares[0] = oc::MatrixView<T>(aligned0, bitCount, wordCount);
                mShares[1] = oc::MatrixView<T>(aligned1, bitCount, wordCount);
            }

        }

        u64 size() const { return mShares[0].size(); }

        // the number of shares that are stored in this packed (shared) binary matrix.
        u64 shareCount() const { return mShareCount; }

        // the number of bits that each share has.
        u64 bitCount() const { return mShares[0].rows(); }

        // the number of i64s in each row = divCiel(mShareCount, 8 * sizeof(i64))
        u64 simdWidth() const { return mShares[0].cols(); }

        sPackedBinBase<T> operator^(const sPackedBinBase<T>& rhs)
        {
            if (shareCount() != rhs.shareCount() || bitCount() != rhs.bitCount())
                throw std::runtime_error(LOCATION);

            sPackedBinBase<T> r(shareCount(), bitCount());
            for (u64 i = 0; i < 2; ++i)
            {
                for (u64 j = 0; j < mShares[0].size(); ++j)
                {
                    r.mShares[i](j) = mShares[i](j) ^ rhs.mShares[i](j);
                }
            }
            return r;
        }

        bool operator!=(const sPackedBinBase<T>& b) const
        {
            return !(*this == b);
        }

        bool operator==(const sPackedBinBase<T>& b) const
        {
            return (shareCount() == b.shareCount() &&
                    bitCount() == b.bitCount() &&
                    details::areEqual(mShares, b.mShares, shareCount()));
        }

        void trim()
        {
            for (auto i = 0; i < mShares.size(); ++i)
            {
                oc::MatrixView<T>s(mShares[i].data(), mShares[i].rows(), mShares[i].cols());
                details::trim(s, shareCount());
            }
        }

    };

    using sPackedBin = sPackedBinBase<i64>;
    using sPackedBin128 = sPackedBinBase<block>;

    template<typename T = i64>
    struct PackedBinBase
    {
        static_assert(std::is_pod<T>::value, "must be pod");
        u64 mShareCount;

        oc::Matrix<T> mData;

        PackedBinBase() = default;
        PackedBinBase(u64 shareCount, u64 bitCount, u64 wordMultiple = 1)
        {
            resize(shareCount, bitCount, wordMultiple);
        }

        void resize(u64 shareCount, u64 bitCount, u64 wordMultiple = 1)
        {
            mShareCount = shareCount;
            auto bitsPerWord = 8 * sizeof(T);
            auto wordCount = (shareCount + bitsPerWord - 1) / bitsPerWord;
            wordCount = oc::roundUpTo(wordCount, wordMultiple);
            mData.resize(bitCount, wordCount, oc::AllocType::Uninitialized);
        }

        u64 size() const { return mData.size(); }

        // the number of shares that are stored in this packed (shared) binary matrix.
        u64 shareCount() const { return mShareCount; }

        // the number of bits that each share has.
        u64 bitCount() const { return mData.rows(); }

        // the number of i64s in each row = divCiel(mShareCount, 8 * sizeof(i64))
        u64 simdWidth() const { return mData.cols(); }

        PackedBinBase<T> operator^(const PackedBinBase<T>& rhs)
        {
            if (shareCount() != rhs.shareCount() || bitCount() != rhs.bitCount())
                throw std::runtime_error(LOCATION);

            PackedBinBase<T> r(shareCount(), bitCount());
            for (u64 j = 0; j < mData.size(); ++j)
            {
                r.mData(j) = mData(j) ^ rhs.mData(j);
            }
            return r;
        }

        void trim()
        {
            details::trim(mData, shareCount());
        }
    };

    using PackedBin = PackedBinBase<i64>;
    using PackedBin128 = PackedBinBase<block>;


    template<typename T>
    inline const T& Ref<T>::operator=(const T & copy)
    {
        mData[0] = (ref_value_type*)&copy.mData[0];
        mData[1] = (ref_value_type*)&copy.mData[1];
        return copy;
    }

    template<typename  ValueType>
    inline si<ValueType>& si<ValueType>::operator=(const si<ValueType>& copy)
    {
        mData[0] = copy.mData[0];
        mData[1] = copy.mData[1];
        return *this;
    }
    template<typename  ValueType>
    inline si<ValueType> si<ValueType>::operator+(const si& rhs) const
    {
        si<ValueType> ret;
        ret.mData[0] = mData[0] + rhs.mData[0];
        ret.mData[1] = mData[1] + rhs.mData[1];
        return ret;
    }

    template<typename  ValueType>
    inline si<ValueType> si<ValueType>::operator-(const si& rhs) const
    {
        si<ValueType> ret;
        ret.mData[0] = mData[0] - rhs.mData[0];
        ret.mData[1] = mData[1] - rhs.mData[1];
        return ret;
    }
    template<typename  ValueType>
    inline Ref<si<ValueType>> siMatrix<ValueType>::operator()(u64 x, u64 y) const
    {
        return Ref<si<ValueType>>(
                (ValueType&)mShares[0](x, y),
                (ValueType&)mShares[1](x, y));
    }

    template<typename ValueType>
    inline Ref<si<ValueType>> siMatrix<ValueType>::operator()(u64 xy) const
    {
        return Ref<si<ValueType>>(
                (ValueType&)mShares[0](xy),
                (ValueType&)mShares[1](xy));
    }

    template<typename ValueType>
    inline siMatrix<ValueType> siMatrix<ValueType>::operator+(const siMatrix<ValueType>& B) const
    {
        siMatrix<ValueType> ret;
        ret.mShares[0] = mShares[0] + B.mShares[0];
        ret.mShares[1] = mShares[1] + B.mShares[1];
        return ret;
    }

    template<typename ValueType>
    inline siMatrix<ValueType> siMatrix<ValueType>::operator-(const siMatrix<ValueType>& B) const
    {
        siMatrix<ValueType> ret;
        ret.mShares[0] = mShares[0] - B.mShares[0];
        ret.mShares[1] = mShares[1] - B.mShares[1];
        return ret;
    }

    template<typename  ValueType>
    inline siMatrix<ValueType> siMatrix<ValueType>::transpose() const
    {
        siMatrix<ValueType> ret;
        ret.mShares[0] = mShares[0].transpose();
        ret.mShares[1] = mShares[1].transpose();
        return ret;
    }

    template<typename  ValueType>
    inline void siMatrix<ValueType>::transposeInPlace()
    {
        mShares[0].transposeInPlace();
        mShares[1].transposeInPlace();
    }

    template<typename  ValueType>
    inline typename siMatrix<ValueType>::Row siMatrix<ValueType>::row(u64 i)
    {
        return Row{ *this, i };
    }

    template<typename  ValueType>
    inline typename siMatrix<ValueType>::ConstRow siMatrix<ValueType>::row(u64 i) const
    {
        return ConstRow{ *this, i };
    }

    template<typename  ValueType>
    inline typename siMatrix<ValueType>::Col siMatrix<ValueType>::col(u64 i)
    {
        return Col{ *this, i };
    }

    template<typename  ValueType>
    inline typename siMatrix<ValueType>::ConstCol siMatrix<ValueType>::col(u64 i) const
    {
        return ConstCol{ *this, i };
    }

    template<typename ValueType>
    inline  const typename siMatrix<ValueType>::Row & siMatrix<ValueType>::Row::operator=(const Row & row)
    {
        mMtx.mShares[0].row(mIdx) = row.mMtx.mShares[0].row(row.mIdx);
        mMtx.mShares[1].row(mIdx) = row.mMtx.mShares[1].row(row.mIdx);

        return row;
    }

    template<typename  ValueType>
    inline const typename  siMatrix<ValueType>::ConstRow & siMatrix<ValueType>::Row::operator=(const ConstRow & row)
    {
        mMtx.mShares[0].row(mIdx) = row.mMtx.mShares[0].row(row.mIdx);
        mMtx.mShares[1].row(mIdx) = row.mMtx.mShares[1].row(row.mIdx);
        return row;
    }
    template<typename ValueType>
    inline const typename  siMatrix<ValueType>::Col & siMatrix<ValueType>::Col::operator=(const Col & col)
    {
        mMtx.mShares[0].col(mIdx) = col.mMtx.mShares[0].col(col.mIdx);
        mMtx.mShares[1].col(mIdx) = col.mMtx.mShares[1].col(col.mIdx);
        return col;
    }

    template<typename ValueType>
    inline const typename siMatrix<ValueType>::ConstCol & siMatrix<ValueType>::Col::operator=(const ConstCol & col)
    {
        mMtx.mShares[0].col(mIdx) = col.mMtx.mShares[0].col(col.mIdx);
        mMtx.mShares[1].col(mIdx) = col.mMtx.mShares[1].col(col.mIdx);
        return col;
    }

    using si64 = si<i64>;
    using sb64 = sb<i64>;
    using si64Matrix = siMatrix<i64>;
    using sbi64Matrix = sbMatrix<i64>;
}