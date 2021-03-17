function [] = setupFromWorkspace(data)

BlockNamePre = '/From Workspace';
VarNamePre = 'data.M400.';

fieldNames = fieldnames(data.M400);

for i=1:length(fieldNames)
    
    BlockName = strcat(BlockNamePre, num2str(i));
    VarName = strcat(VarNamePre, erase(fieldNames{i}, "_"));
    set_param([gcb, BlockName],'VariableName',VarName,'SampleTime','data.tSample');

end

end

