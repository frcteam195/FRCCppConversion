#pragma once

#include <type_traits>
#include <map>
#include "Interpolable.hpp"
#include "InverseInterpolable.hpp"

namespace ck
{
    namespace math
    {
        template <typename K, typename V>
        class InterpolatingTreeMap : public std::map<K, V>
        {
            static_assert(std::is_base_of<InverseInterpolable, K>::value, "K must inherit from InverseInterpolable");
            static_assert(std::is_base_of<Interpolable, V>::value, "V must inherit from Interpolable");

        private:
            int max_;

        public:
            InterpolatingTreeMap(int maximumSize = 0) : std::map(), max_(maximumSize) {}
            /**
             * Inserts a key value pair, and trims the tree if a max size is specified
             *
             * @param key   Key for inserted data
             * @param value Value for inserted data
             * @return the value
             */
            V put(K &key, V &value)
            {
                if (max_ > 0 && max_ <= size())
                {
                    erase(begin());
                }

                std::map::emplace(key, value);

                return value;
            }

            //TODO: Fix and test
            // void putAll(std::map<K, V> &mapData)
            // {
            //     insert(mapData.begin(), mapData.end());
            // }

            // V getInterpolated(K &key)
            // {
            //     V gotval = at(key);
            //     if (!gotval)
            //     {
            //         /** Get surrounding keys for interpolation */
            //         K topBound = ceilingKey(key);
            //         K bottomBound = floorKey(key);

            //         /**
            //  * If attempting interpolation at ends of tree, return the nearest data point
            //  */
            //         if (topBound == null && bottomBound == null)
            //         {
            //             return null;
            //         }
            //         else if (topBound == null)
            //         {
            //             return get(bottomBound);
            //         }
            //         else if (bottomBound == null)
            //         {
            //             return get(topBound);
            //         }

            //         /** Get surrounding values for interpolation */
            //         V topElem = get(topBound);
            //         V bottomElem = get(bottomBound);
            //         return bottomElem.interpolate(topElem, bottomBound.inverseInterpolate(topBound, key));
            //     }
            //     else
            //     {
            //         return gotval;
            //     }
            // }
        };
    } // namespace math
} // namespace ck