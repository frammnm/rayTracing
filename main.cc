
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <cmath>



// #include "utilities.h"
#include "png.h"
// #include "vect3.h"
// #include "ray.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"


color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }
    vect3 unit_direction = r.direction().unit_vector();
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_w = 400;
    const int image_h = static_cast<int>(image_w / aspect_ratio);
	PNG image = PNG(image_w, image_h);


	// World
    hittable_list world;
    world.add(make_shared<sphere>(p3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(p3(0,-100.5,-1), 100));


    // Camera
    // auto viewport_h = 2.0;
    // auto viewport_w = aspect_ratio * viewport_h;
    // auto focal_length = 1.0;

    // auto origin = p3(0, 0, 0);
    // auto horizontal = vect3(viewport_w, 0, 0);
    // auto vertical = vect3(0, viewport_h, 0);
    // auto lower_left_corner = origin - horizontal/2 - vertical/2 - vect3(0, 0, focal_length);

    // Camera
    camera cam;


    // Render
    std::cout << "\nStarting render...2\n";
    std::cout << "Image: \n" << image_w << " " << image_h;

    for (int j = image_h - 1; j >= 0; --j) {
        // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_w; ++i) {
            auto u = double(i) / (image_w-1);
            auto v = double(j) / (image_h-1);
            ray r = cam.get_ray(u, v);
            color pixel_color = ray_color(r, world);
            image.set(i, j, pixel_color[0], pixel_color[1], pixel_color[2]);
        }
    }

    std::cout << "\nSaving PNG Image almost done...\n";
    image.save("image_render.png");
	std::cout << "\nDone...\n";
}

