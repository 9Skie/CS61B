#pragma once
#include "Support.hpp"
#include <cmath>
#include <numeric>
// C++ adaptation of the supplied Princeton StdRandom-based helper library.
namespace RandomUtils {
using course::Random;
inline double uniform(Random &r) {
    return r.nextDouble();
}
inline int uniform(Random &r, int n) {
    return r.nextInt(n);
}
inline int64_t uniform(Random &random, int64_t n) {
    if (n <= 0)
        throw std::invalid_argument("Bound must be positive");
    uint64_t r = uint64_t(random.nextLong()), m = uint64_t(n - 1);
    if ((uint64_t(n) & m) == 0)
        return r & m;
    uint64_t u = r >> 1;
    while (u + m - (r = u % uint64_t(n)) > uint64_t(INT64_MAX))
        u = uint64_t(random.nextLong()) >> 1;
    return r;
}
inline int uniform(Random &r, int a, int b) {
    if (b <= a || int64_t(b) - a >= INT32_MAX)
        throw std::invalid_argument("Invalid range");
    return a + uniform(r, b - a);
}
inline double uniform(Random &r, double a, double b) {
    if (!(a < b))
        throw std::invalid_argument("Invalid range");
    return a + uniform(r) * (b - a);
}
inline bool bernoulli(Random &r, double p = 0.5) {
    if (!(p >= 0 && p <= 1))
        throw std::invalid_argument("Invalid probability");
    return uniform(r) < p;
}
inline double gaussian(Random &r) {
    double x, y, s;
    do {
        x = uniform(r, -1.0, 1.0);
        y = uniform(r, -1.0, 1.0);
        s = x * x + y * y;
    } while (s >= 1 || s == 0);
    return x * std::sqrt(-2 * std::log(s) / s);
}
inline double gaussian(Random &r, double mu, double sigma) {
    return mu + sigma * gaussian(r);
}
inline int geometric(Random &r, double p) {
    if (!(p > 0 && p <= 1))
        throw std::invalid_argument("Invalid probability");
    if (p == 1)
        return 1;
    return int(std::ceil(std::log(1 - uniform(r)) / std::log(1 - p)));
}
inline int poisson(Random &r, double lambda) {
    if (!(lambda > 0) || !std::isfinite(lambda))
        throw std::invalid_argument("Invalid lambda");
    int k = 0;
    double product = 1, limit = std::exp(-lambda);
    do {
        ++k;
        product *= uniform(r);
    } while (product >= limit);
    return k - 1;
}
inline double pareto(Random &r, double alpha = 1) {
    if (!(alpha > 0))
        throw std::invalid_argument("Invalid alpha");
    return std::pow(1 - uniform(r), -1 / alpha) - 1;
}
inline double cauchy(Random &r) {
    return std::tan(std::acos(-1) * (uniform(r) - 0.5));
}
inline int discrete(Random &r, const std::vector<double> &probabilities) {
    double sum = 0;
    for (double p : probabilities) {
        if (!(p >= 0))
            throw std::invalid_argument("Negative probability");
        sum += p;
    }
    if (!std::isfinite(sum) || std::abs(sum - 1) > 1e-14)
        throw std::invalid_argument("Probabilities must sum to 1");
    while (true) {
        double sample = uniform(r);
        sum = 0;
        for (size_t i = 0; i < probabilities.size(); ++i) {
            sum += probabilities[i];
            if (sum > sample)
                return i;
        }
    }
}
inline int discrete(Random &r, const std::vector<int> &frequencies) {
    int64_t sum = 0;
    for (int f : frequencies) {
        if (f < 0)
            throw std::invalid_argument("Negative frequency");
        sum += f;
    }
    if (sum <= 0 || sum >= INT32_MAX)
        throw std::invalid_argument("Invalid frequency sum");
    int sample = uniform(r, int(sum));
    sum = 0;
    for (size_t i = 0; i < frequencies.size(); ++i) {
        sum += frequencies[i];
        if (sum > sample)
            return i;
    }
    throw std::logic_error("Unreachable");
}
inline double exp(Random &r, double lambda) {
    if (!(lambda > 0))
        throw std::invalid_argument("Invalid lambda");
    return -std::log(1 - uniform(r)) / lambda;
}
template <class Sequence> void shuffle(Random &r, Sequence &a, int lo, int hi) {
    if (lo < 0 || hi < lo || hi > int(a.size()))
        throw std::invalid_argument("Invalid subarray");
    for (int i = lo; i < hi; ++i)
        std::swap(a[i], a[i + uniform(r, hi - i)]);
}
template <class Sequence> void shuffle(Random &r, Sequence &a) {
    shuffle(r, a, 0, a.size());
}
inline std::vector<int> permutation(Random &r, int n) {
    if (n < 0)
        throw std::invalid_argument("Negative size");
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    shuffle(r, p);
    return p;
}
inline std::vector<int> permutation(Random &r, int n, int k) {
    if (n < 0 || k < 0 || k > n)
        throw std::invalid_argument("Invalid sample size");
    std::vector<int> p(k);
    for (int i = 0; i < k; ++i) {
        int j = uniform(r, i + 1);
        p[i] = p[j];
        p[j] = i;
    }
    for (int i = k; i < n; ++i) {
        int j = uniform(r, i + 1);
        if (j < k)
            p[j] = i;
    }
    return p;
}
} // namespace RandomUtils
