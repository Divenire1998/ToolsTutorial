#pragma once

#include <Eigen/Core>
#include <LocalCartesian.hpp>

namespace ImuGpsLocalization
{

    constexpr double kDegreeToRadian = M_PI / 180.;
    constexpr double kRadianToDegree = 180. / M_PI;

    // 以初始的 init_lla 经纬高坐标为原点，建立局部ENU坐标系
    // LLA 系 转 ENU
    inline void ConvertLLAToENU(const Eigen::Vector3d &init_lla,
                                const Eigen::Vector3d &point_lla,
                                Eigen::Vector3d *point_enu)
    {
        static GeographicLib::LocalCartesian local_cartesian;

        // 设置局部ENU系得的原点
        local_cartesian.Reset(init_lla(0), init_lla(1), init_lla(2));

        // 经纬高转换成米制坐标 [E,N,U]
        local_cartesian.Forward(point_lla(0), point_lla(1), point_lla(2),
                                point_enu->data()[0], point_enu->data()[1], point_enu->data()[2]);
    }

    // ENU 转 LLA
    inline void ConvertENUToLLA(const Eigen::Vector3d &init_lla,
                                const Eigen::Vector3d &point_enu,
                                Eigen::Vector3d *point_lla)
    {
        static GeographicLib::LocalCartesian local_cartesian;

        local_cartesian.Reset(init_lla(0), init_lla(1), init_lla(2));

        local_cartesian.Reverse(point_enu(0), point_enu(1), point_enu(2),
                                point_lla->data()[0], point_lla->data()[1], point_lla->data()[2]);
    }

}