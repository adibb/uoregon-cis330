#define ROW 3
#define COL 4

bool arrayEqual(int a[ROW][COL], int b[ROW][COL], int m, int n)
{
    /* Compare two arrays for equality */
    int i = 0, j = 0;
    for (; i < ROW; i++){
        for (; j < COL; j++){
            if (a[i	][j] != b[i][j])
                return 0;
        }
    }
    
    return 1;
}

int main(int argc, const char * argv[])
{

    int a[ROW][COL] = {
        {0, 1, 2, 3} ,
        {4, 5, 6, 7} ,
        {8, 9, 10, 11}
    };

    int b[ROW][COL] = {
        {0, 1, 2, 3} ,
        {4, -1, 6, 7} ,
        {8, 9, 10, 11}   
    };


   // put your code here ...

    return 0;
}