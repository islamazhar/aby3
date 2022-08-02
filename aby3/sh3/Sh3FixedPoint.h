#pragma once
#include <aby3/Common/Defines.h>
#include <aby3/sh3/Sh3Types.h>
namespace aby3
{

	enum Decimal
	{
		// this represents number of bits representing the fractional part
		D0 = 0,
		D8 = 8,
		D16 = 16,
		D32 = 32
	};


	struct monostate {};



	template<typename ValueType, Decimal D>
	struct fp
	{

		static const Decimal mDecimal = D;

		ValueType mValue = 0;

		fp() = default;
		fp(const fp&) = default;
		fp(fp&&) = default;
		fp(const double v) {
			*this = v;
		}

		fp operator+(const fp& rhs) const {
			return { mValue + rhs.mValue, monostate{} };
		}

		fp operator-(const fp& rhs) const {
			return { mValue - rhs.mValue, monostate{} };
		}
		fp operator*(const fp& rhs) const;
		fp operator>>(ValueType shift) const { return { mValue >> shift, monostate{} }; }
		fp operator<<(ValueType shift) const { return { mValue << shift, monostate{} }; }


		fp& operator+=(const fp& rhs) {
			mValue += rhs.mValue;
			return *this;
		}

		fp& operator-=(const fp& rhs) {
			mValue -= rhs.mValue;
			return*this;
		}
		fp& operator*=(const fp& rhs) {
			*this = *this * rhs;
			return *this;
		}


		fp& operator=(const fp& v) = default;

		explicit operator double() const
		{
			return mValue / double(ValueType(1) << mDecimal);
		}

		void operator=(const double& v)
		{
			mValue = ValueType(v * (ValueType(1) << D));
		}

		bool operator==(const fp & v) const
		{
			return mValue == v.mValue;
		}
		bool operator!=(const fp & v) const
		{
			return !(*this == v);
		}

	private:
		fp(ValueType v, monostate)
			: mValue(v)
		{}
	};




	template<Decimal D>
	using f64 = fp<i64, D>; // remove this??

	template<typename ValueType, Decimal D>
	std::ostream& operator<<(std::ostream & o, const fp<ValueType, D> & f)
	{
		auto mask = ((1ull << f.mDecimal) - 1);
		std::stringstream ss;
		u64 v;
		if (f.mValue >= 0)
			v = f.mValue;
		else
		{
			ss << '-';
			v = -f.mValue;
		}

		ss << (v >> f.mDecimal) << ".";


		v &= mask;
		if (v)
		{
			while (v & mask)
			{
				v *= 10;
				ss << (v >> f.mDecimal);
				v &= mask;
			}
		}
		else
		{
			ss << '0';
		}

		o << ss.str();
		return o;
	}

	;


	template<typename ValueType, Decimal D>
	struct fpMatrix
	{
		using value_type = fp<ValueType, D>;
		static const Decimal mDecimal = D;
		eMatrix<value_type> mData;

		fpMatrix() = default;
		fpMatrix(const fpMatrix<ValueType, D>&) = default;
		fpMatrix(fpMatrix<ValueType, D>&&) = default;

		fpMatrix(u64 xSize, u64 ySize)
			: mData(xSize, ySize)
		{}

		void resize(u64 xSize, u64 ySize)
		{
			mData.resize(xSize, ySize);
		}


		u64 rows() const { return mData.rows(); }
		u64 cols() const { return mData.cols(); }
		u64 size() const { return mData.size(); }


		const fpMatrix<ValueType, D>& operator=(const fpMatrix<ValueType, D>& rhs)
		{
			mData = rhs.mData;
			return rhs;
		}


		fpMatrix<ValueType, D> operator+(const fpMatrix<ValueType, D>& rhs) const
		{
			return { mData + rhs.mData };
		}
		fpMatrix<ValueType, D> operator-(const fpMatrix<ValueType, D>& rhs) const
		{
			return { mData - rhs.mData };
		}
		fpMatrix<ValueType, D> operator*(const fpMatrix<ValueType, D>& rhs) const
		{
			fpMatrix<ValueType, D> ret;
			eMatrix<ValueType>& view = ret.i64Cast();
			const eMatrix<ValueType>& l = ValueTypeCast();
			const eMatrix<ValueType>& r = rhs.ValueTypeCast();
			view = l * r;
			for (u64 i = 0; i < view.size(); ++i)
				view(i) >>= mDecimal;
			return ret;
		}

