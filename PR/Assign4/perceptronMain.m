% Main

fprintf('Loading Data: ...\n')
[classNo,classList,testData,trainData,trainLabel] = loadData('image'); 
fprintf('Loading Data: finished\n')
W = perceptron(trainData,trainLabel,classNo);
warning('off','MATLAB:NonScalarInput')
confMat = zeros(classNo);
for i = 1:classNo
    % Class
    for j = 1:size(testData{i},2)
        % File
        X = [ones(size(testData{i}{j}),1),testData{i}{j}];
        M=X*W';
        [~,Ind]=max(M,[],2);
        class = mode(Ind); % max voting
        confMat(i,class) = confMat(i,class) + 1;
    end
    fprintf('Classification of class "%s" finished\n',classList{i});
end
accuracy = sum(diag(confMat))/sum(sum(confMat));
disp(confMat);
fprintf('Accuracy = %f\n',accuracy);
clear i j class classNo classList testData trainData trainLabel;