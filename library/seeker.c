#include "stdbool.h"
#include "stdlib.h"
#include "seeker.h"
#include "scene.h"
#include "list.h"
#include "asset.h"
#include "sound_effect.h"
const char *SEEKER_PATH = "assets/seeker_bg.png";

const vector_t MIN_WINDOW = {0, 0};
const vector_t MAX_WINDOW = {1000, 500};
const vector_t INITIAL_VELOCITY = {60, 20};

const size_t GRID_WIDTH_S = 25;
const size_t GRID_HEIGHT_S = 12;
const size_t NUM_CELLS_S = GRID_WIDTH_S * GRID_HEIGHT_S;

const int GRID_CELL_SIZE_S = 40;
const int window_width_s = (GRID_WIDTH_S * GRID_CELL_SIZE_S) + 1;
const int window_height_s = (GRID_HEIGHT_S * GRID_CELL_SIZE_S) + 1;
// ((GRID_WIDTH - 2) * GRID_CELL_SIZE) + GRID_CELL_SIZE / 4, ((GRID_WIDTH - 3) * GRID_CELL_SIZE) + GRID_CELL_SIZE / 4
const vector_t START_POS = {.x =  ((GRID_WIDTH_S - 2) * GRID_CELL_SIZE_S) + GRID_CELL_SIZE_S / 4, .y = ((GRID_WIDTH_S - 3) * GRID_CELL_SIZE_S) + GRID_CELL_SIZE_S / 4};
const double OUTER_RADIUS =  60;
const double INNER_RADIUS = 60;

// SEEKING CONSTANTS
#define STARTING_SEEKERS 1
#define S_NUM_POINTS 20
#define S_RADIUS 0.1
#define NEW_SEEKERS_INTERVAL 30

const rgb_color_t seeker_color = (rgb_color_t){0.1, 0.9, 0.2};

typedef struct seeker {
    list_t *body_assets;
    double last_seeker_time;
    double max_seekers;
}seeker_t;


body_t *make_seeker(double w, double h, vector_t center) {

  list_t *c = list_init(1, free);
  vector_t *v1 = malloc(sizeof(vector_t));
  *v1 = (vector_t){center.x - w / 2 , center.y + h / 2};
  list_add(c, v1);

  vector_t *v2 = malloc(sizeof(vector_t));
  *v2 = (vector_t){center.x + w / 2, center.y + h / 2};
  list_add(c, v2);

  vector_t *v3 = malloc(sizeof(vector_t));
  *v3 = (vector_t){center.x - w / 2, center.y - h / 2};
  list_add(c, v3);

  vector_t *v4 = malloc(sizeof(vector_t));
  *v4 = (vector_t){center.x + w / 2, center.y - h / 2};
  list_add(c, v4);
  body_t *seeker = body_init(c, 1.5, seeker_color);
  // body_set_centroid(seeker, center);
  return seeker;
}

// void wrap_seeker_scene(body_t *seeker) {
//   vector_t centroid = body_get_centroid(seeker);
//   vector_t velocity = body_get_velocity(seeker);
  
//   if (centroid.x >= MAX_WINDOW.x || centroid.x <= MIN_WINDOW.x) {
//         velocity.x = -velocity.x;
//   }
//   if(centroid.y >= MAX_WINDOW.y || centroid.y <= MIN_WINDOW.y) {
//     velocity.y = -velocity.y;
//   }
//   body_set_velocity(seeker, velocity);
// }


void add_new_seeker(scene_t *scene, seeker_t *seeker_ipt, bool is_new){
   
  //  vector_t seeker_vel = {.x = 0.0, .y = 0.0};
   body_t *seeker;
    // if(is_new){
    //   vector_t seeker_pos = (vector_t){
    //     .x = ((GRID_WIDTH_S - 7) * GRID_CELL_SIZE_S) + GRID_CELL_SIZE_S / 4,
    //     .y = ((GRID_HEIGHT_S - 4) * GRID_CELL_SIZE_S) + GRID_CELL_SIZE_S / 4,
    // };
    //  seeker_vel = (vector_t){
    //     .x = rand() % (int)INITIAL_VELOCITY.x + 20,
    //     .y = rand() % (int)INITIAL_VELOCITY.y + 10
    // };
    //   seeker = make_seeker(OUTER_RADIUS, INNER_RADIUS, seeker_pos);
    // }
    vector_t center = (vector_t){.x = ((GRID_WIDTH_S - 2) * GRID_CELL_SIZE_S / 2), .y = ((GRID_HEIGHT_S - 3) * GRID_CELL_SIZE_S / 2)};
    seeker = make_seeker(GRID_CELL_SIZE_S / 2, GRID_CELL_SIZE_S / 2, center);
    // seeker_vel = INITIAL_VELOCITY;
  
    scene_add_body(scene, seeker);
    // body_set_velocity(seeker, seeker_vel);
    // asset_t *new_asset_seeker = asset_make_image_with_body(SEEKER_PATH, seeker);
    list_add(seeker_ipt->body_assets, seeker);
    seeker_ipt->last_seeker_time = 0;
    seeker_ipt->max_seekers += 1;
}

void introduce_seeker(scene_t *scene, seeker_t *seeker, double dt, sound_effect_t *sound_effect){
    printf(" WE are heree ");
    seeker->last_seeker_time += dt;
    // if(seeker->last_seeker_time >= NEW_SEEKERS_INTERVAL){
      add_new_seeker(scene, seeker, true);
      //  tagged_sound(sound_effect);
    // }
    for (size_t i = 0; i < list_size(seeker->body_assets); i++) {
      asset_render(list_get(seeker->body_assets, i));
    }
}

seeker_t *seeker_init(scene_t *scene){
  seeker_t *seeker = malloc(sizeof(seeker_t));
  seeker->max_seekers = 50;
  seeker->last_seeker_time = 0;
  seeker->body_assets = list_init(seeker->max_seekers, (free_func_t)asset_destroy);
    add_new_seeker(scene, seeker, false);
    
    return seeker;
}

void render_seeker_bodies(seeker_t *seeker) {
   for (size_t i = 0; i < list_size(seeker->body_assets); i++) {
      asset_render(list_get(seeker->body_assets, i));
    }
}

void free_seeker(seeker_t *seeker) {
  free(seeker->body_assets);
  free(seeker);
}