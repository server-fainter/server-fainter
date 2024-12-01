#ifndef CANVAS_H
#define CANVAS_H

#include "task_queue.h"
#include "include/uthash.h"
#include <stdbool.h>
#include "client_manager.h"

// 픽셀 구조체
typedef struct {
    uint16_t x;
    uint16_t y;
    uint8_t color;
} Pixel;

// 수정된 픽셀 구조체
typedef struct {
    int key; // x * CANVAS_HEIGHT + y
    uint8_t color;
    UT_hash_handle hh; // uthash 핸들
} ModifiedPixel;

// 캔버스 구조체
typedef struct {
    Pixel *pixels;        // 캔버스 픽셀 데이터 배열
    ClientManager *cm;
    int canvas_width;
    int canvas_height;
    pthread_t tid;
    TaskQueue *queue;
    ModifiedPixel *modified_pixels; // 수정된 픽셀 해시 맵
} Canvas;


// 유효한 좌표인지 확인하는 함수
bool is_valid_coordinate(int x, int y, int width, int height);

// 유효한 HEX 색상인지 확인하는 함수
bool is_valid_hex_color(const char *color);

// 캔버스 초기화 함수
void init_canvas(Canvas *canvas, ClientManager *cm, int width, int height, int queue_size);

// 픽셀 업데이트 처리 함수
void process_pixel_update(Canvas *canvas, void *data);

// 수정된 픽셀을 브로드캐스트하는 함수
void broadcast_updates(Canvas *canvas);


#endif // CANVAS_H
