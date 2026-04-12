#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "lib/Image.hpp"
#include "List.hpp"
#include "Queue.hpp"

struct State {
  intmax_t row;
  intmax_t col;
};

int main(int argc, char *argv[])
{
  // get input/output file names from command line arguments
  if (argc != 3) {
    std::cout << "Usage: pathfinder "
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }

  std::string input_file = argv[1];
  std::string output_file = argv[2];

  // Read input image from file
  Image image;
  try {
    image = readFromFile(input_file);
  } catch (std::exception& ex) {
    std::cerr << "Error: could not read input file: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  intmax_t rows = image.height();
  intmax_t cols = image.width();

  // Find start pixel (red)
  intmax_t startRow = -1, startCol = -1;
  int redCount = 0;

  for (intmax_t r = 0; r < rows; r++){
    for (intmax_t c = 0; c < cols; c++){
      Pixel p = image(r, c);
      if (p == RED){
        redCount++;
        startRow = r;
        startCol = c;
        if (redCount > 1){
          std::cerr << "Error: maze has more than one red pixel" << std::endl;
          return EXIT_FAILURE;
        }
      } else if (p != BLACK && p != WHITE){
        std::cerr << "Error: maze contains invalid pixel color" << std::endl;
      }
    }
  }

  if (redCount == 0){
    std::cerr << "Error: maze has no starting (red) pixel" << std::endl;
    return EXIT_FAILURE;
  }

  // Check if start is on the border
  auto isGoal = [&](intmax_t r, intmax_t c) -> bool {
    return (r == 0 || r == rows - 1 || c == 0 || c == cols - 1);
  };

  if (isGoal(startRow, startCol)){
    image(startRow, startCol) = GREEN;
    writeToFile(image, output_file);
    std::cout << "Solution Found" << std::endl;
    return EXIT_SUCCESS;
  }

  // Explored 2D grid
  std::vector<std::vector<bool>> explored(rows, std::vector<bool>(cols, false));

  // Breadth-first Search
  Queue<State, List<State>> frontier;
  State initial = {startRow, startCol};
  frontier.enqueue(initial);
  explored[startRow][startCol] = true;

  bool found = false;

  const intmax_t dr[] = {-1, 1, 0, 0};
  const intmax_t dc[] = {0, 0, -1, 1};

  while (!frontier.isEmpty()){
    State s = frontier.peekFront();
    frontier.dequeue();

    if (isGoal(s.row, s.col)){
      image(s.row, s.col) = GREEN;
      found = true;
      break;
    }

    for (int d = 0; d < 4; d++){
      intmax_t nr = s.row + dr[d];
      intmax_t nc = s.col + dc[d];

      if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;

      if (image(nr, nc) != WHITE) continue;

      if (explored[nr][nc]) continue;

      explored[nr][nc] = true;
      State next = {nr, nc};
      frontier.enqueue(next);
    }
  }

  // Write solution image to file
  if (found){
    std::cout << "Solution Found" << std::endl;
  } else {
    std::cout << "No Solution Found" << std::endl;
  }

  try {
    writeToFile(image, output_file);
  } catch (std::exception& ex){
    std::cerr << "Error: could not write output file: " << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
  
}
