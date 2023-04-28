#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <signal.h>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <chrono>

#include "vector.hpp"

// ray marching defs
#define MAX_MARCHING_STEPS 50
#define MAX_DEPTH 10.0f
#define MAX_FPS 60
#define FRAME_TIME (1.0f / MAX_FPS)
#define TIME_SCALE 0.02f

void at_exit() {
    endwin();
}

void sig_handler(int signo) {
    at_exit();
    exit(1);
}

void end() {
    at_exit();
    exit(0);
}

float SDF_sphere(float3 pos, float3 center, float radius) {
    return (pos - center).length() - radius;
}

enum face {
        X_POS,
        X_NEG,
        Y_POS,
        Y_NEG,
        Z_POS,
        Z_NEG
    };

float3 face2rgb(face f, int offset = 0) {
    f = (face)(((int)f + offset) % 6);
    switch (f) {
        case 0:
            return rgb(255,0,0);
        case 1:
            return rgb(0,255,0);
        case 2:
            return rgb(0,0,255);
        case 3:
            return rgb(255,255,0);
        case 4: 
            return rgb(255,0,255);
        case 5:
            return rgb(0,255,255);
    };
    return rgb(0,0,0);
} 

struct cube_info {
    float distance;
    face closest_face;
};

cube_info SDF_cube(float3 pos, float3 center, float3 scale) {
    // expensive version
    // float x = std::max
    // (   pos.x - center.x - scale.x / 2.,
    //     center.x - pos.x - scale.x / 2.
    // );
    // float y = std::max
    // (   pos.y - center.y - scale.y / 2.,
    //     center.y - pos.y - scale.y / 2.
    // );
    
    // float z = std::max
    // (   pos.z - center.z - scale.z / 2.,
    //     center.z - pos.z - scale.z / 2.
    // );

    // float d = x;
    // d = std::max(d,y);
    // d = std::max(d,z);
    // return d;

    // cheap version
    // float3 d = (pos - center).abs() - scale;
    // return d.max();

    // shadertoy version
    float3 d = (pos.abs() - center.abs()) - (scale / 2.0);
    
    // Assuming p is inside the cube, how far is it from the surface?
    // Result will be negative or zero.
    float insideDistance = std::min(std::max(d.x, std::max(d.y, d.z)), 0.0f);
    
    // Assuming p is outside the cube, how far is it from the surface?
    // Result will be positive or zero.
    float outsideDistance = length(max(d, float3(0.0)));

    // get the closest face
    
    
    face closest_face;
    if (d.x > d.y && d.x > d.z) {
        if (pos.x > 0) {
            closest_face = X_POS;
        } else {
            closest_face = X_NEG;
        }
    } else if (d.y > d.x && d.y > d.z) {
        if (pos.y > 0) {
            closest_face = Y_POS;
        } else {
            closest_face = Y_NEG;
        }
    } else {
        if (pos.z > 0) {
            closest_face = Z_POS;
        } else {
            closest_face = Z_NEG;
        }
    }

    
    return {insideDistance + outsideDistance, closest_face};
}

float SDF_cylinder(float3 p, float3 center, float h, float r) {
    // How far inside or outside the cylinder the point is, radially
    float inOutRadius = length(p.xy() - center.xy()) - r;
    
    // How far inside or outside the cylinder is, axially aligned with the cylinder
    float inOutHeight = abs(p.z - center.z) - h/2.0;
    
    // Assuming p is inside the cylinder, how far is it from the surface?
    // Result will be negative or zero.
    float insideDistance = std::min(std::max(inOutRadius, inOutHeight), 0.0f);

    // Assuming p is outside the cylinder, how far is it from the surface?
    // Result will be positive or zero.
    float outsideDistance = length(max(float2(inOutRadius, inOutHeight), float2(0.0)));
    
    return insideDistance + outsideDistance;
}

float SDF_union(float a, float b) {
    return std::min(a, b);
}

float SDF_intersection(float a, float b) {
    return std::max(a, b);
}

float SDF_difference(float a, float b) {
    return std::max(a, -b);
}

/**
 * Rotation matrix around the X axis.
 */
mat3 rotateX(float theta) {
    float c = cos(theta);
    float s = sin(theta);
    return mat3(
        float3(1, 0, 0),
        float3(0, c, -s),
        float3(0, s, c)
    );
}

/**
 * Rotation matrix around the Y axis.
 */
mat3 rotateY(float theta) {
    float c = cos(theta);
    float s = sin(theta);
    return mat3(
        float3(c, 0, s),
        float3(0, 1, 0),
        float3(-s, 0, c)
    );
}

/**
 * Rotation matrix around the Z axis.
 */
mat3 rotateZ(float theta) {
    float c = cos(theta);
    float s = sin(theta);
    return mat3(
        float3(c, -s, 0),
        float3(s, c, 0),
        float3(0, 0, 1)
    );
}

