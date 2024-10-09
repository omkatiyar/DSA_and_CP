#include <raylib-cpp.hpp>
#include <vector>

int main()
{
    const int width = 1280;
    const int height = 800;

    raylib::Window window(width, height, "PACMAN");

    // Maze settings
    const int tileSize = 25;  // Dimension of each tile (in pixels)
    const float pacColliderRadius = tileSize / 2.0f; // Radius for collision detection
    const float bufferSpace = 5.0f; // Buffer space to avoid direction change near walls

    // Simple maze layout (1 = wall, 0 = path)
    std::vector<std::vector<int>> maze = {
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    // Function for rendering the maze
    auto renderMaze = [&maze, tileSize]() {
        for (size_t y = 0; y < maze.size(); ++y) {
            for (size_t x = 0; x < maze[y].size(); ++x) {
                Color color;
                if (maze[y][x] == 1) {
                    color = GREEN;
                } else if (maze[y][x] == 2) {
                    color = PURPLE; // Use purple for segment with value 2
                } else {
                    color = BLUE;
                }
                DrawRectangle(x * tileSize + 50, y * tileSize + 100, tileSize, tileSize, color);
            }
        }
    };


    // Pac-Man's properties
    float pacX = 75 + tileSize / 2; // Center of the first tile (0,0)
    float pacY = 100 + tileSize / 2; // Center of the first tile (0,0)
    float pacVisualRadius = 10.0f; // Radius for visual representation

    window.SetTargetFPS(60);

    float movementSpeed = 3.0f;
    int pacDirection = 1; // Start moving down

    // Variables for Pac-Man's mouth animation
    float angleOfMouth = 90.0f; // Initial mouth angle
    bool isMouthOpening = false;

    // Collision detection function (check for walls in the maze)
    auto detectCollisionWithWalls = [&](float x, float y, float radius) {
        int tileX = static_cast<int>((x - 50) / tileSize);
        int tileY = static_cast<int>((y - 100) / tileSize);

        if (tileX >= 0 && tileY >= 0 && tileY < maze.size() && tileX < maze[0].size()) {
            if (maze[tileY][tileX] == 1) {
                // Check if Pac-Man's center is inside the wall
                if (x >= tileX * tileSize + 50 && x <= (tileX + 1) * tileSize + 50 &&
                    y >= tileY * tileSize + 100 && y <= (tileY + 1) * tileSize + 100) {
                    return true;
                }
            }
        }
        return false;
    };

    // Determine if Pac-Man is close to a wall in the current direction
    auto proximityToWall = [&](int direction) {
        float checkX = pacX;
        float checkY = pacY;

        switch (direction) {
            case 0: // Right
                checkX += pacColliderRadius + bufferSpace;
                break;
            case 1: // Down
                checkY += pacColliderRadius + bufferSpace;
                break;
            case 2: // Left
                checkX -= pacColliderRadius + bufferSpace;
                break;
            case 3: // Up
                checkY -= pacColliderRadius + bufferSpace;
                break;
        }

        return detectCollisionWithWalls(checkX, checkY, pacColliderRadius);
    };

    // Determine if a direction change is permissible
    auto canChangeDirection = [&](int newDir) {
        float futureX = pacX;
        float futureY = pacY;

        switch (newDir) {
            case 0: // Right
                futureX += pacColliderRadius + bufferSpace;
                break;
            case 1: // Down
                futureY += pacColliderRadius + bufferSpace;
                break;
            case 2: // Left
                futureX -= pacColliderRadius + bufferSpace;
                break;
            case 3: // Up
                futureY -= pacColliderRadius + bufferSpace;
                break;
        }

        return !detectCollisionWithWalls(futureX, futureY, pacColliderRadius);
    };

    // Align Pac-Man in the tile
    auto alignPacMan = [&]() {
        int tileX = static_cast<int>((pacX - 50) / tileSize);
        int tileY = static_cast<int>((pacY - 100) / tileSize);

        if (tileX >= 0 && tileY >= 0 && tileY < maze.size() && tileX < maze[0].size() && maze[tileY][tileX] == 0) {
            pacX = tileX * tileSize + 50 + tileSize / 2;
            pacY = tileY * tileSize + 100 + tileSize / 2;
        }
    };

    // Update Pac-Man's position based on his direction
    auto updatePacLocation = [&]() {
        float futureX = pacX;
        float futureY = pacY;

        switch (pacDirection) {
            case 0: // Right
                futureX += movementSpeed;
                break;
            case 1: // Down
                futureY += movementSpeed;
                break;
            case 2: // Left
                futureX -= movementSpeed;
                break;
            case 3: // Up
                futureY -= movementSpeed;
                break;
        }

        // Check collisions with walls before updating position
        bool collisionRight = detectCollisionWithWalls(futureX + pacColliderRadius, pacY, pacColliderRadius);
        bool collisionLeft = detectCollisionWithWalls(futureX - pacColliderRadius, pacY, pacColliderRadius);
        bool collisionDown = detectCollisionWithWalls(pacX, futureY + pacColliderRadius, pacColliderRadius);
        bool collisionUp = detectCollisionWithWalls(pacX, futureY - pacColliderRadius, pacColliderRadius);

        if (pacDirection == 0 && !collisionRight) {
            pacX = futureX;
        } else if (pacDirection == 1 && !collisionDown) {
            pacY = futureY;
        } else if (pacDirection == 2 && !collisionLeft) {
            pacX = futureX;
        } else if (pacDirection == 3 && !collisionUp) {
            pacY = futureY;
        }

        // Align Pac-Man after movement
        alignPacMan();
    };

    while (!window.ShouldClose())
    {
        // Handle input to change Pac-Man's direction
        int newDir = pacDirection;

        if (IsKeyDown(KEY_RIGHT)) {
            newDir = 0; // Face right
        } 
        else if (IsKeyDown(KEY_DOWN)) {
            newDir = 1; // Face down
        } 
        else if (IsKeyDown(KEY_LEFT)) {
            newDir = 2; // Face left
        } 
        else if (IsKeyDown(KEY_UP)) {
            newDir = 3; // Face up
        }

        // Only update direction if Pac-Man is not too close to a wall in the new direction
        if (canChangeDirection(newDir)) {
            pacDirection = newDir;
        }

        // Update Pac-Man's position based on the direction
        updatePacLocation();

        // Animate Pac-Man's mouth
        if (isMouthOpening) {
            angleOfMouth -= 5.0f; // Open the mouth
            if (angleOfMouth <= 10.0f) {
                isMouthOpening = false;
            }
        } else {
            angleOfMouth += 5.0f; // Close the mouth
            if (angleOfMouth >= 60.0f) {
                isMouthOpening = true;
            }
        }

        // Drawing the scene
        window.BeginDrawing();
        window.ClearBackground(BLACK);

        // Render maze
        renderMaze();

        // Draw Pac-Man with a fixed visual size but adjusted collider
        DrawCircle(pacX, pacY, pacVisualRadius, YELLOW);
        float startAngle = pacDirection == 0 ? -angleOfMouth / 2 : pacDirection == 1 ? 90 - angleOfMouth / 2 : pacDirection == 2 ? 180 - angleOfMouth / 2 : 270 - angleOfMouth / 2;
        float endAngle = pacDirection == 0 ? angleOfMouth / 2 : pacDirection == 1 ? 90 + angleOfMouth / 2 : pacDirection == 2 ? 180 + angleOfMouth / 2 : 270 + angleOfMouth / 2;
        DrawCircleSector({pacX, pacY}, pacVisualRadius, startAngle, endAngle, 0, BLACK);

        window.EndDrawing();
    }

    return 0;
}
