%By: Nicholas Kopec 2019
%Reads data from darab text file and converts it to a matlab readable
%format

function [data] = darab2matlab()
%DARAB2MATLAB Summary of this function goes here
%   Detailed explanation goes here

%get file path
[fileName, filePath] = uigetfile('.txt', 'Select a DARAB .txt data file');
%file.name = fileName;
%file.path = filePath;

if (fileName ~= 0)
    
    'Processing data......'
    %store the current directory
    scriptDir = pwd;
    fileDir = filePath;   
    
    %switch to the directory containing the selected file
    cd(fileDir);
    fileData = readtable(fileName);
    fileData.Properties.VariableNames;
    
    %switch back to the initial directory
    cd(scriptDir);
    
    for idx = 1:numel(fileData.Properties.VariableNames)
        indices = strfind(fileData.Properties.VariableNames{idx},'_');
        indices = indices(end-1);
        fileData.Properties.VariableNames{idx} = fileData.Properties.VariableNames{idx}(1:indices-1);
    end

    'Processing complete!'
end

%save('data','fileData');

data = fileData;    
end

