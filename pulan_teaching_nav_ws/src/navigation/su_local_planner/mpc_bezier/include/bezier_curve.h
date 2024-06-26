/***********************************************************
 *
 * @file: bezier_curve.h
 * @breif: Bezier curve generation
 * @author: Yang Haodong
 * @update: 2023-12-22
 * @version: 1.0
 *
 * Copyright (c) 2023, Yang Haodong
 * All rights reserved.
 * --------------------------------------------------------
 *
 **********************************************************/
#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include "curve.h"

namespace trajectory_generation
{
class Bezier : public Curve
{
public:
  /**
   * @brief Construct a new Bezier generation object
   * @param step        Simulation or interpolation size (default: 0.1)
   * @param offset      The offset of control points (default: 3.0)
   */
  Bezier();
  Bezier(double step, double offset);

  /**
   * @brief Destroy the Bezier generation object
   */
  ~Bezier();

  /**
   * @brief Running trajectory generation
   * @param points path points <x, y>
   * @param path generated trajectory
   * @return true if generate successfully, else failed
   */
  bool run(const Points2d points, Poses2d& path);

  bool converttrajToNavPath(Poses2d& path,nav_msgs::Path &nav_path);
  /**
   * @brief Running trajectory generation
   * @param points path points <x, y, theta>
   * @param path generated trajectory
   * @return true if generate successfully, else failed
   */
  bool run(const Poses2d points, Poses2d& path);

  /**
   * @brief Calculate the Bezier curve point.
   * @param t scale factor
   * @param control_pts control points
   * @return point point in Bezier curve with t
   */
  Point2d bezier(double t, Points2d control_pts);

  Point2d bezierDerivative(double t, Points2d control_pts);
  /**
   * @brief Calculate control points heuristically.
   * @param start Initial pose (x, y, yaw)
   * @param goal  Target pose (x, y, yaw)
   * @return control_pts control points
   */
  Points2d getControlPoints(Pose2d start, Pose2d goal);

  /**
   * @brief Generate the path.
   * @param start Initial pose (x, y, yaw)
   * @param goal  Target pose (x, y, yaw)
   * @return path The smoothed trajectory points
   */
  Poses2d generation(Pose2d start, Pose2d goal);

  /**
   * @brief Configure the offset of control points.
   * @param offset  The offset of control points
   */
  void setOffset(double offset);
  

private:
  // Calculate the number of combinations
  int _comb(int n, int r);

  double dist(const std::pair<double, double>& node1,
              const std::pair<double, double>& node2);

  double angle(const std::pair<double, double>& node1,
               const std::pair<double, double>& node2);

 protected:
  double offset_;  // The offset of control points
};

}  // namespace trajectory_generation

#endif