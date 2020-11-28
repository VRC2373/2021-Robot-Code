#include "graphics.h"

void displayGraphics()
{
  LV_IMG_DECLARE(falcon);
  lv_obj_t *logo = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(logo, &falcon);
}