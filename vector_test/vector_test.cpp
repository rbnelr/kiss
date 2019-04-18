#include "vector/vector.hpp"

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

	//m3x4 a;
	//
	//a = 0;
	//a = m3x4(0);
	//
	//a = m3x4(	1, 2, 3, 4,
	//		 5, 6, 7, 8,
	//		 9,10,11,12);
	//
	//a = m3x4::rows(	1, 2, 3, 4,
	//			   5, 6, 7, 8,
	//			   9,10,11,12);
	//a = m3x4::rows(	v4(1, 2, 3, 4),
	//			   v4(5, 6, 7, 8),
	//			   v4(9,10,11,12));
	//
	//a = m3x4::columns(	1, 2, 3, 4,
	//				  5, 6, 7, 8,
	//				  9,10,11,12);
	//a = m3x4::columns(	v3(1, 2, 3),
	//				  v3(4, 5, 6),
	//				  v3(7, 8, 9),
	//				  v3(10,11,12));




	return 0;
}
