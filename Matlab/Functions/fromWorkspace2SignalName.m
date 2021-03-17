function [] = fromWorkspace2SignalName(numBlocks)

BlockNamePre = '/From Workspace';


for i=1:numBlocks
    
    BlockName = strcat(BlockNamePre, num2str(i));
    SigName = get_param([gcb,BlockName],'VariableName');
    SigName = SigName(11:end);
    
    PortHandles = get_param([gcb, BlockName],'PortHandles');
    set_param(PortHandles.Outport(1),'Name',SigName);

end

end