		fpMatrix<ValueType, D>& operator+=(const fpMatrix<ValueType, D> & rhs)
		{
			mData += rhs.mData;
			return *this;
		}
		fpMatrix<ValueType, D>& operator-=(const fpMatrix<ValueType, D> & rhs)
		{
			mData -= rhs.mData;
			return *this;
		}

		fpMatrix<ValueType, D>& operator*=(const fpMatrix<ValueType, D> & rhs)
		{
			auto& view = ValueTypeCast();
			view *= rhs.ValueTypeCast();
			for (u64 i = 0; i < size(); ++i)
				view(i) >>= mDecimal;
			return *this;
		}


		value_type& operator()(u64 x, u64 y) { return mData(x, y); }
		value_type& operator()(u64 xy) { return mData(xy); }
		const value_type& operator()(u64 x, u64 y) const { return mData(x, y); }
		const value_type& operator()(u64 xy)const { return mData(xy); }


		eMatrix<ValueType>& ValueTypeCast()
		{
			static_assert(sizeof(value_type) == sizeof(ValueType), "required for this operation");
			return reinterpret_cast<eMatrix<ValueType>&>(mData);
		}
		const eMatrix<ValueType>& ValueTypeCast() const
		{
			static_assert(sizeof(value_type) == sizeof(ValueType), "required for this operation");
			return reinterpret_cast<const eMatrix<ValueType>&>(mData);
		}
	private:
		fpMatrix(const eMatrix<value_type> & v)
			:mData(v) {}
		fpMatrix(eMatrix<value_type> && v)
			:mData(std::forward<eMatrix<value_type>>(v)) {}
	};

	template<Decimal D>
	using f64Matrix = fpMatrix<i64, D>;

	template<typename T, Decimal D>
	std::ostream& operator<<(std::ostream & o, const fpMatrix<T, D> & f)
	{
		o << '[';
		for (u64 i = 0; i < f.rows(); ++i)
		{
			o << '(';
			if (f.cols())
				o << f(i, 0);

			for (u64 j = 1; j < f.cols(); ++j)
				o << ", " << f(i, j);

			o << ")\n";
		}
		o << ']';
		return o;
	}



	template<typename  ValueType, Decimal D>
	struct sf
	{
		// `s` refers to encrypted values like secret-shared 
		static const Decimal mDecimal = D;

		using value_type = ValueType;
		si<i64> mShare;

		sf() = default;
		sf(const sf<ValueType, D>&) = default;
		sf(sf<ValueType, D>&&) = default;
		sf(const std::array<value_type, 2>& d) :mShare(d) {}
		sf(const Ref<sf<ValueType, D>>& s) {
			mShare.mData[0] = *s.mData[0];
			mShare.mData[1] = *s.mData[1];
		}

		sf<ValueType, D>& operator=(const sf<ValueType, D>& copy)
		{
			mShare = copy.mShare;
			return *this;
		}

		sf<ValueType, D> operator+(const sf<ValueType, D>& rhs) const
		{
			sf<ValueType, D> r;
			r.mShare = mShare + rhs.mShare;
			return r;
		}
		sf<ValueType, D> operator-(const sf<ValueType, D>& rhs) const
		{
			sf<ValueType, D> r;
			r.mShare = mShare - rhs.mShare;
			return r;
		}

		value_type& operator[](u64 i) { return mShare[i]; }
		const value_type& operator[](u64 i) const { return mShare[i]; }


		si<ValueType>& ValueTypeCast() { return mShare; };
		const si<ValueType>& ValueTypeCast() const { return mShare; };
	};

    template<Decimal D>
    using sf64 = sf<i64, D>; // this `using` must be in the header file.





	template<typename ValueType, Decimal D>
	struct sfMatrix : public siMatrix<ValueType>
	{
		static const Decimal mDecimal = D;
        using  siMatrix<ValueType>::mShares;
		
		struct ConstRow { const sfMatrix<ValueType, D>& mMtx; const u64 mIdx; };
		struct Row { sfMatrix<ValueType, D>& mMtx; const u64 mIdx;  const Row& operator=(const Row& row); const ConstRow& operator=(const ConstRow& row); };

		struct ConstCol { const sfMatrix<ValueType, D>& mMtx; const u64 mIdx; };
		struct Col { sfMatrix<ValueType, D>& mMtx; const u64 mIdx; const Col& operator=(const Col& col); const ConstCol& operator=(const ConstCol& row); };

		sfMatrix() = default;
		sfMatrix(u64 xSize, u64 ySize)
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

		Ref<sf<ValueType, D>> operator()(u64 x, u64 y)
		{
			typename sf<ValueType, D>::value_type& s0 = mShares[0](x, y);
			typename sf<ValueType, D>::value_type& s1 = mShares[1](x, y);

			return Ref<sf<ValueType, D>>(s0, s1);
		}

