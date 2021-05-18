
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <cmath>

#include "png.h"
#include "vect3.h"
#include "color.h"
#include "ray.h"
#include "intersect.h"

OBJ obj;


bool hit_sphere(const p3& center, double radius, const ray& r) {
    vect3 oc = r.origin() - center;
    auto a = r.direction().dot(r.direction());
    auto b = 2.0 * oc.dot(r.direction());
    auto c = oc.dot(oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

color ray_color(const ray& r) {
	if (hit_sphere(p3(0, 0, -1), 0.5, r))
	return color(1, 0, 0);
    vect3 unit_direction = r.direction().unit_vector();
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return color(1.0, 1.0, 1.0) * (1.0 - t)  + color(0.5, 0.7, 1.0) * t;
}

int main() {

    // Basic Image

    // const int image_w = 256;
    // const int image_h = 256;

    // PNG image = PNG(image_w, image_h);

    // std::cout << "width: " << image.width()  << " height: " << image.height() << "\n";

    // // Render

    // for (int j = 0; j < image_h; ++j) {
    //     for (int i = 0; i < image_w; ++i) {
    //         auto r = double(i) / (image_w - 1);
    //         auto g = double(j) / (image_h - 1);
    //         auto b = 0.25;

    //         // // std::cout << r << ' ' << g << ' ' << b << '\n';
    //         image.set(i, j, r, g, b);
    //         // color pixel_color(double(i)/(image_w-1), double(j)/(image_h-1), 0.25);
    //         // image.set(i, j, r, g, b);
    //         // write_color(std::cout, pixel_color);
    //     }
    // }

    // image.save("image_render.png");
    // std::cout << "\nDone.\n";


   //// test vect
   //  vect3 v1 = vect3(1, 1, 1);
   //  vect3 v2 = vect3(0, 0, 0);
   //  vect3 v3 = vect3(0, 0, 0);
   //  vect3 v4;

  	// v2 = v1 + v1;
  	// v3 = v2 + v2 - v1;
  	// v4 = v2 * 2;

   //  std::cout << v1;
   //  std::cout << v2;
   //  std::cout << v3;
   //  std::cout << v4;
   //  std::cout << v4.unit_vector();
    // std::cout << "v1 + v2" << v1 + v2;



    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_w = 400;
    const int image_h = static_cast<int>(image_w / aspect_ratio);
	PNG image = PNG(image_w, image_h);

    // Camera
    auto viewport_h = 2.0;
    auto viewport_w = aspect_ratio * viewport_h;
    auto focal_length = 1.0;

    auto origin = p3(0, 0, 0);
    auto horizontal = vect3(viewport_w, 0, 0);
    auto vertical = vect3(0, viewport_h, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vect3(0, 0, focal_length);

    // Render
    std::cout << "\nStarting render...\n";
    std::cout << "Image: \n" << image_w << " " << image_h;

    for (int j = image_h - 1; j >= 0; --j) {
        // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_w; ++i) {
            auto u = double(i) / (image_w-1);
            auto v = double(j) / (image_h-1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            image.set(i, j, pixel_color[0], pixel_color[1], pixel_color[2]);
            // write_color(std::cout, pixel_color);
        }
    }

    std::cout << "\nSaving PNG Image almost done...\n";
    image.save("image_render.png");
	std::cout << "\nDone...\n";
}

