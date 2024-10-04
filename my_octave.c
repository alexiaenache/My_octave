#include <stdio.h>
#include <stdlib.h>
#define mod 10007

void matrix_array(int ****mat_array, int *count, int **rows, int **columns) {
    int m, n, i, j;
    scanf("%d%d", &m, &n);
    (*count)++;
    // count-ul reprezinta numarul de matrici;
    (*rows) = (int *)realloc(*rows, (*count) * sizeof(int));
    if ((*rows) == NULL) {
        fprintf(stderr, "Realloc failed\n");
        return;
    }
    (*columns) = (int *)realloc(*columns, (*count) * sizeof(int));
    if ((*columns) == NULL) {
        fprintf(stderr, "Realloc failed\n");
        return;
    }
    (*rows)[(*count) - 1] = m;
    (*columns)[(*count) - 1] = n;
    // aloc memorie pentru noua matrice
    (*mat_array) = (int ***)realloc((*mat_array), (*count) * sizeof(int **));
    if ((*mat_array) == NULL) {
        // daca nu pot aloca opresc executia si afisez un mesaj;
        fprintf(stderr, "Realloc for matrix failed\n");
        return;
    }
    (*mat_array)[(*count) - 1] = (int **)malloc(m * sizeof(int *));
    for (i = 0; i < m; i++) {
        (*mat_array)[(*count) - 1][i] = (int *)malloc((n) * sizeof(int));
    }
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &(*mat_array)[(*count) - 1][i][j]);
}

void print_matrix(int n, int m, int **mat) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    // printf("%d\n", mat[n-1][m-1]);
}

void multiplyMatrix(int ****mat_array, int index1, int index2, int *count, int **rows, int **columns) {
    // int index1, index2;
    // scanf("%d%d", &index1, &index2);

    if (index1 >= *count || index2 >= *count || index1 < 0 || index2 < 0) {
        printf("No matrix with the given index\n");
        return;
    }

    if ((*columns)[index1] != (*rows)[index2]) {
        printf("Cannot perform matrix multiplication\n");
        return;
    }

    // Alocare memorie pentru matricea rezultat
    int result_rows = (*rows)[index1];
    int result_columns = (*columns)[index2];
    int **result_matrix = (int **)malloc(result_rows * sizeof(int *));
    for (int i = 0; i < result_rows; i++) {
        result_matrix[i] = (int *)malloc(result_columns * sizeof(int));
    }

    // Calculul produsului matricilor
    for (int i = 0; i < result_rows; i++) {
        for (int j = 0; j < result_columns; j++) {
            result_matrix[i][j] = 0;
            for (int k = 0; k < (*columns)[index1]; k++) {
                result_matrix[i][j] += (*mat_array)[index1][i][k] * (*mat_array)[index2][k][j] % mod;
                result_matrix[i][j] = ((result_matrix[i][j] % mod) + mod) % mod;
            }
        }
    }

    // Adăugare matrice rezultat în colecție
    (*count)++;
    *rows = (int *)realloc(*rows, (*count) * sizeof(int));
    *columns = (int *)realloc(*columns, (*count) * sizeof(int));
    (*rows)[(*count) - 1] = result_rows;
    (*columns)[(*count) - 1] = result_columns;
    *mat_array = (int ***)realloc(*mat_array, (*count) * sizeof(int **));
    (*mat_array)[(*count) - 1] = result_matrix;
}

void swap_matrix(int ***mat_1, int ***mat_2) {
    int **aux = (*mat_1);
    (*mat_1) = (*mat_2);
    (*mat_2) = (aux);
}

