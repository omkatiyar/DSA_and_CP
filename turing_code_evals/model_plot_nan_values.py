import matplotlib.pyplot as plt

def plotNanValue(data):
    # Find the positions of NaNs
    nan_positions = data.isna()

    # Get the row indices (index) and column names (columns) of NaNs
    nan_rows, nan_cols = nan_positions.stack().index.get_level_values(0), nan_positions.stack().index.get_level_values(1)

    # Create the scatterplot
    plt.figure(figsize=(10, 6))
    plt.scatter(nan_cols, nan_rows, marker='o', color='red')

    plt.xlabel('Column Names')
    plt.ylabel('Row Indices')
    plt.title('Scatterplot of NaN Values')
    plt.grid(True)
    
    return nan
