#include "boost/geometry.hpp"
#include "boost/geometry/geometries/point.hpp"
#include "boost/geometry/geometries/box.hpp"

#include "boost/geometry/index/rtree.hpp"

// to store queries results
#include <vector>

// just for output
#include <iostream>
#include <boost/foreach.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

#include "lem_rtree.hpp"

int main()
{
    // create the rtree using default constructor
    RectTree_t rtree;

    // create some values
    for ( unsigned i = 0 ; i < 10 ; ++i )
    {
        // create a box
        Rect_t b(i + 0.0f, i + 0.0f, i + 1.5f, i + 1.5f);
        // insert new value
        rtree.insert(b, 777+i);
    }

    // find values intersecting some area defined by a box
    Rect_t b(0, 0, 4, 3);
    RectTree_t::vVal_t result_s;
    rtree.touch( b, result_s );

    // find 5 nearest values to a point
    typedef bg::model::point<long, 2, bg::cs::cartesian> point;
    typedef bg::model::box<point> box;
    typedef std::pair<box, unsigned> value;
    RectTree_t::vVal_t result_n;
    rtree.query( boost::geometry::index::nearest(point(0, 0), 5), std::back_inserter(result_n));

    // note: in Boost.Geometry WKT representation of a box is polygon
//
    // display results
    std::cout << "spatial query box:" << std::endl;
    std::cout << bg::wkt<box>(box( point(b.p1.x, b.p1.y), point(b.p2.x,b.p2.y) )) << std::endl;
    std::cout << "spatial query result:" << std::endl;
    BOOST_FOREACH(value const& v, result_s)
        std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;

    std::cout << "knn query point:" << std::endl;
    std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
    std::cout << "knn query result:" << std::endl;
    BOOST_FOREACH(value const& v, result_n)
        std::cout << bg::wkt<box>(v.first) << " - " << v.second << std::endl;

    return 0;
}