void transpusa(int n, int m, int ***mat) {
    int **aux;
    int i, j;

    aux = (int **)malloc(m * sizeof(int *));
    for (i = 0; i < m; i++) {
        aux[i] = (int *)malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            aux[j][i] = (*mat)[i][j];
    // eliberez matricea originala
    for (i = 0; i < n; i++)
        free((*mat)[i]);
    free((*mat));

    (*mat) = (int **)malloc(m * sizeof(int *));
    for (i = 0; i < m; i++) {
        (*mat)[i] = (int *)malloc(n * sizeof(int));
    }
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            (*mat)[i][j] = aux[i][j];
    // eliberez matricea auxiliara
    for (i = 0; i < m; i++)
        free(aux[i]);
    free(aux);
}

int suma_elementelor(int ***mat, int n, int m) {
    int i, j, sum = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) {
            sum = (sum + (*mat)[i][j]) % mod;
            sum = ((sum % mod) + mod) % mod;
        }

    return sum;
}

void sortare(int ****mat, int *count, int **rows, int **columns) {
    for (int i = 0; i < (*count) - 1; i++) {
        for (int j = i + 1; j < (*count); j++) {
            if (suma_elementelor(&(*mat)[i], (*rows)[i], (*columns)[i]) > suma_elementelor(&(*mat)[j], (*rows)[j], (*columns)[j])) {
                swap_matrix(&(*mat)[i], &(*mat)[j]);
                int aux = (*rows)[i];
                (*rows)[i] = (*rows)[j];
                (*rows)[j] = aux;
                aux = (*columns)[i];
                (*columns)[i] = (*columns)[j];
                (*columns)[j] = aux;
            }
        }
    }
}

void dimensiuni(int count, int *rows, int *columns) {
    int index;
    scanf("%d", &index);
    if (index >= count || index <= -1)
        printf("No matrix with the given index\n");
    else
        printf("%d %d\n", rows[index], columns[index]);
}

void resize(int ****mat, int **rows, int **columns, int *count) {
    int index, newRows, newColumns;
    scanf("%d", &index);

    scanf("%d", &newRows);
    int newRowOrder[newRows];
    for (int i = 0; i < newRows; i++) {
        scanf("%d", &newRowOrder[i]);
    }

    scanf("%d", &newColumns);
    int newColumnOrder[newColumns];
    for (int i = 0; i < newColumns; i++) {
        scanf("%d", &newColumnOrder[i]);
    }

    if (index < 0 || index >= *count) {
        printf("No matrix with the given index\n");
        return;
    }

    int **matrix = (*mat)[index];
    int **resizedMatrix = (int **)malloc(newRows * sizeof(int *));
    for (int i = 0; i < newRows; i++) {
        resizedMatrix[i] = (int *)malloc(newColumns * sizeof(int));
        for (int j = 0; j < newColumns; j++) {
            resizedMatrix[i][j] = matrix[newRowOrder[i]][newColumnOrder[j]];
        }
    }

    // eliberez memoria matricei vechi
    for (int i = 0; i < (*rows)[index]; i++) {
        free(matrix[i]);
    }
    free(matrix);

    (*rows)[index] = newRows;
    (*columns)[index] = newColumns;
    (*mat)[index] = resizedMatrix;
}

void free_mat(int ***mat_array, int *rows, int index, int *nr) {
    int **matrix = mat_array[index];
    for (int i = 0; i < rows[index]; i++)
        free(matrix[i]);
    free(matrix);
    // for(int j=index;j<(*nr);j++){
    //     (mat_array)[j]=(mat_array)[j+1];
    //     (rows)[j]=(rows)[j+1];
    //     (columns)[j]=(columns)[j+1];
    // }
    (*nr)--;
}

void eliberare(int ****mat_array, int **rows, int **columns, int *count) {
    // eliberam colectia
    int i, j;
    for (i = 0; i < (*count); i++) {
        for (j = 0; j < (*rows)[i]; j++)
            free((*mat_array)[i][j]);
        free((*mat_array)[i]);
    }
    free(*mat_array);
    // eliberam vectorii de dimensiuni
    free(*rows);
    free(*columns);
    (*count) = 0;
}

void add(int **a, int **b, int **c, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            c[i][j] = (a[i][j] + b[i][j]) % mod;
            c[i][j] = ((c[i][j] % mod) + mod) % mod;
        }
}

