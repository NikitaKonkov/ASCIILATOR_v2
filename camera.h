#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
    float x, y, z;
    float pitch, yaw, roll;
    float fov;           // Field of view (in degrees)
    float aspect_ratio[2];  // Aspect ratio (width / height)
} Camera;


#endif // CAMERA_H  

