
#include "./statistic_factory.hpp"  // StatisticFactory
#include <algorithm>  // min_element, max_element
#include <numeric>    // accumulate
#include <cstdlib> // rand, srand
#include <time.h>
#include <vector>
#include <iostream> // cout, endl
#include <memory> // allocator
#include <limits> // numeric_limits
using std::vector;
using std::cout;
using std::endl;

typedef float NumberType;
struct DummyNewOperandType {void deallocate(void *) {}};
typedef StatisticFactory<NumberType, DummyNewOperandType> SF;

int main()
{
  size_t n = 10;
  vector<NumberType> v;
  srand(time(0));
  cout << "input: ";
  for (size_t i = 0; i < n; ++i) {
    NumberType r = static_cast<NumberType>(rand());   // ok if floating point whole number.
    cout << r << " ";
    v.push_back(r);
  }
  cout << endl;

  SF statisticFactory;

  {
    SF::Statistic *statistic = statisticFactory.ConstructStatistic(SF::MIN);
    for (auto f : v) statistic->Update(f);
    NumberType f = statistic->GetResult();
    cout << "min: " << f << endl;
    assert(f == *min_element(v.begin(), v.end()));
  }

  {
    SF::Statistic *statistic = statisticFactory.ConstructStatistic(SF::MAX);
    for (auto f : v) statistic->Update(f);
    NumberType f = statistic->GetResult();
    cout << "max: " << f << endl;
    assert(f == *max_element(v.begin(), v.end()));
  }

  {
    SF::Statistic *statistic = statisticFactory.ConstructStatistic(SF::AVG);
    for (auto f : v) statistic->Update(f);
    NumberType f = statistic->GetResult();
    cout << "avg: " << f << endl;
    assert(f == std::accumulate(v.begin(), v.end(), NumberType(0)) / static_cast<NumberType>(n));
        // Could use accumulate for min/max too but prefer the variety.
  }

  return 0;
}

