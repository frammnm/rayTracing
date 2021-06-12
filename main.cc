
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/polar_coordinates.hpp>

#include <vector>
#include <iostream>
#include <cmath>

// <<<<<<< HEAD
// =======
// #include "png.h"
// #include "color.h"
// #include "ray.h"
// #include "obj.h"
// >>>>>>> 285781a019b077c44d60a79a0ed4853f67bd4d79

// #include "vect3.h"
#include "ray.h"
#include "utilities.h"
#include "png.h"
#include "obj.h"
#include "color.h"
#include "intersect.h"
// #include "hittable_list.h"
#include "hittable.h"
// #include "sphere.h"
#include "camera.h"

OBJ obj;


color render_eq(glm::vec3 x, glm::vec3 c, glm::vec3 n, glm::vec3 wc, glm::vec3 p, glm::vec3 obj_c) {
    color color_result = glm::vec3(1.0f, 0.0f, 0.0f); 

    color_result =  (p / glm::exp2( glm::abs(c - x))) * (obj_c / pi) * glm::abs(n * ((c - x) / glm::abs(c - x))); 

    return color_result;


    // hit_record rec;
    // if (world.hit(r, 0, infinity, rec)) {
    //     return 0.5f * (rec.normal + color(1,1,1));
    // }
    // glm::vec3 unit_direction = r.direction() / glm::length(r.direction());
    // auto t = 0.5f * (unit_direction[1] + 1.0f);
    // return (1.0f-t)*color(1.0f, 1.0f, 1.0f) + t*color(0.5f, 0.7f, 1.0f);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_w = 400;
    const int image_h = static_cast<int>(image_w / aspect_ratio);
	PNG image = PNG(image_w, image_h);


	// World
    // hittable_list world;
    // world.add(make_shared<sphere>(p3(0,0,-1), 0.5));
    // world.add(make_shared<sphere>(p3(0,-100.5,-1), 100));


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

    // auto origin = glm::vec3(0, 0, 0);
    // auto horizontal = glm::vec3(viewport_w, 0, 0);
    // auto vertical = glm::vec3(0, viewport_h, 0);
    // auto lower_left_corner = origin - horizontal/2.0f - vertical/2.0f - glm::vec3(0, 0, focal_length);
    
	glm::mat4 xf = glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	obj.load("./model/teapot.obj", xf);
	int triangle_size = obj.faces().size();
    glm::vec3 obj_color = glm::vec3(1.0f, 0.0f, 0.0f); 



    // Render
    std::cout << "\nStarting render...2\n";
    std::cout << "Image: \n" << image_w << " " << image_h;
    std::cout << "\nNumber of triangles : " << triangle_size;
    for (int j = 0; j < image_h; ++j) {
        // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_w; ++i) {

            auto u = double(i) / (image_w-1);
            auto v = double(j) / (image_h-1);
            ray r = cam.get_ray(u, v);
            glm::vec3 smallest_intersected = glm::vec3(0.0f, 0.0f, 0.0f);
            int smallest_intersected_pos = -1;

            for (int k = 0; k < triangle_size - 2; k += 3) {
				
				glm::vec3 v0 = obj.faces().data()[k];
				glm::vec3 v1 = obj.faces().data()[k+1];
				glm::vec3 v2 = obj.faces().data()[k+2];
				glm::vec3 intersection_point = glm::vec3(0.0f, 0.0f, 0.0f);
				
				bool intersected = ray_intersects_triangle(r, v0, v1, v2, intersection_point);
			 	// std::cout <<  "Checking triangle in pos :" << k << "\n";
				if (intersected){
			        if (glm::length(smallest_intersected) == 0) {
                        smallest_intersected = intersection_point;
                        smallest_intersected_pos = k;
                    } else if (glm::length(intersection_point) < glm::length(smallest_intersected)) {
                        smallest_intersected = intersection_point;
                        smallest_intersected_pos = k;
                    }
                    // std::cout << "intersected...\n";
				}
			}

            glm::vec3 light_origin = glm::vec3(1.0f, 1.0f, 1.5f);
            glm::vec3 light_direction = glm::vec3(1.0f, 1.0f, 1.0f);
            glm::vec3 light_color = glm::vec3(1.0f, 1.0f, 1.0f);
            ray r_light = ray(light_origin, smallest_intersected);
            
            glm::vec3 light_smallest_intersected = glm::vec3(0.0f, 0.0f, 0.0f);
            int light_smallest_intersected_pos = -1;


            for (int k = 0; k < triangle_size - 2; k += 3) {
                
                glm::vec3 v0 = obj.faces().data()[k];
                glm::vec3 v1 = obj.faces().data()[k+1];
                glm::vec3 v2 = obj.faces().data()[k+2];
                glm::vec3 light_intersection_point = glm::vec3(0.0f, 0.0f, 0.0f);
                
                bool intersected = ray_intersects_triangle(r_light, v0, v1, v2, light_intersection_point);
                // std::cout <<  "Checking triangle in pos :" << k << "\n";
                if (intersected){
                    if (glm::length(light_smallest_intersected) == 0) {
                        light_smallest_intersected = light_intersection_point;
                        light_smallest_intersected_pos = k;
                    } else if (glm::length(light_intersection_point) < glm::length(light_smallest_intersected)) {
                        light_smallest_intersected = light_intersection_point;
                        light_smallest_intersected_pos = k;
                    }
                    // std::cout << "intersected...\n";
                }
            }
            
            if ((smallest_intersected_pos != -1) & (light_smallest_intersected_pos == -1)) {
                color pixel_color = render_eq(smallest_intersected, 
                                        light_origin, 
                                        obj.normals()[smallest_intersected_pos],
                                        cam.return_origin(),
                                        light_color,
                                        obj_color);
                image.set(i, j, pixel_color[0], pixel_color[1], pixel_color[2]);
            }

        }
    }

    std::cout << "\nSaving PNG Image almost done...\n";
    image.save("image_render.png");
	std::cout << "\nDone...\n";
}

