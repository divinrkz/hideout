#ifndef __LANDING_PAGE_H__
#define __LANDING_PAGE_H__

#include <stdlib.h>

typedef struct text_element text_element_t;

typedef struct img_element img_element_t;

typedef struct btn_element btn_element_t;

typedef struct state state_t;

/**
 * Build all assets of the landing page
 * @return current page
 */
size_t build_landing_page(size_t page);

#endif // #ifndef __LANDING_PAGE_H__