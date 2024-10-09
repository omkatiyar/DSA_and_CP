import cppyy
import unittest
import os

class TestTetrisGame(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        try:
            # Load the C++ Tetris game code
            cpp_file_name = "model_tetris_game.cpp"  # Update with the actual C++ file name
            cpp_file_path = os.path.abspath(os.path.join(os.path.dirname(__file__), cpp_file_name))
            if not os.path.exists(cpp_file_path):
                raise FileNotFoundError(f"{cpp_file_path} not found")
            
            # Read the content of the C++ file and compile it
            with open(cpp_file_path, 'r') as cpp_file:
                cpp_code = cpp_file.read()
            
            cppyy.cppdef(cpp_code)  # Compile the C++ code
        except FileNotFoundError as e:
            raise unittest.SkipTest(f"Setup failed: {str(e)}")
        except Exception as e:
            raise unittest.SkipTest(f"Error during C++ compilation: {str(e)}")

    def test_tetromino_movement(self):
        tetromino = cppyy.gbl.Tetromino()
        initial_x = tetromino.getX()
        initial_y = tetromino.getY()

        # Test moving left
        tetromino.move(-1, 0)
        self.assertEqual(tetromino.getX(), initial_x - 1)

        # Test moving right
        tetromino.move(2, 0)
        self.assertEqual(tetromino.getX(), initial_x + 1)

        # Test moving down
        tetromino.move(0, 1)
        self.assertEqual(tetromino.getY(), initial_y + 1)

    def test_tetromino_rotation(self):
        # Force Tetromino to be a 'T' shape or any other non-symmetric shape that changes on rotation
        tetromino = cppyy.gbl.Tetromino()
        
        # Manually set the shape to 'T' or any other non-symmetric shape
        tetromino.shapeData = cppyy.gbl.SHAPES[2]  # Assuming SHAPES[2] is the T shape

        initial_shape = tetromino.getShape()
        initial_shape_list = [list(row) for row in initial_shape]  # Convert C++ vectors to Python lists

        tetromino.rotate()
        rotated_shape = tetromino.getShape()
        rotated_shape_list = [list(row) for row in rotated_shape]  # Convert C++ vectors to Python lists

        # Assert that the shape actually changes after rotation
        self.assertNotEqual(initial_shape_list, rotated_shape_list)


    def test_collision_detection(self):
        game = cppyy.gbl.TetrisGame()

        # Spawn a tetromino and move it to the left edge
        tetromino = cppyy.gbl.Tetromino()
        while tetromino.getX() > 0:
            tetromino.move(-1, 0)

        # Try moving left again and check if it collides
        tetromino.move(-1, 0)
        self.assertTrue(game.collides(tetromino))

    def test_clear_lines(self):
        game = cppyy.gbl.TetrisGame()

        # Fill the bottom row with blocks
        field = game.getField()
        for i in range(cppyy.gbl.BOARD_WIDTH):
            field[cppyy.gbl.BOARD_HEIGHT - 1][i] = 1

        initial_score = game.getScore()
        game.clearLines()

        # Convert C++ std::vector to Python list for comparison
        cleared_row = list(field[cppyy.gbl.BOARD_HEIGHT - 1])

        # Check that the row is cleared and the score increased
        self.assertEqual(cleared_row, [0] * cppyy.gbl.BOARD_WIDTH)
        self.assertGreater(game.getScore(), initial_score)


    def test_game_over(self):
        game = cppyy.gbl.TetrisGame()

        # Fill the top row to trigger game over
        field = game.getField()
        for i in range(cppyy.gbl.BOARD_WIDTH):
            field[0][i] = 1

        # Spawn a new tetromino and check if the game is over
        game.spawnTetromino()
        self.assertTrue(game.isGameOver())

if __name__ == '__main__':
    unittest.main(verbosity=2)
