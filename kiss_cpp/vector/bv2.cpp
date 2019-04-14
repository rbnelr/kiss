// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "bv2.hpp"

#include "bv3.hpp"
#include "bv4.hpp"
#include "bv2.hpp"

bool& bv2::operator[] (int i) {
	return arr[i];
}

bool bv2::operator[] (int i) const {
	return arr[i];
}


bv2::bv2 () {
	
}

constexpr bv2::bv2 (bool all): x{all}, y{all} {
	
}

constexpr bv2::bv2 (bool x, bool y): x{x}, y{y} {
	
}

constexpr bv2::bv2 (bv3 v): x{v.x}, y{v.y} {
	
}

constexpr bv2::bv2 (bv4 v): x{v.x}, y{v.y} {
	
}


//// reducing ops

constexpr bool all (bv2 v) {
	return v.x && v.y;
}

constexpr bool any (bv2 v) {
	return v.x || v.y;
}

//// arthmethic ops

constexpr bv2 operator! (bv2 v) {
	return bv2(!v.x, !v.y);
}

constexpr bv2 operator&& (bv2 l, bv2 r) {
	return bv2(l.x && r.x, l.y && r.y);
}

constexpr bv2 operator|| (bv2 l, bv2 r) {
	return bv2(l.x || r.x, l.y || r.y);
}

//// comparison ops

constexpr bv2 operator== (bv2 l, bv2 r) {
	return bv2(l.x == r.x, l.y == r.y);
}

constexpr bv2 operator!= (bv2 l, bv2 r) {
	return bv2(l.x != r.x, l.y != r.y);
}

constexpr bool equal (bv2 l, bv2 r) {
	return all(l == r);
}

constexpr bv2 select (bv2 c, bv2 l, bv2 r) {
	return c.x ? l.x : r.x, c.y ? l.y : r.y;
}
