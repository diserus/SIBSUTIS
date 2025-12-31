#include <iostream>
int *genRandArray(int size)
{
  int *arr = new int[size];
  for (int i = 0; i < size; i++)
    arr[i] = rand() % 100;
  return arr;
}

int **genRandmatrix(int size)
{
  int **matrix = new int *[size];
  for (int i = 0; i < size; i++)
    matrix[i] = genRandArray(size);
  return matrix;
}
void deletematrix(int **matrix, int size)
{
  for (int i = 0; i < size; i++)
    delete[] matrix[i];
  delete[] matrix;
}
void printmatrix(int **matrix, int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}
void printArray(int *a, int size)
{
  for (int i = 0; i < size; i++)
  {
    std::cout << a[i] << " ";
  }
  std::cout << "\n";
}

void getRightDiagonal(int **matrix, int N)
{
  int *D = new int[N * N];

  int I = 0;
  for (int n = 0; n < N; n++)
    for (int i = 0; i <= n; i++)
      D[I++] = matrix[i][n - i];
  for (int n = 1; n < N; n++)
    for (int i = 0; i < N - n; i++)
      D[I++] = matrix[i + n][N - i - 1];

  std::cout << "Right diagonal: ";
  printArray(D, N * N);

  delete[] D;
}

void getLeftDiagonal(int **matrix, int N)
{
  int *D = new int[N * N];
  int I = 0;
  for (int n = 0; n < N; n++)
    for (int i = 0; i <= n; i++)
      D[I++] = matrix[i + N - 1 - n][i];
  for (int n = 1; n < N; n++)
    for (int i = 0; i < N - n; i++)
      D[I++] = matrix[i][i + n];

  std::cout << "Left diagonal: ";
  printArray(D, N * N);

  delete[] D;
}
void spiralFromCenter(int **matrix, int N)
{
  int x = N / 2, y = N / 2;

  int *D = new int[N * N];
  int i = 0;
  int cnt = 1;
  int max_cnt = 1;
  int mode = 1;
  while (i < N * N)
  {
    D[i++] = matrix[y][x];
    switch (mode)
    {
    case 1:
      cnt--;
      y--;
      if (cnt == 0)
      {

        mode = 2;
        cnt = max_cnt;
      }
      break;
    case 2:
      cnt--;
      x--;
      if (cnt == 0)
      {
        max_cnt++;
        mode = 3;
        cnt = max_cnt;
      }
      break;
    case 3:
      cnt--;
      y++;
      if (cnt == 0)
      {
        mode = 4;
        cnt = max_cnt;
      }
      break;
    case 4:
      cnt--;
      x++;
      if (cnt == 0)
      {
        mode = 1;
        max_cnt++;
        cnt = max_cnt;
      }
      break;
    default:
      break;
    }
  }
  std::cout << "Spiral from center: ";
  printArray(D, N * N);

  delete[] D;
}
void spiralFromTopLeft(int **matrix, int N)
{
  int x = 0, y = 0;

  int *D = new int[N * N];
  int i = 0;
  int cnt = N - 1;
  int max_cnt = N;
  int mode = 1;
  while (i < N * N)
  {
    D[i++] = matrix[y][x];
    switch (mode)
    {
    case 1:
      cnt--;
      x++;
      if (cnt == 0)
      {

        mode = 2;
        max_cnt--;
        cnt = max_cnt;
      }
      break;
    case 2:
      cnt--;
      y++;
      if (cnt == 0)
      {
        mode = 3;
        cnt = max_cnt;
      }
      break;
    case 3:
      cnt--;
      x--;
      if (cnt == 0)
      {
        max_cnt--;
        mode = 4;
        cnt = max_cnt;
      }
      break;
    case 4:
      cnt--;
      y--;
      if (cnt == 0)
      {
        mode = 1;
        cnt = max_cnt;
      }
      break;
    default:
      break;
    }
  }
  std::cout << "Spiral from top left: ";
  printArray(D, N * N);

  delete[] D;
}

int main()
{
  srand(time(NULL));
  int size = 4;
  int **matrix = genRandmatrix(size);
  printmatrix(matrix, size);
  int *D = new int[size * size];
  getRightDiagonal(matrix, size);
  getLeftDiagonal(matrix, size);
  spiralFromCenter(matrix, size);
  spiralFromTopLeft(matrix, size);

  deletematrix(matrix, size);
  delete[] D;
  return 0;
}
