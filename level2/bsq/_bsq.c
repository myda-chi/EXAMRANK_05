#include "stdio.h"
#include "unistd.h"
#include "errno.h"

// Returns minimum of three integers (helper for DP recurrence)
static int min3(int a, int b, int c)
{
    if (b < a)
        a = b; // Update a if b is smaller
    if (c < a)
        a = c;  // Update a if c is smaller
    return (a); // Return the minimum value
}

// Parse map file: read header (rows, empty, obstacle, full chars) and grid
static int parse_map(FILE *fp, int *rows, int *cols,
                     char *empty, char *obstacle, char *full, char ***grid)
{
    char *line = NULL; // Buffer for getline (allocated by getline)
    size_t len = 0;    // Buffer size (managed by getline)
    int i, j;          // Loop counters

    // Read first line: "rows empty_char obstacle_char full_char"
    // Validate: must have 4 items, rows > 0, chars must be distinct
    if (fscanf(fp, "%d %c %c %c\n", rows, empty, obstacle, full) != 4 || *rows <= 0 || *empty == *obstacle || *empty == *full || *obstacle == *full)
        return (-1); // Header invalid
    // Allocate array of row pointers
    *grid = (char **)malloc(sizeof(char *) * (*rows));
    if (!*grid)
        return (-1); // Allocation failed
    *cols = -1;      // Column count unknown until first line read
    // Read each row from file
    for (i = 0; i < *rows; i++)
    {
        (*grid)[i] = NULL; // Initialize pointer (for safety)
        line = NULL;       // Reset line pointer for getline
        len = 0;           // Reset buffer size for getline
        // Read one line (getline allocates memory automatically)
        if (getline(&line, &len, fp) <= 0)
            return (free(line), -1); // Read failed or EOF
        j = strlen(line);            // Get line length
        // Remove trailing newline if present
        if (j > 0 && line[j - 1] == '\n')
            line[--j] = '\0';
        // Empty line is invalid
        if (j <= 0)
            return (free(line), -1);
        // Set column count from first row
        if (*cols == -1)
            *cols = j;
        // All subsequent rows must have same width
        else if (j != *cols)
            return (free(line), -1); // Width mismatch
        // Validate each cell: must be empty or obstacle
        for (j = 0; j < *cols; j++)
            if (line[j] != *empty && line[j] != *obstacle)
                return (free(line), -1); // Invalid character
        (*grid)[i] = line;               // Store line pointer in grid
    }
    return (0); // Success
}

// Find largest square using DP, then fill it with 'full' character
static void find_and_fill(char **grid, int rows, int cols, char obstacle, char full)
{
    int i, j, best = 0, br = 0, bc = 0;                // best = max size, br/bc = bottom-right position
    int *dp = (int *)calloc(rows * cols, sizeof(int)); // DP table: dp[i][j] = max square size ending at (i,j)

    // Build DP table: for each cell, compute largest square ending there
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
        {
            // If cell is obstacle, no square can end here
            if (grid[i][j] == obstacle)
                dp[i * cols + j] = 0;
            // First row or column: max size is 1 (base case)
            else if (i == 0 || j == 0)
                dp[i * cols + j] = 1;
            // Recurrence: dp[i][j] = min(up, left, diagonal) + 1
            // This works because a k×k square needs (k-1)×(k-1) squares at all 3 neighbors
            else
                dp[i * cols + j] = min3(dp[(i - 1) * cols + j], // up
                                        dp[i * cols + j - 1], dp[(i - 1) * cols + j - 1]) +
                                   1; // left, diagonal
            // Track maximum square size and its bottom-right position
            if (dp[i * cols + j] > best)
            {
                best = dp[i * cols + j]; // Update max size
                br = i;                  // Save bottom-right row
                bc = j;                  // Save bottom-right col
            }
        }
    // Fill the square: from top-left (br-best+1, bc-best+1) to bottom-right (br, bc)
    for (i = br - best + 1; i <= br; i++)
        for (j = bc - best + 1; j <= bc; j++)
            grid[i][j] = full; // Replace with 'full' character
    free(dp);                  // Free DP table
}

// Main solving function: parse map, find largest square, print result
static int solve(FILE *fp)
{
    char empty, obstacle, full, **grid; // Map characters and 2D grid
    int rows, cols, i;                  // Dimensions and loop counter

    // Parse the map file into grid structure
    if (parse_map(fp, &rows, &cols, &empty, &obstacle, &full, &grid) < 0)
        return (-1); // Parse failed (invalid format)
    // Find largest square and fill it in-place
    find_and_fill(grid, rows, cols, obstacle, full);
    // Print the modified grid
    for (i = 0; i < rows; i++)
    {
        fputs(grid[i], stdout); // Print row
        fputs("\n", stdout);    // Print newline
        free(grid[i]);          // Free row memory
    }
    free(grid); // Free grid array
    return (0); // Success
}

// Entry point: handle stdin or multiple file arguments
int main(int argc, char **argv)
{
    FILE *fp; // File pointer for reading maps
    int i;    // Loop counter for arguments

    // No arguments: read from stdin
    if (argc == 1)
    {
        if (solve(stdin) < 0)               // Solve map from stdin
            fprintf(stderr, "map error\n"); // Print error on failure
        return (0);
    }
    // Process each file argument
    for (i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");           // Open file for reading
        if (!fp || solve(fp) < 0)           // Open failed or solve failed
            fprintf(stderr, "map error\n"); // Print error message
        if (fp)
            fclose(fp); // Close file if opened
        if (i < argc - 1)
            fputs("\n", stdout); // Print separator between multiple files
    }
    return (0);
}