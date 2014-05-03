function [pred, ac, decv] = ovrpredict(label, data, model,param)

if nargin ==3
    param = '';
end
labelSet = model.labelSet;
labelSetSize = length(labelSet);
models = model.models;
decv= zeros(size(label, 1), labelSetSize);

for i=1:labelSetSize
  [l,a,d] = svmpredict(double(label == labelSet(i)), data, models{i},param);
  decv(:, i) = d * (2 * models{i}.Label(1) - 1);
end
[tmp,pred] = max(decv, [], 2);
pred = labelSet(pred);
ac = sum(label==pred) / size(data, 1);
