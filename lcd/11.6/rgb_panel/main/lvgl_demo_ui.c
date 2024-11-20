/*
 * SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

// This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/examples.html#scatter-chart

#include "lvgl.h"
#include "Untitled1.c"
#include "Untitled2.c"
#include "kul.c"

static void draw_event_cb(lv_event_t *e)
{
    lv_obj_draw_part_dsc_t *dsc = lv_event_get_draw_part_dsc(e);
    if (dsc->part == LV_PART_ITEMS) {
        lv_obj_t *obj = lv_event_get_target(e);
        lv_chart_series_t *ser = lv_chart_get_series_next(obj, NULL);
        uint32_t cnt = lv_chart_get_point_count(obj);
        /*Make older value more transparent*/
        dsc->rect_dsc->bg_opa = (LV_OPA_COVER *  dsc->id) / (cnt - 1);

        /*Make smaller values blue, higher values red*/
        lv_coord_t *x_array = lv_chart_get_x_array(obj, ser);
        lv_coord_t *y_array = lv_chart_get_y_array(obj, ser);
        /*dsc->id is the tells drawing order, but we need the ID of the point being drawn.*/
        uint32_t start_point = lv_chart_get_x_start_point(obj, ser);
        uint32_t p_act = (start_point + dsc->id) % cnt; /*Consider start point to get the index of the array*/
        lv_opa_t x_opa = (x_array[p_act] * LV_OPA_50) / 200;
        lv_opa_t y_opa = (y_array[p_act] * LV_OPA_50) / 1000;

        dsc->rect_dsc->bg_color = lv_color_mix(lv_palette_main(LV_PALETTE_RED),
                                               lv_palette_main(LV_PALETTE_BLUE),
                                               x_opa + y_opa);
    }
}

static void add_data(lv_timer_t *timer)
{
    lv_obj_t *chart = timer->user_data;
    lv_chart_set_next_value2(chart, lv_chart_get_series_next(chart, NULL), lv_rand(0, 200), lv_rand(0, 1000));
}


void example_lvgl_demo_ui(lv_disp_t *disp)

{
   // LV_IMG_DECLARE(Untitled1);

    // lv_obj_t *scr = lv_disp_get_scr_act(disp);
    // lv_obj_t *label = lv_label_create(scr);
    // lv_label_set_text(label, "Hello"); // 设置标签内容

    // // 将标签对象居中对齐
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_t *img = lv_img_create(lv_scr_act());  // 创建图像对象

    // // 设置图像源为 PNG 文件路径
    // lv_img_set_src(img, &Untitled1); 

    // // 将图像居中显示
    // lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    // 获取当前显示屏的活动屏幕
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    // 创建图像对象
    lv_obj_t *img = lv_img_create(scr);

    // 设置图像源为 C 数组中的图片数据
    lv_img_set_src(img, &kul);  // 这里设置图片为 Untitled2

    // 将图像居中显示
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    
}
