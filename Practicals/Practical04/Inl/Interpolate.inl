
namespace exercises {

template<typename PreOp, typename PostOp>
double Interpolate<PreOp,PostOp>::operator()(double dX) const
{
  auto i_it = std::lower_bound(m_xVals.begin(), m_xVals.end(), dX);
  size_t i = std::distance(m_xVals.begin(), i_it);
  double z_interpolate;

  if (dX < m_xVals.front()) {
    z_interpolate = m_yVals.front();
  } else if (dX >= m_xVals.back()) {
    z_interpolate = m_yVals.back();
  } else {
    double x_L = m_xVals[i - 1];
    double x_R = m_xVals[i];
    double z_L = m_yVals[i - 1];
    double z_R = m_yVals[i];

    z_interpolate = z_L + (z_R - z_L) * (dX - x_L) / (x_R - x_L);
  }

  return m_postOp(z_interpolate, dX);
}

}
