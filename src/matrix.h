typedef struct
{
    int totalRows;
    int totalColumns;
    int **items;
} Matrix;

Matrix extractMatrixFromFile(char *path);

void printMatrix(Matrix m);

void cleanMatrix(Matrix m);