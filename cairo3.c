#include <cairo/cairo.h>

int main(int argc, char **argv)
{
    double x;
    cairo_surface_t *surface =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 300, 300);
    cairo_t *cr = cairo_create(surface);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 5);
    for (x = 0.0; x <= 300; x += 10) {
        cairo_move_to(cr, x, x);
        cairo_close_path(cr);
        cairo_stroke(cr);
    }
    cairo_surface_write_to_png(surface, "output.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    return 0;
}
