# -*- coding: utf-8 -*-
"""
Created on Wed Dec  2 19:39:53 2020

@author: Gabriel Sotelo Justo
"""
import pandas as pd
import argparse


def fwf_to_df(input_file):
    """
    The fwf_to_csv function will first convert the fwf to a df, and then the df to
    to a csv file through the df_to_csv function
    """
    
    try:
        df = pd.read_table(input_file, skiprows=5)
    except:
        print(f"{input_file} does not exist")
    
    return df


def df_to_csv(df, output_file):
    """
    The df_to_csv function will convert a df into a csv file
    """
    
    try:
        df.to_csv(output_file, index=False)
    except:
        print("An error occurred")


def main():
    """
    The main function reads command line inputs and calls the fwf_to_csv function
    """
    
    parser = argparse.ArgumentParser(description='Turn a fwf file to a csv file')
    parser.add_argument('input_file', type=str, 
                        help='The filename (and path if necessary) of the input log file. (Ex. "my_log.txt")')
    parser.add_argument('output_file', type=str, default=None, nargs="?",
                        help='(Optional: Default is input filename). The filename (and path if necessary) of the output csv file. (Ex. "log.csv")')
    
    args = parser.parse_args()
    
    if args.output_file is None:
        args.output_file = args.input_file.replace("txt", "csv")
    
    df = fwf_to_df(args.input_file)
    df_to_csv(df, args.output_file)


if __name__ == "__main__":
    main()
