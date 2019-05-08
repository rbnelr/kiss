#pragma once

#include "kiss.hpp"

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

void draw_spinning_ngon (int n, v2 pos, flt size) {
	static flt ori = 0;
	ori += deg(2);
	ori = wrap(ori, deg(360));

	glBegin(GL_TRIANGLE_FAN);

	flt ang = deg(360) / (flt)n;

	for (int i=0; i<n; ++i) {

		v2 vert = (rotate2(-ang/2 + ang * i + ori) * v2(0,-1)) * size + pos.x;

		flt t = (flt)i / (flt)n;

		int a;
		flt b = wrap(t*3, 0.0f,1.0f, &a);

		v3 col = 0;
		col[a] = b;
		col[(a+1) % 3] = 1 -b;

		glVertex2f(vert.x, vert.y);
		glColor3f(col.x, col.y, col.z);
	}

	glEnd();
}

void draw (iv2 window_size, int ngon_n=3) {
	load_ortho_projection(10, window_size);

	glViewport(0,0, window_size.x, window_size.y);

	glClearColor(0.03f, 0.03f, 0.03f, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	draw_spinning_ngon(ngon_n, 0, 4);
}