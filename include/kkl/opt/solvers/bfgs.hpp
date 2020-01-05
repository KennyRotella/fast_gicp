#ifndef KKL_OPT_BFGS_HPP
#define KKL_OPT_BFGS_HPP

#include <iostream>

#include <Eigen/LU>
#include <Eigen/Core>
#include <kkl/opt/solvers/quasi_newton_method.hpp>

namespace kkl {
namespace opt {

template <typename Scalar, int N>
class BFGS : public QuasiNewtonMethod<Scalar, N> {
public:
  using typename Optimizer<Scalar, N>::Function;
  using typename Optimizer<Scalar, N>::Jacobian;

  using typename Optimizer<Scalar, N>::VectorN;
  using typename Optimizer<Scalar, N>::MatrixN;

  BFGS(const Function& f, const Jacobian& j = nullptr) : QuasiNewtonMethod<Scalar, N>(f, j) {}

  virtual MatrixN update_B_inv(const MatrixN& B_inv, const VectorN& s, const VectorN& y) const override {
    auto b_inv1 = (s.transpose() * y + y.transpose() * B_inv * y)(0, 0) * (s * s.transpose()) / std::pow(s.transpose() * y, 2);
    auto b_inv2 = (B_inv * y * s.transpose() + s * y.transpose() * B_inv) / (s.transpose() * y);
    return B_inv + b_inv1 - b_inv2;
  }
};

}  // namespace opt
}  // namespace kkl

#endif