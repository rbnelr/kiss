#include "vector/vector.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

void matrix_to_string (std::ostream* os, std::string const& str, float const* cells_column_maj, int rows, int columns) {

	int cell_w = 3 + 1 + 2; // aaa.bb
	
	*os << str << '(';

	auto indent = str.size() + 1;

	*os << std::fixed << std::setprecision(2);

	for (int row=0; row<rows;) {
		for (int col=0; col<columns;) {
			float cell = cells_column_maj[col * rows + row];

			if (row > 0 && col == 0)
				*os << std::setw(indent + cell_w);
			else
				*os << std::setw(cell_w);

			*os << cell;
			
			if (++col == columns) break;
			*os << ", ";
		}

		if (++row == rows) break;
		*os << ",\n";
	}
	
	*os << std::resetiosflags(std::ios_base::fixed);

	*os << ")";
}
void vector_to_string (std::ostream* os, std::string const& str, float const* components, int len) {

	int cell_w = 3 + 1 + 2; // aaa.bb

	*os << str << '(';

	*os << std::fixed << std::setprecision(3);

	for (int i=0; i<len; ++i) {
		*os << std::setw(cell_w) << components[i];

		if (i < len-1)
			*os << ", ";
	}

	*os << std::resetiosflags(std::ios_base::fixed);

	*os << ")";
}
std::ostream& operator<< (std::ostream& ss, m3x4 const& m) {
	matrix_to_string(&ss, "m3x4", &m.arr[0][0], 3,4);
	return ss;
}
std::ostream& operator<< (std::ostream& ss, m2 const& m) {
	matrix_to_string(&ss, "m2", &m.arr[0][0], 2,2);
	return ss;
}
std::ostream& operator<< (std::ostream& ss, m4 const& m) {
	matrix_to_string(&ss, "m4", &m.arr[0][0], 4,4);
	return ss;
}
std::ostream& operator<< (std::ostream& ss, v3 const& v) {
	vector_to_string(&ss, "v3", &v.arr[0], 3);
	return ss;
}

template <typename T>
std::string to_string (T const& m) {
	std::stringstream ss;
	ss << m;
	return ss.str();
}

#define NOINLINE __declspec(noinline)

NOINLINE m3x4 tranformation(v3 scl, v3 trnsl) {
	return scale(scl) * translate(trnsl);
}
NOINLINE v3 apply_tranformation(m3x4 const& m, v3 v) {
	return m * v;
}

