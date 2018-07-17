
#include "./statistic.hpp"  // Statistic, Min, Max, Avg, StatisticFactory
#include <algorithm>  // min_element, max_element
#include <numeric>    // accumulate
#include <cstdlib> // rand, srand
#include <time.h>
#include <vector>
#include <iostream> // cout, endl
using std::vector;
using std::cout;
using std::endl;

int main()
{
  size_t n = 10;
  vector<float> v;
  srand(time(0));
  cout << "input: ";
  for (size_t i = 0; i < n; ++i) {
    float r = static_cast<float>(rand())
            / static_cast<float>(RAND_MAX);
    cout << r << " ";
    v.push_back(r);
  }
  cout << endl;

  StatisticFactory statisticFactory;

  {
    Statistic *statistic = statisticFactory.ConstructStatistic(Statistic::MIN);
    for (auto f : v) statistic->Update(f);
    float f = statistic->GetResult();
    cout << "min: " << f << endl;
    assert(f == *min_element(v.begin(), v.end()));
  }

  {
    Statistic *statistic = statisticFactory.ConstructStatistic(Statistic::MAX);
    for (auto f : v) statistic->Update(f);
    float f = statistic->GetResult();
    cout << "max: " << f << endl;
    assert(f == *max_element(v.begin(), v.end()));
  }

  {
    Statistic *statistic = statisticFactory.ConstructStatistic(Statistic::AVG);
    for (auto f : v) statistic->Update(f);
    float f = statistic->GetResult();
    cout << "avg: " << f << endl;
    assert(f == std::accumulate(v.begin(), v.end(), 0.0f) / static_cast<float>(n));
        // Could use accumulate for min/max too but prefer the variety.
  }

  return 0;
}

