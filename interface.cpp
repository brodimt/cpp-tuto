#include <exception>
#include <vector>
#include <memory>

#define final_

using std::vector;
using std::shared_ptr;

struct NotScalarCast : std::exception {
const char* what() const { return "trying to cast a non scalar to a single value"; }
};
struct IncompatibleOperation : std::exception {
const char* what() const { return "trying to call an operation which isn't defined for this type"; }
};

typedef unsigned int uint;

template<class E> struct IArithmetic {
enum Op1 { op_not, op_neg };
enum Op2 { op_add, op_mul, op_sub, op_div, op_mod, op_and, op_or, op_xor };
virtual const IArithmetic & op1(Op1 op) = 0;
virtual const IArithmetic & op2(Op2 op, const E & right) = 0;

const IArithmetic & operator~() const { return op1(op_not); }
const IArithmetic & operator-() const { return op1(op_neg); }

const IArithmetic & operator+(const E & right) const { return op2(op_add, right); }
const IArithmetic & operator-(const E & right) const { return op2(op_sub, right); }
const IArithmetic & operator*(const E & right) const { return op2(op_mul, right); }
const IArithmetic & operator/(const E & right) const { return op2(op_div, right); }
const IArithmetic & operator%(const E & right) const { return op2(op_mod, right); }
const IArithmetic & operator&(const E & right) const { return op2(op_and, right); }
const IArithmetic & operator|(const E & right) const { return op2(op_or, right); }
const IArithmetic & operator^(const E & right) const { return op2(op_xor, right); }
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
template<class E> struct IScalar : IScalar_Read<E> {
operator E & () {
if(!scalar()) throw NotScalarCast;
return getScalar();
}
virtual E & getScalar() = 0;
};

template<class E> struct ISet : ICount, IScalar<E> {
virtual E operator[](uint i) const = 0;
virtual E min() const = 0;
virtual E max() const = 0;
virtual bool contiguous() const = 0;
bool isScalar() const override final_ { return count() == 0; }
};

struct IIndex : IDepth, IScalar<uint>{
vector<shared_ptr<ISet<uint>>> data;
bool isScalar() const override final_ { return data.size() == 1 && data[0]->isScalar(); }
uint depth() const override final_ { return data.size(); }
virtual const ISet<uint> & operator[](uint i) const = 0;
};

template<class E> struct IArray_Read : IDepth, IScalar<E>, IArithmetic<E>, IArithmetic<IArray_Read<E>> {
virtual const IArray_Read<uint> & size() const = 0;
virtual bool empty() const = 0;

bool isScalar() const override final_ { return depth() == 0; }

virtual operator const E & () const = 0;
virtual const IArray_Read & operator[](const IIndex &) const = 0;
};

template<class E> struct IArray_WriteData : IArray_Read<E> {
virtual operator E & () = 0;
virtual IArray_WriteData & operator[](const IIndex &) = 0;
};

template<class E> struct IArray_Write : IArray_WriteData<E> {
virtual void size(const IArray_Read<int> &) = 0;
};



template<class E> struct Range : ISet<E> {
};
