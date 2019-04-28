#include "kiss.hpp"
#include "stdio.h"

kiss::Input inp;

void draw_spinning_triangle (v2 pos, flt size) {
	static flt ang = 0;
	ang += deg(2);
	ang = wrap(ang, deg(360));

	v2 verts[3] = {
		rotate2(deg(-60) + ang) * v2(0,-1),
		rotate2(deg(+60) + ang) * v2(0,-1),
		rotate2(deg(180) + ang) * v2(0,-1),
	};
	v3 colors[3] = {
		v3(1,0,0),
		v3(0,1,0),
		v3(0,0,1),
	};

	glBegin(GL_TRIANGLES);

	for (int i=0; i<3; ++i) {
		glVertex2f(verts[i].x * size + pos.x, verts[i].y * size + pos.y);
		glColor3f(colors[i].x, colors[i].y, colors[i].z);
	}

	glEnd();
}

void load_ortho_projection (flt cam_h, iv2 viewport_size, flt near=-10, flt far=100) {
	flt cam_w = cam_h * ( (flt)viewport_size.x / (flt)viewport_size.y );

	flt x = 2.0f / cam_w;
	flt y = 2.0f / cam_h;

	flt a = 1.0f / (far - near);
	flt b = near * a;

	fm4 cam_to_clip = fm4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, a, b,
		0, 0, 0, 1
	);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&cam_to_clip.arr[0][0]);

}

int main () {
	auto wnd = kiss::Window("Kiss Test");

	for (;;) {
		inp = wnd.get_input();

		if (inp.close)
			break;

		load_ortho_projection(10, inp.window_size);

		glViewport(0,0, inp.window_size.x, inp.window_size.y);

		glClearColor(0.03f, 0.03f, 0.03f, 1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		draw_spinning_triangle(0, 4);

		wnd.swap_buffers();
	}
}
