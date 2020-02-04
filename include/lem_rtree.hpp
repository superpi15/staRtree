#ifndef LEM_RTREE_HPP
#define LEM_RTREE_HPP

#include "lem_geom.hpp"
class RectTree_t {
	typedef boost::geometry::model::point<long, 2, boost::geometry::cs::cartesian> _point_t;
    typedef boost::geometry::model::box< _point_t > _box_t;
public:
	typedef std::pair< _box_t , unsigned > value_t;
	typedef std::vector<value_t> vVal_t;
private:
    typedef boost::geometry::index::rtree< value_t, boost::geometry::index::quadratic<16> > _rtree_t;
    _rtree_t tree;
public:
	/*
	 * fast access 
	 */
	void insert( const Rect_t& rect, int id )
	{
		_box_t b(_point_t( rect.p1.x, rect.p1.y), _point_t( rect.p2.x, rect.p2.y));
		tree.insert(std::make_pair(b, id)); }

	void touch( const Rect_t& rect, vVal_t& vVal ) const 
	{
		_box_t query_box(_point_t( rect.p1.x, rect.p1.y), _point_t( rect.p2.x, rect.p2.y));
		tree.query( boost::geometry::index::intersects(query_box), std::back_inserter(vVal)); }

	void clear(){ tree.clear(); }

	/*
	 * operations using boost library 
	 */
	template<typename Predicates, typename OutIter>\
	size_t query(Predicates const & predicates, OutIter out_it) {
		return tree.query( predicates, out_it); }

};

#endif