int main() {

	f32 f;
	f = wrap(4.5f, 2.0f);
	f = wrap(4.5f, -2.0f);
	f = wrap(-4.5f, 2.0f);
	f = wrap(-4.5f, -2.0f);

	int i;
	i = wrap(7, 3);
	i = wrap(7, -3);
	i = wrap(-7, 3);
	i = wrap(-7, -3);

	f = wrap(4.5f, 2.0f, 4.0f);
	int qi;
	f = wrap(2.5f, 2.0f, 4.0f, &qi);
	f = wrap(4.5f, 2.0f, 4.0f, &qi);
	f = wrap(6.5f, 2.0f, 4.0f, &qi);
	f = wrap(0.5f, 2.0f, 4.0f, &qi);

	i = floori(4.5f);
	i = (int)ceili(4.5); // conversion from 'vector::s64' to 'int', possible loss of data
	i = roundi(4.5f);
	//i = roundi(4);

	i = min(4,8);
	f = max(4.0f,8.0f);

	i = clamp(7, 5,6);
	f = clamp(5.2f, 5.0f,6.0f);

	f = select(false, 3.0f,4.0f);

	f = length(7.0f);
	f = length(-7.0f);
	i = length(7);
	i = length(-7);
	f = length(0.0f);

	i = length_sqr(7);

	i = normalize(7);
	i = normalize(-7);
	f = normalize(0.0f);
	i = normalize_or_zero(0);

	f = lerp(1.0f,2.0f, 0.5f);
	f = map(7.0f, 2.0f,5.0f);
	f = map(7.0f, 2.0f,5.0f, -2.0f,-5.0f);
	f = smoothstep(0.7f);

	v3 v;
	v = 0;
	v = v3(7);
	v = v3(7,9,-1);
	v = v3(v2(1,2),3);
	v = v3(v4(1,2,3,4));
	v = (v3)v4(1,2,3,4);
	//v = (v4)v3(1,2,3);

	auto dv = (dv3)v;
	//auto dv = (dv4)v;

	auto iv = (iv3)v;

	v += v3(3,2,1);
	v += 1;
	v -= 1;
	v *= v3(2,1,3);
	v *= 10;
	v /= 4;

	v = +v3(1,2,3);
	v = -v3(1,2,3);

	v = v3(1,2,3) * v3(1,2,3);
	v = v3(1,2,3) * 4;
	v = 4 * v3(1,2,3);
	v = 4 + v3(1,2,3);
	v = 4 - v3(1,2,3);
	v = 4 / v3(1,2,3);

	auto bv = v3(1,2,3) < v3(3,2,1);
	bv = v3(1,2,3) > v3(3,2,1);

	bv = v3(1,2,3) < 2;
	bv = v3(1,2,3) <= 2;
	bv = v3(1,2,3) >= 2;
	bv = v3(1,2,3) > 2;
	bv = v3(1,2,3) == 2;
	bv = v3(1,2,3) != 2;
	auto b = equal(v3(1,2,3), 2);

	v = select(bv3(1,0,0), v3(1,2,3), v3(-1,-2,-3));

	v = abs(v3(-5,7,-33));
	v = min(v3(0,0,0), v3(-5,7,-33));
	v = max(v3(0,0,0), v3(-5,7,-33));
	v = clamp(v3(-5,7,3), 0,5);

	f = min_component(v3(-5,7,-33));
	f = max_component(v3(-5,7,-33), &i);

	v = floor(v3(2, 2.5f, 2.9f));
	v = ceil(v3(2, 2.5f, 2.9f));
	v = round(v3(2, 2.5f, 2.9f));
	iv = floori(v3(2, 2.5f, 2.9f));
	iv = ceili(v3(2, 2.5f, 2.9f));
	iv = roundi(v3(2, 2.5f, 2.9f));

	v = pow(v3(2,2,2), v3(2,3,4));
	v = wrap(v3(-1,3,3.5f), v3(1.5f,1.5f,1.5f));

	v = lerp(0, 7, v3(0,0.5f,1));
	v = lerp(v3(1,2,3), v3(4,5,6), 0.5f);

	f = deg(360);
	f = to_deg(f);

	f = length(v3(1,2,3));
	f = length(v3(1,1,1));
	f = length(v2(1,1));
	f = length(v2(0.7f,0.7f));
	f = length_sqr(v3(5,5,5));
	f = distance(2, v2(0.5f, 7));

	f = dot(v2(0,1), v2(1,0));
	f = dot(v2(0,1), v2(0,1));
	v = cross(v3(1,0,0), v3(0,1,0));
	f = cross(v2(1,0), v2(0,1));

	v2 _2 = rotate90(v2(3,7));

	m3x4 m;
	
	//#m = 0; // mat ctor explicit
	m = m3x4(0);
	
	m = m3x4(1, 2, 3, 4,
			 5, 6, 7, 8,
			 9,10,11,12);
	
	m = m3x4::rows(1, 2, 3, 4,
				   5, 6, 7, 8,
				   9,10,11,12);
	m = m3x4::rows(v4(1, 2, 3, 4),
				   v4(5, 6, 7, 8),
				   v4(9,10,11,12));

	m = m3x4::columns( 1,  2,  3,
					   4,  5,  6,
					   7,  8,  9,
					  10, 11, 12);
	m = m3x4::columns(v3(1, 2, 3),
					  v3(4, 5, 6),
					  v3(7, 8, 9),
					  v3(10,11,12));

 	auto n = m2(m);
	n = (m2)m;
	auto o = m4(m);
	o = (m4)m;

	m = m3x4::identity();

	auto mm = dm3x4(m);

	n = m2(1,2,3,4) + m2(2,3,4,5);
	n = m2(1,2,3,4) - m2(2,3,4,5);
	n = mul_elementwise(m2(1,2,3,4), m2(2,3,4,5));
	n = div_elementwise(m2(1,2,3,4), m2(2,3,4,5));

	n = m2(1,2,3,4) + 2;
	n = m2(1,2,3,4) - 2;
	n = m2(1,2,3,4) * 2;
	n = m2(1,2,3,4) / 2;

	n += 2;
	n -= 2;
	n *= 2;
	n /= 2;

	n = 2 + m2(1,2,3,4);
	n = 2 - m2(1,2,3,4);
	n = 2 * m2(1,2,3,4);
	n = 2 / m2(1,2,3,4);

	auto scl = scale(v2(-2,4));
	auto trnsl = translate(v2(3,7));

	auto u = v2(1,1);

	auto uu = scl * u;
	uu = (v2)(trnsl * v3(u, 1));

	uu = scl * (v2)(trnsl * v3(u, 1));

	auto transf = scl * trnsl;
	uu = (v2)(transf * v3(u, 1));

	transf = trnsl * (m3)scl;
	uu = (v2)(transf * v3(u, 1));

	// shorthands
	transf = scl * trnsl;
	uu = transf * u;

	transf = trnsl * scl;
	uu = transf * u;
	
	transf = trnsl * trnsl;
	uu = transf * u;

	auto T = tranformation(v3(-2,3,5), v3(1,3,7));
	auto V = apply_tranformation(T, 1);

	std::cout << T <<"\n"<< V;

	//auto l = transpose(m3x4(	1,2,3,4,
	//							5,6,7,8,
	//							9,10,11,12)); // no m4x3 type, since it's not that useful
	auto l = transpose(m4(	 1, 2, 3, 4,
							 5, 6, 7, 8,
							 9,10,11,12,
							 0, 0, 0, 0)); // no m4x3 type, since it's not that useful

	f = det(scl);
	f = det((m3)trnsl);

	auto _4 = m4(	-2, 0, 0, 7,
					 0, 3, 0, 4,
					 0, 0, 0.5f, -13,
					 0, 0, 0, 1);
	auto det_4 = det(_4);
	auto inv_4 = inverse(_4);
	auto test_4 = _4 * inv_4;
	test_4 = inv_4 * _4;
	
	auto inv_scl = inverse(scl);

	auto test_scl = inv_scl * scl;
	test_scl = scl * inv_scl;
	uu = inv_scl * (scl * u);
	
	auto inv_trnsl = inverse((m3)trnsl);

	auto test_trnsl = inv_trnsl * (m3)trnsl;
	test_trnsl = (m3)trnsl * inv_trnsl;
	uu = (v2)(inv_trnsl * ((m3)trnsl * v3(u,1)));

	return 0;
}
