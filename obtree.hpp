#include <cassert>
#include <cstdio>
#include <iostream>
#include <limits>
#include <vector>
class ObTree {
    using vectorType = std::vector<double>;
    using matrixType = std::vector<std::vector<double>>;

    vectorType P;
    vectorType Q;

    // UNUSED
    double buildTree_Inocent(unsigned long long i, unsigned long long j) {
        if (j == i - 1) {
            return Q[i - 1];
        } else {
            auto q = std::numeric_limits<double>::max();

            for (auto r = i; r <= j; r += 1) {
                auto el = buildTree_Inocent(i, r - 1);
                auto er = buildTree_Inocent(r + 1, j);
                auto w = Q[i - 1];
                for (auto l = i; l <= j; l += 1) {
                    w += P[l - 1] + Q[l];
                }
                auto e = el + er + w;

                if (e < q) {
                    q = e;
                }
            }
            return q;
        }
    }

    // UNUSED
    double buildTree_Memoized(unsigned long long i, unsigned long long j,
                              matrixType M) {
        if (M[i][j] == std::numeric_limits<double>::max()) {
            if (j == i - 1) {
                M[i][j] = Q[i - 1];
            } else {
                auto q = std::numeric_limits<double>::max();

                for (auto r = i; r <= j; r += 1) {
                    auto el = buildTree_Memoized(i, r - 1, M);
                    auto er = buildTree_Memoized(r + 1, j, M);
                    auto w = Q[i - 1];
                    for (auto l = i; l <= j; l += 1) {
                        w += P[l - 1] + Q[l];
                    }
                    auto e = el + er + w;

                    if (e < q) {
                        q = e;
                    }
                }
                M[i][j] = q;
            }
        }
        return M[i][j];
    }

    // unused
    double buildTree_BottomUp() {
        matrixType M{Q.size(), vectorType(Q.size(), 0.0)};
        for (int i = 0; i < Q.size(); i += 1) {
            M[i][i] = Q[i];
        }

        for (int i = P.size(); i > 0; i -= 1) {
            for (int j = i; j < Q.size(); j += 1) {
                auto q = std::numeric_limits<double>::max();

                for (auto r = i; r <= j; r += 1) {
                    auto el = M[i - 1][r - 1];
                    auto er = M[r][j];
                    auto w = Q[i - 1];
                    for (auto l = i; l <= j; l += 1) {
                        w += P[l - 1] + Q[l];
                    }
                    auto e = el + er + w;

                    if (e < q) {
                        q = e;
                    }
                }
                M[i - 1][j] = q;
            }
        }
        return M[0][P.size()];
    }

  public:
    ObTree(const vectorType &P, const vectorType &Q) {
        this->P = P;
        this->Q = Q;
    }

    double build() { return buildTree_BottomUp(); }
};