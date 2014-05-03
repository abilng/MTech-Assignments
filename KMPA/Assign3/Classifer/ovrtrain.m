function [model] = ovrtrain(label, data, cmd)

labelSet = unique(label);
labelSetSize = length(labelSet);
models = cell(labelSetSize,1);

for i=1:labelSetSize
    models{i} = svmtrain(double(label == labelSet(i)), data, cmd);
end

model = struct('models', {models}, 'labelSet', labelSet);
