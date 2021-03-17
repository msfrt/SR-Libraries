%By: Nicholas Kopec 2020
%this function can be used to create each line of code that is ued by
%processData_SRXX(). You must change the A variable for each device being
%added. 

function [] = createDataProcessorCmds(chNames, idxStart, idxEnd)

fileID = fopen('Inputs.txt', 'w');

% change this according to the module
A = 'data.MM5.';

B = ' = timeseries( table2array(chData(:,find(string(chNames) == "';
C = '"))), data.xtime);';

format = '%s%s%s%s%s\n';

for i=idxStart:idxEnd
    fprintf(fileID, format, A, chNames{i}(5:end), B, chNames{i}, C);
end    

fclose(fileID);
end

