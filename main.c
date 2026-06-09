#include <stdio.h>
#include <stdlib.h>
 

#define ROWS    25     
#define COLS    70    
#define BLANK   '_'     
#define DOT     '*'     
#define MAX     64
 

#define CIRCLE    1
#define RECTANGLE 2
#define LINE      3
#define TRIANGLE  4
 


struct Shape {
    int id;       
    int type;     
    int alive;    
    int x, y;     
    int a, b;     
};
 

char         canvas[ROWS][COLS];      
struct Shape shapes[MAX];             
int          total   = 0;             
int          next_id = 1;            
 

void clear_canvas(void)
{
    int r, c;
    for (r = 0; r < ROWS; r++)
        for (c = 0; c < COLS; c++)
            canvas[r][c] = BLANK;
}
 

void show_canvas(void)
{
    int r, c;
 
    
    printf("+");
    for (c = 0; c < COLS; c++) printf("-");
    printf("+\n");
 
    
    for (r = 0; r < ROWS; r++) {
        printf("|");
        for (c = 0; c < COLS; c++)
            printf("%c", canvas[r][c]);
        printf("|\n");
    }
 
    
    printf("+");
    for (c = 0; c < COLS; c++) printf("-");
    printf("+\n");
}
 

void put_dot(int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
        canvas[row][col] = DOT;
}
 

void remove_dot(int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
        canvas[row][col] = BLANK;
}


void draw_rectangle(int x, int y, int width, int height)
{
    int i;

    
    for(i = x; i < x + width; i++)
        put_dot(y, i);

    
    for(i = x; i < x + width; i++)
        put_dot(y + height - 1, i);

    
    for(i = y; i < y + height; i++)
        put_dot(i, x);

    
    for(i = y; i < y + height; i++)
        put_dot(i, x + width - 1);
}


void draw_line(int x1, int y1, int x2, int y2)
{
    int i;

    if(y1 == y2) 
    {
        for(i = x1; i <= x2; i++)
            put_dot(y1, i);
    }

    else if(x1 == x2) 
    {
        for(i = y1; i <= y2; i++)
            put_dot(i, x1);
    }
}


void draw_triangle(int x, int y, int height)
{
    int i;

    
    for(i = 0; i < height; i++)
        put_dot(y + i, x - i);

    
    for(i = 0; i < height; i++)
        put_dot(y + i, x + i);

    
    for(i = x - height + 1; i <= x + height - 1; i++)
        put_dot(y + height - 1, i);
}


void draw_circle(int x, int y, int radius)
{
    int row, col;
    int distance;

    for(row = y - radius; row <= y + radius; row++)
    {
        for(col = x - radius; col <= x + radius; col++)
        {
            distance = (row - y) * (row - y) +
                       (col - x) * (col - x);

            if(distance >= radius * radius - 2 &&
               distance <= radius * radius + 2)
            {
                put_dot(row, col);
            }
        }
    }
}

void redraw_shapes(void)
{
    int i;

    for(i = 0; i < total; i++)
    {
        if(shapes[i].alive == 0)
        {
            continue;
        }
        else if(shapes[i].type == RECTANGLE)
        {
            draw_rectangle(
                shapes[i].x,
                shapes[i].y,
                shapes[i].a,
                shapes[i].b
            );
        }
        else if(shapes[i].type == LINE)
        {
            draw_line(
                shapes[i].x,
                shapes[i].y,
                shapes[i].a,
                shapes[i].b
            );
        }
        else if(shapes[i].type == CIRCLE)
        {
            draw_circle(
                shapes[i].x,
                shapes[i].y,
                shapes[i].a
            );
        }
        else if(shapes[i].type == TRIANGLE)
        {
            draw_triangle(
                shapes[i].x,
                shapes[i].y,
                shapes[i].a
            );
        }
    }
}
void delete_shape(int id)
{
    int index;

    for(index = 0; index < total; index++)
    {
        if(shapes[index].id == id)
        {
            shapes[index].alive = 0;

            printf("Shape deleted.\n");
            return;
        }
    }

    printf("Shape ID not found.\n");
}
void delete_shape_menu(void)
{
    int id;

    printf("Enter shape ID to delete: ");
    scanf("%d", &id);

    delete_shape(id);

    clear_canvas();
    redraw_shapes();
}

