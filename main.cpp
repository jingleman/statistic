
#include "./statistic.hpp"  // Statistic, Min, Max, Avg, StatisticFactory
#include <algorithm>  // min_element, max_element, accumulate
#include <cstdlib> // rand, srand
#include <time.h>
#include <vector>
#include <iostream> // cout, endl
using std::vector;
using std::cout;
using std::endl;

float ComputeStatistic(Statistic::Type type_)
{
  Statistic *statistic = statisticFactory.ConstructStatistic(type_);
  for (auto f : v) {
    statistic->Update(f);
  }
  float f = statistic->GetResult();
  cout << "ComputeStatistic: returning " << f << endl;
  return f;
}

int main()
{
  size_t n = 10;
  vector<float> v;
  srand(time(0));
  for (size_t i = 0; i < n; ++i) {
    float r = static_cast<float>(rand())
            / static_cast<float>(RAND_MAX);
    cout << "i= " << i << " r= " << r << endl;
    v.push_back(r);
  }

  StatisticFactory statisticFactory;

  assert(f == *min_element(v.begin(), v.end()));
  {
  }

  Statistic *statistic = statisticFactory.ConstructStatistic(Statistic::MAX);
  for (auto f : v) statistic->Update(f);
  float f = statistic->GetResult();
  cout << "f= " << f << endl;
  assert(f == *max_element(v.begin(), v.end()));
 
  Statistic *statistic = statisticFactory.ConstructStatistic(Statistic::AVG);
  for (auto f : v) statistic->Update(f);
  float f = statistic->GetResult();
  cout << "f= " << f << endl;
  assert(f == std::accumulate(v.begin(), v.end()) / static_cast<float>(n));
  
  return 0;
}

