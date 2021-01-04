# Ansys Data to Excel
A quick script to convert exported Ansys Data to a formatted and neat Excel table (.xlsx)\
– Gabriel Sotelo (2021)


## Purpose
Ansys, one of the 3D design softwares used by the team, allows to export certain data to a .txt in a fwf format ("fixed width file"). 
However, this file's format is inconvenient for reading and data handiling purposes.

This script will convert the exported .txt Data to a neat and simple .xlsx file, making it easier to handle and work with the data on it.

## Dependencies
The conversion process performed by the script relies on the [pandas](https://pypi.org/project/pandas/) software library.\
The formatting of the information in the table relies on the [XlsxWriter](https://pypi.org/project/XlsxWriter/) software library.\
NOTE: These might not be included within the default Python installation. Thus, you may need to install them:
- [Pandas](https://pandas.pydata.org/pandas-docs/stable/getting_started/install.html)
- [XlsxWriter](https://xlsxwriter.readthedocs.io/getting_started.html)

_Install them through PyPi by running the following commands:_

```shell script
>>> pip install pandas
>>> pip install XlsxWriter
```

## Usage
A default Ansys Data exported .txt file is required for use. If the execution is successful, a file will be created with the name supplied in the second command line 
argument **-if none is provided, the input filename will be used as default-**.

This Python script is designed to be ran from the command line. You can obtain information about the usage of the script by running:
```shell script
python3 ansys-data_to_xlsx.py -h
```


A complete use case may look like this: _(This usage will output a .xlsx of name: "data.xlsx")_
```shell script
python3 ansys-data_to_xlsx.py path/to/my/data.txt
```

If want to specify the output filename, use: _(This usage will output a .xlsx of name: "new_data.xlsx")_
```shell script
python3 ansys-data_to_xlsx.py path/to/my/log.txt new_data.xlsx
```


## Notes
* Omitting the output filename in your command can be dangerous, so be completely sure you will not overwrite another file beforehand.
