#include "Point.h"

namespace PointProcessor
{

    /// <summary>
    /// Point constructor
    /// </summary>
    Point::Point() :
        value(0),
        quality(Quality::UNKNOWN),
        frequency(Frequency::UNKNOWN),
        average_calc_time()
    {
    }

    /// <summary>
    /// Get the point ID
    /// </summary>
    /// <returns>Point ID</returns>
    std::string Point::get_id() const
    {
        return this->id;
    }

    /// <summary>
    /// Set the point ID
    /// </summary>
    /// <param name="id">Point ID</param>
    void Point::set_id(std::string id)
    {
        this->id = id;
    }

    /// <summary>
    /// Get the point description
    /// </summary>
    /// <returns>Point description</returns>
    std::string Point::get_description() const
    {
        return this->description;
    }

    /// <summary>
    /// Set the point description
    /// </summary>
    /// <param name="description">Point description</param>
    void Point::set_description(std::string description)
    {
        this->description = description;
    }

    /// <summary>
    /// Get the point aliases
    /// </summary>
    /// <returns>Point aliases</returns>
    std::vector<std::string> Point::get_aliases() const
    {
        return std::vector<std::string>(this->aliases.begin(), this->aliases.end());
    }

    /// <summary>
    /// Add a point alias
    /// </summary>
    /// <param name="alias">Point alias</param>
    void Point::add_alias(std::string alias)
    {
        this->aliases.push_back(alias);
    }

    /// <summary>
    /// Get the point quality
    /// </summary>
    /// <returns>Point quality</returns>
    Quality Point::get_quality() const
    {
        return this->quality;
    }

    /// <summary>
    /// Get the point processing frequency
    /// </summary>
    /// <returns>Point processing frequency</returns>
    Frequency Point::get_freqeuncy() const
    {
        return this->frequency;
    }

    /// <summary>
    /// Set the point processing frequency
    /// </summary>
    /// <param name="frequency">Point processing frequency</param>
    void Point::set_frequency(Frequency frequency)
    {
        this->frequency = frequency;
    }

    /// <summary>
    /// Get the average time it takes to calculate this point
    /// </summary>
    /// <returns>Average calculation time</returns>
    std::chrono::duration<int, std::micro> Point::get_average_calc_time() const
    {
        return this->average_calc_time;
    }

    /// <summary>
    /// Calculate the point value
    /// </summary>
    void Point::calculate()
    {
        using namespace std::chrono;
        steady_clock::time_point t1 = steady_clock::now();
        this->calc();
        auto calc_duration = duration_cast<duration<int, std::micro>>(
            std::chrono::steady_clock::now() - t1);
        if (this->average_calc_time.count() == 0)
        {
            this->average_calc_time = calc_duration;
        }

        else
        {
            auto avg = 0.1 * calc_duration.count() +
                0.9 * this->average_calc_time.count();
            auto int_avg = static_cast<int>(avg);
            this->average_calc_time = duration<int, std::micro>(int_avg);
        }
    }

    /// <summary>
    /// Print the point summary to an output stream
    /// </summary>
    /// <param name="os">Output stream</param>
    /// <param name="point">Point</param>
    /// <returns>Output stream</returns>
    std::ostream& operator<<(std::ostream& os, Point& point)
    {
        os << "POINT" << std::endl
            << "    ID          = " << point.get_id() << std::endl
            << "    Description = " << point.get_description() << std::endl
            << "    Aliases     = " << std::endl;
        auto aliases = point.get_aliases();
        for (auto it = aliases.cbegin();
            it != aliases.cend(); it++)
        {
            os << "                  " << *it << std::endl;
        }
        os << "    Value       = " << point.get_value<double>() << std::endl
            << "    Quality     = " << point.get_quality() << std::endl
            << "    Frequency   = " << point.get_freqeuncy() << std::endl
            << "    Avg Calc    = " << point.get_average_calc_time().count()
            << " usec" << std::endl
            ;
        return os;
    }
}
