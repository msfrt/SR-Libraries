# WinDarab Log Data to .csv
A quick script to convert a WinDarab's Log Data to a simple .csv\
– Gabriel Sotelo (2020)


## Purpose
WinDarab, the Data Acquisition software used by the team, allows to export the Log Data to a .txt in a fwf format ("fixed width file"). 
However, this file's format is inconvenient for reading and data handiling purposes.

This script will convert the exported .txt Log Data to a neat and simple .csv file, making it easier to handle and work with the data on it.

## Dependencies
The conversion process performed by the script relies on the [pandas](https://pypi.org/project/pandas/) software library.\
NOTE: This might not be included within the default Python installation. Thus, you may need to [install](https://pandas.pydata.org/pandas-docs/stable/getting_started/install.html)
it in your root Python installation

_Install it through PyPi by running the following command:_

```shell script
pip install pandas
```

## Usage
A default WinDarab's Log Data exported .txt file is required for use. If the execution is successful, a file will be created with the name supplied in the second command line 
argument **-if none is provided, the input filename will be used as default-**.

This Python script is designed to be ran from the command line. You can obtain information about the usage of the script by running:
```shell script
python3 log_to_csv.py -h
```


A complete use case may look like this: _(This usage will output a .csv of name: "log.csv")_
```shell script
python3 log_to_csv.py path/to/my/log.txt
```

If want to specify the output filename, use: _(This usage will output a .csv of name: "new_name.csv")_
```shell script
python3 log_to_csv.py path/to/my/log.txt new_name.csv
```


## Notes
* The current script won't accept a Data Log exported in binary, so make sure to select the fwf format before exporting the Data Log.
* Omitting the output filename in your command can be dangerous, so be completely sure you will not overwrite another file beforehand.
