import unittest
import pandas as pd
import numpy as np
from model_plot_nan_values import plotNanValue  # Make sure to replace this with the correct path if necessary

class TestPlotNanValues(unittest.TestCase):

    def assert_nan_positions(self, expected_nan_rows, expected_nan_cols, data):
        nan_rows, nan_cols = plotNanValue(data)
        self.assertTrue(nan_rows.equals(expected_nan_rows))
        self.assertTrue(nan_cols.equals(expected_nan_cols))

    def test_random_nans(self):
        data1 = {
            'A': [1, np.nan, 3, 4],
            'B': [np.nan, 2, np.nan, 4],
            'C': [1, 2, 3, np.nan]
        }
        X1 = pd.DataFrame(data1)
        
        expected_nan_rows = pd.Index([0, 1, 2, 3])
        expected_nan_cols = pd.Index(['B', 'A', 'B', 'C'])
        
        self.assert_nan_positions(expected_nan_rows, expected_nan_cols, X1)

    def test_no_nans(self):
        data2 = {
            'A': [1, 2, 3, 4],
            'B': [1, 2, 3, 4],
            'C': [1, 2, 3, 4]
        }
        X2 = pd.DataFrame(data2)
        
        expected_nan_rows = pd.Index([])
        expected_nan_cols = pd.Index([])
        
        self.assert_nan_positions(expected_nan_rows, expected_nan_cols, X2)

    def test_nans_in_specific_column(self):
        data3 = {
            'A': [1, 2, 3, np.nan],
            'B': [np.nan, np.nan, np.nan, np.nan],
            'C': [1, 2, np.nan, 4]
        }
        X3 = pd.DataFrame(data3)
        
        # Corrected expected results
        expected_nan_rows = pd.Index([0, 1, 2, 2, 3, 3])
        expected_nan_cols = pd.Index(['B', 'B', 'B', 'C', 'A', 'B'])
        
        self.assert_nan_positions(expected_nan_rows, expected_nan_cols, X3)


if __name__ == '__main__':
    unittest.main(verbosity=2)
