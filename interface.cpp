using uint = unsigned int;

struct IArithmetic {
	virtual const IArithmetic & operator+(const IArithmetic & left, const IArithmetic & right) = 0;
	virtual const IArithmetic & operator*(const IArithmetic & left, const IArithmetic & right) = 0;
};

struct IDepth {
	virtual uint depth() const = 0;
};
struct ICount {
	virtual uint count() const = 0;
};
template<class E> struct IScalar_Read {
	virtual bool isScalar() const = 0;
	operator const E & () const {
		if(!isScalar()) throw NotScalarCast;
		return getScalar();
	}
	virtual const E & getScalar() const = 0;
};
template<class E> struct IScalar : IScalar_Read {
	operator E & () {
		if(!scalar()) throw NotScalarCast;
		return getScalar();
	}
	virtual E & getScalar() = 0;
};

template<class E> struct IRange : ICount, IScalar {
	virtual E operator[](uint i) const = 0;
	virtual E min() const = 0;
	virtual E max() const = 0;
	virtual bool contiguous() const = 0;
	bool isScalar() const override final { return count() == 0; }
};

struct IIndex : IDepth, IScalar {
	vector<shared_ptr<IScalar>> data;
	bool isScalar() const override final { return data.size() == 1 && data[0]->isScalar(); }
	uint depth() const override final { return data.size(); }
	virtual const IRange & operator[](uint i) const = 0;
};

template<class E> struct IArray_Read : IDepth, IScalar {
	virtual const IArray_Read<uint> & size() const = 0;
	virtual bool empty() const = 0;
	
	bool isScalar() const override final { return depth() == 0; }
	
	virtual operator const E & () const = 0;
	virtual const IArray_Read & operator[](const IIndex &) const = 0;
};

template<class E> struct IArray_WriteStruct {
	virtual void size(const IArray_Read<int> &) = 0;
};

template<class E> struct IArray_WriteData {
	virtual operator T & () = 0;
	virtual IArray_WriteData & operator[](const IIndex &) = 0;
};