		Ref<sf<ValueType, D>> operator()(u64 xy)
		{
			auto& s0 = static_cast<typename sf<ValueType, D>::value_type&>(mShares[0](xy));
			auto& s1 = static_cast<typename sf<ValueType, D>::value_type&>(mShares[1](xy));

			return Ref<sf<ValueType, D>>(s0, s1);
		}

		const sfMatrix<ValueType, D>& operator=(const sfMatrix<ValueType, D>& B)
		{
			mShares = B.mShares;
			return B;
		}


		sfMatrix<ValueType, D>& operator+=(const sfMatrix<ValueType, D>& B)
		{
			mShares[0] += B.mShares[0];
			mShares[1] += B.mShares[1];
			return *this;
		}


		sfMatrix<ValueType, D>& operator-=(const sfMatrix<ValueType, D>& B)
		{
			mShares[0] -= B.mShares[0];
			mShares[1] -= B.mShares[1];
			return *this;
		}

		sfMatrix<ValueType, D> operator+(const sfMatrix<ValueType, D>& B) const
		{
			sfMatrix<ValueType, D> r = *this;
			r += B;
			return r;
		}
		sfMatrix<ValueType, D> operator-(const sfMatrix<ValueType, D>& B) const
		{
			sfMatrix<ValueType, D> r = *this;
			r -= B;
			return r;
		}

		sfMatrix<ValueType, D> transpose() const
		{
			sfMatrix<ValueType, D> r = *this;
			r.transposeInPlace();
			return r;
		}
		void transposeInPlace()
		{
			mShares[0].transposeInPlace();
			mShares[1].transposeInPlace();
		}


		Row row(u64 i) { return Row{ *this, i }; }
		Col col(u64 i) { return Col{ *this, i }; }
		ConstRow row(u64 i) const { return ConstRow{ *this, i }; }
		ConstCol col(u64 i) const { return ConstCol{ *this, i }; }

		bool operator !=(const sfMatrix<ValueType, D>& b) const
		{
			return !(*this == b);
		}

		bool operator ==(const sfMatrix<ValueType, D> & b) const
		{
			return (rows() == b.rows() &&
				cols() == b.cols() &&
				mShares == b.mShares);
		}


		siMatrix<ValueType>& ValueTypeCast() { return static_cast<siMatrix<ValueType>&>(*this); }
		const siMatrix<ValueType>& ValueTypeCast() const { return static_cast<const siMatrix<ValueType>&>(* this); }


		eMatrix<ValueType>& operator[](u64 i) { return mShares[i]; }
		const eMatrix<ValueType>& operator[](u64 i) const { return mShares[i]; }
	};

    template<Decimal  D>
    using sf64Matrix = sfMatrix<i64, D>;


	template<typename ValueType, Decimal D>
	inline const typename sfMatrix<ValueType, D>::Row& sfMatrix<ValueType, D>::Row::operator=(const Row & row)
	{
		mMtx.mShares[0].row(mIdx) = row.mMtx.mShares[0].row(row.mIdx);
		mMtx.mShares[1].row(mIdx) = row.mMtx.mShares[1].row(row.mIdx);

		return row;
	}

	template<typename ValueType, Decimal D>
	inline const typename sfMatrix<ValueType, D>::ConstRow& sfMatrix<ValueType, D>::Row::operator=(const ConstRow & row)
	{
		mMtx.mShares[0].row(mIdx) = row.mMtx.mShares[0].row(row.mIdx);
		mMtx.mShares[1].row(mIdx) = row.mMtx.mShares[1].row(row.mIdx);
		return row;
	}


	template<typename ValueType, Decimal D>
	inline const typename sfMatrix<ValueType, D>::Col& sfMatrix<ValueType, D>::Col::operator=(const Col & row)
	{
		mMtx.mShares[0].col(mIdx) = row.mMtx.mShares[0].col(row.mIdx);
		mMtx.mShares[1].col(mIdx) = row.mMtx.mShares[1].col(row.mIdx);

		return row;
	}

	template<typename ValueType, Decimal D>
	inline const typename sfMatrix<ValueType, D>::ConstCol& sfMatrix<ValueType, D>::Col::operator=(const ConstCol & row)
	{
		mMtx.mShares[0].col(mIdx) = row.mMtx.mShares[0].col(row.mIdx);
		mMtx.mShares[1].col(mIdx) = row.mMtx.mShares[1].col(row.mIdx);
		return row;
	}
}