struct SDF_result {
    float distance;
    float3 color;
};

SDF_result SDF_scene(float3 pos, float time) {
    float3 color_final = rgb(0, 0, 0);

    float3 rotated_pos = rotateY(-time) * pos;
    rotated_pos = rotateX(-time) * rotated_pos;

    float3 rotated_pos_alt = rotateY(time / 2) * pos;
    rotated_pos_alt = rotateX(time / 2) * rotated_pos_alt;
    

    float3 cube_center = float3(0, 0, 0);
    float3 cube_scale = float3(2, 2, 2);
    // float3 cube_color = rgb(230, 70 , 80);
    cube_info info = SDF_cube(rotated_pos, cube_center, cube_scale);
    float cube_d = info.distance;
    color_final = face2rgb(info.closest_face);

    float3 sphere_center = float3(0, 0, 0);
    float sphere_radius = 1.2f;
    float3 sphere_color = rgb(70 , 80 , 230);
    float sphere_d = SDF_sphere(pos, sphere_center, sphere_radius);

    color_final = cube_d < -sphere_d ? sphere_color : color_final;
    float d = SDF_difference(cube_d, sphere_d);

    float3 cylinder_center = float3(0, 0, 0);
    float cylinder_height = 2.0f;
    float cylinder_radius = 0.3f;
    float3 cylinder_color = rgb(70 , 230, 80);
    float cylinder_d = SDF_cylinder(rotated_pos, cylinder_center, cylinder_height, cylinder_radius);

    d = SDF_union(SDF_intersection(cylinder_d, -cube_d), d);
    color_final = cylinder_d < cube_d ? cylinder_color : color_final;

    float3 cube2_center = float3(0, 0, 0);
    float cube2_radius = .7f;
    cube_info info2 = SDF_cube(rotated_pos_alt, cube2_center, cube2_radius);
    float cube2_d = info2.distance;
    float3 cube2_color = face2rgb(info2.closest_face, 2);

    float tmp_d = SDF_difference(cube2_d, cylinder_d);

    color_final = tmp_d < d ? cube2_color : color_final;
    d = SDF_union(d, cube2_d);

    float3 sphere2_center = float3(0, 0, 2);
    float sphere2_radius = 0.3f;
    float3 sphere2_color = rgb(0, 255, 255);
    float sphere2_d = SDF_sphere(rotated_pos, sphere2_center, sphere2_radius);

    color_final = sphere2_d < d ? sphere2_color : color_final;
    d = SDF_union(d, sphere2_d);

    float3 sphere3_center = float3(0, 0, -2);
    float sphere3_radius = 0.3f;
    float3 sphere3_color = rgb(255, 0, 255);
    float sphere3_d = SDF_sphere(rotated_pos, sphere3_center, sphere3_radius);

    color_final = sphere3_d < d ? sphere3_color : color_final;
    d = SDF_union(d, sphere3_d);


    return {d, color_final};
}



int screen_width;
int screen_height;


struct ray {
    float3 origin;
    float3 direction;

    void marching_step(float scale) {
        origin = origin + direction * scale;
    }
};

char depth2char(float depth) {
    float ratio = depth / MAX_DEPTH;
    // smaller ratio means closer to the camera

    if (ratio < 0.3f)       return '@';
    else if (ratio < 0.4f)  return '#';
    else if (ratio < 0.5f)  return '$';
    else if (ratio < 0.55f)  return '%';
    else if (ratio < 0.60f)  return '&';
    else if (ratio < 0.65f)  return '*';
    else if (ratio < 0.75f)  return '+';
    else if (ratio < 0.8f)  return '-';
    else if (ratio < 0.9f)  return '.';
    else                    return ' ';


}

struct term_color {
    float3 rgb_color;
    short curses_color;
};

#define COLOR_LIGHT_BLACK 8
#define COLOR_LIGHT_RED 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_YELLOW 11
#define COLOR_LIGHT_BLUE 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_LIGHT_CYAN 14
#define COLOR_LIGHT_WHITE 15



term_color palette[] = {
    {rgb(12 , 12 , 12 ), COLOR_BLACK        },
    {rgb(255, 0  , 0  ), COLOR_RED          },
    {rgb(0  , 255, 0  ), COLOR_GREEN        },
    {rgb(255, 255, 0  ), COLOR_YELLOW       },
    {rgb(0  , 0  , 255), COLOR_BLUE         },
    {rgb(255, 0  , 255), COLOR_MAGENTA      },
    {rgb(0  , 255, 255), COLOR_CYAN         },
    {rgb(230, 230, 230), COLOR_WHITE        },
    {rgb(127, 127, 127), COLOR_LIGHT_BLACK  },
    {rgb(230, 70 , 80 ), COLOR_LIGHT_RED    },
    {rgb(70 , 230, 80 ), COLOR_LIGHT_GREEN  },
    {rgb(230, 230, 80 ), COLOR_LIGHT_YELLOW },
    {rgb(70 , 80 , 230), COLOR_LIGHT_BLUE   },
    {rgb(230, 70 , 230), COLOR_LIGHT_MAGENTA},
    {rgb(70 , 230, 230), COLOR_LIGHT_CYAN   },
    {rgb(255, 255, 255), COLOR_LIGHT_WHITE  }
};

