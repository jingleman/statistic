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

template <class T>
class StatisticFactory
{
  T _t;
public:
  class Statistic
  {
  protected:
    float _f;
    Statistic(float f_) : _f(f_) {}
  public:
    virtual ~Statistic() {}
    virtual void Update(float f_)   = 0;
    virtual float GetResult() const = 0;
  };

  class Min : public Statistic
  {
    using Statistic::_f;
  public:
    Min() : Statistic(numeric_limits<float>::infinity()) {}
    virtual void Update(float f_) {_f = std::min(_f, f_);}
    virtual float GetResult() const
    {
      assert(_f != numeric_limits<float>::infinity());
      return _f;
    }
  };

  class Max : public Statistic
  {
    using Statistic::_f;
  public:
    Max() : Statistic(-numeric_limits<float>::infinity()) {}
    virtual void Update(float f_) {_f = std::max(_f, f_);}
    virtual float GetResult() const
    {
      assert(_f != -numeric_limits<float>::infinity());
      return _f;
    }
  };

  class Avg : public Statistic
  {
    using Statistic::_f;
    size_t _n;  // Could have this in Statistic, for debug purposes.
  public:
    Avg() : Statistic(0.0f), _n(0) {}
    virtual void Update(float f_) {_f += f_; ++_n;}
    virtual float GetResult() const
    {
      assert(_n != 0);
      return _f / static_cast<float>(_n);
    }
  };

  enum Type {MIN, MAX, AVG};

private:
  vector<Statistic*> _statistics;
public:
  ~StatisticFactory()
  {
    for (auto statistic : _statistics) {
      delete statistic;
    }
  }
  Statistic *ConstructStatistic(Type type_)
  {
    Statistic *statistic = nullptr;
    if      (type_ == MIN) statistic = new Min();
    else if (type_ == MAX) statistic = new Max();
    else if (type_ == AVG) statistic = new Avg();
    assert(statistic != nullptr);
    _statistics.push_back(statistic);
    return statistic;
  }
};


#endif