void sub(int **a, int **b, int **c, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            c[i][j] = (a[i][j] - b[i][j]) % mod;
            c[i][j] = ((c[i][j] % mod) + mod) % mod;
        }
}

int putere2(int x)
{
	if (x % 2 == 1)
		return 0;
	if (x == 1)
		return 1;
	while (x % 2 == 0)
		x /= 2;
	if (x == 1)
		return 1;
	return 0;
}

void strassen(int **a, int **b, int **c, int n) {
    if (n == 1) {
        c[0][0] = (a[0][0] * b[0][0]) % mod;
        c[0][0] = ((c[0][0] % mod) + mod) % mod;
    } else {
        // impart matricea a si b in matrici de n/2
        int i, j;
        int dim = n / 2;
        int ***M;
        // Alocare matrice M pentru stocarea rezultatelor intermediare
        M = (int ***)malloc(30 * sizeof(int **));
        for (i = 0; i < 30; i++) {
            M[i] = (int **)malloc(dim * sizeof(int *));
            for (j = 0; j < dim; j++) {
                M[i][j] = (int *)malloc(dim * sizeof(int));
            }
        }  
    

        for (i = 0; i < dim; i++) {
			for (j = 0; j < dim; j++) {
				M[0][i][j] = a[i][j];                // a11 - A1
				M[1][i][j] = a[i][j + dim];         // a12 - A2
				M[2][i][j] = a[i + dim][j];         // a21 - A3
				M[3][i][j] = a[i + dim][j + dim];  // a22 - A4
				M[4][i][j] = b[i][j];                // b11 - B1
				M[5][i][j] = b[i][j + dim];         // b12 -  B2
				M[6][i][j] = b[i + dim][j];         // b21 - b3
				M[7][i][j] = b[i + dim][j + dim];  // b22 - b4
			}
		}

        // Calcul matricelor auxiliare
        add(M[0], M[3], M[8], dim); // a1 + a4
        add(M[4], M[7], M[9], dim); // b1 + b4
        add(M[2], M[3], M[10], dim); // a3 + a4
        sub(M[5], M[7], M[11], dim); // b2 - b4
        sub(M[6], M[4], M[12], dim); // b3 - b1
        sub(M[0], M[1], M[13], dim); // a1+a2
        add(M[2], M[0], M[14], dim);//a3 - a1
        add(M[4], M[5], M[15], dim);//b1 + b2
        sub(M[1], M[3], M[16], dim);//a2 - a4
        add(M[6], M[7], M[17], dim);//b3 + b4

        // Calculul produselor P1-P7
        strassen(M[8], M[9], M[18], dim); // P1 = (a1 + a4) * (b1 + b4)
        strassen(M[10], M[4], M[19], dim); // P2 = (a3 + a4) * b1
        strassen(M[0], M[11], M[20], dim); // p3 = a1 * (b2 - b4)
        strassen(M[3], M[12], M[21], dim); // p4 = a4 * (b3 - b1)
        strassen(M[13], M[7], M[22], dim); // p5 = (a1 + a2) * b4
        strassen(M[14], M[15], M[23], dim); // p6 = (a3 - a1) * (b1 + b2)
        strassen(M[16], M[17], M[24], dim); // p7 = (a2 - a4) * (b3 + b4)

        // Calculul matricii rezultat
        add(M[18], M[21], M[25], dim); // c11 = p1 + p4 
        sub(M[25], M[22], M[25], dim); // c11 = p1 + p4 - p5
        add(M[25], M[24], M[25], dim); // c11 = p1 + p4 - p5 + p7
        add(M[20], M[22], M[26], dim); // c12 = p3 + p5
        add(M[19], M[21], M[27], dim); // c21 = p2 + p4
        sub(M[18],M[19],M[28],dim); // c22 = p1 - p2
        add(M[28],M[20],M[28],dim); // c22 = p1 - p2 + p3
        add(M[28],M[23],M[28],dim); // c22 = p1 - p2 + p3 + p6

        // Construirea matricii rezultat
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim; j++) {
                c[i][j] = M[25][i][j];
                c[i][j + dim] = M[26][i][j];
                c[i + dim][j] = M[27][i][j];
                c[i + dim][j + dim] = M[28][i][j];
            }
        }

        // Eliberare memorie
        for (i = 0; i < 30; i++) {
            for (j = 0; j < dim; j++) {
                free(M[i][j]);
            }
            free(M[i]);
        }
        free(M);

    }
}

