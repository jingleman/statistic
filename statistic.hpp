#ifndef STATISTIC_H
#define STATISTIC_H


#include <algorithm>   // min, ...
#include <assert.h>
#include <vector>
#include <limits>   // numeric_limits
using std::vector;
using std::numeric_limits;

class Statistic
{
protected:
  float _f;
  Statistic(float f_) : _f(f_) {}
public:
  // Leaving ctor to child classes, for simplicity.
  virtual ~Statistic() {}
  virtual void Update(float f_) = 0;
  virtual float GetResult() const = 0;
  enum Type {MIN, MAX, AVG};
};

class Min : public Statistic
{
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

class StatisticFactory
{
  vector<Statistic*> _statistics;
public:
  ~StatisticFactory()
  {
    for (auto statistic : _statistics) {
      delete statistic;
    }
  }
  Statistic *ConstructStatistic(Statistic::Type type_)
  {
    Statistic *statistic = nullptr;
    if      (type_ == Statistic::MIN) statistic = new Min();
    else if (type_ == Statistic::MAX) statistic = new Max();
    else if (type_ == Statistic::AVG) statistic = new Avg();
    assert(statistic != nullptr);
    _statistics.push_back(statistic);
    return statistic;
  }
};


#endif
