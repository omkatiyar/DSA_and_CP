# ideal_completion.py

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

def plotNanValue(data):
    # Find the positions of NaNs
    nan_positions = data.isna()

    # Filter the stacked series to get only NaN positions
    nan_positions_stack = nan_positions.stack()
    nan_rows, nan_cols = nan_positions_stack[nan_positions_stack].index.get_level_values(0), nan_positions_stack[nan_positions_stack].index.get_level_values(1)

    #Create the scatterplot
    plt.figure(figsize=(10, 6))
    plt.scatter(nan_cols, nan_rows, marker='o', color='red')

    plt.xlabel('Column Names')
    plt.ylabel('Row Indices')
    plt.title('Scatterplot of NaN Values')
    #plt.xticks(rotation=90)  # Rotate column names if necessary
    plt.grid(True)
    #plt.show()
    return nan_rows,nan_cols

# Create a sample DataFrame with NaN values
data = {
            'A': [1, 2, 3, np.nan],
            'B': [np.nan, np.nan, np.nan, np.nan],
            'C': [1, 2, np.nan, 4]
        }
X = pd.DataFrame(data)

# Call the function with the sample DataFrame
nan_rows,nan_cols = plotNanValue(X)