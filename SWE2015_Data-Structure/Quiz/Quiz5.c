typedef struct {
    float x, y;
} coordinates; // array 대신 사용할 좌표계 struct 설정정

typedef struct {
    coordinates point1, point2, point3, point4; // 4개 꼭짓점 좌표
    float length, height; // 직사각형 두 변 길이
} rectangle;

typedef struct {
    coordinates point1, point2, point3; // 3개 꼭짓점 좌표
    float side1, side2, side3; // 3개의 빗변 길이
    float angle1, angle2, angle3; // 세 각의 크기
} triangle;

typedef struct {
    coordinates center; // 중심점
    float radius; // 반지름
} circle;

void main(void)
{
    rectangle rect;
    rect.length = 2;
    rect.height = 5;
    rect.point1.x = 3.8;
    rect.point1.y = 9.7;
    
    triangle tri;
    tri.side1 = 7;
    tri.angle1 = 90;
    tri.point1.x = 10;
    tri.point1.y = 4;
    
    circle cir;
    cir.radius = 10;
    cir.center.x = 13.7;
    cir.center.y = 16.9;
}
