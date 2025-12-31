#include <cstdlib>
#include <iostream>

int main()
{
  srand(time(NULL));

  int N = rand() % 10 + 1;
  int **matrix = new int *[N];

  for (int i = 0; i < N; i++)
  {
    int R = rand() % 10 + 2;
    matrix[i] = new int[R];
    matrix[i][0] = R - 1;
  }

  for (int i = 0; i < N; i++)
  {
    for (int j = 1; j < matrix[i][0] + 1; j++)
    {
      matrix[i][j] = rand() % 50 + 1;
    }
  }

  for (int i = 0; i < N; i++)
  {
    std::cout << i + 1 << " stroka: ";
    for (int j = 1; j < matrix[i][0] + 1; j++)
    {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }

  for (int i = 0; i < N; i++)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
  return 0;
}
