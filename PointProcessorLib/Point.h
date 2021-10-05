#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{

    /// <summary>
    /// Base Point class
    /// </summary>
    class Point
    {
    public:
        /// <summary>
        /// Point constructor
        /// </summary>
        Point(PointType type);
        /// <summary>
        /// Get the point ID
        /// </summary>
        /// <returns>Point ID</returns>
        std::string get_id() const;
        /// <summary>
        /// Set the point ID
        /// </summary>
        /// <param name="id">Point ID</param>
        void set_id(std::string id);
        /// <summary>
        /// Get the point type
        /// </summary>
        /// <returns>Point type</returns>
        PointType get_type() const;
        /// <summary>
        /// Get the point description
        /// </summary>
        /// <returns>Point description</returns>
        std::string get_description() const;
        /// <summary>
        /// Set the point description
        /// </summary>
        /// <param name="description">Point description</param>
        void set_description(std::string description);
        /// <summary>
        /// Get the point aliases
        /// </summary>
        /// <returns>Point aliases</returns>
        std::vector<std::string> get_aliases() const;
        /// <summary>
        /// Add a point alias
        /// </summary>
        /// <param name="alias">Point alias</param>
        void add_alias(std::string alias);
        /// <summary>
        /// Get the point value as type T
        /// </summary>
        /// <typeparam name="T">Type to cast this value to</typeparam>
        /// <returns>Point value</returns>
        template <typename T>
        T get_value() const
        {
            return static_cast<T>(this->value);
        }
        /// <summary>
        /// Get the point quality
        /// </summary>
        /// <returns>Point quality</returns>
        Quality get_quality() const;
        /// <summary>
        /// Get the point processing frequency
        /// </summary>
        /// <returns>Point processing frequency</returns>
        Frequency get_freqeuncy() const;
        /// <summary>
        /// Set the point processing frequency
        /// </summary>
        /// <param name="frequency">Point processing frequency</param>
        void set_frequency(Frequency frequency);
        /// <summary>
        /// Get the average time it takes to calculate this point
        /// </summary>
        /// <returns>Average calculation time</returns>
        std::chrono::duration<int, std::micro> get_average_calc_time() const;
        /// <summary>
        /// Calculate the point value
        /// </summary>
        void calculate();
        /// <summary>
        /// Print the point summary to an output stream
        /// </summary>
        /// <param name="os">Output stream</param>
        /// <param name="point">Point</param>
        /// <returns>Output stream</returns>
        friend std::ostream& operator<<(std::ostream& os, Point& point);
    protected:
        /// <summary>
        /// Point ID
        /// </summary>
        ShmString id;
        /// <summary>
        /// Point Type
        /// </summary>
        PointType type;
        /// <summary>
        /// Point value
        /// </summary>
        double value;
        /// <summary>
        /// Point quality
        /// </summary>
        Quality quality;
        /// <summary>
        /// Point Description
        /// </summary>
        ShmString description;
        /// <summary>
        /// Point Alias
        /// </summary>
        ShmVector<ShmString> aliases;
        /// <summary>
        /// Point update frequency
        /// </summary>
        Frequency frequency;
        /// <summary>
        /// Average amount of time it takes to execute this calculation
        /// </summary>
        std::chrono::duration<int, std::micro> average_calc_time;
        /// <summary>
        /// Point calculation
        /// </summary>
        inline virtual void calc() {};
    private:
    };
}