int main() {
    char oper_letter;
    int m, n, nr = -1, index, index1, index2, count = 0;
    int *rows, *columns, ***mat_array;
    mat_array = (int ***)malloc(1 * sizeof(int **));
    rows = (int *)malloc(1 * sizeof(int));
    columns = (int *)malloc(1 * sizeof(int));
    while (1) {
        scanf(" %c", &oper_letter);
        if (oper_letter == 'L' || oper_letter == 'P' || oper_letter == 'D' || oper_letter == 'Q' || oper_letter == 'T' || oper_letter == 'F' || oper_letter == 'M' || oper_letter == 'O' || oper_letter == 'C' || oper_letter == 'R' || oper_letter == 'S') {
            if (oper_letter == 'L') {
                matrix_array(&mat_array, &count, &rows, &columns);
            }
            if (oper_letter == 'P') {
                scanf("%d", &index);
                if (index >= count || index <= -1)
                    printf("No matrix with the given index\n");
                else
                    print_matrix(rows[index], columns[index], mat_array[index]);
            }
            if (oper_letter == 'D') {
                dimensiuni(count, rows, columns);
            }
            if (oper_letter == 'T') {
                int aux;
                scanf("%d", &index);
                if (index >= count || index <= -1)
                    printf("No matrix with the given index\n");
                else
                    transpusa(rows[index], columns[index], &mat_array[index]);
                aux = rows[index];
                rows[index] = columns[index];
                columns[index] = aux;
            }
            if (oper_letter == 'O') {
                sortare(&mat_array, &count, &rows, &columns);
            }
            if (oper_letter == 'F') {
                scanf("%d", &index);
                if (index >= count || index < 0)
                    printf("No matrix with the given index\n");
                else {  // free_mat(mat_array[index], rows, columns, index,&nr);
                    for (int i = index + 1; i < count; i++) {
                        swap_matrix(&mat_array[i - 1], &mat_array[i]);
                        int aux = rows[i];
                        rows[i] = rows[i - 1];
                        rows[i - 1] = aux;
                        aux = columns[i];
                        columns[i] = columns[i - 1];
                        columns[i - 1] = aux;
                    }
                    free_mat(mat_array, rows, count - 1, &count);
                }
            }
            if (oper_letter == 'M') {
                scanf("%d%d", &index1, &index2);
                multiplyMatrix(&mat_array, index1, index2, &count, &rows, &columns);
            }
            if (oper_letter == 'C') {
                resize(&mat_array, &rows, &columns, &count);
            }
            if (oper_letter == 'Q') {
                eliberare(&mat_array, &rows, &columns, &count);
                break;
            }
            // if (oper_letter == 'R') {
            //     powerMatrix(&mat_array, &count, &rows, &columns);
            // }
            if(oper_letter == 'S') {
              scanf("%d %d", &index1, &index2);
                if (index1 >= count || index2 >= count || index1 < 0 || index2 < 0) {
                    printf("No matrix with the given index\n");
                    continue;
                }
                (*mat_array) = (int ***)realloc((*mat_array), (count + 1) * sizeof(int **));
                mat_array[count] = (int **)malloc(rows[index1] * sizeof(int *));
                for (int i = 0; i < rows[index1]; i++) {
                    mat_array[count][i] = (int *)malloc(columns[index1] * sizeof(int));
                }
                rows[count] = rows[index1];
                columns[count] = columns[index1];
                strassen(mat_array[index1], mat_array[index2], mat_array[count], rows[index1]); 
                count++;
            }
        } else {
            printf("Unrecognized command\n");
        }
    }
}