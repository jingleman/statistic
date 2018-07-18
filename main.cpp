
#include "./statistic_factory.hpp"  // StatisticFactory<float>
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

template <class T>
class C
{
  T _t;
};

int main()
{

  cout << endl << "float:";   // double basically same
  cout << endl <<  numeric_limits<float>::has_infinity;
  cout << endl << -numeric_limits<float>::infinity();
  cout << endl <<  numeric_limits<float>::lowest();
  cout << endl <<  numeric_limits<float>::min();
  cout << endl <<  numeric_limits<float>::max();
  cout << endl <<  numeric_limits<float>::infinity();
  cout << endl;

  cout << endl << "int:";
  cout << endl <<  numeric_limits<int>::has_infinity;
  cout << endl << -numeric_limits<int>::infinity();
  cout << endl <<  numeric_limits<int>::lowest();
  cout << endl <<  numeric_limits<int>::min();
  cout << endl <<  numeric_limits<int>::max();
  cout << endl <<  numeric_limits<int>::infinity();
  cout << endl;

  cout << endl << "size_t:";
  cout << endl <<  numeric_limits<size_t>::has_infinity;
  cout << endl << -numeric_limits<size_t>::infinity();
  cout << endl <<  numeric_limits<size_t>::lowest();
  cout << endl <<  numeric_limits<size_t>::min();
  cout << endl <<  numeric_limits<size_t>::max();
  cout << endl <<  numeric_limits<size_t>::infinity();
  cout << endl;

  cout << endl << "unsigned char:";   // double basically same
  cout << endl <<  numeric_limits<unsigned char>::has_infinity;
  cout << endl << -numeric_limits<unsigned char>::infinity();
  cout << endl <<  numeric_limits<unsigned char>::lowest();
  cout << endl <<  numeric_limits<unsigned char>::min();
  cout << endl <<  numeric_limits<unsigned char>::max();
  cout << endl <<  numeric_limits<unsigned char>::infinity();
  cout << endl;

  return 1;


  size_t n = 10;
  vector<float, std::allocator<float>> v;
  srand(time(0));
  cout << "input: ";
  for (size_t i = 0; i < n; ++i) {
    float r = static_cast<float>(rand())
            / static_cast<float>(RAND_MAX);
    cout << r << " ";
    v.push_back(r);
  }
  cout << endl;

  StatisticFactory<float> statisticFactory;

  {
    StatisticFactory<float>::Statistic *statistic = statisticFactory.ConstructStatistic(StatisticFactory<float>::MIN);
    for (auto f : v) statistic->Update(f);
    float f = statistic->GetResult();
    cout << "min: " << f << endl;
    assert(f == *min_element(v.begin(), v.end()));
  }

  {
    StatisticFactory<float>::Statistic *statistic = statisticFactory.ConstructStatistic(StatisticFactory<float>::MAX);
    for (auto f : v) statistic->Update(f);
    float f = statistic->GetResult();
    cout << "max: " << f << endl;
    assert(f == *max_element(v.begin(), v.end()));
  }

  {
    StatisticFactory<float>::Statistic *statistic = statisticFactory.ConstructStatistic(StatisticFactory<float>::AVG);
    for (auto f : v) statistic->Update(f);
    float f = statistic->GetResult();
    cout << "avg: " << f << endl;
    assert(f == std::accumulate(v.begin(), v.end(), 0.0f) / static_cast<float>(n));
        // Could use accumulate for min/max too but prefer the variety.
  }

  return 0;
}

