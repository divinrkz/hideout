#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "asset.h"
#include "asset_cache.h"
#include "sdl_wrapper.h"
#include "landing_page.h"

const vector_t MIN = {0, 0};
const vector_t MAX = {1000, 500};
const vector_t CENTER = {500, 250};

struct state
{
    scene_t *scene;
    size_t page;
};

void load_game_screen(state_t *state)
{
    state->page = 1;
}

state_t *emscripten_init()
{
    asset_cache_init();
    sdl_init(MIN, MAX);
    state_t *state = malloc(sizeof(state_t));
    state->page = 0;
    return state;
}

bool emscripten_main(state_t *state)
{
    sdl_clear();

    if (state->page == 0)
    {
        build_landing_page();
    }
    else
    {
    }

    sdl_show();
    return false;
}

void emscripten_free(state_t *state)
{
    scene_free(state->scene);
    asset_cache_destroy();
    free(state);
}
