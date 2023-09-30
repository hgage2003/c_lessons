#define TEST 1

#include <stdio.h>

#if TEST
#include <stdlib.h>

struct point_t 
{
  int x, y;
};
struct triangle_t 
{
  struct point_t pts[3];
};

#endif

int double_area(struct triangle_t tr)
{
    /*
    | x1 y1 1 |
    | x2 y2 1 |
    | x3 y3 1 |

    det(M) = x1*y2 + x2*y3 + y1*x3 - x3*y2 - x1*y3 - y1*x2
    */
    int det = tr.pts[0].x * tr.pts[1].y + tr.pts[1].x * tr.pts[2].y + tr.pts[0].y * tr.pts[2].x 
            - tr.pts[2].x * tr.pts[1].y - tr.pts[0].x * tr.pts[2].y - tr.pts[0].y * tr.pts[1].x;

    return det < 0 ? -det : det;
}

#if TEST
void read_input(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3)
{
    int ninput = scanf("%d%d%d%d%d%d", x1, y1, x2, y2, x3, y3);
    if (ninput != 6)
    {
        printf("Error: wrong input\n");
        abort();
    }
}

int main()
{
    struct triangle_t t;
    int res;

    read_input( &t.pts[0].x, &t.pts[0].y, &t.pts[1].x, &t.pts[1].y, 
                &t.pts[2].x, &t.pts[2].y);
    
    res = double_area(t);

    printf("%d\n", res);
}

#endif