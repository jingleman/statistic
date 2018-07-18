#ifndef STATISTIC_FACTORY_H
#define STATISTIC_FACTORY_H


#include <algorithm>   // min, max
#include <assert.h>
#include <vector>
#include <limits>   // numeric_limits
#include <iostream> // cout, endl
using std::vector;
using std::numeric_limits;
using std::cout;
using std::endl;

template <class NumberType, class NewOperandType>
class StatisticFactory
{
public:
  class Statistic
  {
  protected:
    NumberType _f;
    Statistic(NumberType f_) : _f(f_) {}
  public:
    virtual ~Statistic() {}
    virtual void Update(NumberType f_)   = 0;
    virtual NumberType GetResult() const = 0;
  };

  class Min : public Statistic
  {
    using Statistic::_f;
    NumberType Initial() const {
      return numeric_limits<NumberType>::has_infinity
          ?  numeric_limits<NumberType>::infinity()
          :  numeric_limits<NumberType>::max();
    }
  public:
    Min() : Statistic(Initial()) {}
    virtual void Update(NumberType f_) {_f = std::min(_f, f_);}
    virtual NumberType GetResult() const
    {
      assert(_f != Initial());
      return _f;
    }
  };

  class Max : public Statistic
  {
    using Statistic::_f;
    NumberType Initial() const {
      return numeric_limits<NumberType>::has_infinity
          ? -numeric_limits<NumberType>::infinity()
          :  numeric_limits<NumberType>::lowest();
    }
  public:
    Max() : Statistic(Initial()) {}
    virtual void Update(NumberType f_) {_f = std::max(_f, f_);}
    virtual NumberType GetResult() const
    {
      assert(_f != Initial());
      return _f;
    }
  };

  class Avg : public Statistic
  {
    using Statistic::_f;
    size_t _n;  // Could have this in Statistic, for debug purposes.
  public:
    Avg() : Statistic(0.0f), _n(0) {}
    virtual void Update(NumberType f_) {_f += f_; ++_n;}
    virtual NumberType GetResult() const
    {
      assert(_n != 0);
      return _f / static_cast<NumberType>(_n);
          // Rounding not worth casting to float/double.
    }
  };

  enum Type {MIN, MAX, AVG, NONE};

private:
  vector<Statistic*> _statistics;
  NewOperandType *_newOperand;
public:
  StatisticFactory(NewOperandType *newOperand_ = NULL) : _newOperand(newOperand_) {}
  ~StatisticFactory()
  {
    for (auto statistic : _statistics) {
      if (_newOperand != NULL) {
        statistic->~Statistic();
        _newOperand->deallocate(statistic);
      } else {
        delete statistic;
      }
    }
  }
  Statistic *ConstructStatistic(Type type_)
  {
    assert(type_ != NONE);   // redundant for now.
    Statistic *statistic = nullptr;
    if      (type_ == MIN) statistic = _newOperand ? new (_newOperand) Min() : new Min();
    else if (type_ == MAX) statistic = _newOperand ? new (_newOperand) Max() : new Max();
    else if (type_ == AVG) statistic = _newOperand ? new (_newOperand) Avg() : new Avg();
    assert(statistic != nullptr);
    _statistics.push_back(statistic);
    return statistic;
  }
};


#endif