void list_shapes(void)
{
    int i;

    printf("\n========== SHAPE LIST ==========\n");

    for(i = 0; i < total; i++)
    {
        printf("ID : %d\n", shapes[i].id);

        if(shapes[i].type == RECTANGLE)
        {
            printf("Type : Rectangle\n");
        }
        else if(shapes[i].type == LINE)
        {
            printf("Type : Line\n");
        }
        else if(shapes[i].type == CIRCLE)
        {
            printf("Type : Circle\n");
        }
        else if(shapes[i].type == TRIANGLE)
        {
            printf("Type : Triangle\n");
        }

        if(shapes[i].alive == 1)
        {
            printf("Status : Active\n");
        }
        else
        {
            printf("Status : Deleted\n");
        }

        printf("-------------------------\n");
    }
}


void show_menu(void)
{
    printf("\n============================\n");
    printf("      SHAPE EDITOR MENU\n");
    printf("============================\n");
    printf("1 -> Rectangle\n");
    printf("2 -> Line\n");
    printf("3 -> Circle\n");
    printf("4 -> Triangle\n");
    printf("5 -> Delete\n");
    printf("6 -> Shape List\n");
    printf("7 -> Canvas View\n");
    printf("8 -> Quit\n");
}

void add_rectangle(void)
{
    int x, y, width, height;

    printf("Enter x: ");
    scanf("%d", &x);

    printf("Enter y: ");
    scanf("%d", &y);

    printf("Enter width: ");
    scanf("%d", &width);

    printf("Enter height: ");
    scanf("%d", &height);

    shapes[total].id = next_id++;
    shapes[total].type = RECTANGLE;
    shapes[total].alive = 1;
    shapes[total].x = x;
    shapes[total].y = y;
    shapes[total].a = width;
    shapes[total].b = height;

    total++;

    clear_canvas();
    redraw_shapes();
}

void add_line(void)
{
    int x1, y1, x2, y2;

    printf("Enter x1: ");
    scanf("%d", &x1);

    printf("Enter y1: ");
    scanf("%d", &y1);

    printf("Enter x2: ");
    scanf("%d", &x2);

    printf("Enter y2: ");
    scanf("%d", &y2);

    shapes[total].id = next_id++;
    shapes[total].type = LINE;
    shapes[total].alive = 1;
    shapes[total].x = x1;
    shapes[total].y = y1;
    shapes[total].a = x2;
    shapes[total].b = y2;

    total++;

    clear_canvas();
    redraw_shapes();
}

void add_circle(void)
{
    int x, y, radius;

    printf("Enter center x: ");
    scanf("%d", &x);

    printf("Enter center y: ");
    scanf("%d", &y);

    printf("Enter radius: ");
    scanf("%d", &radius);

    shapes[total].id = next_id++;
    shapes[total].type = CIRCLE;
    shapes[total].alive = 1;
    shapes[total].x = x;
    shapes[total].y = y;
    shapes[total].a = radius;

    total++;

    clear_canvas();
    redraw_shapes();
}

void add_triangle(void)
{
    int x, y, height;

    printf("Enter apex x: ");
    scanf("%d", &x);

    printf("Enter apex y: ");
    scanf("%d", &y);

    printf("Enter height: ");
    scanf("%d", &height);

    shapes[total].id = next_id++;
    shapes[total].type = TRIANGLE;
    shapes[total].alive = 1;
    shapes[total].x = x;
    shapes[total].y = y;
    shapes[total].a = height;

    total++;

    clear_canvas();
    redraw_shapes();
}
int main(void)
{
    int choice;
    int running = 1;

    clear_canvas();

    while(running)
    {
        show_menu();

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            add_rectangle();
        }
        else if(choice == 2)
        {
            add_line();
        }
        else if(choice == 3)
        {
            add_circle();
        }
        else if(choice == 4)
        {
            add_triangle();
        }
        else if(choice == 5)
        {
            delete_shape_menu();
        }
        else if(choice == 6)
        {
            list_shapes();
        }
        else if(choice == 7)
        {
            show_canvas();
        }
        else if(choice == 8)
        {
            printf("Exiting Program...\n");
            running = 0;
        }
        else
        {
            printf("Invalid Choice.\n");
        }
    }

    return 0;
}