short get_color(float3 rgb) {
    float min_dist = 1000000;
    short min_color = 0;
    for (unsigned int i = 0; i < sizeof(palette) / sizeof(term_color); i++) {
        float dist = (rgb - palette[i].rgb_color).length();
        if (dist < min_dist) {
            min_dist = dist;
            min_color = palette[i].curses_color;
        }
    }
    return min_color;
}

// single ray marching frame
void ray_marching(float3 cam_pos, float3 cam_dir, float time) { 
    move(0, 0);
    for (int i = 0; i < screen_height; i++) {
        for (int j = 0; j < screen_width ; j++)  {
            float depth = 0;
            float x = (float)j / screen_width - 0.5f;
            float y = (float)i / screen_height - 0.5f;
            float z = 0;

            float3 dir = float3(x, y, z);
            ray r = {cam_pos, cam_dir + dir};
            float3 color_rgb(0);
            for (int k = 0; k < MAX_MARCHING_STEPS; k++) {
                SDF_result rslt = SDF_scene(float3(r.origin.x, r.origin.y, r.origin.z), time);
                float dist = rslt.distance;
                color_rgb = rslt.color;
                if (dist < 0) {
                    break;
                }
                depth += dist;
                r.marching_step(dist);
            }
            short color = get_color(color_rgb);
            attron(COLOR_PAIR(color));
            addch(depth2char(depth));
            attroff(COLOR_PAIR(color));
        }
        move(i, 0);
    }
}


int main() {
    atexit(at_exit);
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
    initscr();
    noecho();
    curs_set(0);

    start_color();
    for (unsigned int i = 0; i < sizeof(palette) / sizeof(term_color); i++) {
        init_pair(i, palette[i].curses_color, COLOR_BLACK);
    }

    

    getmaxyx(stdscr, screen_height, screen_width);
    int c = 0;
    while (screen_height * 2 != screen_width || c == KEY_RESIZE) {
        clear();
        mvprintw(screen_height / 2, screen_width / 2 - 10, "Please resize the window to 2:1 ratio, width: %d, height: %d", screen_width, screen_height * 2);
        refresh();
        c = getch();
        getmaxyx(stdscr, screen_height, screen_width);
    }
    clear();
    float3 cam_pos = float3(0, 0, -5);
    float3 cam_dir = float3(0, 0, 1);
    ray_marching(cam_pos, cam_dir, 0);
    refresh();
    float time = 0;
    timeout(0);
    while (1) {
        auto start = std::chrono::high_resolution_clock::now();
        int c = getch();


        // move cam position keys
        // azerty layout (cause that's the keybord I'm using)

        // down
        if (c == 's') {
            cam_pos.y += 0.1f;
        }

        // up
        else if (c == 'z') {
            cam_pos.y -= 0.1f;
        }

        // left
        else if (c == 'q') {
            cam_pos.x -= 0.1f;
        }

        // right
        else if (c == 'd') {
            cam_pos.x += 0.1f;
        }

        // forward
        else if (c == 'w') {
            cam_pos.z += 0.1f;
        }

        // backward
        else if (c == 'x') {
            cam_pos.z -= 0.1f;
        }


        // rotate cam direction keys
        else if (c == 'j') {
            cam_dir.x -= 0.1f;
            cam_dir = cam_dir.normalize();
        }
        else if (c == 'l') {
            cam_dir.x += 0.1f;
            cam_dir = cam_dir.normalize();
        }
        else if (c == 'i') {
            cam_dir.y -= 0.1f;
            cam_dir = cam_dir.normalize();
        }
        else if (c == 'k') {
            cam_dir.y += 0.1f;
            cam_dir = cam_dir.normalize();
        }
        else if (c == 'u') {
            cam_dir.z -= 0.1f;
            cam_dir = cam_dir.normalize();
        }
        else if (c == 'o') {
            cam_dir.z += 0.1f;
            cam_dir = cam_dir.normalize();
        }


        auto end = std::chrono::high_resolution_clock::now();

        // get elapsed time in milliseconds
        std::chrono::duration<float, std::milli> elapsed = end - start;
        float elapsed_time = elapsed.count();
        if (elapsed_time < FRAME_TIME) {
            usleep((FRAME_TIME - elapsed_time) * 1000);
        }

        time += TIME_SCALE;
        ray_marching(cam_pos, cam_dir, time);

        refresh();
    }
    endwin();
    return 0;
}