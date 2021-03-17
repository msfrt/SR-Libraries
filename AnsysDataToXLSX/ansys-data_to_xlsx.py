# -*- coding: utf-8 -*-
"""
Created on Mon Jan  4 13:30:45 2021

@author: Gabriel Sotelo Justo
"""
import pandas as pd
import xlsxwriter
import argparse
import os

# Indicate rows and columns to drop from the input file
ROWS_TO_DROP = ["LCA_Joint", "TieRod_Joint", "UCA_Joint", "Probe: Springs", "Spring Probe"]
COLUMNS_TO_DROP = ["Units", "Time (s) ", "Unnamed: 7"]


def fwf_to_df(file):
    """
    The fwf_to_df function takes an input txt file and converts it into a pandas dataframe.
    It will also drop from the dataframe the rows and columns indicated above by the user.
    """
    try:
        df = pd.read_table(file, index_col = 0)
    except:
        print(f"{file} does not exist")
    
    df = df.drop(ROWS_TO_DROP)
    df = df.drop(columns = COLUMNS_TO_DROP)
    
    for col in df.columns:
        df[col] = df[col].astype(float)
    
    return df


def df_to_xlsx(df, filename):
    """
    The df_to_xlsx function takes a dataframe and converts it into a formatted xlsx file.
    """
    writer = pd.ExcelWriter(f'{filename}', engine='xlsxwriter')
    df.to_excel(writer, sheet_name='Resultant Forces')
    
    workbook  = writer.book
    worksheet = writer.sheets['Resultant Forces']
    
    format1 = workbook.add_format({'num_format': '', 'bottom':1, 'top':1, 'left':1, 'right':1})
    worksheet.conditional_format(xlsxwriter.utility.xl_range(0, 0, len(df), len(df.columns)), {'type': 'no_errors','format': format1})
    worksheet.set_column(0, len(df.columns), 20)
    writer.save()
    
    
def main():
    """
    The main function reads command line inputs and calls the defined functions to convert an
    input Ansys data file to a formatted xlsx sheet.
    """
    parser = argparse.ArgumentParser(description='Turn an Ansys data file (.txt) to a xlsx file')
    parser.add_argument('input_file', type=str, 
                        help='The filename (and path if necessary) of the input Ansys data file. (Ex. "ansys_data.txt")')
    parser.add_argument('output_file', type=str, default=None, nargs="?",
                        help='(Optional: Default is input filename). The filename (and path if necessary) of the output xlsx file. (Ex. "ansys_data_1.xlsx")')
    
    args = parser.parse_args()
    
    if args.output_file is None:
        args.output_file = args.input_file.replace("txt", "xlsx")
       
    df = fwf_to_df(args.input_file)
    df_to_xlsx(df, args.output_file)
    os.startfile(args.output_file)


if __name__ == "__main__":
    main()
