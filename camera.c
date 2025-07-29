#include "camera.h"


void camera_init(cam_coord *camera, float x, float y, float z, float roll, float pitch, float yaw, float fov) {
    camera->x = x;
    camera->y = y;
    camera->z = z;
    camera->roll = roll;
    camera->pitch = pitch;
    camera->yaw = yaw;
    camera->fov = fov;
}

void camera_set_position(cam_coord *camera, float x, float y, float z) {
    camera->x = x;
    camera->y = y;
    camera->z = z;
}

void camera_set_rotation(cam_coord *camera, float roll, float pitch, float yaw) {
    camera->roll = roll;
    camera->pitch = pitch;
    camera->yaw = yaw;
}

void camera_set_fov(cam_coord *camera, float fov) {
    camera->fov = fov;
}

