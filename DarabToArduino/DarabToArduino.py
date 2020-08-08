import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data_file = "sim_data.txt"
column_labels = ["xtime", "enginespeed"]


def load_windarab_log(path, column_labels):
    """
    Loads a file exported by WinDarab's "export text" functionality.
    :param path: string - the file path to the data log
    :param column_labels: list - the labels of the columns as they appear in the txt log file. Ex: ['Time', 'RPM']
    :return: the data frame of the log file
    """

    # load the data using numpy
    data = np.genfromtxt(path, skip_header=6, unpack=False)

    # create a data frame of the data
    df = pd.DataFrame(data)

    # check to make sure the oder is correct for labels!
    df.columns = column_labels

    return df


df = load_windarab_log(data_file, column_labels)
df = df.set_index("xtime")
array = df[column_labels[1]].to_numpy()

output_str = "float data[] = ["

for val in array:
    output_str += "{}, ".format(val)

output_str = output_str[0:-2]
output_str += ']'

print(output_str)
